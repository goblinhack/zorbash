import my
import tp


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_msg(me, "The thunderstone explodes into fragments.")
    my.level_spawn_thing_at(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_thing_at(me, "fire")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_dead(me, "exploded")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_use(owner, me, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("me    {} {:X}".format(my.thing_name_get(me), me))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))
    my.level_spawn_thing_at(target, "explosion_major")
    my.level_spawn_using_items_radius_range(owner, me, target, "explosion_destroy_floor")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.blast_max_radius(self, 4)
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.environ_avoids_fire(self, 20)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.is_able_to_fall(self, True)
    my.is_auto_throw(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_stone(self, True)
    my.is_throwable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_used_when_thrown(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 10)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "This most dangerous stone can devistate any are where it is thrown. Be careful where you drop it...")
    my.text_short_description(self, "A harmless looking brownish stone.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="diamond_solid", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="thunderstone", text_long_name="thunderstone", text_short_name="thunderstone")


init()
