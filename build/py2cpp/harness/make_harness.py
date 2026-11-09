#!/usr/bin/env python3
"""
Differential test: run the ORIGINAL python modules against a recording mock of the python `my` module, and the
GENERATED C++ modules against a recording fake of the native layer, then diff the per-module call logs.

  make_harness.py gen    -> writes /tmp/harness/{my_native.hpp,main.cpp}
  make_harness.py py     -> runs python modules, writes /tmp/harness/py.log
  make_harness.py cmp    -> compares /tmp/harness/py.log with /tmp/harness/cpp.log
"""
import ast
import importlib.util
import json
import os
import re
import sys

PYROOT = "/home/claude/python"
SRC = "/home/claude/src"
ORIG = "/tmp/orig/src"
WORK = "/home/claude/work"
H = "/tmp/harness"

sys.path.insert(0, WORK)
import py2cpp  # noqa: E402

TILE_FIELDS = py2cpp.TILE_FIELDS
TILE_STR = py2cpp.TILE_STR_FIELDS
TILE_DEFAULT = {f: (None if f in TILE_STR else (255 if f.endswith("_alpha") else 0)) for f in TILE_FIELDS}

consts_txt = open(f"{ORIG}/python_consts.cpp").read()
CONSTS = dict(re.findall(r'PyModule_AddIntConstant\(\s*my_mod,\s*"(\w+)",\s*([^)]+?)\s*\)', consts_txt))
EXPR_ID = {}
for e in sorted(set(CONSTS.values())):
    EXPR_ID[e] = 1000000 + len(EXPR_ID)

tp_txt = open(f"{ORIG}/py_tp.cpp").read()
TP_SETTERS = {m.group(2): {"INT": "int", "INT_INT": "int_int", "STRING": "str"}[m.group(1)]
              for m in re.finditer(r'^TP_BODY_SET_(INT_INT|INT|STRING)\((\w+)\)', tp_txt, re.M)}
API = json.load(open(f"{WORK}/apitable.json"))


def fmt(v):
    if v is None:
        return "None"
    if isinstance(v, bool):
        return str(int(v))
    if isinstance(v, int):
        return str(v)
    if isinstance(v, float):
        return "%g" % v
    if isinstance(v, str):
        return '"' + v.replace("\\", "\\\\").replace('"', '\\"').replace("\n", "\\n") + '"'
    if isinstance(v, (list, tuple)):
        return "[" + "|".join(fmt(x) for x in v) + "]"
    raise TypeError(type(v))


