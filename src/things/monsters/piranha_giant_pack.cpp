//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/monsters/piranha_giant_pack.py
//

#include "my_native.hpp"

namespace mod_things_monsters_piranha_giant_pack {

static void on_you_are_declared_leader(uint32_t me, int x, int y);
static void on_you_are_declared_a_follower(uint32_t me, uint32_t leader, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name);
static void init(void);

static void on_you_are_declared_leader(uint32_t me, int x, int y)
{
  my::thing_polymorph(me, "piranha_giant");
}

static void on_you_are_declared_a_follower(uint32_t me, uint32_t leader, int x, int y)
{
  my::thing_polymorph(me, "piranha_giant");
}

static void tp_init(const std::string &name, const std::string &text_long_name)
{
  Tpp self = my::tp_load(name, text_long_name);
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->gfx_ascii_shown_set(true);
  self->distance_recruitment_max_set(7);
  self->is_able_to_follow_set(true);
  self->is_allied_with_set("piranha_giant_pack");
  self->is_biome_dungeon_set(true);
  self->is_biome_flooded_set(true);
  self->is_biome_swamp_set(true);
  self->is_monst_class_C_set(true);
  self->is_loggable_set(true);
  self->rarity_set(THING_RARITY_RARE);
  self->on_you_are_declared_a_follower_do_set("me.on_you_are_declared_a_follower()");
  self->environ_likes_deep_water_set(true);
  self->on_you_are_declared_leader_do_set("me.on_you_are_declared_leader()");
  self->is_swimmer_set(true);
  self->is_monst_pack_set(true);
  self->is_loggable_set(true);
  self->spawn_group_radius_set(5);
  self->spawn_group_size_dice_set("1d4+3");
}

static void init(void)
{
  tp_init("piranha_giant_pack", "piranha_giant pack");
}

void module_init(void)
{
  native_register("piranha_giant_pack", "on_you_are_declared_leader", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_are_declared_leader((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("piranha_giant_pack", "on_you_are_declared_a_follower", 4, [](const int64_t *a) -> NativeRet { (void) a; on_you_are_declared_a_follower((uint32_t) a[0], (uint32_t) a[1], (int) a[2], (int) a[3]); return NativeRet {}; });
  init();
}

} // namespace mod_things_monsters_piranha_giant_pack
