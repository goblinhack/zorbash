import my
import tp


def on_targetted(me, x, y):
    radius = my.thing_effect_radius_get(me)
    # my.con("targetted {} {:X}".format(my.thing_name_get(me), me))

    for dx in range(-radius, radius + 1):
        for dy in range(-radius, radius + 1):
            x1 = x + dx
            y1 = y + dy
            distance = (((x1 - x)**2 + (y1 - y)**2)**0.5)
            if distance > radius + 0.5:
                continue

            my.place_at(me, "magical_effect", x1, y1)
            for it in my.level_get_all(me, x1, y1):
                if my.thing_possible_to_attack(me, it):
                    my.thing_hit(me, it)


def on_targetted_radially(me, x, y):
    radius = my.thing_effect_radius_get(me)
    radius += 1
    # my.con("targetted radially {} {:X}".format(my.thing_name_get(me), me))

    for dx in range(-radius, radius + 1):
        for dy in range(-radius, radius + 1):
            if dx == 0 and dy == 0:
                continue
            x1 = x + dx
            y1 = y + dy
            distance = (((x1 - x)**2 + (y1 - y)**2)**0.5)
            if distance > radius + 0.5:
                continue

            my.place_at(me, "magical_effect", x1, y1)
            for it in my.level_get_all(me, x1, y1):
                if my.thing_possible_to_attack(me, it):
                    my.thing_hit(me, it)


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_charge_count(me) < my.thing_initial_charge_count_get(me):
        my.thing_charge_count_incr(me, 1)
        owner = my.thing_top_owner_id_get(me)
        if my.thing_is_player(owner):
            my.thing_msg(me, f"%%fg=orange$The {my.thing_name_get(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    if my.thing_charge_count(me) == 0:
        return

    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(me, "Your staff of negation explodes.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s staff of negation explodes.")
    else:
        my.thing_msg(me, "The staff of negation explodes.")

    my.spawn_at_my_position(me, "explosion_major")
    my.spawn_set_fire_to_things_around_me(me, "fire")
    my.spawn_at_my_position(me, "fire")
    my.thing_dead(me, "exploded")


def on_thrown(me, x, y):
    if my.thing_charge_count(me) == 0:
        return
    if my.level_is_chasm_at(me, x, y):
        return
    if my.level_is_water_at(me, x, y):
        return
    explode(me, x, y)


def on_receiving_dmg_negation(me, hitter, x, y, damage):
    explode(me, x, y)
    return damage


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.charge_count(self, 5)
    my.collision_hit_priority(self, 6)
    my.dmg_negation_chance_d1000(self, 0, 1000)
    my.dmg_negation_dice(self, "1")  # This is the damage when the monst fires
    my.dmg_received_doubled_from_cold(self, True)
    my.environ_avoids_water(self, 100)
    my.equip_carry_anim(self, "staff_negation_carry")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_targetted_laser(self, "staff_negation_laser")
    my.gfx_targetted_radial(self, "staff_negation_radial")
    my.gold_value_dice(self, "300")
    my.health_initial_dice(self, "20+1d10")
    my.is_able_to_burn(self, True)
    my.is_able_to_fall(self, True)
    # my.is_able_to_spawn_things(self, False) else we end up owning effects
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_staff(self, True)
    my.is_target_radial(self, True)
    my.is_target_select(self, True)
    my.is_throwable(self, True)
    my.is_tickable(self, True)  # So it can interact with negation
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 5)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_idle_tick_freq_dice(self, "1d200+200:me.on_idle()")
    my.on_receiving_dmg_negation_do(self, "me.on_receiving_dmg_negation()")
    my.on_targetted_do(self, "me.on_targetted()")
    my.on_targetted_radially_do(self, "me.on_targetted_radially()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.range_max(self, 7)
    my.temperature(self, 30)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Discharges a single blast of negation at an ungrateful recipient and their equipment...")
    my.text_description_short(self, "A staff of negation.")
    my.tick_prio(self, my.MAP_TICK_PRIO_LOW)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="~", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", delay_ms=100)
    my.tile(self,
            ascii_fg_char="~", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="~", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="~", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="~", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="~", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="staff_negation", text_long_name="staff of negation", text_short_name="staff of negation")


init()
