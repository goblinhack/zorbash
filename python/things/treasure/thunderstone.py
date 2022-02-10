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
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_blast_max_radius(4)
    mytp.set_collision_hit_priority(5)
    mytp.set_collision_hit_priority(6)
    mytp.set_environ_avoids_fire(20)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_auto_throw(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_stone(True)
    mytp.set_is_throwable(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_used_when_thrown(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("This most dangerous stone can devistate any are where it is thrown. Be careful where you drop it...")
    mytp.set_noise_on_moving_or_being_carried(10)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_fall_do("me.on_fall()")
    mytp.set_on_use_do("me.on_use()")
    mytp.set_on_you_are_hit_and_now_dead_do("me.on_you_are_hit_and_now_dead()")
    mytp.set_on_you_are_on_fire_do("me.on_fire()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A harmless looking brownish stone.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, delay_ms=100)

    mytp.update()


def init():
    tp_init(name="thunderstone", text_name="thunderstone", short_text_name="thunderstone")


init()
