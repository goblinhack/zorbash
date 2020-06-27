import zx
import tp

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_ai_delay_after_moving_ms(10)
    x.set_ai_scent_distance(20)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_change_levels(True)
    x.set_is_active(True)
    x.set_is_attack_lunge(True)
    x.set_is_attackable(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_intelligent(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_undead(True)
    x.set_normal_placement_rules(True)
    x.set_stats_attack_dice("1d3")
    x.set_stats_defence(1)
    x.set_stats_health_hunger_pct(95)
    x.set_stats_health_initial(3)
    x.set_stats_move_speed_ms(500)
    x.set_stats_strength(1)
    x.set_text_a_or_an("a");
    x.set_text_hits("chills");
    x.set_tick_rate_tenths(1)
    x.set_weapon_use_anim("claws1")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)

    delay=10
    x.set_tile("splat1.1", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.2", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.3", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.4", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.5", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.6", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.7", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.8", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.9", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.10", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.11", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.12", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.13", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.14", is_dead=True, delay_ms=delay, is_end_of_anim = True)

    x.update()

def init():
    tp_init(name="ghost1", text_name="ghost")

init()

