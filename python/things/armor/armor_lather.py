import my
import tp

mytp = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_slippery")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_slippery")


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The armor glows.")
    my.thing_incr_stat_def(me, 1)


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(mytp, 5)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_enchant_max(mytp, 5)
    my.tp_set_equip_carry_anim(mytp, "armor_lather_carry")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "5")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_armor(mytp, True)
    my.tp_set_is_auto_equipped(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_enchantable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_treasure_class_a(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "Lathered armor. Not to be confused with leather armor, this armor is leathery with a fine soapy film to help you wriggle out of sticky situations. Apart from that it is mostly useless.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 5)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_enchant_do(mytp, "me.on_enchant()")
    my.tp_set_on_equip_do(mytp, "me.on_equip()")
    my.tp_set_on_unequip_do(mytp, "me.on_unequip()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stat_def(mytp, 11)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Lathered armor.")
    my.tp_set_text_enchant(mytp, "+1 AC")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="armor_lather",
        text_name="lathered armor",
        short_text_name="lathered armor",
    )


init()
