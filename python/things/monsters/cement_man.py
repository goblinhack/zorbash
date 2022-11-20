import my
import tp


def on_you_nat_att(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_tick(owner, me, x, y):
    if my.thing_health(me) < my.thing_health_max(me):
        my.thing_health_incr(me, 1)
        return True
    return False


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_living(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.attacks_per_round(self, 1)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_vision(self, 5)
    my.dmg_nat_att_chance_d1000(self, 0, 1000)
    my.dmg_nat_att_chance_d1000(self, 1, 1000)
    my.dmg_nat_att_dice(self, "3d8+6")
    my.dmg_nat_att_type(self, "gore")
    my.gfx_anim_use(self, "attack_claws")
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
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "11d8+44")
    my.hunger_is_insatiable(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shove_chance_d1000(self, 500)
    my.is_allied_with(self, "cement_man")
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fearless(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_d(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_shovable(self, True)
    my.is_stone(self, True)
    my.is_tickable(self, True)
    my.is_tireless(self, True)
    my.is_very_hard(self, True)
    my.move_speed(self, 30)
    my.noise_decibels_hearing(self, 100)
    my.noise_on_moving(self, 20)
    my.normal_placement_rules(self, True)
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_RARE)
    my.shove_strength_mod(self, 3)
    my.stat_att_penalty_when_in_deep_water(self, 5)
    my.stat_att_penalty_when_in_shallow_water(self, 2)
    my.stat_con(self, 18)
    my.stat_def_penalty_when_in_deep_water(self, 5)
    my.stat_def_penalty_when_in_shallow_water(self, 2)
    my.stat_def(self, 17)
    my.stat_dex(self, 9)
    my.stat_luck(self, 1)
    my.stat_str(self, 22)
    my.temperature(self, 20)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "claws")
    my.text_long_description2(self, "Cement men are able to slowly recharge health.")
    my.text_long_description3(self, "Makes an excellent patio ornament.")
    my.text_long_description(self, "A hideous mass of animated cement. Possibly brought into being by an evil necromancer who was annoyed with constant roadworks. Cement men are immune to cold, poison, fire and draining attacks.")
    my.text_short_description(self, "A cement man.")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BIG_MONST)
    # end sort marker

    delay = 500
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".5", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="C", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name + ".dead.3", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="cement_man", text_long_name="cement man")


init()
