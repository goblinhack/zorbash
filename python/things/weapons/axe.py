import my
import tp


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_get_name(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_get_name(item), item))
    # my.con("target  {} {:X}".format(my.thing_get_name(target), target))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")
    damage = my.thing_get_damage_melee(item)
    enchant = my.thing_get_enchant(item)
    my.thing_set_current_damage(owner, damage + enchant)


def init_weapon(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(mytp, 10)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_damage_melee_chance_d1000(mytp, 1000)
    my.tp_set_damage_melee_dice(mytp, "1d10+1")
    my.tp_set_equip_carry_anim(mytp, "axe_carry")
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "axe_swing")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "150")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_auto_equipped(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_enchantable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_metal(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_is_weapon_class_b(mytp, True)
    my.tp_set_is_weapon(mytp, True)
    my.tp_set_is_wooden(mytp, True)
    my.tp_set_item_height(mytp, 6)
    my.tp_set_item_width(mytp, 6)
    my.tp_set_long_text_description(mytp, "A gleaming wooden handled axe. It's edge is hungry.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 15)
    my.tp_set_on_use_do(mytp, "me.on_use()")
    my.tp_set_rarity(mytp, my.RARITY_UNCOMMON)
    my.tp_set_stat_att_mod(mytp, 1)  # means +1 per enchant
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Thy choppy means of justice.")
    my.tp_set_text_enchant(mytp, "+1 damage")
    my.tp_set_text_enchant(mytp, "increase damage by 1")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name + ".1")

    my.tp_update(mytp, )


def init():
    init_weapon(name="axe", text_name="single headed axe", short_text_name="short axe")


init()
