#!/usr/bin/env python3
"""
One-shot generator: ports the Python C-API wrapper functions that the game's python
modules relied on into plain C++ functions in `namespace my`.

Bodies of hand-written wrappers are preserved verbatim; only the Python argument
parsing and Py_RETURN_*/Py_BuildValue returns are replaced.

Outputs (under SRC):
  native_thing.cpp   thing_* / spawn_* / place_at / thing getters+setters
  native_level.cpp   level_* helpers
  my_native_api.hpp  prototypes for everything above (included by my_native.hpp)
  work/apitable.json signature table consumed by the py2cpp transpiler
"""
import json, os, re, sys

SRC = "/tmp/orig/src"          # original (python-enabled) sources to read
OUT = "/home/claude/src"       # where generated native sources go
WORK = "/home/claude/work"

used = json.load(open("/tmp/an/used.json"))
groups = json.load(open("/tmp/an/groups.json"))

def rd(f):
    return open(os.path.join(SRC, f), encoding="utf-8").read()

# ---------------------------------------------------------------------------
# helpers
# ---------------------------------------------------------------------------
FMT_CTYPE = {"I": "uint32_t", "i": "int", "s": "const char *", "f": "float", "d": "double", "O": "const std::vector< std::string > &"}

def func_text(src, name):
    m = re.search(r'^(?:static )?PyObject \*' + re.escape(name) + r'\(PyObject \*[^\n]*\n\{', src, re.M)
    if not m:
        return None
    end = src.index("\n}\n", m.end()) + 3
    return src[m.start():end]

def strip_py_dbg(body):
    return re.sub(r'\n[ \t]*PY_DBG\((?:[^;]|\n)*?\);[ \t]*(?=\n)', '', body)

# ---------------------------------------------------------------------------
# macro families (thing/level getters + setters) -> native macros
# ---------------------------------------------------------------------------
macro_inv = re.compile(r'^(THING_BODY_[A-Z_]+|LEVEL_BODY_[A-Z_]+)\(\s*(\w+)\s*,\s*(\w+)\s*\)\s*$', re.M)
macro_defs = {}
for f in ("py_thing_get.cpp", "py_thing_set.cpp", "py_level.cpp"):
    for m in macro_inv.finditer(rd(f)):
        macro_defs.setdefault(m.group(2), (m.group(1), m.group(3)))

MACRO_RET = {
    "THING_BODY_GET_BOOL": ("bool", [("id", "uint32_t")]),
    "THING_BODY_GET_INT": ("int", [("id", "uint32_t")]),
    "THING_BODY_GET_STRING": ("std::string", [("id", "uint32_t")]),
    "THING_BODY_GET_THING": ("uint32_t", [("id", "uint32_t")]),
    "THING_BODY_SET_INT": ("int", [("id", "uint32_t"), ("value", "int")]),
    "THING_BODY_SET_THING": ("uint32_t", [("id", "uint32_t"), ("oid", "uint32_t")]),
    "LEVEL_BODY_GET_BOOL_AT": ("bool", [("id", "uint32_t"), ("x", "int"), ("y", "int")]),
}

# Show the exact macro bodies so the native versions can mirror them
def macro_body(src, name):
    m = re.search(r'^#define ' + name + r'\(.*?(?=^\S)', src, re.M | re.S)
    return m.group(0) if m else None

api = {}   # name -> {"params":[(n,ctype,default)], "ret": "..."}

# ---------------------------------------------------------------------------
# Hand-written wrappers: scripted transformation
# ---------------------------------------------------------------------------
HAND_SOURCES = ["py_thing.cpp", "py_thing_hit.cpp", "py_tp.cpp", "py_level.cpp", "py_tile.cpp", "py_tex.cpp", "py_music.cpp", "py_sound.cpp", "py_room.cpp", "py_skill_tree.cpp", "py_spell_tree.cpp"]
hand_src = {f: rd(f) for f in HAND_SOURCES}

