import my
import tp


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "ghost_explosion")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_aggression_level_pct(100)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_lunge(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_natural_attack_dice("1")
    mytp.set_damage_natural_attack_type("touch")
    mytp.set_distance_vision(5)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_claws")
    mytp.set_gfx_glows(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_health_initial_dice("1")
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_able_to_walk_through_walls(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_ethereal(True)
    mytp.set_is_fearless(True)
    mytp.set_is_floating(True)
    mytp.set_is_hittable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_monst_class_a(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_undead(True)
    mytp.set_light_color("green")
    mytp.set_light_power(1)
    mytp.set_long_text_description("A spirit of one less fortunate than you. Beware, ghosts can traverse chasms that you cannot.")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("me.on_death()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stat_con(10)
    mytp.set_stat_def(11)
    mytp.set_stat_dex(13)
    mytp.set_stat_str(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("The angry spirit of one long passed.")
    mytp.set_text_hits("slashes")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    delay = 200
    mytp.set_tile("ghost.1", delay_ms=delay)
    mytp.set_tile("ghost.2", delay_ms=delay)
    mytp.set_tile("ghost.3", delay_ms=delay)
    mytp.set_tile("ghost.4", delay_ms=delay)
    mytp.set_tile("ghost.5", delay_ms=delay)
    mytp.set_tile("ghost.6", delay_ms=delay)
    mytp.set_tile("ghost.7", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.8", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.9", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.10", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.11", delay_ms=delay, is_invisible=True)

    mytp.update()


def init():
    tp_init(name="ghost", text_name="ghost")


init()
