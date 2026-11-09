#!/usr/bin/env python3
"""
py2cpp: converts the zorbash python modules into standalone C++ files.

It understands exactly the restricted python subset those modules use and FAILS LOUDLY (raising
Unsupported) on anything it cannot type or translate with confidence, rather than guessing.

Usage: py2cpp.py <python_root> <src_out> <work_dir>
"""
import ast
import collections
import json
import os
import re
import sys


class Unsupported(Exception):
    pass


# ---------------------------------------------------------------------------------------------
# Static tables
# ---------------------------------------------------------------------------------------------
THING_PARAMS = {"me", "owner", "hitter", "real_hitter", "target", "item", "skill", "victim", "leader", "it", "eater", "what"}
INT_PARAMS = {"x", "y", "damage", "crit", "target_x", "target_y", "dx", "dy", "unused", "level_no", "is_boss_level",
              "damage_reduction_percent", "bonus"}
STR_PARAMS = {"name", "text_long_name", "text_short_name"}
PARAM_NAME_TYPE = {**{n: "thing" for n in THING_PARAMS}, **{n: "int" for n in INT_PARAMS},
                   **{n: "str" for n in STR_PARAMS}, "self": "tp"}

# Order of TileArgs members (== order of the former python keywords)
TILE_FIELDS = ["tile", "ascii_fg_char", "ascii_bg_char", "ascii_bg_col_name", "ascii_fg_col_name", "ascii_bg_alpha",
               "ascii_fg_alpha", "delay_ms", "frame", "is_moving", "is_jumping", "begin_jump", "is_outline",
               "is_dir_left", "is_dir_right", "is_dir_up", "is_dir_down", "is_dir_none", "is_yyy5", "is_yyy6",
               "is_yyy7", "is_yyy8", "is_yyy9", "is_invisible", "is_hp_25_percent", "is_hp_50_percent",
               "is_hp_75_percent", "is_hp_100_percent", "is_in_water", "is_sleeping", "is_open", "is_dead",
               "is_end_of_anim", "is_end_of_ascii_anim", "is_dead_on_end_of_anim", "is_dead_on_end_of_ascii_anim",
               "is_alive_on_end_of_anim", "is_alive_on_end_of_ascii_anim", "is_resurrecting"]
TILE_STR_FIELDS = {"tile", "ascii_fg_char", "ascii_bg_char", "ascii_bg_col_name", "ascii_fg_col_name"}
TILE_FUNCS = {"tile", "top1_tile", "top2_tile", "bot1_tile", "bot2_tile", "bot3_tile", "left1_tile", "left2_tile",
              "right1_tile", "right2_tile", "tl1_tile", "tl2_tile", "tr1_tile", "tr2_tile", "bl1_tile", "bl2_tile",
              "br1_tile", "br2_tile"}

DICE_FUNCS = {"py_d4": "d4", "py_d6": "d6", "py_d20": "d20", "py_d100": "d100"}
MISC_MY = {"py_pcg_random_range_inclusive": ("my::pcg_random_inclusive", "int", ["int", "int"]),
           "py_non_pcg_random_range_inclusive": ("my::non_pcg_random_inclusive", "int", ["int", "int"]),
           "log": ("my::log", "void", ["str"]), "topcon": ("my::topcon", "void", ["str"]),
           "game_set_request_to_update_same_level": ("my::game_set_request_to_update_same_level", "void", [])}

NUMERIC = {"int", "float", "bool", "thing"}


def cpp_type(t):
    return {"int": "int", "float": "double", "bool": "bool", "str": "std::string", "thing": "uint32_t", "tp": "Tpp",
            "list_str": "std::vector< std::string >", "list_thing": "std::vector< uint32_t >",
            "pair_int": "std::pair< int, int >", "void": "void",
            "opt_list_str": "std::optional< std::vector< std::string > >"}[t]


def cstr(s):
    out = []
    for ch in s:
        o = ord(ch)
        if ch == "\\":
            out.append("\\\\")
        elif ch == '"':
            out.append('\\"')
        elif ch == "\n":
            out.append("\\n")
        elif ch == "\t":
            out.append("\\t")
        elif ch == "\r":
            out.append("\\r")
        elif o < 32 or o == 127:
            out.append("\\%03o" % o)
        elif ch == "?":
            out.append("\\?")      # avoid trigraph-style surprises
        elif o > 127:
            raise Unsupported("non-ascii string literal")
        else:
            out.append(ch)
    return '"' + "".join(out) + '"'


def unify(a, b, what=""):
    if a == b:
        return a
    if a is None:
        return b
    if b is None:
        return a
    s = {a, b}
    if s <= NUMERIC:
        if "float" in s:
            return "float"
        if "thing" in s:
            return "thing" if s <= {"thing", "int", "bool"} else "int"
        return "int"
    if a == "list_empty":
        return b
    if b == "list_empty":
        return a
    raise Unsupported(f"cannot unify types {a} and {b} {what}")


# ---------------------------------------------------------------------------------------------
# Module model
# ---------------------------------------------------------------------------------------------
class Module:
    def __init__(self, relpath, tree):
        self.relpath = relpath                      # e.g. things/amulets/amulet_endurance.py
        self.stem = os.path.splitext(os.path.basename(relpath))[0]
        self.tree = tree
        d = os.path.dirname(relpath)
        sub = os.path.join(d, self.stem) if d else os.path.join("modules", self.stem)
        self.out_rel = sub + ".cpp"                 # under src/
        self.ns = "mod_" + sub.replace("/", "_")
        self.funcs = {n.name: n for n in tree.body if isinstance(n, ast.FunctionDef)}
        self.imports = {}                           # alias -> Module (project modules only)
        self.globals = {}                           # module level constants/variables: name -> (type, cpp init)
        for n in tree.body:
            if isinstance(n, ast.Assign) and len(n.targets) == 1 and isinstance(n.targets[0], ast.Name) \
                    and isinstance(n.value, ast.Constant) and n.targets[0].id not in ("self", "timeme_enabled"):
                v = n.value.value
                if isinstance(v, bool):
                    self.globals[n.targets[0].id] = ("bool", "true" if v else "false")
                elif isinstance(v, int):
                    self.globals[n.targets[0].id] = ("int", str(v))
                elif isinstance(v, str):
                    self.globals[n.targets[0].id] = ("str", cstr(v))
        self.shared = False                         # imported by another module


class Tables:
    def __init__(self, src_orig, work):
        t = open(os.path.join(src_orig, "py_tp.cpp")).read()
        self.tp_setters = {}
        for m in re.finditer(r'^TP_BODY_SET_(INT_INT|INT|STRING)\((\w+)\)', t, re.M):
            self.tp_setters[m.group(2)] = {"INT": "int", "INT_INT": "int_int", "STRING": "str"}[m.group(1)]
        c = open(os.path.join(src_orig, "python_consts.cpp")).read()
        self.consts = dict(re.findall(r'PyModule_AddIntConstant\(\s*my_mod,\s*"(\w+)",\s*([^)]+?)\s*\)', c))
        self.api = json.load(open(os.path.join(work, "apitable.json")))


# ---------------------------------------------------------------------------------------------
# Function signature
# ---------------------------------------------------------------------------------------------
CPP_RESERVED = {"new", "delete", "class", "this", "template", "typename", "namespace", "default", "switch", "case",
                "auto", "register", "signed", "unsigned", "char", "short", "long", "double", "float", "int", "bool",
                "void", "union", "struct", "enum", "typedef", "public", "private", "protected", "virtual",
                "operator", "friend", "inline", "static", "const", "volatile", "explicit", "export", "mutable",
                "using", "try", "catch", "throw", "do", "goto", "and", "or", "not", "xor", "asm", "NULL", "true",
                "false", "errno", "stdin", "stdout", "stderr", "assert", "min", "max", "abs", "pow", "log", "exp",
                "round", "floor", "ceil", "sqrt", "time", "index", "signal", "remove", "rand", "random", "y0", "y1",
                "j0", "j1", "jn", "yn", "main", "module_init", "string", "vector", "list", "map", "set"}


def ident(n):
    return n + "_" if n in CPP_RESERVED else n


