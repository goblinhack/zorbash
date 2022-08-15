import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The cloak of protection shimmers.")
    my.thing_stat_def_mod_incr(me, 2)


def on_tick(owner, item, x, y):
    if not owner:
        return False
    my.thing_stamina_decr(owner, 2)
    return True


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 10)
    my.equip_carry_anim(self, "cloak_protection_carry")
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "250")
    my.is_able_to_fall(self, True)
    my.is_cloak(self, True)
    my.is_tickable(self, True)
    my.on_tick_do(self, "me.on_tick()")
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.text_long_description(self, "A finely embroidered cloak that offers modest protection against attack.")
    my.noise_on_dropping(self, -20)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_mod(self, 2)
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "Cloak of protection.")
    my.text_enchant(self, "+2 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="cloak_protection",
        text_long_name="cloak of protection",
        text_short_name="cloak, prot",
    )


init()
