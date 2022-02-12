import my
import tp


def on_idle_tick_frequency_dice(me, x, y):
    #
    # Make sure to only spawn minions so they have the is_minion flag set
    #
    if my.level_spawn_next_to(me, "bat_minion"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_BIRTH, "bones2")


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "mob_explosion")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.ai_shove_chance_d1000(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_received_doubled_from_fire(self, True)
    my.damage_received_doubled_from_water(self, True)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_water(self, 100)
    my.gfx_animated(self, True)
    my.gfx_glows(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.health_initial_dice(self, "6d6")
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_ethereal_mob(self, True)
    my.is_loggable(self, True)
    my.is_mob_challenge_class_a(self, True)
    my.is_mob(self, True)
    my.is_obs_destructable(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "green")
    my.light_power(self, 3)
    my.long_text_description(self, "A dark gateway for the creatures of the night. Also cheap boarding rates.")
    my.minion_limit(self, 5)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_frequency_dice(self, "1d10+10:me.on_idle_tick_frequency_dice()")
    my.text_a_or_an(self, "a")
    my.text_description(self, "A cursed coffin, spawning all manner of surprises.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tile(self, tile=name + ".100", is_hp_100_percent=True, delay_ms=delay)
    my.tile(self, tile=name + ".75", is_hp_75_percent=True, delay_ms=delay)
    my.tile(self, tile=name + ".50", is_hp_50_percent=True, delay_ms=delay)
    my.tile(self, tile=name + ".25", is_hp_25_percent=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="coffin_mob", text_name="coffin mobber")


init()
