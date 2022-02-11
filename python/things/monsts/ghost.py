import my
import tp


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "ghost_explosion")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(mytp, 100)
    my.tp_set_ai_wanderer(mytp, True)
    my.tp_set_attack_humanoid(mytp, True)
    my.tp_set_attack_lunge(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_damage_cold_dice(mytp, "1")
    my.tp_set_distance_vision(mytp, 7)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "attack_claws")
    my.tp_set_gfx_glows(mytp, True)
    my.tp_set_gfx_health_bar_shown(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_health_initial_dice(mytp, "1")
    my.tp_set_is_able_to_see_in_the_dark(mytp, True)
    my.tp_set_is_able_to_walk_through_walls(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_ethereal(mytp, True)
    my.tp_set_is_fearless(mytp, True)
    my.tp_set_is_floating(mytp, True)
    my.tp_set_is_green_blooded(mytp, True)  # not really
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_immune_to_acid(mytp, True)
    my.tp_set_is_immune_to_cold(mytp, True)
    my.tp_set_is_immune_to_fire(mytp, True)
    my.tp_set_is_immune_to_necrosis(mytp, True)
    my.tp_set_is_immune_to_poison(mytp, True)
    my.tp_set_is_immune_to_water(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_monst_class_a(mytp, True)
    my.tp_set_is_monst(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_undead(mytp, True)
    my.tp_set_light_color(mytp, "green")
    my.tp_set_light_power(mytp, 1)
    my.tp_set_long_text_description(mytp, "A spirit of one less fortunate than you. Beware, ghosts can traverse chasms that you cannot.")
    my.tp_set_monst_size(mytp, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(mytp, 0)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stat_con(mytp, 10)
    my.tp_set_stat_def(mytp, 11)
    my.tp_set_stat_dex(mytp, 13)
    my.tp_set_stat_luck(mytp, 10)
    my.tp_set_stat_str(mytp, 7)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "The angry spirit of one long passed.")
    my.tp_set_text_hits(mytp, "slashes")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    delay = 200
    my.tp_set_tile(mytp, "ghost.1", delay_ms=delay)
    my.tp_set_tile(mytp, "ghost.2", delay_ms=delay)
    my.tp_set_tile(mytp, "ghost.3", delay_ms=delay)
    my.tp_set_tile(mytp, "ghost.4", delay_ms=delay)
    my.tp_set_tile(mytp, "ghost.5", delay_ms=delay)
    my.tp_set_tile(mytp, "ghost.6", delay_ms=delay)
    my.tp_set_tile(mytp, "ghost.7", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(mytp, "ghost.8", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(mytp, "ghost.9", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(mytp, "ghost.10", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(mytp, "ghost.11", delay_ms=delay, is_invisible=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="ghost", text_name="ghost")


init()
