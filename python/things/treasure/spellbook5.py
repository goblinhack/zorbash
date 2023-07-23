import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.charge_count(self, 5)
    my.collision_hit_priority(self, 5)
    my.environ_dislikes_fire(self, 10)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "3000")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_spellbook(self, True)
    my.is_throwable(self, True)
    my.is_treasure_class_C(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.item_height(self, 5)
    my.item_width(self, 5)
    my.noise_on_dropping(self, 90)
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_VERY_RARE)
    my.stat_luck_bonus(self, -8)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "This book is emblazoned with a monstrous demonic face on its cover. It has a dark energy about it. Best to learn the spells inside quickly and get rid of it soon!")
    my.text_description_long(self, "Read this darkest of spellbooks to learn some new spells into your brain matter thing.")
    my.text_description_short(self, "A dusty spellbook.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="diamond_solid", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="spellbook5", text_long_name="spellbook", text_short_name="spellbook")


init()
