import my
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 2)
    my.tp_set_damage_crush_chance_d1000(mytp, 1000)
    my.tp_set_damage_crush_dice(mytp, "1d6")
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_flickers(mytp, True)
    my.tp_set_gfx_glows(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_brazier(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_dead_on_shove(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_fire(mytp, True)
    my.tp_set_is_floor_deco(mytp, True)
    my.tp_set_is_heavy(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # for pushing and falling
    my.tp_set_light_color(mytp, "orange")
    my.tp_set_light_power(mytp, 2)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_spawn_on_shoved(mytp, "fire")
    my.tp_set_temperature(mytp, 100)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A beacon of light in this blighted place.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 100
    for t in tiles:
        my.tp_set_tile(mytp, tile=t, delay_ms=delay)

    my.tp_set_tile(mytp, tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="brazier1",
        text_name="brazier",
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
        ],
    )


init()
