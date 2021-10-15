import zx
import tp

mytp = None

def on_use(owner, debuff, target, x, y):
    zx.topcon("%%fg=green$You are immune to poison!")

def buff_poison_resistant_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)
    mytp.set_is_loggable(True)
    mytp.set_is_buff(True)
    mytp.set_text_buff("You are poison resistant");
    mytp.set_long_text_description("Poison cannot harm you.")
    mytp.set_on_use_do("buff_poison_resistant.on_use()")
    mytp.set_text_description("Poison resistant buff.")
    mytp.set_tile(tile="buff_poison_resistant")
    mytp.update()

def init():
    buff_poison_resistant_init(name="buff_poison_resistant", text_name="poison resistant")

init()
