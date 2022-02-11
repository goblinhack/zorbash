import my
import tp

mytp = None


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
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_equip_carry_anim(mytp, "boots_fluffy_carry")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "50")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_boots(mytp, True)
    my.tp_set_is_auto_equipped(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_biome_swamp(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_noise_on_jumping(mytp, -50)
    my.tp_set_noise_on_moving_or_being_carried(mytp, -50)
    my.tp_set_is_enchantable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_treasure_class_a(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "Fluffy boots. Keeps your feet warm and lowers your noise footprint. Pun intended.")
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_enchant_do(mytp, "me.on_enchant()")
    my.tp_set_on_equip_do(mytp, "me.on_equip()")
    my.tp_set_on_unequip_do(mytp, "me.on_unequip()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Fluffy boots.")
    my.tp_set_text_enchant(mytp, "-10 decibels")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="boots_fluffy",
        text_name="fluffy boots",
        short_text_name="fluffy boots",
    )


init()
