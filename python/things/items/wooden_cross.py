import my
import tp


def on_equip(owner, me, x, y):
    my.topcon("E")
    my.thing_buff_add(owner, "buff_undead_resist")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_undead_resist")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.equip_carry_anim(self, "wooden_cross_carry")
    my.gold_value_dice(self, "1")
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
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
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 2)
    my.item_width(self, 2)
    my.long_text_description(self, "When carrying these two sticks that have been oddly combined, you somehow know that you will take only half damage from any udead attack. Not bad for some twigs. Item is equipped in the gauntlet slot.")
    my.noise_on_moving_or_being_carried(self, 5)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stat_def_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A pair of sticks.")
    my.text_enchant(self, "+1 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="wooden_cross", text_name="wooden cross", short_text_name="wooden cross")


init()
