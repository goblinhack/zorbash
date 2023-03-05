import my
import tp


def gold_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 6)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shadow_very_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gold_value_dice(self, "50+1d50")
    my.is_able_to_fall(self, True)
    my.is_auto_collect_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_collected_as_gold(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_C(self, True)
    my.is_treasure(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_treasure_type(self, True)
    my.light_color(self, "yellow")
    my.light_dist(self, 1)
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "an")
    my.text_description_long(self, "Lots of gold coins.")
    my.text_description_short(self, "Lots of gold coins.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".1", is_dir_none=True)

    my.tp_update(self)


def init():
    gold_init(name="gold5", text_long_name="lots of gold coins", text_short_name="gold coins")


init()
