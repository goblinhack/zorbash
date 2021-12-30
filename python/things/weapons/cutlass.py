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


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_melee_chance_d1000(1000)
    mytp.set_damage_melee_dice("1d10+1")
    mytp.set_equip_carry_anim("cutlass_carry")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("cutlass_swing")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gold_value_dice("100")
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
    mytp.set_is_sword(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_weapon_class_b(True)
    mytp.set_is_weapon(True)
    mytp.set_item_height(5)
    mytp.set_item_width(5)
    mytp.set_long_text_description("A gleaming cutlass. Ideal for the entry level pirate.")
    mytp.set_on_use_do("me.on_use()")
    mytp.set_attack_bonus(10)  # 10, means no bonus
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy curved and pointy means of justice. Aar.")
    mytp.set_text_enchant("+1 damage")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name)

    mytp.update()


def init():
    tp_init(name="cutlass", text_name="cutlass", short_text_name="cutlass")


init()
