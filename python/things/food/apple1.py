import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_collectable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_food(True)
    mytp.set_is_interesting(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_organic(True)
    mytp.set_is_throwable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_usable(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("A juicy dungeon apple. From local dungeon apple trees, if you can believe that.")
    mytp.set_noise_decibels(1)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("10+1d10")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("Juicy apple.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name, is_hp_100_percent=True)
    mytp.update()


def init():
    tp_init(name="food_apple1", text_name="juicy apple", short_text_name="juicy apple")


init()
