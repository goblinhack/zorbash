import zx
import tp


def tp_init(name, tiles=[]):
    x = tp.Tp(name, "dry trampled fungus")
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gfx_very_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_dry_fungus(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_text_a_or_an("the")
    x.set_text_description("Burnt not so funky fungus.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="dry_fungus_dead",
        tiles=[
            "dry_fungus_dead.1", "dry_fungus_dead.2", "dry_fungus_dead.3", "dry_fungus_dead.4",
            "dry_fungus_dead.5", "dry_fungus_dead.6", "dry_fungus_dead.7", "dry_fungus_dead.8",
            "dry_fungus_dead.9", "dry_fungus_dead.10", "dry_fungus_dead.11", "dry_fungus_dead.12",
            "dry_fungus_dead.13", "dry_fungus_dead.14", "dry_fungus_dead.15", "dry_fungus_dead.16",
            "dry_fungus_dead.17", "dry_fungus_dead.18", 
        ])
init()
