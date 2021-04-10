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
    sound (std::string alias) : alias(alias)
    {
    }

    ~sound (void)
    {
        Mix_FreeChunk(chunk);
        myfree(data);
    }

    std::string alias;
    Mix_Chunk *chunk = {};
    unsigned char *data = {};
    int32_t len = {};
    float volume {};
};

static std::map<std::string, class sound *> all_sound;

bool sound_init_done;

bool sound_init (void)
{_
    Mix_AllocateChannels(16);

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
}

bool sound_load (float volume, const char *file_in, const char *alias_in)
{_
    auto file  = std::string(file_in);
    auto alias = std::string(alias_in);

    return sound_load(volume, file, alias);
}

bool sound_load (float volume, const std::string &file, 
                 const std::string &alias)
{_
    if (alias == "") {
        auto s = sound_find(alias);
        if (s) {
            return (true);
        }
    }

    class sound * s = new sound(alias);

    s->volume = volume;
    s->data = file_load(file.c_str(), &s->len);
    if (!s->data) {
        ERR("Cannot load sound %s", file.c_str());
        return false;
    }

    SDL_RWops *rw;

    rw = SDL_RWFromMem(s->data, s->len);
    if (!rw) {
        ERR("SDL_RWFromMem fail %s: %s %s", 
            file.c_str(), Mix_GetError(), SDL_GetError());
        SDL_ClearError();
        return false;
    }

    s->chunk = Mix_LoadWAV_RW(rw, false /* A non-zero value mean is will automatically close/free the src for you. */);
    if (!s->chunk) {
        ERR("Mix_LoadWAV_RW fail %s: %s %s", 
            file.c_str(), Mix_GetError(), SDL_GetError());
        SDL_ClearError();
        return false;
    }

    auto result = all_sound.insert(std::make_pair(alias, s));
    if (result.second == false) {
        ERR("Cannot insert sound name [%s] failed", alias.c_str());
        return false;
    }

    DBG("Load %s", file.c_str());

    return (true);
}

//
// Find an existing pice of sound.
//
bool sound_find (const std::string &alias)
{_
    auto result = all_sound.find(alias);
    return result != all_sound.end();
}

bool sound_play (const std::string &alias)
{_
    auto sound = all_sound.find(alias);
    if (sound == all_sound.end()) {
        ERR("Cannot find sound %s", alias.c_str());
        return false;
    }

    float volume = sound->second->volume *
        ((float) game->config.sound_volume / (float) MIX_MAX_VOLUME);

    volume *= MIX_MAX_VOLUME;

    Mix_VolumeChunk(sound->second->chunk, volume);

    if (Mix_PlayChannel(-1 /* first free channel */,
                        sound->second->chunk, 
                        0 /* loops */) == -1) {

        LOG("Cannot play sound %s on any channel", alias.c_str());
        Mix_HaltChannel(0);
        SDL_ClearError();

        if (Mix_PlayChannel(-1 /* first free channel */,
                            sound->second->chunk, 
                            0 /* loops */) == -1) {
            ERR("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
            SDL_ClearError();
        }
    }

    return true;
}

bool sound_play_channel (int channel, const std::string &alias)
{_
    auto sound = all_sound.find(alias);
    if (sound == all_sound.end()) {
        ERR("Cannot find sound %s", alias.c_str());
        return false;
    }

    if (Mix_Playing(channel)) {
        LOG("Cannot play sound %s on channel %d, something else playing", alias.c_str(), channel);
        return false;
    }

    float volume = sound->second->volume *
        ((float) game->config.sound_volume / (float) MIX_MAX_VOLUME);

    volume *= MIX_MAX_VOLUME;

    Mix_VolumeChunk(sound->second->chunk, volume);

    if (Mix_PlayChannel(channel,
                        sound->second->chunk, 
                        0 /* loops */) == -1) {
        LOG("Cannot play sound %s on channel %d", alias.c_str(), channel);
        return false;
    }

    LOG("Play sound %s on channel %d", alias.c_str(), channel);

    return true;
}

void sound_halt (void)
{_
}
