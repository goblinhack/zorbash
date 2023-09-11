import my
import tp


def on_thrown(owner, me, x, y):
    shatters(me, me, x, y)


def on_use(owner, item, target, x, y):
    owner = my.thing_top_owner_id_get(item)
    if owner:
        my.thing_stat_psi_incr(owner, 1)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "The darkness envelops you!")
            my.thing_blinded_count_incr(owner, 30)
            my.thing_popup(owner, "!!!")
    for it in my.level_flood_fill_gas_get_all_grid_things(item, x, y, 3):
        my.spawn_darkness_around_thing(it, 1)
    my.thing_dead(item, "broken")


def shatters(item, target, x, y):
    if my.thing_is_dead(item):
        return

    owner = my.thing_top_owner_id_get(item)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "Your potion of darkness shatters.")
        else:
            my.thing_msg(owner, f"The {my.thing_name_get(owner)}'s potion of darkness shatters.")
    else:
        my.thing_msg(item, "The potion of darkness shatters.")

    for it in my.level_flood_fill_gas_get_all_grid_things(item, x, y, 3):
        my.spawn_darkness_around_thing(it, 1)
    my.thing_dead(item, "broken")


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    shatters(me, me, x, y)


def on_fire(me, x, y):
    shatters(me, me, x, y)


def on_fall(me, x, y):
    shatters(me, me, x, y)


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
    my.is_treasure_class_A(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 50)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "The darkness is so profound that not even other gasses may co-exist in the same tile.")
    my.text_description_long(self, "A bubbling black elixir that will spawn a thick gas cloud of utter darkness when opened. Use this cloud to escape your enemies. Or to get thoroughly lost.")
    my.text_description_short(self, "A potion of darkness.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="gray10",
            tile=name, delay_ms=500)

    my.tp_update(self)


def init():
    tp_init(name="potion_darkness", text_long_name="potion of darkness", text_short_name="potion, darkness")


init()