def find_hand(name):
    for f, s in hand_src.items():
        for cand in (name + "_", name):
            t = func_text(s, cand)
            if t:
                return cand, t
    return None, None

# Functions handled by hand-written native code instead of the transform
MANUAL = {
    "level_get_all", "level_flood_fill_get_all_things", "level_flood_fill_gas_get_all_grid_things",
    "thing_all_followers_get", "thing_get_followers", "thing_coords_get",
    "tp_load", "tp_update",
    "thing_hit", "thing_hit_dmg_energy", "thing_hit_dmg_fire", "thing_hit_dmg_impact",
    "thing_hit_dmg_missile", "thing_hit_dmg_poison", "thing_hit_dmg_stamina",
}

def transform(name, text):
    """Return (ret_type, params, native_source). params: [(name, ctype, default|None)]"""
    kw = re.search(r'kwlist\[\]\s*=\s*\{(.*?)\};', text, re.S)
    kwnames = re.findall(r'"(\w+)"', kw.group(1)) if kw else []
    pm = re.search(r'PyArg_ParseTupleAndKeywords\(\s*args,\s*keywds,\s*"([^"]*)",\s*kwlist((?:[^;]|\n)*?)\)\)\s*\{', text)
    fmt = pm.group(1) if pm else ""
    vars_ = re.findall(r'&(\w+)', pm.group(2)) if pm else []
    optional_from = fmt.index("|") if "|" in fmt else None
    fchars = [c for c in fmt if c not in "|:"]
    if len(vars_) > len(fchars):
        print('note: %s passes %d pointers for format %r; extra ignored' % (name, len(vars_), fmt), file=sys.stderr)
        extras = vars_[len(fchars):]
        vars_ = vars_[:len(fchars)]
        for ev in extras:
            text = re.sub(r'^[ \t]*[\w:\* ]+?[ \t]+' + re.escape(ev) + r'[ \t]*(?:=[^;]*)?;[ \t]*\n', '', text, count=1, flags=re.M)
    assert len(fchars) == len(vars_), (name, fmt, vars_)
    # declarations of those vars -> default init values
    params = []
    body = text
    for idx, (v, c) in enumerate(zip(vars_, fchars)):
        dm = re.search(r'^[ \t]*([\w:\* ]+?)[ \t]+\*?' + re.escape(v) + r'[ \t]*(?:=[ \t]*([^;]+))?;[ \t]*\n', body, re.M)
        init = dm.group(2).strip() if dm and dm.group(2) else None
        is_opt = optional_from is not None and idx >= optional_from
        ctype = FMT_CTYPE[c]
        if c == "s" and dm and "const" in dm.group(1):
            ctype = "const char *"
        if c == 'O' and is_opt:
            init = '{}'
        params.append([v, ctype, init if is_opt else None])
        if dm:
            body = body.replace(dm.group(0), "", 1)
    # kwlist decl + parse block
    body = re.sub(r'[ \t]*static char \*kwlist\[\][^;]*;[ \t]*\n', '', body)
    pm2 = re.search(r'[ \t]*if \(! PyArg_ParseTupleAndKeywords\((?:[^;]|\n)*?\)\) \{\n(?:.*\n)*?[ \t]*\}\n', body)
    if pm2:
        body = body[:pm2.start()] + body[pm2.end():]
    # return type
    ret_id = 'Py_BuildValue("I"' in body
    ret_t = "uint32_t" if ret_id else "bool"
    falsev = "0" if ret_id else "false"
    body = body.replace("Py_RETURN_TRUE;", "return true;")
    body = body.replace("Py_RETURN_FALSE;", f"return {falsev};")
    body = body.replace("Py_RETURN_NONE;", f"return {falsev};")
    body = re.sub(r'return Py_BuildValue\("I", ([\w>\-\.]+)->id\);', r'return \1->id.id;', body)
    body = re.sub(r'return Py_BuildValue\("I", ([\w>\-\.]+)\);', r'return \1;', body)
    body = body.replace("PY_ERR(", "ERR(")
    body = strip_py_dbg(body)
    body = re.sub(r"PyObject \*lst = PyList_New\(0\);\s*return lst;", f"return {falsev};", body)
    # signature
    sig_m = re.match(r'(?:static )?PyObject \*\w+\(PyObject \*[^\n]*\n\{', body)
    plist = ", ".join(f"{t}{'' if t.endswith('*') else ' '}{n}" + (f" = {d}" if d else "") for n, t, d in params)
    proto_list = ", ".join(f"{t}{'' if t.endswith('*') else ' '}{n}" + (f" = {d}" if d else "") for n, t, d in params)
    def_list = ", ".join(f"{t}{'' if t.endswith('*') else ' '}{n}" for n, t, _ in params)
    body = body[sig_m.end():]
    body = re.sub(r'(?<![\w:>.])' + re.escape(name) + r'\(', '::' + name + '(', body)
    body = re.sub(r'PyList_Size\((\w+)\)', r'((int) \1.size())', body)
    body = re.sub(r'PyList_GetItem\((\w+), ', r'list_item(\1, ', body)
    body = re.sub(r'py_obj_to_std_string\((\w+)\)', r'(*\1)', body)
    body = body.replace('arr[ i ] = py_obj_to_string(strObj);', 'arr[ i ] = strObj->c_str();')
    body = re.sub(r'\n[ \t]*for \(i = 0; i < numLines; i\+\+\) \{\n[ \t]*if \(! arr\[ i \]\) \{\n[ \t]*continue;\n[ \t]*\}\n\n?[ \t]*myfree\(\(char \*\) arr\[ i \]\);\n[ \t]*\}\n', '\n', body)
    body = body.replace('PyObject *strObj;', 'const std::string *strObj;')
    body = re.sub(r'\n[ \t]*if \(! e\) \{\n[^\n]*\n[^\n]*\n[ \t]*\}\n', '\n', body)
    body = re.sub(r'if \(! (py_\w+_data|py_room_data|py_tree_data|py_skill_data|py_spell_data)\)', r'if (\1.empty())', body)
    body = re.sub(r'if \((py_\w+_data)\) \{', r'if (! \1.empty()) {', body)
    src = f"{ret_t} {name}({def_list})\n{{" + body
    return ret_t, params, proto_list, src, kwnames

