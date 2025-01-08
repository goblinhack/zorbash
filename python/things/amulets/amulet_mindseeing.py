import my
import tp

self = None


def on_equip(owner, me, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "Your sense danger all around!")


def on_unequip(owner, me, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "The world seems more boring now!")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_enchanted(self, 20)
    my.equip_carry_anim(self, "amulet_mindseeing_carry")
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
    my.is_treasure(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_additional_on_jump_end(self, 10)
    my.noise_on_dropping(self, 50)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_RARE)
    my.stat_psi_bonus(self, 5)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 PSI")
    my.text_description_long(self, "Amulet of mindseeing. This amulet increases your Psi abilities and may allow you to sense the presence on nasties nearby.")
    my.text_description_short(self, "Amulet of mindseeing.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="ankh", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="amulet_mindseeing",
        text_long_name="amulet of mindseeing",
        text_short_name="amulet, mindseeing",
    )


init()
