import my
import tp


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "1d150")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_collected_as_gold(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_stone(mytp, True)
    my.tp_set_is_treasure_class_c(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_long_text_description(mytp, "Magnificent and blessed sapphire, in all its celestial hues. It is a stone of wisdom, prophecy and divine good portents. Putting all that aside, it's worth a few bob. Grab it!")
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_rarity(mytp, my.RARITY_UNCOMMON)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Polished blue sapphire.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name + ".1", is_dir_none=True, delay_ms=2000)
    my.tp_set_tile(mytp, tile=name + ".2", is_dir_none=True, delay_ms=50)
    my.tp_set_tile(mytp, tile=name + ".3", is_dir_none=True, delay_ms=50)

    my.tp_update(mytp, )


def init():
    tp_init(name="gem_sapphire", text_name="sapphire")


init()
