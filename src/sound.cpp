/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_main.h"
#include "my_sound.h"
#include "my_ptrcheck.h"
#include "my_file.h"
#include "my_game.h"

class sound {
public:
    sound (std::string name_alias) : name_alias(name_alias)
    {
    }

    ~sound (void)
    {
#if 0
        Mix_FreeMusic(m);
#endif
        myfree(data);
    }

    std::string name_alias;
    Mix_Music *m = {};
    unsigned char *data = {};
    int32_t len = {};
};

static std::map<std::string, std::shared_ptr< class sound > > all_sound;

static std::string sound_current;

uint8_t sound_init_done;

uint8_t sound_init (void)
{_
    return (true);
}

void sound_fini (void)
{_
    if (sound_init_done) {
        sound_init_done = false;

        auto iter = all_sound.begin();

        while (iter != all_sound.end()) {
            iter = all_sound.erase(iter);
        }
    }

    Mix_CloseAudio();
}

bool sound_load (const std::string &file, const std::string &name_alias)
{_
    if (name_alias == "") {
        auto m = sound_find(name_alias);
        if (m) {
            return (true);
        }
    }

    auto m = std::make_shared< class sound >(name_alias);

    auto result = all_sound.insert(std::make_pair(name_alias, m));

    if (result.second == false) {
        ERR("Cannot insert sound name [%s] failed", name_alias.c_str());
        return false;
    }

    m->data = file_load(file.c_str(), &m->len);
    if (!m->data) {
        ERR("Cannot load sound %s", file.c_str());
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
 * Find an existing pice of sound.
 */
bool sound_find (const std::string &name_alias)
{_
    auto result = all_sound.find(name_alias);
    return result != all_sound.end();
}

void sound_update_volume (void)
{_
    Mix_VolumeMusic(game->config.sound_volume);
    SDL_ClearError();
}

bool sound_play (const std::string &file, const std::string &alias, uint32_t rate)
{_
    if (file == sound_current) {
        return true;
    }
    sound_current = file;

    int audio_format = MIX_DEFAULT_FORMAT;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if (!sound_init_done) {
        if (Mix_OpenAudio(rate,
                          audio_format,
                          audio_channels,
                          audio_buffers) != 0) {

            ERR("Mix_OpenAudio fail: %s %s", Mix_GetError(), SDL_GetError());
            SDL_ClearError();
            return false;
        }

        sound_init_done = true;
    }

    if (!sound_load(file, alias)) {
        return false;
    }

    sound_update_volume();

#if 0
    static int sound_loaded;
    if (!sound_loaded) {
        sound_loaded = true;
        sound_load_all();
    }
#endif

#if 0
    auto sound = all_sound.find(alias);

    if (Mix_FadeInMusicPos(sound->second->m, -1, 2000, 0) == -1) {
        ERR("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
        SDL_ClearError();
    }
#endif

    return true;
}

#if 0
void sound_play_game (uint32_t level_no)
{_
    static std::string sound[] = {
        "data/sound/Faith.ogg",
    };

    /*
     * So we get the same sound for each player on the same level.
     */
    int r = level_no;
    int x = r % ARRAY_SIZE(sound);

    sound_play(sound[x], sound[x], 44100);
}

void sound_play_death (void)
{_
    sound_play("data/sound/Faith.ogg", "death", 44100 );
}

void sound_play_demo (void)
{_
    sound_play("data/sound/Faith.ogg", "battle", 44100 );
}

void sound_play_dead (void)
{_
    sound_play("data/sound/Faith.ogg", "dead", 44100 );
}

void sound_play_game_over (void)
{_
    sound_play("data/sound/Faith.ogg", "game over", 44100 );
}

void sound_play_intro (void)
{_
    sound_play("data/sound/DST-PhaserSwitch.mp3", "intro", 44100 );
}
#endif

void sound_halt (void)
{_
    sound_current = "";

#if 0
    Mix_FadeOutMusic(1500);
#endif
}
