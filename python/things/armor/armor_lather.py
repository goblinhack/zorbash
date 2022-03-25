import my
import tp

self = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_slippery")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_slippery")


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_topcon(me, "The armor glows.")
    my.thing_stat_def_mod_incr(me, 1)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.break_chance_d10000(self, 5)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 5)
    my.equip_carry_anim(self, "armor_lather_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "5")
    my.is_able_to_fall(self, True)
    my.is_armor(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_a(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "Lathered armor. Not to be confused with leather armor, this armor is leathery with a fine soapy film to help you wriggle out of sticky situations. Apart from that it is mostly useless.")
    my.noise_on_dropping(self, -10)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_mod(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Lathered armor.")
    my.text_enchant(self, "+2 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="armor_lather",
        text_name="lathered armor",
        short_text_name="lathered armor",
    )


init()
