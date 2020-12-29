import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_is_bag(True)
    x.set_is_temporary_bag(True)
    x.set_is_combustible(True)
    x.set_long_text_description("Items found.")
    x.set_text_a_or_an("a");
    x.set_text_description("Items found")

    x.set_tile(tile="bag", delay_ms=1000)
    x.update()

def init():
    tp_init(name="bag_items", text_name="Items found")

init()
