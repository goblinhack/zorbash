import my
import tp


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_text_a_or_an("an")
    mytp.set_text_description("An empty podium. With claw marks.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(tile=t)

    mytp.update()


def init():
    tp_init(
        name="gargoyle_podium",
        text_name="empty podium",
        tiles=[
            "gargoyle.podium",
        ],
    )


init()
