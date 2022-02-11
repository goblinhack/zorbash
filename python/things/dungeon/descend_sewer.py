import my
import tp


def spawn(me, x, y):
    my.level_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):
    # my.tp_set_is_mob(self, True) # don't set to avoid auto place
    self = tp.Tp(name)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_shown_in_bg(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_descend_sewer(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_light_color(self, "lime")
    my.tp_set_light_power(self, 1)
    my.tp_set_long_text_description(self, "A filthy sewer pipe. Watch out, they can spawn surprises. Don't fall in!")
    my.tp_set_minion_limit(self, 5)
    my.tp_set_on_idle_tick_frequency_dice(self, "1d50+50:descend_sewer.spawn()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A slime coated sewer pipe.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 2500
    for t in tiles:
        my.tp_set_tile(self, tile=t, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(
        name="descend_sewer1",
        tiles=[
            "descend_sewer1.1",
            "descend_sewer1.2",
        ],
    )
    tp_init(
        name="descend_sewer2",
        tiles=[
            "descend_sewer2.1",
            "descend_sewer2.2",
        ],
    )
    tp_init(
        name="descend_sewer3",
        tiles=[
            "descend_sewer3.1",
            "descend_sewer3.2",
        ],
    )
    tp_init(
        name="descend_sewer4",
        tiles=[
            "descend_sewer4.1",
            "descend_sewer4.2",
        ],
    )
    tp_init(
        name="descend_sewer5",
        tiles=[
            "descend_sewer5.1",
            "descend_sewer5.2",
        ],
    )


init()
