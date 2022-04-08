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


def on_receiving_damage_lightning(me, hitter, x, y, damage):
    # my.topcon("hitter  {} {}".format(my.thing_name_get(hitter), my.thing_health(hitter)))
    owner = my.thing_top_owner_id_get(hitter)
    if (owner and my.thing_is_player(owner)) or my.thing_is_player(hitter):
        my.thing_msg(me, "The golem corpse twitches with renewed energy from the lightning.")
    my.thing_health_incr(me, damage)
    return 0


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_shove_chance_d1000(self, 200)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_living(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_nat_attack_chance_d1000(self, 0, 1000)
    my.damage_nat_attack_chance_d1000(self, 1, 1000)
    my.damage_nat_attack_type(self, "gore")
    my.damage_natural_dice(self, "2d8+4")
    my.damage_received_doubled_from_fire(self, True)
    my.distance_vision(self, 5)
    my.environ_avoids_fire(self, 100)
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
    my.is_immune_to_poison(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_c(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_red_blood_eater(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.is_tireless(self, True)
    my.long_text_description(self, "A hideous progeny of animated flesh that wishes to add your skin to its body mass. Golems are immune to cold, poison and stamina/draining attacks. They also gain health from lightning. Golems are also able to slowly recharge health. Reknowed for being no fun at parties.")
    my.monst_size(self, my.MONST_SIZE_LARGE)
    my.move_speed(self, 30)
    my.noise_decibels_hearing(self, 100)
    my.noise_on_moving(self, 20)
    my.normal_placement_rules(self, True)
    my.num_attacks(self, 2)
    my.on_receiving_damage_lightning_do(self, "me.on_receiving_damage_lightning()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_RARE)
    my.shove_strength_mod(self, 2)
    my.stat_con(self, 18)
    my.stat_def(self, 9)
    my.stat_dex(self, 9)
    my.stat_luck(self, 1)
    my.stat_str(self, 19)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A flesh golem.")
    my.text_hits(self, "claws")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 500
    my.tile(self, tile=name + ".1", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)
    my.tile(self, tile=name + ".3", delay_ms=delay)
    my.tile(self, tile=name + ".4", delay_ms=delay)
    my.tile(self, tile=name + ".5", delay_ms=delay)

    my.tile(self, tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.3", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="flesh_golem", text_name="flesh golem")


init()
