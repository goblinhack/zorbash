import zx
import tp


def tp_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)

    x.set_text_a_or_an("a");
    x.set_ai_obstacle(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_combustible(True)
    x.set_is_corpse_on_death(True)
    x.set_is_dead_on_shove(True)
    x.set_is_flammable(True)
    x.set_is_floor_deco(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_is_light_strength(2)
    x.set_is_loggable(False)
    x.set_is_movement_blocking(True)
    x.set_is_shovable(True)
    x.set_is_torch(True)
    x.set_light_color("yellow")
    x.set_normal_placement_rules(True)
    x.set_spawn_on_death("fire")
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)

    delay=50
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.set_tile(tile=name + ".dead", is_dead=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="torch1", text_name="torch",
            tiles=[
                "torch1.1",
                "torch1.2",
                "torch1.3",
                "torch1.4",
                "torch1.5",
                "torch1.6",
                "torch1.7",
                "torch1.8",
                "torch1.9",
                "torch1.10",
                "torch1.11",
                "torch1.12",
                "torch1.13",
                "torch1.14",
                "torch1.15",
                "torch1.16",
                "torch1.17",
                "torch1.18",
                ])
init()
