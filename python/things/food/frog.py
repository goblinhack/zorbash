import my
import tp


def on_eaten(eater, item, x, y):
    # my.con("eater {} {:X}".format(my.thing_name_get(eater), eater))
    # my.con("item  {} {:X}".format(my.thing_name_get(item), item))
    if my.thing_poisoned_amount_get(eater) != 0:
        my.thing_sound_play_channel(eater, my.CHANNEL_WEAPON, "potion")
        my.thing_poisoned_amount_set(eater, 0)
        if eater and my.thing_is_player(eater):
            my.thing_msg(eater, "%%fg=pink$That frog hit the spot! You feel much better!%%fg=reset$")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d1000_melting(self, 500)
    my.collision_hit_priority(self, 6)
    my.environ_dislikes_fire(self, 100)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_bounce_always(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_melt(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_food(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_organic(self, True)
    my.is_throwable(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "50+1d100")
    my.on_eaten_do(self, "me.on_eaten()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.temperature_max(self, 25)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_pluralize(self, "chocolate frogs")
    my.text_apostrophize(self, "chocolate frog's")
    my.text_description_long(self, "The food of the Gods. May seem out of place in a dungeon and you'd be correct. It is rumored a helpful god left them here for brave adventurers to assist them on their path. Often found in a purple wrapper. Almost looks too good to eat.")
    my.text_description_short(self, "The food of the Gods: a chocolate frog.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char=";", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name, is_hp_100_percent=True)
    my.tp_update(self)


def init():
    tp_init(name="frog",
            text_long_name="chocolate frog",
            text_short_name="choc frog")


init()
