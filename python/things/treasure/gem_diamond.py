import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "1d300+100")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_collected_as_gold(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_stone(self, True)
    my.tp_set_is_treasure_class_c(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_long_text_description(self, "A glistening diamond. Like a spark of white fire in the darkness. Is there anything more precious. Probably. Grab it quick anyway.")
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_rarity(self, my.RARITY_UNCOMMON)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Just a lonely diamond.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name + ".1", is_dir_none=True, delay_ms=200)
    my.tp_set_tile(self, tile=name + ".2", is_dir_none=True, delay_ms=50)
    my.tp_set_tile(self, tile=name + ".3", is_dir_none=True, delay_ms=50)
    my.tp_set_tile(self, tile=name + ".1", is_dir_none=True, delay_ms=200)
    my.tp_set_tile(self, tile=name + ".2", is_dir_none=True, delay_ms=300)
    my.tp_set_tile(self, tile=name + ".3", is_dir_none=True, delay_ms=300)
    my.tp_set_tile(self, tile=name + ".1", is_dir_none=True, delay_ms=200)
    my.tp_set_tile(self, tile=name + ".2", is_dir_none=True, delay_ms=300)
    my.tp_set_tile(self, tile=name + ".3", is_dir_none=True, delay_ms=300)
    my.tp_set_tile(self, tile=name + ".1", is_dir_none=True, delay_ms=200)
    my.tp_set_tile(self, tile=name + ".2", is_dir_none=True, delay_ms=50)
    my.tp_set_tile(self, tile=name + ".3", is_dir_none=True, delay_ms=50)

    my.tp_update(self)


def init():
    tp_init(name="gem_diamond", text_name="diamond")


init()
