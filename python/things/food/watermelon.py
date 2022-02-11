import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(self, 6)
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
    my.tp_set_is_organic(self, True)
    my.tp_set_is_throwable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "A chunk of watermelon. Those black bits are likely seeds. Yes...")
    my.tp_set_noise_on_moving_or_being_carried(self, 1)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_nutrition_dice(self, "10+1d20")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Watermelon.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name, is_hp_100_percent=True)
    my.tp_update(self)


def init():
    tp_init(name="food_watermelon", text_name="watermelon", short_text_name="waterlemon")


init()
