import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "gnome_thief")
    my.thing_friend(me, "gnome_dwarf")
    my.thing_friend(me, "gnome_rock")
    my.thing_friend(me, "gnome_knight")


def on_you_nat_attack_attempt(me, x, y):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_death(me, x, y):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monst_death1"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 25)
    my.ai_detect_secret_doors(self, True)
    my.ai_resent_count(self, 20)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_undead(self, True)
    my.capacity_height(self, 5)
    my.capacity_width(self, 5)
    my.chance_d1000_shooting_avoid_friends(self, 50)
    my.chance_d1000_shooting(self, 500)
    my.chance_d1000_shove(self, 500)
    my.chance_d1000_steal_item(self, 200)
    my.chance_d1000_tameable(self, 0)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 10)
    my.distance_avoid(self, 5)
    my.distance_leader_max(self, 5)
    my.distance_throw(self, 8)
    my.distance_vision(self, 7)
    my.dmg_limited_per_tick(self, True)
    my.dmg_nat_att_dice(self, "1d2+1")
    my.dmg_nat_att_type(self, "stab")
    my.environ_dislikes_acid(self, 100)
    my.environ_dislikes_fire(self, 10)
    my.environ_dislikes_poison(self, 100)
    my.gfx_anim_use(self, "attack_red")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.has_a_head(self, True)
    my.health_initial_dice(self, "1d6")
    my.hunger_clock_tick_freq(self, 50)
    my.is_able_to_attack_mobs(self, True)
    my.is_able_to_attack_totems(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_break_down_doors(self, True)
    my.is_able_to_break_out_of_ice(self, True)
    my.is_able_to_break_out_of_webs(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_follow(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump(self, True)
    my.is_able_to_learn_skills(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_move_diagonally(self, True)
    my.is_able_to_open_doors(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at_close_range(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_tire(self, True)
    my.is_able_to_use_ranged_weapons(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bleeder(self, True)
    my.is_buffable(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_daring(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_explorer(self, True)
    my.is_hittable(self, True)
    my.is_humanoid(self, True)
    my.is_immune_to_poison(self, True)
    my.is_intelligent(self, True)
    my.is_interesting(self, True)
    my.is_item_carrier(self, True)
    my.is_item_collector(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_red_blooded(self, True)
    my.is_shootable(self, True)
    my.is_shovable(self, True)
    my.is_thief(self, 5)
    my.is_tickable(self, True)
    my.jump_distance(self, 3)
    my.move_speed(self, 150)
    my.noise_decibels_hearing(self, 5)
    my.noise_on_moving(self, 5)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "gnome_all.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_hit_and_still_alive_do(self, "gnome_all.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "gnome_all.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "gnome_all.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stamina(self, 100)
    my.stat_att_penalty_when_idle_max(self, 0)
    my.stat_att_penalty_when_idle(self, 0)
    my.stat_att_penalty_when_in_deep_water(self, 2)
    my.stat_att_penalty_when_in_shallow_water(self, 1)
    my.stat_att_penalty_when_stuck_max(self, 2)
    my.stat_att_penalty_when_stuck(self, 1)
    my.stat_con(self, 10)
    my.stat_def_penalty_when_idle_max(self, 5)
    my.stat_def_penalty_when_idle(self, 5)
    my.stat_def_penalty_when_in_deep_water(self, 2)
    my.stat_def_penalty_when_in_shallow_water(self, 1)
    my.stat_def_penalty_when_stuck_max(self, 15)
    my.stat_def_penalty_when_stuck(self, 10)
    my.stat_def(self, 10)
    my.stat_dex(self, 14)
    my.stat_luck(self, 12)
    my.stat_psi(self, 8)
    my.stat_str(self, 6)
    my.stat_thv(self, 14)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Watch your items as gnomes are proficient thieves, or as they call themselves small business people.")
    my.text_description_long(self, "Gnomes stand tall and proud. They have bright eyes and keen vision in the dark. They take great pride in their noses and do not think very highly of your normal sized conk.")
    my.text_hits(self, "claws")
    my.thing_size(self, my.THING_SIZE_SMALL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker
    return self
