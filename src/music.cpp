/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_main.h"
#include "my_music.h"
#include "my_ptrcheck.h"
#include "my_ramdisk.h"
#include "my_game.h"

class music {
public:
    music (std::string name_alias) : name_alias(name_alias)
    {
    }

    ~music (void)
    {
        Mix_FreeMusic(m);
        myfree(data);
    }

    std::string name_alias;
    Mix_Music *m = {};
    unsigned char *data = {};
    int32_t len = {};
};

static std::map<std::string, std::shared_ptr< class music > > all_music;

static std::string music_current;

uint8_t music_init_done;

uint8_t music_init (void)
{_
    return (true);
}

void music_fini (void)
{_
    if (music_init_done) {
        music_init_done = false;

        auto iter = all_music.begin();

        while (iter != all_music.end()) {
            iter = all_music.erase(iter);
        }
    }

    Mix_CloseAudio();
}

bool music_load (const std::string &file, const std::string &name_alias)
{_
    if (name_alias == "") {
        auto m = music_find(name_alias);
        if (m) {
            return (true);
        }
    }

    auto m = std::make_shared< class music >(name_alias);

    auto result = all_music.insert(std::make_pair(name_alias, m));

    if (result.second == false) {
        ERR("Cannot insert music name [%s] failed", name_alias.c_str());
        return false;
    }

    m->data = file_load(file.c_str(), &m->len);
    if (!m->data) {
        ERR("Cannot load music %s", file.c_str());
        return false;
    }

    SDL_RWops *rw;

    rw = SDL_RWFromMem(m->data, m->len);
    if (!rw) {
        ERR("SDL_RWFromMem fail %s: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
        SDL_ClearError();
        return false;
    }

    m->m = Mix_LoadMUS_RW(rw, false);
    if (!m->m) {
        ERR("Mix_LoadMUS_RW fail %s: %s %s", file.c_str(), Mix_GetError(), SDL_GetError());
        SDL_ClearError();
        return false;
    }

    DBG("Load %s", file.c_str());

    return (true);
}

/*
 * Find an existing pice of music.
 */
bool music_find (const std::string &name_alias)
{_
    auto result = all_music.find(name_alias);
    return result != all_music.end();
}

void music_update_volume (void)
{_
    Mix_VolumeMusic(game->config.music_volume);
    SDL_ClearError();
}

bool music_play (const std::string &file, const std::string &alias, uint32_t rate)
{_
    if (file == music_current) {
        return true;
    }
    music_current = file;

    int audio_format = MIX_DEFAULT_FORMAT;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if (!music_init_done) {
        if (Mix_OpenAudio(rate,
                          audio_format,
                          audio_channels,
                          audio_buffers) != 0) {

            ERR("Mix_OpenAudio fail: %s %s", Mix_GetError(), SDL_GetError());
            SDL_ClearError();
            return false;
        }

        music_init_done = true;
    }

    if (!music_load(file, alias)) {
        return false;
    }

    music_update_volume();

#if 0
    static int sound_loaded;
    if (!sound_loaded) {
        sound_loaded = true;
        sound_load_all();
    }
#endif
    auto music = all_music.find(alias);

    if (Mix_FadeInMusicPos(music->second->m, -1, 2000, 0) == -1) {
        ERR("Cannot play music %s: %s", alias.c_str(), Mix_GetError());
        SDL_ClearError();
    }

    return true;
}

#if 0
void music_play_game (uint32_t level_no)
{_
    static std::string music[] = {
        "data/music/Faith.ogg",
    };

    /*
     * So we get the same music for each player on the same level.
     */
    int r = level_no;
    int x = r % ARRAY_SIZE(music);

    music_play(music[x], music[x], 44100);
}

void music_play_death (void)
{_
    music_play("data/music/Faith.ogg", "death", 44100 );
}

void music_play_demo (void)
{_
    music_play("data/music/Faith.ogg", "battle", 44100 );
}

void music_play_dead (void)
{_
    music_play("data/music/Faith.ogg", "dead", 44100 );
}

void music_play_game_over (void)
{_
    music_play("data/music/Faith.ogg", "game over", 44100 );
}
#endif

void music_play_intro (void)
{_
    music_play("data/music/DST-PhaserSwitch.mp3", "intro", 44100 );
}

void music_halt (void)
{_
    music_current = "";

    Mix_FadeOutMusic(1500);
}
