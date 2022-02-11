import my
import tp

self = None


def on_equip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your feet are nice and warm!")


def on_unequip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your feet are cold again!")


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The boots become yet more fluffy and quiet.")
    my.thing_incr_noise(me, -10)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_equip_carry_anim(self, "boots_fluffy_carry")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "50")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_boots(self, True)
    my.tp_set_is_auto_equipped(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_noise_on_jumping(self, -50)
    my.tp_set_noise_on_moving_or_being_carried(self, -50)
    my.tp_set_is_enchantable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Fluffy boots. Keeps your feet warm and lowers your noise footprint. Pun intended.")
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_enchant_do(self, "me.on_enchant()")
    my.tp_set_on_equip_do(self, "me.on_equip()")
    my.tp_set_on_unequip_do(self, "me.on_unequip()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Fluffy boots.")
    my.tp_set_text_enchant(self, "-10 decibels")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="boots_fluffy",
        text_name="fluffy boots",
        short_text_name="fluffy boots",
    )


init()
