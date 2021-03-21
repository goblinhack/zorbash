import zx
import tp

def on_use(me, what, target, x, y):
    zx.tp_spawn_radius_range(me, what, "skill_devoted_thrust_effect")
    #zx.topcon("me     {} {}".format(zx.thing_get_name(me), zx.thing_get_health(me)))
    #zx.topcon("what   {} {}".format(zx.thing_get_name(what), zx.thing_get_health(what)))
    #zx.topcon("target {} {}".format(zx.thing_get_name(target), zx.thing_get_health(target)))
    bonus = int(zx.thing_get_stamina(me) / 2)
    zx.topcon("%%fg=yellow$You strike with a mighty thrust bonus of {}%%fg=reset$".format(bonus))
    zx.thing_incr_current_damage(me, bonus)
    zx.thing_decr_stamina(me, bonus)

def skill_devoted_thrust_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_skill(True)
    x.set_long_text_description("Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away.")
    x.set_on_use_do("skill_devoted_thrust.on_use()")
    x.set_text_description("Devoted thrust.")
    x.set_tile(tile=name)
    x.set_tile(tile=name + "_activated")
    x.update()

def init():
    skill_devoted_thrust_init(name="skill_devoted_thrust", text_name="devoted thrust")

init()
