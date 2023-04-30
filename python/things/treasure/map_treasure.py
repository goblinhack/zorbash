import my
import tp


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The map glows. It seems full of knowledge.")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 1)
    my.environ_dislikes_fire(self, 100)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "300")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_flat(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_map_treasure(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "all levels")
    my.text_description_long(self, "When carrying this magical map you are able to see all the treasure, food and keys on the current level.")
    my.text_description_short(self, "An aged treasure map.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="cross", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="map_treasure", text_long_name="treasure map", text_short_name="treasure map")


init()
