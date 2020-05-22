import zx
import tp


def chasm_init(name, real_name, tiles=[], left_tiles=[]):
    x = tp.Tp(name, real_name)

    x.set_a_or_an("a");
    x.set_ai_obstacle(True)
    x.set_is_chasm(True)
    x.set_is_hazard(True)
    x.set_is_interesting(True)
    x.set_z_depth(zx.MAP_DEPTH_CHASM)

    delay = 1250
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    chasm_init(name="chasm1", real_name="chasm",
            tiles=[
                "chasm1.1",
                "chasm1.2",
                "chasm1.3",
                "chasm1.4",
                "chasm1.5",
                "chasm1.6",
                "chasm1.7",
                "chasm1.8",
                "chasm1.9",
                "chasm1.10",
                "chasm1.11",
                "chasm1.12",
                "chasm1.13",
                "chasm1.14",
                "chasm1.15",
                "chasm1.16",
                ])
init()
