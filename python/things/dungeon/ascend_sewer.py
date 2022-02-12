import my
import tp


def spawn(me, x, y):
    my.level_spawn_next_to(me, "jelly_baby")


def tp_init(name, tiles=[], left1_tiles=[]):
    # my.is_mob(self, True) # don't set to avoid auto place
    self = tp.Tp(name)
    my.gfx_animated(self, True)
    my.gfx_shown_in_bg(self, True)
    my.gfx_show_outlined(self, True)
    my.is_ascend_sewer(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "lime")
    my.light_power(self, 1)
    my.long_text_description(self, "A way out of these stinking sewers!")
    my.minion_limit(self, 5)
    my.on_idle_tick_frequency_dice(self, "1d50+50:ascend_sewer.spawn()")
    my.text_a_or_an(self, "a")
    my.text_description(self, "A slime coated sewer pipe.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 1000
    for t in tiles:
        my.tile(self, tile=t, delay_ms=delay)

    my.tp_update(self)


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
