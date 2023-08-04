import my
import tp


def on_thrown(owner, me, x, y):
    shatters(me, x, y)


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))
    did_something = False

    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "potion")

    enchant = my.thing_enchant_count_get(item)

    health = my.thing_health(owner)
    new_health = int((float(my.thing_health_max(owner)) / 100.0) * 10.0 + enchant * 10.0)
    if new_health > health:
        did_something = True
        my.thing_health_set(owner, new_health)

    stamina = my.thing_stamina(owner)
    new_stamina = int((float(my.thing_stamina_max(owner)) / 100.0) * 10.0 + enchant * 10.0)
    if new_stamina > stamina:
        did_something = True
        my.thing_stamina_set(owner, new_stamina)

    if my.thing_poisoned_amount_get(owner) != 0:
        did_something = True
        my.thing_poisoned_amount_set(owner, 0)

    if did_something:
        my.spawn_using_items_radius_range(owner, item, target, "potion_effect")
        if my.thing_is_player(owner):
            my.thing_msg(owner, "%%fg=pink$You glow with holiness, however you define that.%%fg=reset$")
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "Hmm. The holy water didn't seem to do anything.")


def shatters(me, x, y):
    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(me, "Your beaker of holy water shatters.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s beaker of holy water shatters.")
    else:
        my.thing_msg(me, "The beaker of holy water shatters.")

    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # if (owner):
    #     my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))

    selection_x, selection_y = my.thing_coords_get(me)
    for it in my.level_get_all(me, selection_x, selection_y):
        # my.con("it      {} {:X}".format(my.thing_name_get(it), it))
        if my.thing_is_undead(it):
            # my.con("hit it  {} {:X}".format(my.thing_name_get(it), it))
            my.thing_hit_dmg_energy(owner, me, it, my.py_pcg_random_range_inclusive(10, 20))
            my.spawn_at_my_position(me, "explosion_fire")

    my.spawn_at_my_position(me, "water")
    my.thing_dead(me, "broken")


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    shatters(me, x, y)


def on_fire(me, x, y):
    shatters(me, x, y)


def on_fall(me, x, y):
    shatters(me, x, y)


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The holy water shimmers.")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_set_on_fire(self, 5000)
    my.chance_d1000_appearing(self, 10)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_food(self, True)
    my.is_holy(self, True)
    my.is_holy_water(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_throwable(self, True)
    my.is_treasure_class_A(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.noise_on_dropping(self, 55)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d1")
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_fall_do(self, "me.on_fall()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.rarity(self, my.RARITY_RARE)
    my.stat_luck_bonus(self, 2)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 LUCK")
    my.text_description_long2(self, "Ideal for those undead visitors that refuse to go away.")
    my.text_description_long(self, "A beaker of holy water. Quite how it got here and managed to be blessed in this accursed place is beyond me.")
    my.text_description_short(self, "A beaker of holy water.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="halo", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="holy_water", text_long_name="beaker of holy water", text_short_name="holy water")


init()
