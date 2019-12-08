import zx
import tp

def tp_init(name):
    x = tp.Tp(name)

    x.set_ai_delay_after_moving_ms(100)
    x.set_ai_scent_distance(30)
    x.set_bite_damage_hd("1d4+1")
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.5)
    x.set_gfx_animated(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_can_hflip(True)
    x.set_gfx_show_hiddend(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_hunger_at_health_pct(95)
    x.set_hunger_constant(True)
    x.set_hunger_initial_health_at(10)
    x.set_is_active(True)
    x.set_is_attackable(True)
    x.set_is_corpse_on_death(True)
    x.set_is_interesting(True)
    x.set_is_loggable(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_is_undead(True)
    x.set_is_water_hater(100)
    x.set_move_speed_ms(300)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)

    x.update()
    
def init():
    tp_init(name="mummy1")

init()
