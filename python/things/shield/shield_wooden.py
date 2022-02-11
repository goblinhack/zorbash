import my
import tp

mytp = None


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The shield shines a woody wood color.")
    my.thing_incr_stat_def(me, 1)


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(mytp, 20)
    my.tp_set_enchant_max(mytp, 10)
    my.tp_set_equip_carry_anim(mytp, "shield_wooden_carry")
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gold_value_dice(mytp, "10")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_shield(mytp, True)
    my.tp_set_is_auto_equipped(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_enchantable(mytp, True)
    my.tp_set_is_wooden(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_noise_on_moving_or_being_carried(mytp, 25)
    my.tp_set_is_item(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_treasure_class_a(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "An actual very rare wooden shield. I know, I can hardly believe it myself. Gives a staggering +2 to armor class.")
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_enchant_do(mytp, "me.on_enchant()")
    my.tp_set_rarity(mytp, my.RARITY_COMMON)
    my.tp_set_stat_def_mod(mytp, 2)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "Wooden shield.")
    my.tp_set_text_enchant(mytp, "+1 AC")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="shield_wooden",
        text_name="wooden shield",
        short_text_name="wooden shield",
    )


init()
