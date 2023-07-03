//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"

void Thing::update_light(void)
{
  TRACE_NO_INDENT();

  if (! is_player()) {
    return;
  }

  if (is_hidden) {
    return;
  }

  if (! level) {
    return;
  }

  for (auto l : light_get()) {
    l->cached_light_pos = point(-1, -1);
  }
}

void Thing::update(void)
{
  TRACE_NO_INDENT();

  auto tpp     = tp();
  int  carried = 0;

  //
  // Cached as used often
  //
  gfx_pixelart_animated = tpp->gfx_pixelart_animated();
  gfx_ascii_animated    = tpp->gfx_ascii_animated();

  //
  // If polymorphed, retain the same health
  //
  if (! health()) {
    TRACE_NO_INDENT();
    //
    // Well it wont be the same health, it is a dice roll
    //
    auto v = tpp->health_initial();
    if (unlikely(v)) {
      health_set(v);
      health_max_set(v);
    }
  }

  if (has_temperature()) {
    TRACE_NO_INDENT();
    auto v = tpp->temperature();
    if (unlikely(v)) {
      temperature_set(v);
    }
  }
  if (! stamina()) {
    TRACE_NO_INDENT();
    auto v = tpp->stamina();
    if (unlikely(v)) {
      stamina_set(v);
      stamina_max_set(v);
    }
  }
  if (! magic()) {
    TRACE_NO_INDENT();
    auto v = tpp->magic();
    if (unlikely(v)) {
      magic_set(v);
      magic_max_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->distance_throw();
    if (unlikely(v)) {
      distance_throw_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->enchant_max();
    if (unlikely(v)) {
      enchant_max_current_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->jump_distance_bonus();
    if (unlikely(v)) {
      jump_distance_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->lifespan();
    if (unlikely(v)) {
      lifespan_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->move_speed_bonus();
    if (unlikely(v)) {
      move_speed_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->noise_on_moving();
    if (unlikely(v)) {
      noise_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->shove_bonus();
    if (unlikely(v)) {
      shove_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_att_bonus();
    if (unlikely(v)) {
      stat_att_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_att();
    if (unlikely(v)) {
      stat_att_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_con_bonus();
    if (unlikely(v)) {
      stat_con_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_con();
    if (unlikely(v)) {
      stat_con_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_def_bonus();
    if (unlikely(v)) {
      stat_def_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_def();
    if (unlikely(v)) {
      stat_def_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_dex_bonus();
    if (unlikely(v)) {
      stat_dex_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_dex();
    if (unlikely(v)) {
      stat_dex_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_luck_bonus();
    if (unlikely(v)) {
      stat_luck_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_luck();
    if (unlikely(v)) {
      stat_luck_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats02();
    if (unlikely(v)) {
      stats02_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats03();
    if (unlikely(v)) {
      stats03_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats04();
    if (unlikely(v)) {
      stats04_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats05();
    if (unlikely(v)) {
      stats05_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats06();
    if (unlikely(v)) {
      stats06_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats07();
    if (unlikely(v)) {
      stats07_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stats09();
    if (unlikely(v)) {
      stats09_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_str_bonus();
    if (unlikely(v)) {
      stat_str_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_str();
    if (unlikely(v)) {
      stat_str_set(v);
    }
  }

  if (unlikely(tpp->charge_count())) {
    charge_count_set(tpp->charge_count());
  }

  //
  // If not already animating, then start it
  //
  if (! ts_next_frame) {
    TRACE_NO_INDENT();
    auto tiles = &tpp->tiles;
    if (gfx_pixelart_animated || gfx_ascii_animated) {
      animate();
    } else {
      auto tile = tile_random(tiles);
      if (tile) {
        tile_curr = tile->global_index;
        if (is_debug_type()) {
          con("Tile init (random): %s", tile_name(tile).c_str());
        }
      } else {
        tile_curr = 0;
      }
    }
  }

  CarryOptions carry_options;

  //
  // Auto carry of weapons?
  //
  if (is_able_to_use_weapons()) {
    dbg("Is weapon equipper");
    TRACE_AND_INDENT();

    if (d1000() < chance_d1000_carrier_of_weapon_class_A()) {
      dbg("New weapon class A");
      auto W = level->thing_new(tp_random_weapon_class_A(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_weapon_class_B()) {
      dbg("New weapon class B");
      auto W = level->thing_new(tp_random_weapon_class_B(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_weapon_class_C()) {
      dbg("New weapon class C");
      auto W = level->thing_new(tp_random_weapon_class_C(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
  }

  if (is_able_to_use_staffs()) {
    dbg("Is staff equipper");
    TRACE_AND_INDENT();

    if (d1000() < chance_d1000_carrier_of_treasure_class_A()) {
      dbg("New staff class A");
      auto W = level->thing_new(tp_random_staff_class_A(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_B()) {
      dbg("New staff class B");
      auto W = level->thing_new(tp_random_staff_class_B(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_C()) {
      dbg("New staff class C");
      auto W = level->thing_new(tp_random_staff_class_C(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
  }

  if (is_able_to_use_rings()) {
    dbg("Is ring equipper");
    TRACE_AND_INDENT();

    if (d1000() < chance_d1000_carrier_of_treasure_class_A()) {
      dbg("New ring class A");
      auto W = level->thing_new(tp_random_ring_class_A(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_B()) {
      dbg("New ring class B");
      auto W = level->thing_new(tp_random_ring_class_B(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_C()) {
      dbg("New ring class C");
      auto W = level->thing_new(tp_random_ring_class_C(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
  }

  if (is_bag_item_container()) {
    dbg("Is bag item container");
    TRACE_AND_INDENT();

    if (d1000() < chance_d1000_carrier_of_treasure_class_A()) {
      dbg("New item class A");
      auto W = level->thing_new(tp_random_item_not_a_container_class_A(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_B()) {
      dbg("New item class B");
      auto W = level->thing_new(tp_random_item_not_a_container_class_B(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_C()) {
      dbg("New item class C");
      auto W = level->thing_new(tp_random_item_not_a_container_class_C(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
  } else if (is_item_carrier()) {
    dbg("Is item carrier");
    TRACE_AND_INDENT();

    if (d1000() < chance_d1000_carrier_of_treasure_class_A()) {
      dbg("New item class A");
      auto W = level->thing_new(tp_random_item_class_A(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_B()) {
      dbg("New item class B");
      auto W = level->thing_new(tp_random_item_class_B(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
    if (d1000() < chance_d1000_carrier_of_treasure_class_C()) {
      dbg("New item class C");
      auto W = level->thing_new(tp_random_item_class_C(), curr_at, this);
      if (W) {
        carried += carry(W, carry_options);
      }
    }
  }

  //
  // Initial equip of weapons
  //
  if (is_able_to_use_weapons()) {
    dbg("Weapon equip");
    TRACE_AND_INDENT();

    Thingp best_weapon = nullptr;
    carried_weapon_highest_value(&best_weapon);
    if (best_weapon) {
      equip(best_weapon, MONST_EQUIP_WEAPON);
    }
  }

  //
  // Initial equip of armor
  //
  if (is_able_to_use_armor()) {
    dbg("Armor equip");
    TRACE_AND_INDENT();

    Thingp best_armor = nullptr;
    carried_armor_highest_value(&best_armor);
    if (best_armor) {
      equip(best_armor, MONST_EQUIP_ARMOR);
    }
  }

  //
  // Initial equip of wand
  //
  if (is_able_to_use_staffs()) {
    dbg("Staff equip");
    TRACE_AND_INDENT();

    Thingp best_staff = nullptr;
    carried_staff_highest_value(&best_staff);
    if (best_staff) {
      equip(best_staff, MONST_EQUIP_WEAPON);
    }
  }

  //
  // Initial equip of rings
  //
  if (is_able_to_use_rings()) {
    dbg("Rings equip");
    TRACE_AND_INDENT();

    //
    // Ring 1
    //
    {
      Thingp best_ring = nullptr;
      carried_ring_highest_value(&best_ring);
      if (best_ring) {
        equip(best_ring, MONST_EQUIP_RING1);
      }
    }
    //
    // Ring 2
    //
    {
      Thingp best_ring = nullptr;
      carried_ring_highest_value(&best_ring);
      if (best_ring) {
        equip(best_ring, MONST_EQUIP_RING2);
      }
    }
  }

  //
  // Initial equip of helmet
  //
  if (is_able_to_use_helmet()) {
    dbg("Helmet equip");
    TRACE_AND_INDENT();

    Thingp best_helmet = nullptr;
    carried_helmet_highest_value(&best_helmet);
    if (best_helmet) {
      equip(best_helmet, MONST_EQUIP_HELMET);
    }
  }

  //
  // Initial equip of amulet
  //
  if (is_able_to_use_amulet()) {
    dbg("Amulet equip");
    TRACE_AND_INDENT();

    Thingp best_amulet = nullptr;
    carried_amulet_highest_value(&best_amulet);
    if (best_amulet) {
      equip(best_amulet, MONST_EQUIP_AMULET);
    }
  }

  //
  // Initial equip of boots
  //
  if (is_able_to_use_boots()) {
    dbg("Boos equip");
    TRACE_AND_INDENT();

    Thingp best_boots = nullptr;
    carried_boots_highest_value(&best_boots);
    if (best_boots) {
      equip(best_boots, MONST_EQUIP_BOOTS);
    }
  }

  //
  // Initial equip of gauntlet
  //
  if (is_able_to_use_gauntlet()) {
    dbg("Gauntlet equip");
    TRACE_AND_INDENT();

    Thingp best_gauntlet = nullptr;
    carried_gauntlet_highest_value(&best_gauntlet);
    if (best_gauntlet) {
      equip(best_gauntlet, MONST_EQUIP_GAUNTLET);
    }
  }

  //
  // Initial equip of cloak
  //
  if (is_able_to_use_cloak()) {
    dbg("Cloak equip");
    TRACE_AND_INDENT();

    Thingp best_cloak = nullptr;
    carried_cloak_highest_value(&best_cloak);
    if (best_cloak) {
      equip(best_cloak, MONST_EQUIP_CLOAK);
    }
  }

  //
  // Initial equip of shield
  //
  if (is_able_to_use_shield()) {
    dbg("Shield equip");
    TRACE_AND_INDENT();

    Thingp best_shield = nullptr;
    carried_shield_highest_value(&best_shield);
    if (best_shield) {
      equip(best_shield, MONST_EQUIP_SHIELD);
    }
  }

  if (carried && (is_monst() || is_player())) {
    dbg("Final item list:");
    TRACE_AND_INDENT();
    check_all_carried_items_are_owned();
  }

  if (is_player()) {
    TRACE_NO_INDENT();
    level->request_player_light_update = true;
  }
}
