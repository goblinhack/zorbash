import my
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_text_a_or_an(mytp, "an")
    my.tp_set_text_description(mytp, "An empty podium. With claw marks.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    for t in tiles:
        my.tp_set_tile(mytp, tile=t)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="gargoyle_podium",
        text_name="empty podium",
        tiles=[
            "gargoyle.podium",
        ],
    )


init()
