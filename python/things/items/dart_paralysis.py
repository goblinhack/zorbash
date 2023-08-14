import my
import tp


def on_thrown(owner, me, x, y):
    for it in my.level_get_all(me, x, y):
        if my.thing_is_alive_monst(it) or my.thing_is_player(it):
            if it == me:
                continue
            if it == owner:
                continue
            if not my.thing_paralysis_count_incr(it, 10):
                if owner and my.thing_is_player(owner):
                    my.thing_msg(owner, "%%fg=red$Your paralysis dart has no effect.")
            else:
                if owner and my.thing_is_player(owner):
                    if owner == it:
                        my.thing_msg(owner, "%%fg=red$You paralyse yourself!%%fg=reset$")
                    else:
                        my.thing_msg(owner, f"%%fg=red$You paralyse the {my.thing_name_get(it)}!%%fg=reset$")

    if my.py_pcg_random_range_inclusive(1, 100) < 90:
        my.thing_dead(me, "used")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d1000_appearing(self, 10)
    my.dmg_chance_d1000_missile(self, 0, 1000)
    my.dmg_chance_d1000_poison(self, 0, 1000)
    my.dmg_missile_dice(self, "1d4")
    my.dmg_poison_dice(self, "1d4")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_targeted_projectile(self, "projectile_dart_poison")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_aerodynamic(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable_as_a_group(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_light(self, True)
    my.is_loggable(self, True)
    my.is_missile(self, True)
    my.is_moveable(self, True)
    my.is_pointy(self, True)
    my.is_ranged_weapon(self, True)
    my.is_throwable(self, True)
    my.is_thrown_as_a_weapon(self, True)
    my.is_treasure_class_A(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_on_dropping(self, 1)
    my.normal_placement_rules(self, True)
    my.on_thrown_do(self, "me.on_thrown()")
    my.rarity(self, my.RARITY_COMMON)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 DMG")
    my.text_description_long(self, "This dart will bring your enemies to a standstill. Literally.")
    my.text_description_short(self, "A paralysing tipped dart.")
    my.thing_size(self, my.THING_SIZE_TINY)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="'", ascii_bg_col_name="", ascii_fg_col_name="gray90",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="dart_paralysis", text_long_name="paralysis dart", text_short_name="paralysis dart")


init()
