import my
import tp


def on_you_nat_att(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_you_are_hit_but_dodge_it_do(me, hitter, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "monster_roar")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "monst_death1")
    my.thing_polymorph(me, "gargoyle_moving")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_resent_count(self, 100)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_vision(self, 10)
    my.dmg_nat_att_dice(self, "1d6+2")
    my.dmg_nat_att_type(self, "gore")
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergable(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "7d8+20")
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump_attack_chance_d1000(self, 100)
    my.is_able_to_jump_attack(self, True)
    my.is_able_to_jump_escape(self, True)
    my.is_able_to_jump_on_low_hp_chance_d1000(self, 500)
    my.is_able_to_jump(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_corpse_on_death(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_c(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_shovable(self, True)
    my.is_stone(self, True)
    my.is_tickable(self, True)
    my.is_very_hard(self, True)
    my.is_very_heavy(self, True)
    my.jump_distance(self, 2)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 60)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_want_to_fire_at_something_do(self, "me.on_want_to_fire_at_something()")
    my.on_you_are_hit_but_dodge_it_do(self, "me.on_you_are_hit_but_dodge_it_do()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_att_mod(self, 4)
    my.stat_con(self, 16)
    my.stat_def(self, 17)
    my.stat_dex(self, 11)
    my.stat_luck(self, 10)
    my.stat_str(self, 15)
    my.temperature(self, 20)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "an")
    my.text_description_long(self, "These monstrous creatures guard the dungeon from the likes of you. This particular gargoyle has been unleashed, to roam the dungeon with impunitiy.")
    my.text_description_short(self, "A fearsome gargoyle.")
    my.text_hits(self, "slashes")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray70",
            tile="gargoyle.moving.7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="G", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile="gargoyle.moving.dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gargoyle_moving", text_long_name="unleashed gargoyle")


init()
