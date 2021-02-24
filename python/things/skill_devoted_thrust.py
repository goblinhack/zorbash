import zx
import tp


def skill_devoted_thrust_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_is_skill(True)
    x.set_text_description("Devoted thrust.")
    x.set_long_text_description("Uses half of your stamina points up in one mighty strike.")
    x.set_tile(tile=name)
    x.update()

def init():
    skill_devoted_thrust_init(name="skill_devoted_thrust", text_name="devoted thrust")

init()
