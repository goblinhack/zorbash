import zx
import tp

def on_use(me, what, target, x, y):
    zx.tp_spawn_radius_range(me, what, "skill_devoted_thrust_effect")


def skill_devoted_thrust_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_skill(True)
    x.set_long_text_description("Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away.")
    x.set_on_use_do("skill_devoted_thrust.on_use()")
    x.set_text_on_use("%%fg=yellow$You strike with a mighty thrust%%fg=reset$")
    x.set_text_description("Devoted thrust.")
    x.set_tile(tile=name)
    x.set_tile(tile=name + "_activated")
    x.update()

def init():
    skill_devoted_thrust_init(name="skill_devoted_thrust", text_name="devoted thrust")

init()
