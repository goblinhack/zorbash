import my
import tp


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_food(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_meat(mytp, True)
    my.tp_set_is_organic(mytp, True)
    my.tp_set_is_throwable(mytp, True)
    my.tp_set_is_tickable(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "Fried eggs. Just lying on the floor. You'll have to scoop them off the dirt to eat them, but you have no standards, right? Don't even start to ask where they were cooked. Or by whom. On what.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 1)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_nutrition_dice(mytp, "10+1d25")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Fried eggs.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name, is_hp_100_percent=True)
    my.tp_update(mytp, )


def init():
    tp_init(name="food_eggs", text_name="eggs", short_text_name="eggs")


init()
