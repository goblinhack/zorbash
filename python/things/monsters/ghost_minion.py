import my
import tp


def on_you_nat_att(me, x, y):
    sound = f"hiss{my.non_pcg_randint(1, 10)}"
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, sound)


def on_death(me, x, y):
    my.spawn_at_my_position(me, "ghost_explosion")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.attack_humanoid(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_minion_vision_shared(self, True)
    my.distance_mob_max(self, 4)
    my.distance_vision(self, 7)
    my.dmg_cold_dice(self, "1")
    my.gfx_anim_use(self, "attack_claws")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_glows(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1")
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_see_invisible(self, True)
    my.is_able_to_walk_through_walls(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_ethereal(self, True)
    my.is_fearless(self, True)
    my.is_floating(self, True)
    my.is_green_blooded(self, True)  # not really
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_draining(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_water(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_minion(self, True)
    my.is_monst_class_A(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_surprised(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_tickable(self, True)
    my.is_undead(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.move_speed(self, 200)
    my.noise_decibels_hearing(self, 0)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_con(self, 10)
    my.stat_def(self, 11)
    my.stat_dex(self, 13)
    my.stat_luck(self, 8)
    my.stat_str(self, 7)
    my.temperature(self, 0)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "The spirit of one less fortunate than you. Beware, ghosts can traverse chasms that you cannot.")
    my.text_description_short(self, "The angry spirit of one long passed.")
    my.text_hits(self, "touches")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MONST)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="white",
            tile="ghost.1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="gray90",
            tile="ghost.2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="gray80",
            tile="ghost.3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="gray70",
            tile="ghost.4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="gray60",
            tile="ghost.5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="gray30",
            tile="ghost.6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_fg_col_name="gray30",
            tile="ghost.7", delay_ms=delay, is_invisible=True)
    my.tile(self,
            ascii_fg_char="", ascii_fg_col_name="none",
            tile="ghost.8", delay_ms=delay, is_invisible=True)
    my.tile(self,
            ascii_fg_char="", ascii_fg_col_name="none",
            tile="ghost.9", delay_ms=delay, is_invisible=True)
    my.tile(self,
            ascii_fg_char="", ascii_fg_col_name="none",
            tile="ghost.10", delay_ms=delay, is_invisible=True)
    my.tile(self,
            ascii_fg_char="", ascii_fg_col_name="none",
            tile="ghost.11", delay_ms=delay, is_invisible=True)

    my.tp_update(self)


def init():
    tp_init(name="ghost_minion", text_long_name="ghost")


init()
