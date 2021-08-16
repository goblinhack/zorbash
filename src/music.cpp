//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <SDL_mixer.h>
#include "my_sys.h"
#include "my_main.h"
#include "my_music.h"
#include "my_ptrcheck.h"
#include "my_file.h"
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
    uint32_t rate = 44100;
};

static std::map<std::string, class music *> all_music;

static std::string music_current;

bool music_init_done;

bool music_init (void)
{_
    //
    // MP3 is a pain to use, use OGG instead
    // int flags = MIX_INIT_OGG|MIX_INIT_MP3;
    //
    int flags = MIX_INIT_OGG;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        ERR("Mix_Init: Failed to init required OGG support");
    }
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
}

bool music_load (uint32_t rate, const std::string &file,
                 const std::string &name_alias)
{_
    if (name_alias == "") {
        auto m = music_find(name_alias);
        if (m) {
            return (true);
        }
    }

    class music * m = new music(name_alias);

    m->rate = rate;
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

    auto result = all_music.insert(std::make_pair(name_alias, m));
    if (result.second == false) {
        ERR("Cannot insert music name [%s] failed", name_alias.c_str());
        return false;
    }

    // DBG("Load %s", file.c_str());

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

bool music_play (const std::string &name)
{_
    if (name == music_current) {
        return true;
    }
    music_current = name;

    music_update_volume();

    auto music = all_music.find(name);
    if (music == all_music.end()) {
        ERR("Cannot find music %s: %s", name.c_str(), Mix_GetError());
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
    music_play("intro");
}

void music_halt (void)
{_
    music_current = "";

    Mix_FadeOutMusic(1500);
}
