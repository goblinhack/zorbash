import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("on_owner_attack_dmg_melee")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_impact{my.non_pcg_randint(1, 4)}")
    return damage + my.thing_enchant_count_get(me)


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "The axe glows.")


def on_equip(owner, me, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "sword_equip")
    return


def on_unequip(owner, me, x, y):
    return


def init_weapon(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_crit(self, 500)
    my.chance_d10000_damaged(self, 10)
    my.collision_hit_360(self, True)
    my.dmg_chance_d1000_melee(self, 0, 1000)
    my.dmg_melee_dice(self, "1d6")
    my.equip_carry_anim(self, "axe_carry")
    my.gfx_anim_use(self, "axe_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "150")
    my.health_initial_dice(self, "1d200+150")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_lava(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_equippable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_weapon_class_B(self, True)
    my.is_weapon(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 6)
    my.item_width(self, 6)
    my.noise_on_dropping(self, 15)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_owner_attack_dmg_melee_do(self, "me.on_owner_attack_dmg_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stamina_drain_on_attacking(self, 2)
    my.stat_att_mod(self, 1)  # means +1 per enchant
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DMG, +1 ATT")
    my.text_description_long(self, "A gleaming wooden handled axe. It's a bit short and extra hungry for vengeance. Against what, who can say. Take care, as your mighty swing can hit all monsters adjacent to you.")
    my.text_description_short(self, "Thy choppy means of justice.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    init_weapon(name="axe", text_long_name="short axe", text_short_name="short axe")


init()
