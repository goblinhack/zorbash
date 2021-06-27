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
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(5)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(False)
    mytp.set_hates_fire(100)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantstone(True)
    mytp.set_is_interesting(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_moveable(True)
    mytp.set_is_throwable(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure(True)
    mytp.set_is_usable(True)
    mytp.set_is_used_when_thrown(False)
    mytp.set_long_text_description("Use this magical stone to bestow powers on other items you carry.")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_fall_do("enchantstone.on_fall()")
    mytp.set_on_fire_do("enchantstone.on_fire()")
    mytp.set_on_hit_do("enchantstone.on_hit()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A glowing enchantstone")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, delay_ms=100)

    mytp.update()

def init():
    tp_init(name="enchantstone", text_name="enchantstone", short_text_name="enchantstone")

init()
