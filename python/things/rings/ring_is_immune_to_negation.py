import my
import tp


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_permanent_immune_to_negation")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_permanent_immune_to_negation")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_enchanted(self, 20)
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.equip_carry_anim(self, "ring_is_immune_to_negation_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gold_value_dice(self, "500")
    my.health_initial_dice(self, "1d20")
    my.health_initial_dice(self, "200")
    my.is_able_to_be_equipped(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_spawn_things(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_immune_to_negation(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_ring(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_value_defensive(self, 1)
    my.is_very_combustible(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.stat_con_bonus(self, -1)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "rings of negation immunities")
    my.text_apostrophize(self, "ring of negation immunity's")
    my.text_description_enchant(self, "+1 CON")
    my.text_description_long(self, "Negate your negative qualities with this ring of mega nega negativity. Attacks of negation will have no impact on you.")
    my.text_description_short(self, "A ring of negation immunity.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="ring_is_immune_to_negation",
            text_long_name="ring of negation immunity",
            text_short_name="ring, negation")


init()
