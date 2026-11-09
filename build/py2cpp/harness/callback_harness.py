#!/usr/bin/env python3
"""
Differential test of callbacks. Both sides get a fake API whose return values are a deterministic hash of
(function name, formatted arguments, call counter), so the python original and the C++ translation see
identical "world" responses; their call logs and return values must then be identical.

  callback_harness.py gen   -> /tmp/harness2/{my_native.hpp,main.cpp,vectors.txt}
  callback_harness.py py    -> /tmp/harness2/py.log
  callback_harness.py cmp
"""
import importlib.util
import os
import random
import re
import sys

sys.path.insert(0, "/home/claude/work")
sys.path.insert(0, "/home/claude/work/harness")
import make_harness as mh  # noqa: E402
import py2cpp  # noqa: E402

H2 = "/tmp/harness2"
PYROOT, SRC, WORK, ORIG = mh.PYROOT, mh.SRC, mh.WORK, mh.ORIG
K = int(os.environ.get("K","90"))


def fnv(s):
    h = 0xcbf29ce484222325
    for b in s.encode():
        h ^= b
        h = (h * 0x100000001b3) & 0xFFFFFFFFFFFFFFFF
    return h


class World:
    counter = 0
    enabled = True
    log = []


VARIANT = os.environ.get("VARIANT", "A")


def derive(ret, h):
    """Map a hash to a value of the api return type (mirrors the C++ side)."""
    if VARIANT in ("C", "D"):
        if ret == "bool":
            return VARIANT == "C"
        if ret == "int":
            return (h >> 7) % 4
        if ret == "thing":
            return (h >> 9) % 4 + 1
        if ret == "str":
            return "s" + str((h >> 11) % 3)
        if ret == "list_thing":
            n = 1 + (h >> 13) % 3
            return [1 + ((h >> (17 + 3 * i)) % 4) for i in range(n)]
        if ret == "pair_int":
            return ((h >> 21) % 10, (h >> 25) % 10)
        if ret == "float":
            return ((h >> 7) % 4) / 2.0
    if VARIANT == "B":
        if ret == "bool":
            return ((h >> 5) & 3) != 0
        if ret == "int":
            return (h >> 7) % 12
        if ret == "thing":
            return (h >> 9) % 4 + 1
        if ret == "str":
            return "s" + str((h >> 11) % 3)
        if ret == "list_thing":
            n = (h >> 13) % 5
            return [1 + ((h >> (17 + 3 * i)) % 4) for i in range(n)]
        if ret == "pair_int":
            return ((h >> 21) % 10, (h >> 25) % 10)
        if ret == "float":
            return ((h >> 7) % 12) / 2.0
    if ret == "bool":
        return bool((h >> 5) & 1)
    if ret == "int":
        return (h >> 7) % 9
    if ret == "thing":
        return (h >> 9) % 5
    if ret == "str":
        return "s" + str((h >> 11) % 3)
    if ret == "list_thing":
        n = (h >> 13) % 4
        return [1 + ((h >> (17 + 3 * i)) % 4) for i in range(n)]
    if ret == "pair_int":
        return ((h >> 21) % 10, (h >> 25) % 10)
    if ret == "float":
        return ((h >> 7) % 9) / 2.0
    raise ValueError(ret)


class Abort(Exception):
    pass


CAP = 4000


def world_call(name, argstr, ret):
    if World.counter > CAP:
        raise Abort()
    s = f"{name}|{argstr}|{World.counter}"
    World.counter += 1
    h = fnv(s)
    if World.enabled:
        World.log.append("CALL " + name + argstr)
    return derive(ret, h) if ret else None, h


DEFAULT_EVAL = {"nullptr": None, "NO_VALUE": -99999, "{}": [], "true": 1, "false": 0}


def eval_default(txt):
    if txt in DEFAULT_EVAL:
        return DEFAULT_EVAL[txt]
    try:
        return int(txt)
    except ValueError:
        return float(txt)


