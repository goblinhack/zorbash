//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_ptrcheck.hpp"

Level::Level(void)
{
  TRACE_NO_INDENT();
  newptr(MTYPE_LEVEL, this, "level");
}

void Level::clear(void)
{
  TRACE_NO_INDENT();
  _fade_in_map                       = {};
  _gfx_water                         = {};
  _heatmap                           = {};
  _is_able_to_dampen_footsteps       = {};
  _is_able_to_amplify_footsteps      = {};
  _is_attackable_by_monst            = {};
  _is_attackable_by_player           = {};
  _is_able_to_stand_on               = {};
  _is_acid                           = {};
  _is_ascend_dungeon                 = {};
  _is_ascend_sewer                   = {};
  _is_basalt                         = {};
  _is_block_of_ice                   = {};
  _is_bridge                         = {};
  _is_carnivorous_plant              = {};
  _is_chasm                          = {};
  _is_corpse                         = {};
  _is_corridor                       = {};
  _is_currently_pixelart_raycast_lit = {};
  _is_deep_water                     = {};
  _is_descend_dungeon                = {};
  _is_descend_sewer                  = {};
  _is_dirt                           = {};
  _is_door                           = {};
  _is_dry_grass                      = {};
  _is_enchantstone                   = {};
  _is_fire                           = {};
  _is_floor                          = {};
  _is_foliage                        = {};
  _is_food                           = {};
  _is_gas_blocker                    = {};
  _is_gas_poison                     = {};
  _is_gold                           = {};
  _is_green_blood                    = {};
  _is_lava                           = {};
  _is_light_blocker                  = {};
  _is_light_blocker_for_monst        = {};
  _is_walked                         = {};
  _is_monst                          = {};
  _is_obs_destructable               = {};
  _is_obs_for_jump_landing           = {};
  _is_obs_wall_or_door               = {};
  _is_obs_when_dead                  = {};
  _is_portal                         = {};
  _is_red_blood                      = {};
  _is_rock                           = {};
  _is_shallow_water                  = {};
  _is_shovable                       = {};
  _is_skillstone                     = {};
  _is_smoke                          = {};
  _is_spiderweb                      = {};
  _is_steam                          = {};
  _is_sticky                         = {};
  _is_treasure_type                  = {};
  _is_wall                           = {};
  _is_wet_grass                      = {};
  _noise_blocker                     = {};
  _noisemap                          = {};
  _noisemap_in                       = {};

  can_see_currently = {};
  can_see_ever      = {};

  ts_created = time_ms();
  ts_entered = ts_created;
  ts_saved   = 0;

  tick_created = game->tick_current;
}
