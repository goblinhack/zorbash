//
// Copyright goblinhack@gmail.com
//
// Converted from python/events.py
//

#include "my_native.hpp"

namespace mod_modules_events {

static void on_main_menu_select(int unused);
static void on_initial_dungeon_menu_select(int unused);
static void on_next_dungeon_menu_select(int unused);
static void on_level_change(int level_no, int is_boss_level);
static void on_player_death(int level_no);

static void on_main_menu_select(int unused)
{
  my::music_play("intro");
}

static void on_initial_dungeon_menu_select(int unused)
{
  return;
}

static void on_next_dungeon_menu_select(int unused)
{
  my::music_play("relaxing");
}

static void on_level_change(int level_no, int is_boss_level)
{
  return;
}

static void on_player_death(int level_no)
{
  return;
}

void module_init(void)
{
  native_register("events", "on_main_menu_select", 1, [](const int64_t *a) -> NativeRet { (void) a; on_main_menu_select((int) a[0]); return NativeRet {}; });
  native_register("events", "on_initial_dungeon_menu_select", 1, [](const int64_t *a) -> NativeRet { (void) a; on_initial_dungeon_menu_select((int) a[0]); return NativeRet {}; });
  native_register("events", "on_next_dungeon_menu_select", 1, [](const int64_t *a) -> NativeRet { (void) a; on_next_dungeon_menu_select((int) a[0]); return NativeRet {}; });
  native_register("events", "on_level_change", 2, [](const int64_t *a) -> NativeRet { (void) a; on_level_change((int) a[0], (int) a[1]); return NativeRet {}; });
  native_register("events", "on_player_death", 1, [](const int64_t *a) -> NativeRet { (void) a; on_player_death((int) a[0]); return NativeRet {}; });
}

} // namespace mod_modules_events
