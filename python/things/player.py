import zx
import tp


def tp_init(name, real_name):
    x = tp.Tp(name, real_name)

    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(20)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_attack_shove(True)
    x.set_is_attackable(True)
    x.set_is_bleeder(True)
    x.set_is_corpse_on_death(True)
    x.set_is_interesting(True)
    x.set_is_loggable(True)
    x.set_is_made_of_meat(True)
    x.set_is_movable(True)
    x.set_is_player(True)
    x.set_is_shovable(True)
    x.set_a_or_an("the");
    x.set_stats_attack(3)
    x.set_stats_attack_rate_tenths(3)
    x.set_stats_defence(3)
    x.set_stats_health_hunger_pct(5)
    x.set_stats_health_initial(100)
    x.set_stats_health_starving_pct(5)
    x.set_stats_move_speed_ms(100)
    x.set_stats_strength(10)
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

    x.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_up=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_up=True, is_moving=True,
               delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_down=True, is_moving=True,
               delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_down=True, is_moving=True,
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

    x.set_tile(tile=name + ".dead", is_dead=True)

    x.update()

def init():
    tp_init(name="player1", real_name="noble warrior")

init()
