import my
import tp


def tp_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_text_a_or_an(self, "an")
    my.tp_set_text_description(self, "An empty podium. With claw marks.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(self, tile=t)

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
