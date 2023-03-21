import my
import tp


def on_thrown(owner, me, x, y):
    for it in my.level_get_all(me, x, y):
        if my.thing_is_interesting(it):
            if it == me:
                continue
            my.thing_hit_dmg_missile(owner, me, it, thrown=True)

    if my.pcg_randint(1, 100) < 50:
        my.thing_dead(me, "used")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d1000_appearing(self, 10)
    my.dmg_chance_d1000_missile(self, 0, 1000)
    my.dmg_missile_dice(self, "1d6+3")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable_as_a_group(self, True)
    my.is_enchantable(self, True)
    my.is_hard(self, True)
    my.is_heavy(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_made_of_rock(self, True)
    my.is_missile(self, True)
    my.is_moveable(self, True)
    my.is_ranged_weapon(self, True)
    my.is_throwable(self, True)
    my.is_thrown_as_a_weapon(self, True)
    my.is_treasure_class_A(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_on_dropping(self, 20)
    my.normal_placement_rules(self, True)
    my.on_thrown_do(self, "me.on_thrown()")
    my.rarity(self, my.RARITY_COMMON)
    my.target_name_projectile(self, "projectile_rock")
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DMG")
    my.text_description_long(self, "The less civilized person's melee weapon. This rock has has great potential... for causing injury")
    my.text_description_short(self, "A small menacing rock.")
    my.thing_size(self, my.THING_SIZE_TINY)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="o", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="rock", text_long_name="rock", text_short_name="rock")


init()
