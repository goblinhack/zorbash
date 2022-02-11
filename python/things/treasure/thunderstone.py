import my
import tp


def explode(me, x, y):
    my.con("explode {} {:X}".format(my.thing_get_name(me), me))
    my.thing_msg(me, "The thunderstone explodes into fragments.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_at_thing(me, "fire")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_dead(me, "exploded")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_use(owner, me, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_get_name(owner), owner))
    # my.con("me    {} {:X}".format(my.thing_get_name(me), me))
    # my.con("target  {} {:X}".format(my.thing_get_name(target), target))
    my.level_spawn_at_thing(target, "explosion_major")
    my.level_spawn_using_items_radius_range(owner, me, target, "explosion_destroy_floor")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(self, 4)
    my.tp_set_collision_hit_priority(self, 5)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_environ_avoids_fire(self, 20)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_auto_throw(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
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
    my.tp_set_is_used_when_thrown(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "This most dangerous stone can devistate any are where it is thrown. Be careful where you drop it...")
    my.tp_set_noise_on_moving_or_being_carried(self, 10)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_fall_do(self, "me.on_fall()")
    my.tp_set_on_use_do(self, "me.on_use()")
    my.tp_set_on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_on_you_are_on_fire_do(self, "me.on_fire()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A harmless looking brownish stone.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="thunderstone", text_name="thunderstone", short_text_name="thunderstone")


init()
