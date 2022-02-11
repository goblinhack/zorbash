import my
import tp


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_get_name(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_get_name(item), item))
    # my.con("target  {} {:X}".format(my.thing_get_name(target), target))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")
    damage = my.thing_get_damage_melee(item)
    enchant = my.thing_get_enchant(item) * 2
    my.thing_set_current_damage(owner, damage + enchant)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(self, 20)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_damage_melee_chance_d1000(self, 1000)
    my.tp_set_damage_melee_dice(self, "1d4")
    my.tp_set_equip_carry_anim(self, "sword1_wood_carry")
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "sword1_wood_swing")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "25")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_auto_equipped(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_enchantable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_sword(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_is_weapon_class_a(self, True)
    my.tp_set_is_weapon(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "A wooden short sword. Ideal for play fighting and not much else.")
    my.tp_set_noise_on_moving_or_being_carried(self, 5)
    my.tp_set_on_use_do(self, "me.on_use()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Thy wooden means of justice.")
    my.tp_set_text_enchant(self, "increase damage by 2")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="sword1_wood",
        text_name="wooden short sword",
        short_text_name="wooden short sword",
    )


init()
