import my
import tp


def gold_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_very_short_shadow_caster(True)
    mytp.set_gold_value_dice("100+1d100")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_auto_collect_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_collected_as_gold(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_gold(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_metal(True)
    mytp.set_is_moveable(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_type(True)
    mytp.set_light_color("yellow")
    mytp.set_light_power(1)
    mytp.set_normal_placement_rules(True)
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_text_a_or_an("an")
    mytp.set_text_description("Some gold goins.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", is_dir_none=True)

    mytp.update()


def init():
    gold_init(name="gold6", text_name="a pile of gold coins")


init()
