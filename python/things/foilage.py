import zx
import tp


def tp_init(name, tiles=[]):
    x = tp.Tp(name, "foilage")
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_initial_dice("1d5")
    x.set_is_able_to_fall(True)
    x.set_is_attackable_by_player(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_foilage(True)
    x.set_is_light_blocker(True)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_text_a_or_an("the")
    x.set_text_description("Thick and sicky looking foilage and roots.")
    x.set_z_depth(zx.MAP_DEPTH_FLOOR2)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    for t in tiles:
        x.set_tile(t)

    x.update()

def init():
    tp_init(name="foilage",
        tiles=[
            "foilage.1", "foilage.2", "foilage.3", "foilage.4",
            "foilage.5", "foilage.6", "foilage.7", "foilage.8",
            "foilage.9", "foilage.10", "foilage.11", "foilage.12",
            "foilage.13", "foilage.14", "foilage.15", "foilage.16",
            "foilage.17", "foilage.18", 
        ])
init()
