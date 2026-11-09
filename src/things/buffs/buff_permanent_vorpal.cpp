//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/buffs/buff_permanent_vorpal.py
//

#include "my_native.hpp"

namespace mod_things_buffs_buff_permanent_vorpal {

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name);
static void init(void);

static int on_owner_attack_dmg_melee(uint32_t me, uint32_t owner, uint32_t victim, int x, int y, int damage)
{
  int roll = 0;
  if ((! my::thing_is_immune_to_vorpal_weapons(victim))) {
    roll = d100();
    if ((roll < (10 + (my::thing_enchant_count_get(me) * 5)))) {
      if ((owner != 0)) {
        if (my::thing_is_player(owner)) {
          my::thing_msg(owner, ((std::string("Your vorpal weapon bites deep on the ") + my::thing_name_get(victim) + ".")).c_str());
        } else {
          my::thing_msg(owner, ([&]() { auto t1_0_ = my::thing_name_get(owner); auto t1_1_ = my::thing_name_get(victim); return (std::string("The ") + t1_0_ + "'s vorpal weapon bites deep on the " + t1_1_ + "."); }()).c_str());
        }
      }
      my::thing_dead(victim, "by a vorpal weapon");
    }
  }
  my::thing_sound_play_channel(owner, CHANNEL_WEAPON, ((std::string("sword_impact") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
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
  self->text_description_long2_set("Not all monsters are vulnerable to this kind of attack. It is a matter of scholarly debate as to whether goldfish are immune to vorpal weapons.");
  self->text_description_long3_set("Every enchant of the weapon will add 5 percent chance");
  self->text_description_long_set("This weapon has a 10 percent chance of splitting or beheading its victim.");
  self->text_description_short_set("Vorpal weapon");
  self->tick_prio_set(MAP_TICK_PRIO_NORMAL);
  self->z_prio_set(MAP_Z_PRIO_ALWAYS_BEHIND);
  my::tile(self, {.tile = "buff_vorpal"});
}

static void init(void)
{
  tp_init("buff_permanent_vorpal", "vorpal weapon", "vorpal weapon");
}

void module_init(void)
{
  native_register("buff_permanent_vorpal", "on_owner_attack_dmg_melee", 6, [](const int64_t *a) -> NativeRet { (void) a; return NativeRet {(int) on_owner_attack_dmg_melee((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5]), {}}; });
  init();
}

} // namespace mod_things_buffs_buff_permanent_vorpal
