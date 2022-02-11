import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The shield looks a bit more wooden.")
    my.thing_incr_stat_def(me, 1)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_break_chance_d10000(self, 100)
    my.tp_set_enchant_max(self, 5)
    my.tp_set_equip_carry_anim(self, "shield_woodon_carry")
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gold_value_dice(self, "5")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_shield(self, True)
    my.tp_set_is_auto_equipped(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_enchantable(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_treasure_class_a(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Woodon shield. Yes. Woodon. This is a low quality shield sprayed with patented Woodon (self, tm), to give a nice woody sheen. Not to be confused with an actual wooden shield made of actual wood. This shield gives a measly +1 to armor class and is liable to break. 30 day return policy.")
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_enchant_do(self, "me.on_enchant()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stat_def_mod(self, 1)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "Woodon shield.")
    my.tp_set_text_enchant(self, "+1 AC")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="shield_woodon",
        text_name="woodon shield",
        short_text_name="woodon shield",
    )


init()
