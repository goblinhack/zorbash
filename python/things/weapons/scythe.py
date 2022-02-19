import my
import tp


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, f"sword_swing{my.non_pcg_randint(1, 3)}")
    damage = my.thing_damage_melee(item)
    enchant = my.thing_enchant_get(item)
    my.thing_damage_current_set(owner, damage + enchant)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.break_chance_d10000(self, 5)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.collision_hit_priority(self, 6)
    my.damage_melee_chance_d1000(self, 1000)
    my.damage_melee_dice(self, "3d6+1")
    my.equip_carry_anim(self, "scythe_carry")
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "scythe_swing")
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "250")
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
    my.long_text_description(self, "A huge gleaming scythe. Ideal for gardening and other uses.")
    my.noise_on_moving_or_being_carried(self, 20)
    my.on_use_do(self, "me.on_use()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Thy swingy means of justice.")
    my.text_enchant(self, "+1 DMG")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name + ".1")

    my.tp_update(self)


def init():
    tp_init(name="scythe", text_name="single headed scythe", short_text_name="short scythe")


init()
