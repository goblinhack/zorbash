import zx
import tp
import random


def explode(me, x, y):
    zx.thing_msg(me, "The oil filled barrel explodes. Health and safety have been alerted.")
    zx.level_spawn_at_thing(me, "explosion_major")
    zx.level_spawn_fire_around_thing(me, "fire")
    zx.level_spawn_at_thing(me, "fire")
    zx.thing_killed(me, "exploded")

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    explode(me, x, y)

def on_fire(me, x, y):
    explode(me, x, y)

def on_fall(me, x, y):
    explode(me, x, y)

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_obstacle(True)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_hit_priority(2)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_shown_in_bg(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_hates_fire(100)
    x.set_is_able_to_fall(True)
    x.set_is_active(True) # So it can interact with fire
    x.set_is_always_hit(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_barrel(True)
    x.set_is_burnable(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_floor_deco(False) # Else it can be placed next to lava and starts a firestorm
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_very_combustible(True)
    x.set_normal_placement_rules(True)
    x.set_on_fall_do("barrel.on_fall()")
    x.set_on_fire_do("barrel.on_fire()")
    x.set_on_hit_do("barrel.on_hit()")
    x.set_text_a_or_an("the")
    x.set_text_description("A barrel of oil. Why? Don't ask.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    x.set_tile(tile=name)

    x.update()

def init():
    tp_init(name="barrel", text_name="barrel")

init()
