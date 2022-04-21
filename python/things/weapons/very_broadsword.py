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


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The broadsword seems even wider somehow.")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.break_chance_d10000(self, 1)
    my.collision_check(self, True)
    my.collision_hit_adj(self, True)
    my.collision_hit_priority(self, 10)
    my.collision_hit_priority(self, 6)
    my.crit_chance_d10000(self, 500)
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "2d12")
    my.equip_carry_anim(self, "very_broadsword_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "very_broadsword_swing")
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "350")
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
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_weapon_class_c(self, True)
    my.is_weapon(self, True)
    my.item_height(self, 8)
    my.item_width(self, 8)
    my.long_text_description(self, "A broardsword plus some. The girth of this extreme weapon allows you to additionally attack adjacent targets to your intended target. Also useful for chopping tomatoes.")
    my.noise_on_dropping(self, 40)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_owner_attacking_damage_melee_do(self, "me.on_owner_attacking_damage_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stamina_drain_on_attacking(self, 3)
    my.stat_att_mod(self, 1)  # means +1 per enchant
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy decapitaty means of justice.")
    my.text_enchant(self, "+1 DMG, +1 ATT")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="very_broadsword", text_name="very broadsword", short_text_name="very broadsword")


init()
