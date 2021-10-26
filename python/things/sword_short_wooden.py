import zx
import tp

def on_use(owner, item, target, x, y):
    #zx.con("owner   {} {:08X}".format(zx.thing_get_name(owner), owner))
    #zx.con("item    {} {:08X}".format(zx.thing_get_name(item), item))
    #zx.con("target  {} {:08X}".format(zx.thing_get_name(target), target))
    zx.thing_sound_play_channel(owner, zx.CHANNEL_WEAPON, "sword_swing{}".format(zx.non_pcg_randint(1,3)))
    damage = zx.thing_get_damage_melee(item)
    enchant = zx.thing_get_enchant(item) * 2
    zx.thing_set_current_damage(owner, damage + enchant)

def init_swing(name):
    mytp = tp.Tp(name)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated_can_vflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_attack_anim(True)
    mytp.set_gfx_dead_anim(False)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_tmp_thing(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy wooden mechanism of justice.")
    mytp.set_z_depth(zx.MAP_DEPTH_WEAPON)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 10
    mytp.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    mytp.set_tile(tile=name + "_left.6", delay_ms=delay, is_dir_left=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    mytp.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    mytp.set_tile(tile=name + "_left.6", delay_ms=delay, is_dir_right=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    mytp.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    mytp.set_tile(tile=name + "_up.6", delay_ms=delay, is_dir_up=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    mytp.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    mytp.set_tile(tile=name + "_up.6", delay_ms=delay, is_dir_down=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)

    mytp.update()

def init_carry(name):
    mytp = tp.Tp(name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_equip_carry_anim(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy wooden mechanism of justice.")
    mytp.set_z_depth(zx.MAP_DEPTH_WEAPON)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 550
    mytp.set_tile(tile=name + ".1", delay_ms=delay)
    mytp.set_tile(tile=name + ".2", delay_ms=delay)

    mytp.update()

def init_weapon(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_melee_dice("1d4")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("sword_short_wooden_swing")
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_gold_value_dice("25")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_wooden(True)
    mytp.set_is_loggable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_sword(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_weapon(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("A wooden short sword. Ideal for play fighting and not much else.")
    mytp.set_on_use_do("sword_short_wooden.on_use()")
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(0)
    mytp.set_stat_defence(0)
    mytp.set_stat_strength(0)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Thy wooden means of justice.")
    mytp.set_text_enchant("increase damage by 2")
    mytp.set_equip_carry_anim("sword_short_wooden_carry")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1")

    mytp.update()

def init():
    init_swing(name="sword_short_wooden_swing")
    init_carry(name="sword_short_wooden_carry")
    init_weapon(name="sword_short_wooden", text_name="wooden short sword", short_text_name="wooden short sword")

init()
