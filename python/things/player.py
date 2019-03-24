import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_collision_circle(True)
    x.set_collision_hit_priority(20)
    x.set_collision_radius(0.5)
    x.set_collision_check(True)
    x.set_gfx_animated(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_can_hflip(True)
    x.set_gfx_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_hunger_initial_health_at(10)
    x.set_is_active(True)
    x.set_is_bleeder(True)
    x.set_is_made_of_meat(True)
    x.set_is_movable(True)
    x.set_is_player(True)
    x.set_move_speed_ms(100)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_PLAYER)

    delay = 550
    x.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_left=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_left=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_right=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_right=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)

def init():
    tp_init(name="player1", short_name="player1")

init()
