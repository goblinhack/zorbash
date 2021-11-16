import my
import tp

mytp = None

def on_owner_set(me, owner, x, y):
    if my.thing_is_player(owner):
        my.topcon("A green glow surrounds you.")

def on_owner_unset(me, owner, x, y):
    if my.thing_is_player(owner):
        my.topcon("The green glow around you fades.")

def on_tick(owner, item, x, y):
    poison = my.thing_get_poison(item)
    if poison == 0:
        return True
    mew_poison = int(poison / 2)
    if new_poison == 0:
        my.topcon("%%fg=green$The poison has no effect on you!")
    else:
        my.topcon("%%fg=green$The poison fades from your system!")
    my.thing_set_poison(owner, new_poison)
    return True

def buff_poison_resist_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)
    mytp.set_is_loggable(True)
    mytp.set_is_buff(True)
    mytp.set_text_buff("You are mostly poison resistant");
    mytp.set_long_text_description("Poison causes you 50 percent less damage.")
    mytp.set_on_tick_do("buff_poison_resist.on_tick()")
    mytp.set_on_owner_set_do("buff_poison_resist.on_owner_set()")
    mytp.set_on_owner_unset_do("buff_poison_resist.on_owner_unset()")
    mytp.set_text_description("Poison resistant buff.")
    mytp.set_tile(tile="buff_poison_resist")
    mytp.update()

def init():
    buff_poison_resist_init(name="buff_poison_resist", text_name="poison resistant")

init()
