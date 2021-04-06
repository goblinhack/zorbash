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

static std::map<std::string, std::shared_ptr< class sound > > all_sound;

static std::string sound_current;

bool sound_init_done;

bool sound_init (void)
{_
    sound_load(1, "data/sounds/misc/clack.wav",               "clack");
    sound_load(1, "data/sounds/misc/step.wav",                "step");
    sound_load(1, "data/sounds/misc/bay_door_close.wav",      "bay_door_close");
    sound_load(1, "data/sounds/misc/fall.wav",                "fall");
    sound_load(1, "data/sounds/misc/close_shut.wav",          "close_shut");
    sound_load(1, "data/sounds/misc/swerve.wav",              "swerve");
    sound_load(1, "data/sounds/misc/mushroom.wav",            "mushroom");
    sound_load(1, "data/sounds/misc/rebound.wav",             "rebound");
    sound_load(1, "data/sounds/misc/collect_a.wav",           "collect_a");
    sound_load(1, "data/sounds/misc/bay_door_open.wav",       "bay_door_open");
    sound_load(1, "data/sounds/misc/collect_b.wav",           "collect_b");
    sound_load(1, "data/sounds/misc/shriek.wav",              "shriek");
    sound_load(1, "data/sounds/misc/whistle.wav",             "whistle");
    sound_load(1, "data/sounds/misc/zong.wav",                "zong");
    sound_load(1, "data/sounds/misc/open.wav",                "open");
    sound_load(1, "data/sounds/misc/scatter.wav",             "scatter");
    sound_load(1, "data/sounds/misc/drip.wav",                "drip");
    sound_load(1, "data/sounds/misc/unlock.wav",              "unlock");
    sound_load(1, "data/sounds/misc/chime.wav",               "chime");
    sound_load(1, "data/sounds/misc/transistor.wav",          "transistor");
    sound_load(1, "data/sounds/misc/close.wav",               "close");
    sound_load(1, "data/sounds/misc/resurrect.wav",           "resurrect");
    sound_load(1, "data/sounds/misc/wave.wav",                "wave");
    sound_load(1, "data/sounds/misc/wiggle_b.wav",            "wiggle_b");
    sound_load(1, "data/sounds/misc/blurb.wav",               "blurb");
    sound_load(1, "data/sounds/misc/wiggle_a.wav",            "wiggle_a");
    sound_load(1, "data/sounds/misc/scramble.wav",            "scramble");
    sound_load(1, "data/sounds/misc/twing.wav",               "twing");
    sound_load(1, "data/sounds/misc/shut.wav",                "shut");
    sound_load(1, "data/sounds/misc/rubberband.wav",          "rubberband");
    sound_load(1, "data/sounds/misc/ping.wav",                "ping");
    sound_load(1, "data/sounds/interface/select_b.wav",       "select_b");
    sound_load(1, "data/sounds/interface/select_a.wav",       "select_a");
    sound_load(1, "data/sounds/interface/end_turn.wav",       "end_turn");
    sound_load(1, "data/sounds/interface/bonus.wav",          "bonus");
    sound_load(1, "data/sounds/interface/paper.wav",          "paper");
    sound_load(1, "data/sounds/interface/lose_a.wav",         "lose_a");
    sound_load(1, "data/sounds/interface/lose_b.wav",         "lose_b");
    sound_load(1, "data/sounds/interface/new_turn.wav",       "new_turn");
    sound_load(1, "data/sounds/interface/gold.wav",           "gold");
    sound_load(1, "data/sounds/interface/1up_a.wav",          "1up_a");
    sound_load(1, "data/sounds/interface/blip.wav",           "blip");
    sound_load(1, "data/sounds/interface/1up_b.wav",          "1up_b");
    sound_load(1, "data/sounds/interface/coin.wav",           "coin");
    sound_load(1, "data/sounds/interface/click.wav",          "click");
    sound_load(1, "data/sounds/interface/error.wav",          "error");
    sound_load(1, "data/sounds/interface/score.wav",          "score");
    sound_load(1, "data/sounds/interface/dong.wav",           "dong");
    sound_load(1, "data/sounds/interface/level_up.wav",       "level_up");
    sound_load(1, "data/sounds/interface/ding.wav",           "ding");
    sound_load(1, "data/sounds/impacts/boom_a.wav",           "boom_a");
    sound_load(1, "data/sounds/impacts/boom_b.wav",           "boom_b");
    sound_load(1, "data/sounds/impacts/impact_b.wav",         "impact_b");
    sound_load(1, "data/sounds/impacts/impact_a.wav",         "impact_a");
    sound_load(1, "data/sounds/impacts/explode_a.wav",        "explode_a");
    sound_load(1, "data/sounds/impacts/pit_trap_fall.wav",    "pit_trap_fall");
    sound_load(1, "data/sounds/impacts/sear.wav",             "sear");
    sound_load(1, "data/sounds/impacts/explode_b.wav",        "explode_b");
    sound_load(1, "data/sounds/impacts/explode_c.wav",        "explode_c");
    sound_load(1, "data/sounds/impacts/magic_crumble.wav",    "magic_crumble");
    sound_load(1, "data/sounds/impacts/area_effect_a.wav",    "area_effect_a");
    sound_load(1, "data/sounds/impacts/area_effect_b.wav",    "area_effect_b");
    sound_load(1, "data/sounds/impacts/pit_trap_damage.wav",  "pit_trap_damage");
    sound_load(1, "data/sounds/impacts/spike_trap_a.wav",     "spike_trap_a");
    sound_load(1, "data/sounds/impacts/hit.wav",              "hit");
    sound_load(1, "data/sounds/impacts/spike_trap_b.wav",     "spike_trap_b");
    sound_load(1, "data/sounds/impacts/magic_dust_b.wav",     "magic_dust_b");
    sound_load(1, "data/sounds/impacts/magic_dust_a.wav",     "magic_dust_a");
    sound_load(1, "data/sounds/status/curse.wav",             "curse");
    sound_load(1, "data/sounds/status/freeze.wav",            "freeze");
    sound_load(1, "data/sounds/status/mutation.wav",          "mutation");
    sound_load(1, "data/sounds/status/confuse.wav",           "confuse");
    sound_load(1, "data/sounds/status/disease.wav",           "disease");
    sound_load(1, "data/sounds/status/burn.wav",              "burn");
    sound_load(1, "data/sounds/status/charm.wav",             "charm");
    sound_load(1, "data/sounds/status/poison.wav",            "poison");
    sound_load(1, "data/sounds/abilities/jump_a.wav",         "jump_a");
    sound_load(1, "data/sounds/abilities/disarm_single.wav",  "disarm_single");
    sound_load(1, "data/sounds/abilities/jump_b.wav",         "jump_b");
    sound_load(1, "data/sounds/abilities/disarm_multi_b.wav", "disarm_multi_b");
    sound_load(1, "data/sounds/abilities/heal_b.wav",         "heal_b");
    sound_load(1, "data/sounds/abilities/laser_a.wav",        "laser_a");
    sound_load(1, "data/sounds/abilities/disarm_success.wav", "disarm_success");
    sound_load(1, "data/sounds/abilities/sorcery.wav",        "sorcery");
    sound_load(1, "data/sounds/abilities/disarm_multi_a.wav", "disarm_multi_a");
    sound_load(1, "data/sounds/abilities/heal_a.wav",         "heal_a");
    sound_load(1, "data/sounds/abilities/laser_b.wav",        "laser_b");
    sound_load(1, "data/sounds/abilities/blaster.wav",        "blaster");
    sound_load(1, "data/sounds/abilities/woosh_a.wav",        "woosh_a");
    sound_load(1, "data/sounds/abilities/bazooka.wav",        "bazooka");
    sound_load(1, "data/sounds/abilities/swing.wav",          "swing");
    sound_load(1, "data/sounds/abilities/fire_a.wav",         "fire_a");
    sound_load(1, "data/sounds/abilities/woosh_b.wav",        "woosh_b");
    sound_load(1, "data/sounds/abilities/fire_b.wav",         "fire_b");
    sound_load(1, "data/sounds/abilities/fire_c.wav",         "fire_c");
    sound_load(1, "data/sounds/abilities/special_b.wav",      "special_b");
    sound_load(1, "data/sounds/abilities/spell_a.wav",        "spell_a");
    sound_load(1, "data/sounds/abilities/teleport.wav",       "teleport");
    sound_load(1, "data/sounds/abilities/special_a.wav",      "special_a");
    sound_load(1, "data/sounds/abilities/spell_b.wav",        "spell_b");
    sound_load(1, "data/sounds/abilities/shoot_b.wav",        "shoot_b");
    sound_load(1, "data/sounds/abilities/shoot_a.wav",        "shoot_a");
    sound_load(1, "data/sounds/abilities/reload.wav",         "reload");
    sound_load(1, "data/sounds/abilities/attack_a.wav",       "attack_a");
    sound_load(1, "data/sounds/abilities/attack_b.wav",       "attack_b");
    sound_load(1, "data/sounds/abilities/shotgun.wav",        "shotgun");
    sound_load(1, "data/sounds/abilities/lightning_a.wav",    "lightning_a");
    sound_load(1, "data/sounds/abilities/summon.wav",         "summon");
    sound_load(1, "data/sounds/abilities/lightning_b.wav",    "lightning_b");
    sound_load(1, "data/sounds/abilities/telepathy.wav",      "telepathy");
    sound_load(1, "data/sounds/creatures/bird.wav",           "bird");
    sound_load(1, "data/sounds/creatures/wings.wav",          "wings");
    sound_load(1, "data/sounds/creatures/skeleton.wav",       "skeleton");
    sound_load(1, "data/sounds/creatures/beetle.wav",         "beetle");
    sound_load(1, "data/sounds/creatures/mystical.wav",       "mystical");
    sound_load(1, "data/sounds/creatures/claw.wav",           "claw");
    sound_load(1, "data/sounds/creatures/jelly.wav",          "jelly");
    sound_load(1, "data/sounds/creatures/snake.wav",          "snake");
    sound_load(1, "data/sounds/creatures/mouse.wav",          "mouse");
    sound_load(1, "data/sounds/creatures/swarm.wav",          "swarm");
    sound_load(1, "data/sounds/creatures/frog.wav",           "frog");

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

    auto s = std::make_shared< class sound >(alias);

    auto result = all_sound.insert(std::make_pair(alias, s));
    if (result.second == false) {
        ERR("Cannot insert sound name [%s] failed", alias.c_str());
        return false;
    }

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

    if (Mix_PlayChannel(-1 /* first free channel */,
                        sound->second->chunk, 
                        0 /* loops */) == -1) {
        ERR("Cannot play sound %s: %s", alias.c_str(), Mix_GetError());
        SDL_ClearError();
    }

    float volume = sound->second->volume *
        ((float) game->config.sound_volume / (float) MIX_MAX_VOLUME);

    volume *= MIX_MAX_VOLUME;

    Mix_VolumeChunk(sound->second->chunk, volume);

    return true;
}

void sound_halt (void)
{_
    sound_current = "";
}
