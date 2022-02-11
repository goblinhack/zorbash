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
    my.tp_set_collision_hit_priority(mytp, 5)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_environ_avoids_fire(mytp, 10)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_skillstone(mytp, True)
    my.tp_set_is_stone(mytp, True)
    my.tp_set_is_throwable(mytp, True)
    my.tp_set_is_treasure_class_c(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "Use this magical stone to learn some new skills into your brain matter thing.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 10)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_fall_do(mytp, "me.on_fall()")
    my.tp_set_on_you_are_hit_and_now_dead_do(mytp, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_on_you_are_on_fire_do(mytp, "me.on_fire()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A glowing skillstone.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name, delay_ms=100)

    my.tp_update(mytp, )


def init():
    tp_init(name="skillstone", text_name="skillstone", short_text_name="skillstone")


init()
