import my
import tp


def on_lifespan_tick(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "One of your torches fizzles out.")


def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    my.tp_set_charge_count(mytp, 10)
    my.tp_set_collision_hit_priority(mytp, 1)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_flickers(mytp, True)
    my.tp_set_gfx_glows(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # for pushing and falling
    my.tp_set_is_torch(mytp, True)
    my.tp_set_is_treasure_class_a(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_wooden(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_lifespan_dice(mytp, "1d300+100")
    my.tp_set_light_color(mytp, "orange")
    my.tp_set_light_power(mytp, 1)
    my.tp_set_long_text_description(mytp, "A bundle of torches to light the way. Be warned, they do burn out slowly. Don't find yourself lost in the dark...")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 1)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_lifespan_tick_do(mytp, "me.on_lifespan_tick()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A small beacon of light in this blighted place.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    delay = 100
    for t in tiles:
        my.tp_set_tile(mytp, tile=t, delay_ms=delay)

    my.tp_update(mytp, )


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
