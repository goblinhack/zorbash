import my
import tp


def tp_init(name, tiles=[]):
    mytp = tp.Tp(name, "foilage")
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(2)
    mytp.set_gfx_long_shadow_caster(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_shown_in_bg(True)
    mytp.set_gfx_solid_shadow(True)
    mytp.set_health_initial_dice("1d5")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_foilage(True)
    mytp.set_is_loggable(False)
    mytp.set_is_loggable(False)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Thick and sicky looking foilage and roots.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_INFRONT)

    for t in tiles:
        mytp.set_tile(t)

    mytp.update()

def init():
    tp_init(name="foilage",
        tiles=[
            "foilage.1", "foilage.2", "foilage.3", "foilage.4",
            "foilage.5", "foilage.6", "foilage.7", "foilage.8",
            "foilage.9", "foilage.10", "foilage.11", "foilage.12",
            "foilage.13", "foilage.14", "foilage.15", "foilage.16",
        ])
init()
