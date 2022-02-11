import my
import tp


def explode(me, x, y):
    my.thing_msg(me, "The enchantstone explodes.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_at_thing(me, "fire")
    my.thing_dead(me, "exploded")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(self, 5)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_environ_avoids_fire(self, 10)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_enchantstone(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_stone(self, True)
    my.tp_set_is_throwable(self, True)
    my.tp_set_is_treasure_class_c(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Use this magical stone to bestow powers on other items you carry.")
    my.tp_set_noise_on_moving_or_being_carried(self, 10)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_fall_do(self, "me.on_fall()")
    my.tp_set_on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_on_you_are_on_fire_do(self, "me.on_fire()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A glowing enchantstone.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="enchantstone", text_name="enchantstone", short_text_name="enchantstone")


init()
