/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include <SDL_mixer.h>

#include "my_main.h"
#include "my_music.h"
#include "my_ramdisk.h"
#include "my_sound.h"
#include "my_config.h"

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

musicp music_load (std::string file, std::string name_alias)
{_
    if (name_alias == "") {
        musicp m = music_find(name_alias);
        if (m) {
            return (m);
        }
    }

    if (file == "") {
        if (name_alias == "") {
            ERR("no file for music");
        } else {
            ERR("no file for music loading %s", name_alias.c_str());
        }
    }

    auto m = std::make_shared< class music >(name_alias);

    auto result = all_music.insert(std::make_pair(name_alias, m));

    if (result.second == false) {
        DIE("music insert name [%s] failed", name_alias.c_str());
    }

    m->data = ramdisk_load(file.c_str(), &m->len);
    if (!m->data) {
        ERR("cannot load music %s", file.c_str());
    }

    SDL_RWops *rw;

    rw = SDL_RWFromMem(m->data, m->len);
    if (!rw) {
        ERR("cannot make RW music %s", file.c_str());
    }

#if SDL_MAJOR_VERSION == 1 && SDL_MINOR_VERSION == 2 /* { */
    m->m = Mix_LoadMUS_RW(rw);
#else
    m->m = Mix_LoadMUS_RW(rw, false);
#endif /* } */
    if (!m->m) {
        MSG_BOX("Mix_LoadMUS_RW fail %s: %s %s", file.c_str(), Mix_GetError(),
            SDL_GetError());
        SDL_ClearError();
    }

    DBG("Load %s", file.c_str());

    return (m);
}

/*
 * Find an existing pice of music.
 */
musicp music_find (std::string name_alias)
{_
    if (name_alias == "") {
        DIE("no filename given for font find %s", __FUNCTION__);
    }

    auto result = all_music.find(name_alias);
    if (result == all_music.end()) {
        return (0);
    }

    return (result->second);
}

void music_update_volume (void)
{_
    Mix_VolumeMusic((int)
                    (float) game.music_volume *
                    ((float) MIX_MAX_VOLUME / (float) SOUND_MAX));
}

static std::string music_current;

void music_play (std::string file,
                 std::string alias,
                 uint32_t rate)
{_
    if (file == music_current) {
        return;
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

            MSG_BOX("Mix_OpenAudio fail: %s %s",
                    Mix_GetError(), SDL_GetError());
            SDL_ClearError();
        }

        music_init_done = true;
    }

    musicp music = music_load(file, alias);

    music_update_volume();

    static int sound_loaded;
    if (!sound_loaded) {
        sound_loaded = true;
        sound_load_all();
    }

    if (Mix_FadeInMusicPos(music->m, -1, 2000, 0) == -1) {
//    if (Mix_PlayMusic(music->m, -1) == -1) {
        WARN("cannot play music %s: %s", music->name_alias.c_str(), Mix_GetError());
    }
}

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

void music_play_intro (void)
{_
    music_play("data/music/Faith.ogg", "intro", 44100 );
}

void music_play_dead (void)
{_
    music_play("data/music/Faith.ogg", "dead", 44100 );
}

void music_play_game_over (void)
{_
    music_play("data/music/Faith.ogg", "game over", 44100 );
}

void music_halt (void)
{_
    music_current = "";

    Mix_FadeOutMusic(1500);
}
