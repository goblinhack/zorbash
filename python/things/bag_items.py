import zx
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_bag(True)
    mytp.set_is_burnable(True)
    mytp.set_is_temporary_bag(True)
    mytp.set_long_text_description("Items found.")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Items found.")

    mytp.set_tile(tile="bag", delay_ms=1000)
    mytp.update()

def init():
    tp_init(name="bag_items", text_name="Items found")

init()
