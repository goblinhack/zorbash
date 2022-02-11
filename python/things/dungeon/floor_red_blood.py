import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(self, 2)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated_can_vflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "1d4")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_red_blood(self, True)
    my.tp_set_is_removeable_if_out_of_slots(self, True)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_nutrition_dice(self, "1d4")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "An artwork comprised mainly of blood.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name + ".100", is_hp_100_percent=True)
    my.tp_set_tile(self, tile=name + ".75", is_hp_75_percent=True)
    my.tp_set_tile(self, tile=name + ".50", is_hp_50_percent=True)
    my.tp_set_tile(self, tile=name + ".25", is_hp_25_percent=True)

    my.tp_update(self)


def init():
    tp_init(name="floor_red_blood1", text_name="pool of blood")
    tp_init(name="floor_red_blood2", text_name="pool of blood")
    tp_init(name="floor_red_blood3", text_name="pool of blood")
    tp_init(name="floor_red_blood4", text_name="pool of blood")
    tp_init(name="floor_red_blood5", text_name="pool of blood")
    tp_init(name="floor_red_blood6", text_name="pool of blood")
    tp_init(name="floor_red_blood7", text_name="pool of blood")
    tp_init(name="floor_red_blood8", text_name="pool of blood")


init()
