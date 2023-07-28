import my
import tp


def on_you_nat_attack_attempt(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_hit_dodge_do(me, hitter, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_death(me, x, y):
    my.thing_msg(me, "The skeleton collapses into a huge pile of bones!")
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")


def on_receiving_dmg_melee(me, hitter, real_hitter, x, y, damage):
    # my.topcon("hitter  {} {}".format(my.thing_name_get(hitter), my.thing_health(hitter)))
    if my.thing_is_pointy(hitter):
        if my.thing_is_player(real_hitter):
            my.thing_msg(me, "The {} takes half damage from your {}.".format(
                         my.thing_name_get(me), my.thing_name_get(hitter)))
        return int(damage / 2)
    return damage


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 10)
    my.ai_wanderer(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_shove(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 50)
    my.distance_avoid(self, 2)
    my.distance_vision(self, 7)
    my.dmg_nat_att_dice(self, "1d6")
    my.dmg_nat_att_type(self, "gore")
    my.dmg_received_doubled_from_water(self, True)
    my.environ_hates_water(self, 100)
    my.gfx_anim_use(self, "attack_red")
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
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "10d12+50")
    my.is_able_to_be_resurrected(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_see_through_doors(self, True)
    my.is_able_to_use_weapons(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_fearless(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_stamina_drain(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_C(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_shovable(self, True)
    my.is_skeleton(self, True)
    my.is_tickable(self, True)
    my.is_undead(self, True)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 50)
    my.noise_on_moving(self, 45)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_receiving_dmg_melee_do(self, "me.on_receiving_dmg_melee()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.resurrect_dice(self, "1d20+30")
    my.stat_con(self, 20)
    my.stat_def(self, 17)
    my.stat_dex(self, 10)
    my.stat_int(self, 8)
    my.stat_luck(self, 10)
    my.stat_psi(self, 8)
    my.stat_str(self, 21)
    my.temperature(self, 5)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A monstrous skeleton. It towers above you. It seems unhappy. Quite what body this skeleton came from, you hope not to find out. Water and fire are your friends here with creatures like this. Watch, these can rise again!")
    my.text_description_short(self, "A monstrous skeleton, possibly unfriendly.")
    my.text_hits(self, "claws")
    my.thing_size(self, my.THING_SIZE_GIANT)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_left=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_left=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_left=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_left=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_up=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_up=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_up=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_up=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_down=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_down=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_down=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_down=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_right=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_right=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_right=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_right=True, delay_ms=delay)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", is_dir_none=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", is_dir_none=True, delay_ms=delay)

    #
    # Resurrecting
    #
    delay = 20
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.4", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".dead.4", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".dead.3", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".dead.2", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="K", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".dead.1",
            is_resurrecting=True,
            is_end_of_anim=True,
            is_alive_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="skel_giant", text_long_name="giant skeleton")


init()
