//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_color.hpp"
#include "my_depth.hpp"
#include "my_dmap.hpp"
#include "my_level.hpp"
#include "my_light.hpp"
#include "my_sprintf.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"

void Thing::update_light(void)
{
  TRACE_AND_INDENT();
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
  auto tpp = tp();

  {
    TRACE_AND_INDENT();
    auto v = tpp->get_health_initial();
    if (unlikely(v)) {
      set_health(v);
      set_health_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stamina();
    if (unlikely(v)) {
      set_stamina(v);
      set_stamina_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->enchant_level();
    if (unlikely(v)) {
      set_enchant(v);
      set_enchant_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->enchant_max();
    if (unlikely(v)) {
      set_enchant_max(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_armor_class();
    if (unlikely(v)) {
      set_stat_armor_class(v);
      set_stats19(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->lifespan();
    if (unlikely(v)) {
      set_lifespan(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_dexterity();
    if (unlikely(v)) {
      set_stat_dexterity(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats02();
    if (unlikely(v)) {
      set_stats02(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats03();
    if (unlikely(v)) {
      set_stats03(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats04();
    if (unlikely(v)) {
      set_stats04(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats05();
    if (unlikely(v)) {
      set_stats05(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats06();
    if (unlikely(v)) {
      set_stats06(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats07();
    if (unlikely(v)) {
      set_stats07(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats08();
    if (unlikely(v)) {
      set_stats08(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats09();
    if (unlikely(v)) {
      set_stats09(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats10();
    if (unlikely(v)) {
      set_stats10(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats11();
    if (unlikely(v)) {
      set_stats11(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats12();
    if (unlikely(v)) {
      set_stats12(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_constitution();
    if (unlikely(v)) {
      set_stat_constitution(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_attack_bonus();
    if (unlikely(v)) {
      set_stat_attack_bonus(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_constitution();
    if (unlikely(v)) {
      set_stat_constitution(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stats17();
    if (unlikely(v)) {
      set_stats17(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->distance_throw();
    if (unlikely(v)) {
      set_distance_throw(v);
    }
  }

  {
    TRACE_AND_INDENT();
    auto v = tpp->stat_strength();
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
  if (is_weapon_equiper()) {
    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_weapon_class_a(), curr_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_weapon_class_b(), curr_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_weapon_class_c(), curr_at);
      if (W) {
        carry(W);
      }
    }
  }

  if (is_bag_item_container()) {
    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_a(), curr_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_b(), curr_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_item_not_a_container_class_c(), curr_at);
      if (W) {
        carry(W);
      }
    }
  } else if (is_item_carrier()) {
    if (is_carrier_of_treasure_class_a()) {
      auto W = level->thing_new(tp_random_item_class_a(), curr_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_b()) {
      auto W = level->thing_new(tp_random_item_class_b(), curr_at);
      if (W) {
        carry(W);
      }
    }
    if (is_carrier_of_treasure_class_c()) {
      auto W = level->thing_new(tp_random_item_class_c(), curr_at);
      if (W) {
        carry(W);
      }
    }
  }
}
