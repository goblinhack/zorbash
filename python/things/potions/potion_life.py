import my
import tp


def on_thrown(owner, me, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    for it in my.level_get_all(me, x, y):
        # my.con("it      {} {:X} {},{}".format(my.thing_name_get(it), it, x, y))
        if my.thing_is_alive_monst(it) or my.thing_is_player(it):
            on_use(owner, me, it, x, y)
            return

    my.thing_dead(me, "used")


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))
    my.thing_sound_play_channel(target, my.CHANNEL_WEAPON, "potion")
    my.thing_wake(target, "potion")

    my.thing_health_max_incr(target, 10)
    my.thing_stamina_max_incr(target, 10)

    my.thing_health_set(target, my.thing_health_max(target))
    my.thing_stamina_set(target, my.thing_stamina_max(target))

    my.thing_poisoned_amount_set(target, 0)

    my.thing_debuff_remove(target, "debuff_status_blinded")
    my.thing_debuff_remove(target, "debuff_status_confused")
    my.thing_debuff_remove(target, "debuff_status_hungry")
    my.thing_debuff_remove(target, "debuff_status_necrotized")
    my.thing_debuff_remove(target, "debuff_status_paralysis")
    my.thing_debuff_remove(target, "debuff_status_poisoned")
    my.thing_debuff_remove(target, "debuff_status_starving")
    my.thing_debuff_remove(target, "debuff_temporary_slow")
    my.thing_blinded_count_set(owner, 0)

    my.spawn_using_items_radius_range(target, item, target, "potion_effect")
    if my.thing_is_player(target):
        my.thing_msg(target, "%%fg=pink$You glow with renewed life.%%fg=reset$")
    else:
        my.thing_msg(target, f"The {my.thing_name_get(target)} glows with renewed life.")


def shatters(me, x, y):
    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(me, "Your potion of life shatters.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s potion of life shatters.")
    else:
        my.thing_msg(me, "The potion of life shatters.")

    my.spawn_at_my_position(me, "water")
    my.thing_dead(me, "broken")


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    shatters(me, x, y)


def on_fire(me, x, y):
    shatters(me, x, y)


def on_fall(me, x, y):
    shatters(me, x, y)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 5)
    my.environ_dislikes_fire(self, 20)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "500")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_drinkable(self, True)
    my.is_droppable(self, True)
    my.is_glass(self, True)
    my.is_health_booster(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_obs_shooting(self, True)
    my.is_potion(self, True)
    my.is_throwable(self, True)
    my.is_treasure_class_B(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 10)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Cures all known poison ailments and other... conditions.")
    my.text_description_long3(self, "Guaranteed to work or, well, let's face it, you're not going to make it back!")
    my.text_description_long4(self, "Contains no snake oil, guaranteed.")
    my.text_description_long5(self, "PT Barnum patent pending.")
    my.text_description_long(self, "A swirling elixir that permanently Increases your maximum health and stamina values by 10 and then restores you to your original pathetic mortal glory.")
    my.text_description_short(self, "Potion of life")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name, delay_ms=500)

    my.tp_update(self)


def init():
    tp_init(name="potion_life", text_long_name="potion of life", text_short_name="potion, life")


init()
