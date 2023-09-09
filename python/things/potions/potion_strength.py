import my
import tp


def on_thrown(owner, me, x, y):
    shatters(me, x, y)


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))

    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "potion")

    stamina = my.thing_stamina(owner)
    new_stamina = int((float(my.thing_stamina_max(owner)) / 100.0) * 80.0)
    if new_stamina > stamina:
        my.thing_stamina_set(owner, new_stamina)

    my.thing_stat_str_incr(owner, 1)

    my.spawn_using_items_radius_range(owner, item, target, "potion_effect")
    if my.thing_is_player(owner):
        my.thing_msg(owner, "%%fg=pink$You look like you've been working out!%fg=reset$")


def shatters(me, x, y):
    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(me, "Your potion of strength shatters.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s potion of strength shatters.")
    else:
        my.thing_msg(me, "The potion of strength shatters.")

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
    my.collision_hit_priority(self, 6)
    my.environ_dislikes_fire(self, 20)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gold_value_dice(self, "250")
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
    my.is_treasure_class_A(self, True)
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
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "You'll feel like your old self again. Only even more awesome, if that could be possible...")
    my.text_description_long(self, "A bubbling red elixir that restores stamina and gives a permanent increase in strength.")
    my.text_description_short(self, "A potion of strength.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name, delay_ms=500)

    my.tp_update(self)


def init():
    tp_init(name="potion_strength", text_long_name="potion of strength", text_short_name="potion of strength")


init()
