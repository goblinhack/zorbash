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
    my.tp_set_break_chance_d10000(mytp, 10)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 10)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_damage_melee_chance_d1000(mytp, 1000)
    my.tp_set_damage_melee_dice(mytp, "1d8+1")
    my.tp_set_equip_carry_anim(mytp, "sword1_carry")
    my.tp_set_gfx_animated_can_hflip(mytp, True)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_anim_use(mytp, "sword1_swing")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "100")
    my.tp_set_is_able_to_fall(mytp, True)
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
    my.tp_set_is_metal(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_sword(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_is_weapon_class_a(mytp, True)
    my.tp_set_is_weapon(mytp, True)
    my.tp_set_item_height(mytp, 5)
    my.tp_set_item_width(mytp, 5)
    my.tp_set_long_text_description(mytp, "A gleaming entry-level short sword. Ideal for beginners or the occasional weekend dungeoneer.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 10)
    my.tp_set_on_use_do(mytp, "me.on_use()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Thy pointy means of justice.")
    my.tp_set_text_enchant(mytp, "+1 damage")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(name="sword1", text_name="short sword", short_text_name="short sword")


init()
