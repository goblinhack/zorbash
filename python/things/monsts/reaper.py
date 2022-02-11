import my
import tp


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_resent_count(self, 100)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_humanoid(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_natural_attack_type(self, "touch")
    my.tp_set_damage_natural_dice(self, "1d6+6")
    my.tp_set_damage_received_doubled_from_water(self, True)
    my.tp_set_distance_vision(self, 7)
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "scythe_swing")
    my.tp_set_gfx_bounce_on_move(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_health_initial_dice(self, "2d20+200")
    my.tp_set_is_able_to_change_levels(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_ethereal(self, True)
    my.tp_set_is_fearless(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_acid(self, True)
    my.tp_set_is_immune_to_cold(self, True)
    my.tp_set_is_immune_to_fire(self, True)
    my.tp_set_is_immune_to_necrosis(self, True)
    my.tp_set_is_immune_to_poison(self, True)
    my.tp_set_is_immune_to_water(self, True)
    my.tp_set_is_intelligent(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_monst_class_c(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_resurrectable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_undead(self, True)
    my.tp_set_long_text_description(self, "A lesser reaper. You cannot defeat what does not live!")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 0)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_rarity(self, my.RARITY_VERY_RARE)
    my.tp_set_resurrect_dice(self, "1d10+30")
    my.tp_set_stat_con(self, 25)
    my.tp_set_stat_def(self, 25)
    my.tp_set_stat_dex(self, 10)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 25)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A lesser reaper. Death incarnate.")
    my.tp_set_text_hits(self, "claws")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 1000
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)

    delay = 20
    my.tp_set_tile(self, tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    my.tp_set_tile(self, tile=name + ".5.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self, tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    my.tp_set_tile(self,
        tile=name + ".1.dead",
        is_resurrecting=True,
        is_end_of_anim=True,
        is_alive_on_end_of_anim=True,
    )

    my.tp_update(self)


def init():
    tp_init(name="reaper", text_name="reaper")


init()
