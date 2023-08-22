import my
import tp


def tp_init(name, text_long_name, tiles=[]):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_floor_deco(self, True)
    my.is_interesting(self, True)
    my.is_obs_ai(self, True)
    my.is_obs_jump_end(self, True)
    my.is_obs_jumping(self, True)
    my.is_obs_shooting(self, True)
    my.is_obs_shoving(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_obs_spawn(self, True)
    my.is_obs_spell_casting(self, True)
    my.is_obs_throwing(self, True)
    my.is_obs_wall_or_door(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_pillar(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "An aged and moss-covered stone pillar.")
    my.thing_size(self, my.THING_SIZE_GIANT)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="|", ascii_bg_col_name="", ascii_fg_col_name="white",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="pillar",
        text_long_name="stone pillar",
        tiles=[
            "pillar.1",
            "pillar.2",
            "pillar.3",
            "pillar.4",
            "pillar.5",
            "pillar.6",
            "pillar.7",
            "pillar.8",
            "pillar.9",
            "pillar.10",
            "pillar.11",
            "pillar.12",
            "pillar.13",
            "pillar.14",
            "pillar.15",
            "pillar.16",
            "pillar.17",
            "pillar.18",
            "pillar.19",
            "pillar.20",
            "pillar.21",
            "pillar.22",
            "pillar.23",
            "pillar.24",
            "pillar.25",
            "pillar.26",
            "pillar.27",
            "pillar.28",
            "pillar.29",
            "pillar.30",
            "pillar.31",
            "pillar.32",
            "pillar.33",
            "pillar.34",
            "pillar.35",
            "pillar.36",
            "pillar.37",
            "pillar.38",
            "pillar.39",
            "pillar.40",
            "pillar.41",
            "pillar.42",
            "pillar.43",
            "pillar.44",
            "pillar.45",
            "pillar.46",
            "pillar.47",
            "pillar.48",
        ],
    )


init()
