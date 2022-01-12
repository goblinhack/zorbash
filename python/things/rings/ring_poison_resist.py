import my
import tp


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_poison_resist")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_poison_resist")


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_blast_max_radius(2)
    mytp.set_collision_hit_priority(5)
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("500")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_item_magical(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_ring(True)
    mytp.set_is_spawner(True)
    mytp.set_is_tickable(True)  # So it can interact with fire
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_very_combustible(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Eat drink and be merry while wearing this ring, for poison can do you no harm. Please wear responsibly...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_equip_do("me.on_equip()")
    mytp.set_on_unequip_do("me.on_unequip()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A ring of poison resist.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)
    mytp.set_equip_carry_anim("ring_poison_resist_carry")

    mytp.set_tile(tile=name, delay_ms=100)

    mytp.update()


def init():
    tp_init(
        name="ring_poison_resist",
        text_name="ring of poison loving",
        short_text_name="ring of poison resist",
    )


init()
