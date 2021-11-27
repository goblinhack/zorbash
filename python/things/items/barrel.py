import my
import tp


def explode(me, x, y):
    my.thing_msg(me, "The oil filled barrel explodes. Health and safety have been alerted.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_at_thing(me, "fire")
    my.thing_defeated(me, "exploded")

def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, necrosis, damage):
    explode(me, x, y)

def on_fire(me, x, y):
    explode(me, x, y)

def on_fall(me, x, y):
    explode(me, x, y)

def on_death(me, x, y):
    explode(me, x, y)

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_obstacle(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(1)
    mytp.set_damage_crush_dice("2d6")
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_always_hit(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_barrel(True)
    mytp.set_is_burnable(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hittable(True)
    mytp.set_is_tickable(True) # So it can interact with fire
    mytp.set_is_very_combustible(True)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("barrel.on_death()")
    mytp.set_on_fall_do("barrel.on_fall()")
    mytp.set_on_you_are_hit_do("barrel.on_you_are_hit()")
    mytp.set_on_you_are_on_fire_do("barrel.on_fire()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A barrel of oil. Why? Don't ask.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    mytp.set_tile(tile=name)

    mytp.update()

def init():
    tp_init(name="barrel", text_name="barrel")

init()
