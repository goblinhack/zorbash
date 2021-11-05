import zx
import tp


def lava_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(100)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_melee_dice("1d12+6")
    mytp.set_gfx_animated(True)
    mytp.set_gfx_glows(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_cursor_can_hover_over_x2_click(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_cursor_path_hazard_for_player(True)
    mytp.set_is_hazard(True)
    mytp.set_is_lava(True)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_light_color("red")
    mytp.set_light_strength(2)
    mytp.set_text_a_or_an("")
    mytp.set_text_description("%%fg=orange$Freshly scented lava%%fg=reset$ (double click to move onto)")
    mytp.set_text_hits("tickles")
    mytp.set_z_depth(zx.MAP_DEPTH_LAVA)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()

def init():
    lava_init(name="lava1", text_name="broiling lava",
            tiles=[
                "lava1.1",
                "lava1.2",
                "lava1.3",
                "lava1.4",
                "lava1.5",
                "lava1.6",
                "lava1.7",
                "lava1.8",
                "lava1.9",
                "lava1.10",
                "lava1.11",
                "lava1.12",
                "lava1.13",
                "lava1.14",
                "lava1.15",
                "lava1.16",
                ])
init()
