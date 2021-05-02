import zx
import tp

def on_use(owner, item, target, x, y):
    #zx.con("owner   {} {:08X}".format(zx.thing_get_name(owner), owner))
    #zx.con("item    {} {:08X}".format(zx.thing_get_name(item), item))
    #zx.con("target  {} {:08X}".format(zx.thing_get_name(target), target))
    zx.level_spawn_at_thing(target, "explosion_major")
    zx.level_spawn_using_items_radius_range(owner, item, target, "explosion_destroy_floor")

def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_hates_fire(100)
    x.set_bag_item_height(2)
    x.set_bag_item_width(2)
    x.set_blast_max_radius(4)
    x.set_blast_min_radius(0)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
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
    x.set_is_thrown_automatically_when_chosen(True)
    x.set_is_treasure(True)
    x.set_is_treasure_class_c(True)
    x.set_is_usable(True)
    x.set_is_used_when_thrown(True)
    x.set_long_text_description("This most dangerous stone can devistate any are where it is thrown. Be careful where you drop it...")
    x.set_normal_placement_rules(True)
    x.set_on_use_do("thunderstone.on_use()")
    x.set_text_a_or_an("a")
    x.set_text_description("A harmless looking brownish stone")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name, delay_ms=100)

    x.update()

def init():
    tp_init(name="thunderstone", text_name="thunderstone", short_text_name="thunderstone")

init()