class Sig:
    """Signature of a module level python function."""

    def __init__(self, mod, node):
        self.mod = mod
        self.node = node
        self.name = node.name
        self.params = [a.arg for a in node.args.args]
        self.defaults = {}
        dl = node.args.defaults
        for a, d in zip(self.params[len(self.params) - len(dl):], dl):
            self.defaults[a] = d
        if node.args.vararg or node.args.kwarg or node.args.kwonlyargs:
            raise Unsupported(f"{mod.relpath}:{node.name}: varargs not supported")
        self.assigned_params = set()
        for nd in ast.walk(node):
            if isinstance(nd, (ast.Assign, ast.AugAssign)):
                for t in (nd.targets if isinstance(nd, ast.Assign) else [nd.target]):
                    for x in ast.walk(t):
                        if isinstance(x, ast.Name) and x.id in self.params:
                            self.assigned_params.add(x.id)
        self.ptypes = {}          # name -> type
        self.ret = None           # type or 'void'
        self.kind = None          # callback kind, if referenced as one

    def cpp_params(self):
        out = []
        for p in self.params:
            t = self.ptypes[p]
            ct = cpp_type(t)
            if t in ("str", "list_str", "opt_list_str") and p not in self.assigned_params:
                out.append(f"const {ct} &{ident(p)}")
            else:
                out.append(f"{ct} {ident(p)}")
        return ", ".join(out) if out else "void"

    def cpp_ret(self):
        return cpp_type(self.ret or "void")


