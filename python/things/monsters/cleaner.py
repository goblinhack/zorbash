import my
import tp


def on_you_nat_attack_attempt(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_idle(me, x, y):
    if not my.level_is_acid_at(me, x, y):
        my.spawn_at_my_position(me, "acid1")


def on_move(me, x, y):
    for it in my.level_get_all(me, x, y):
        if my.thing_possible_to_attack(me, it):
            if my.thing_is_player(it):
                my.thing_msg(me, "The dungeon cleaner engulfs you!")
            else:
                my.thing_msg(me, f"The dungeon cleaner engulfs the {my.thing_name_get(it)}.")


def on_death(me, x, y):
    my.spawn_at_my_position(me, "green_splatter")


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_dead(me, "exploded")
    my.thing_msg(me, "The dungeon cleaner erupts in flaming goo!")
    my.spawn_at_my_position(me, "explosion_major")
    my.spawn_set_fire_to_things_around_me(me, "fire")
    my.spawn_at_my_position(me, "fire")


def on_fire(me, x, y):
    explode(me, x, y)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.capacity_height(self, 10)
    my.capacity_width(self, 10)
    my.chance_d1000_attack_engulf(self, 1000)
    my.chance_d1000_carrier_of_treasure_class_A(self, 1000)
    my.chance_d1000_carrier_of_treasure_class_B(self, 500)
    my.chance_d1000_carrier_of_treasure_class_C(self, 100)
    my.chance_d1000_steal_item(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 50)
    my.distance_vision(self, 3)
    my.dmg_chance_d1000_digest(self, 0, 1000)
    my.dmg_chance_d1000_nat_att(self, 0, 1000)
    my.dmg_digest_dice(self, "1d40")
    my.dmg_nat_att_dice(self, "1d20")
    my.dmg_nat_att_type(self, "burn")
    my.dmg_received_doubled_from_cold(self, True)
    my.dmg_received_doubled_from_fire(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "8d10+40")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_sewer(self, True)
    my.is_bleeder(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_amulets(self, True)
    my.is_eater_of_armor(self, True)
    my.is_eater_of_boots(self, True)
    my.is_eater_of_cloaks(self, True)
    my.is_eater_of_food(self, True)
    my.is_eater_of_gauntlets(self, True)
    my.is_eater_of_green_blood(self, True)
    my.is_eater_of_helmets(self, True)
    my.is_eater_of_magical_items(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_potions(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_eater_of_rings(self, True)
    my.is_eater_of_shields(self, True)
    my.is_eater_of_slime(self, True)
    my.is_eater_of_staffs(self, True)
    my.is_eater_of_treasure(self, True)
    my.is_eater_of_weapons(self, True)
    my.is_engulfer(self, True)
    my.is_gelatinous(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_interesting(self, True)
    my.is_item_collector(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_soft(self, True)
    my.is_sticky(self, True)
    my.is_thief(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_death_do(self, "me.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_idle_tick_freq_dice(self, "1d5:me.on_idle()")
    my.on_move_do(self, "me.on_move()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stat_con(self, 20)
    my.stat_def(self, 6)
    my.stat_dex(self, 3)
    my.stat_luck(self, 10)
    my.stat_str(self, 14)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Dungeon cleaners have evolved to scrub their domain of all messy organic matter. That means you. Cleaners leave a trail of corrosive slime in their wake. Avoid this. Cleaners also have a habit of eating your hard fought items.")
    my.text_description_short(self, "A dungeon auto cleaner slime thingy.")
    my.text_hits(self, "burns")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CONSUMER)  # so it appears over things when consuming
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="limegreen",
            tile=name + ".4", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cleaner", text_long_name="dungeon cleaner", text_short_name="cleaner")


init()
