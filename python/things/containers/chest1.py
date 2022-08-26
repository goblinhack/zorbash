import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"door_hit{my.non_pcg_randint(1, 2)}")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_break")


def on_open(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_open")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.capacity_height(self, 8)
    my.capacity_width(self, 8)
    my.collision_hit_priority(self, 6)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_bag_item_container(self, True)
    my.is_bag_item_not_stackable(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_carrier_of_treasure_class_a(self, True)
    my.is_carrier_of_treasure_class_b(self, True)
    my.is_carrier_of_treasure_class_c(self, True)
    my.is_collectable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item_carrier(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.is_openable(self, True)
    my.is_treasure_chest(self, True)
    my.is_treasure_class_a(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_death_is_open(self, True)
    my.on_open_do(self, "me.on_open()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "A small treasure chest.")
    my.text_short_description(self, "A small treasure chest.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile="chest1", delay_ms=1000)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".open", is_open=True)
    my.tile(self,
            ascii_fg_char="up_triangle", ascii_bg_col_name="", ascii_fg_col_name="gold",
            tile=name + ".open", is_dead=True)
    my.tp_update(self)


def init():
    tp_init(name="chest1", text_long_name="small treasure chest", text_short_name="chest, small")


init()
