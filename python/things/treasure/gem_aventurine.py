import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("1d50")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_collectable(True)
    mytp.set_is_collected_as_gold(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_stone(True)
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_type(True)
    mytp.set_long_text_description("If you are need of luck, adventurine is the stone for you. It has a few drops of blood on it, ignore those. You will be more lucky.")
    mytp.set_normal_placement_rules(True)
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=forestgreen$Some adventurine, the luckiest stone.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=2000)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=50)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=50)

    mytp.update()

def init():
    tp_init(name="gem_aventurine", text_name="aventurine") # good luck

init()
