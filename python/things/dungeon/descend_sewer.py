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
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_descend_sewer(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "lime")
    my.light_dist(self, 1)
    my.long_text_description(self, "A filthy sewer pipe. Watch out, they can spawn surprises. Don't fall in!")
    my.minion_limit(self, 5)
    my.on_idle_tick_freq_dice(self, "1d50+50:descend_sewer.spawn()")
    my.text_a_or_an(self, "a")
    my.text_description(self, "A slime coated sewer pipe.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_ALWAYS_BEHIND)

    delay = 2500
    for t in tiles:
        my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=t, delay_ms=delay)

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
