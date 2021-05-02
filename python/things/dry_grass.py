import zx
import tp


def on_death(me, x, y):
    zx.level_spawn_at_thing(me, "small_fire")
    zx.topcon("The dry grass burns!")

def tp_init(name, tiles=[]):
    x = tp.Tp(name, "dry grass")
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gfx_very_small_shadow_caster(True)
    x.set_is_able_to_fall(False)
    x.set_is_burnable(True)
    x.set_is_combustible(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_dry_grass(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_on_death_do("dry_grass.on_death()")
    x.set_text_a_or_an("the")
    x.set_text_description("Brittle dry grass.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="dry_grass",
        tiles=[
            "dry_grass.1", "dry_grass.2", "dry_grass.3", "dry_grass.4",
            "dry_grass.5", "dry_grass.6", "dry_grass.7", "dry_grass.8",
            "dry_grass.9", "dry_grass.10", "dry_grass.11", "dry_grass.12",
            "dry_grass.13", "dry_grass.14", "dry_grass.15", "dry_grass.16",
            "dry_grass.17", "dry_grass.18", 
        ])
init()
