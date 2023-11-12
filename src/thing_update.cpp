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

  auto tpp = tp();

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
    auto v = tpp->distance_spell_cast();
    if (unlikely(v)) {
      distance_spell_cast_set(v);
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
    auto v = tpp->stat_thv_bonus();
    if (unlikely(v)) {
      stat_thv_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_thv();
    if (unlikely(v)) {
      stat_thv_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_psi_bonus();
    if (unlikely(v)) {
      stat_psi_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_psi();
    if (unlikely(v)) {
      stat_psi_set(v);
    }
  }

  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_int_bonus();
    if (unlikely(v)) {
      stat_int_bonus_set(v);
    }
  }
  {
    TRACE_NO_INDENT();
    auto v = tpp->stat_int();
    if (unlikely(v)) {
      stat_int_set(v);
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

  //
  // Start out with immunities from the template. This can change with negation.
  //
  _is_immune_to_electricity         = tpp->is_immune_to_electricity();
  _is_immune_to_entrancement        = tpp->is_immune_to_entrancement();
  _is_immune_to_fire                = tpp->is_immune_to_fire();
  _is_immune_to_holy_damage         = tpp->is_immune_to_holy_damage();
  _is_immune_to_lightning           = tpp->is_immune_to_lightning();
  _is_immune_to_magic_drain         = tpp->is_immune_to_magic_drain();
  _is_immune_to_necrosis            = tpp->is_immune_to_necrosis();
  _is_immune_to_negation            = tpp->is_immune_to_negation();
  _is_immune_to_paralysis           = tpp->is_immune_to_paralysis();
  _is_immune_to_poison              = tpp->is_immune_to_poison();
  _is_immune_to_spell_of_beckoning  = tpp->is_immune_to_spell_of_beckoning();
  _is_immune_to_spell_of_holding    = tpp->is_immune_to_spell_of_holding();
  _is_immune_to_spell_of_repulsion  = tpp->is_immune_to_spell_of_repulsion();
  _is_immune_to_spell_of_sanctuary  = tpp->is_immune_to_spell_of_sanctuary();
  _is_immune_to_spell_of_slowness   = tpp->is_immune_to_spell_of_slowness();
  _is_immune_to_spiderwebs          = tpp->is_immune_to_spiderwebs();
  _is_immune_to_stamina_drain       = tpp->is_immune_to_stamina_drain();
  _is_immune_to_teleport_attack     = tpp->is_immune_to_teleport_attack();
  _is_immune_to_vorpal_weapons      = tpp->is_immune_to_vorpal_weapons();
  _is_immune_to_non_magical_weapons = tpp->is_immune_to_non_magical_weapons();
  _is_immune_to_water               = tpp->is_immune_to_water();
  _is_able_to_regenerate            = tpp->is_able_to_regenerate();

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

  //
  // Auto carry of weapons?
  //
  auto_equip();

  if (is_player()) {
    TRACE_NO_INDENT();
    level->request_player_light_update = true;
  }
}
