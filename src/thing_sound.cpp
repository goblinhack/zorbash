//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_game.hpp"
#include "my_sound.hpp"
#include "my_thing.hpp"
#include <SDL_mixer.h>

bool Thing::thing_sound_play(const std::string &alias)
{
  TRACE_NO_INDENT();
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

  int distance = distance_to_player();
  if (distance >= DMAP_IS_PASSABLE) {
    return true;
  }

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * ((float) game->config.sound_volume / (float) MIX_MAX_VOLUME);

  volume *= MIX_MAX_VOLUME;

  volume -= distance;
  if (volume <= 0) {
    return true;
  }

  Mix_VolumeChunk(sound->second->chunk, volume);

  if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {

    LOG("Cannot play sound %s on any channel", alias.c_str());
    Mix_HaltChannel(0);
    SDL_ClearError();

    if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
      ERR("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
      SDL_ClearError();
    }
  }

  return true;
}

bool Thing::thing_sound_play_channel(int channel, const std::string &alias)
{
  TRACE_NO_INDENT();
  auto level = game->get_current_level();
  if (! level) {
    return false;
  }
  auto player = level->player;
  if (! player) {
    return false;
  }

  int distance = distance_to_player();
  if (distance == DMAP_IS_WALL) {
    if (level->is_obs_wall_or_door(curr_at.x, curr_at.y)) {
      //
      // Ok to hit walls or doors.
      //
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

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * ((float) game->config.sound_volume / (float) MIX_MAX_VOLUME);

  volume *= MIX_MAX_VOLUME;

  if (distance == DMAP_IS_WALL) {
    volume /= 2;
  } else {
    volume -= distance;
  }

  if (volume <= 0) {
    return true;
  }

  Mix_VolumeChunk(sound->second->chunk, volume);

  if (Mix_Playing(channel)) {
    if (Mix_PlayChannel(-1, sound->second->chunk, 0 /* loops */) == -1) {
      dbg2("Cannot play sound %s on channel %d, something else playing", alias.c_str(), channel);
      return false;
    }
  } else if (Mix_PlayChannel(channel, sound->second->chunk, 0 /* loops */) == -1) {
    dbg2("Cannot play sound %s on channel %d", alias.c_str(), channel);
    return false;
  }

  dbg2("Play sound %s on channel %d volume %f distance %d", alias.c_str(), channel, volume, distance);

  return true;
}