# ---------------------------------------------------------------------------
# build the list of names we must provide
# ---------------------------------------------------------------------------
names = sorted(n for n in used if n in groups["HAND"] or n in macro_defs)
protos = []
thing_defs = []
level_defs = []
table = {}

for n in names:
    if n in MANUAL:
        continue
    if n in macro_defs:
        fam, _api = macro_defs[n]
        ret, params = MACRO_RET[fam]
        table[n] = {"kind": "native", "ret": {"bool": "bool", "int": "int", "std::string": "str", "uint32_t": "thing"}[ret],
                    "params": [(p, "thing" if t == "uint32_t" and p in ("id", "oid") else ("int" if t == "int" else "thing")) for p, t in params]}
        protos.append(f"{ret} {n}({', '.join(f'{t} {p}' for p, t in params)});")
        continue
    fname, text = find_hand(n)
    if not text:
        print("!! cannot find", n, file=sys.stderr)
        continue
    ret_t, params, proto_list, src, kwnames = transform(n, text)
    protos.append(f"{ret_t} {n}({proto_list});")
    (level_defs if n.startswith("level_") else thing_defs).append(src)
    ctmap = {"uint32_t": "thing", "int": "int", "const char *": "str", "float": "float", "double": "float", "const std::vector< std::string > &": "list_str"}
    table[n] = {"kind": "native", "ret": {"bool": "bool", "uint32_t": "thing"}[ret_t],
                "params": [(p if p != "t" else p, ctmap[t]) for p, t, d in params],
                "defaults": {p: d for p, t, d in params if d}, "kwnames": kwnames}

