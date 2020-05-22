import zx


class Tp:
    """thing template"""

    def __init__(self, name, real_name=None):
        self.name = name

        if real_name is None:
            self.real_name = name
        else:
            self.real_name = real_name

        #
        # Load it into the game engine
        #
        zx.tp_load(self)

    def update(self):
        zx.tp_update(self)

    def set_tile(self, tile=None, **kw):
        zx.tp_set_tile(self, tile, **kw)

    def set_left1_tile(self, left1_tile=None, **kw):
        zx.tp_set_left1_tile(self, left1_tile, **kw)

    def set_right1_tile(self, right1_tile=None, **kw):
        zx.tp_set_right1_tile(self, right1_tile, **kw)

    def set_bot1_tile(self, bot1_tile=None, **kw):
        zx.tp_set_bot1_tile(self, bot1_tile, **kw)

    def set_top1_tile(self, top1_tile=None, **kw):
        zx.tp_set_top1_tile(self, top1_tile, **kw)

    def set_tl1_tile(self, tl1_tile=None, **kw):
        zx.tp_set_tl1_tile(self, tl1_tile, **kw)

    def set_tr1_tile(self, tr1_tile=None, **kw):
        zx.tp_set_tr1_tile(self, tr1_tile, **kw)

    def set_br1_tile(self, br1_tile=None, **kw):
        zx.tp_set_br1_tile(self, br1_tile, **kw)

    def set_bl1_tile(self, bl1_tile=None, **kw):
        zx.tp_set_bl1_tile(self, bl1_tile, **kw)

    def set_left2_tile(self, left2_tile=None, **kw):
        zx.tp_set_left2_tile(self, left2_tile, **kw)

    def set_right2_tile(self, right2_tile=None, **kw):
        zx.tp_set_right2_tile(self, right2_tile, **kw)

    def set_bot2_tile(self, bot2_tile=None, **kw):
        zx.tp_set_bot2_tile(self, bot2_tile, **kw)

    def set_top2_tile(self, top2_tile=None, **kw):
        zx.tp_set_top2_tile(self, top2_tile, **kw)

    def set_tl2_tile(self, tl2_tile=None, **kw):
        zx.tp_set_tl2_tile(self, tl2_tile, **kw)

    def set_tr2_tile(self, tr2_tile=None, **kw):
        zx.tp_set_tr2_tile(self, tr2_tile, **kw)

    def set_br2_tile(self, br2_tile=None, **kw):
        zx.tp_set_br2_tile(self, br2_tile, **kw)

    def set_bl2_tile(self, bl2_tile=None, **kw):
        zx.tp_set_bl2_tile(self, bl2_tile, **kw)

    def set_name(self, value):
        zx.tp_set_name(self, value)

    def set_short_name(self, value):
        zx.tp_set_short_name(self, value)

    def set_blit_top_off(self, value):
        zx.tp_set_blit_top_off(self, value)

    def set_blit_bot_off(self, value):
        zx.tp_set_blit_bot_off(self, value)

    def set_blit_left_off(self, value):
        zx.tp_set_blit_left_off(self, value)

    def set_blit_right_off(self, value):
        zx.tp_set_blit_right_off(self, value)

    def set_is_gfx_animated(self, value):
        zx.tp_set_is_gfx_animated(self, value)

    def set_is_gfx_animated_no_dir(self, value):
        zx.tp_set_is_gfx_animated_no_dir(self, value)

    def set_is_gfx_an_animation_only(self, value):
        zx.tp_set_is_gfx_an_animation_only(self, value)

    def set_is_gfx_on_fire_anim(self, value):
        zx.tp_set_is_gfx_on_fire_anim(self, value)

    def set_is_monst(self, value):
        zx.tp_set_is_monst(self, value)

    def set_is_key(self, value):
        zx.tp_set_is_key(self, value)

    def set_is_floor_deco(self, value):
        zx.tp_set_is_floor_deco(self, value)

    def set_is_wall_deco(self, value):
        zx.tp_set_is_wall_deco(self, value)

    def set_is_player(self, value):
        zx.tp_set_is_player(self, value)

    def set_str_zzz1(self, value):
        zx.tp_set_str_zzz1(self, value)

    def set_str_zzz2(self, value):
        zx.tp_set_str_zzz2(self, value)

    def set_str_zzz3(self, value):
        zx.tp_set_str_zzz3(self, value)

    def set_str_zzz4(self, value):
        zx.tp_set_str_zzz4(self, value)

    def set_str_zzz5(self, value):
        zx.tp_set_str_zzz5(self, value)

    def set_str_zzz6(self, value):
        zx.tp_set_str_zzz6(self, value)

    def set_str_zzz7(self, value):
        zx.tp_set_str_zzz7(self, value)

    def set_str_zzz8(self, value):
        zx.tp_set_str_zzz8(self, value)

    def set_str_zzz9(self, value):
        zx.tp_set_str_zzz9(self, value)

    def set_str_zzz10(self, value):
        zx.tp_set_str_zzz10(self, value)

    def set_str_zzz11(self, value):
        zx.tp_set_str_zzz11(self, value)

    def set_str_zzz12(self, value):
        zx.tp_set_str_zzz12(self, value)

    def set_str_zzz13(self, value):
        zx.tp_set_str_zzz13(self, value)

    def set_str_zzz14(self, value):
        zx.tp_set_str_zzz14(self, value)

    def set_str_zzz15(self, value):
        zx.tp_set_str_zzz15(self, value)

    def set_a_or_an(self, value):
        zx.tp_set_a_or_an(self, value)

    def set_real_name(self, value):
        zx.tp_set_real_name(self, value)

    def set_light_color(self, value):
        zx.tp_set_light_color(self, value)

    def set_weapon_carry_anim(self, value):
        zx.tp_set_weapon_carry_anim(self, value)

    def set_weapon_use_anim(self, value):
        zx.tp_set_weapon_use_anim(self, value)

    def set_is_rrr1(self, value):
        zx.tp_set_is_rrr1(self, value)

    def set_is_rrr2(self, value):
        zx.tp_set_is_rrr2(self, value)

    def set_is_rrr3(self, value):
        zx.tp_set_is_rrr3(self, value)

    def set_is_rrr4(self, value):
        zx.tp_set_is_rrr4(self, value)

    def set_is_rrr5(self, value):
        zx.tp_set_is_rrr5(self, value)

    def set_is_rrr6(self, value):
        zx.tp_set_is_rrr6(self, value)

    def set_is_rrr7(self, value):
        zx.tp_set_is_rrr7(self, value)

    def set_is_rrr8(self, value):
        zx.tp_set_is_rrr8(self, value)

    def set_is_rrr9(self, value):
        zx.tp_set_is_rrr9(self, value)

    def set_is_rrr10(self, value):
        zx.tp_set_is_rrr10(self, value)

    def set_is_rrr11(self, value):
        zx.tp_set_is_rrr11(self, value)

    def set_is_rrr12(self, value):
        zx.tp_set_is_rrr12(self, value)

    def set_is_rrr13(self, value):
        zx.tp_set_is_rrr13(self, value)

    def set_is_rrr14(self, value):
        zx.tp_set_is_rrr14(self, value)

    def set_is_rrr15(self, value):
        zx.tp_set_is_rrr15(self, value)

    def set_is_rrr16(self, value):
        zx.tp_set_is_rrr16(self, value)

    def set_is_rrr17(self, value):
        zx.tp_set_is_rrr17(self, value)

    def set_is_rrr18(self, value):
        zx.tp_set_is_rrr18(self, value)

    def set_is_rrr19(self, value):
        zx.tp_set_is_rrr19(self, value)

    def set_is_rrr20(self, value):
        zx.tp_set_is_rrr20(self, value)

    def set_is_rrr21(self, value):
        zx.tp_set_is_rrr21(self, value)

    def set_is_rrr22(self, value):
        zx.tp_set_is_rrr22(self, value)

    def set_is_rrr23(self, value):
        zx.tp_set_is_rrr23(self, value)

    def set_is_rrr24(self, value):
        zx.tp_set_is_rrr24(self, value)

    def set_is_rrr25(self, value):
        zx.tp_set_is_rrr25(self, value)

    def set_is_rrr26(self, value):
        zx.tp_set_is_rrr26(self, value)

    def set_is_loggable(self, value):
        zx.tp_set_is_loggable(self, value)

    def set_is_torch(self, value):
        zx.tp_set_is_torch(self, value)

    def set_is_gfx_bounce_always(self, value):
        zx.tp_set_is_gfx_bounce_always(self, value)

    def set_normal_placement_rules(self, value):
        zx.tp_set_normal_placement_rules(self, value)

    def set_is_flammable(self, value):
        zx.tp_set_is_flammable(self, value)

    def set_is_combustible(self, value):
        zx.tp_set_is_combustible(self, value)

    def set_is_gfx_attack_anim(self, value):
        zx.tp_set_is_gfx_attack_anim(self, value)

    def set_is_attack_shove_chance_d1000(self, value):
        zx.tp_set_is_attack_shove_chance_d1000(self, value)

    def set_is_chasm(self, value):
        zx.tp_set_is_chasm(self, value)

    def set_is_hazard(self, value):
        zx.tp_set_is_hazard(self, value)

    def set_is_attack_shove(self, value):
        zx.tp_set_is_attack_shove(self, value)

    def set_is_shovable(self, value):
        zx.tp_set_is_shovable(self, value)

    def set_is_cursor_path(self, value):
        zx.tp_set_is_cursor_path(self, value)

    def set_is_blood_splatter(self, value):
        zx.tp_set_is_blood_splatter(self, value)

    def set_is_no_tile(self, value):
        zx.tp_set_is_no_tile(self, value)

    def set_is_msg(self, value):
        zx.tp_set_is_msg(self, value)

    def set_is_attack_lunge(self, value):
        zx.tp_set_is_attack_lunge(self, value)

    def set_stats_strength(self, value):
        zx.tp_set_stats_strength(self, value)

    def set_stats_defence(self, value):
        zx.tp_set_stats_defence(self, value)

    def set_stats_attack(self, value):
        zx.tp_set_stats_attack(self, value)

    def set_stats_attack_rate_tenths(self, value):
        zx.tp_set_stats_attack_rate_tenths(self, value)

    def set_lifespan_count(self, value):
        zx.tp_set_lifespan_count(self, value)

    def set_is_secret_door(self, value):
        zx.tp_set_is_secret_door(self, value)

    def set_is_cursor_can_hover_over(self, value):
        zx.tp_set_is_cursor_can_hover_over(self, value)

    def set_is_cursor(self, value):
        zx.tp_set_is_cursor(self, value)

    def set_is_gfx_dead_anim(self, value):
        zx.tp_set_is_gfx_dead_anim(self, value)

    def set_ai_obstacle(self, value):
        zx.tp_set_ai_obstacle(self, value)

    def set_is_attackable(self, value):
        zx.tp_set_is_attackable(self, value)

    def set_is_food(self, value):
        zx.tp_set_is_food(self, value)

    def set_is_water_hater(self, value):
        zx.tp_set_is_water_hater(self, value)

    def set_is_hunger_insatiable(self, value):
        zx.tp_set_is_hunger_insatiable(self, value)

    def set_is_undead(self, value):
        zx.tp_set_is_undead(self, value)

    def set_is_rrr16(self, value):
        zx.tp_set_is_rrr16(self, value)

    def set_is_nutrition_hd(self, value):
        zx.tp_set_is_nutrition_hd(self, value)

    def set_stats_attack_hd(self, value):
        zx.tp_set_stats_attack_hd(self, value)

    def set_collision_check(self, value):
        zx.tp_set_collision_check(self, value)

    def set_collision_attack(self, value):
        zx.tp_set_collision_attack(self, value)

    def set_is_water_dweller(self, value):
        zx.tp_set_is_water_dweller(self, value)

    def set_collision_hit_priority(self, value):
        zx.tp_set_collision_hit_priority(self, value)

    def set_collision_radius(self, value):
        zx.tp_set_collision_radius(self, value)

    def set_ai_delay_after_moving_ms(self, value):
        zx.tp_set_ai_delay_after_moving_ms(self, value)

    def set_is_gfx_bounce_on_move(self, value):
        zx.tp_set_is_gfx_bounce_on_move(self, value)

    def set_is_loggable(self, value):
        zx.tp_set_is_loggable(self, value)

    def set_is_bleeder(self, value):
        zx.tp_set_is_bleeder(self, value)

    def set_is_corpse_on_death(self, value):
        zx.tp_set_is_corpse_on_death(self, value)

    def set_is_meat_eater(self, value):
        zx.tp_set_is_meat_eater(self, value)

    def set_is_made_of_meat(self, value):
        zx.tp_set_is_made_of_meat(self, value)

    def set_is_active(self, value):
        zx.tp_set_is_active(self, value)

    def set_stats_health_starving_pct(self, value):
        zx.tp_set_stats_health_starving_pct(self, value)

    def set_stats_health_initial(self, value):
        zx.tp_set_stats_health_initial(self, value)

    def set_stats_health_hunger_pct(self, value):
        zx.tp_set_stats_health_hunger_pct(self, value)

    def set_stats_attack(self, value):
        zx.tp_set_stats_attack(self, value)

    def set_stats_defence(self, value):
        zx.tp_set_stats_defence(self, value)

    def set_hunger_clock_freq_ms(self, value):
        zx.tp_set_hunger_clock_freq_ms(self, value)

    def set_ai_scent_distance(self, value):
        zx.tp_set_ai_scent_distance(self, value)

    def set_is_ripple(self, value):
        zx.tp_set_is_ripple(self, value)

    def set_is_light_strength(self, value):
        zx.tp_set_is_light_strength(self, value)

    def set_is_blood(self, value):
        zx.tp_set_is_blood(self, value)

    def set_is_gfx_animated_can_vflip(self, value):
        zx.tp_set_is_gfx_animated_can_vflip(self, value)

    def set_is_corridor(self, value):
        zx.tp_set_is_corridor(self, value)

    def set_is_gfx_oversized_but_sitting_on_the_ground(self, value):
        zx.tp_set_is_gfx_oversized_but_sitting_on_the_ground(self, value)

    def set_is_interesting(self, value):
        zx.tp_set_is_interesting(self, value)

    def set_is_exit(self, value):
        zx.tp_set_is_exit(self, value)

    def set_is_door(self, value):
        zx.tp_set_is_door(self, value)

    def set_is_entrance(self, value):
        zx.tp_set_is_entrance(self, value)

    def set_stats_move_speed_ms(self, value):
        zx.tp_set_stats_move_speed_ms(self, value)

    def set_weapon_use_delay_hundredths(self, value):
        zx.tp_set_weapon_use_delay_hundredths(self, value)

    def set_collision_box(self, value):
        zx.tp_set_collision_box(self, value)

    def set_collision_circle(self, value):
        zx.tp_set_collision_circle(self, value)

    def set_weapon_damage(self, value):
        zx.tp_set_weapon_damage(self, value)

    def set_is_projectile(self, value):
        zx.tp_set_is_projectile(self, value)

    def set_is_explosion(self, value):
        zx.tp_set_is_explosion(self, value)

    def set_is_combustible(self, value):
        zx.tp_set_is_combustible(self, value)

    def set_weapon_use_distance(self, value):
        zx.tp_set_weapon_use_distance(self, value)

    def set_is_gfx_weapon_carry_anim(self, value):
        zx.tp_set_is_gfx_weapon_carry_anim(self, value)

    def set_is_gfx_attack_anim(self, value):
        zx.tp_set_is_gfx_attack_anim(self, value)

    def set_is_weapon(self, value):
        zx.tp_set_is_weapon(self, value)

    def set_is_gfx_show_outlined(self, value):
        zx.tp_set_is_gfx_show_outlined(self, value)

    def set_is_gfx_large_shadow(self, value):
        zx.tp_set_is_gfx_large_shadow(self, value)

    def set_z_depth(self, value):
        zx.tp_set_z_depth(self, value)

    def set_is_movable(self, value):
        zx.tp_set_is_movable(self, value)

    def set_is_gfx_animated_can_hflip(self, value):
        zx.tp_set_is_gfx_animated_can_hflip(self, value)

    def set_is_gfx_animated_can_vflip(self, value):
        zx.tp_set_is_gfx_animated_can_vflip(self, value)

    def set_is_movement_blocking(self, value):
        zx.tp_set_is_movement_blocking(self, value)

    def set_is_treasure(self, value):
        zx.tp_set_is_treasure(self, value)

    def set_is_wall(self, value):
        zx.tp_set_is_wall(self, value)

    def set_is_rock(self, value):
        zx.tp_set_is_rock(self, value)

    def set_is_floor(self, value):
        zx.tp_set_is_floor(self, value)

    def set_is_dirt(self, value):
        zx.tp_set_is_dirt(self, value)

    def set_is_lava(self, value):
        zx.tp_set_is_lava(self, value)

    def set_is_chasm(self, value):
        zx.tp_set_is_chasm(self, value)

    def set_is_water(self, value):
        zx.tp_set_is_water(self, value)

    def set_is_deep_water(self, value):
        zx.tp_set_is_deep_water(self, value)

    def set_is_gfx_small_shadow_caster(self, value):
        zx.tp_set_is_gfx_small_shadow_caster(self, value)
