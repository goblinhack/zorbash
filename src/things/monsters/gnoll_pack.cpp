//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/gnoll_pack.py
//

#include "my_native.hpp"

namespace mod_things_monsters_gnoll_pack {

static void on_born(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_born(uint32_t me, int x, int y)
{
  my::thing_friend(me, "gnoll");
  my::thing_enemy(me, "dogman");
  my::thing_carry(me, "dagger");
  my::thing_carry(me, "dart");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->gfx_ascii_shown_set(true);
  self->is_able_to_follow_set(true);
  self->is_allied_with_set("gnoll_pack");
  self->is_biome_dungeon_set(true);
  self->is_biome_swamp_set(true);
  self->distance_recruitment_max_set(7);
  self->is_monst_class_B_set(true);
  self->is_loggable_set(true);
  self->is_monst_pack_set(true);
  self->is_loggable_set(true);
  self->spawn_group_radius_set(4);
  self->spawn_group_size_dice_set("1d4+3");
}

static void init(void)
{
  tp_init("gnoll_pack", "gnoll pack");
}

void module_init(void)
{
  native_register("gnoll_pack", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_gnoll_pack
