import my
import tp


def explode(me, x, y):
    my.thing_msg(me, "The skillstone explodes.")
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
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_hit_priority(5)
    mytp.set_environ_avoids_fire(10)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
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
    mytp.set_is_skillstone(True)
    mytp.set_is_stone(True)
    mytp.set_is_throwable(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Use this magical stone to learn some new skills into your brain matter thing.")
    mytp.set_noise_level(10)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_fall_do("me.on_fall()")
    mytp.set_on_you_are_hit_and_now_dead_do("me.on_you_are_hit_and_now_dead()")
    mytp.set_on_you_are_on_fire_do("me.on_fire()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A glowing skillstone.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, delay_ms=100)

    mytp.update()


def init():
    tp_init(name="skillstone", text_name="skillstone", short_text_name="skillstone")


init()