class MyMod:
    def __getattr__(self, name):
        if name.startswith("__"):
            raise AttributeError(name)
        if name in mh.CONSTS:
            return mh.num_const(name)
        if name in ("tp_update", "tp_load"):
            return lambda *a, **k: None
        if name in ("py_pcg_random_range_inclusive", "py_non_pcg_random_range_inclusive"):
            new = "pcg_random" if "non" not in name else "non_pcg_random"

            def rnd(lo, hi):
                _, h = world_call(new, f" lo={mh.fmt(int(lo))} hi={mh.fmt(int(hi))}", None)
                if os.environ.get("RND") == "hi":
                    return hi if hi > lo else lo
                return lo + (h >> 3) % (hi - lo + 1) if hi > lo else lo
            return rnd
        if name in ("py_d4", "py_d6", "py_d20", "py_d100"):
            n = int(name[4:])

            def die():
                _, h = world_call("d" + str(n), "", None)
                return 1 + (h >> 3) % n
            return die
        if name in ("log", "topcon"):
            return lambda s: world_call("my_" + name, " msg=" + mh.fmt(s), None) and None
        if name == "game_set_request_to_update_same_level":
            return lambda: world_call(name, "", None) and None
        if name in mh.API:
            e = mh.API[name]
            pn = [p for p, _ in e["params"]]
            kwn = e.get("kwnames") or pn
            defaults = e.get("defaults", {})

            def call(*a, **k):
                vals = dict(zip(pn, a))
                for kk, v in k.items():
                    vals[pn[kwn.index(kk)] if kk in kwn else kk] = v
                for p in pn:
                    if p not in vals:
                        vals[p] = eval_default(defaults[p])
                argstr = "".join(f" {p}={mh.fmt(vals[p])}" for p in pn)
                v, _ = world_call(name, argstr, e["ret"])
                if name == "thing_all_followers_get" and v == []:
                    return None      # the real python api returned None when there were no followers
                return v
            return call
        raise AttributeError(f"unmocked my.{name}")


def make_vectors(prog):
    rng = random.Random(int(os.environ.get("SEED","987")))
    vec = []
    for m in prog.modules:
        for f in prog.active_funcs(m):
            sig = prog.sigs[(m.relpath, f.name)]
            if not prog.eligible(sig):
                continue
            for _ in range(K):
                args = []
                for p in sig.params:
                    if p in py2cpp.THING_PARAMS:
                        args.append(rng.choice([0, 1, 2, 3, 4, 5]))
                    elif p in ("damage", "damage_reduction_percent", "bonus"):
                        args.append(rng.randint(0, 40))
                    else:
                        args.append(rng.randint(-2, 12))
                vec.append((m.stem, m.relpath, f.name, args))
    return vec