# ---------------------------------------------------------------------------------------------
# Function translator
# ---------------------------------------------------------------------------------------------
class FuncTr:
    def __init__(self, prog, mod, sig, known_vars=None, emit=False):
        self.prog, self.mod, self.sig = prog, mod, sig
        self.emit = emit
        self.vars = dict(known_vars or {})
        self.loopvars = set()
        self.assigned = set()
        self.tmp_id = 0
        self.lines = []
        self.ind = 1
        self.ret_types = []
        self.unknown = False
        self.tp_names = set()           # local variables holding a Tpp
        self.ctx = f"{mod.relpath}:{sig.name}"
        self.pre_assigned = set()
        self.global_names = {g for nd in ast.walk(sig.node) if isinstance(nd, ast.Global) for g in nd.names}
        for nd in ast.walk(sig.node):
            if isinstance(nd, ast.Assign):
                for t in nd.targets:
                    for x in ast.walk(t):
                        if isinstance(x, ast.Name):
                            self.pre_assigned.add(x.id)
            elif isinstance(nd, ast.AugAssign) and isinstance(nd.target, ast.Name):
                self.pre_assigned.add(nd.target.id)

    # ---- helpers -----------------------------------------------------------------------------
    def err(self, msg, node=None):
        ln = getattr(node, "lineno", "?")
        raise Unsupported(f"{self.ctx}:{ln}: {msg}")

    def w(self, line):
        if self.emit:
            self.lines.append("  " * self.ind + line)

    def vtype(self, name):
        if name in self.sig.ptypes:
            return self.sig.ptypes[name]
        if name in self.vars:
            return self.vars[name]
        if name in self.mod.globals and name not in self.pre_assigned or name in self.global_names:
            g = self.mod.globals.get(name)
            return g[0] if g else None
        return None

    def set_var(self, name, ty, node):
        if name in self.global_names:
            g = self.mod.globals.get(name)
            if not g:
                self.err(f"global '{name}' has no module level initial value", node)
            if ty is not None and not ({g[0], ty} <= NUMERIC or g[0] == ty):
                self.err(f"global '{name}' of type {g[0]} assigned {ty}", node)
            return
        if name in self.sig.ptypes:
            old = self.sig.ptypes[name]
            if ty is not None and old != ty:
                if {old, ty} <= NUMERIC and old in ("int", "thing", "bool") and ty in ("int", "thing", "bool"):
                    return
                if {old, ty} <= NUMERIC and old == "float":
                    return
                self.err(f"parameter '{name}' of type {old} assigned {ty}", node)
            return
        if ty is None:
            return
        if ty == "none":
            self.err("assigning None to a variable", node)
        self.assigned.add(name)
        self.vars[name] = unify(self.vars.get(name), ty, f"(variable {name})")

    def set_loop_var(self, name, ty, node):
        if name in self.sig.ptypes:
            self.err(f"loop variable '{name}' shadows a parameter", node)
        self.loopvars.add(name)
        self.vars[name] = unify(self.vars.get(name), ty, f"(loop variable {name})")


    # ---- evaluation order -----------------------------------------------------------------------
    # python evaluates operands and arguments strictly left to right; C++ leaves the order of operands of
    # most operators and of function arguments unspecified. When two or more operands contain calls we hoist
    # them (in python order) into temporaries inside an immediately invoked lambda.
    PURE_BUILTINS = {"int", "float", "abs", "len", "str", "min", "max", "round"}

    def n_impure(self, node):
        n = 0
        for x in ast.walk(node):
            if isinstance(x, ast.Call):
                f = x.func
                if isinstance(f, ast.Name) and f.id in self.PURE_BUILTINS:
                    continue
                if isinstance(f, ast.Attribute) and isinstance(f.value, ast.Name) and f.value.id == "math":
                    continue
                n += 1
        return n

    def sequenced(self, entries, build):
        """entries: [(code, node)] in python evaluation order. build(codes) -> C++ expression string."""
        impure = [i for i, (_, nd) in enumerate(entries) if nd is not None and self.n_impure(nd) > 0]
        if len(impure) < 2:
            return build([c for c, _ in entries])
        self.tmp_id += 1
        pre, codes = [], [c for c, _ in entries]
        for k, i in enumerate(impure):
            name = f"t{self.tmp_id}_{k}_"
            pre.append(f"auto {name} = {codes[i]};")
            codes[i] = name
        return "[&]() { " + " ".join(pre) + " return " + build(codes) + "; }()"

    # ---- string helpers ----------------------------------------------------------------------
    @staticmethod
    def is_lit(code):
        return code.startswith('"') and code.endswith('"') and not code.startswith('std::string')

    def as_string(self, code, ty):
        if ty != "str":
            raise Unsupported("expected str")
        return f"std::string({code})" if self.is_lit(code) else code

    def as_cstr(self, code, ty, node):
        if ty != "str":
            self.err(f"expected a string, got {ty}", node)
        return code if self.is_lit(code) else f"({code}).c_str()"

    # ---- expressions -------------------------------------------------------------------------
    def ex(self, n):
        m = getattr(self, "ex_" + type(n).__name__, None)
        if not m:
            self.err(f"unsupported expression {type(n).__name__}: {ast.unparse(n)[:60]}", n)
        return m(n)

    def ex_Constant(self, n):
        v = n.value
        if v is None:
            return "nullptr", "none"
        if isinstance(v, bool):
            return ("true" if v else "false"), "bool"
        if isinstance(v, int):
            return str(v), "int"
        if isinstance(v, float):
            r = repr(v)
            return r, "float"
        if isinstance(v, str):
            return cstr(v), "str"
        self.err(f"unsupported constant {v!r}", n)

    def ex_Name(self, n):
        name = n.id
        t = self.vtype(name)
        if name in self.tp_names:
            return ident(name), "tp"
        if t is None:
            if self.emit:
                self.err(f"unknown variable '{name}'", n)
            self.unknown = True
            return ident(name), None
        return ident(name), t

    def ex_Attribute(self, n):
        if isinstance(n.value, ast.Name) and n.value.id == "my":
            if n.attr in self.prog.tables.consts:
                return self.prog.tables.consts[n.attr], "int"
            self.err(f"unknown my.{n.attr}", n)
        if isinstance(n.value, ast.Name) and n.value.id == "math" and n.attr == "pi":
            return "3.14159265358979323846", "float"
        self.err(f"unsupported attribute {ast.unparse(n)}", n)

    def ex_List(self, n):
        return self.list_lit(n.elts, n)

    def ex_Tuple(self, n):
        return self.list_lit(n.elts, n)

    def list_lit(self, elts, n):
        if not elts:
            return "{}", "list_empty"
        parts = [self.ex(e) for e in elts]
        t = None
        for _, ty in parts:
            t = unify(t, ty)
        if t == "str":
            codes = [c for c, _ in parts]
            if len(codes) > 3 and sum(len(c) for c in codes) > 80:
                body = "{\n" + ",\n".join("      " + c for c in codes) + ",\n    }"
            else:
                body = "{" + ", ".join(codes) + "}"
            return "std::vector< std::string >" + body, "list_str"
        if t in ("int", "thing"):
            return "std::vector< uint32_t >{" + ", ".join(c for c, _ in parts) + "}", "list_thing"
        if t is None:
            return "{}", None
        self.err(f"unsupported list element type {t}", n)

    def ex_Subscript(self, n):
        c, t = self.ex(n.value)
        ic, it = self.ex(n.slice)
        if it not in ("int", "thing", None):
            self.err("subscript index must be an integer", n)
        if t == "list_str":
            return f"{c}.at({ic})", "str"
        if t in ("list_thing",):
            return f"{c}.at({ic})", "thing"
        if t is None:
            return "0", None
        self.err(f"cannot subscript {t}", n)

    def ex_UnaryOp(self, n):
        c, t = self.ex(n.operand)
        if isinstance(n.op, ast.Not):
            return f"(! {self.cond_of(c, t, n)})", "bool"
        if isinstance(n.op, ast.USub):
            return f"(-{c})", ("int" if t in ("bool", "thing") else t)
        if isinstance(n.op, ast.UAdd):
            return c, t
        self.err("unsupported unary op", n)

    def ex_BinOp(self, n):
        lc, lt = self.ex(n.left)
        rc, rt = self.ex(n.right)
        op = type(n.op).__name__
        if lt is None or rt is None:
            return "0", None
        ent = [(lc, n.left), (rc, n.right)]
        if op == "Add" and lt == "str" and rt == "str":
            return self.sequenced(ent, lambda c: f"({self.as_string(c[0], lt)} + {c[1]})"), "str"
        if lt not in NUMERIC or rt not in NUMERIC:
            self.err(f"binary {op} on {lt}, {rt}", n)
        isf = "float" in (lt, rt)
        sym = {"Add": "+", "Sub": "-", "Mult": "*"}.get(op)
        if sym:
            return self.sequenced(ent, lambda c: f"({c[0]} {sym} {c[1]})"), ("float" if isf else "int")
        if op == "Div":
            return self.sequenced(ent, lambda c: f"((double) {c[0]} / (double) {c[1]})"), "float"
        if op == "Pow":
            if not isf and isinstance(n.right, ast.Constant) and isinstance(n.right.value, int) and n.right.value >= 0:
                k = n.right.value
                if k == 2:
                    return f"my::ipow2({lc})", "int"
                self.err("integer power other than **2", n)
            return f"std::pow((double) {lc}, (double) {rc})", "float"
        self.err(f"unsupported binary operator {op}", n)

    def cond_of(self, c, t, n):
        if t == "bool":
            return c
        if t in ("int", "thing", "float"):
            return f"({c} != 0)" if not c.startswith("(") else f"({c} != 0)"
        if t == "str":
            return f"(! {self.as_string(c, t)}.empty())"
        if t in ("list_thing", "list_str", "opt_list_str"):
            return f"(! {c}.empty())" if t != "opt_list_str" else f"({c}.has_value())"
        if t is None:
            return "false"
        self.err(f"cannot use {t} as a condition", n)

    def cond(self, n):
        if isinstance(n, ast.BoolOp):
            op = " && " if isinstance(n.op, ast.And) else " || "
            return "(" + op.join(self.cond(v) for v in n.values) + ")"
        c, t = self.ex(n)
        return self.cond_of(c, t, n)

    def ex_BoolOp(self, n):
        parts = [self.ex(v) for v in n.values]
        if all(t in ("bool", None) for _, t in parts):
            op = " && " if isinstance(n.op, ast.And) else " || "
            return "(" + op.join(c for c, _ in parts) + ")", "bool"
        # python yields an operand; only translate when the result is used as a truth value
        op = " && " if isinstance(n.op, ast.And) else " || "
        return "(" + op.join(self.cond_of(c, t, n) for c, t in parts) + ")", "bool"

    def ex_IfExp(self, n):
        t_c = self.cond(n.test)
        ac, at = self.ex(n.body)
        bc, bt = self.ex(n.orelse)
        if at == "str" and bt == "str":
            return f"({t_c} ? {self.as_string(ac, at)} : {self.as_string(bc, bt)})", "str"
        return f"({t_c} ? {ac} : {bc})", unify(at, bt)

    def ex_Compare(self, n):
        parts = []
        left = n.left
        lc, lt = self.ex(left)
        if len(n.ops) > 1 and sum(1 for x in [n.left] + list(n.comparators[:-1]) if self.n_impure(x)) > 0:
            self.err("chained comparison with calls in the middle", n)
        lnode = left
        for op, right in zip(n.ops, n.comparators):
            if isinstance(op, (ast.Is, ast.IsNot)):
                if not (isinstance(right, ast.Constant) and right.value is None):
                    self.err("'is' only supported against None", n)
                neg = isinstance(op, ast.IsNot)
                if lt == "opt_list_str":
                    parts.append(f"({lc}.has_value())" if neg else f"(! {lc}.has_value())")
                elif lt == "list_thing":
                    # the python api returned None instead of an empty list (thing_all_followers_get)
                    parts.append(f"(! {lc}.empty())" if neg else f"({lc}.empty())")
                elif lt in ("str", "list_str", "int", "thing", "bool", "float", "tp"):
                    # can never be None in the native version
                    parts.append("true" if neg else "false")
                elif lt is None:
                    parts.append("true")
                else:
                    self.err(f"'is None' on {lt}", n)
                lc, lt = "nullptr", "none"
                continue
            rc, rt = self.ex(right)
            if isinstance(op, (ast.In, ast.NotIn)):
                if not isinstance(right, (ast.List, ast.Tuple)):
                    self.err("'in' only supported against list/tuple literals", n)
                items = [self.ex(e) for e in right.elts]
                tests = []
                for ic, it in items:
                    if lt == "str":
                        tests.append(f"({self.as_string(lc, lt)} == {ic})")
                    else:
                        tests.append(f"({lc} == {ic})")
                expr = "(" + " || ".join(tests) + ")"
                parts.append(f"(! {expr})" if isinstance(op, ast.NotIn) else expr)
            else:
                sym = {ast.Eq: "==", ast.NotEq: "!=", ast.Lt: "<", ast.LtE: "<=", ast.Gt: ">", ast.GtE: ">="}.get(type(op))
                if not sym:
                    self.err("unsupported comparison", n)
                ent = [(lc, lnode), (rc, right)]
                if lt == "str" and rt == "str":
                    parts.append(self.sequenced(ent, lambda c: f"({self.as_string(c[0], lt)} {sym} {c[1]})"))
                elif (lt in NUMERIC or lt is None) and (rt in NUMERIC or rt is None):
                    parts.append(self.sequenced(ent, lambda c: f"({c[0]} {sym} {c[1]})"))
                else:
                    self.err(f"compare {lt} with {rt}", n)
            lc, lt = rc, rt
            lnode = right
        if len(parts) == 1:
            return parts[0], "bool"
        return "(" + " && ".join(parts) + ")", "bool"

    def ex_JoinedStr(self, n):
        parts = []
        pnodes = []
        for v in n.values:
            pnodes.append(v.value if isinstance(v, ast.FormattedValue) else None)
            if isinstance(v, ast.Constant):
                parts.append(cstr(v.value))
            elif isinstance(v, ast.FormattedValue):
                if v.format_spec is not None or v.conversion not in (-1, None):
                    self.err("f-string format spec/conversion unsupported", n)
                c, t = self.ex(v.value)
                parts.append(self.stringify(c, t, v))
            else:
                self.err("bad f-string", n)
        if not parts:
            return '""', "str"
        return self.concat(parts, pnodes), "str"

    def stringify(self, c, t, n):
        if t == "str":
            return c
        if t in ("int", "thing"):
            return f"std::to_string({c})"
        if t == "bool":
            return f'({c} ? "True" : "False")'
        if t is None:
            return '""'
        self.err(f"cannot format {t} in a string", n)

    def concat(self, parts, nodes=None):
        if nodes is not None:
            return self.sequenced(list(zip(parts, nodes)), lambda c: self.concat_plain(c))
        return self.concat_plain(parts)

    def concat_plain(self, parts):
        out = parts[0]
        if self.is_lit(out) or out.startswith("(") and False:
            out = f"std::string({out})"
        elif not out.startswith("std::string(") and not out.startswith("std::to_string("):
            out = f"std::string({out})"
        for p in parts[1:]:
            out = f"{out} + {p}"
        return "(" + out + ")"

    # ---- calls -------------------------------------------------------------------------------
    def ex_Call(self, n):
        f = n.func
        if isinstance(f, ast.Attribute) and isinstance(f.value, ast.Name):
            base = f.value.id
            if base == "my":
                return self.call_my(n, f.attr)
            if base == "math":
                return self.call_math(n, f.attr)
            if base == "random" and f.attr == "choice":
                c, t = self.ex(n.args[0])
                if t not in ("list_str",):
                    self.err("random.choice only on list of str", n)
                return f"my::random_choice({c})", "str"
            if base in self.mod.imports:
                return self.local_call(n, self.mod.imports[base], f.attr)
        if isinstance(f, ast.Attribute) and isinstance(f.value, ast.Constant) and isinstance(f.value.value, str) \
                and f.attr == "format":
            return self.str_format(n)
        if isinstance(f, ast.Name):
            return self.call_name(n, f.id)
        self.err(f"unsupported call {ast.unparse(f)}", n)

    def call_math(self, n, name):
        if len(n.args) != 1:
            self.err("math call arity", n)
        c, t = self.ex(n.args[0])
        if t not in NUMERIC and t is not None:
            self.err("math on non number", n)
        if name == "ceil":
            return f"((int) std::ceil((double) {c}))", "int"
        if name == "floor":
            return f"((int) std::floor((double) {c}))", "int"
        if name == "sqrt":
            return f"std::sqrt((double) {c})", "float"
        self.err(f"unsupported math.{name}", n)

    def call_name(self, n, name):
        if name in ("int", "float", "abs", "len", "str", "min", "max", "round"):
            args = [self.ex(a) for a in n.args]
            if n.keywords:
                self.err("keywords to builtin", n)
            if any(t is None for _, t in args):
                return "0", None
            if name == "int":
                c, t = args[0]
                if t not in NUMERIC:
                    self.err("int() of non number", n)
                return f"((int) ({c}))", "int"
            if name == "float":
                c, t = args[0]
                return f"((double) ({c}))", "float"
            if name == "abs":
                c, t = args[0]
                return (f"std::fabs({c})", "float") if t == "float" else (f"std::abs((int) ({c}))", "int")
            if name == "len":
                c, t = args[0]
                if t not in ("list_str", "list_thing"):
                    self.err("len() of non list", n)
                return f"((int) {c}.size())", "int"
            if name == "str":
                c, t = args[0]
                return self.stringify(c, t, n), "str"
            if name in ("min", "max"):
                if len(args) != 2:
                    self.err("min/max arity", n)
                (ac, at), (bc, bt) = args
                if "float" in (at, bt):
                    return f"std::{name}< double >((double) {ac}, (double) {bc})", "float"
                return f"std::{name}< int >((int) {ac}, (int) {bc})", "int"
            self.err(f"unsupported builtin {name}", n)
        sig = self.prog.sigs.get((self.mod.relpath, name))
        if sig:
            return self.local_call(n, self.mod, name)
        self.err(f"unknown function {name}", n)

    def str_format(self, n):
        tmpl = n.func.value.value
        pieces = tmpl.split("{}")
        if len(pieces) - 1 != len(n.args) or n.keywords:
            self.err("str.format placeholders", n)
        parts, pnodes = [], []
        for i, p in enumerate(pieces):
            if p:
                parts.append(cstr(p))
                pnodes.append(None)
            if i < len(n.args):
                c, t = self.ex(n.args[i])
                parts.append(self.stringify(c, t, n))
                pnodes.append(n.args[i])
        return (self.concat(parts, pnodes) if parts else '""'), "str"

    # ---- argument binding for api / local functions ------------------------------------------
    def conv_arg(self, node, want, expect_node):
        """Translate node to a C++ expression suitable for a parameter of type `want`."""
        if want in ("list_str", "opt_list_str") and isinstance(node, (ast.List, ast.Tuple)):
            c, t = self.list_lit(node.elts, node)
            if t == "list_empty" or c == "{}":
                return "{}" if want == "list_str" else "std::vector< std::string >{}"
            if t != "list_str":
                self.err("expected list of str", node)
            return c
        if isinstance(node, ast.Constant) and node.value is None and want == "opt_list_str":
            return "std::nullopt"
        c, t = self.ex(node)
        if t is None:
            return c
        if want == "str":
            if t != "str":
                self.err(f"expected str argument, got {t}", node)
            return c
        if want in ("int", "thing"):
            if t not in ("int", "thing", "bool"):
                self.err(f"expected int argument, got {t}: {ast.unparse(node)[:50]}", node)
            return c
        if want == "float":
            if t not in NUMERIC:
                self.err(f"expected number argument, got {t}", node)
            return c
        if want in ("list_str", "opt_list_str"):
            if t not in ("list_str", "opt_list_str"):
                self.err(f"expected list argument, got {t}", node)
            return c
        if want == "tp":
            if t != "tp":
                self.err("expected tp", node)
            return c
        self.err(f"unsupported parameter type {want}", node)

    def prep_arg(self, node, want):
        """Translate an argument for a parameter of type `want`; returns the C++ code (no c_str conversion)."""
        if want == "str":
            c, t = self.ex(node)
            if t is not None and t != "str":
                self.err(f"expected str argument, got {t}: {ast.unparse(node)[:50]}", node)
            return c
        return self.conv_arg(node, want, node)

    def bind(self, n, pnames, kwnames=None):
        """Map call arguments (positional + keywords) onto parameter names -> ast nodes."""
        bound = {}
        if len(n.args) > len(pnames):
            self.err(f"too many arguments in {ast.unparse(n)[:60]}", n)
        for p, a in zip(pnames, n.args):
            bound[p] = a
        for k in n.keywords:
            if k.arg is None:
                self.err("** arguments unsupported", n)
            target = k.arg
            if target not in pnames and kwnames and target in kwnames:
                target = pnames[kwnames.index(target)]
            if target not in pnames:
                self.err(f"unknown keyword '{k.arg}'", n)
            if target in bound:
                self.err(f"duplicate argument {k.arg}", n)
            bound[target] = k.value
        return bound

    def api_call(self, n, name, e):
        pnames = [p for p, _ in e["params"]]
        ptype = dict(e["params"])
        bound = self.bind(n, pnames, e.get("kwnames"))
        # arguments must be supplied up to the last one given; later ones fall back to C++ defaults
        last = max([i for i, p in enumerate(pnames) if p in bound], default=-1)
        order = list(bound.keys())                      # python (source) evaluation order
        entries = [(self.prep_arg(bound[p], ptype[p]), bound[p]) for p in order]

        def build(codes):
            by = dict(zip(order, codes))
            args = []
            for i, p in enumerate(pnames):
                if p in by:
                    c = by[p]
                    if ptype[p] == "str" and not self.is_lit(c):
                        c = f"({c}).c_str()"
                    args.append(c)
                elif i <= last:
                    d = e.get("defaults", {}).get(p)
                    if d is None:
                        self.err(f"missing argument '{p}' for {name}", n)
                    args.append(d)
                else:
                    if p not in e.get("defaults", {}):
                        self.err(f"missing argument '{p}' for {name}", n)
            return f"my::{name}({', '.join(args)})"
        rt = {"bool": "bool", "int": "int", "str": "str", "thing": "thing", "list_thing": "list_thing",
              "pair_int": "pair_int", "float": "float"}[e["ret"]]
        for p in pnames[:last + 1]:
            if p not in bound and p not in e.get("defaults", {}):
                self.err(f"missing argument '{p}' for {name}", n)
        return self.sequenced(entries, build), rt

    def tp_setter(self, n, name):
        fam = self.prog.tables.tp_setters[name]
        if not n.args or not isinstance(n.args[0], ast.Name) or n.args[0].id not in self.tp_names:
            self.err(f"my.{name}() must be called on a thing template variable", n)
        tpv = ident(n.args[0].id)
        rest = n.args[1:]
        if n.keywords:
            # the python names are 'class' then 'value' (and 'value2') but keyword use is not expected
            self.err("keyword arguments to tp setter unsupported", n)
        if fam == "int":
            if len(rest) > 1:
                self.err(f"my.{name}: too many arguments", n)
            v = self.conv_arg(rest[0], "int", rest[0]) if rest else "0"
            return f"{tpv}->{name}_set({v})", "void"
        if fam == "str":
            if len(rest) != 1:
                self.err(f"my.{name}: expected one string argument", n)
            c, t = self.ex(rest[0])
            if t is not None and t != "str":
                self.err(f"my.{name}: expected str, got {t}", n)
            return f"{tpv}->{name}_set({c})", "void"
        if fam == "int_int":
            if len(rest) != 2:
                self.err(f"my.{name}: expected two integers", n)
            a = self.conv_arg(rest[0], "int", rest[0])
            b = self.conv_arg(rest[1], "int", rest[1])
            return self.sequenced([(a, rest[0]), (b, rest[1])], lambda c: f"{tpv}->{name}_set({c[0]}, {c[1]})"), "void"
        self.err("tp setter family", n)

    def tile_call(self, n, name):
        if not n.args or not isinstance(n.args[0], ast.Name) or n.args[0].id not in self.tp_names:
            self.err(f"my.{name}() must be called on a thing template variable", n)
        given = {}
        if len(n.args) - 1 > len(TILE_FIELDS):
            self.err("too many positional tile arguments", n)
        for fld, a in zip(TILE_FIELDS, n.args[1:]):
            given[fld] = a
        for k in n.keywords:
            if k.arg not in TILE_FIELDS:
                self.err(f"unknown tile keyword {k.arg}", n)
            if k.arg in given:
                self.err(f"duplicate tile argument {k.arg}", n)
            given[k.arg] = k.value
        order = list(given.keys())                       # python evaluation order
        entries = []
        for fld in order:
            nd = given[fld]
            if fld in TILE_STR_FIELDS:
                c, t = self.ex(nd)
                if t is not None and t != "str":
                    self.err(f"tile {fld} must be a string", n)
            else:
                c = self.conv_arg(nd, 'int', nd)
            entries.append((c, nd))
        tpv = ident(n.args[0].id)

        def build(codes):
            by = dict(zip(order, codes))
            parts = [f".{fld} = {by[fld]}" for fld in TILE_FIELDS if fld in by]
            return f"my::{name}({tpv}, {{{', '.join(parts)}}})"
        return self.sequenced(entries, build), "void"

    def call_my(self, n, name):
        t = self.prog.tables
        if name in t.tp_setters:
            return self.tp_setter(n, name)
        if name in TILE_FUNCS:
            return self.tile_call(n, name)
        if name in ("tp_update", "tp_load"):
            return "", "void"
        if name in DICE_FUNCS:
            return f"{DICE_FUNCS[name]}()", "int"
        if name in MISC_MY:
            fn, ret, ptypes = MISC_MY[name]
            if len(n.args) != len(ptypes) or n.keywords:
                self.err(f"my.{name} arity", n)
            entries = [(self.prep_arg(a, pt), a) for a, pt in zip(n.args, ptypes)]

            def build(codes):
                args = [(f"({c}).c_str()" if pt == "str" and not self.is_lit(c) else c) for c, pt in zip(codes, ptypes)]
                return f"{fn}({', '.join(args)})"
            return self.sequenced(entries, build), ret
        if name in t.api:
            return self.api_call(n, name, t.api[name])
        self.err(f"unknown my.{name}", n)

    def local_call(self, n, mod, fname):
        sig = self.prog.sigs.get((mod.relpath, fname))
        if not sig:
            self.err(f"unknown function {mod.stem}.{fname}", n)
        bound = self.bind(n, sig.params)
        order = list(bound.keys())
        entries = []
        for p in order:
            pt = sig.ptypes.get(p)
            entries.append((self.ex(bound[p])[0] if pt is None else self.conv_arg(bound[p], pt, bound[p]), bound[p]))
        by_default = {}
        for p in sig.params:
            if p not in bound:
                if p not in sig.defaults:
                    self.err(f"missing argument '{p}' calling {fname}", n)
                pt = sig.ptypes.get(p)
                by_default[p] = self.conv_arg(sig.defaults[p], pt, sig.defaults[p]) if pt else "0"
        prefix = "" if mod is self.mod else mod.ns + "::"
        self.prog.note_call(self.mod, mod, sig)

        def build(codes):
            by = dict(zip(order, codes))
            by.update(by_default)
            return f"{prefix}{ident(fname)}({', '.join(by[p] for p in sig.params)})"
        return self.sequenced(entries, build), (sig.ret or ("void" if self.prog.rets_final else None))

    # ---- statements --------------------------------------------------------------------------
    def stmts(self, body):
        for s in body:
            self.stmt(s)

    def stmt(self, s):
        m = getattr(self, "st_" + type(s).__name__, None)
        if not m:
            self.err(f"unsupported statement {type(s).__name__}", s)
        m(s)

    def st_Pass(self, s):
        pass

    def st_Global(self, s):
        pass

    def st_Import(self, s):
        pass

    def st_Break(self, s):
        self.w("break;")

    def st_Continue(self, s):
        self.w("continue;")

    def st_Expr(self, s):
        v = s.value
        if isinstance(v, ast.Constant):
            return
        if isinstance(v, ast.Call) and isinstance(v.func, ast.Attribute) and v.func.attr == "append" \
                and isinstance(v.func.value, ast.Name):
            name = v.func.value.id
            c, t = self.ex(v.args[0])
            self.set_var(name, {"str": "list_str", "int": "list_thing", "thing": "list_thing"}.get(t), s)
            self.w(f"{ident(name)}.push_back({c});")
            return
        c, t = self.ex(v)
        if c:
            self.w(c + ";")

    def st_Assign(self, s):
        if len(s.targets) != 1:
            self.err("chained assignment", s)
        tgt = s.targets[0]
        v = s.value
        # self = tp.Tp(...)
        if isinstance(tgt, ast.Name) and isinstance(v, ast.Call) and isinstance(v.func, ast.Attribute) \
                and isinstance(v.func.value, ast.Name) and v.func.value.id == "tp" and v.func.attr == "Tp":
            if v.keywords or not (1 <= len(v.args) <= 3):
                self.err("tp.Tp() arguments", s)
            args = []
            for a in v.args:
                c, t = self.ex(a)
                if t is not None and t != "str":
                    self.err("tp.Tp() takes strings", s)
                args.append(self.as_string(c, t) if t else c)
            first = tgt.id not in self.tp_names
            self.tp_names.add(tgt.id)
            self.w(f"{'Tpp ' if first else ''}{ident(tgt.id)} = my::tp_load({', '.join(args)});")
            return
        if isinstance(tgt, ast.Name):
            if isinstance(v, (ast.List, ast.Tuple)) and not v.elts:
                self.set_var(tgt.id, "list_empty", s)
                if self.emit and self.vars.get(tgt.id) == "list_empty":
                    self.err("empty list never filled", s)
                self.w(f"{ident(tgt.id)}.clear();")
                return
            c, t = self.ex(v)
            if t == "none":
                self.err("None assignment", s)
            if t == "tp":
                first = tgt.id not in self.tp_names
                self.tp_names.add(tgt.id)
                self.w(f"{'Tpp ' if first else ''}{ident(tgt.id)} = {c};")
                return
            self.set_var(tgt.id, t, s)
            vt = self.vtype(tgt.id)
            if vt == "str" and t == "str":
                c = self.as_string(c, t)
            if vt in ("int", "thing") and t == "float":
                self.err(f"float assigned to integer variable {tgt.id}", s)
            self.w(f"{ident(tgt.id)} = {c};")
            return
        if isinstance(tgt, (ast.Tuple, ast.List)):
            c, t = self.ex(v)
            if t != "pair_int" and t is not None:
                self.err(f"tuple unpack of {t}", s)
            if len(tgt.elts) != 2 or not all(isinstance(e, ast.Name) for e in tgt.elts):
                self.err("unsupported unpack target", s)
            for e in tgt.elts:
                self.set_var(e.id, "int", s)
            tmp = f"pair{s.lineno}_"
            self.w(f"{{ auto {tmp} = {c}; {ident(tgt.elts[0].id)} = {tmp}.first; {ident(tgt.elts[1].id)} = {tmp}.second; }}")
            return
        self.err("unsupported assignment target", s)

    def st_AugAssign(self, s):
        if not isinstance(s.target, ast.Name):
            self.err("augmented assignment target", s)
        c, t = self.ex(s.value)
        name = s.target.id
        cur = self.vtype(name)
        sym = {ast.Add: "+", ast.Sub: "-", ast.Mult: "*"}.get(type(s.op))
        if cur == "str" and isinstance(s.op, ast.Add):
            self.w(f"{ident(name)} += {c};")
            return
        if not sym:
            self.err("unsupported augmented operator", s)
        if t == "float":
            self.set_var(name, "float", s)
        elif t is not None and t not in NUMERIC:
            self.err("augmented assignment of non number", s)
        else:
            self.set_var(name, cur if cur else "int", s)
        self.w(f"{ident(name)} {sym}= {c};")

    def static_none_test(self, test):
        """True/False if `x is [not] None` is decided by x's static type, else None."""
        if isinstance(test, ast.Compare) and len(test.ops) == 1 and isinstance(test.ops[0], (ast.Is, ast.IsNot)) \
                and isinstance(test.comparators[0], ast.Constant) and test.comparators[0].value is None \
                and isinstance(test.left, ast.Name):
            t = self.vtype(test.left.id)
            if t in ("str", "list_str", "int", "thing", "bool", "float", "tp"):
                return isinstance(test.ops[0], ast.IsNot)
        return None

    def st_If(self, s):
        decided = self.static_none_test(s.test)
        if decided is not None:
            chosen = s.body if decided else s.orelse
            self.w("{")
            self.ind += 1
            self.stmts(chosen)
            self.ind -= 1
            self.w("}")
            return
        self.w(f"if ({self.cond(s.test)}) {{")
        self.ind += 1
        self.stmts(s.body)
        self.ind -= 1
        orelse = s.orelse
        while len(orelse) == 1 and isinstance(orelse[0], ast.If):
            e = orelse[0]
            self.w(f"}} else if ({self.cond(e.test)}) {{")
            self.ind += 1
            self.stmts(e.body)
            self.ind -= 1
            orelse = e.orelse
        if orelse:
            self.w("} else {")
            self.ind += 1
            self.stmts(orelse)
            self.ind -= 1
        self.w("}")

    def st_For(self, s):
        if s.orelse or not isinstance(s.target, ast.Name):
            self.err("for/else or tuple target", s)
        var = s.target.id
        if var in self.pre_assigned:
            return self.st_For_shared(s, var)
        it = s.iter
        if isinstance(it, ast.Call) and isinstance(it.func, ast.Name) and it.func.id == "range":
            a = [self.conv_arg(x, "int", x) for x in it.args]
            lo, hi, step = ("0", a[0], "1") if len(a) == 1 else (a[0], a[1], a[2] if len(a) == 3 else "1")
            if len(a) == 3 and not (isinstance(it.args[2], ast.Constant) and it.args[2].value > 0):
                self.err("range step must be a positive constant", s)
            self.set_loop_var(var, "int", s)
            end = f"{ident(var)}_end_"
            self.w(f"for (int {ident(var)} = {lo}, {end} = {hi}; {ident(var)} < {end}; {ident(var)} += {step}) {{")
        else:
            c, t = self.ex(it)
            if t in ("list_thing",):
                self.set_loop_var(var, "thing", s)
                self.w(f"for (auto {ident(var)} : {c}) {{")
            elif t == "list_str":
                self.set_loop_var(var, "str", s)
                self.w(f"for (const auto &{ident(var)} : {c}) {{")
            elif t == "opt_list_str":
                self.set_loop_var(var, "str", s)
                self.w(f"for (const auto &{ident(var)} : *{c}) {{")
            elif t is None:
                self.w("for (;;) {")
            else:
                self.err(f"cannot iterate over {t}", s)
        self.ind += 1
        self.stmts(s.body)
        self.ind -= 1
        self.w("}")

    def st_For_shared(self, s, var):
        """Loop variable that is also assigned elsewhere in the function: hoisted, set from a loop temporary."""
        it = s.iter
        tmp = f"{var}_loop_"
        if isinstance(it, ast.Call) and isinstance(it.func, ast.Name) and it.func.id == "range":
            a = [self.conv_arg(x, "int", x) for x in it.args]
            lo, hi = ("0", a[0]) if len(a) == 1 else (a[0], a[1])
            if len(a) > 2:
                self.err("range step with shared loop variable", s)
            self.set_var(var, "int", s)
            self.w(f"for (int {tmp} = {lo}, {tmp}end_ = {hi}; {tmp} < {tmp}end_; {tmp}++) {{")
        else:
            c, t = self.ex(it)
            if t == "list_thing":
                self.set_var(var, "thing", s)
            elif t == "list_str":
                self.set_var(var, "str", s)
            elif t is None:
                self.w("for (;;) {")
                self.ind += 1
                self.stmts(s.body)
                self.ind -= 1
                self.w("}")
                return
            else:
                self.err(f"cannot iterate over {t}", s)
            self.w(f"for (const auto &{tmp} : {c}) {{")
        self.ind += 1
        self.w(f"{ident(var)} = {tmp};")
        self.stmts(s.body)
        self.ind -= 1
        self.w("}")

    def st_Return(self, s):
        kind = self.sig.kind
        v = s.value
        if kind in ("void", None) and self.sig.ret in (None, "void") and not self.prog.infer_ret.get(id(self.sig)):
            pass
        if kind == "void":
            if v is not None and not (isinstance(v, ast.Constant)):
                c, t = self.ex(v)
                if c:
                    self.w(f"(void) {c};")
            self.w("return;")
            return
        if v is None or (isinstance(v, ast.Constant) and v.value is None):
            if kind == "bool":
                self.w("return false;")
            elif kind == "int":
                self.w("return 0;")
            elif kind == "list_str":
                self.w("return {};")
            else:
                self.ret_types.append("void")
                self.w("return;")
            return
        if kind == "bool":
            self.w(f"return {self.cond(v)};")
            return
        if kind == "int":
            c, t = self.ex(v)
            if t == "float":
                self.err("int callback returns a float", s)
            if t not in ("int", "thing", "bool", None):
                self.err(f"int callback returns {t}", s)
            self.w(f"return {c};")
            return
        if kind == "list_str":
            c, t = self.conv_arg_list_return(v)
            self.w(f"return {c};")
            return
        c, t = self.ex(v)
        self.ret_types.append(t)
        if t == "str":
            c = self.as_string(c, t)
        self.w(f"return {c};")

    def conv_arg_list_return(self, v):
        if isinstance(v, (ast.List, ast.Tuple)):
            c, t = self.list_lit(v.elts, v)
            if t not in ("list_str", "list_empty"):
                self.err("list return must be strings", v)
            return ("{}" if t == "list_empty" else c), "list_str"
        c, t = self.ex(v)
        if t != "list_str":
            self.err("list return", v)
        return c, t


