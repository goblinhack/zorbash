import my
import tp


def on_idle(me, x, y):
    if not my.thing_is_sleeping(me):
        my.level_spawn_gas_poison_around_thing(me, 2)


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "green_splatter")


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_eater(self, True)
    my.tp_set_attack_engulf_chance_d1000(self, 1000)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 20)
    my.tp_set_damage_digest_dice(self, "1d10")
    my.tp_set_damage_natural_attack_type(self, "burn")
    my.tp_set_damage_natural_dice(self, "1d20")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_distance_vision(self, 5)
    my.tp_set_environ_avoids_acid(self, True)
    my.tp_set_environ_avoids_fire(self, 100)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "green_splatter")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_health_initial_dice(self, "1d10+10")
    my.tp_set_hunger_clock_tick_frequency(self, 50)
    my.tp_set_hunger_health_pct(self, 95)
    my.tp_set_hunger_is_insatiable(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_asleep_initially(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_engulfer(self, True)
    my.tp_set_is_green_blooded(self, True)
    my.tp_set_is_heavy(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_meat_eater(self, True)
    my.tp_set_is_monst_class_b(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_obstacle_when_dead(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_sticky(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_toughness_soft(self, True)
    my.tp_set_light_color(self, "green")
    my.tp_set_light_power(self, 2)
    my.tp_set_long_text_description(self, "Dungeon belchers are carnivorous plants that have evolved creative means of catching their prey. Beware their stench...")
    my.tp_set_monst_size(self, my.MONST_SIZE_LARGE)
    my.tp_set_noise_decibels_hearing(self, 50)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_nutrition_dice(self, "1d4")
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_idle_tick_frequency_dice(self, "1d5:me.on_idle()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stat_con(self, 20)
    my.tp_set_stat_def(self, 0)
    my.tp_set_stat_dex(self, 0)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 10)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A gaseous belcher. But don't call it that to its face.")
    my.tp_set_text_hits(self, "burns")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)  # so it appears over things when consuming

    delay = 200
    my.tp_set_tile(self, tile=name + "_awake.1", delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_awake.2", delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_awake.3", delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_awake.4", delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_dead.1", delay_ms=delay, is_dead=True)
    delay = 500
    my.tp_set_tile(self, tile=name + "_asleep.1", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_asleep.2", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_asleep.3", is_sleeping=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + "_asleep.2", is_sleeping=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="belcher", text_name="dungeon belcher", short_text_name="belcher")


init()
