import zx
import tp

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_ai_delay_after_moving_ms(1000)
    x.set_ai_scent_distance(5)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_attackable(True)
    x.set_is_combustible(True)
    x.set_is_baby_slime(True)
    x.set_is_double_damage_from_fire(True)
    x.set_is_attack_lunge(True)
    x.set_is_fire_hater(100)
    x.set_is_jumper_chance_d1000(500)
    x.set_is_jumper_distance(5)
    x.set_is_jumper(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat_eater(True)
    x.set_is_baby_slime_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_normal_placement_rules(True)
    x.set_stats_attack_dice("1d1+3")
    x.set_stats_defence(0)
    x.set_stats_health_hunger_pct(95)
    x.set_stats_health_initial(5)
    x.set_stats_move_speed_ms(1000)
    x.set_stats_strength(1)
    x.set_text_a_or_an("a");
    x.set_text_hits("splats");
    x.set_tick_rate_tenths(3)
    x.set_weapon_use_anim("splat1")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)

    #x.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    #x.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    #x.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    #x.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    #x.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)
    x.set_tile(tile=name + ".dead", is_dead=True, is_end_of_anim=True)

    x.update()

def init():
    tp_init(name="slime1", text_name="slime")

init()

