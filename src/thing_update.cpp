//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_monst.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

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

  size_t c = 0;
  for (auto l : light_get()) {
    l->cached_light_pos = point(-1, -1);
    c++;
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
  is_gfx_pixelart_animated = tpp->gfx_pixelart_animated();
  is_gfx_ascii_animated    = tpp->gfx_ascii_animated();

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

  //
  // If polymorphed, retain the same health
  //
  if (! stamina()) {
    TRACE_NO_INDENT();
    auto v = tpp->stamina();
    if (unlikely(v)) {
      stamina_set(v);
      stamina_max_set(v);
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
    auto v = tpp->stat_def();
    if (unlikely(v)) {
      stat_def_set(v);
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
    auto v = tpp->stat_dex();
    if (unlikely(v)) {
      stat_dex_set(v);
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
    auto v = tpp->stat_att_mod();
    if (unlikely(v)) {
      stat_att_mod_set(v);
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
    auto v = tpp->stat_def_mod();
    if (unlikely(v)) {
      stat_def_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_con_mod();
    if (unlikely(v)) {
      stat_con_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_dex_mod();
    if (unlikely(v)) {
      stat_dex_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_luck_mod();
    if (unlikely(v)) {
      stat_luck_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->move_speed_mod();
    if (unlikely(v)) {
      move_speed_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->shove_strength_mod();
    if (unlikely(v)) {
      shove_strength_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->jump_distance_mod();
    if (unlikely(v)) {
      jump_distance_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_att_mod();
    if (unlikely(v)) {
      stat_att_mod_set(v);
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
    auto v = tpp->stat_str_mod();
    if (unlikely(v)) {
      stat_str_mod_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_att_mod();
    if (unlikely(v)) {
      stat_att_mod_set(v);
    }
  }

  if (has_temperature()) {
    TRACE_NO_INDENT();
    auto v = tpp->temperature();
    if (unlikely(v)) {
      temperature_set(v);
    }
  }

  //
  // Allow polymorph to change noise
  //
  {
    TRACE_NO_INDENT();
    auto v = tpp->noise_on_moving();
    if (unlikely(v)) {
      noise_set(v);
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
    auto v = tpp->stat_str();
    if (unlikely(v)) {
      stat_str_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_att();
    if (unlikely(v)) {
      stat_att_set(v);
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
    if (is_gfx_pixelart_animated || is_gfx_ascii_animated) {
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

  //
  // Auto carry of weapons?
  //
  if (is_able_to_use_weapons()) {
    dbg("Is weapon equipper");
    TRACE_AND_INDENT();

    if (is_carrier_of_weapon_class_a()) {
      auto W = level->thing_new(tp_random_weapon_class_a(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_weapon_class_b()) {
      auto W = level->thing_new(tp_random_weapon_class_b(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_weapon_class_c()) {
      auto W = level->thing_new(tp_random_weapon_class_c(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
  }

  if (is_able_to_use_wands_or_staffs()) {
    dbg("Is wand equipper");
    TRACE_AND_INDENT();

    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_wand_or_staff_class_a(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_wand_or_staff_class_b(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_wand_or_staff_class_c(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
  }

  if (is_able_to_use_rings()) {
    dbg("Is ring equipper");
    TRACE_AND_INDENT();

    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_ring_class_a(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_ring_class_b(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_ring_class_c(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
  }

  if (is_bag_item_container()) {
    dbg("Is bag item container");
    TRACE_AND_INDENT();

    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_a(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_b(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_c(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
  } else if (is_item_carrier()) {
    dbg("Is item carrier");
    TRACE_AND_INDENT();

    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_item_class_a(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_item_class_b(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_item_class_c(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
  }

  //
  // Initial equp of weapons
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
  // Initial equp of wand
  //
  if (is_able_to_use_wands_or_staffs()) {
    dbg("Wand equip");
    TRACE_AND_INDENT();

    Thingp best_wand = nullptr;
    carried_wand_highest_value(&best_wand);
    if (best_wand) {
      equip(best_wand, MONST_EQUIP_WEAPON);
    }
  }

  //
  // Initial equp of rings
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

  TRACE_NO_INDENT();
  hunger_update();

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
