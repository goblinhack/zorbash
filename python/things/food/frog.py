import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_environ_avoids_fire(self, 100)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_food(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meltable(self, True)
    my.tp_set_is_organic(self, True)
    my.tp_set_is_throwable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Chocolate frogs. The food of Gods. May seem out of place in a dungeon and you'd be correct. It is rumored a helpful god left them here for brave adventurers to assist them on their path. Often found in a purple wrapper. Almost looks too good to eat.")
    my.tp_set_melting_chance_d1000(self, 500)
    my.tp_set_noise_on_moving_or_being_carried(self, 1)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_nutrition_dice(self, "50+1d100")
    my.tp_set_rarity(self, my.RARITY_UNCOMMON)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "The food of the Gods: a chocolate frog.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name, is_hp_100_percent=True)
    my.tp_update(self)


def init():
    tp_init(name="food_frog", text_name="chocolate frog", short_text_name="choc frog")


init()
