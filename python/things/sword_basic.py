import zx
import tp
import random

def on_use(owner, item, target, x, y):
    #zx.con("owner   {} {:08X}".format(zx.thing_get_name(owner), owner))
    #zx.con("item    {} {:08X}".format(zx.thing_get_name(item), item))
    #zx.con("target  {} {:08X}".format(zx.thing_get_name(target), target))
    zx.sound_play_channel_at(zx.CHANNEL_WEAPON, "sword_swing{}".format(random.randint(1,3)), x, y)

def init_swing(name):
    x = tp.Tp(name)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_animated_can_vflip(True)
    x.set_gfx_attack_anim(True)
    x.set_gfx_dead_anim(False)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_moveable(True)
    x.set_text_a_or_an("a");
    x.set_text_description("Thy shining pointy mechanism of justice.")
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 10
    x.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_left=True)
    x.set_tile(tile=name + "_left.6", delay_ms=delay, is_dir_left=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    x.set_tile(tile=name + "_left.1", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.2", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.3", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.4", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.5", delay_ms=delay, is_dir_right=True)
    x.set_tile(tile=name + "_left.6", delay_ms=delay, is_dir_right=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    x.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_up=True)
    x.set_tile(tile=name + "_up.6", delay_ms=delay, is_dir_up=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)
    x.set_tile(tile=name + "_up.1", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.2", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.3", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.4", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.5", delay_ms=delay, is_dir_down=True)
    x.set_tile(tile=name + "_up.6", delay_ms=delay, is_dir_down=True,
               is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()

def init_carry(name):
    x = tp.Tp(name)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gfx_weapon_carry_anim(True)
    x.set_is_able_to_fall(False)
    x.set_is_active(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_moveable(True)
    x.set_text_a_or_an("a");
    x.set_text_description("Thy shining pointy mechanism of justice.")
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 550
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)

    x.update()

def init_weapon(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_bag_item_height(4)
    x.set_bag_item_width(4)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_melee_dice("1d8+1")
    x.set_gfx_anim_attack("sword_basic_swing")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_collectable(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_droppable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_moveable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_treasure(True)
    x.set_is_treasure_class_b(True)
    x.set_is_weapon(True)
    x.set_long_text_description("A gleaming entry-level sword. Ideal for beginners or the occasional weekend dungeoneer.")
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(0)
    x.set_stat_defence(0)
    x.set_stat_strength(0)
    x.set_on_use_do("sword_basic.on_use()")
    x.set_text_a_or_an("a");
    x.set_text_description("Thy pointy means of justice.")
    x.set_weapon_carry_anim("sword_basic_carry")
    x.set_weapon_use_delay_hundredths(5)
    x.set_weapon_use_distance(1)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1")

    x.update()

def init():
    init_swing(name="sword_basic_swing")
    init_carry(name="sword_basic_carry")
    init_weapon(name="sword_basic", text_name="short sword", short_text_name="short sword")

init()