def gen():
    os.makedirs(H2, exist_ok=True)
    prog = py2cpp.Program(PYROOT, SRC, WORK, ORIG)
    prog.load(); prog.build_sigs(); prog.assign_kinds(); prog.infer_all()
    vec = make_vectors(prog)
    with open(f"{H2}/vectors.txt", "w") as fh:
        for stem, rel, fn, args in vec:
            fh.write(f"{stem} {fn} {rel} {' '.join(map(str, args))}\n")

    real = open(f"{SRC}/my_native.hpp").read()
    tile_struct = re.search(r'struct TileArgs \{.*?\n\};', real, re.S).group(0)
    api = open(f"{SRC}/my_native_api.hpp").read()
    protos = re.findall(r'^([\w:<>, \*]+?)\s+(\w+)\((.*)\);\s*$', api, re.M)
    o = []
    o.append(open(f"{mh.H}/my_native.hpp").read().split("enum : int {")[0])   # hlog helpers etc
    o.append("enum : int {")
    for e, i in mh.EXPR_ID.items():
        if re.fullmatch(r'[A-Za-z_]\w*', e):
            o.append(f"  {e} = {i},")
    o.append("};")
    o.append(tile_struct)
    o.append('''
#include <map>
struct NativeRet { int value {}; std::vector< std::string > strings; };
using NativeFn = std::function< NativeRet(const int64_t *) >;
struct Reg { int nargs; NativeFn fn; };
inline std::map< std::pair< std::string, std::string >, Reg > &registry() { static std::map< std::pair< std::string, std::string >, Reg > r; return r; }
inline void native_register(const char *m, const char *n, int nargs, NativeFn fn) { registry()[{m, n}] = Reg {nargs, fn}; }
void native_init_all(void);
struct FakeTp { };
using Tpp = FakeTp *;
namespace world {
inline unsigned long long counter = 0;
inline bool enabled = true;
inline unsigned long long fnv(const std::string &s) { unsigned long long h = 0xcbf29ce484222325ULL; for (unsigned char b : s) { h ^= b; h *= 0x100000001b3ULL; } return h; }
struct Abort {};
inline unsigned long long call(const char *name, const std::string &args) {
  if (counter > 4000) throw Abort();
  std::string s = std::string(name) + "|" + args + "|" + std::to_string(counter++);
  if (enabled) hlog::line(std::string("CALL ") + name + args);
  return fnv(s);
}
template < typename T > T derive(unsigned long long h);
template <> inline bool derive< bool >(unsigned long long h) { return (h >> 5) & 1; }
template <> inline int derive< int >(unsigned long long h) { return (int) ((h >> 7) % 9); }
template <> inline uint32_t derive< uint32_t >(unsigned long long h) { return (uint32_t) ((h >> 9) % 5); }
template <> inline std::string derive< std::string >(unsigned long long h) { return "s" + std::to_string((h >> 11) % 3); }
template <> inline std::vector< uint32_t > derive< std::vector< uint32_t > >(unsigned long long h) { std::vector< uint32_t > v; unsigned n = (h >> 13) % 4; for (unsigned i = 0; i < n; i++) v.push_back(1 + ((h >> (17 + 3 * i)) % 4)); return v; }
template <> inline std::pair< int, int > derive< std::pair< int, int > >(unsigned long long h) { return {(int) ((h >> 21) % 10), (int) ((h >> 25) % 10)}; }
}
inline int d4() { return 1 + (world::call("d4", "") >> 3) % 4; }
inline int d6() { return 1 + (world::call("d6", "") >> 3) % 6; }
inline int d20() { return 1 + (world::call("d20", "") >> 3) % 20; }
inline int d100() { return 1 + (world::call("d100", "") >> 3) % 100; }
namespace my {
inline int ipow2(int v) { return v * v; }
inline int pcg_random_inclusive(int lo, int hi) { auto h = world::call("pcg_random", " lo=" + hlog::f(lo) + " hi=" + hlog::f(hi)); return hi > lo ? lo + (int) ((h >> 3) % (unsigned long long) (hi - lo + 1)) : lo; }
inline int non_pcg_random_inclusive(int lo, int hi) { auto h = world::call("non_pcg_random", " lo=" + hlog::f(lo) + " hi=" + hlog::f(hi)); return hi > lo ? lo + (int) ((h >> 3) % (unsigned long long) (hi - lo + 1)) : lo; }
inline void log(const char *s) { world::call("my_log", " msg=" + hlog::f(s)); }
inline void topcon(const char *s) { world::call("my_topcon", " msg=" + hlog::f(s)); }
inline void game_set_request_to_update_same_level(void) { world::call("game_set_request_to_update_same_level", ""); }
template < typename T > inline const T &random_choice(const std::vector< T > &v) { auto h = world::call("random_choice", ""); return v.at((h >> 3) % v.size()); }
inline Tpp tp_load(const std::string &, const std::string &, const std::string &) { return new FakeTp; }
inline Tpp tp_load(const std::string &, const std::string &) { return new FakeTp; }
inline Tpp tp_load(const std::string &) { return new FakeTp; }
''')
    for n in sorted(py2cpp.TILE_FUNCS):
        o.append(f"inline bool {n}(Tpp, const TileArgs &) {{ return true; }}")
    for ret, name, params in protos:
        plist = [p.strip() for p in re.split(r',\s*(?![^<]*>)', params) if p.strip()]
        pn = [re.search(r'(\w+)\s*$', p.split("=")[0].strip()).group(1) for p in plist]
        argexpr = " + ".join(f'" {n}=" + hlog::f({n})' for n in pn) or '""'
        o.append(f'inline {ret} {name}({params}) {{ auto h = world::call("{name}", {argexpr}); return world::derive< {ret.strip()} >(h); }}')
    o.append("} // namespace my")
    # fake Tp setters are not needed for callbacks, but tp_init is also run (logging disabled); provide a catch-all
    setters = []
    for n, fam in mh.TP_SETTERS.items():
        setters.append(f"  void {n}_set(" + {"int": "int", "str": "const std::string &", "int_int": "int, int"}[fam] + ") {}")
    text = "\n".join(o)
    if VARIANT in ("C", "D"):
        text = text.replace("{ return (h >> 5) & 1; }", "{ return %s; }" % ("true" if VARIANT == "C" else "false"))
        text = text.replace("{ return (int) ((h >> 7) % 9); }", "{ return (int) ((h >> 7) % 4); }")
        text = text.replace("{ return (uint32_t) ((h >> 9) % 5); }", "{ return (uint32_t) ((h >> 9) % 4 + 1); }")
        text = text.replace("unsigned n = (h >> 13) % 4;", "unsigned n = 1 + (h >> 13) % 3;")
    if VARIANT == "B":
        text = text.replace("{ return (h >> 5) & 1; }", "{ return ((h >> 5) & 3) != 0; }")
        text = text.replace("{ return (int) ((h >> 7) % 9); }", "{ return (int) ((h >> 7) % 12); }")
        text = text.replace("{ return (uint32_t) ((h >> 9) % 5); }", "{ return (uint32_t) ((h >> 9) % 4 + 1); }")
        text = text.replace("unsigned n = (h >> 13) % 4;", "unsigned n = (h >> 13) % 5;")
    if os.environ.get("RND") == "hi":
        text = text.replace("return hi > lo ? lo + (int) ((h >> 3) % (unsigned long long) (hi - lo + 1)) : lo;", "(void) h; return hi > lo ? hi : lo;")
    text = text.replace("struct FakeTp { };", "struct FakeTp {\n" + "\n".join(setters) + "\n};")
    open(f"{H2}/my_native.hpp", "w").write(text)

    main = ['#include "my_native.hpp"', "#include <fstream>", "#include <sstream>"]
    for m in prog.modules:
        main.append(f"namespace {m.ns} {{ void module_init(void); }}")
    main.append('''
int main() {
  world::enabled = false;
  native_init_all();
  std::ifstream in("/tmp/harness2/vectors.txt");
  std::string line;
  while (std::getline(in, line)) {
    std::istringstream is(line);
    std::string mod, fn, rel; is >> mod >> fn >> rel;
    std::vector< int64_t > a; long long v; while (is >> v) a.push_back(v);
    auto it = registry().find({mod, fn});
    std::string head = "CB " + mod + " " + fn;
    for (auto x : a) head += " " + std::to_string(x);
    hlog::line(head);
    if (it == registry().end() || it->second.nargs != (int) a.size()) { hlog::line("NOTREGISTERED"); continue; }
    world::counter = 0; world::enabled = true;
    a.push_back(0);
    NativeRet r;
    try { r = it->second.fn(a.data()); } catch (world::Abort &) { world::enabled = false; hlog::line("ABORT"); continue; }
    world::enabled = false;
    std::string out = "RET " + std::to_string(r.value);
    for (auto &s : r.strings) out += " " + hlog::s(s);
    hlog::line(out);
  }
  return 0;
}''')
    open(f"{H2}/main.cpp", "w").write("\n".join(main))
    print("vectors:", len(vec))


