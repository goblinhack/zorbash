import my
import tp


def gold_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.collision_hit_priority(self, 6)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_very_short_shadow_caster(self, True)
    my.gold_value_dice(self, "20+1d25")
    my.is_able_to_fall(self, True)
    my.is_auto_collect_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_collected_as_gold(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_immune_to_cold(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.light_color(self, "yellow")
    my.light_power(self, 1)
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "an")
    my.text_description(self, "Some gold goins.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name + ".1", is_dir_none=True)

    my.tp_update(self)


def init():
    gold_init(name="gold4", text_name="small pile of gold coins")


init()
