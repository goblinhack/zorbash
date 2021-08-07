import zx
import tp


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "dry trampled grass")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_very_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_dry_grass(True)
    mytp.set_is_interesting(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Burnt not so funky grass.")
    mytp.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()

def init():
    tp_init(name="dry_grass_dead",
        tiles=[
            "dry_grass_dead.1", "dry_grass_dead.2", "dry_grass_dead.3", "dry_grass_dead.4",
            "dry_grass_dead.5", "dry_grass_dead.6", "dry_grass_dead.7", "dry_grass_dead.8",
            "dry_grass_dead.9", "dry_grass_dead.10", "dry_grass_dead.11", "dry_grass_dead.12",
            "dry_grass_dead.13", "dry_grass_dead.14", "dry_grass_dead.15", "dry_grass_dead.16",
            "dry_grass_dead.17", "dry_grass_dead.18",
        ])
init()
