import my
import tp


def acid_init(name, text_name, short_text_name, tiles=[], left_tiles=[]):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_damage_acid_dice("1d3+1")
    mytp.set_damage_acid_chance_d1000(1000)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_acid(True)
    mytp.set_is_hazard(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_removeable_if_out_of_slots(True)
    mytp.set_is_tickable(True) # for lifespan tick
    mytp.set_lifespan_dice("1d20+20")
    mytp.set_light_color("green")
    mytp.set_light_strength(2)
    mytp.set_text_a_or_an("")
    mytp.set_text_description("A pool of hissing acid.")
    mytp.set_text_hits("burns")
    mytp.set_z_depth(my.MAP_DEPTH_FLOOR2)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    for t in tiles:
        mytp.set_tile(tile=t)

    mytp.update()

def init():
    acid_init(name="acid1", text_name="hissing acid", short_text_name="acid",
            tiles=[
                "acid1.1",
                "acid1.2",
                "acid1.3",
                "acid1.4",
                "acid1.5",
                "acid1.6",
                "acid1.7",
                "acid1.8",
                "acid1.9",
                "acid1.10",
                "acid1.11",
                "acid1.12",
                "acid1.13",
                "acid1.14",
                "acid1.15",
                "acid1.16",
                "acid1.17",
                "acid1.18",
                "acid1.19",
                ])
init()
