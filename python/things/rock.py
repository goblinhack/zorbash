import zx
import tp


def tp_init(name, tiles=[], left1_tiles=[]):
    x = tp.Tp(name)

    x.set_a_or_an("the");
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_large_shadow(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_interesting(False)
    x.set_is_loggable(False)
    x.set_is_movement_blocking(True)
    x.set_is_obstacle(True)
    x.set_is_rock(True)
    x.set_is_wall(True)
    x.set_z_depth(zx.MAP_DEPTH_WALLS)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="rock1",
            tiles=[
                        "rock1.1", "rock1.2", "rock1.3", "rock1.4",
                        "rock1.5", "rock1.6", "rock1.7", "rock1.8",
                        "rock1.9", "rock1.10", "rock1.11", "rock1.12",
                        "rock1.13", "rock1.14", "rock1.15", "rock1.16",
                        "rock1.17", "rock1.18", "rock1.19",
                ])
    tp_init(name="rock2",
            tiles=[
                        "rock2.1", "rock2.2", "rock2.3", "rock2.4",
                        "rock2.5", "rock2.6", "rock2.7", "rock2.8",
                        "rock2.9", "rock2.10", "rock2.11", "rock2.12",
                        "rock2.13", "rock2.14", "rock2.15", "rock2.16",
                        "rock2.17", "rock2.18", "rock2.19",
                ])
init()
