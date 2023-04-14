//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_biomes.hpp"
#include "my_callstack.hpp"
#include "my_color_defs.hpp"
#include "my_globals.hpp"
#include "my_main.hpp"
#include "my_ui.hpp"

biome_t get_biome(point3d world_at, int difficulty_depth)
{
  TRACE_AND_INDENT();

  //
  // Choose the biome for the level
  //
  auto biome = get_biome(difficulty_depth);

  //
  // Sewers are in alternate z depths
  //
  if (! (world_at.z & 1)) {
    biome = BIOME_SEWER;
  }

  return biome;
}

biome_t get_biome(int difficulty_depth)
{
  TRACE_AND_INDENT();

  biome_t biome = BIOME_DUNGEON;

  switch (difficulty_depth) {
    case 0: biome = BIOME_DUNGEON; break;
    case 1: biome = BIOME_SWAMP; break;
    case 2: biome = BIOME_CHASMS; break;
    case 3:
      biome = BIOME_ICE;
      biome = BIOME_DUNGEON; // HACK
      break;
    case 4: biome = BIOME_DUNGEON; break;
    case 5:
      biome = BIOME_LAVA;
      biome = BIOME_DUNGEON; // HACK
      break;
    case 6: biome = BIOME_DUNGEON; break;
    case 7: biome = BIOME_DUNGEON; break;
    default: biome = BIOME_DUNGEON; break;
  }

  if (g_opt_biome_swamp) {
    biome = BIOME_SWAMP;
  }

  if (g_opt_biome_ice) {
    biome = BIOME_ICE;
  }

  if (g_opt_biome_chasms) {
    biome = BIOME_CHASMS;
  }

  if (g_opt_biome_lava) {
    biome = BIOME_LAVA;
  }

  return biome;
}

std::string biome_to_string(biome_t biome)
{
  TRACE_AND_INDENT();

  switch (biome) {
    case BIOME_UNKNOWN: return "Unknown";
    case BIOME_DUNGEON: return "Dungeon";
    case BIOME_SWAMP: return "Swamp";
    case BIOME_SEWER: return "Sewer";
    case BIOME_ICE: return "Ice";
    case BIOME_CHASMS: return "Chasms";
    case BIOME_LAVA: return "Lava";
    case BIOME_DUNGEONS: return "Dungeons";
    case BIOME_MAX: DIE("unxpected enum");
  }
  return "Unknown";
}

color get_biome_color(biome_t biome)
{
  TRACE_AND_INDENT();

  switch (biome) {
    case BIOME_UNKNOWN: return BIOME_DUNGEON_COLOR;
    case BIOME_DUNGEON: return BIOME_DUNGEON_COLOR;
    case BIOME_SWAMP: return BIOME_SWAMP_COLOR;
    case BIOME_SEWER: return BIOME_SEWER_COLOR;
    case BIOME_ICE: return BIOME_ICE_COLOR;
    case BIOME_CHASMS: return BIOME_CHASMS_COLOR;
    case BIOME_LAVA: return BIOME_LAVA_COLOR;
    case BIOME_DUNGEONS: return BIOME_DUNGEON_COLOR;
    case BIOME_MAX: DIE("unxpected enum");
  }
  return BIOME_DUNGEON_COLOR;
}

color get_difficulty_depth_color(int difficulty_depth)
{
  TRACE_AND_INDENT();

  return get_biome_color(get_biome(difficulty_depth));
}
