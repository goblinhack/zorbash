import my
import tp

mytp = None

def on_tick(owner, item, x, y):
    necrosis = my.thing_get_necrotized_amount(owner)
    if necrosis == 0:
        my.topcon("You are no longer rotting any more than usua..")
        my.thing_defeated(item, "end of debuff")
        return True
    # Too noisy
    # my.topcon("%%fg=yellow$You are necrotized!%%fg=reset$")
    return True

def tp_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    mytp.set_is_debuff(True)
    mytp.set_is_loggable(True)
    mytp.set_long_text_description("Your skin is peeling off!")
    mytp.set_on_tick_do("debuff_necrotized.on_tick()")
    mytp.set_text_debuff("You are rotting!");
    mytp.set_text_description("Rotting debuff.")
    mytp.set_tile(tile="debuff_necrotized")
    # mytp.set_z_prio(my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    mytp.update()

def init():
    tp_init(name="debuff_necrotized", text_name="rotting away")

init()
