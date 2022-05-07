import my
import tp


def tp_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.text_a_or_an(self, "an")
    my.text_description(self, "An empty podium. With claw marks.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=t)

    my.tp_update(self)


def init():
    tp_init(
        name="gargoyle_podium",
        text_name="empty podium",
        tiles=[
            "gargoyle.podium",
        ],
    )


init()
