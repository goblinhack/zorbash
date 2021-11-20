import my
import tp

def on_use(owner, item, target, x, y):
    #my.con("owner   {} {:08X}".format(my.thing_get_name(owner), owner))
    #my.con("item    {} {:08X}".format(my.thing_get_name(item), item))
    #my.con("target  {} {:08X}".format(my.thing_get_name(target), target))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "sword_swing{}".format(my.non_pcg_randint(1,3)))
    damage = my.thing_get_damage_melee(item)
    enchant = my.thing_get_enchant(item)
    my.thing_set_current_damage(owner, damage + enchant)

def init_weapon(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_melee_dice("1d10+1")
    mytp.set_equip_carry_anim("axe_basic_carry")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("axe_basic_swing")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gold_value_dice("150")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_auto_equipped(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_metal(True)
    mytp.set_is_moveable(True)
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_weapon(True)
    mytp.set_item_height(6)
    mytp.set_item_width(6)
    mytp.set_long_text_description("A gleaming axe. It's edge is hungry.")
    mytp.set_on_use_do("axe_basic.on_use()")
    mytp.set_stat_attack_bonus(10) # 10, means no bonus
    mytp.set_stat_constitution(0)
    mytp.set_stat_armor_class(0)
    mytp.set_stat_strength(0)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy choppy means of justice.")
    mytp.set_text_enchant("+1 damage")
    mytp.set_text_enchant("increase damage by 1")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1")

    mytp.update()

def init():
    init_weapon(name="axe_basic", text_name="single headed axe", short_text_name="short axe")

init()
