import my
import tp


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_undead_protection")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_undead_protection")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.equip_carry_anim(self, "wooden_cross_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_gauntlet(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 2)
    my.item_width(self, 2)
    my.noise_on_dropping(self, 5)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stat_def_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DEF")
    my.text_description_long(self, "When carrying these two sticks that have been oddly combined, you somehow know that you will take only half damage from any undead attack. Necrosis and draining will also have no effect on you. Not bad for some twigs. Item is equipped in the gauntlet slot.")
    my.text_description_short(self, "A pair of sticks.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="cross", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="wooden_cross", text_long_name="wooden cross", text_short_name="wooden cross")


init()
