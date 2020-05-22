import zx
import tp


def tp_init(name, real_name, tiles=[]):
    x = tp.Tp(name, real_name)

    x.set_a_or_an("a");
    x.set_ai_obstacle(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_is_gfx_animated(True)
    x.set_is_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_is_gfx_show_outlined(True)
    x.set_is_gfx_small_shadow_caster(True)
    x.set_is_combustible(True)
    x.set_is_flammable(True)
    x.set_is_floor_deco(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(2)
    x.set_is_loggable(False)
    x.set_is_movement_blocking(True)
    x.set_is_shovable(True)
    x.set_light_color("yellow")
    x.set_z_depth(zx.MAP_DEPTH_WALLS)

    delay=50
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    tp_init(name="brazier1", real_name="brazier",
            tiles=[
                "brazier1.1",
                "brazier1.2",
                "brazier1.3",
                "brazier1.4",
                "brazier1.5",
                "brazier1.6",
                "brazier1.7",
                "brazier1.8",
                "brazier1.9",
                "brazier1.10",
                "brazier1.11",
                "brazier1.12",
                "brazier1.13",
                "brazier1.14",
                "brazier1.15",
                "brazier1.16",
                "brazier1.17",
                "brazier1.18",
                "brazier1.19",
                "brazier1.20",
                "brazier1.21",
                "brazier1.22",
                "brazier1.23",
                "brazier1.24",
                "brazier1.25",
                "brazier1.26",
                "brazier1.27",
                "brazier1.28",
                "brazier1.29",
                "brazier1.30",
                "brazier1.31",
                "brazier1.32",
                ])
init()
