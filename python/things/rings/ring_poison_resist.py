import my
import tp


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_poison_resist")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_poison_resist")


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(mytp, 2)
    my.tp_set_collision_hit_priority(mytp, 5)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_gold_value_dice(mytp, "500")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_item_magical(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_ring(mytp, True)
    my.tp_set_is_spawner(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # So it can interact with fire
    my.tp_set_is_treasure_class_c(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_is_very_combustible(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "Eat drink and be merry while wearing this ring, for poison can do you no harm. Please wear responsibly...")
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_equip_do(mytp, "me.on_equip()")
    my.tp_set_on_unequip_do(mytp, "me.on_unequip()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A ring of poison resist.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)
    my.tp_set_equip_carry_anim(mytp, "ring_poison_resist_carry")

    my.tp_set_tile(mytp, tile=name, delay_ms=100)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="ring_poison_resist",
        text_name="ring of poison loving",
        short_text_name="ring of poison resist",
    )


init()
