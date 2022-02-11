import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(mytp, 2)
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated_can_vflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_health_initial_dice(mytp, "1d4")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_green_blood(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_removeable_if_out_of_slots(mytp, True)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_nutrition_dice(mytp, "1d4")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "An artwork comprised mainly of green blood.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name + ".100", is_hp_100_percent=True)
    my.tp_set_tile(mytp, tile=name + ".75", is_hp_75_percent=True)
    my.tp_set_tile(mytp, tile=name + ".50", is_hp_50_percent=True)
    my.tp_set_tile(mytp, tile=name + ".25", is_hp_25_percent=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="floor_green_blood1", text_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood2", text_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood3", text_name="pool of fluorescent blood with bits in it")
    tp_init(name="floor_green_blood4", text_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood5", text_name="pool of yucky fluorescent blood")
    tp_init(name="floor_green_blood6", text_name="pool of icky fluorescent blood")
    tp_init(name="floor_green_blood7", text_name="pool of fluorescent blood")
    tp_init(name="floor_green_blood8", text_name="pool of fluorescent blood")


init()
