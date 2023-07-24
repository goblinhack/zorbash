import my
import tp


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "lime stalker fungus", "lime stlkr fungus")
    # begin sort marker
    my.collision_hit_priority(self, 1)
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_poison_dice(self, "1d10")
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, False)
    my.is_described_when_hovering_over(self, True)
    my.is_food(self, True)
    my.is_fungus_poison(self, True)
    my.is_fungus(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_organic(self, True)
    my.is_throwable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.nutrition_dice(self, "1d5")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_long2(self, "Is it poisonous? Who can tell... Well you probably, if you dare to eat it.")
    my.text_description_long(self, "An enormous pale mushroom with a ghostly stem and lime green spots on its cap.")
    my.text_description_short(self, "An enormous mushroom.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self, delay_ms=300,
                ascii_fg_char="lollipop", ascii_bg_col_name="", ascii_fg_col_name="lime",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_poison_14", tiles=["fungus_poison_14"])


init()
