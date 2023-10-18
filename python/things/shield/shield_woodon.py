import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if owner and my.thing_is_player(owner):
        my.thing_msg(me, "The shield looks a bit more wooden.")
    my.thing_stat_def_incr(me, 1)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_damaged(self, 100)
    my.chance_d10000_set_on_fire(self, 500)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 2)
    my.equip_carry_anim(self, "shield_woodon_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gold_value_dice(self, "5")
    my.health_initial_dice(self, "10")
    my.is_able_to_be_equipped(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_shield(self, True)
    my.is_treasure_class_A(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_value_defensive(self, 1)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_bonus(self, 1)
    my.stat_dex_bonus(self, -1)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DEF")
    my.text_description_long2(self, "This shield gives a measly +1 to defense and is liable to break.")
    my.text_description_long3(self, "No 30 day return policy.")
    my.text_description_long(self, "Woodon shield. Yes. Woodon. This is a low quality foam shield sprayed with patented Woodon (tm), to give a nice woody sheen. Not to be confused with an actual wooden shield made of actual wood.")
    my.text_description_short(self, "Woodon shield.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="shield_woodon", text_long_name="woodon shield", text_short_name="shield, woodon")


init()
