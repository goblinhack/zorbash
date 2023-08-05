//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_file.hpp"
#include "my_game.hpp"
#include "my_sound.hpp"

std::map< std::string, class sound * > all_sound;

bool sound_init_done;

bool sound_init(void)
{
  TRACE_AND_INDENT();
  Mix_AllocateChannels(16);

  sound_init_done = true;

  return true;
}

void sound_fini(void)
{
  TRACE_AND_INDENT();
  if (sound_init_done) {
    sound_init_done = false;

    for (;;) {
      auto iter = all_sound.begin();
      if (iter == all_sound.end()) {
        break;
      }
      delete iter->second;
      iter = all_sound.erase(iter);
    }

    Mix_Quit();
  }
}

bool sound_load(float volume, const char *file_in, const char *alias_in)
{
  TRACE_AND_INDENT();
  auto file  = std::string(file_in);
  auto alias = std::string(alias_in);

  return sound_load(volume, file, alias);
}

bool sound_load(float volume, const std::string &file, const std::string &alias)
{
  TRACE_AND_INDENT();
  if (alias == "") {
    auto s = sound_find(alias);
    if (s) {
      return true;
    }
  }

  auto *s = new sound(alias);

  s->volume = volume;
  s->data   = file_load(file.c_str(), &s->len);
  if (! s->data) {
    ERR("Cannot load sound [%s]", file.c_str());
    delete s;
    return false;
  }

  SDL_RWops *rw;

  rw = SDL_RWFromMem(s->data, s->len);
  if (! rw) {
    ERR("SDL_RWFromMem fail [%s]: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
    SDL_ClearError();
    delete s;
    return false;
  }

  s->chunk = Mix_LoadWAV_RW(rw, false /* A non-zero value mean is will automatically close/free the src for you. */);
  if (! s->chunk) {
    ERR("Mix_LoadWAV_RW fail [%s]: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
    SDL_ClearError();
    delete s;
    return false;
  }

  auto result = all_sound.insert(std::make_pair(alias, s));
  if (! result.second) {
    ERR("Cannot insert sound name [%s] failed", alias.c_str());
    delete s;
    return false;
  }

  // DBG("Load %s", file.c_str());

  return true;
}

//
// Find an existing pice of sound.
//
bool sound_find(const std::string &alias)
{
  TRACE_AND_INDENT();
  auto result = all_sound.find(alias);
  return result != all_sound.end();
}

bool sound_play(const std::string &alias)
{
  TRACE_AND_INDENT();

  if (g_opt_silent) {
    return true;
  }

  DBG2("Play sound %s", alias.c_str());

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  if (! sound->second) {
    ERR("Cannot find sound data %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game->config.sound_volume) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  if (! sound->second->chunk) {
    ERR("Cannot find sound chunk %s", alias.c_str());
    return false;
  }

  Mix_VolumeChunk(sound->second->chunk, volume);

  if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
    DBG2("Cannot play sound %s on any channel", alias.c_str());
    Mix_HaltChannel(0);
    SDL_ClearError();

    if (Mix_PlayChannel(-1 /* first free channel */, sound->second->chunk, 0 /* loops */) == -1) {
      ERR("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
      SDL_ClearError();
    }
  }

  return true;
}

bool sound_play_channel(int channel, const std::string &alias)
{
  TRACE_AND_INDENT();

  if (g_opt_silent) {
    return true;
  }

  DBG2("Play sound %s on channel %d", alias.c_str(), channel);

  auto sound = all_sound.find(alias);
  if (sound == all_sound.end()) {
    ERR("Cannot find sound %s", alias.c_str());
    return false;
  }

  if (! sound->second) {
    ERR("Cannot find sound data %s", alias.c_str());
    return false;
  }

  float volume = sound->second->volume * (((float) game->config.sound_volume) / ((float) MIX_MAX_VOLUME));

  volume *= MIX_MAX_VOLUME;

  Mix_VolumeChunk(sound->second->chunk, volume);

  if (Mix_Playing(channel)) {
    if (Mix_PlayChannel(-1, sound->second->chunk, 0 /* loops */) == -1) {
      DBG2("Cannot play sound %s on channel %d", alias.c_str(), channel);
      return false;
    }
    return true;
  }

  if (! sound->second->chunk) {
    ERR("Cannot find sound chunk %s", alias.c_str());
    return false;
  }

  if (Mix_PlayChannel(channel, sound->second->chunk, 0 /* loops */) == -1) {
    if (Mix_PlayChannel(-1, sound->second->chunk, 0 /* loops */) == -1) {
      DBG2("Cannot play sound %s on channel %d", alias.c_str(), channel);
      return false;
    }
  }

  return true;
}

void sound_halt(void) { TRACE_AND_INDENT(); }