# -------------------------------------------------------------------------------------------------
def gen():
    os.makedirs(H, exist_ok=True)
    real = open(f"{SRC}/my_native.hpp").read()
    tile_struct = re.search(r'struct TileArgs \{.*?\n\};', real, re.S).group(0)
    api = open(f"{SRC}/my_native_api.hpp").read()
    protos = re.findall(r'^([\w:<>, \*]+?)\s+(\w+)\((.*)\);\s*$', api, re.M)
    out = []
    out.append('''#pragma once
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>
namespace hlog {
inline std::string s(const std::string &v) { std::string o = "\\""; for (char c : v) { if (c == '\\\\') o += "\\\\\\\\"; else if (c == '"') o += "\\\\\\""; else if (c == '\\n') o += "\\\\n"; else o += c; } return o + "\\""; }
inline std::string f(int v) { return std::to_string(v); }
inline std::string f(unsigned v) { return std::to_string(v); }
inline std::string f(long v) { return std::to_string(v); }
inline std::string f(bool v) { return v ? "1" : "0"; }
inline std::string f(double v) { char b[64]; snprintf(b, sizeof b, "%g", v); return b; }
inline std::string f(float v) { return f((double) v); }
inline std::string f(const char *v) { return v ? s(v) : "None"; }
inline std::string f(const std::string &v) { return s(v); }
inline std::string f(const std::vector< std::string > &v) { std::string o = "["; for (size_t i = 0; i < v.size(); i++) { if (i) o += "|"; o += s(v[i]); } return o + "]"; }
inline std::string f(const std::optional< std::string > &v) { return v ? s(*v) : "None"; }
inline void line(const std::string &l) { puts(l.c_str()); }
}
''')
    out.append("enum : int {")
    for e, i in EXPR_ID.items():
        if re.fullmatch(r'[A-Za-z_]\w*', e):
            out.append(f"  {e} = {i},")
    out.append("};")
    out.append(tile_struct)
    out.append("struct NativeRet { int value {}; std::vector< std::string > strings; };")
    out.append("using NativeFn = std::function< NativeRet(const int64_t *) >;")
    out.append('inline void native_register(const char *m, const char *n, int nargs, NativeFn) { hlog::line(std::string("REG ") + m + " " + n + " " + std::to_string(nargs)); }')
    out.append("void native_init_all(void);")
    out.append("inline int d4() { return 0; } inline int d6() { return 0; } inline int d20() { return 0; } inline int d100() { return 0; }")
    out.append("struct FakeTp {")
    for n, fam in TP_SETTERS.items():
        if fam == "int":
            out.append(f'  void {n}_set(int v) {{ hlog::line("SET {n} " + hlog::f(v)); }}')
        elif fam == "str":
            out.append(f'  void {n}_set(const std::string &v) {{ hlog::line("SET {n} " + hlog::f(v)); }}')
        else:
            out.append(f'  void {n}_set(int a, int b) {{ hlog::line("SET2 {n} " + hlog::f(a) + " " + hlog::f(b)); }}')
    out.append("};")
    out.append("using Tpp = FakeTp *;")
    out.append("namespace my {")
    out.append('''inline Tpp tp_load(const std::string &n, const std::string &l, const std::string &s) { hlog::line("TP " + hlog::f(n) + " " + hlog::f(l) + " " + hlog::f(s)); return new FakeTp; }
inline Tpp tp_load(const std::string &n, const std::string &l) { return tp_load(n, l, l); }
inline Tpp tp_load(const std::string &n) { return tp_load(n, n, n); }
inline int ipow2(int v) { return v * v; }
template < typename T > inline const T &random_choice(const std::vector< T > &v) { return v.at(0); }
inline int pcg_random_inclusive(int lo, int) { return lo; }
inline int non_pcg_random_inclusive(int lo, int) { return lo; }
inline void log(const char *) {}
inline void topcon(const char *) {}
inline void game_set_request_to_update_same_level(void) {}''')
    tilecalls = "\n".join(f'''inline bool {n}(Tpp, const TileArgs &a) {{ std::string o = "TILE {n}";
{"".join(f'  o += " {fld}=" + hlog::f(a.{fld});' + chr(10) for fld in TILE_FIELDS)}  hlog::line(o); return true; }}''' for n in sorted(py2cpp.TILE_FUNCS))
    out.append(tilecalls)
    # api stubs from prototypes
    for ret, name, params in protos:
        plist = [p.strip() for p in re.split(r',\s*(?![^<]*>)', params) if p.strip()]
        pn = []
        for p in plist:
            left = p.split("=")[0].strip()
            pn.append(re.search(r'(\w+)\s*$', left).group(1))
        body = " ".join(f'o += " {n}=" + hlog::f({n});' for n in pn)
        out.append(f'inline {ret} {name}({params}) {{ std::string o = "CALL {name}"; {body} hlog::line(o); return {ret}(); }}')
    out.append("} // namespace my")
    open(f"{H}/my_native.hpp", "w").write("\n".join(out))

    # main: run every module in load order
    prog = py2cpp.Program(PYROOT, SRC, WORK, ORIG)
    prog.load()
    main = ['#include "my_native.hpp"']
    for m in prog.modules:
        main.append(f"namespace {m.ns} {{ void module_init(void); }}")
    main.append("int main() {")
    for m in prog.modules:
        main.append(f'  puts("BEGIN {m.relpath}"); {m.ns}::module_init();')
    main.append("  return 0; }")
    open(f"{H}/main.cpp", "w").write("\n".join(main))
    print("harness generated:", len(protos), "api stubs,", len(TP_SETTERS), "tp setters")


# -------------------------------------------------------------------------------------------------
class Recorder:
    def __init__(self):
        self.lines = []

    def add(self, s):
        self.lines.append(s)


REC = Recorder()


def num_const(name):
    return EXPR_ID[CONSTS[name]]


class TpObj:
    def __init__(self, name, long_=None, short=None):
        self.name = name
        self.text_long_name = name if long_ is None else long_
        self.text_short_name = self.text_long_name if short is None else short
        REC.add(f"TP {fmt(self.name)} {fmt(self.text_long_name)} {fmt(self.text_short_name)}")


