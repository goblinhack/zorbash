import my
import tp

self = None


def on_equip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel an urge to peek through keyholes!")


def on_unequip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your vision is normal again!")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.equip_carry_anim(self, "amulet_peeking_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "250")
    my.is_able_to_fall(self, True)
    my.is_able_to_see_through_doors(self, True)
    my.is_amulet(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_additional_on_jump_end(self, 10)
    my.noise_on_dropping(self, 50)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.text_a_or_an(self, "a")
    my.text_long_description(self, "Amulet of peeking. You are now able to see through doors as if they were made of glass.")
    my.text_short_description(self, "Amuler of peeking.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="amulet_peeking",
        text_long_name="amulet of peeking",
        text_short_name="amulet, peek",
    )


init()
