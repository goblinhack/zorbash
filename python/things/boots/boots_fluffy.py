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
    mytp.set_equip_carry_anim("boots_fluffy_carry")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gold_value_dice("50")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_boots(True)
    mytp.set_is_auto_equipped(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_biome_swamp(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_noise_on_jumping(-50)
    mytp.set_noise_on_moving_or_being_carried(-50)
    mytp.set_is_enchantable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_burnable(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Fluffy boots. Keeps your feet warm and lowers your noise footprint. Pun intended.")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("me.on_enchant()")
    mytp.set_on_equip_do("me.on_equip()")
    mytp.set_on_unequip_do("me.on_unequip()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Fluffy boots.")
    mytp.set_text_enchant("-10 decibels")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name)

    mytp.update()


def init():
    tp_init(
        name="boots_fluffy",
        text_name="fluffy boots",
        short_text_name="fluffy boots",
    )


init()
