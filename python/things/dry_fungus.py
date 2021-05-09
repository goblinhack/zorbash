import zx
import tp


def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    zx.level_spawn_at_thing(me, "small_fire")
    zx.level_place_at(me, "dry_fungus_dead", x, y)
    zx.topcon("The dry fungus burns!")

def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "dry fungus")
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_small_shadow_caster(True)
    mytp.set_gfx_very_small_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_burnable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_dry_fungus(True)
    mytp.set_is_interesting(True)
    mytp.set_is_loggable_for_important_stuff(False)
    mytp.set_is_loggable_for_unimportant_stuff(False)
    mytp.set_on_hit_do("dry_fungus.on_hit()")
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Brittle dry and slightly funky fungus.")
    mytp.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()

def init():
    tp_init(name="dry_fungus",
        tiles=[
            "dry_fungus.1", "dry_fungus.2", "dry_fungus.3", "dry_fungus.4",
            "dry_fungus.5", "dry_fungus.6", "dry_fungus.7", "dry_fungus.8",
            "dry_fungus.9", "dry_fungus.10", "dry_fungus.11", "dry_fungus.12",
            "dry_fungus.13", "dry_fungus.14", "dry_fungus.15", "dry_fungus.16",
            "dry_fungus.17", "dry_fungus.18", 
        ])
init()