def run_py():
    import random as pyrandom
    my = MyMod()
    tpmod = type(sys)("tp")

    class TpObj:
        def __init__(self, *a):
            self.name = a[0]
    tpmod.Tp = TpObj
    sys.modules["my"] = my
    sys.modules["tp"] = tpmod

    def choice(seq):
        _, h = world_call("random_choice", "", None)
        return seq[(h >> 3) % len(seq)]
    pyrandom.choice = choice
    for d in [PYROOT] + [os.path.join(PYROOT, "things", x) for x in os.listdir(os.path.join(PYROOT, "things"))]:
        sys.path.append(d)
    prog = py2cpp.Program(PYROOT, SRC, WORK, ORIG)
    prog.load(); prog.build_sigs(); prog.assign_kinds()
    # tp_init runs at import: the fake `my` accepts any setter
    class Any(MyMod):
        def __getattr__(self, name):
            if name in mh.TP_SETTERS or name in py2cpp.TILE_FUNCS:
                return lambda *a, **k: None
            return MyMod.__getattr__(self, name)
    sys.modules["my"] = Any()
    World.enabled = False
    mods = {}
    for m in prog.modules:
        spec = importlib.util.spec_from_file_location(m.stem + "__cb", os.path.join(PYROOT, m.relpath))
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        mods[m.relpath] = mod
    out = []
    kinds = {}
    for line in open(f"{H2}/vectors.txt"):
        stem, fn, rel, *args = line.split()
        args = [int(x) for x in args]
        out.append(f"CB {stem} {fn}" + "".join(f" {a}" for a in args))
        World.counter = 0
        World.log = []
        World.enabled = True
        try:
            r = getattr(mods[rel], fn)(*args)
            exc = None
        except Exception as e:  # noqa: BLE001
            r, exc = None, e
        World.enabled = False
        if exc is not None:
            out.append(f"EXC {type(exc).__name__}")
            continue
        out += World.log
        sig = prog.sigs[(rel, fn)]
        if sig.kind == "void":
            out.append("RET 0")
        elif isinstance(r, list):
            out.append("RET 0 " + " ".join(mh.fmt(x) for x in r))
        elif r is None:
            out.append("RET 0")
        else:
            out.append(f"RET {int(r)}")
    open(f"{H2}/py.log", "w").write("\n".join(out) + "\n")
    print("python callback log lines:", len(out))