json.dump({"table": table, "protos": protos}, open(f"{WORK}/apitable_gen.json", "w"), indent=1)
open(f"{WORK}/gen_thing_defs.cpp", "w").write("\n\n".join(thing_defs))
open(f"{WORK}/gen_level_defs.cpp", "w").write("\n\n".join(level_defs))
open(f"{WORK}/gen_protos.hpp", "w").write("\n".join(protos))
print("generated:", len(thing_defs), "thing fns,", len(level_defs), "level fns,", len([p for p in protos if 'bool' in p or True]), "protos")
print("macro-based:", [n for n in names if n in macro_defs][:5], "...", sum(1 for n in names if n in macro_defs))
print("skipped manual:", sorted(n for n in names if n in MANUAL))


# ===========================================================================
# Assemble final native sources
# ===========================================================================
def rename_py(txt):
    for a, b in (("py_room_data", "room_data"), ("py_skill_data", "skill_data"), ("py_spell_data", "spell_data"),
                 ("py_tree_data", "tree_data"), ("py_tree_name", "tree_name_arg")):
        txt = txt.replace(a, b)
    # the one local clash: parameter tree_name_arg vs local std::string tree_name is intentional
    return txt

thing_defs_txt = rename_py("\n\n".join(thing_defs))
protos_txt = rename_py("\n".join(protos))
# collapse runs of blank lines
thing_defs_txt = re.sub(r'\n{3,}', '\n\n', thing_defs_txt)

NATIVE_MACROS = r'''
//
// Native replacements for the old THING_BODY_* / LEVEL_BODY_* python wrapper macros.
// Semantics (including failure return values) match the originals. A failed lookup
// logs an error and returns false/0/"".
//
#define NATIVE_THING_GET_BOOL(__func__, __api__)                                                                     \
  bool __func__(uint32_t id)                                                                                         \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return false;                                                                                                  \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return false;                                                                                                  \
    }                                                                                                                \
    return t->__api__() ? true : false;                                                                              \
  }

#define NATIVE_THING_GET_INT(__func__, __api__)                                                                      \
  int __func__(uint32_t id)                                                                                          \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    return (int) t->__api__();                                                                                       \
  }

#define NATIVE_THING_GET_STRING(__func__, __api__)                                                                   \
  std::string __func__(uint32_t id)                                                                                  \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return "";                                                                                                     \
    }                                                                                                                \
    return t->__api__();                                                                                             \
  }

#define NATIVE_THING_GET_THING(__func__, __api__)                                                                    \
  uint32_t __func__(uint32_t id)                                                                                     \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return 0;                                                                                                      \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    ThingId found = t->__api__();                                                                                    \
    return found.id;                                                                                                 \
  }

#define NATIVE_THING_SET_INT(__func__, __api__)                                                                      \
  int __func__(uint32_t id, int value)                                                                               \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    auto out = t->__api__(value);                                                                                    \
    return (int) out;                                                                                                \
  }

#define NATIVE_THING_SET_THING(__func__, __api__)                                                                    \
  uint32_t __func__(uint32_t id, uint32_t oid)                                                                       \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return 0;                                                                                                      \
    }                                                                                                                \
    if (! oid) {                                                                                                     \
      ERR("%s: No oid thing ID set", __FUNCTION__);                                                                  \
      return 0;                                                                                                      \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return 0;                                                                                                      \
    }                                                                                                                \
    Thingp o = game->thing_find(oid);                                                                                \
    if (unlikely(! o)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, oid);                                                         \
      return 0;                                                                                                      \
    }                                                                                                                \
    t->__api__(o);                                                                                                   \
    return 1;                                                                                                        \
  }

#define NATIVE_LEVEL_GET_BOOL_AT(__func__, __api__)                                                                  \
  bool __func__(uint32_t id, int x, int y)                                                                           \
  {                                                                                                                  \
    TRACE_NO_INDENT();                                                                                               \
    if (! id) {                                                                                                      \
      ERR("%s: No thing ID set", __FUNCTION__);                                                                      \
      return false;                                                                                                  \
    }                                                                                                                \
    Thingp t = game->thing_find(id);                                                                                 \
    if (unlikely(! t)) {                                                                                             \
      ERR("%s: Cannot find thing ID %u", __FUNCTION__, id);                                                          \
      return false;                                                                                                  \
    }                                                                                                                \
    if (t->level->is_oob(x, y)) {                                                                                    \
      return false;                                                                                                  \
    }                                                                                                                \
    FOR_ALL_NON_INTERNAL_THINGS(t->level, t, x, y)                                                                   \
    {                                                                                                                \
      if (t->__api__()) {                                                                                            \
        return true;                                                                                                 \
      }                                                                                                              \
    }                                                                                                                \
    FOR_ALL_THINGS_END()                                                                                             \
    return false;                                                                                                    \
  }
'''

