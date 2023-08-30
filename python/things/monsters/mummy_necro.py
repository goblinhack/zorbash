import my
import tp


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(leader):
        my.thing_msg(me, "The mummy necromancer begins muttering some unknown words!")


def on_born(me, x, y):
    my.thing_msg(me, "Die mortal!")


def on_tick(owner, me, x, y):
    if my.py_pcg_random_range_inclusive(1, 100) < 90:
        return False

    risen = 0
    if my.thing_stat_con(me) > 1:
        followers = my.thing_all_followers_get(me)
        if followers is None:
            return False

        for follower in followers:
            if my.thing_is_dead_or_dying(follower):
                if my.thing_resurrect(follower, "arise"):
                    my.thing_stat_con_decr(me, 1)
                    my.thing_msg(me, "Arise my minion!")
                    my.thing_msg(follower, "Groan!")
                    if my.thing_stat_con(me) <= 1:
                        return True
                    risen += 1

    if risen > 0:
        return True
    return False


def on_death(me, x, y):
    followers = my.thing_all_followers_get(me)
    if followers is None:
        return False

    for follower in followers:
        if my.thing_is_resurrected_or_resurrecting(follower):
            my.thing_speaks(follower, "Free at last!")
            my.thing_perma_death(follower, "Leader died!")


def on_you_nat_attack_attempt(me, x, y):
    sound = f"growl{my.py_non_pcg_random_range_inclusive(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_hit_and_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_hit_dodge_do(me, hitter, x, y):
    sound = f"hiss{my.py_non_pcg_random_range_inclusive(1, 10)}"
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, sound)


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    my.thing_shoot_projectile_or_laser_at(me, "laser_lightning", target)
    return True


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_living(self, True)
    my.attack_meat(self, True)
    my.chance_d1000_carrier_of_treasure_class_C(self, 1000)
    my.chance_d1000_shooting(self, 300)
    my.chance_d1000_shove(self, 200)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 30)
    my.distance_leader_max(self, 5)
    my.distance_vision(self, 5)
    my.dmg_chance_d1000_nat_att(self, 0, 950)
    my.dmg_chance_d1000_necrosis(self, 0, 50)
    my.dmg_nat_att_dice(self, "1d6+2")
    my.dmg_nat_att_type(self, "gore")
    my.dmg_necrosis_dice(self, "1")
    my.dmg_received_doubled_from_fire(self, True)
    my.dmg_received_doubled_from_water(self, True)
    my.environ_hates_fire(self, 100)
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
    my.health_initial_dice(self, "2d8")
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_resurrected(self, True)
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_fearless(self, True)
    my.is_green_blooded(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_stamina_drain(self, True)
    my.is_intelligent(self, True)
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
    my.is_mummy(self, True)
    my.is_necrotic_danger_level(self, 1)  # danger level
    my.is_shovable(self, True)
    my.is_tickable(self, True)
    my.is_undead(self, True)
    my.move_speed(self, 100)
    my.noise_decibels_hearing(self, 50)
    my.noise_on_moving(self, 5)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_hit_and_still_alive_do(self, "me.on_hit_and_still_alive()")
    my.on_hit_dodge_do(self, "me.on_hit_dodge_do()")
    my.on_tick_do(self, "me.on_tick()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.on_you_nat_attack_attempt_do(self, "me.on_you_nat_attack_attempt()")
    my.rarity(self, my.RARITY_UNCOMMON)  # how rare within this monster class
    my.resurrect_dice(self, "1d10+30")
    my.stat_con(self, 15)
    my.stat_def(self, 11)
    my.stat_dex(self, 10)
    my.stat_int(self, 14)
    my.stat_luck(self, 10)
    my.stat_psi(self, 14)
    my.stat_str(self, 16)
    my.temperature(self, 5)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A corpse wrapped in once fine linens and bathed in the essence of evil. Unlike most corpses, this one likes to wander around with its minions. Beware of the dark powers this mummy can wield. Likes to keep pet snakes.")
    my.text_description_short(self, "A mummy necromancer.")
    my.text_hits(self, "claws")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray80",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray80",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray80",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray80",
            tile=name + ".4", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.4", is_dead=True, is_end_of_anim=True)

    delay = 200
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.4", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.3", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.2", is_resurrecting=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="M", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.1",
            is_resurrecting=True,
            is_end_of_anim=True,
            is_alive_on_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="mummy_necro", text_long_name="mummy necromancer")


init()
