import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The shield shines a woody wood color.")
    my.thing_incr_stat_def(me, 1)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(self, 20)
    my.tp_set_enchant_max(self, 10)
    my.tp_set_equip_carry_anim(self, "shield_wooden_carry")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "10")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_shield(self, True)
    my.tp_set_is_auto_equipped(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_enchantable(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_noise_on_moving_or_being_carried(self, 25)
    my.tp_set_is_item(self, True)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "An actual very rare wooden shield. I know, I can hardly believe it myself. Gives a staggering +2 to armor class.")
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_enchant_do(self, "me.on_enchant()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stat_def_mod(self, 2)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Wooden shield.")
    my.tp_set_text_enchant(self, "+1 AC")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="shield_wooden",
        text_name="wooden shield",
        short_text_name="wooden shield",
    )


init()
