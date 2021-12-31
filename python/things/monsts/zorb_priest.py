import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(leader):
        my.topcon("The zorblin priest prays for the departed!")


def on_born(me, x, y):
    my.thing_carry(me, "wand_fire")


def tp_init(name, text_name):
    mytp = zorb_all.tp_init(name, text_name)
    mytp.set_long_text_description_extra("This particular zorblin is well trained in the martial arts and prefers to fight bare fisted.")
    mytp.set_on_death_of_a_follower_do("me.on_death_of_a_follower()")
    mytp.set_on_born_do("me.on_born()")
    mytp.set_text_description("A master in physical punishment.")
    mytp.set_stat_strength(12)
    mytp.set_distance_avoid(5)
    mytp.set_text_hits("hits")
    mytp.set_gfx_anim_use("attack_punch")
    mytp.set_damage_natural_attack_type("punch")
    mytp.set_damage_natural_attack_dice("2d6+2")
    mytp.set_health_initial_dice("2d8+4")
    mytp.set_is_intelligent(True)

    delay = 300
    mytp.set_tile(tile=name + ".1", delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    mytp.update()


def init():
    tp_init(name="zorb_priest", text_name="zorblin priest")


init()
