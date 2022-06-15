import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")


def on_owner_attacking_dmg_melee(me, owner, victim, x, y, damage):
    # my.con("on_owner_attacking_dmg_melee")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    return damage + my.thing_enchant_get(me)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.damaged_chance_d10000(self, 200)
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "1d6+1")
    my.damage_poison_chance_d1000(self, 0, 100)
    my.damage_poison_dice(self, "1d2+1")
    my.equip_carry_anim(self, "sword_rusty_carry")
    my.gfx_anim_use(self, "sword_rusty_swing")
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "50")
    my.health_initial_dice(self, "1d20")
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_metal(self, True)
    my.is_moveable(self, True)
    my.is_rusty(self, True)
    my.is_sword(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_weapon_class_a(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 5)
    my.item_width(self, 5)
    my.noise_on_dropping(self, 10)
    my.on_owner_attacking_dmg_melee_do(self, "me.on_owner_attacking_dmg_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina_drain_on_attacking(self, 1)
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+1 DMG")
    my.text_long_description(self, "A rusting short sword. Ideal for absolutely no one.")
    my.text_short_description(self, "Thy rusty means of justice.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="sword_rusty",
        text_long_name="rusty short sword",
        text_short_name="sword, rusty",
    )


init()
