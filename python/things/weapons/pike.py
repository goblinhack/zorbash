import my
import tp


def on_swing(owner, item, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")
    damage = my.thing_damage_melee(item)
    enchant = my.thing_enchant_get(item)
    my.thing_damage_current_set(owner, damage + enchant)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.break_chance_d10000(self, 50)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.collision_hit_priority(self, 6)
    my.collision_hit_two_tiles_ahead(self, True)
    my.crit_chance_d10000(self, 1000)
    my.damage_melee_chance_d1000(self, 1000)
    my.damage_melee_dice(self, "1d10")
    my.equip_carry_anim(self, "pike_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "pike_swing")
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "10")
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
    my.item_height(self, 8)
    my.item_width(self, 8)
    my.long_text_description(self, "Not to be confused with the fish of legend, this deadly weapon is ideal at skewering enemies up to two tiles ahead.")
    my.noise_on_moving_or_being_carried(self, 40)
    my.on_swing_do(self, "me.on_swing()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stamina_on_use(self, 3)
    my.stat_att_mod(self, 1)  # means +1 per enchant
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy skewering means of justice.")
    my.text_enchant(self, "+1 DMG, +1 ATT")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(name="pike", text_name="pike", short_text_name="pike")


init()