# ---------------------------------------------------------------------------------------------
# Program
# ---------------------------------------------------------------------------------------------
DMG_KIND_RE = re.compile(r'^on_(owner_rcv|rcv|attacking|owner_attack)_dmg_\w+_do$')
BOOL_SETTERS = {"on_tick_do", "on_tick_when_activated_do", "on_tick_when_deactivated_do", "on_want_to_shoot_at_do"}
SKIP_FILES = {"init.py", "tp.py", "__init__.py"}
MODULE_LEVEL_SKIP_ASSIGN = {"self", "timeme_enabled"}


def setter_kind(setter):
    if DMG_KIND_RE.match(setter):
        return "int"
    if setter in BOOL_SETTERS:
        return "bool"
    if setter == "on_get_text_description_long_do":
        return "list_str"
    return "void"


class Program:
    def __init__(self, pyroot, outsrc, work, src_orig):
        self.pyroot, self.outsrc, self.work = pyroot, outsrc, work
        self.tables = Tables(src_orig, work)
        self.modules = []
        self.by_stem = collections.defaultdict(list)
        self.sigs = {}
        self.rets_final = False
        self.failed = {}
        self.infer_ret = {}
        self.cross = collections.defaultdict(set)     # caller relpath -> set(callee Module)
        self.ref_stats = collections.Counter()

    # ---- loading ----------------------------------------------------------------------------
    def load(self):
        rels = []
        for d, _, fs in os.walk(self.pyroot):
            if "__pycache__" in d:
                continue
            for f in fs:
                if f.endswith(".py") and f not in SKIP_FILES and not f.startswith("._"):
                    rels.append(os.path.relpath(os.path.join(d, f), self.pyroot))
        rels.sort()
        for r in rels:
            tree = ast.parse(open(os.path.join(self.pyroot, r), encoding="utf-8").read())
            m = Module(r, tree)
            self.modules.append(m)
            self.by_stem[m.stem].append(m)
        for m in self.modules:
            for n in m.tree.body:
                if isinstance(n, ast.Import):
                    for a in n.names:
                        if a.name in self.by_stem:
                            cands = self.by_stem[a.name]
                            if len(cands) != 1:
                                raise Unsupported(f"{m.relpath}: ambiguous import {a.name}")
                            m.imports[a.asname or a.name] = cands[0]
                            cands[0].shared = True
                        elif a.name not in ("my", "tp", "math", "random", "time", "os", "sys", "fnmatch"):
                            raise Unsupported(f"{m.relpath}: unknown import {a.name}")
                elif isinstance(n, ast.ImportFrom):
                    raise Unsupported(f"{m.relpath}: from-import")

    def active_funcs(self, m):
        return [f for f in m.tree.body if isinstance(f, ast.FunctionDef) and f.name != "timeme"]

    # ---- signatures -------------------------------------------------------------------------
    def build_sigs(self):
        for m in self.modules:
            for f in self.active_funcs(m):
                for d in f.decorator_list:
                    if not (isinstance(d, ast.Name) and d.id == "timeme"):
                        raise Unsupported(f"{m.relpath}:{f.name}: decorator")
                self.sigs[(m.relpath, f.name)] = Sig(m, f)
        # parameter types: by name, by defaults, then by call sites
        for sig in self.sigs.values():
            for p in sig.params:
                if p in PARAM_NAME_TYPE:
                    sig.ptypes[p] = PARAM_NAME_TYPE[p]
                elif p in sig.defaults:
                    d = sig.defaults[p]
                    if isinstance(d, ast.List):
                        sig.ptypes[p] = "list_str"
                    elif isinstance(d, ast.Constant) and d.value is None:
                        sig.ptypes[p] = None            # decided from call sites
                    elif isinstance(d, ast.Constant):
                        sig.ptypes[p] = self.light(d, None)
        # call site inference
        pending = [(s, p) for s in self.sigs.values() for p in s.params if s.ptypes.get(p) is None]
        for _ in range(4):
            still = []
            for sig, p in pending:
                t = None
                for caller_mod, caller_sig, call in self.calls_to(sig):
                    bound = {}
                    for pn, a in zip(sig.params, call.args):
                        bound[pn] = a
                    for k in call.keywords:
                        bound[k.arg] = k.value
                    if p in bound:
                        lt = self.light(bound[p], caller_sig)
                        if lt is not None:
                            t = unify_param(t, lt)
                if t is None and p in sig.defaults and isinstance(sig.defaults[p], ast.Constant) and sig.defaults[p].value is None:
                    t = None
                if t is None:
                    still.append((sig, p))
                else:
                    sig.ptypes[p] = t
            pending = still
            if not pending:
                break
        for sig, p in pending:
            if p in sig.defaults:
                sig.ptypes[p] = "opt_list_str"
            else:
                raise Unsupported(f"{sig.mod.relpath}:{sig.name}: cannot infer type of parameter '{p}'")

    def calls_to(self, sig):
        for m in self.modules:
            for f in self.active_funcs(m):
                csig = self.sigs[(m.relpath, f.name)]
                for c in ast.walk(f):
                    if not isinstance(c, ast.Call):
                        continue
                    fn = c.func
                    if isinstance(fn, ast.Name) and m is sig.mod and fn.id == sig.name:
                        yield m, csig, c
                    elif isinstance(fn, ast.Attribute) and isinstance(fn.value, ast.Name) \
                            and m.imports.get(fn.value.id) is sig.mod and fn.attr == sig.name:
                        yield m, csig, c
            # module level calls
            for n in m.tree.body:
                if isinstance(n, ast.Expr):
                    for c in ast.walk(n):
                        if isinstance(c, ast.Call) and isinstance(c.func, ast.Name) and m is sig.mod \
                                and c.func.id == sig.name:
                            yield m, None, c

    def light(self, node, caller_sig):
        if isinstance(node, ast.Constant):
            v = node.value
            if isinstance(v, bool):
                return "bool"
            if isinstance(v, int):
                return "int"
            if isinstance(v, float):
                return "float"
            if isinstance(v, str):
                return "str"
            return None
        if isinstance(node, (ast.List, ast.Tuple)):
            if all(isinstance(e, ast.Constant) and isinstance(e.value, str) for e in node.elts):
                return "list_str"
            return None
        if isinstance(node, ast.Name):
            if node.id in PARAM_NAME_TYPE:
                return PARAM_NAME_TYPE[node.id]
            if caller_sig and caller_sig.ptypes.get(node.id):
                return caller_sig.ptypes[node.id]
            return None
        if isinstance(node, (ast.JoinedStr,)):
            return "str"
        if isinstance(node, ast.Call) and isinstance(node.func, ast.Name) and caller_sig is not None:
            callee = self.sigs.get((caller_sig.mod.relpath, node.func.id))
            if callee:
                for r in ast.walk(callee.node):
                    if isinstance(r, ast.Return) and r.value is not None:
                        return self.light(r.value, callee)
            return None
        if isinstance(node, ast.BinOp) and isinstance(node.op, ast.Add):
            a, b = self.light(node.left, caller_sig), self.light(node.right, caller_sig)
            return "str" if "str" in (a, b) else None
        return None

    def note_call(self, caller, callee, sig):
        if callee is not caller:
            self.cross[caller.relpath].add(callee)
            callee.shared = True

    # ---- callback kinds ---------------------------------------------------------------------
    def assign_kinds(self):
        def mark(owner_mod, modkey, fn, kind, where):
            if modkey == "me":
                # 'me' is the name of the thing being initialised. That is normally this module, but a shared
                # setter library (tp_init(self)) is run on behalf of the modules that import it.
                if (owner_mod.relpath, fn) in self.sigs:
                    targets = [owner_mod]
                else:
                    targets = [x for x in self.modules if owner_mod in x.imports.values() and (x.relpath, fn) in self.sigs]
                if not targets:
                    self.ref_stats[f"unresolved me.{fn} (from {where})"] += 1
                    return
            else:
                targets = [(self.by_stem.get(modkey) or [None])[0]]
                if targets[0] is None:
                    self.ref_stats["unresolved module " + modkey] += 1
                    return
            for target in targets:
                mark_one(target, fn, kind, where)

        def mark_one(target, fn, kind, where):
            sig = self.sigs.get((target.relpath, fn))
            if not sig:
                self.ref_stats[f"missing function {target.stem}.{fn} (from {where})"] += 1
                return
            if sig.kind and sig.kind != kind:
                # void references (dice strings) never conflict; a value kind wins over void
                if kind == "void":
                    return
                if sig.kind != "void":
                    raise Unsupported(f"{target.relpath}:{fn} referenced as both {sig.kind} and {kind}")
            sig.kind = kind if (not sig.kind or sig.kind == "void") else sig.kind

        for m in self.modules:
            for f in self.active_funcs(m):
                for c in ast.walk(f):
                    if not (isinstance(c, ast.Call) and isinstance(c.func, ast.Attribute)
                            and isinstance(c.func.value, ast.Name) and c.func.value.id == "my"):
                        continue
                    setter = c.func.attr
                    if setter not in self.tables.tp_setters or self.tables.tp_setters[setter] != "str":
                        continue
                    if len(c.args) < 2 or not isinstance(c.args[1], ast.Constant) or not isinstance(c.args[1].value, str):
                        continue
                    s = c.args[1].value
                    if setter.endswith("_do"):
                        mm = re.match(r'^(\w+)\.(\w+)\(\)$', s)
                        if mm:
                            mark(m, mm.group(1), mm.group(2), setter_kind(setter), f"{m.relpath}:{setter}")
                        elif s:
                            self.ref_stats["odd _do string"] += 1
                    elif ":" in s or "()" in s:
                        for tok in s.split(":"):
                            mm = re.match(r'^(?:(\w+)\.)?(\w+)\(\)$', tok)
                            if mm and mm.group(1):
                                mark(m, mm.group(1), mm.group(2), "void", f"{m.relpath}:{setter}")
        for m in self.by_stem.get("events", []):
            for f in self.active_funcs(m):
                self.sigs[(m.relpath, f.name)].kind = "void"

    # ---- translation ------------------------------------------------------------------------
    def translate(self, m, sig, emit):
        body = sig.node.body
        known = {}
        tr = None
        for _ in range(8):
            tr = FuncTr(self, m, sig, known)
            tr.tp_names = {p for p, t in sig.ptypes.items() if t == "tp"}
            tr.stmts(body)
            if tr.vars == known and not tr.unknown:
                break
            known = dict(tr.vars)
        if emit:
            tr = FuncTr(self, m, sig, known, emit=True)
            tr.tp_names = {p for p, t in sig.ptypes.items() if t == "tp"}
            tr.stmts(body)
        return tr

    def infer_all(self):
        for rnd in range(8):
            changed = False
            for m in self.modules:
                for f in self.active_funcs(m):
                    sig = self.sigs[(m.relpath, f.name)]
                    try:
                        tr = self.translate(m, sig, False)
                    except Unsupported as e:
                        self.failed[(m.relpath, f.name)] = str(e)
                        continue
                    self.failed.pop((m.relpath, f.name), None)
                    if sig.kind:
                        new = sig.kind
                    else:
                        ts = [t for t in tr.ret_types if t not in (None, "void", "none")]
                        if not ts:
                            new = "void" if not any(t is None for t in tr.ret_types) else None
                        else:
                            t = None
                            for x in ts:
                                t = unify(t, x)
                            new = t
                    if new != sig.ret:
                        sig.ret = new
                        changed = True
            if not changed:
                break
        self.rets_final = True
        for sig in self.sigs.values():
            if sig.ret is None:
                sig.ret = "void"

    # ---- emission ---------------------------------------------------------------------------
    def hdr_rel(self, m):
        return m.out_rel[:-4] + ".hpp"

    def decl_default(self, t):
        return {"int": "0", "float": "0.0", "bool": "false", "thing": "0"}.get(t)

    def func_cpp(self, m, sig):
        tr = self.translate(m, sig, True)
        out = []
        static = "" if m.shared else "static "
        out.append(f"{static}{sig.cpp_ret()} {ident(sig.name)}({sig.cpp_params()})")
        out.append("{")
        decls = []
        for v, t in sorted(tr.vars.items()):
            if v in sig.ptypes or v in tr.tp_names:
                continue
            if v in tr.loopvars and v in tr.assigned:
                raise Unsupported(f"{tr.ctx}: variable '{v}' is both a loop variable and assigned")
            if v not in tr.assigned:
                continue
            if t == "list_empty":
                raise Unsupported(f"{tr.ctx}: list variable '{v}' has no element type")
            dd = self.decl_default(t)
            decls.append(f"  {cpp_type(t)} {ident(v)}" + (f" = {dd};" if dd else ";"))
        out += decls
        out += tr.lines
        r = sig.ret
        if tr.lines and tr.lines[-1].strip().startswith("return") and tr.lines[-1].startswith("  return"):
            r = None
        if r == "bool":
            out.append("  return false;")
        elif r in ("int", "thing"):
            out.append("  return 0;")
        elif r == "float":
            out.append("  return 0.0;")
        elif r == "str":
            out.append('  return "";')
        elif r in ("list_str", "list_thing"):
            out.append("  return {};")
        elif r == "tp":
            out.append("  return nullptr;")
        out.append("}")
        return "\n".join(out)

    def eligible(self, sig):
        if sig.defaults or not sig.params:
            return False
        if not all(p in THING_PARAMS or p in INT_PARAMS for p in sig.params):
            return False
        if sig.name == "init" or sig.name.endswith("_init"):
            return False
        return sig.ret in ("void", "bool", "int", "thing") or sig.kind == "list_str"

    def thunk(self, m, sig):
        args = []
        for i, p in enumerate(sig.params):
            args.append(f"({'uint32_t' if sig.ptypes[p] == 'thing' else 'int'}) a[{i}]")
        call = f"{ident(sig.name)}({', '.join(args)})"
        kind = sig.kind or {"void": "void", "bool": "bool", "int": "int", "thing": "int"}[sig.ret]
        if kind == "void":
            body = f"{call}; return NativeRet {{}};"
        elif kind in ("bool", "int"):
            body = f"return NativeRet {{(int) {call}, {{}}}};"
        else:
            body = f"return NativeRet {{0, {call}}};"
        return (f'  native_register({cstr(m.stem)}, {cstr(sig.name)}, {len(sig.params)}, '
                f'[](const int64_t *a) -> NativeRet {{ (void) a; {body} }});')

    def module_cpp(self, m):
        bad = [v for (rel, fn), v in self.failed.items() if rel == m.relpath]
        if bad:
            raise Unsupported(" | ".join(bad))
        funcs = self.active_funcs(m)
        sigs = [self.sigs[(m.relpath, f.name)] for f in funcs]
        protos, defs = [], []
        for s in sigs:
            static = "" if m.shared else "static "
            protos.append(f"{static}{s.cpp_ret()} {ident(s.name)}({s.cpp_params()});")
            defs.append(self.func_cpp(m, s))
        # module body
        body_sig = Sig.__new__(Sig)
        body_sig.mod, body_sig.name, body_sig.params, body_sig.defaults = m, "module_init", [], {}
        body_sig.ptypes, body_sig.ret, body_sig.kind = {}, "void", "void"
        stmts = []
        for n in m.tree.body:
            if isinstance(n, (ast.FunctionDef, ast.Import)):
                continue
            if isinstance(n, ast.Expr) and isinstance(n.value, ast.Constant):
                continue
            if isinstance(n, ast.Assign) and all(isinstance(t, ast.Name) and (t.id in MODULE_LEVEL_SKIP_ASSIGN or t.id in m.globals) for t in n.targets):
                continue
            stmts.append(n)
        body_sig.node = ast.FunctionDef(name="module_init", args=ast.arguments(posonlyargs=[], args=[], kwonlyargs=[],
                                        kw_defaults=[], defaults=[]), body=stmts or [ast.Pass()], decorator_list=[])
        self.sigs[(m.relpath, "<module>")] = body_sig
        tr = self.translate(m, body_sig, True)
        reg = [self.thunk(m, s) for s in sigs if self.eligible(s)]
        inc = ['#include "my_native.hpp"']
        for callee in sorted({c.relpath for c in self.cross.get(m.relpath, ())}):
            cm = next(x for x in self.modules if x.relpath == callee)
            inc.append(f'#include "{self.hdr_rel(cm)}"')
        if m.shared:
            inc.append(f'#include "{self.hdr_rel(m)}"')
        out = [f"//\n// Copyright goblinhack@gmail.com\n//\n// Converted from python/{m.relpath}\n//\n"]
        out.append("\n".join(inc))
        out.append(f"\nnamespace {m.ns} {{\n")
        if m.globals:
            out.append("\n".join(f"static {cpp_type(t)} {ident(k)} = {v};" for k, (t, v) in m.globals.items()) + "\n")
        if not m.shared:
            out.append("\n".join(protos) + "\n")
        out.append("\n\n".join(defs))
        out.append("\nvoid module_init(void)\n{")
        out += reg
        out += tr.lines
        out.append("}\n")
        out.append(f"}} // namespace {m.ns}\n")
        return "\n".join(out)

    def header_cpp(self, m):
        funcs = self.active_funcs(m)
        guard = "_" + m.ns.upper() + "_HPP_"
        lines = [f"//\n// Copyright goblinhack@gmail.com\n//\n// Converted from python/{m.relpath}\n//\n",
                 f"#pragma once\n#ifndef {guard}\n#define {guard}\n", '#include "my_native.hpp"\n',
                 f"namespace {m.ns} {{"]
        for f in funcs:
            s = self.sigs[(m.relpath, f.name)]
            lines.append(f"{s.cpp_ret()} {ident(s.name)}({s.cpp_params()});")
        lines.append(f"void module_init(void);")
        lines.append(f"}} // namespace {m.ns}\n\n#endif\n")
        return "\n".join(lines)

    def modules_cpp(self):
        lines = ["//\n// Copyright goblinhack@gmail.com\n//\n// Loads every converted python module, in the order the python loader did.\n"
                 "// Generated by py2cpp.\n//\n", '#include "my_native.hpp"\n']
        for m in self.modules:
            lines.append(f"namespace {m.ns} {{ void module_init(void); }}")
        lines.append("\nvoid native_init_all(void)\n{")
        for m in self.modules:
            lines.append(f"  {m.ns}::module_init();")
        lines.append("}\n")
        return "\n".join(lines)


