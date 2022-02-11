import my
import tp


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_poison_resist")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_poison_resist")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(self, 2)
    my.tp_set_collision_hit_priority(self, 5)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_gold_value_dice(self, "500")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_item_magical(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_ring(self, True)
    my.tp_set_is_spawner(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with fire
    my.tp_set_is_treasure_class_c(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_is_very_combustible(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Eat drink and be merry while wearing this ring, for poison can do you no harm. Please wear responsibly...")
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_equip_do(self, "me.on_equip()")
    my.tp_set_on_unequip_do(self, "me.on_unequip()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A ring of poison resist.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)
    my.tp_set_equip_carry_anim(self, "ring_poison_resist_carry")

    my.tp_set_tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(
        name="ring_poison_resist",
        text_name="ring of poison loving",
        short_text_name="ring of poison resist",
    )


init()
