import zx
import tp


def skill_devoted_thrust_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_is_skill(True)
    x.set_text_description("Devoted thrust.")
    x.set_long_text_description("Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away.")
    x.set_tile(tile=name)
    x.set_tile(tile=name + "_activated")
    x.update()

def init():
    skill_devoted_thrust_init(name="skill_devoted_thrust", text_name="devoted thrust")

init()