def unify_param(a, b):
    if a is None:
        return b
    if a == b:
        return a
    if {a, b} <= {"list_str", "opt_list_str"}:
        return "opt_list_str"
    return unify(a, b)


def main():
    pyroot, outsrc, work = sys.argv[1:4]
    src_orig = os.environ.get("ORIG_SRC", "/tmp/orig/src")
    only = os.environ.get("ONLY")
    p = Program(pyroot, outsrc, work, src_orig)
    p.load()
    p.build_sigs()
    p.assign_kinds()
    p.infer_all()
    ok, bad = 0, []
    outputs = {}
    for m in p.modules:
        if only and only not in m.relpath:
            continue
        try:
            outputs[m.out_rel] = p.module_cpp(m)
            if m.shared:
                outputs[p.hdr_rel(m)] = p.header_cpp(m)
            ok += 1
        except Unsupported as e:
            bad.append((m.relpath, str(e)))
    # shared flag can change while emitting (note_call): regenerate headers/modules that became shared
    for m in p.modules:
        if m.shared and p.hdr_rel(m) not in outputs and (not only or only in m.relpath):
            outputs[p.hdr_rel(m)] = p.header_cpp(m)
    outputs["native_modules.cpp"] = p.modules_cpp()
    for rel, text in outputs.items():
        full = os.path.join(outsrc, rel)
        os.makedirs(os.path.dirname(full), exist_ok=True)
        open(full, "w").write(text)
    print(f"translated {ok} modules, {len(bad)} failed; ref stats: {dict(p.ref_stats)}")
    json.dump(bad, open(os.path.join(work, "failures.json"), "w"), indent=1)
    for rel, e in bad[:40]:
        print("FAIL", rel, "::", e)


if __name__ == "__main__":
    main()
