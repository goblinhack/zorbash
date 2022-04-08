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


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 10) < 3:
        my.thing_fire_at(me, "projectile_fire", target)
        return True
    return False


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_nat_attack_type(self, "bite")
    my.damage_natural_dice(self, "2d6")
    my.damage_received_doubled_from_cold(self, True)
    my.distance_avoid(self, 4)
    my.distance_vision(self, 8)
    my.environ_avoids_cold(self, 10)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_bounce_on_move(self, True)
    my.gfx_health_bar_shown(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_asleep(self, True)
    my.gfx_show_outlined(self, True)
    my.health_initial_dice(self, "9d4+18")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fire_at(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fire(self, True)
    my.is_floating(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_poison(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_c(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.is_toughness_soft(self, True)
    my.is_undead(self, True)
    my.light_color(self, "orange")
    my.light_dist(self, 2)
    my.long_text_description(self, "This disembodied skull blasts foes with its fiery eyes, all the while laughing maniacally.")
    my.monst_size(self, my.MONST_SIZE_SMALL)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_UNCOMMON)
    my.stamina(self, 100)
    my.stat_con(self, 14)
    my.stat_def(self, 13)
    my.stat_dex(self, 17)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A floating fire hazard.")
    my.text_hits(self, "slashes")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 100
    my.tile(self, tile=name + ".1", delay_ms=delay)
    my.tile(self, tile=name + ".2", delay_ms=delay)
    my.tile(self, tile=name + ".3", delay_ms=delay)
    my.tile(self, tile=name + ".4", delay_ms=delay)

    my.tile(self, tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self, tile=name + ".dead.4", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="flameskull", text_name="flameskull")


init()
