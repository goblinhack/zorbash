import my
import tp


def on_lifespan_tick(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "One of your torches fizzles out.")


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_charge_count(4)
    mytp.set_collision_hit_priority(1)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_glows(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_burnable(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_hittable(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_tickable(True)  # for pushing and falling
    mytp.set_is_torch(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_wooden(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_lifespan_dice("1d300+100")
    mytp.set_light_color("orange")
    mytp.set_light_power(2)
    mytp.set_long_text_description("A bundle of torches to light the way. Be warned, they do burn out slowly. Don't find yourself lost in the dark...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_lifespan_tick_do("me.on_lifespan_tick()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A small beacon of light in this blighted place.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 100
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()


def init():
    tp_init(
        name="torch",
        text_name="torch",
        tiles=[
            "torch.1",
            "torch.2",
            "torch.3",
            "torch.4",
            "torch.5",
        ],
    )


init()
