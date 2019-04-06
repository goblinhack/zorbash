import zx
import tp

def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_ai_delay_after_moving_ms(10)
    x.set_ai_scent_distance(30)
    x.set_attack_on_collision(True)
    x.set_bite_damage_hd("1d4+1")
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.5)
    x.set_gfx_animated(True)
    x.set_gfx_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_hunger_at_health_pct(95)
    x.set_hunger_every_ms(10000)
    x.set_hunger_initial_health_at(10)
    x.set_hunger_starving_at_health_pct(10)
    x.set_is_active(True)
    x.set_is_corpse_on_death(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_movement_blocking(True)
    x.set_is_water_dweller(True)
    x.set_move_speed_ms(1000)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_MONST)

    delay = 100
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)

    x.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)

    x.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)

    x.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)

    x.set_tile(tile=name + ".dead", is_dead=True)

    x.update()
    
def init():
    tp_init(name="slime1", short_name="slime1")

init()
