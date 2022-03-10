import my
import tp


def tp_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.ai_obstacle(self, True)
    my.collision_hit_priority(self, 2)
    my.damage_crush_chance_d1000(self, 1000)
    my.damage_crush_dice(self, "1d6")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_flickers(self, True)
    my.gfx_glows(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_brazier(self, True)
    my.is_corpse_on_death(self, True)
    my.is_dead_on_shove(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fire(self, True)
    my.is_floor_deco(self, True)
    my.is_heavy(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)  # for pushing and falling
    my.light_color(self, "orange")
    my.light_dist(self, 2)
    my.normal_placement_rules(self, True)
    my.spawn_on_shoved(self, "fire")
    my.temperature(self, 100)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A beacon of light in this blighted place.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 100
    for t in tiles:
        my.tile(self, tile=t, delay_ms=delay)

    my.tile(self, tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


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
