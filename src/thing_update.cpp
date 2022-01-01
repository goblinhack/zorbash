//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_level.hpp"
#include "my_light.hpp"
#include "my_monst.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
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

  size_t c = 0;
  for (auto l : get_light()) {
    l->cached_light_pos = point(-1, -1);
    c++;
  }
}

void Thing::update(void)
{
  TRACE_NO_INDENT();
  if (is_loggable()) {
    dbg("Update");
  }
  TRACE_AND_INDENT();

  auto tpp     = tp();
  int  carried = 0;

  {
    TRACE_NO_INDENT();
    auto v = tpp->get_health_initial();
    if (unlikely(v)) {
      set_health(v);
      set_health_max(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stamina();
    if (unlikely(v)) {
      set_stamina(v);
      set_stamina_max(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->enchant_level();
    if (unlikely(v)) {
      set_enchant(v);
      set_enchant_max(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->enchant_max();
    if (unlikely(v)) {
      set_enchant_max(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->armor_class();
    if (unlikely(v)) {
      set_armor_class(v);
      set_stats19(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->lifespan();
    if (unlikely(v)) {
      set_lifespan(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->dexterity();
    if (unlikely(v)) {
      set_stat_dexterity(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats02();
    if (unlikely(v)) {
      set_stats02(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats03();
    if (unlikely(v)) {
      set_stats03(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats04();
    if (unlikely(v)) {
      set_stats04(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats05();
    if (unlikely(v)) {
      set_stats05(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats06();
    if (unlikely(v)) {
      set_stats06(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats07();
    if (unlikely(v)) {
      set_stats07(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats08();
    if (unlikely(v)) {
      set_stats08(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats09();
    if (unlikely(v)) {
      set_stats09(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats10();
    if (unlikely(v)) {
      set_stats10(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats11();
    if (unlikely(v)) {
      set_stats11(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats12();
    if (unlikely(v)) {
      set_stats12(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->constitution();
    if (unlikely(v)) {
      set_stat_constitution(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->attack_bonus();
    if (unlikely(v)) {
      set_attack_bonus(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->constitution();
    if (unlikely(v)) {
      set_stat_constitution(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stats17();
    if (unlikely(v)) {
      set_stats17(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->distance_throw();
    if (unlikely(v)) {
      set_distance_throw(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->strength();
    if (unlikely(v)) {
      set_stat_strength(v);
    }
  }

  if (unlikely(tpp->charge_count())) {
    set_charge_count(tpp->charge_count());
  }

  auto tiles = &tpp->tiles;
  if (tpp->gfx_animated()) {
    auto tile = tile_first(tiles);
    if (tile) {
      tile_curr = tile->global_index;
    } else {
      tile_curr = 0;
    }
  } else {
    auto tile = tile_random(tiles);
    if (tile) {
      tile_curr = tile->global_index;
    } else {
      tile_curr = 0;
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

  if (is_able_to_use_wands()) {
    dbg("Is wand equipper");
    TRACE_AND_INDENT();

    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_wand_class_a(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_wand_class_b(), curr_at, this);
      if (W) {
        carried += carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_wand_class_c(), curr_at, this);
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
    get_carried_weapon_highest_value(&best_weapon);
    if (best_weapon) {
      equip(best_weapon, MONST_EQUIP_WEAPON);
    }
  }

  //
  // Initial equp of armor
  //
  if (is_able_to_use_armor()) {
    dbg("Weapon equip");
    TRACE_AND_INDENT();

    Thingp best_armor = nullptr;
    get_carried_armor_highest_value(&best_armor);
    if (best_armor) {
      equip(best_armor, MONST_EQUIP_ARMOR);
    }
  }

  //
  // Initial equp of wand
  //
  if (is_able_to_use_wands()) {
    dbg("Wand equip");
    TRACE_AND_INDENT();

    Thingp best_wand = nullptr;
    get_carried_wand_highest_value(&best_wand);
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
      get_carried_ring_highest_value(&best_ring);
      if (best_ring) {
        equip(best_ring, MONST_EQUIP_RING1);
      }
    }
    //
    // Ring 2
    //
    {
      Thingp best_ring = nullptr;
      get_carried_ring_highest_value(&best_ring);
      if (best_ring) {
        equip(best_ring, MONST_EQUIP_RING2);
      }
    }
  }

  hunger_update();

  if (carried && (is_monst() || is_player())) {
    dbg("Final item list:");
    TRACE_AND_INDENT();
    check_all_carried_items_are_owned();
  }
}
