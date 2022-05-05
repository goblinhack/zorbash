import my
import tp


def on_you_nat_attack(me, x, y):
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


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_shove_chance_d1000(self, 500)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_living(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.attacks_per_round(self, 2)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_nat_attack_chance_d1000(self, 0, 1000)
    my.damage_nat_attack_chance_d1000(self, 1, 1000)
    my.damage_nat_attack_type(self, "gore")
    my.damage_natural_dice(self, "3d8+6")
    my.distance_vision(self, 5)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_bounce_on_move(self, True)
    my.gfx_health_bar_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "11d8+44")
    my.hunger_is_insatiable(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shove(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fearless(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_poison(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_d(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.is_tireless(self, True)
    my.long_text_description(self, "A hideous mass of animated and moss covered stone. Stone golems are immune to cold, poison, fire and draining attacks. Stone golems are also able to slowly recharge health. Makes an excellent patio ornament.")
    my.monst_size(self, my.MONST_SIZE_LARGE)
    my.move_speed(self, 30)
    my.noise_decibels_hearing(self, 100)
    my.noise_on_moving(self, 20)
    my.normal_placement_rules(self, True)
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_RARE)
    my.shove_strength_mod(self, 3)
    my.stat_con(self, 18)
    my.stat_def(self, 17)
    my.stat_dex(self, 9)
    my.stat_luck(self, 1)
    my.stat_str(self, 22)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A stone golem.")
    my.text_hits(self, "claws")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 500
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".5", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.3", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="stone_golem", text_name="stone golem")


init()
