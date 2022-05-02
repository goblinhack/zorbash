import my
import tp


def on_swing(owner, item, x, y):
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")


def on_owner_attacking_damage_melee(me, owner, victim, x, y, damage):
    # my.con("on_owner_attacking_damage_melee")
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("victim  {} {:X}".format(my.thing_name_get(victim), victim))
    # my.con("damage  {}".format(damage))
    return damage + my.thing_enchant_get(me)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.damaged_chance_d10000(self, 200)
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "1d6+1")
    my.damage_poison_chance_d1000(self, 0, 100)
    my.damage_poison_dice(self, "1d2+1")
    my.equip_carry_anim(self, "sword_rusty_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "sword_rusty_swing")
    my.gfx_short_shadow_caster(self, True)
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
    my.long_text_description(self, "A rusting short sword. Ideal for absolutely no one.")
    my.noise_on_dropping(self, 10)
    my.on_owner_attacking_damage_melee_do(self, "me.on_owner_attacking_damage_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina_drain_on_attacking(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy rusty means of justice.")
    my.text_enchant(self, "+1 DMG")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="sword_rusty",
        text_name="rusty short sword",
        short_text_name="rusty short sword",
    )


init()
