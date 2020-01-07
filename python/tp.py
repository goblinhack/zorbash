import zx
import random


class Tp:
    """thing template"""

    def __init__(self, name):
        self.name = name

        #
        # Load it into the game engine
        #
        zx.tp_load(self)

    def update(self):
        zx.tp_update(self)

    def set_tile(self, tile=None, **kw):
        zx.tp_set_tile(self, tile, **kw)

    def set_tile_left(self, tile_left=None, **kw):
        zx.tp_set_tile_left(self, tile_left, **kw)

    def set_tile_right(self, tile_right=None, **kw):
        zx.tp_set_tile_right(self, tile_right, **kw)

    def set_tile_bot(self, tile_bot=None, **kw):
        zx.tp_set_tile_bot(self, tile_bot, **kw)

    def set_tile_top(self, tile_top=None, **kw):
        zx.tp_set_tile_top(self, tile_top, **kw)

    def set_tile_tl(self, tile_tl=None, **kw):
        zx.tp_set_tile_tl(self, tile_tl, **kw)

    def set_tile_tr(self, tile_tr=None, **kw):
        zx.tp_set_tile_tr(self, tile_tr, **kw)

    def set_tile_br(self, tile_br=None, **kw):
        zx.tp_set_tile_br(self, tile_br, **kw)

    def set_tile_bl(self, tile_bl=None, **kw):
        zx.tp_set_tile_bl(self, tile_bl, **kw)


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

    def set_gfx_animated(self, value):
        zx.tp_set_gfx_animated(self, value)

    def set_gfx_animated_no_dir(self, value):
        zx.tp_set_gfx_animated_no_dir(self, value)

    def set_gfx_is_an_animation_only(self, value):
        zx.tp_set_gfx_is_an_animation_only(self, value)

    def set_is_monst(self, value):
        zx.tp_set_is_monst(self, value)

    def set_is_key(self, value):
        zx.tp_set_is_key(self, value)

    def set_gfx_is_floor_deco(self, value):
        zx.tp_set_gfx_is_floor_deco(self, value)

    def set_gfx_is_wall_deco(self, value):
        zx.tp_set_gfx_is_wall_deco(self, value)

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

    def set_str_zzz16(self, value):
        zx.tp_set_str_zzz16(self, value)

    def set_str_zzz17(self, value):
        zx.tp_set_str_zzz17(self, value)

    def set_str_light_color(self, value):
        zx.tp_set_str_light_color(self, value)

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

    def set_is_rrr28(self, value):
        zx.tp_set_is_rrr28(self, value)

    def set_is_rrr29(self, value):
        zx.tp_set_is_rrr29(self, value)

    def set_is_rrr30(self, value):
        zx.tp_set_is_rrr30(self, value)

    def set_is_rrr31(self, value):
        zx.tp_set_is_rrr31(self, value)

    def set_is_rrr32(self, value):
        zx.tp_set_is_rrr32(self, value)

    def set_is_rrr33(self, value):
        zx.tp_set_is_rrr33(self, value)

    def set_is_rrr34(self, value):
        zx.tp_set_is_rrr34(self, value)

    def set_is_rrr35(self, value):
        zx.tp_set_is_rrr35(self, value)

    def set_is_rrr36(self, value):
        zx.tp_set_is_rrr36(self, value)

    def set_is_rrr37(self, value):
        zx.tp_set_is_rrr37(self, value)

    def set_is_rrr38(self, value):
        zx.tp_set_is_rrr38(self, value)

    def set_is_rrr39(self, value):
        zx.tp_set_is_rrr39(self, value)

    def set_is_rrr41(self, value):
        zx.tp_set_is_rrr41(self, value)

    def set_is_rrr42(self, value):
        zx.tp_set_is_rrr42(self, value)

    def set_is_rrr43(self, value):
        zx.tp_set_is_rrr43(self, value)

    def set_is_attack_lunge(self, value):
        zx.tp_set_is_attack_lunge(self, value)

    def set_stats_defence(self, value):
        zx.tp_set_stats_defence(self, value)

    def set_stats_attack(self, value):
        zx.tp_set_stats_attack(self, value)

    def set_stats_attack_rate_tenths(self, value):
        zx.tp_set_stats_attack_rate_tenths(self, value)

    def set_stats_attacked_rate_tenths(self, value):
        zx.tp_set_stats_attacked_rate_tenths(self, value)

    def set_is_secret_door(self, value):
        zx.tp_set_is_secret_door(self, value)

    def set_is_cursor_hover(self, value):
        zx.tp_set_is_cursor_hover(self, value)

    def set_is_cursor(self, value):
        zx.tp_set_is_cursor(self, value)

    def set_gfx_dead_anim(self, value):
        zx.tp_set_gfx_dead_anim(self, value)

    def set_is_obstacle(self, value):
        zx.tp_set_is_obstacle(self, value)

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

    def set_gfx_bounce_on_move(self, value):
        zx.tp_set_gfx_bounce_on_move(self, value)

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

    def set_gfx_animated_can_vflip(self, value):
        zx.tp_set_gfx_animated_can_vflip(self, value)

    def set_is_corridor(self, value):
        zx.tp_set_is_corridor(self, value)

    def set_gfx_oversized_but_sitting_on_the_ground(self, value):
        zx.tp_set_gfx_oversized_but_sitting_on_the_ground(self, value)

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

    def set_is_combustable(self, value):
        zx.tp_set_is_combustable(self, value)

    def set_weapon_use_distance(self, value):
        zx.tp_set_weapon_use_distance(self, value)

    def set_gfx_is_weapon_carry_anim(self, value):
        zx.tp_set_gfx_is_weapon_carry_anim(self, value)

    def set_gfx_is_weapon_use_anim(self, value):
        zx.tp_set_gfx_is_weapon_use_anim(self, value)

    def set_is_weapon(self, value):
        zx.tp_set_is_weapon(self, value)

    def set_gfx_show_hiddend(self, value):
        zx.tp_set_gfx_show_hiddend(self, value)

    def set_gfx_large_shadow_caster(self, value):
        zx.tp_set_gfx_large_shadow_caster(self, value)

    def set_z_depth(self, value):
        zx.tp_set_z_depth(self, value)

    def set_is_movable(self, value):
        zx.tp_set_is_movable(self, value)

    def set_gfx_can_hflip(self, value):
        zx.tp_set_gfx_can_hflip(self, value)

    def set_gfx_animated_can_vflip(self, value):
        zx.tp_set_gfx_animated_can_vflip(self, value)

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

    def set_is_water(self, value):
        zx.tp_set_is_water(self, value)

    def set_is_deep_water(self, value):
        zx.tp_set_is_deep_water(self, value)

    def set_gfx_small_shadow_caster(self, value):
        zx.tp_set_gfx_small_shadow_caster(self, value)
