import my
import tp


def on_you_natural_attack(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_firing_at_something(me, target, x, y):  # Return True on doing an action
    if my.pcg_randint(1, 10) < 8:
        sound = f"growl{my.non_pcg_randint(1, 10)}"
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)
        my.thing_fire_at(me, "projectile_acid", target)
        return True
    return False


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.aggression_level_pct(self, 100)
    my.ai_resent_count(self, 90)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.damage_natural_attack_chance_d1000(self, 100)
    my.damage_natural_attack_type(self, "bite")
    my.damage_natural_dice(self, "1d3+1")
    my.damage_poison_chance_d1000(self, 1000)
    my.damage_poison_dice(self, "1d20+10")
    my.damage_received_doubled_from_fire(self, True)
    my.distance_avoid(self, 2)
    my.distance_jump(self, 2)
    my.distance_teleport(self, 5)
    my.distance_vision(self, 3)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_cold(self, 100)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_poison(self, 100)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_bounce_on_move(self, True)
    my.gfx_health_bar_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_asleep(self, True)
    my.health_initial_dice(self, "2d6")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_fire_at(self, True)
    my.is_able_to_jump_attack_chance_d1000(self, 800)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_onto_chance_d1000(self, 100)
    my.is_able_to_jump_onto(self, True)
    my.is_able_to_jump_randomly_chance_d1000(self, 20)
    my.is_able_to_jump(self, True)
    my.is_able_to_jump_without_tiring(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_sleep(self, True)
    my.is_able_to_teleport_attack_chance_d1000(self, 100)
    my.is_able_to_teleport_attack(self, True)
    my.is_able_to_teleport_escape(self, True)
    my.is_able_to_teleport_without_tiring(self, True)
    my.is_able_to_tire(self, True)
    my.is_asleep_initially(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_breather(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_green_blood_eater(self, True)
    my.is_green_blooded(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_water(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_monst_class_b(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_poisonous_danger_level(self, 4)
    my.is_red_blood_eater(self, True)
    my.is_shovable(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.is_toughness_soft(self, True)
    my.long_text_description(self, "An oddly aggressive, shortsighted and intensely venomous toad with a knack for escaping delicate situations by teleporting. How a creature like this evolved is beyond me... Tastes awful on toast, probably due to its poison. Oh and it can fire acide blobs too. Avoid.")
    my.monst_size(self, my.MONST_SIZE_SMALL)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 10)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "-10")
    my.on_death_do(self, "me.on_death()")
    my.on_firing_at_something_do(self, "me.on_firing_at_something()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_natural_attack_do(self, "me.on_you_natural_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stamina(self, 100)
    my.stat_con(self, 10)
    my.stat_def(self, 8)
    my.stat_dex(self, 14)
    my.stat_luck(self, 10)
    my.stat_str(self, 7)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A hopping mad teletoad.")
    my.text_hits(self, "splats")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_NORMAL)

    delay = 10000
    my.tile(self, "teletoad.1", is_sleeping=True, delay_ms=delay)
    my.tile(self, "teletoad.2", is_sleeping=True, delay_ms=delay)
    delay = 150
    my.tile(self, "teletoad.1", delay_ms=delay)
    my.tile(self, "teletoad.2", delay_ms=delay)
    my.tile(self, "teletoad.3", delay_ms=delay)
    my.tile(self, "teletoad.4", delay_ms=delay)
    my.tile(self, "teletoad.5", delay_ms=delay)
    my.tile(self, "teletoad.6", delay_ms=delay)
    my.tile(self, "teletoad.7", delay_ms=delay)
    my.tile(self, "teletoad.8", delay_ms=delay)
    my.tile(self, "teletoad.9", delay_ms=delay)
    my.tile(self, "teletoad.dead", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="teletoad", text_name="teletoad")


init()
