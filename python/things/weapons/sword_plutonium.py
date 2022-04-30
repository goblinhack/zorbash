import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")


def on_tick(owner, me, x, y):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    #
    # Radiation damage
    #
    if my.pcg_randint(1, 100) > 80:
        if my.pcg_randint(1, 20) > my.thing_stat_con(owner):
            target = owner
            if my.pcg_randint(1, 100) > 10:
                my.thing_hit_damage_draining(me, target, my.pcg_randint(1, 4))
            elif my.pcg_randint(1, 100) > 10:
                my.thing_hit_damage_health(me, target, my.pcg_randint(1, 4))
            else:
                my.thing_hit_damage_poison(me, target, my.pcg_randint(1, 4))

            if my.thing_is_player(owner):
                my.topcon("You feel sick.")
            return True
    return False


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.damaged_chance_d10000(self, 1)
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "1d12+4")
    my.equip_carry_anim(self, "sword_plutonium_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "sword_plutonium_swing")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "2000")
    my.health_initial_dice(self, "1d100")
    my.is_able_to_fall(self, True)
    my.is_able_to_attack_owner(self, True)
    my.is_tickable(self, True)
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
    my.is_very_hard(self, True)
    my.is_moveable(self, True)
    my.is_sword(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_weapon_class_a(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "This glowing and very heavy sword offers supreme damage potential and durability. Crafted from the core of a long gone power source of the ancients, you must take care as prolonged exposure to this sword will make you weak and sick. But maybe it is worth it?")
    my.noise_on_dropping(self, 5)
    my.attacks_per_round(self, 1)
    my.attack_no_msg(self, True)
    my.on_swing_do(self, "me.on_swing()")
    my.on_tick_do(self, "me.on_tick()")
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy nuclear means of justice.")
    my.stat_att_mod(self, 2)  # means +2 per enchant
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+1 DMG, +2 ATT")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="sword_plutonium",
        text_name="sword of plutonium",
        short_text_name="sword of plutonium",
    )


init()
