import my
import tp


def gold_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_very_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "12+1d12")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_auto_collect_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_collected_as_gold(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_gold(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_metal(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_treasure_class_b(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_light_color(self, "yellow")
    my.tp_set_light_power(self, 1)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(self, "an")
    my.tp_set_text_description(self, "Some gold goins.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name + ".1", is_dir_none=True)

    my.tp_update(self)


def init():
    gold_init(name="gold3", text_name="gold coins")


init()
