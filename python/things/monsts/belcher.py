import my
import tp


def on_idle(me, x, y):
    my.level_spawn_gas_swamp_around_thing(me, 2)


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "green_splatter")


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_aggression_level_pct(100)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_engulf_chance_d1000(1000)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(20)
    mytp.set_damage_digest_dice("1d10")
    mytp.set_damage_natural_attack_type("burn")
    mytp.set_damage_natural_dice("1d20")
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_distance_vision(5)
    mytp.set_environ_avoids_acid(True)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("green_splatter")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("1d10+10")
    mytp.set_hunger_clock_tick_frequency(50)
    mytp.set_hunger_health_pct(95)
    mytp.set_hunger_is_insatiable(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_asleep_initially(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_biome_swamp(True)
    mytp.set_is_combustible(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_engulfer(True)
    mytp.set_is_green_blooded(True)
    mytp.set_is_hittable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_monst_class_b(True)
    mytp.set_is_monst(True)
    mytp.set_is_obstacle_when_dead(True)
    mytp.set_is_shovable(True)
    mytp.set_is_sticky(True)
    mytp.set_is_tickable(True)
    mytp.set_is_toughness_soft(True)
    mytp.set_light_color("green")
    mytp.set_light_power(2)
    mytp.set_long_text_description("Dungeon belchers are carnivorous plants that have evolved creative means of catching their prey. Beware their stench...")
    mytp.set_monst_size(my.MONST_SIZE_LARGE)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d4")
    mytp.set_on_death_do("me.on_death()")
    mytp.set_on_idle_tick_frequency_dice("1d5:me.on_idle()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stat_con(20)
    mytp.set_stat_def(0)
    mytp.set_stat_dex(0)
    mytp.set_stat_str(10)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A gaseous belcher. But don't call it that to its face.")
    mytp.set_text_hits("burns")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_IN_FRONT)  # so it appears over things when consuming

    delay = 200
    mytp.set_tile(tile=name + "_awake.1", delay_ms=delay)
    mytp.set_tile(tile=name + "_awake.2", delay_ms=delay)
    mytp.set_tile(tile=name + "_awake.3", delay_ms=delay)
    mytp.set_tile(tile=name + "_awake.4", delay_ms=delay)
    mytp.set_tile(tile=name + "_dead.1", delay_ms=delay, is_dead=True)

    mytp.update()


def init():
    tp_init(name="belcher", text_name="dungeon belcher", short_text_name="belcher")


init()
