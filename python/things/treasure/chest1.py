import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"door_hit{my.non_pcg_randint(1, 2)}")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_break")


def on_open(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_open")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_capacity_height(self, 8)
    my.tp_set_capacity_width(self, 8)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_bag_item_container(self, True)
    my.tp_set_is_bag_item_not_stackable(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_carrier_of_treasure_class_a(self, True)
    my.tp_set_is_carrier_of_treasure_class_b(self, True)
    my.tp_set_is_carrier_of_treasure_class_c(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item_carrier(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_metal(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_openable(self, True)
    my.tp_set_is_treasure_chest(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_treasure_class_b(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "A small treasure chest.")
    my.tp_set_noise_on_moving_or_being_carried(self, 1)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_death_drop_all_items(self, True)
    my.tp_set_on_death_is_open(self, True)
    my.tp_set_on_open_do(self, "me.on_open()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A small treasure chest.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile="chest1", delay_ms=1000)
    my.tp_set_tile(self, tile=name + ".open", is_open=True)
    my.tp_set_tile(self, tile=name + ".open", is_dead=True)
    my.tp_update(self)


def init():
    tp_init(name="chest1", text_name="small treasure chest")


init()
