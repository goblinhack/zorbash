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


def on_death(me, x, y):
    my.thing_msg(me, "The skeleton collapses into a pile of bones!")

    if my.non_pcg_randint(1, 2) == 1:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones1"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones1")
    else:
        if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "bones2"):
            my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "bones2")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # start sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 10)
    my.ai_shove_chance_d1000(self, 200)
    my.attack_humanoid(self, True)
    my.attack_lunge(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.damage_nat_att_dice(self, "1d3")
    my.damage_nat_att_type(self, "gore")
    my.damage_received_doubled_from_water(self, True)
    my.distance_mob_max(self, 10)
    my.distance_vision(self, 11)
    my.environ_avoids_water(self, 100)
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "3")
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shove(self, True)
    my.is_able_to_use_weapons(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_fearless(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_loggable(self, True)
    my.is_minion(self, True)
    my.is_monst_class_a(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_red_blood_eater(self, True)
    my.is_resurrectable(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.is_undead(self, True)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 50)
    my.noise_on_moving(self, 25)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.resurrect_dice(self, "1d20+30")
    my.stat_con(self, 9)
    my.stat_def(self, 13)
    my.stat_dex(self, 14)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.temperature(self, 5)
    my.text_a_or_an(self, "a")
    my.text_hits(self, "claws")
    my.text_long_description(self, "A collection of tortured bones, driven to wander the dungeon forever. Or at least until you release them. Such creatures abhor the cleansing powers of water.")
    my.text_short_description(self, "The bones of one surprised to be moving again.")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_left=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_up=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_down=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_right=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_left=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_left=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_left=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_left=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_up=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_up=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_up=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_up=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_down=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_down=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_down=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_down=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_right=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_right=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_right=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_right=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.1", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.2", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.3", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.4", is_dir_none=True, delay_ms=delay)

    #
    # Resurrecting
    #
    delay = 20
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="skeleton.dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="skeleton.dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="skeleton.dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile="skeleton.dead.4", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.dead.4", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.dead.3", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.dead.2", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="k", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile="skeleton.dead.1",
            is_resurrecting=True,
            is_end_of_anim=True,
            is_alive_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="skel_minion_wander", text_long_name="skeleton")


init()
