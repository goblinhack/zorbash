import my
import tp


def on_death(me, x, y):
    my.thing_msg(me, "The spectral blade vanishes!")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_humanoid(self, True)
    my.chance_d1000_tameable(self, 0)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_minion_from_mob_max(self, 4)
    my.distance_minion_vision_shared(self, True)
    my.distance_vision(self, 8)
    my.dmg_chance_d1000_nat_att(self, 0, 1000)
    my.dmg_nat_att_dice(self, "1d3")
    my.dmg_nat_att_type(self, "slices")
    my.dmg_num_of_attacks(self, 1)
    my.dmg_rcv_doubled_from_fire(self, True)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_centered(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at_close_range(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_ethereal(self, True)
    my.is_fearless(self, True)
    my.is_floating(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_blinding(self, True)
    my.is_immune_to_confusion(self, True)
    my.is_immune_to_entrancement(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_paralysis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_minion(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_not_shown_as_a_pet(self, True)
    my.is_shootable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "white")
    my.light_dist(self, 1)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 0)
    my.noise_on_moving(self, 0)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.rarity(self, my.RARITY_UNIQUE)  # how rare within this monster class
    my.stat_con(self, 10)
    my.stat_def(self, 10)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_psi(self, 0)
    my.stat_str(self, 10)
    my.temperature_max(self, 50)
    my.temperature_min(self, -50)
    my.temperature(self, 0)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A phantom blade that just wants to play.")
    my.text_description_short(self, "A spectral blde.")
    my.text_hits(self, "slices")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 25
    name = "spectral_blade"

    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="white",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="white",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="/", ascii_fg_col_name="white",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="|", ascii_fg_col_name="white",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="\\", ascii_fg_col_name="white",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="-", ascii_fg_col_name="white",
            tile=name + ".8", delay_ms=delay)


def init():
    tp_init(name="spectral_blade_minion", text_long_name="spectral blade", text_short_name="spectral blade")


init()