def blocks(path):
    res, cur = [], None
    for l in open(path).read().splitlines():
        if l.startswith("CB "):
            cur = [l]
            res.append(cur)
        elif cur is not None:
            cur.append(l)
    return res


def compare():
    py, cpp = blocks(f"{H2}/py.log"), blocks(f"{H2}/cpp.log")
    print("blocks:", len(py), len(cpp))
    bad = skipped = 0
    seen = set()
    for a, b in zip(py, cpp):
        if a[0] != b[0]:
            print("ORDER MISMATCH", a[0], b[0])
            return 1
        if len(a) == 2 and a[1].startswith("EXC"):
            skipped += 1
            seen.add(a[0].split()[1] + "." + a[0].split()[2] + ":" + a[1])
            continue
        if a != b:
            bad += 1
            if bad <= 12:
                print("DIFF", a[0])
                for i, (x, y) in enumerate(zip(a, b)):
                    if x != y:
                        print("   py :", x[:200]); print("   c++:", y[:200]); break
                else:
                    print("   length", len(a), len(b))
    print(f"compared {len(py) - skipped} callback runs: {bad} differences; {skipped} python-side exceptions skipped")
    if seen:
        print("exceptions (python):", sorted(seen)[:10])
    return bad


if __name__ == "__main__":
    {"gen": gen, "py": run_py, "cmp": compare}[sys.argv[1]]()