FAMILY_TO_NATIVE = {
    "THING_BODY_GET_BOOL": "NATIVE_THING_GET_BOOL", "THING_BODY_GET_INT": "NATIVE_THING_GET_INT",
    "THING_BODY_GET_STRING": "NATIVE_THING_GET_STRING", "THING_BODY_GET_THING": "NATIVE_THING_GET_THING",
    "THING_BODY_SET_INT": "NATIVE_THING_SET_INT", "THING_BODY_SET_THING": "NATIVE_THING_SET_THING",
    "LEVEL_BODY_GET_BOOL_AT": "NATIVE_LEVEL_GET_BOOL_AT",
}
thing_inv, level_inv = [], []
for n in sorted(names):
    if n in macro_defs:
        fam, a = macro_defs[n]
        line = f"{FAMILY_TO_NATIVE[fam]}({n}, {a})"
        (level_inv if fam.startswith("LEVEL") else thing_inv).append(line)

HEADER_INCLUDES = '''#include "my_native.hpp"

#include "my_array_bounds_check.hpp"
#include "my_charmap.hpp"
#include "my_game.hpp"
#include "my_level_static.hpp"
#include "my_monst.hpp"
#include "my_music.hpp"
#include "my_room.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_tex.hpp"
#include "my_tile.hpp"
#include "my_template.hpp"
#include "my_thing.hpp"
#include "my_thing_attack_options.hpp"
#include "my_vector_bounds_check.hpp"
'''
LIST_ITEM = '''
static const int NO_VALUE = -99999;

//
// Safe element access for the string lists handed to the loaders.
//
static const std::string *list_item(const std::vector< std::string > &v, long i)
{
  if ((i < 0) || (i >= (long) v.size())) {
    return nullptr;
  }
  return &v[ (size_t) i ];
}
'''
manual = open(f"{WORK}/native_manual.cpp.in").read()

native_thing = ("//\n// Copyright goblinhack@gmail.com\n//\n"
    "// Native (C++) versions of the thing/spawn/loader API that python modules used to reach via the `my` module.\n"
    "// Generated from the former python bindings; edit freely.\n//\n\n"
    + HEADER_INCLUDES + "\n" + LIST_ITEM + "\nnamespace my {\n" + NATIVE_MACROS + "\n// begin sort marker1 {\n"
    + "\n".join(thing_inv) + "\n// end sort marker1 }\n\n" + thing_defs_txt + "\n\n" + manual + "\n} // namespace my\n")
native_level = ("//\n// Copyright goblinhack@gmail.com\n//\n"
    "// Native (C++) level queries formerly exposed to python.\n//\n\n"
    + HEADER_INCLUDES + "\nnamespace my {\n"
    + NATIVE_MACROS.split("#define NATIVE_LEVEL_GET_BOOL_AT")[0].split("//\n// Native replacements")[0]
    + "#define NATIVE_LEVEL_GET_BOOL_AT" + NATIVE_MACROS.split("#define NATIVE_LEVEL_GET_BOOL_AT")[1]
    + "\n// begin sort marker1 {\n" + "\n".join(level_inv) + "\n// end sort marker1 }\n\n} // namespace my\n")

