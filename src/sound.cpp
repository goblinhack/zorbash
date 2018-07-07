/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the README file for license info for license.
 */

#include <SDL_mixer.h>

#include "my_main.h"
#include "my_sound.h"
#include "my_ramdisk.h"
#include "my_music.h"
#include "my_math_util.h"
#include "my_time_util.h"
#include "my_config.h"

class sound {

public:
    sound (std::string name_alias) : name_alias(name_alias)
    {
    }

    ~sound (void)
    {
        Mix_FreeChunk(m);
        myfree(data);
    }

    std::string name_alias;
    Mix_Chunk *m = {};
    unsigned char *data = {};
    int32_t len = {};
    double volume = {};
};

static std::map<std::string, std::shared_ptr< class sound > > all_sound;

static uint8_t sound_init_done;

uint8_t sound_init (void)
{_
    sound_init_done = true;

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

static soundp sound_load (double volume, std::string filename, std::string name_alias)
{_
    if (name_alias == "") {
        soundp m = sound_find(name_alias);
        if (m) {
            return (m);
        }
    }

    if (filename == "") {
        if (name_alias == "") {
            ERR("no file for sound");
        } else {
            ERR("no file for sound loading %s", name_alias.c_str());
        }
    }

    auto m = std::make_shared< class sound >(name_alias);

    auto result = all_sound.insert(std::make_pair(name_alias, m));

    if (result.second == false) {
        DIE("sound insert name [%s] failed", name_alias.c_str());
    }

    m->data = ramdisk_load(filename.c_str(), &m->len);
    if (!m->data) {
        ERR("cannot load sound %s from ramdisk", filename.c_str());
        return (0);
    }

    m->volume = volume;

    SDL_RWops *rw = SDL_RWFromMem(m->data, m->len);
    if (!rw) {
        ERR("cannot make RW sound %s", filename.c_str());
        return (0);
    }

    m->m = Mix_LoadWAV_RW(rw, 0 /* freesrc */);
    if (!m->m) {
        ERR("cannot make sound %s: %s %s", filename.c_str(), Mix_GetError(),
            SDL_GetError());
        SDL_ClearError();
        return (0);
    }

    DBG("Load %s", filename.c_str());

    return (m);
}

/*
 * Find an existing pice of sound.
 */
soundp sound_find (std::string name_alias)
{_
    if (name_alias == "") {
        DIE("no filename given for font find %s", __FUNCTION__);
    }

    auto result = all_sound.find(name_alias);
    if (result == all_sound.end()) {
        return (0);
    }

    return (result->second);
}

void sound_play_at (std::string name_alias, double x, double y)
{_
    if (!music_init_done) {
        return;
    }

    soundp sound = sound_load(0.5, 0, name_alias);
    if (!sound) {
        LOG("Cannot load sound %s: %s", name_alias.c_str(), Mix_GetError());

        return;
    }

    double volume = (float) game.sound_volume * sound->volume *
              ((float) MIX_MAX_VOLUME / (float) SOUND_MAX);

#if 0
    if (player) {
        double sx, sy;

        real_to_map(x, y, &sx, &sy);

        int distance = dmap_distance_to_player(sx, sy);
        if (distance == -1) {
            return;
        }

        /*
         * Cheap effect, make the light fade away with distance.
         */
        double scale = (256.0 - (((double)distance) * 4.0)) / 256.0;
        if (scale <= 0.1) {
            return;
        }

        volume *= scale;

        if (level && (distance > 1)) {
            if (!can_see(level, player->x, player->y, sx, sy)) {
                volume /= 2.0;
            }
        }

        if (volume < 1.0) {
            return;
        }

        LOG("Play: %s vol %f dist %d",name_alias, volume, distance);
    }
#endif

    if (Mix_PlayChannel(-1, sound->m, 0) == -1) {
        LOG("Cannot play sound %s: %s", sound->name_alias.c_str(), Mix_GetError());

        return;
    }

    Mix_VolumeChunk(sound->m, volume);
}

/*
 * Like the above but no checks for line of sight and always make some sound
 * even if quiet
 */
void sound_play_global_at (std::string name_alias, double x, double y)
{_
    if (!music_init_done) {
        return;
    }

    soundp sound = sound_load(0.5, 0, name_alias);
    if (!sound) {
        LOG("Cannot load sound %s: %s", name_alias.c_str(), Mix_GetError());

        return;
    }

    double volume = (float) game.sound_volume * sound->volume *
              ((float) MIX_MAX_VOLUME / (float) SOUND_MAX);

    if (Mix_PlayChannel(-1, sound->m, 0) == -1) {
        /*
         * Try harder for global sounds as they are important.
         */
        Mix_HaltChannel(0);

        if (Mix_PlayChannel(-1, sound->m, 0) == -1) {
            ERR("cannot play sound %s: %s", sound->name_alias.c_str(), Mix_GetError());
            return;
        }
    }

    Mix_VolumeChunk(sound->m, volume);
}

void sound_play (std::string name_alias)
{_
    if (!music_init_done) {
        return;
    }

    LOG("Play: %s", name_alias.c_str());

    soundp sound = sound_load(0.5, 0, name_alias);
    if (!sound) {
        LOG("Cannot load sound %s: %s", name_alias.c_str(), Mix_GetError());

        return;
    }

    if (Mix_PlayChannel(-1, sound->m, 0) == -1) {
        LOG("Cannot play %s: %s", sound->name_alias.c_str(), Mix_GetError());

        return;
    }

    double volume = (float) game.sound_volume * sound->volume *
              ((float) MIX_MAX_VOLUME / (float) SOUND_MAX);


    LOG("Play: %s vol %f", name_alias.c_str(), volume);

    Mix_VolumeChunk(sound->m, volume);
}

void sound_play_n (std::string name_alias, int32_t n)
{_
    if (!music_init_done) {
        return;
    }

    soundp sound = sound_load(0.5, 0, name_alias);

    if (Mix_PlayChannel(-1, sound->m, n) == -1) {
        LOG("Cannot play %s: %s", sound->name_alias.c_str(), Mix_GetError());

        return;
    }

    Mix_VolumeChunk(sound->m,
                    (float) game.sound_volume * sound->volume *
                    ((float) MIX_MAX_VOLUME / (float) SOUND_MAX));
}

void sound_play_dead (void)
{_
    sound_play("dead");
}

void sound_play_click (void)
{_
    static uint32_t last_click;
    if (time_have_x_tenths_passed_since(1, last_click)) {
        last_click = time_get_time_ms();
        sound_play("sword");
    }
}

void sound_play_level_end (void)
{_
    sound_play("level_end");
}

void sound_play_slime (void)
{_
    sound_play("slime");
}

void sound_load_all (void)
{_
    sound_load(0.5, "data/sound/click.wav", "click");
    sound_load(0.5, "data/sound/powerup.wav", "powerup");
    sound_load(0.7, "data/sound/teleport.wav", "teleport");
    sound_load(0.7, "data/sound/188712__oceanictrancer__happy_effect.wav", "level_end");
    sound_load(0.7, "data/sound/explosion.wav", "explosion");
    sound_load(0.2, "data/sound/slime.wav", "slime");
    sound_load(0.5, "data/sound/swords_collide_sound_explorer_2015600826.wav", "sword");
    sound_load(0.5, "data/sound/shotgun_reload_by_ra_the_sun_god.wav", "shotgun_reload");
    sound_load(0.5, "data/sound/shotgun_by_ra_the_sun_god.wav", "shotgun");
    sound_load(0.2, "data/sound/60009__qubodup__swosh_22.ogg", "swoosh");
    sound_load(0.2, "data/sound/flame_Arrow_SoundBible.com_618067908.wav", "fireball1");
    sound_load(0.2, "data/sound/105016__julien_matthey__jm_fx_fireball_01.wav", "fireball2");
    sound_load(0.2, "data/sound/39016__wildweasel__dsfirxpl.wav", "fireball3");
    sound_load(0.2, "data/sound/219566__qubodup__poison_spell_magic.ogg", "poison");
    sound_load(0.2, "data/sound/207562__jwsoundfoley__open_24oz_soda_bottle_outdoors_long_fizz_explode.ogg", "acid");
    sound_load(0.5, "data/sound/coin_roll.wav", "payment");
    sound_load(0.5, "data/sound/treasure.wav", "treasure");
    sound_load(1.0, "data/sound/85568__joelaudio__dragon_roar.wav", "dragon");
    sound_load(1.0, "data/sound/212764__qubodup__lion_roar.ogg", "orc");
    sound_load(1.0, "data/sound/Red_Alert_FX_001.wav", "thief");
    sound_load(1.0, "data/sound/boom.wav", "boom");
    sound_load(0.5, "data/sound/effect.wav", "effect");
    sound_load(0.3, "data/sound/zombie_SoundBible.com_1966938763.wav", "zombie");
    sound_load(0.3, "data/sound/Bite_SoundBible.com_2056759375.wav", "bite");
    sound_load(0.1, "data/sound/bite_SoundBible.com_1625781385.wav", "urgh");
    sound_load(0.4, "data/sound/zombie_in_painSoundBible.com_134322253.wav", "urgh2");
    sound_load(0.7, "data/sound/demon_die.wav", "urgh3");
    sound_load(0.5, "data/sound/82388__robinhood76__01308_man_hit_9.wav", "player_hit");
    sound_load(0.8, "data/sound/45137__dj_chronos__dark_church_bell.wav", "player_death");
    sound_load(0.5, "data/sound/205563__everheat__arrow.wav", "arrow");
    sound_load(0.2, "data/sound/49676__ejfortin__energy_short_sword_5.wav", "energy1");
    sound_load(0.2, "data/sound/146733__fins__energy.wav", "energy2");
    sound_load(0.3, "data/sound/148975__adam_n__squelch_1.wav", "squelch");
    sound_load(0.5, "data/sound/Object_Drop_001.wav", "drop");
    sound_load(0.5, "data/sound/Door_Latch_002.wav", "door");
    sound_load(0.5, "data/sound/Electric_Zap.wav", "shield");
    sound_load(1.0, "data/sound/65195__uair01__chamber_choir_chord_o.wav", "choir");
    sound_load(0.5, "data/sound/238855__limetoe__collected_item.wav", "potion");
    sound_load(0.5, "data/sound/317827__blockfighter298__weapon_pickup.wav", "pickup");
    sound_load(0.5, "data/sound/170243__beatsbycasper__car_horn.wav", "beep");
    sound_load(0.5, "data/sound/244745__reitanna__egg_crack19.wav", "egg");
    sound_load(0.2, "data/sound/saw.wav", "saw");
}
