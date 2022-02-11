import my
import tp

mytp = None


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The scale armor glows.")
    my.thing_incr_stat_def(me, 2)


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(mytp, 100)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_enchant_max(mytp, 10)
    my.tp_set_equip_carry_anim(mytp, "armor_lime_scale_carry")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "50")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_armor(mytp, True)
    my.tp_set_is_auto_equipped(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_crushable(mytp, True)
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
    my.tp_set_long_text_description(mytp, "Lime scale armor. Very tough while it lasts. Which is not long...")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 20)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_enchant_do(mytp, "me.on_enchant()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stat_def(mytp, 15)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Lime scale mail armor.")
    my.tp_set_text_enchant(mytp, "+2 AC")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="armor_lime_scale",
        text_name="lime scale armor",
        short_text_name="lime scale armor",
    )


init()
