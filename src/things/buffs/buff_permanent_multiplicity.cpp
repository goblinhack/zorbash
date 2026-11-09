//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_multiplicity.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_multiplicity {

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  uint32_t it = 0;
  int roll = 0;
  int vx = 0;
  int vy = 0;
  { auto pair13_ = my::thing_coords_get(victim); vx = pair13_.first; vy = pair13_.second; }
  if ((! my::level_is_spectral_blade_at(me, vx, vy))) {
    if ((my::level_is_alive_monst_at(me, vx, vy) || my::level_is_monst_at(me, vx, vy))) {
      roll = d100();
      if ((roll < (100 + (my::thing_enchant_count_get(me) * 5)))) {
        it = my::spawn_at_my_position(victim, "spectral_blade_companion");
        if ((it != 0)) {
          my::thing_set_leader(it, owner);
        }
      }
    }
  }
  return damage;
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);
  self->is_buff_set(true);
  self->is_loggable_set(true);
  self->is_runic_offensive_class_A_set(true);
  self->on_owner_attack_dmg_melee_do_set("me.on_owner_attack_dmg_melee()");
  self->text_description_long_set("This weapon has a chance of spawning a spectral blade every attack upon a monster");
  self->text_description_short_set("Multiplicity weapon");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_multiplicity"});
}

static void init(void)
{
  tp_init("buff_permanent_multiplicity", "multiplicity", "multiplicity");
}

void module_init(void)
{
  native_register("buff_permanent_multiplicity", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_permanent_multiplicity
