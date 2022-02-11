import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"door_hit{my.non_pcg_randint(1, 2)}")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_break")


def on_open(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_open")


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_capacity_height(mytp, 8)
    my.tp_set_capacity_width(mytp, 8)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_bag_item_container(mytp, True)
    my.tp_set_is_bag_item_not_stackable(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_carrier_of_treasure_class_a(mytp, True)
    my.tp_set_is_carrier_of_treasure_class_b(mytp, True)
    my.tp_set_is_carrier_of_treasure_class_c(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item_carrier(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_metal(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_openable(mytp, True)
    my.tp_set_is_treasure_chest(mytp, True)
    my.tp_set_is_treasure_class_a(mytp, True)
    my.tp_set_is_treasure_class_b(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_wooden(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "A small treasure chest.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 1)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_death_drop_all_items(mytp, True)
    my.tp_set_on_death_is_open(mytp, True)
    my.tp_set_on_open_do(mytp, "me.on_open()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A small treasure chest.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile="chest1", delay_ms=1000)
    my.tp_set_tile(mytp, tile=name + ".open", is_open=True)
    my.tp_set_tile(mytp, tile=name + ".open", is_dead=True)
    my.tp_update(mytp, )


def init():
    tp_init(name="chest1", text_name="small treasure chest")


init()
