import my
import tp


def on_you_nat_att(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_idle(me, x, y):
    if not my.thing_is_sleeping(me):
        my.spawn_gas_poison_around_thing(me, 1)


def on_death(me, x, y):
    my.spawn_at_my_position(me, "green_splatter")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.chance_d1000_attack_engulf(self, 1000)
    my.chance_d1000_dmg_digest(self, 0, 1000)
    my.chance_d1000_dmg_nat_att(self, 0, 1000)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 30)
    my.distance_vision(self, 5)
    my.dmg_digest_dice(self, "1d10")
    my.dmg_nat_att_dice(self, "1d20")
    my.dmg_nat_att_type(self, "burn")
    my.dmg_received_doubled_from_fire(self, True)
    my.environ_avoids_acid(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d10+10")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_asleep_initially(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_carnivorous_plant(self, True)
    my.is_combustible(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_engulfer(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_obs_when_dead(self, True)
    my.is_plant(self, True)
    my.is_shovable(self, True)
    my.is_soft(self, True)
    my.is_sticky(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_freq_dice(self, "1d5:me.on_idle()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stat_con(self, 20)
    my.stat_def(self, 0)
    my.stat_dex(self, 0)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Dungeon belchers are carnivorous plants that have evolved creative means of catching their prey. Beware their stench...")
    my.text_description_short(self, "A gaseous belcher. But don't call it that to its face.")
    my.text_hits(self, "burns")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_awake.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_awake.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_awake.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_awake.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + "_dead.1", delay_ms=delay, is_dead=True)
    delay = 500
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_asleep.1", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_asleep.2", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_asleep.3", is_sleeping=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + "_asleep.2", is_sleeping=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="belcher", text_long_name="dungeon belcher", text_short_name="belcher")


init()
