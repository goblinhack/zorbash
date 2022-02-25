import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.collision_hit_priority(self, 2)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated_can_vflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_show_outlined(self, True)
    my.health_initial_dice(self, "1d4")
    my.is_able_to_fall(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_flat(self, True)
    my.is_interesting(self, True)
    my.is_red_blood(self, True)
    my.is_removeable_if_out_of_slots(self, True)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.text_a_or_an(self, "a")
    my.text_description(self, "An artwork comprised mainly of blood.")
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name + ".100", is_hp_100_percent=True)
    my.tile(self, tile=name + ".75", is_hp_75_percent=True)
    my.tile(self, tile=name + ".50", is_hp_50_percent=True)
    my.tile(self, tile=name + ".25", is_hp_25_percent=True)

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
