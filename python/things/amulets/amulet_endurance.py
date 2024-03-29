import my
import tp

self = None


def on_equip(owner, me, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "You feel full of energy!")


def on_unequip(owner, me, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "Your feel your normal tired old self!")


def on_owner_rcv_dmg_stamina(me, owner, hitter, real_hitter, x, y, damage):
    damage = int(damage / 2)
    enchant = my.thing_enchant_count_get(me)
    damage -= 10 * enchant
    if damage < 0:
        damage = 0
    return damage


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_enchanted(self, 20)
    my.equip_carry_anim(self, "amulet_endurance_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gold_value_dice(self, "1250")
    my.is_able_to_be_equipped(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_amulet(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_C(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_value_defensive(self, 1)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_additional_on_jump_end(self, 10)
    my.noise_on_dropping(self, 50)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_owner_rcv_dmg_stamina_do(self, "me.on_owner_rcv_dmg_stamina()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_RARE)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "-10 stamina DMG")
    my.text_description_long(self, "Amulet of endurance. Leap for joy whilst wearing this amulet for you will only use half as much stamina as normal. This also applies to magical items that may attempt to drain stamina, like boots of jumping or skills such as Devoted Thrust. Each enchant will reduce a further 10 points of stamina damage.")
    my.text_description_short(self, "Amulet of endurance.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="ankh", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="amulet_endurance",
        text_long_name="amulet of endurance",
        text_short_name="amulet, endurance",
    )


init()
