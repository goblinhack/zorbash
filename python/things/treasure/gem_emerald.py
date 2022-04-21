import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.collision_hit_priority(self, 6)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "1d200")
    my.is_able_to_fall(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_collected_as_gold(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_stone(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.long_text_description(self, "The stone of loyalty. Can't be that loyal as someone left it lying here. Best to pick it up for safe keeping.")
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_UNCOMMON)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Grass green emerald.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".1", is_dir_none=True, delay_ms=2000)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".2", is_dir_none=True, delay_ms=50)
    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name + ".3", is_dir_none=True, delay_ms=50)

    my.tp_update(self)


def init():
    tp_init(name="gem_emerald", text_name="emerald")


init()
