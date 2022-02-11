import my
import tp


def on_idle_tick_frequency_dice(me, x, y):
    #
    # Make sure to only spawn minions so they have the is_minion flag set
    #
    my.level_spawn_next_to(me, "ghost_minion")


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "mob_explosion")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_shove_chance_d1000(mytp, 200)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_damage_received_doubled_from_water(mytp, True)
    my.tp_set_environ_avoids_acid(mytp, 100)
    my.tp_set_environ_avoids_fire(mytp, 10)
    my.tp_set_environ_avoids_water(mytp, 100)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_glows(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "1d6")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_always_hit(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_ethereal_mob(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_mob_challenge_class_a(mytp, True)
    my.tp_set_is_mob(mytp, True)
    my.tp_set_is_obs_destructable(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_light_color(mytp, "cyan")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_long_text_description(mytp, "A bone portal which spews the angry spirits of those long passed.")
    my.tp_set_minion_limit(mytp, 3)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_idle_tick_frequency_dice(mytp, "1d20+20:me.on_idle_tick_frequency_dice()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A cursed pile of bones, spawning spirits.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 200
    my.tp_set_tile(mytp, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="ghost_mob", text_name="ghost mobber")


init()
