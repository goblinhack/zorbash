import zx
import tp

def explode(me, x, y):
    zx.thing_msg(me, "The enchantstone explodes.")
    zx.level_spawn_at_thing(me, "explosion_major")
    zx.level_spawn_fire_around_thing(me, "fire")
    zx.level_spawn_at_thing(me, "fire")
    zx.thing_killed(me, "exploded")

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    explode(me, x, y)

def on_fire(me, x, y):
    explode(me, x, y)

def on_fall(me, x, y):
    explode(me, x, y)

def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_hates_fire(100)
    x.set_bag_item_height(2)
    x.set_bag_item_width(2)
    x.set_blast_max_radius(4)
    x.set_blast_min_radius(0)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(5)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_attackable_by_player(True)
    x.set_is_collectable(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_droppable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_moveable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_throwable(True)
    x.set_is_treasure(True)
    x.set_is_treasure_class_c(True)
    x.set_is_enchantstone(True)
    x.set_is_usable(True)
    x.set_is_used_when_thrown(True)
    x.set_long_text_description("Use this magical stone to bestow powers on other items you carry.")
    x.set_on_fall_do("enchantstone.on_fall()")
    x.set_on_fire_do("enchantstone.on_fire()")
    x.set_on_hit_do("enchantstone.on_hit()")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a")
    x.set_text_description("A glowing enchantstone")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name, delay_ms=100)

    x.update()

def init():
    tp_init(name="enchantstone", text_name="enchantstone", short_text_name="enchantstone")

init()
