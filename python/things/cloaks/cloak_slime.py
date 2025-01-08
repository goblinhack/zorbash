import my
import tp

self = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_permanent_slime_protection")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_permanent_slime_protection")


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 6)
    my.equip_carry_anim(self, "cloak_slime_carry")
    my.gfx_ascii_show_light_once_seen(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gold_value_dice(self, "100")
    my.is_able_to_be_equipped(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_cloak(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure(self, True)
    my.is_treasure_class_A(self, True)
    my.is_treasure_type(self, True)
    my.is_value_defensive(self, 1)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.light_color(self, "green")
    my.light_dist(self, 1)
    my.noise_on_dropping(self, -20)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_bonus(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A brilliant slimy green cloak that you know will afford you protection against repellent slimes.")
    my.text_description_short(self, "Cloak of slime protection.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="cloak_slime",
        text_long_name="cloak of slime protection",
        text_short_name="cloak, slime",
    )


init()
