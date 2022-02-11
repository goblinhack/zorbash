import my
import tp


def on_idle(me, x, y):
    if not my.thing_is_sleeping(me):
        my.level_spawn_gas_poison_around_thing(me, 2)


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "green_splatter")


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_wanderer(mytp, True)
    my.tp_set_attack_eater(mytp, True)
    my.tp_set_attack_engulf_chance_d1000(mytp, 1000)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 20)
    my.tp_set_damage_digest_dice(mytp, "1d10")
    my.tp_set_damage_natural_attack_type(mytp, "burn")
    my.tp_set_damage_natural_dice(mytp, "1d20")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_distance_vision(mytp, 5)
    my.tp_set_environ_avoids_acid(mytp, True)
    my.tp_set_environ_avoids_fire(mytp, 100)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "green_splatter")
    my.tp_set_gfx_bounce_on_move(mytp, True)
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "1d10+10")
    my.tp_set_hunger_clock_tick_frequency(mytp, 50)
    my.tp_set_hunger_health_pct(mytp, 95)
    my.tp_set_hunger_is_insatiable(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_asleep_initially(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_engulfer(mytp, True)
    my.tp_set_is_green_blooded(mytp, True)
    my.tp_set_is_heavy(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat_eater(mytp, True)
    my.tp_set_is_monst_class_b(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_obstacle_when_dead(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_sticky(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_toughness_soft(mytp, True)
    my.tp_set_light_color(mytp, "green")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_long_text_description(mytp, "Dungeon belchers are carnivorous plants that have evolved creative means of catching their prey. Beware their stench...")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_LARGE)
    my.tp_set_noise_decibels_hearing(mytp, 50)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_nutrition_dice(mytp, "1d4")
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_idle_tick_frequency_dice(mytp, "1d5:me.on_idle()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stat_con(mytp, 20)
    my.tp_set_stat_def(mytp, 0)
    my.tp_set_stat_dex(mytp, 0)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 10)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A gaseous belcher. But don't call it that to its face.")
    my.tp_set_text_hits(mytp, "burns")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)  # so it appears over things when consuming

    delay = 200
    my.tp_set_tile(mytp, tile=name + "_awake.1", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_awake.2", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_awake.3", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_awake.4", delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_dead.1", delay_ms=delay, is_dead=True)
    delay = 500
    my.tp_set_tile(mytp, tile=name + "_asleep.1", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_asleep.2", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_asleep.3", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(mytp, tile=name + "_asleep.2", is_sleeping=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(name="belcher", text_name="dungeon belcher", short_text_name="belcher")


init()
