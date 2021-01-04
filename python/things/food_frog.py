import zx
import tp


def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_bag_item_height(2)
    x.set_bag_item_width(2)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_collectable(True)
    x.set_is_combustible(True)
    x.set_is_food(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_throwable(True)
    x.set_is_treasure_class_a(False)
    x.set_is_usable(True)
    x.set_long_text_description("Chocolate frogs may seem out of place in the dungeon as they are one of the few items the denizens of the dungeon tend not to eat. It is rumored a helpful god left them here for brave adventurers to assist them on their path.")
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d10")
    x.set_stats_health_initial(4)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=brown$The food of the gods: a chocolate frog")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name, is_hp_100_percent=True)
    x.update()

def init():
    tp_init(name="food_frog1", text_name="chocolate frog", short_text_name="choc frog")

init()
