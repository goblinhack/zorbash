import zx
import tp


def tp_init(name, short_name):
    x = tp.Tp(name)

    x.set_has_initial_health(4)
    x.set_is_boring(True)
    x.set_is_blood(True)
    x.set_short_name(short_name)
    x.set_z_depth(zx.MAP_DEPTH_BLOOD)
    
    x.set_tile(tile=name + ".100", is_hp_100_percent=True)
    x.set_tile(tile=name + ".75", is_hp_75_percent=True)
    x.set_tile(tile=name + ".50", is_hp_50_percent=True)
    x.set_tile(tile=name + ".25", is_hp_25_percent=True)

def init():
    tp_init(name="blood1", short_name="blood")
init()
