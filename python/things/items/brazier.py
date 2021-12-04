import my
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_collision_hit_priority(2)
    mytp.set_damage_crush_dice("1d6")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_glows(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_brazier(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_dead_on_shove(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_fire(True)
    mytp.set_is_floor_deco(True)
    mytp.set_is_heavy(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True) # for pushing and falling
    mytp.set_light_color("orange")
    mytp.set_light_strength(2)
    mytp.set_normal_placement_rules(True)
    mytp.set_spawn_on_shoved("fire")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A beacon of light in this blighted place.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay=100
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.set_tile(tile=name + ".dead", is_dead=True, delay_ms=delay)

    mytp.update()

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
