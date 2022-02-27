import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The stone cloak glistens.")
    my.thing_stat_def_mod_incr(me, 2)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.break_chance_d10000(self, 100)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 10)
    my.equip_carry_anim(self, "stone_cloak_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "500")
    my.is_able_to_fall(self, True)
    my.is_cloak(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_able_to_walk_through_walls(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "A strange cloak that looks to be covered in stone dust...")
    my.noise_on_moving_or_being_carried(self, -20)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Stone cloak.")
    my.text_enchant(self, "+1 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="stone_cloak",
        text_name="stone cloak",
        short_text_name="stone cloak",
    )


init()
