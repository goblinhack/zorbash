import my
import tp


def spawn(me, x, y):
    my.level_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):
    # my.tp_set_is_mob(mytp, True) # don't set to avoid auto place
    mytp = tp.Tp(name)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_shown_in_bg(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_ascend_sewer(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_light_color(mytp, "lime")
    my.tp_set_light_power(mytp, 1)
    my.tp_set_long_text_description(mytp, "A way out of these stinking sewers!")
    my.tp_set_minion_limit(mytp, 5)
    my.tp_set_on_idle_tick_frequency_dice(mytp, "1d50+50:ascend_sewer.spawn()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A slime coated sewer pipe.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 1000
    for t in tiles:
        my.tp_set_tile(mytp, tile=t, delay_ms=delay)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="ascend_sewer1",
        tiles=[
            "ascend_sewer1.1",
            "ascend_sewer1.2",
        ],
    )
    tp_init(
        name="ascend_sewer2",
        tiles=[
            "ascend_sewer2.1",
            "ascend_sewer2.2",
        ],
    )
    tp_init(
        name="ascend_sewer3",
        tiles=[
            "ascend_sewer3.1",
            "ascend_sewer3.2",
        ],
    )
    tp_init(
        name="ascend_sewer4",
        tiles=[
            "ascend_sewer4.1",
            "ascend_sewer4.2",
        ],
    )


init()
