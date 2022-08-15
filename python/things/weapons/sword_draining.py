import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")


def on_owner_attack_dmg_draining(me, owner, victim, x, y, damage):
    # my.con("on_owner_attack_dmg_draining")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    return damage + my.thing_enchant_get(me) * 3


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.attacks_per_round(self, 2)
    my.damaged_chance_d10000(self, 5)
    my.damage_draining_chance_d1000(self, 1, 1000)
    my.damage_draining_dice(self, "1d20")
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "1d8")
    my.equip_carry_anim(self, "sword_draining_carry")
    my.gfx_anim_use(self, "sword_draining_swing")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "1000")
    my.health_initial_dice(self, "1d20")
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
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_weapon_class_c(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 5)
    my.on_owner_attack_dmg_draining_do(self, "me.on_owner_attack_dmg_draining()")
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina_drain_on_attacking(self, 0)
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+3 DMG stam")
    my.text_long_description(self, "This magical sword deals additional draining damage to suck the will to live out of your opponents.")
    my.text_short_description(self, "Thy tiring means of justice.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="sword_draining", text_long_name="sword of draining", text_short_name="sword, draing")


init()
