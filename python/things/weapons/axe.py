import my
import tp


def on_swing(owner, item, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")
    enchant = my.thing_enchant_get(item)

    damage = my.thing_damage_melee(item)
    my.thing_damage_current_set(owner, damage + enchant)


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The axe glows.")


def init_weapon(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.break_chance_d10000(self, 10)
    my.collision_check(self, True)
    my.collision_hit_360(self, True)
    my.collision_hit_priority(self, 10)
    my.collision_hit_priority(self, 6)
    my.crit_chance_d10000(self, 500)
    my.damage_melee_chance_d1000(self, 1000)
    my.damage_melee_dice(self, "1d12")
    my.equip_carry_anim(self, "axe_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "axe_swing")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "150")
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
    my.item_height(self, 6)
    my.item_width(self, 6)
    my.long_text_description(self, "A gleaming wooden handled axe. It's a bit short and extra hungry for vengeance. Against what, who can say. Take care, as your mighty swing can hit all monsters adjacent to you.")
    my.noise_on_moving_or_being_carried(self, 15)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stamina_on_use(self, 2)
    my.stat_att_mod(self, 1)  # means +1 per enchant
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy choppy means of justice.")
    my.text_enchant(self, "+1 DMG, +1 ATT")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    init_weapon(name="axe", text_name="short axe", short_text_name="short axe")


init()
