import my
import tp

self = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_aquatic")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_aquatic")


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The scale armor glows.")
    my.thing_stat_def_mod_incr(me, 2)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.collision_hit_priority(self, 6)
    my.damaged_chance_d10000(self, 1000)
    my.enchant_max(self, 10)
    my.equip_carry_anim(self, "armor_fish_scale_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "50")
    my.is_able_to_fall(self, True)
    my.is_armor(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_meltable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.melting_chance_d1000(self, 2)
    my.noise_on_dropping(self, 25)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_mod(self, 2)
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+2 DEF")
    my.text_long_description(self, "Scale mail armor composed of lots of little fish shaped scales. Smells a bit fishy too. You might actually be wearing a fish.")
    my.text_short_description(self, "Fish scale mail armor.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="armor_fish_scale",
        text_long_name="fish scale armor",
        text_short_name="armor, fish",
    )


init()
