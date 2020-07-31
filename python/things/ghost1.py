import zx
import tp

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_ai_delay_after_moving_ms(10)
    x.set_ai_scent_distance(10)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_shown_on_monstbar(True)
    x.set_is_able_to_change_levels(True)
    x.set_is_active(True)
    x.set_is_attack_lunge(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_intelligent(True)
    x.set_is_interesting(True)
    x.set_is_floating(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_gfx_moves_ahead_shown(True)
    x.set_is_gfx_health_bar_shown(True)
    x.set_is_ethereal(True)
    x.set_is_movable(True)
    x.set_is_undead(True)
    x.set_normal_placement_rules(True)
    x.set_stats_attack_dice("1d1")
    x.set_stats_defence(1)
    x.set_stats_health_hunger_pct(95)
    x.set_stats_health_initial(3)
    x.set_stats_move_speed_ms(250)
    x.set_stats_strength(1)
    x.set_text_a_or_an("a");
    x.set_text_hits("chills");
    x.set_tick_rate_tenths(3)
    x.set_gfx_anim_attack("claws1")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_text_description("The angry spirit of one long passed")

    delay = 200
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)
    x.set_tile(tile=name + ".3", delay_ms=delay)
    x.set_tile(tile=name + ".4", delay_ms=delay)
    x.set_tile(tile=name + ".5", delay_ms=delay)
    x.set_tile(tile=name + ".6", delay_ms=delay)
    x.set_tile(tile=name + ".7", delay_ms=delay, is_invisible=True)
    x.set_tile(tile=name + ".8", delay_ms=delay, is_invisible=True)
    x.set_tile(tile=name + ".9", delay_ms=delay, is_invisible=True)
    x.set_tile(tile=name + ".10", delay_ms=delay, is_invisible=True)
    x.set_tile(tile=name + ".11", delay_ms=delay, is_invisible=True)

    delay=10
    x.set_tile("attack_slime.1", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.2", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.3", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.4", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.5", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.6", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.7", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.8", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.9", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.10", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.11", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.12", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.13", is_dead=True, delay_ms=delay)
    x.set_tile("attack_slime.14", is_dead=True, delay_ms=delay, is_end_of_anim = True)

    x.update()

def init():
    tp_init(name="ghost1", text_name="ghost")

init()

