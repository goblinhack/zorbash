import my
import tp


def on_you_nat_att(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_death(me, x, y):
    explode(me, x, y)


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_msg(me, "The gas blob explodes!")
    my.spawn_at_my_position(me, "explosion_major")
    # my.spawn_radius_range(me, "fire", min=0, max=3)


def on_fire(me, x, y):
    explode(me, x, y)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.aggression_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_engulf_chance_d1000(self, 1000)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_digest_chance_d1000(self, 0, 1000)
    my.damage_digest_dice(self, "1d40")
    my.damage_nat_att_chance_d1000(self, 0, 1000)
    my.damage_nat_att_dice(self, "1d20")
    my.damage_nat_att_type(self, "burn")
    my.damage_received_doubled_from_acid(self, True)
    my.damage_received_doubled_from_cold(self, True)
    my.damage_received_doubled_from_fire(self, True)
    my.distance_vision(self, 5)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.health_initial_dice(self, "1")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_engulfer(self, True)
    my.is_gelatinous(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_b(self, True)
    my.is_monst(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.is_moveable(self, True)
    my.is_soft(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "pink")
    my.light_dist(self, 2)
    my.move_speed(self, 25)
    my.msg_is_seen(self, True)
    my.msg_is_wounded(self, True)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_con(self, 20)
    my.stat_def(self, 6)
    my.stat_dex(self, 3)
    my.stat_luck(self, 10)
    my.stat_str(self, 14)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "burns")
    my.text_long_description(self, "Gaseous blobs are lonely creatures that spend their lives wandering dungeons, yearning for companionship. As they tend to have explosive friendships... it is best to avoid these poor lonely creatures.")
    my.text_short_description(self, "A floating gaseous blob.")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CONSUMER)  # so it appears over things when consuming
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".8", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="blob", text_long_name="gaseous blob", text_short_name="gas blob")


init()