class MyMod:
    """Mock of the python `my` module. Records calls in the same textual form as the C++ fake."""

    def __getattr__(self, name):
        if name.startswith("__"):
            raise AttributeError(name)
        if name in CONSTS:
            return num_const(name)
        if name in TP_SETTERS:
            fam = TP_SETTERS[name]

            def setter(cls, *a):
                if fam == "int":
                    REC.add(f"SET {name} {fmt(int(a[0]) if a else 0)}")
                elif fam == "str":
                    REC.add(f"SET {name} {fmt(a[0])}")
                else:
                    REC.add(f"SET2 {name} {fmt(int(a[0]))} {fmt(int(a[1]))}")
            return setter
        if name in py2cpp.TILE_FUNCS:
            def tile(cls, *pos, **kw):
                vals = dict(TILE_DEFAULT)
                for f, v in zip(TILE_FIELDS, pos):
                    vals[f] = v
                for k, v in kw.items():
                    if k not in TILE_FIELDS:
                        raise TypeError(f"{name}: bad keyword {k}")
                    vals[k] = v
                o = f"TILE {name}"
                for f in TILE_FIELDS:
                    v = vals[f]
                    o += f" {f}={fmt(v if f in TILE_STR or v is None else int(v))}"
                REC.add(o)
            return tile
        if name in ("tp_update", "tp_load"):
            return lambda *a, **k: None
        if name in API:
            e = API[name]
            pn = [p for p, _ in e["params"]]
            kwn = e.get("kwnames") or pn

            def call(*a, **k):
                vals = dict(zip(pn, a))
                for kk, v in k.items():
                    t = pn[kwn.index(kk)] if kk in kwn else kk
                    vals[t] = v
                REC.add("CALL " + name + "".join(f" {p}={fmt(vals[p])}" for p in pn if p in vals))
                return None
            return call
        return lambda *a, **k: 0


def run_py():
    my = MyMod()
    tpmod = type(sys)("tp")
    tpmod.Tp = TpObj
    sys.modules["my"] = my
    sys.modules["tp"] = tpmod
    for d in [PYROOT] + [os.path.join(PYROOT, "things", x) for x in os.listdir(os.path.join(PYROOT, "things"))]:
        sys.path.append(d)
    prog = py2cpp.Program(PYROOT, SRC, WORK, ORIG)
    prog.load()
    for m in prog.modules:
        REC.add(f"BEGIN {m.relpath}")
        spec = importlib.util.spec_from_file_location(m.stem + "__run", os.path.join(PYROOT, m.relpath))
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
    open(f"{H}/py.log", "w").write("\n".join(REC.lines) + "\n")
    print("python log lines:", len(REC.lines))


def split_blocks(path):
    blocks, cur = {}, None
    for l in open(path).read().splitlines():
        if l.startswith("BEGIN "):
            cur = l[6:]
            blocks[cur] = []
        elif cur is not None:
            blocks[cur].append(l)
    return blocks


def parse_kv(line):
    """'CALL fn a=1 b="x y" c=[..]' -> (fn, ordered dict) using a tolerant tokenizer"""
    m = re.match(r'CALL (\w+)(.*)$', line)
    fn, rest = m.group(1), m.group(2)
    d = {}
    for mm in re.finditer(r' (\w+)=("(?:[^"\\]|\\.)*"|\[(?:[^\]\\"]|"(?:[^"\\]|\\.)*"|\\.)*\]|\S+)', rest):
        d[mm.group(1)] = mm.group(2)
    return fn, d


def compare():
    py = split_blocks(f"{H}/py.log")
    cpp = split_blocks(f"{H}/cpp.log")
    bad = 0
    if list(py) != list(cpp):
        print("MODULE ORDER/SET DIFFERS", len(py), len(cpp))
        bad += 1
    for rel, plines in py.items():
        clines = [l for l in cpp.get(rel, []) if not l.startswith("REG ")]
        if len(plines) != len(clines):
            print(f"DIFF {rel}: {len(plines)} python lines vs {len(clines)} c++ lines")
            bad += 1
            for a, b in zip(plines, clines):
                if a != b and not (a.startswith("CALL") and b.startswith("CALL")):
                    print("   first mismatch:", a[:150], "||", b[:150])
                    break
            continue
        for a, b in zip(plines, clines):
            if a == b:
                continue
            if a.startswith("CALL ") and b.startswith("CALL "):
                fa, da = parse_kv(a)
                fb, db = parse_kv(b)
                if fa == fb and all(db.get(k) == v or (k in db and _num_eq(db[k], v)) for k, v in da.items()):
                    continue
            print(f"DIFF {rel}:\n   py : {a[:200]}\n   c++: {b[:200]}")
            bad += 1
            break
    print(f"compared {len(py)} modules: {bad} with differences")
    return bad


def _num_eq(a, b):
    try:
        return float(a) == float(b)
    except ValueError:
        return False


if __name__ == "__main__":
    {"gen": gen, "py": run_py, "cmp": compare}[sys.argv[1]]()
