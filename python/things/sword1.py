import zx
import tp


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
    x.set_gfx_dead_anim(False)
    x.set_gfx_attack_anim(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_movable(True)
    x.set_text_a_or_an("a");
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 20
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
    x.set_gfx_weapon_carry_anim(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_active(True)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_movable(True)
    x.set_text_a_or_an("a");
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)

    delay = 550
    x.set_tile(tile=name + ".1", delay_ms=delay)
    x.set_tile(tile=name + ".2", delay_ms=delay)

    x.update()

def init_weapon(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_movable(True)
    x.set_is_weapon(True)
    x.set_stats_attack_dice("1d8+1")
    x.set_text_a_or_an("a");
    x.set_weapon_carry_anim("sword1_carry")
    x.set_weapon_use_anim("sword1_swing")
    x.set_weapon_use_delay_hundredths(5)
    x.set_weapon_use_distance(1)
    x.set_z_depth(zx.MAP_DEPTH_WEAPON)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    x.set_tile(tile=name + ".1")

    x.update()

def init():
    init_swing(name="sword1_swing")
    init_carry(name="sword1_carry")
    init_weapon(name="sword1", text_name="sword")

init()
