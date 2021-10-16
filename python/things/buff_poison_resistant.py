import zx
import tp

mytp = None

def on_tick(owner, item, x, y):
    poison = zx.thing_get_poison(item)
    if poison != 0:
        zx.topcon("%%fg=green$The poison has no effect on you!")
        zx.thing_set_poison(owner, 0)
    return True

def buff_poison_resistant_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)
    mytp.set_is_loggable(True)
    mytp.set_is_buff(True)
    mytp.set_text_buff("You are poison resistant");
    mytp.set_long_text_description("Poison cannot harm you.")
    mytp.set_on_tick_do("buff_poison_resistant.on_tick()")
    mytp.set_text_description("Poison resistant buff.")
    mytp.set_tile(tile="buff_poison_resistant")
    mytp.update()

def init():
    buff_poison_resistant_init(name="buff_poison_resistant", text_name="poison resistant")

init()
