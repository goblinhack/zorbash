import my
import tp


def on_you_nat_attack(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_idle(me, x, y):
    if not my.thing_is_sleeping(me):
        my.level_spawn_gas_poison_around_thing(me, 2)


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "green_splatter")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.aggression_level_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_engulf_chance_d1000(self, 1000)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_digest_dice(self, "1d10")
    my.damage_nat_attack_type(self, "burn")
    my.damage_natural_dice(self, "1d20")
    my.damage_received_doubled_from_fire(self, True)
    my.distance_vision(self, 5)
    my.environ_avoids_acid(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_mode_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.health_initial_dice(self, "1d10+10")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_asleep_initially(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_combustible(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_engulfer(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_monst_class_b(self, True)
    my.is_monst(self, True)
    my.is_obstacle_when_dead(self, True)
    my.is_shovable(self, True)
    my.is_soft(self, True)
    my.is_sticky(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.monst_size(self, my.MONST_SIZE_LARGE)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_death_do(self, "me.on_death()")
    my.on_idle_tick_freq_dice(self, "1d5:me.on_idle()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_con(self, 20)
    my.stat_def(self, 0)
    my.stat_dex(self, 0)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "burns")
    my.text_long_description(self, "Dungeon belchers are carnivorous plants that have evolved creative means of catching their prey. Beware their stench...")
    my.text_short_description(self, "A gaseous belcher. But don't call it that to its face.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CONSUMER)  # so it appears over things when consuming
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
            ascii_fg_char="B", ascii_bg_col_name="", ascii_fg_col_name="gray50",
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
