import my
import tp


def on_you_nat_attack_attempt(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_idle(me, x, y):
    if not my.level_is_acid_at(me, x, y):
        my.spawn_at_my_position(me, "acid1")


def on_death(me, x, y):
    my.spawn_at_my_position(me, "green_splatter")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.chance_d1000_tameable(self, 0)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_vision(self, 3)
    my.dmg_chance_d1000_nat_att(self, 0, 1000)
    my.dmg_limited_per_tick(self, True)
    my.dmg_nat_att_dice(self, "1d10")
    my.dmg_nat_att_type(self, "burn")
    my.dmg_rcv_doubled_from_cold(self, True)
    my.dmg_rcv_doubled_from_fire(self, True)
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
    my.health_initial_dice(self, "4d10+20")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_eat_rotting_food(self, True)
    my.is_able_to_eat_unpleasant_food(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_acid_blob(self, True)
    my.is_acid(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_bleeder(self, True)
    my.is_buffable(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
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
    my.is_gelatinous(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_A(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_shootable(self, True)
    my.is_soft(self, True)
    my.is_sticky(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "cyan")
    my.light_dist(self, 2)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 50)
    my.noise_on_moving(self, 15)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_idle_tick_freq_dice(self, "1d5:me.on_idle()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stat_con(self, 20)
    my.stat_def(self, 6)
    my.stat_dex(self, 3)
    my.stat_luck(self, 10)
    my.stat_psi(self, 0)
    my.stat_str(self, 14)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Acid blobs are, surprisingly highly acidic and ideal for getting rid of those extra pesky weapons you have.")
    my.text_description_short(self, "An acid blob.")
    my.text_hits(self, "burns")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CONSUMER)  # so it appears over things when consuming
    # end sort marker

    delay = 50
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".9", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".10", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".11", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".12", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".13", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".14", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".15", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".16", delay_ms=delay)
    my.tile(self,
            ascii_bg_char="block", ascii_fg_char="A", ascii_bg_col_name="", ascii_fg_col_name="cyan",
            tile=name + ".dead", delay_ms=delay, is_dead=True)

    my.tp_update(self)


def init():
    tp_init(name="acid_blob", text_long_name="acid blob", text_short_name="acid blob")


init()
