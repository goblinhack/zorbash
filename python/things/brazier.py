import zx
import tp


def tp_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)
    x.set_ai_obstacle(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_glows(True)
    x.set_gfx_flickers(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True) # for pushing and falling
    x.set_is_brazier(True)
    x.set_is_corpse_on_death(True)
    x.set_is_dead_on_shove(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_fire(True)
    x.set_is_floor_deco(True)
    x.set_is_item(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_movement_blocking_soft(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_shown_uniquely_on_leftbar(True)
    x.set_light_color("orange")
    x.set_light_strength(2)
    x.set_normal_placement_rules(True)
    x.set_spawn_on_shoved("fire")
    x.set_text_a_or_an("a");
    x.set_text_description("A beacon of light in this blighted place.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=100
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.set_tile(tile=name + ".dead", is_dead=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="brazier1", text_name="brazier",
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
                "brazier1.33",
                "brazier1.34",
                "brazier1.35",
                "brazier1.36",
                "brazier1.37",
                ])
init()