open(f"{WORK}/out_native_thing.cpp", "w").write(native_thing)
open(f"{WORK}/out_native_level.cpp", "w").write(native_level)

MANUAL_PROTOS = '''std::vector< uint32_t > level_get_all(uint32_t id, int x, int y);
std::vector< uint32_t > level_flood_fill_get_all_things(uint32_t id, int x, int y, const char *filter);
std::vector< uint32_t > level_flood_fill_gas_get_all_grid_things(uint32_t id, int x, int y, int distance);
std::vector< uint32_t > thing_all_followers_get(uint32_t id);
std::vector< uint32_t > thing_get_followers(uint32_t id);
std::pair< int, int >   thing_coords_get(uint32_t id);
bool thing_hit(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
bool thing_hit_dmg_energy(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
bool thing_hit_dmg_fire(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
bool thing_hit_dmg_impact(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
bool thing_hit_dmg_missile(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
bool thing_hit_dmg_poison(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
bool thing_hit_dmg_stamina(uint32_t owner, uint32_t hitter, uint32_t target, int damage = 0, int crit = 0, int thrown = 0);
'''
open(f"{WORK}/out_native_api.hpp", "w").write(
    "//\n// Copyright goblinhack@gmail.com\n//\n// Native replacements for the former python `my` module functions.\n//\n\n"
    "#pragma once\n#ifndef _MY_NATIVE_API_HPP_\n#define _MY_NATIVE_API_HPP_\n\nnamespace my {\n"
    + MANUAL_PROTOS + protos_txt + "\n} // namespace my\n\n#endif\n")

# signature table for transpiler
KW_MACRO = {"bool": ["id"], "int": ["id"], "str": ["id"], "thing": ["id"]}
for n, e in table.items():
    if n in macro_defs:
        fam, _ = macro_defs[n]
        e["kwnames"] = {"THING_BODY_SET_INT": ["id", "value"], "THING_BODY_SET_THING": ["id", "oid"],
                        "LEVEL_BODY_GET_BOOL_AT": ["id", "x", "y"]}.get(fam, ["id"])
        e["defaults"] = {}
def M(name, ret, params, kw=None, defaults=None):
    table[name] = {"kind": "native", "ret": ret, "params": params, "kwnames": kw or [p for p, _ in params], "defaults": defaults or {}}
hit_p = [("owner", "thing"), ("hitter", "thing"), ("target", "thing"), ("damage", "int"), ("crit", "int"), ("thrown", "int")]
for h in ("thing_hit", "thing_hit_dmg_energy", "thing_hit_dmg_fire", "thing_hit_dmg_impact", "thing_hit_dmg_missile",
          "thing_hit_dmg_poison", "thing_hit_dmg_stamina"):
    M(h, "bool", hit_p, defaults={"damage": "0", "crit": "0", "thrown": "0"})
M("level_get_all", "list_thing", [("id", "thing"), ("x", "int"), ("y", "int")])
M("level_flood_fill_get_all_things", "list_thing", [("id", "thing"), ("x", "int"), ("y", "int"), ("filter", "str")])
M("level_flood_fill_gas_get_all_grid_things", "list_thing", [("id", "thing"), ("x", "int"), ("y", "int"), ("distance", "int")])
M("thing_all_followers_get", "list_thing", [("id", "thing")])
M("thing_get_followers", "list_thing", [("id", "thing")])
M("thing_coords_get", "pair_int", [("id", "thing")])
for k, e in table.items():
    if "kwnames" in e:
        e["kwnames"] = [rename_py(x) for x in e["kwnames"]]
    e["params"] = [(rename_py(p), t) for p, t in e["params"]]
    if "defaults" in e:
        e["defaults"] = {rename_py(k): v for k, v in e["defaults"].items()}
json.dump(table, open(f"{WORK}/apitable.json", "w"), indent=1)
print("assembled: thing=%d bytes level=%d bytes table=%d entries" % (len(native_thing), len(native_level), len(table)))
