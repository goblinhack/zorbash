//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_file.hpp"
#include "my_game.hpp"
// REMOVED #include "my_main.hpp"
#include "my_music.hpp"
#include "my_ptrcheck.hpp"
// REMOVED #include "my_sys.hpp"
#include <SDL_mixer.h>

class music
{
public:
  music(std::string name_alias) : name_alias(name_alias) {}

  ~music(void)
  {
    Mix_FreeMusic(m);
    myfree(data);
  }

  std::string    name_alias;
  Mix_Music     *m    = {};
  unsigned char *data = {};
  int            len  = {};
  uint32_t       rate = 44100;
};

static std::map< std::string, class music * > all_music;

static std::string music_current;

bool music_init_done;

bool music_init(void)
{
  TRACE_AND_INDENT();
  //
  // MP3 is a pain to use, use OGG instead
  // int flags = MIX_INIT_OGG|MIX_INIT_MP3;
  //
  int flags   = MIX_INIT_OGG;
  int initted = Mix_Init(flags);
  if ((initted & flags) != flags) {
    ERR("Mix_Init: Failed to init required OGG support");
  }

  music_init_done = true;
  return true;
}

void music_fini(void)
{
  TRACE_AND_INDENT();
  if (music_init_done) {
    music_init_done = false;

    auto iter = all_music.begin();

    while (iter != all_music.end()) {
      delete iter->second;
      iter = all_music.erase(iter);
    }

    Mix_Quit();
  }
}

bool music_load(uint32_t rate, const std::string &file, const std::string &name_alias)
{
  TRACE_AND_INDENT();
  if (name_alias == "") {
    auto m = music_find(name_alias);
    if (m) {
      return true;
    }
  }

  auto *m = new music(name_alias);

  m->rate = rate;
  m->data = file_load(file.c_str(), &m->len);
  if (! m->data) {
    DIE("Cannot load music [%s]", file.c_str());
    return false;
  }

  SDL_RWops *rw;

  rw = SDL_RWFromMem(m->data, m->len);
  if (! rw) {
    ERR("SDL_RWFromMem fail [%s]: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
    SDL_ClearError();
    return false;
  }

  m->m = Mix_LoadMUS_RW(rw, false);
  if (! m->m) {
    ERR("Mix_LoadMUS_RW fail [%s]: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
    SDL_ClearError();
    return false;
  }

  auto result = all_music.insert(std::make_pair(name_alias, m));
  if (! result.second) {
    ERR("Cannot insert music name [%s] failed", name_alias.c_str());
    return false;
  }

  // DBG("Load %s", file.c_str());

  return true;
}

/*
 * Find an existing pice of music.
 */
bool music_find(const std::string &name_alias)
{
  TRACE_AND_INDENT();
  auto result = all_music.find(name_alias);
  return result != all_music.end();
}

void music_update_volume(void)
{
  TRACE_AND_INDENT();
  Mix_VolumeMusic(game->config.music_volume);
  SDL_ClearError();
}

bool music_play(const std::string &name)
{
  TRACE_AND_INDENT();
  if (name == music_current) {
    return true;
  }
  music_current = name;

  music_update_volume();

  auto music = all_music.find(name);
  if (music == all_music.end()) {
    DIE("Cannot find music %s: %s", name.c_str(), Mix_GetError());
    SDL_ClearError();
    return false;
  }

  if (Mix_FadeInMusicPos(music->second->m, -1, 2000, 0) == -1) {
    ERR("Cannot play music %s: %s", name.c_str(), Mix_GetError());
    SDL_ClearError();
    return false;
  }

  return true;
}

bool music_halt(void)
{
  TRACE_AND_INDENT();
  music_current = "";

  Mix_FadeOutMusic(1500);
  return true;
}
