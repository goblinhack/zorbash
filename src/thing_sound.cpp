//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"

bool Thing::thing_sound_play(const std::string &alias)
{
  TRACE_NO_INDENT();

  if (g_opt_silent) {
    return true;
  }

  //
  // No sound if in a locked room
  //
  auto level = game->get_current_level();
  if (! level) {
    return false;
  }
  auto player = level->player;
  if (! player) {
    return false;
  }
  //
  // Avoid initial equip sounds
  //
  if (! game->player_is_ready_for_messages) {
    return false;
  }

  int distance = distance_to_player();
  if (distance >= DMAP_IS_PASSABLE) {
    return true;
  }

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game->config.sound_volume) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  // con("SOUND %s dist %d", alias.c_str(), distance);

  //
  // Dampen sounds according to distance.
  //
  auto my_owner = top_owner();
  if (my_owner && my_owner->is_player()) {
    //
    // Full volume for player events; else if we fire a fireball far away we will hear nothing
    //
  } else {
    if (distance == DMAP_IS_WALL) {
      volume /= 2;
      // con("  - vol(a) %f", volume);
    } else {
      volume -= (distance * distance);
      // con("  - vol(b) %f", volume);
    }

    if (! get(player->aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
      volume /= 2;
      // con("  - vol(c) %f", volume);
    }
  }

  if (volume <= 0) {
    return true;
  }

  Mix_VolumeChunk(sound->second->chunk, volume);

  if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
    dbg2("Cannot play sound %s on any channel", alias.c_str());
    Mix_HaltChannel(0);
    SDL_ClearError();

    if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
      dbg2("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
      SDL_ClearError();
      return false;
    }
  }

  dbg2("Played sound %s on any channel volume %f distance %d", alias.c_str(), volume, distance);
  return true;
}

bool Thing::thing_sound_play_channel(int channel, const std::string &alias)
{
  TRACE_NO_INDENT();

  if (g_opt_silent) {
    return true;
  }

  auto level = game->get_current_level();
  if (! level) {
    return false;
  }
  auto player = level->player;
  if (! player) {
    return false;
  }
  //
  // Avoid initial equip sounds
  //
  if (! game->player_is_ready_for_messages) {
    return false;
  }

  int distance = distance_to_player();
  if (distance == DMAP_IS_WALL) {
    if (level->is_obs_wall_or_door(curr_at.x, curr_at.y)) {
      //
      // Ok to hit walls or doors.
      //
      if (! level->can_see_unimpeded(player->curr_at, curr_at)) {
        //
        // Only if we can see the wall or door
        //
        return false;
      }
    } else {
      //
      // Likely far away
      //
      IF_DEBUG2 { LOG("Cannot play sound %s on channel %d, cannot reach target", alias.c_str(), channel); }
      return true;
    }
  } else if (distance >= DMAP_IS_PASSABLE) {
    IF_DEBUG2 { LOG("Cannot play sound %s on channel %d, too far", alias.c_str(), channel); }
    return true;
  }

  // con("SOUND %s dist %d", alias.c_str(), distance);

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game->config.sound_volume) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  //
  // Dampen sounds according to distance.
  //
  auto my_owner = top_owner();
  if (my_owner && my_owner->is_player()) {
    //
    // Full volume for player events; else if we fire a fireball far away we will hear nothing
    //
  } else {
    if (distance == DMAP_IS_WALL) {
      volume /= 2;
      // con("  - vol(a) %f", volume);
    } else {
      volume -= (distance * distance);
      // con("  - vol(b) %f", volume);
    }

    if (! get(player->aip()->can_see_currently.can_see, curr_at.x, curr_at.y)) {
      volume /= 2;
      // con("  - vol(c) %f", volume);
    }
  }

  if (volume <= 0) {
    return true;
  }

  // con("  - vol(final) %f", volume);

  Mix_VolumeChunk(sound->second->chunk, volume);

  if (Mix_Playing(channel)) {
    if (Mix_PlayChannel(-1, sound->second->chunk, 0 /* loops */) == -1) {
      dbg2("Cannot play sound %s on any channel, originally %d, something else playing", alias.c_str(), channel);
      return false;
    } else {
      dbg2("Played sound %s on any channel volume %f distance %d", alias.c_str(), volume, distance);
      return true;
    }
  } else if (Mix_PlayChannel(channel, sound->second->chunk, 0 /* loops */) == -1) {
    dbg2("Cannot play sound %s on channel %d", alias.c_str(), channel);
    return false;
  }

  dbg2("Played sound %s on channel %d volume %f distance %d", alias.c_str(), channel, volume, distance);
  return true;
}
