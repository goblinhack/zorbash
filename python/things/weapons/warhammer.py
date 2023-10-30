import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.py_non_pcg_random_range_inclusive(1, 3)}")
    my.thing_move_penalty_incr(owner, 1)


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("on_owner_attack_dmg_melee")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_impact{my.py_non_pcg_random_range_inclusive(1, 4)}")
    if my.thing_is_moveable(victim):
        my.thing_repulse(owner, victim)
    return damage + my.thing_enchant_count_get(me)


def on_equip(owner, me, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "sword_equip")
    return


def on_unequip(owner, me, x, y):
    return


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if owner and my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "The warhammer glows.")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_damaged(self, 1)
    my.chance_d10000_runic(self, 1000)
    my.chance_d10000_set_on_fire(self, 5)
    my.collision_hit_360(self, True)
    my.dmg_chance_d1000_melee(self, 0, 1000)
    my.dmg_melee_dice(self, "4d8")
    my.equip_carry_anim(self, "warhammer_carry")
    my.gfx_anim_use(self, "warhammer_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "450")
    my.health_initial_dice(self, "1d200+10")
    my.is_able_to_be_equipped(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_aerodynamic(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_blunt(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_C(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_warhammer(self, True)
    my.is_weapon_class_C(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 5)
    my.item_width(self, 5)
    my.noise_on_dropping(self, 30)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_owner_attack_dmg_melee_do(self, "me.on_owner_attack_dmg_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina_drain_on_attacking(self, 3)
    my.stat_str_min(self, 14)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DMG")
    my.text_description_long2(self, "Also useful for pruning and general gardening activities.")
    my.text_description_long3(self, "Blunt weapons are very effective against soft slimy enemies.")
    my.text_description_long(self, "Dealing massive damage and driving the victim back one tile, the only disadvantage of the mighty warhammer is that each swing has a move penalty. Hopefully the extra damage dealt compensates!")
    my.text_description_short(self, "Mighty warhammer")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="warhammer", text_long_name="warhammer", text_short_name="warhammer")


init()
