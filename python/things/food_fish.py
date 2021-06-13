import zx
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_bag_item_height(2)
    mytp.set_bag_item_width(2)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(False)
    #mytp.set_hates_fire(100)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_food(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    #mytp.set_is_meat(True)
    mytp.set_is_shown_on_leftbar(True)
    mytp.set_is_throwable(True)
    mytp.set_is_usable(True)
    mytp.set_is_used_automatically_when_selected(False)
    mytp.set_long_text_description("A misplaced fish.")
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d25")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=brown$Lost fish.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, is_hp_100_percent=True)
    mytp.update()

def init():
    tp_init(name="food_fish", text_name="fish", short_text_name="fish")

init()
