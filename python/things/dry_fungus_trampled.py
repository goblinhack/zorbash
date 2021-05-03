import zx
import tp


def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    zx.level_spawn_at_thing(me, "small_fire")
    zx.level_place_at(me, "dry_fungus_dead", x, y)
    zx.topcon("The dry fungus burns!")

def tp_init(name, tiles=[]):
    x = tp.Tp(name, "trampled fungus")
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(False)
    x.set_gfx_very_small_shadow_caster(False)
    x.set_is_able_to_fall(True)
    x.set_is_burnable(True)
    x.set_is_combustible(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_dry_fungus(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_on_hit_do("dry_fungus_trampled.on_hit()")
    x.set_text_a_or_an("the")
    x.set_text_description("Trampled fungus.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="dry_fungus_trampled",
        tiles=[
            "dry_fungus_trampled.1", "dry_fungus_trampled.2", "dry_fungus_trampled.3", "dry_fungus_trampled.4",
            "dry_fungus_trampled.5", "dry_fungus_trampled.6", "dry_fungus_trampled.7", "dry_fungus_trampled.8",
            "dry_fungus_trampled.9", "dry_fungus_trampled.10", "dry_fungus_trampled.11", "dry_fungus_trampled.12",
            "dry_fungus_trampled.13", "dry_fungus_trampled.14", "dry_fungus_trampled.15", "dry_fungus_trampled.16",
            "dry_fungus_trampled.17", "dry_fungus_trampled.18", 
        ])
init()
