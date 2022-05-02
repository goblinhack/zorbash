import my
import tp

self = None


def on_equip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your fists feel full of roaring rage!")


def on_unequip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your fists feel like normal fists again!")


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.equip_carry_anim(self, "gauntlets_lion_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "550")
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_gauntlet(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.long_text_description(self, "Gauntlets of lion armor as modelled by Henry II. With these gauntlets, your hide is as tough as a lion and you find you are able to better dodge attacks.")
    my.noise_additional_on_jump_end(self, -50)
    my.noise_on_dropping(self, -50)
    my.noise_on_moving(self, 25)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_VERY_RARE)
    my.stat_def_mod(self, 3)
    my.stat_dex_mod(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Gauntlets of lion armor.")
    my.text_enchant(self, "+1 def, +1 dex")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col="", ascii_fg_col="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="gauntlets_lion",
        text_name="gauntlets of lion armor",
        short_text_name="gauntlets of lion armor",
    )


init()
