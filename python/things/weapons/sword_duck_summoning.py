import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.py_non_pcg_random_range_inclusive(1, 3)}")


def on_owner_attack_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("on_owner_attack_dmg_melee")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_impact{my.py_non_pcg_random_range_inclusive(1, 4)}")
    return damage + my.thing_enchant_count_get(me)


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    if not target:
        return
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))

    nducks = my.py_pcg_random_range_inclusive(1, 6)
    for n in range(0, nducks):
        duck = my.spawn_at_my_position(target, "duck1")
        if duck:
            # my.con("duck    {} {:X}".format(my.thing_name_get(duck), duck))
            my.thing_friend_add(duck, owner)
    my.spawn_at_my_position(target, "magical_effect")


def on_equip(owner, me, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "sword_equip")
    return


def on_unequip(owner, me, x, y):
    return


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "The sword quacks.")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.attack_no_msg(self, True)
    my.chance_d10000_damaged(self, 1)
    my.charge_count(self, 5)
    my.dmg_chance_d1000_melee(self, 0, 1000)
    my.dmg_melee_dice(self, "1d10+2")
    my.dmg_num_of_attacks(self, 1)
    my.equip_carry_anim(self, "sword_duck_summoning_carry")
    my.gfx_anim_use(self, "sword_duck_summoning_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "1500")
    my.health_initial_dice(self, "1d1000+500")
    my.is_able_to_attack_owner(self, True)
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
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_item_targeted(self, True)
    my.is_kept_after_final_use(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_pointy(self, True)
    my.is_sword(self, True)
    my.is_target_select(self, True)
    my.is_tickable(self, True)
    my.is_treasure_class_C(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_very_hard(self, True)
    my.is_weapon_class_C(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.light_color(self, "yellow")
    my.light_dist(self, 1)
    my.noise_on_dropping(self, 5)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_owner_attack_dmg_melee_do(self, "me.on_owner_attack_dmg_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.on_use_do(self, "me.on_use()")
    my.rarity(self, my.RARITY_VERY_RARE)
    my.stat_att_bonus(self, 2)  # means +2 per enchant
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DMG, +2 ATT")
    my.text_description_long(self, "This powerful sword additionally grants you the ability to summon a duck at any given location within range. Said duck will be friendly towards you and may or may not be an assist in battle.")
    my.text_description_short(self, "Thy ducky powered means of justice.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="sword_duck_summoning", text_long_name="sword of duck summoning", text_short_name="sword, duck")


init()
