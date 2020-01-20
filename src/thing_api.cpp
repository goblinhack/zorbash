//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_game_status.h"
#include "my_thing.h"
#include <list>

void Thing::new_monst (void)
{
    if (unlikely(!monst)) {
//con("new");
        monst = new Monst();
        // uncomment to see who allocates things
        // err("new monst");
        newptr(monst, "Monst");
    }
}

////////////////////////////////////////////////////////////////////////////
// age_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_age_map (void)
{
    if (monst) {
        return (monst->age_map);
    } else {
        return (0);
    }
}

void Thing::new_age_map (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    if (!monst->age_map) {
        monst->age_map = new AgeMap();
        newptr(monst->age_map, "Dmap age");
    }
}

void Thing::delete_age_map (void)
{_
    if (monst) {
        verify(monst);
        if (monst->age_map) {
            oldptr(monst->age_map);
            delete monst->age_map; monst->age_map = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// dmap_scent
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::get_dmap_scent (void)
{
    if (monst) {
        return (monst->dmap_scent);
    } else {
        return (0);
    }
}

void Thing::new_dmap_scent (void)
{_
    new_monst();
    if (!monst->dmap_scent) {
        monst->dmap_scent = new Dmap();
        newptr(monst->dmap_scent, "AgeMap");
    }
}

void Thing::delete_dmap_scent (void)
{_
    if (monst) {
        verify(monst);
        if (monst->dmap_scent) {
            oldptr(monst->dmap_scent);
            delete monst->dmap_scent; monst->dmap_scent = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// light
////////////////////////////////////////////////////////////////////////////
Lightp Thing::get_light (void)
{
    if (monst) {
        return (monst->light);
    } else {
        return (0);
    }
}

void Thing::new_light (fpoint at,
                       double strength,
                       LightQuality quality,
                       color col)
{_
    new_monst();
    if (!monst->light) {
        monst->light = light_new(this, at, strength, quality, col);
        monst->light_strength = strength;
        monst->light_quality = quality;
        monst->light_col = col;
    }
}

void Thing::delete_light (void)
{_
    if (monst) {
        verify(monst);
        if (monst->light) {
            delete monst->light; monst->light = 0;
        }
    }
}

int Thing::ai_delay_after_moving_ms(void)
{
    return (tp_ai_delay_after_moving_ms(tp()));
}

int Thing::ai_scent_distance(void)
{
    return (tp_ai_scent_distance(tp()));
}

int Thing::collision_attack(void)
{
    return (tp_collision_attack(tp()));
}

int Thing::collision_box(void)
{
    return (tp_collision_box(tp()));
}

int Thing::collision_check(void)
{
    return (tp_collision_check(tp()));
}

int Thing::collision_circle(void)
{
    return (tp_collision_circle(tp()));
}

int Thing::collision_hit_priority(void)
{
    return (tp_collision_hit_priority(tp()));
}

int Thing::is_interesting(void)
{
    return (tp_is_interesting(tp()));
}

int Thing::gfx_animated(void)
{
    return (tp_gfx_animated(tp()));
}

int Thing::gfx_animated_can_vflip(void)
{
    return (tp_gfx_animated_can_vflip(tp()));
}

int Thing::gfx_animated_no_dir(void)
{
    return (tp_gfx_animated_no_dir(tp()));
}

int Thing::gfx_bounce_on_move(void)
{
    return (tp_gfx_bounce_on_move(tp()));
}

int Thing::gfx_animated_can_hflip(void)
{
    return (tp_gfx_animated_can_hflip(tp()));
}

int Thing::gfx_is_an_animation_only(void)
{
    return (tp_gfx_is_an_animation_only(tp()));
}

int Thing::gfx_is_floor_deco(void)
{
    return (tp_gfx_is_floor_deco(tp()));
}

int Thing::gfx_is_wall_deco(void)
{
    return (tp_gfx_is_wall_deco(tp()));
}

int Thing::gfx_is_weapon_carry_anim(void)
{
    return (tp_gfx_is_weapon_carry_anim(tp()));
}

int Thing::gfx_is_attack_anim(void)
{
    return (tp_gfx_is_attack_anim(tp()));
}

int Thing::gfx_large_shadow_caster(void)
{
    return (tp_gfx_large_shadow_caster(tp()));
}

int Thing::gfx_show_outlined(void)
{
    return (tp_gfx_show_outlined(tp()));
}

int Thing::gfx_oversized_but_sitting_on_the_ground(void)
{
    return (tp_gfx_oversized_but_sitting_on_the_ground(tp()));
}

int Thing::gfx_small_shadow_caster(void)
{
    return (tp_gfx_small_shadow_caster(tp()));
}

int Thing::health_hunger_pct(void)
{
    return (tp_stats_health_hunger_pct(tp()));
}

int Thing::hunger_clock_freq_ms(void)
{
    return (tp_hunger_clock_freq_ms(tp()));
}

int Thing::is_hunger_insatiable(void)
{
    return (tp_is_hunger_insatiable(tp()));
}

int Thing::health_initial(void)
{
    return (tp_stats_health_initial(tp()));
}

int Thing::health_starving_pct(void)
{
    return (tp_stats_health_starving_pct(tp()));
}

int Thing::is_active(void)
{
    return (tp_is_active(tp()));
}

int Thing::is_attackable(void)
{
    return (tp_is_attackable(tp()));
}

int Thing::is_bleeder(void)
{
    return (tp_is_bleeder(tp()));
}

int Thing::is_blood(void)
{
    return (tp_is_blood(tp()));
}

int Thing::is_combustable(void)
{
    return (tp_is_combustable(tp()));
}

int Thing::is_corpse_on_death(void)
{
    return (tp_is_corpse_on_death(tp()));
}

int Thing::is_corridor(void)
{
    return (tp_is_corridor(tp()));
}

int Thing::is_deep_water(void)
{
    return (tp_is_deep_water(tp()));
}

int Thing::is_dirt(void)
{
    return (tp_is_dirt(tp()));
}

int Thing::is_door(void)
{
    return (tp_is_door(tp()));
}

int Thing::is_entrance(void)
{
    return (tp_is_entrance(tp()));
}

int Thing::is_exit(void)
{
    return (tp_is_exit(tp()));
}

int Thing::is_explosion(void)
{
    return (tp_is_explosion(tp()));
}

int Thing::is_floor(void)
{
    return (tp_is_floor(tp()));
}

int Thing::is_food(void)
{
    return (tp_is_food(tp()));
}

int Thing::is_key(void)
{
    return (tp_is_key(tp()));
}

int Thing::is_lava(void)
{
    return (tp_is_lava(tp()));
}

int Thing::is_light_strength(void)
{
    return (tp_is_light_strength(tp()));
}

int Thing::is_made_of_meat(void)
{
    return (tp_is_made_of_meat(tp()));
}

int Thing::is_meat_eater(void)
{
    return (tp_is_meat_eater(tp()));
}

int Thing::is_monst(void)
{
    return (tp_is_monst(tp()));
}

int Thing::is_alive_monst(void)
{
    return (tp_is_monst(tp()) && !is_dead);
}

int Thing::is_movable(void)
{
    return (tp_is_movable(tp()));
}

int Thing::is_movement_blocking(void)
{
    return (tp_is_movement_blocking(tp()));
}

int Thing::is_obstacle(void)
{
    return (tp_is_obstacle(tp()));
}

int Thing::is_player(void)
{
    return (tp_is_player(tp()));
}

int Thing::is_projectile(void)
{
    return (tp_is_projectile(tp()));
}

int Thing::is_ripple(void)
{
    return (tp_is_ripple(tp()));
}

int Thing::is_rock(void)
{
    return (tp_is_rock(tp()));
}

int Thing::is_rrr1(void)
{
    return (tp_is_rrr1(tp()));
}

int Thing::is_rrr10(void)
{
    return (tp_is_rrr10(tp()));
}

int Thing::is_rrr11(void)
{
    return (tp_is_rrr11(tp()));
}

int Thing::is_rrr12(void)
{
    return (tp_is_rrr12(tp()));
}

int Thing::is_rrr13(void)
{
    return (tp_is_rrr13(tp()));
}

int Thing::is_rrr14(void)
{
    return (tp_is_rrr14(tp()));
}

int Thing::is_rrr15(void)
{
    return (tp_is_rrr15(tp()));
}

int Thing::is_rrr16(void)
{
    return (tp_is_rrr16(tp()));
}

int Thing::is_rrr17(void)
{
    return (tp_is_rrr17(tp()));
}

int Thing::is_rrr18(void)
{
    return (tp_is_rrr18(tp()));
}

int Thing::is_rrr19(void)
{
    return (tp_is_rrr19(tp()));
}

int Thing::is_rrr2(void)
{
    return (tp_is_rrr2(tp()));
}

int Thing::is_rrr20(void)
{
    return (tp_is_rrr20(tp()));
}

int Thing::is_rrr21(void)
{
    return (tp_is_rrr21(tp()));
}

int Thing::is_rrr22(void)
{
    return (tp_is_rrr22(tp()));
}

int Thing::is_rrr23(void)
{
    return (tp_is_rrr23(tp()));
}

int Thing::is_rrr24(void)
{
    return (tp_is_rrr24(tp()));
}

int Thing::is_rrr25(void)
{
    return (tp_is_rrr25(tp()));
}

int Thing::is_rrr26(void)
{
    return (tp_is_rrr26(tp()));
}

int Thing::is_loggable(void)
{
    return (tp_is_loggable(tp()));
}

int Thing::is_rrr28(void)
{
    return (tp_is_rrr28(tp()));
}

int Thing::is_rrr29(void)
{
    return (tp_is_rrr29(tp()));
}

int Thing::is_rrr3(void)
{
    return (tp_is_rrr3(tp()));
}

int Thing::is_rrr30(void)
{
    return (tp_is_rrr30(tp()));
}

int Thing::is_rrr31(void)
{
    return (tp_is_rrr31(tp()));
}

int Thing::is_rrr32(void)
{
    return (tp_is_rrr32(tp()));
}

int Thing::is_rrr33(void)
{
    return (tp_is_rrr33(tp()));
}

int Thing::is_rrr34(void)
{
    return (tp_is_rrr34(tp()));
}

int Thing::is_rrr35(void)
{
    return (tp_is_rrr35(tp()));
}

int Thing::is_rrr36(void)
{
    return (tp_is_rrr36(tp()));
}

int Thing::is_rrr37(void)
{
    return (tp_is_rrr37(tp()));
}

int Thing::is_rrr38(void)
{
    return (tp_is_rrr38(tp()));
}

int Thing::is_rrr39(void)
{
    return (tp_is_rrr39(tp()));
}

int Thing::is_rrr4(void)
{
    return (tp_is_rrr4(tp()));
}

int Thing::is_blood_splatter(void)
{
    return (tp_is_blood_splatter(tp()));
}

int Thing::is_no_tile(void)
{
    return (tp_is_no_tile(tp()));
}

int Thing::is_msg(void)
{
    return (tp_is_msg(tp()));
}

int Thing::is_attack_lunge(void)
{
    return (tp_is_attack_lunge(tp()));
}

int Thing::defence(void)
{
    return (tp_stats_defence(tp()));
}

int Thing::attack(void)
{
    return (tp_stats_attack(tp()));
}

int Thing::is_secret_door(void)
{
    return (tp_is_secret_door(tp()));
}

int Thing::is_cursor_can_hover_over(void)
{
    return (tp_is_cursor_can_hover_over(tp()));
}

int Thing::is_cursor(void)
{
    return (tp_is_cursor(tp()));
}

int Thing::is_rrr5(void)
{
    return (tp_is_rrr5(tp()));
}

int Thing::gfx_dead_anim(void)
{
    return (tp_gfx_dead_anim(tp()));
}

int Thing::is_rrr6(void)
{
    return (tp_is_rrr6(tp()));
}

int Thing::is_rrr7(void)
{
    return (tp_is_rrr7(tp()));
}

int Thing::is_rrr8(void)
{
    return (tp_is_rrr8(tp()));
}

int Thing::is_rrr9(void)
{
    return (tp_is_rrr9(tp()));
}

int Thing::is_undead(void)
{
    return (tp_is_undead(tp()));
}

int Thing::is_wall(void)
{
    return (tp_is_wall(tp()));
}

int Thing::is_water(void)
{
    return (tp_is_water(tp()));
}

int Thing::is_water_dweller(void)
{
    return (tp_is_water_dweller(tp()));
}

int Thing::is_water_hater(void)
{
    return (tp_is_water_hater(tp()));
}

int Thing::is_weapon(void)
{
    return (tp_is_weapon(tp()));
}

int Thing::weapon_damage(void)
{
    return (tp_weapon_damage(tp()));
}

int Thing::weapon_use_delay_hundredths(void)
{
    return (tp_weapon_use_delay_hundredths(tp()));
}

int Thing::weapon_use_distance(void)
{
    return (tp_weapon_use_distance(tp()));
}

int Thing::z_depth(void)
{
    return (tp_z_depth(tp()));
}

std::string Thing::stats_attack_hd(void)
{
    return (tp_stats_attack_hd(tp()));
}

std::string Thing::is_nutrition_hd(void)
{
    return (tp_is_nutrition_hd(tp()));
}

int Thing::is_nutrition(void)
{
    return (tp()->is_nutrition());
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_lunge_to (void)
{
    if (monst) {
        return (monst->lunge_to);
    } else {
        return (fpoint(0, 0));
    }
}

void Thing::set_lunge_to (fpoint v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->lunge_to = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_height (void)
{
    if (monst) {
        return (monst->bounce_height);
    } else {
        return (0);
    }
}

void Thing::set_bounce_height (float v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->bounce_height = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_fade (void)
{
    if (monst) {
        return (monst->bounce_fade);
    } else {
        return (0);
    }
}

void Thing::set_bounce_fade (float v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->bounce_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_bounce_count (void)
{
    if (monst) {
        return (monst->bounce_count);
    } else {
        return (0);
    }
}

void Thing::set_bounce_count (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->bounce_count = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_height (void)
{
    if (monst) {
        return (monst->fadeup_height);
    } else {
        return (0);
    }
}

void Thing::set_fadeup_height (float v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->fadeup_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_fade (void)
{
    if (monst) {
        return (monst->fadeup_fade);
    } else {
        return (0);
    }
}

void Thing::set_fadeup_fade (float v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->fadeup_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// rot
////////////////////////////////////////////////////////////////////////////
float Thing::get_rot (void)
{
    if (monst) {
        return (monst->rot);
    } else {
        return (0);
    }
}

void Thing::set_rot (float v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->rot = v;
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
std::string Thing::get_msg (void)
{
    if (monst) {
        return (monst->msg);
    } else {
        return ("");
    }
}

void Thing::set_msg (std::string v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
float Thing::get_submerged_offset (void)
{
    if (monst) {
        return (monst->submerged_offset);
    } else {
        return (0);
    }
}

void Thing::set_submerged_offset (float v)
{
    new_monst();
//con("%s", __FUNCTION__);
    monst->submerged_offset = v;
}

////////////////////////////////////////////////////////////////////////////
// gold
////////////////////////////////////////////////////////////////////////////
int Thing::get_gold (void)
{
    if (monst) {
        return (monst->gold);
    } else {
        return (0);
    }
}

int Thing::set_gold (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->gold = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_gold (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->gold -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_gold (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->gold += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_gold (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->gold--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_gold (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->gold++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// tick
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick (void)
{
    if (monst) {
        return (monst->tick);
    } else {
        return (0);
    }
}

uint32_t Thing::set_tick (uint32_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->tick = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

uint32_t Thing::decr_tick (uint32_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->tick -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

uint32_t Thing::incr_tick (uint32_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->tick += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

uint32_t Thing::decr_tick (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->tick--);
    if (is_player()) { game_status_init(); }
    return (n);
}

uint32_t Thing::incr_tick (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->tick++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_health (void)
{
    if (monst) {
        return (monst->stats_health);
    } else {
        return (0);
    }
}

int Thing::set_stats_health (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_health (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_health (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_health (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_health (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_health_max (void)
{
    if (monst) {
        return (monst->stats_health_max);
    } else {
        return (0);
    }
}

int Thing::set_stats_health_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health_max = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_health_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health_max -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_health_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health_max += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_health_max (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health_max--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_health_max (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_health_max++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// defence
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_defence (void)
{
    if (monst) {
        return (monst->stats_defence);
    } else {
        return (0);
    }
}

int Thing::set_stats_defence (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_defence (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_defence (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_defence (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_defence (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// defence_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_defence_max (void)
{
    if (monst) {
        return (monst->stats_defence_max);
    } else {
        return (0);
    }
}

int Thing::set_stats_defence_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence_max = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_defence_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence_max -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_defence_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence_max += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_defence_max (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence_max--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_defence_max (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_defence_max++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attack (void)
{
    if (monst) {
        if (monst->stats_attack) {
            return (monst->stats_attack);
        }
        return (tp()->attack_damage.roll());
    } else {
        return (0);
    }
}

int Thing::set_stats_attack (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attack (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attack (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attack (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attack (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attack_max (void)
{
    if (monst) {
        return (monst->stats_attack_max);
    } else {
        return (0);
    }
}

int Thing::set_stats_attack_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_max = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attack_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_max -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attack_max (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_max += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attack_max (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_max--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attack_max (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_max++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack_rate_tenths
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attack_rate_tenths (void)
{
    if (monst) {
        return (monst->stats_attack_rate_tenths);
    } else {
        return (0);
    }
}

int Thing::set_stats_attack_rate_tenths (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_rate_tenths = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attack_rate_tenths (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_rate_tenths -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attack_rate_tenths (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_rate_tenths += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attack_rate_tenths (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_rate_tenths--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attack_rate_tenths (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attack_rate_tenths++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attacked_rate_tenths
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attacked_rate_tenths (void)
{
    if (monst) {
        return (monst->stats_attacked_rate_tenths);
    } else {
        return (0);
    }
}

int Thing::set_stats_attacked_rate_tenths (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attacked_rate_tenths = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attacked_rate_tenths (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attacked_rate_tenths -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attacked_rate_tenths (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attacked_rate_tenths += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats_attacked_rate_tenths (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attacked_rate_tenths--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats_attacked_rate_tenths (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats_attacked_rate_tenths++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats01
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats01 (void)
{
    if (monst) {
        return (monst->stats01);
    } else {
        return (0);
    }
}

int Thing::set_stats01 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats01 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats01 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats01 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats01 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats01 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats01 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats01--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats01 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats01++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats02
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats02 (void)
{
    if (monst) {
        return (monst->stats02);
    } else {
        return (0);
    }
}

int Thing::set_stats02 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats02 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats02 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats02 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats02 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats02 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats02 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats02--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats02 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats02++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats03
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats03 (void)
{
    if (monst) {
        return (monst->stats03);
    } else {
        return (0);
    }
}

int Thing::set_stats03 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats03 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats03 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats03 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats03 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats03 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats03 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats03--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats03 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats03++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats04
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats04 (void)
{
    if (monst) {
        return (monst->stats04);
    } else {
        return (0);
    }
}

int Thing::set_stats04 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats04 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats04 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats04 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats04 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats04 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats04 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats04--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats04 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats04++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats05
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats05 (void)
{
    if (monst) {
        return (monst->stats05);
    } else {
        return (0);
    }
}

int Thing::set_stats05 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats05 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats05 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats05 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats05 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats05 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats05 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats05--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats05 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats05++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats06
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats06 (void)
{
    if (monst) {
        return (monst->stats06);
    } else {
        return (0);
    }
}

int Thing::set_stats06 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats06 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats06 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats06 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats06 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats06 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats06 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats06--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats06 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats06++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats07
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats07 (void)
{
    if (monst) {
        return (monst->stats07);
    } else {
        return (0);
    }
}

int Thing::set_stats07 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats07 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats07 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats07 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats07 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats07 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats07 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats07--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats07 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats07++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats08
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats08 (void)
{
    if (monst) {
        return (monst->stats08);
    } else {
        return (0);
    }
}

int Thing::set_stats08 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats08 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats08 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats08 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats08 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats08 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats08 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats08--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats08 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats08++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats09
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats09 (void)
{
    if (monst) {
        return (monst->stats09);
    } else {
        return (0);
    }
}

int Thing::set_stats09 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats09 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats09 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats09 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats09 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats09 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats09 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats09--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats09 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats09++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats10
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats10 (void)
{
    if (monst) {
        return (monst->stats10);
    } else {
        return (0);
    }
}

int Thing::set_stats10 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats10 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats10 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats10 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats10 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats10 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats10 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats10--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats10 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats10++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats11
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats11 (void)
{
    if (monst) {
        return (monst->stats11);
    } else {
        return (0);
    }
}

int Thing::set_stats11 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats11 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats11 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats11 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats11 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats11 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats11 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats11--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats11 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats11++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats12
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats12 (void)
{
    if (monst) {
        return (monst->stats12);
    } else {
        return (0);
    }
}

int Thing::set_stats12 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats12 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats12 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats12 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats12 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats12 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats12 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats12--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats12 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats12++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats13
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats13 (void)
{
    if (monst) {
        return (monst->stats13);
    } else {
        return (0);
    }
}

int Thing::set_stats13 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats13 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats13 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats13 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats13 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats13 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats13 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats13--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats13 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats13++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats14
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats14 (void)
{
    if (monst) {
        return (monst->stats14);
    } else {
        return (0);
    }
}

int Thing::set_stats14 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats14 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats14 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats14 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats14 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats14 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats14 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats14--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats14 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats14++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats15
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats15 (void)
{
    if (monst) {
        return (monst->stats15);
    } else {
        return (0);
    }
}

int Thing::set_stats15 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats15 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats15 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats15 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats15 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats15 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats15 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats15--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats15 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats15++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats16
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats16 (void)
{
    if (monst) {
        return (monst->stats16);
    } else {
        return (0);
    }
}

int Thing::set_stats16 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats16 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats16 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats16 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats16 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats16 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats16 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats16--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats16 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats16++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats17
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats17 (void)
{
    if (monst) {
        return (monst->stats17);
    } else {
        return (0);
    }
}

int Thing::set_stats17 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats17 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats17 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats17 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats17 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats17 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats17 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats17--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats17 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats17++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats18
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats18 (void)
{
    if (monst) {
        return (monst->stats18);
    } else {
        return (0);
    }
}

int Thing::set_stats18 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats18 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats18 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats18 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats18 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats18 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats18 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats18--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats18 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats18++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats19
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats19 (void)
{
    if (monst) {
        return (monst->stats19);
    } else {
        return (0);
    }
}

int Thing::set_stats19 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats19 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats19 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats19 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats19 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats19 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats19 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats19--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats19 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats19++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats20
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats20 (void)
{
    if (monst) {
        return (monst->stats20);
    } else {
        return (0);
    }
}

int Thing::set_stats20 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats20 = v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats20 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats20 -= v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats20 (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats20 += v);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::decr_stats20 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats20--);
    if (is_player()) { game_status_init(); }
    return (n);
}

int Thing::incr_stats20 (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monst->stats20++);
    if (is_player()) { game_status_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// owned_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_owned_count (void)
{
    if (monst) {
        return (monst->owned_count);
    } else {
        return (0);
    }
}

int Thing::set_owned_count (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->owned_count = v);
}

int Thing::decr_owned_count (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->owned_count -= v);
}

int Thing::incr_owned_count (int v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->owned_count += v);
}

int Thing::decr_owned_count (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->owned_count--);
}

int Thing::incr_owned_count (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->owned_count++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_lunge_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_lunge_begin (void)
{
    if (monst) {
        return (monst->timestamp_lunge_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_lunge_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_begin = v);
}

timestamp_t Thing::decr_timestamp_lunge_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_begin -= v);
}

timestamp_t Thing::incr_timestamp_lunge_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_begin += v);
}

timestamp_t Thing::decr_timestamp_lunge_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_begin--);
}

timestamp_t Thing::incr_timestamp_lunge_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_lunge_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_lunge_end (void)
{
    if (monst) {
        return (monst->timestamp_lunge_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_lunge_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_end = v);
}

timestamp_t Thing::decr_timestamp_lunge_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_end -= v);
}

timestamp_t Thing::incr_timestamp_lunge_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_end += v);
}

timestamp_t Thing::decr_timestamp_lunge_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_end--);
}

timestamp_t Thing::incr_timestamp_lunge_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_lunge_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_bounce_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_bounce_begin (void)
{
    if (monst) {
        return (monst->timestamp_bounce_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_bounce_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_begin = v);
}

timestamp_t Thing::decr_timestamp_bounce_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_begin -= v);
}

timestamp_t Thing::incr_timestamp_bounce_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_begin += v);
}

timestamp_t Thing::decr_timestamp_bounce_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_begin--);
}

timestamp_t Thing::incr_timestamp_bounce_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_bounce_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_bounce_end (void)
{
    if (monst) {
        return (monst->timestamp_bounce_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_bounce_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_end = v);
}

timestamp_t Thing::decr_timestamp_bounce_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_end -= v);
}

timestamp_t Thing::incr_timestamp_bounce_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_end += v);
}

timestamp_t Thing::decr_timestamp_bounce_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_end--);
}

timestamp_t Thing::incr_timestamp_bounce_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_fadeup_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_fadeup_begin (void)
{
    if (monst) {
        return (monst->timestamp_fadeup_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_fadeup_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_begin = v);
}

timestamp_t Thing::decr_timestamp_fadeup_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_begin -= v);
}

timestamp_t Thing::incr_timestamp_fadeup_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_begin += v);
}

timestamp_t Thing::decr_timestamp_fadeup_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_begin--);
}

timestamp_t Thing::incr_timestamp_fadeup_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_fadeup_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_fadeup_end (void)
{
    if (monst) {
        return (monst->timestamp_fadeup_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_fadeup_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_end = v);
}

timestamp_t Thing::decr_timestamp_fadeup_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_end -= v);
}

timestamp_t Thing::incr_timestamp_fadeup_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_end += v);
}

timestamp_t Thing::decr_timestamp_fadeup_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_end--);
}

timestamp_t Thing::incr_timestamp_fadeup_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_fadeup_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_last_attacked
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_last_attacked (void)
{
    if (monst) {
        return (monst->timestamp_last_attacked);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_last_attacked (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attacked = v);
}

timestamp_t Thing::decr_timestamp_last_attacked (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attacked -= v);
}

timestamp_t Thing::incr_timestamp_last_attacked (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attacked += v);
}

timestamp_t Thing::decr_timestamp_last_attacked (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attacked--);
}

timestamp_t Thing::incr_timestamp_last_attacked (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_last_attack
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_last_attack (void)
{
    if (monst) {
        return (monst->timestamp_last_attack);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_last_attack (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attack = v);
}

timestamp_t Thing::decr_timestamp_last_attack (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attack -= v);
}

timestamp_t Thing::incr_timestamp_last_attack (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attack += v);
}

timestamp_t Thing::decr_timestamp_last_attack (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attack--);
}

timestamp_t Thing::incr_timestamp_last_attack (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_last_attack++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_flip_start
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_flip_start (void)
{
    if (monst) {
        return (monst->timestamp_flip_start);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_flip_start (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_flip_start = v);
}

timestamp_t Thing::decr_timestamp_flip_start (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_flip_start -= v);
}

timestamp_t Thing::incr_timestamp_flip_start (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_flip_start += v);
}

timestamp_t Thing::decr_timestamp_flip_start (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_flip_start--);
}

timestamp_t Thing::incr_timestamp_flip_start (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_flip_start++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_move_start
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_move_begin (void)
{
    if (monst) {
        return (monst->timestamp_move_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_move_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_begin = v);
}

timestamp_t Thing::decr_timestamp_move_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_begin -= v);
}

timestamp_t Thing::incr_timestamp_move_begin (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_begin += v);
}

timestamp_t Thing::decr_timestamp_move_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_begin--);
}

timestamp_t Thing::incr_timestamp_move_begin (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_move_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_move_end (void)
{
    if (monst) {
        return (monst->timestamp_move_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_move_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_end = v);
}

timestamp_t Thing::decr_timestamp_move_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_end -= v);
}

timestamp_t Thing::incr_timestamp_move_end (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_end += v);
}

timestamp_t Thing::decr_timestamp_move_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_end--);
}

timestamp_t Thing::incr_timestamp_move_end (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_move_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_born
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_born (void)
{
    if (monst) {
        return (monst->timestamp_born);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_born (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_born = v);
}

timestamp_t Thing::decr_timestamp_born (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_born -= v);
}

timestamp_t Thing::incr_timestamp_born (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_born += v);
}

timestamp_t Thing::decr_timestamp_born (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_born--);
}

timestamp_t Thing::incr_timestamp_born (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_born++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_hunger_tick
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_hunger_tick (void)
{
    if (monst) {
        return (monst->timestamp_hunger_tick);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_hunger_tick (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_hunger_tick = v);
}

timestamp_t Thing::decr_timestamp_hunger_tick (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_hunger_tick -= v);
}

timestamp_t Thing::incr_timestamp_hunger_tick (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_hunger_tick += v);
}

timestamp_t Thing::decr_timestamp_hunger_tick (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_hunger_tick--);
}

timestamp_t Thing::incr_timestamp_hunger_tick (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_hunger_tick++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_ai_next
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_ai_next (void)
{
    if (monst) {
        return (monst->timestamp_ai_next);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_ai_next (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_ai_next = v);
}

timestamp_t Thing::decr_timestamp_ai_next (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_ai_next -= v);
}

timestamp_t Thing::incr_timestamp_ai_next (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_ai_next += v);
}

timestamp_t Thing::decr_timestamp_ai_next (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_ai_next--);
}

timestamp_t Thing::incr_timestamp_ai_next (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_ai_next++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_collision
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_collision (void)
{
    if (monst) {
        return (monst->timestamp_collision);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_collision (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_collision = v);
}

timestamp_t Thing::decr_timestamp_collision (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_collision -= v);
}

timestamp_t Thing::incr_timestamp_collision (timestamp_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_collision += v);
}

timestamp_t Thing::decr_timestamp_collision (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_collision--);
}

timestamp_t Thing::incr_timestamp_collision (void)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->timestamp_collision++);
}

////////////////////////////////////////////////////////////////////////////
// owner_id
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_owner_id (void)
{
    if (monst) {
        return (monst->owner_id);
    } else {
        return (0);
    }
}

uint32_t Thing::set_owner_id (uint32_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->owner_id = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_carry_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_weapon_id_carry_anim (void)
{
    if (monst) {
        return (monst->weapon_id_carry_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_weapon_id_carry_anim (uint32_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->weapon_id_carry_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_use_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_weapon_id_use_anim (void)
{
    if (monst) {
        return (monst->weapon_id_use_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_weapon_id_use_anim (uint32_t v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->weapon_id_use_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_tp_id
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_weapon_id (void)
{
    if (monst) {
        // con("get weapon ID-%08X", monst->weapon_id);
        return (monst->weapon_id);
    } else {
        // con("get weapon id => none");
        return (0);
    }
}

uint32_t Thing::set_weapon_id (uint32_t v)
{
    new_monst();
    // con("set weapon ID-%08X", v);
    return (monst->weapon_id = v);
}

////////////////////////////////////////////////////////////////////////////
// interpolated_mid_at
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_interpolated_mid_at (void)
{
    if (monst) {
        if (monst->interpolated_mid_at == fpoint(0, 0)) {
            return (mid_at);
        } else {
            return (monst->interpolated_mid_at);
        }
    } else {
        return (mid_at);
    }
}

fpoint Thing::set_interpolated_mid_at (fpoint v)
{
    new_monst();
//con("%s", __FUNCTION__);
    return (monst->interpolated_mid_at = v);
}
