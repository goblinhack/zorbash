import my
import tp


def on_born(me, x, y):
    my.thing_friend(me, "is_molekin")


def on_you_nat_attack_attempt(me, x, y):
    sound = f"growl{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 50)
    my.ai_resent_count(self, 10)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.chance_d1000_jump_randomly(self, 20)
    my.chance_d1000_steal_item(self, 50)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 20)
    my.distance_avoid(self, 8)
    my.distance_vision(self, 3)
    my.dmg_nat_att_dice(self, "1d12+8")
    my.dmg_nat_att_type(self, "claw")
    my.dmg_received_doubled_from_fire(self, True)
    my.dmg_received_doubled_from_poison(self, True)
    my.environ_dislikes_poison(self, 100)
    my.environ_hates_fire(self, 10)
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
    my.health_initial_dice(self, "3d8")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_rest(self, True)
    my.is_able_to_run_away_after_stealing(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at_close_range(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_swim(self, True)
    my.is_able_to_tire(self, True)
    my.is_able_to_use_ranged_weapons(self, True)
    my.is_air_breather(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_sewer(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_cowardly(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_food(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_mantisman(self, True)
    my.is_meat(self, True)
    my.is_molekin(self, True)
    my.is_monst_class_C(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_thief(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 3)
    my.light_color(self, "green")
    my.light_dist(self, 1)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 45)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d6")
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_UNCOMMON)  # how rare within this monster class
    my.shove_strength_mod(self, 2)
    my.spawn_group_radius(self, 4)
    my.spawn_group_size_dice(self, "1d4+3")
    my.stamina(self, 100)
    my.stat_con(self, 10)
    my.stat_def(self, 12)
    my.stat_dex(self, 8)
    my.stat_luck(self, 8)
    my.stat_str(self, 12)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Beware the fearsome mandible bite of the mantisman.")
    my.text_description_long(self, "Half man, half mantis, the unsurprisingly called, mantisman are often shunned by society due to their abysmal table manners. They lurk the halls of dungeons, messily consuming whatever they find there.")
    my.text_description_short(self, "Mantisman")
    my.text_hits(self, "claws")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 150
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="mantisman.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="mantisman.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="mantisman.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile="mantisman.4", delay_ms=delay)
    delay = 150
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="mantisman.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="mantisman", text_long_name="mantisman")


init()
