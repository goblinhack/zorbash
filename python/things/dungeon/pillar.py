import my
import tp


def tp_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_always_hit(self, True)
    my.tp_set_is_floor_deco(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_obs_wall_or_door(self, True)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "An aged and moss-covered stone pillar.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    for t in tiles:
        my.tp_set_tile(self, tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="pillar1",
        text_name="stone pillar",
        tiles=[
            "pillar1.1",
            "pillar1.2",
            "pillar1.3",
            "pillar1.4",
            "pillar1.5",
            "pillar1.6",
            "pillar1.7",
            "pillar1.8",
            "pillar1.9",
            "pillar1.10",
            "pillar1.11",
            "pillar1.12",
            "pillar1.13",
            "pillar1.14",
            "pillar1.15",
            "pillar1.16",
            "pillar1.17",
            "pillar1.18",
            "pillar1.19",
            "pillar1.20",
            "pillar1.21",
            "pillar1.22",
            "pillar1.23",
            "pillar1.24",
            "pillar1.25",
            "pillar1.26",
            "pillar1.27",
            "pillar1.28",
            "pillar1.29",
            "pillar1.30",
            "pillar1.31",
            "pillar1.32",
        ],
    )


init()
