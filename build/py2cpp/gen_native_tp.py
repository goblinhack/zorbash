import re
orig=open("/tmp/orig/src/py_tile.cpp").read()
start=orig.index("static PyObject *tile_dir(")
body_start=orig.index("  Tilemap *tiles = nullptr;", start)
end=orig.index("PyObject *tile(PyObject *obj", start)
body=orig[body_start:end].rstrip()
assert body.endswith("}")
body=body[:-1].rstrip()   # drop closing brace of tile_dir
body=body.replace("Py_RETURN_TRUE;","return true;").replace("Py_RETURN_FALSE;","return false;")
body=body.replace("PY_ERR(","ERR(")
body=re.sub(r'\n[ \t]*if \(tp_name\) \{\n[ \t]*myfree\(tp_name\);\n[ \t]*\}\n','\n',body)
assert "Py" not in body and "py_" not in body, [l for l in body.splitlines() if "Py" in l or "py_" in l]

fields=["delay_ms","ascii_fg_alpha","ascii_bg_alpha","frame","is_moving","is_jumping","begin_jump","is_outline",
 "is_yyy5","is_yyy6","is_yyy7","is_yyy8","is_yyy9","is_invisible","is_hp_25_percent","is_hp_50_percent","is_hp_75_percent",
 "is_hp_100_percent","is_in_water","is_sleeping","is_open","is_dead","is_end_of_anim","is_end_of_ascii_anim",
 "is_dead_on_end_of_anim","is_dead_on_end_of_ascii_anim","is_alive_on_end_of_anim","is_alive_on_end_of_ascii_anim","is_resurrecting"]
locals_=["  const char *tp_name           = tp->name().c_str();"]
locals_+= [f"  [[maybe_unused]] int {f} = a.{f};" for f in fields]
locals_+= ["  [[maybe_unused]] int left  = a.is_dir_left;","  [[maybe_unused]] int right = a.is_dir_right;",
           "  [[maybe_unused]] int up    = a.is_dir_up;","  [[maybe_unused]] int down  = a.is_dir_down;","  [[maybe_unused]] int none  = a.is_dir_none;"]
locals_+= [f"  const char *{n} = a.{k} ? a.{k}->c_str() : nullptr;" for n,k in
   (("tile_name","tile"),("ascii_fg_char_str","ascii_fg_char"),("ascii_bg_char_str","ascii_bg_char"),
    ("ascii_bg_col_name","ascii_bg_col_name"),("ascii_fg_col_name","ascii_fg_col_name"))]

variants=[("tile","NONE",1),("top1_tile","UP",1),("bot1_tile","DOWN",1),("left1_tile","LEFT",1),("right1_tile","RIGHT",1),
 ("tl1_tile","TL",1),("tr1_tile","TR",1),("bl1_tile","BL",1),("br1_tile","BR",1),("top2_tile","UP",2),("bot2_tile","DOWN",2),
 ("bot3_tile","DOWN",3),("left2_tile","LEFT",2),("right2_tile","RIGHT",2),("tl2_tile","TL",2),("tr2_tile","TR",2),
 ("bl2_tile","BL",2),("br2_tile","BR",2)]
wrappers="\n".join(f"bool {n}(Tpp tp, const TileArgs &args) {{ TRACE_NO_INDENT(); return tile_dir(tp, args, THING_DIR_{d}, {l}); }}" for n,d,l in variants)

out=f'''//
// Copyright goblinhack@gmail.com
//
// Native thing template and tile loading, formerly the python `my.tp_load()` / `my.tile()` family.
//

#include "my_native.hpp"

#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_game.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_string.hpp"
#include "my_thing_template.hpp"
#include "my_unicode.hpp"

namespace my {{

Tpp tp_load(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{{
  TRACE_NO_INDENT();
  BIG_LOCK();

  int id;
  tp_get_id(name, &id);
  auto tp = ::tp_load(id, name, text_long_name, text_short_name);

  BIG_UNLOCK();
  return tp;
}}

Tpp tp_load(const std::string &name)
{{
  return tp_load(name, name, name);
}}

Tpp tp_load(const std::string &name, const std::string &text_long_name)
{{
  return tp_load(name, text_long_name, text_long_name);
}}

static bool tile_dir(Tpp tp, const TileArgs &a, int dir, int level)
{{
{chr(10).join(locals_)}

{body}
}}

{wrappers}

int pcg_random_inclusive(int lo, int hi)
{{
  TRACE_NO_INDENT();
  return pcg_random_range_inclusive(lo, hi);
}}

int non_pcg_random_inclusive(int lo, int hi)
{{
  TRACE_NO_INDENT();
  return non_pcg_random_range_inclusive(lo, hi);
}}

void log(const char *msg)
{{
  TRACE_NO_INDENT();
  if (msg) {{
    LOG("%s", msg);
  }}
}}

void topcon(const char *msg)
{{
  TRACE_NO_INDENT();
  if (msg) {{
    auto b = string_to_wstring(msg);
    ::topcon(b.c_str());
  }}
}}

void game_set_request_to_update_same_level(void)
{{
  TRACE_NO_INDENT();
  if (! game) {{
    return;
  }}
  game->set_request_to_update_same_level();
}}

}} // namespace my
'''
open("/home/claude/src/native_tp.cpp","w").write(out)
print(len(out))
