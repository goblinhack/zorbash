import zx
import tp
import random


def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    zx.sound_play("door_hit{}".format(random.randrange(1, 2)))

def on_death(me, x, y):
    zx.sound_play("door_break")

def on_open(me, x, y):
    zx.sound_play("door_open")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_avoids_fire(100)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_gfx_animated(True)
    x.set_gfx_health_bar_shown_only_when_injured(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_initial_dice("10d10")
    x.set_is_able_to_fall(False)
    x.set_is_always_hit(True)
    x.set_is_attackable_by_player(True)
    x.set_is_burnable(True)
    x.set_is_combustible(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_door(True)
    x.set_is_flammable(True)
    x.set_is_interesting(True)
    x.set_is_light_blocker(True)
    x.set_is_movement_blocking_hard(True)
    x.set_is_shown_on_leftbar(True)
    x.set_modifier_attack(0)
    x.set_modifier_constitution(0)
    x.set_modifier_defence(20)
    x.set_modifier_strength(0)
    x.set_normal_placement_rules(True)
    x.set_on_death_do("door.on_death()")
    x.set_on_open_do("door.on_open()")
    x.set_on_death_is_corpse(True)
    x.set_on_death_is_open(True)
    x.set_on_hit_do("door.on_hit()")
    x.set_text_a_or_an("the");
    x.set_text_description("A door covered in claw marks.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    x.set_tile(tile=name + ".100", is_hp_100_percent=True)
    x.set_tile(tile=name + ".75", is_hp_75_percent=True)
    x.set_tile(tile=name + ".50", is_hp_50_percent=True)
    x.set_tile(tile=name + ".25", is_hp_25_percent=True)
    x.set_tile(tile=name + ".dead", is_dead=True)
    x.set_tile(tile=name + ".open", is_hp_100_percent=True, is_open=True)
    x.set_tile(tile=name + ".open", is_hp_75_percent=True, is_open=True)
    x.set_tile(tile=name + ".open", is_hp_50_percent=True, is_open=True)
    x.set_tile(tile=name + ".open", is_hp_25_percent=True, is_open=True)

    x.update()

def init():
    tp_init(name="door1", text_name="door")

init()
