import my
import tp


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.collision_hit_priority(self, 6)
    my.gfx_short_shadow_caster(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_food(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_organic(self, True)
    my.is_throwable(self, True)
    my.is_tickable(self, True)
    my.is_usable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "A slice of chef prepared salmon. No sign of the chef in sight. Might not be salmon. It's wriggling a bit.")
    my.noise_on_moving_or_being_carried(self, 1)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "10+1d25")
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Salmon.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name, is_hp_100_percent=True)
    my.tp_update(self)


def init():
    tp_init(name="food_salmon", text_name="salmon", short_text_name="salmon")


init()
