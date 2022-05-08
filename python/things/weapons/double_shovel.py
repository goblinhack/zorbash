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
    my.collision_hit_180(self, True)
    my.crit_chance_d10000(self, 500)
    my.damaged_chance_d10000(self, 100)
    my.damage_melee_chance_d1000(self, 0, 1000)
    my.damage_melee_dice(self, "2d10")
    my.equip_carry_anim(self, "double_shovel_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "double_shovel_swing")
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "50")
    my.health_initial_dice(self, "1d20")
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
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
    my.is_weapon_class_b(self, True)
    my.is_weapon(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 9)
    my.item_width(self, 9)
    my.long_text_description(self, "A truly dreadful weapon of last resort. The masterwork double bladed shovel. Ideal for allotment use and casual bludgeoning.")
    my.noise_on_dropping(self, 40)
    my.on_owner_attacking_damage_melee_do(self, "me.on_owner_attacking_damage_melee()")
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_RARE)
    my.stamina_drain_on_attacking(self, 3)
    my.stat_att_mod(self, 1)  # means +1 per enchant
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy diggy means of justice.")
    my.text_enchant(self, "+1 DMG, +1 ATT")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="up_arrow", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(name="double_shovel", text_name="double shovel", short_text_name="double shovel")


init()
