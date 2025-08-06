import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if owner and my.thing_is_player(owner):
        my.thing_msg_if_not_dead_or_dying(me, "The armor glows a bright green.")
    my.thing_stat_def_bonus_incr(me, 1)


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_permanent_slime_protection")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_permanent_slime_protection")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_damaged(self, 5)
    my.chance_d10000_enchanted(self, 200)
    my.chance_d10000_runic_class_A(self, 100)
    my.collision_hit_priority(self, 6)
    my.equip_carry_anim(self, "armor_slime_carry")
    my.gfx_ascii_show_light_once_seen(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gold_value_dice(self, "1000")
    my.is_able_to_be_equipped(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_armor(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_heavy(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_C(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_value_defensive(self, 1)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.light_color(self, "green")
    my.light_dist(self, 1)
    my.noise_on_dropping(self, 10)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_RARE)
    my.stat_def_bonus(self, 3)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "slime armor")
    my.text_apostrophize(self, "slime armor's")
    my.text_description_enchant(self, "+1 DEF")
    my.text_description_long(self, "Slime resistant armor for all your slime related needs.")
    my.text_description_short(self, "Slime resistant armor.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="armor_slime",
        text_long_name="slime armor",
        text_short_name="armor, slime",
    )


init()
