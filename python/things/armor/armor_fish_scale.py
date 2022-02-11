import my
import tp

self = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_aquatic")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_aquatic")


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The scale armor glows.")
    my.thing_incr_stat_def(me, 2)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(self, 1000)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_enchant_max(self, 10)
    my.tp_set_equip_carry_anim(self, "armor_fish_scale_carry")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "50")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_armor(self, True)
    my.tp_set_is_auto_equipped(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_enchantable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meltable(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Scale mail armor composed of lots of little fish shaped scales. Smells a bit fishy too. You might actually be wearing a fish.")
    my.tp_set_melting_chance_d1000(self, 2)
    my.tp_set_noise_on_moving_or_being_carried(self, 25)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_enchant_do(self, "me.on_enchant()")
    my.tp_set_on_equip_do(self, "me.on_equip()")
    my.tp_set_on_unequip_do(self, "me.on_unequip()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stat_def(self, 12)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Fish scale mail armor.")
    my.tp_set_text_enchant(self, "+2 AC")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="armor_fish_scale",
        text_name="fish scale armor",
        short_text_name="fish scale armor",
    )


init()
