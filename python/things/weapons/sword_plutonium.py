import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")


def on_tick(owner, me, x, y):
    if not owner:
        return False

    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))

    #
    # Radiation damage
    #
    if my.pcg_randint(1, 100) > 95:
        if my.pcg_randint(1, 20) > my.thing_stat_con(owner):
            target = owner
            if my.pcg_randint(1, 100) > 10:
                my.thing_hit_damage_draining(me, target, my.pcg_randint(1, 4))
            else:
                my.thing_hit_damage_poison(me, target, my.pcg_randint(1, 20))

            if my.thing_is_player(owner):
                my.topcon("You feel sick from radiation poisoning.")
            return True
    return False


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.attack_no_msg(self, True)
    my.attacks_per_round(self, 1)
    my.damaged_chance_d10000(self, 1)
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "1d12+4")
    my.equip_carry_anim(self, "sword_plutonium_carry")
    my.gfx_anim_use(self, "sword_plutonium_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "2000")
    my.health_initial_dice(self, "1d100")
    my.is_able_to_attack_owner(self, True)
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_sword(self, True)
    my.is_tickable(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_very_hard(self, True)
    my.is_weapon_class_c(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 5)
    my.on_swing_do(self, "me.on_swing()")
    my.on_tick_do(self, "me.on_tick()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_att_mod(self, 2)  # means +2 per enchant
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+1 DMG, +2 ATT")
    my.text_long_description(self, "This glowing and very heavy sword offers supreme damage potential and durability. Crafted from the core of a long gone power source of the ancients, you must take care as prolonged exposure to this sword will make you weak and sick. But maybe it is worth it?")
    my.text_short_description(self, "Thy nuclear means of justice.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="sword_plutonium", text_long_name="sword of plutonium", text_short_name="sword, pluton")


init()
