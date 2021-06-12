import zx
import tp


def gold_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_collision_circle(True)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_bounce_always(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_very_short_shadow_caster(True)
    mytp.set_gold_value_dice("1")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_auto_collect_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_gold(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item_collected_as_gold(True)
    mytp.set_is_item(True)
    mytp.set_is_moveable(True)
    mytp.set_is_shown_on_leftbar(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure(True)
    mytp.set_light_color("yellow")
    mytp.set_light_strength(1)
    mytp.set_normal_placement_rules(True)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A gold goin.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".7", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".8", is_dir_none=True, delay_ms=50)

    mytp.update()

def init():
    gold_init(name="gold1", text_name="gold1")

init()
