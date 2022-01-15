import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gold_value_dice("1d300+100")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_collectable(True)
    mytp.set_is_collected_as_gold(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_stone(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_type(True)
    mytp.set_long_text_description("A glistening diamond. Like a spark of white fire in the darkness. Is there anything more precious. Probably. Grab it quick anyway.")
    mytp.set_normal_placement_rules(True)
    mytp.set_rarity(my.RARITY_UNCOMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Just a lonely diamond.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=200)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=200)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=300)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=300)
    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=200)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=300)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=300)
    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=200)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)

    mytp.update()


def init():
    tp_init(name="gem_diamond", text_name="diamond")


init()
