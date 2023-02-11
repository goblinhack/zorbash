import my
import tp


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_missile_protection")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_missile_protection")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.effect_radius(self, 2)
    my.equip_carry_anim(self, "ring_shield_carry")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gold_value_dice(self, "750")
    my.health_initial_dice(self, "1d20")
    my.is_able_to_fall(self, True)
    my.is_able_to_spawn_things(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_ring(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_very_combustible(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.stat_con_mod(self, 1)
    my.stat_def_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DEF")
    my.text_description_long(self, "This magical ring is designed to create a protective shield from missles or missile like objects. It will not help if someone throws a wardrobe at you. Damage will be reduced by 50 percent for such attacks whilst this ring is worn. It also provides modest defence from melee attacks.")
    my.text_description_short(self, "Shield ring.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="circle", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="ring_shield", text_long_name="shield ring", text_short_name="ring, shield")


init()
