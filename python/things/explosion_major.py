import zx
import tp

def attack(me, thing):
    if zx.thing_possible_to_attack(me, thing):
        if thing != me:
            zx.thing_hit(me, thing)

def on_death(me, x, y):
    zx.thing_sound_play_channel(me,  zx.CHANNEL_EXPLOSION, "explosion_d")

    target_x, target_y = zx.thing_get_coords(me)
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            for thing in zx.level_get_all(me, target_x + dx, target_y + dy):
                attack(me, thing)

def tp_init(name):
    x = tp.Tp(name, "huge explosion")
    x.set_damage_melee_dice("2d6")
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(False)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(False)
    x.set_is_explosion(True)
    x.set_is_floating(True)
    x.set_is_interesting(False)
    x.set_is_loggable_for_important_stuff(False)
    x.set_is_loggable_for_unimportant_stuff(False)
    x.set_light_color("yellow")
    x.set_light_strength(4)
    x.set_on_death_do("explosion_major.on_death()")
    x.set_text_hits("blasts")
    x.set_z_depth(zx.MAP_DEPTH_EXPLOSION_MAJOR)
    x.set_z_prio(zx.MAP_PRIO_INFRONT)

    x.set_tile(tile=name + ".1", delay_ms=50)
    x.set_tile(tile=name + ".2", delay_ms=50)
    x.set_tile(tile=name + ".3", delay_ms=50)
    x.set_tile(tile=name + ".4", delay_ms=50)
    x.set_tile(tile=name + ".5", delay_ms=50)
    x.set_tile(tile=name + ".6", delay_ms=50)
    x.set_tile(tile=name + ".7", delay_ms=50)
    x.set_tile(tile=name + ".8", delay_ms=50)
    x.set_tile(tile=name + ".9", delay_ms=50)
    x.set_tile(tile=name + ".10", delay_ms=50)
    x.set_tile(tile=name + ".11", delay_ms=50)
    x.set_tile(tile=name + ".12", delay_ms=50)
    x.set_tile(tile=name + ".13", delay_ms=50)
    x.set_tile(tile=name + ".14", delay_ms=50)
    x.set_tile(tile=name + ".15", delay_ms=50)
    x.set_tile(tile=name + ".16", delay_ms=50, is_end_of_anim = True, is_dead_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="explosion_major")

init()
