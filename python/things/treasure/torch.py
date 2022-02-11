import my
import tp


def on_lifespan_tick(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "One of your torches fizzles out.")


def tp_init(name, text_name, tiles=[]):
    self = tp.Tp(name, text_name)
    my.tp_set_charge_count(self, 10)
    my.tp_set_collision_hit_priority(self, 1)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_flickers(self, True)
    my.tp_set_gfx_glows(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_tickable(self, True)  # for pushing and falling
    my.tp_set_is_torch(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_lifespan_dice(self, "1d300+100")
    my.tp_set_light_color(self, "orange")
    my.tp_set_light_power(self, 1)
    my.tp_set_long_text_description(self, "A bundle of torches to light the way. Be warned, they do burn out slowly. Don't find yourself lost in the dark...")
    my.tp_set_noise_on_moving_or_being_carried(self, 1)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_lifespan_tick_do(self, "me.on_lifespan_tick()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A small beacon of light in this blighted place.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 100
    for t in tiles:
        my.tp_set_tile(self, tile=t, delay_ms=delay)

    my.tp_update(self)


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
