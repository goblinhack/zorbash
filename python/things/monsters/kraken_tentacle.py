import my
import tp


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_dmg_nat_att(self, 0, 900)
    my.chance_d1000_dmg_poison(self, 0, 500)
    my.chance_d1000_is_able_to_grapple(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 1)
    my.distance_minion_vision_shared(self, True)
    my.distance_mob_max(self, 3)
    my.distance_vision(self, 3)
    my.dmg_nat_att_dice(self, "1d3+1")
    my.dmg_nat_att_type(self, "lash")
    my.dmg_poison_dice(self, "1d8+1")
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d10")
    my.hunger_clock_tick_freq(self, 50)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_air_breather(self, True)
    my.is_always_submerged(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_deep_water_swimmer(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_green_blooded(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_limb(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_minion(self, True)
    my.is_monst_class_A(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_shallow_water_swimmer(self, True)
    my.is_soft(self, True)
    my.is_tentacle(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 50)
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 10)
    my.stat_def(self, 4)
    my.stat_dex(self, 5)
    my.stat_luck(self, 10)
    my.stat_str(self, 18)
    my.temperature_max(self, 50)
    my.temperature_min(self, -20)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A deadly kraken tentacle. Beware its grapple attack.")
    my.text_description_short(self, "A slimy tentacle.")
    my.text_hits(self, "bites")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 800
    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".6", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="t", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="kraken_tentacle", text_long_name="kraken tentacle")


init()
