import my
import tp


def on_you_nat_att(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_tick(owner, me, x, y):
    if my.pcg_randint(1, 100) < 90:
        return False

    my.spawn_at_my_position(me, "fire")
    return True


def on_death(me, x, y):
    my.thing_msg(me, "The demon screams angrily and vanishes!")
    my.spawn_at_my_position(me, "fire")

    sound = f"growl{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    if my.pcg_randint(1, 10) < 3:
        my.thing_shoot_at(me, "staff_fire_projectile", target)
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
    my.attack_meat(self, True)
    my.attacks_per_round(self, 2)
    my.chance_d1000_dmg_nat_att(self, 0, 1000)
    my.chance_d1000_jump_attack(self, 800)
    my.chance_d1000_jump_onto(self, 100)
    my.chance_d1000_jump_randomly(self, 20)
    my.chance_d1000_shove(self, 200)
    my.chance_d1000_teleport_self(self, 50)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_vision(self, 7)
    my.dmg_nat_att_dice(self, "1d14+4")
    my.dmg_nat_att_type(self, "bludgeon")
    my.dmg_received_doubled_from_water(self, True)
    my.gfx_anim_use(self, "sword_plutonium_swing")
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
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "10d8")
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_see_through_doors(self, True)
    my.is_able_to_teleport_escape(self, True)
    my.is_able_to_teleport_self(self, True)
    my.is_able_to_teleport_without_tiring(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_daring(self, True)
    my.is_demon(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_ethereal(self, True)
    my.is_fearless(self, True)
    my.is_fire(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_intelligent(self, True)
    my.is_interesting(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_C(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_obs_when_dead(self, True)
    my.is_tickable(self, True)
    my.move_speed(self, 150)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_tick_do(self, "me.on_tick()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_UNCOMMON)  # how rare within this monster class
    my.shove_strength_mod(self, 1)
    my.stamina(self, 100)
    my.stat_con(self, 20)
    my.stat_def(self, 14)
    my.stat_dex(self, 8)
    my.stat_luck(self, 2)
    my.stat_str(self, 18)
    my.teleport_distance(self, 5)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Fire demons are formidable enemies. Execute extreme caution or be executed extremely...")
    my.text_description_long(self, "Accursed creature of the abyss. Devoid of life. Full of hatred, and just wants to get back to the pit so it can take care of its pet cats. And you are in the way...")
    my.text_description_short(self, "A hot fire demon.")
    my.text_hits(self, "whips")
    my.thing_size(self, my.THING_SIZE_GIANT)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 350
    my.tile(self,
            ascii_fg_char="D", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="D", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_fg_char="D", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_fg_char="T", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="demon_fire.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="demon_fire", text_long_name="fire demon")


init()
