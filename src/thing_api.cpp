//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_game_status.h"
#include "my_thing.h"

void Thing::new_monst (void)
{_
    if (unlikely(!monstp)) {
//con("new");
        monstp = new Monst();
        // uncomment to see who allocates things
        // err("new monst");
        newptr(monstp, "Monst");
    }
}

////////////////////////////////////////////////////////////////////////////
// age_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::get_age_map (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->age_map);
    } else {
        return (0);
    }
}

void Thing::new_age_map (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    if (!monstp->age_map) {
        monstp->age_map = new AgeMap();
        newptr(monstp->age_map, "Dmap age");
    }
}

void Thing::delete_age_map (void)
{_
    if (monstp) {
        verify(monstp);
        if (monstp->age_map) {
            oldptr(monstp->age_map);
            delete monstp->age_map; monstp->age_map = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// dmap_scent
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::get_dmap_scent (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->dmap_scent);
    } else {
        return (0);
    }
}

void Thing::new_dmap_scent (void)
{_
    new_monst();
    if (!monstp->dmap_scent) {
        monstp->dmap_scent = new Dmap();
        newptr(monstp->dmap_scent, "AgeMap");
    }
}

void Thing::delete_dmap_scent (void)
{_
    if (monstp) {
        verify(monstp);
        if (monstp->dmap_scent) {
            oldptr(monstp->dmap_scent);
            delete monstp->dmap_scent; monstp->dmap_scent = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////
// light
////////////////////////////////////////////////////////////////////////////
std::vector<Lightp> &Thing::get_light (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->light);
    } else {
        static std::vector<Lightp> no_light;
        return no_light;
    }
}

std::size_t Thing::get_light_count (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->light.size());
    } else {
        return (0);
    }
}

void Thing::new_light (fpoint at, fpoint offset, double strength, color col)
{_
    new_monst();
    auto l = light_new(this, at, offset, strength, col);
    monstp->light.push_back(l);
    monstp->light_strength = strength;
    monstp->light_col = col;
}

void Thing::new_light (fpoint at, double strength, color col)
{_
    new_light(at, fpoint(0, 0), strength, col);
}

void Thing::delete_light (void)
{_
    if (monstp) {
        verify(monstp);
        for (auto l : monstp->light) {
            delete l;
        }
    }
}

int Thing::ai_delay_after_moving_ms(void)
{_
    return (tp_ai_delay_after_moving_ms(tp()));
}

int Thing::ai_scent_distance(void)
{_
    return (tp_ai_scent_distance(tp()));
}

int Thing::collision_attack(void)
{_
    return (tp_collision_attack(tp()));
}

int Thing::collision_box(void)
{_
    return (tp_collision_box(tp()));
}

int Thing::collision_check(void)
{_
    return (tp_collision_check(tp()));
}

int Thing::collision_circle(void)
{_
    return (tp_collision_circle(tp()));
}

int Thing::collision_hit_priority(void)
{_
    return (tp_collision_hit_priority(tp()));
}

int Thing::is_interesting(void)
{_
    return (tp_is_interesting(tp()));
}

int Thing::gfx_animated(void)
{_
    return (tp_gfx_animated(tp()));
}

int Thing::gfx_animated_can_vflip(void)
{_
    return (tp_gfx_animated_can_vflip(tp()));
}

int Thing::gfx_animated_no_dir(void)
{_
    return (tp_gfx_animated_no_dir(tp()));
}

int Thing::gfx_bounce_on_move(void)
{_
    return (tp_gfx_bounce_on_move(tp()));
}

int Thing::gfx_animated_can_hflip(void)
{_
    return (tp_gfx_animated_can_hflip(tp()));
}

int Thing::gfx_is_an_animation_only(void)
{_
    return (tp_gfx_is_an_animation_only(tp()));
}

int Thing::is_floor_deco(void)
{_
    return (tp_is_floor_deco(tp()));
}

int Thing::is_wall_deco(void)
{_
    return (tp_is_wall_deco(tp()));
}

int Thing::gfx_is_weapon_carry_anim(void)
{_
    return (tp_gfx_is_weapon_carry_anim(tp()));
}

int Thing::gfx_is_attack_anim(void)
{_
    return (tp_gfx_is_attack_anim(tp()));
}

int Thing::gfx_large_shadow(void)
{_
    return (tp_gfx_large_shadow(tp()));
}

int Thing::gfx_show_outlined(void)
{_
    return (tp_gfx_show_outlined(tp()));
}

int Thing::gfx_oversized_but_sitting_on_the_ground(void)
{_
    return (tp_gfx_oversized_but_sitting_on_the_ground(tp()));
}

int Thing::gfx_small_shadow_caster(void)
{_
    return (tp_gfx_small_shadow_caster(tp()));
}

int Thing::health_hunger_pct(void)
{_
    return (tp_stats_health_hunger_pct(tp()));
}

int Thing::hunger_clock_freq_ms(void)
{_
    return (tp_hunger_clock_freq_ms(tp()));
}

int Thing::is_hunger_insatiable(void)
{_
    return (tp_is_hunger_insatiable(tp()));
}

int Thing::health_initial(void)
{_
    return (tp_stats_health_initial(tp()));
}

int Thing::health_starving_pct(void)
{_
    return (tp_stats_health_starving_pct(tp()));
}

int Thing::is_active(void)
{_
    return (tp_is_active(tp()));
}

int Thing::is_attackable(void)
{_
    return (tp_is_attackable(tp()));
}

int Thing::is_bleeder(void)
{_
    return (tp_is_bleeder(tp()));
}

int Thing::is_blood(void)
{_
    return (tp_is_blood(tp()));
}

int Thing::is_combustible(void)
{_
    return (tp_is_combustible(tp()));
}

int Thing::is_corpse_on_death(void)
{_
    return (tp_is_corpse_on_death(tp()));
}

int Thing::is_corpse (void)
{_
    return (is_dead && is_corpse_on_death());
}

int Thing::is_corridor(void)
{_
    return (tp_is_corridor(tp()));
}

int Thing::is_deep_water(void)
{_
    return (tp_is_deep_water(tp()));
}

int Thing::is_dirt(void)
{_
    return (tp_is_dirt(tp()));
}

int Thing::is_door(void)
{_
    return (tp_is_door(tp()));
}

int Thing::is_entrance(void)
{_
    return (tp_is_entrance(tp()));
}

int Thing::is_exit(void)
{_
    return (tp_is_exit(tp()));
}

int Thing::is_explosion(void)
{_
    return (tp_is_explosion(tp()));
}

int Thing::is_floor(void)
{_
    return (tp_is_floor(tp()));
}

int Thing::is_food(void)
{_
    return (tp_is_food(tp()));
}

int Thing::is_key(void)
{_
    return (tp_is_key(tp()));
}

int Thing::is_lava(void)
{_
    return (tp_is_lava(tp()));
}

int Thing::is_chasm(void)
{_
    return (tp_is_chasm(tp()));
}

int Thing::is_light_strength(void)
{_
    return (tp_is_light_strength(tp()));
}

int Thing::is_made_of_meat(void)
{_
    return (tp_is_made_of_meat(tp()));
}

int Thing::is_meat_eater(void)
{_
    return (tp_is_meat_eater(tp()));
}

int Thing::is_monst(void)
{_
    return (tp_is_monst(tp()));
}

int Thing::is_alive_monst(void)
{_
    return (tp_is_monst(tp()) && !is_dead);
}

int Thing::is_movable(void)
{_
    return (tp_is_movable(tp()));
}

int Thing::is_movement_blocking(void)
{_
    return (tp_is_movement_blocking(tp()));
}

int Thing::is_obstacle(void)
{_
    return (tp_is_obstacle(tp()));
}

int Thing::is_player(void)
{_
    return (tp_is_player(tp()));
}

int Thing::is_projectile(void)
{_
    return (tp_is_projectile(tp()));
}

int Thing::is_ripple(void)
{_
    return (tp_is_ripple(tp()));
}

int Thing::is_rock(void)
{_
    return (tp_is_rock(tp()));
}

int Thing::is_rrr1(void)
{_
    return (tp_is_rrr1(tp()));
}

int Thing::is_rrr10(void)
{_
    return (tp_is_rrr10(tp()));
}

int Thing::is_rrr11(void)
{_
    return (tp_is_rrr11(tp()));
}

int Thing::is_rrr12(void)
{_
    return (tp_is_rrr12(tp()));
}

int Thing::is_rrr13(void)
{_
    return (tp_is_rrr13(tp()));
}

int Thing::is_rrr14(void)
{_
    return (tp_is_rrr14(tp()));
}

int Thing::is_rrr15(void)
{_
    return (tp_is_rrr15(tp()));
}

int Thing::is_rrr16(void)
{_
    return (tp_is_rrr16(tp()));
}

int Thing::is_rrr17(void)
{_
    return (tp_is_rrr17(tp()));
}

int Thing::is_rrr18(void)
{_
    return (tp_is_rrr18(tp()));
}

int Thing::is_rrr19(void)
{_
    return (tp_is_rrr19(tp()));
}

int Thing::is_rrr2(void)
{_
    return (tp_is_rrr2(tp()));
}

int Thing::is_rrr20(void)
{_
    return (tp_is_rrr20(tp()));
}

int Thing::is_rrr21(void)
{_
    return (tp_is_rrr21(tp()));
}

int Thing::is_rrr22(void)
{_
    return (tp_is_rrr22(tp()));
}

int Thing::is_rrr23(void)
{_
    return (tp_is_rrr23(tp()));
}

int Thing::is_rrr24(void)
{_
    return (tp_is_rrr24(tp()));
}

int Thing::is_rrr25(void)
{_
    return (tp_is_rrr25(tp()));
}

int Thing::is_rrr26(void)
{_
    return (tp_is_rrr26(tp()));
}

int Thing::is_loggable(void)
{_
    return (tp_is_loggable(tp()));
}

int Thing::is_rrr28(void)
{_
    return (tp_is_rrr28(tp()));
}

int Thing::is_rrr29(void)
{_
    return (tp_is_rrr29(tp()));
}

int Thing::is_rrr3(void)
{_
    return (tp_is_rrr3(tp()));
}

int Thing::is_rrr30(void)
{_
    return (tp_is_rrr30(tp()));
}

int Thing::is_rrr31(void)
{_
    return (tp_is_rrr31(tp()));
}

int Thing::gfx_is_on_fire_anim(void)
{_
    return (tp_gfx_is_on_fire_anim(tp()));
}

int Thing::is_attack_shove_chance_d1000(void)
{_
    return (tp_is_attack_shove_chance_d1000(tp()));
}

int Thing::is_hazard(void)
{_
    return (tp_is_hazard(tp()));
}

int Thing::is_attack_shove(void)
{_
    return (tp_is_attack_shove(tp()));
}

int Thing::is_shovable(void)
{_
    return (tp_is_shovable(tp()));
}

int Thing::is_cursor_path(void)
{_
    return (tp_is_cursor_path(tp()));
}

int Thing::is_rrr4(void)
{_
    return (tp_is_rrr4(tp()));
}

int Thing::is_blood_splatter(void)
{_
    return (tp_is_blood_splatter(tp()));
}

int Thing::is_no_tile(void)
{_
    return (tp_is_no_tile(tp()));
}

int Thing::is_msg(void)
{_
    return (tp_is_msg(tp()));
}

int Thing::is_attack_lunge(void)
{_
    return (tp_is_attack_lunge(tp()));
}

int Thing::defence(void)
{_
    return (tp_stats_defence(tp()));
}

int Thing::attack(void)
{_
    return (tp_stats_attack(tp()));
}

int Thing::is_secret_door(void)
{_
    return (tp_is_secret_door(tp()));
}

int Thing::is_cursor_can_hover_over(void)
{_
    return (tp_is_cursor_can_hover_over(tp()));
}

int Thing::is_cursor(void)
{_
    return (tp_is_cursor(tp()));
}

int Thing::is_rrr5(void)
{_
    return (tp_is_rrr5(tp()));
}

int Thing::gfx_dead_anim(void)
{_
    return (tp_gfx_dead_anim(tp()));
}

int Thing::is_rrr6(void)
{_
    return (tp_is_rrr6(tp()));
}

int Thing::is_rrr7(void)
{_
    return (tp_is_rrr7(tp()));
}

int Thing::is_rrr8(void)
{_
    return (tp_is_rrr8(tp()));
}

int Thing::is_rrr9(void)
{_
    return (tp_is_rrr9(tp()));
}

int Thing::is_undead(void)
{_
    return (tp_is_undead(tp()));
}

int Thing::is_wall(void)
{_
    return (tp_is_wall(tp()));
}

int Thing::is_water(void)
{_
    return (tp_is_water(tp()));
}

int Thing::is_water_dweller(void)
{_
    return (tp_is_water_dweller(tp()));
}

int Thing::is_water_hater(void)
{_
    return (tp_is_water_hater(tp()));
}

int Thing::is_weapon(void)
{_
    return (tp_is_weapon(tp()));
}

int Thing::weapon_damage(void)
{_
    return (tp_weapon_damage(tp()));
}

int Thing::weapon_use_delay_hundredths(void)
{_
    return (tp_weapon_use_delay_hundredths(tp()));
}

int Thing::weapon_use_distance(void)
{_
    return (tp_weapon_use_distance(tp()));
}

int Thing::z_depth(void)
{_
    return (tp_z_depth(tp()));
}

std::string Thing::stats_attack_hd(void)
{_
    return (tp_stats_attack_hd(tp()));
}

std::string Thing::is_nutrition_hd(void)
{_
    return (tp_is_nutrition_hd(tp()));
}

int Thing::is_nutrition(void)
{_
    return (tp()->is_nutrition());
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_lunge_to (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->lunge_to);
    } else {
        return (fpoint(0, 0));
    }
}

void Thing::set_lunge_to (fpoint v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->lunge_to = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_height (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->bounce_height);
    } else {
        return (0);
    }
}

void Thing::set_bounce_height (float v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->bounce_height = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_bounce_fade (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->bounce_fade);
    } else {
        return (0);
    }
}

void Thing::set_bounce_fade (float v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->bounce_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// bounce_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_bounce_count (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->bounce_count);
    } else {
        return (0);
    }
}

void Thing::set_bounce_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->bounce_count = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_height
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_height (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->fadeup_height);
    } else {
        return (0);
    }
}

void Thing::set_fadeup_height (float v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->fadeup_height = v;
}

////////////////////////////////////////////////////////////////////////////
// fadeup_fade
////////////////////////////////////////////////////////////////////////////
float Thing::get_fadeup_fade (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->fadeup_fade);
    } else {
        return (0);
    }
}

void Thing::set_fadeup_fade (float v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->fadeup_fade = v;
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
std::string Thing::get_msg (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->msg);
    } else {
        return ("");
    }
}

void Thing::set_msg (std::string v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
int Thing::get_submerged_offset (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->submerged_offset);
    } else {
        return (0);
    }
}

void Thing::set_submerged_offset (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->submerged_offset = v;
}

////////////////////////////////////////////////////////////////////////////
// gold
////////////////////////////////////////////////////////////////////////////
int Thing::get_gold (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->gold);
    } else {
        return (0);
    }
}

int Thing::set_gold (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->gold = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_gold (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->gold -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_gold (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->gold += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_gold (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->gold--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_gold (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->gold++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// tick
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->tick);
    } else {
        return (0);
    }
}

uint32_t Thing::set_tick (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

uint32_t Thing::decr_tick (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

uint32_t Thing::incr_tick (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

uint32_t Thing::decr_tick (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

uint32_t Thing::incr_tick (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_health (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_health);
    } else {
        return (0);
    }
}

int Thing::set_stats_health (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_health (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_health (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_health (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_health (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_health_max (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_health_max);
    } else {
        return (0);
    }
}

int Thing::set_stats_health_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health_max = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_health_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health_max -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_health_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health_max += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_health_max (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health_max--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_health_max (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_health_max++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// defence
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_defence (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_defence);
    } else {
        return (0);
    }
}

int Thing::set_stats_defence (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_defence (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_defence (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_defence (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_defence (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// defence_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_defence_max (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_defence_max);
    } else {
        return (0);
    }
}

int Thing::set_stats_defence_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence_max = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_defence_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence_max -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_defence_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence_max += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_defence_max (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence_max--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_defence_max (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_defence_max++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attack (void)
{_
    if (monstp) {
        verify(monstp);
        if (monstp->stats_attack) {
            return (monstp->stats_attack);
        }
        return (tp()->attack_damage.roll());
    } else {
        return (0);
    }
}

int Thing::set_stats_attack (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_attack (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_attack (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_attack (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_attack (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attack_max (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_attack_max);
    } else {
        return (0);
    }
}

int Thing::set_stats_attack_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_max = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_attack_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_max -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_attack_max (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_max += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_attack_max (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_max--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_attack_max (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_max++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attack_rate_tenths
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_attack_rate_tenths (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_attack_rate_tenths);
    } else {
        return (0);
    }
}

int Thing::set_stats_attack_rate_tenths (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_rate_tenths = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_attack_rate_tenths (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_rate_tenths -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_attack_rate_tenths (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_rate_tenths += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_attack_rate_tenths (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_rate_tenths--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_attack_rate_tenths (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_attack_rate_tenths++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// attacked_rate_tenths
////////////////////////////////////////////////////////////////////////////
int Thing::get_lifespan_count (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->lifespan_count);
    } else {
        return (0);
    }
}

int Thing::set_lifespan_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->lifespan_count = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_lifespan_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->lifespan_count -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_lifespan_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->lifespan_count += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_lifespan_count (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->lifespan_count--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_lifespan_count (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->lifespan_count++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats01
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats01 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats01);
    } else {
        return (0);
    }
}

int Thing::set_stats01 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats01 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats01 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats01 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats01 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats01 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats01 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats01--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats01 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats01++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats02
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats02 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats02);
    } else {
        return (0);
    }
}

int Thing::set_stats02 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats02 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats02 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats02 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats02 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats02 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats02 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats02--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats02 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats02++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats03
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats03 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats03);
    } else {
        return (0);
    }
}

int Thing::set_stats03 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats03 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats03 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats03 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats03 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats03 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats03 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats03--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats03 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats03++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats04
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats04 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats04);
    } else {
        return (0);
    }
}

int Thing::set_stats04 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats04 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats04 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats04 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats04 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats04 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats04 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats04--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats04 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats04++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats05
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats05 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats05);
    } else {
        return (0);
    }
}

int Thing::set_stats05 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats05 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats05 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats05 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats05 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats05 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats05 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats05--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats05 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats05++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats06
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats06 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats06);
    } else {
        return (0);
    }
}

int Thing::set_stats06 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats06 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats06 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats06 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats06 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats06 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats06 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats06--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats06 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats06++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats07
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats07 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats07);
    } else {
        return (0);
    }
}

int Thing::set_stats07 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats07 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats07 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats07 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats07 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats07 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats07 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats07--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats07 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats07++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats08
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats08 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats08);
    } else {
        return (0);
    }
}

int Thing::set_stats08 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats08 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats08 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats08 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats08 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats08 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats08 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats08--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats08 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats08++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats09
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats09 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats09);
    } else {
        return (0);
    }
}

int Thing::set_stats09 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats09 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats09 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats09 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats09 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats09 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats09 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats09--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats09 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats09++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats10
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats10 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats10);
    } else {
        return (0);
    }
}

int Thing::set_stats10 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats10 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats10 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats10 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats10 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats10 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats10 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats10--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats10 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats10++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats11
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats11 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats11);
    } else {
        return (0);
    }
}

int Thing::set_stats11 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats11 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats11 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats11 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats11 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats11 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats11 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats11--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats11 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats11++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats12
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats12 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats12);
    } else {
        return (0);
    }
}

int Thing::set_stats12 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats12 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats12 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats12 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats12 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats12 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats12 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats12--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats12 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats12++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats13
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats13 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats13);
    } else {
        return (0);
    }
}

int Thing::set_stats13 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats13 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats13 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats13 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats13 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats13 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats13 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats13--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats13 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats13++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats14
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats14 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats14);
    } else {
        return (0);
    }
}

int Thing::set_stats14 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats14 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats14 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats14 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats14 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats14 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats14 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats14--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats14 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats14++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats15
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats15 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats15);
    } else {
        return (0);
    }
}

int Thing::set_stats15 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats15 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats15 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats15 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats15 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats15 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats15 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats15--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats15 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats15++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats16
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats16 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats16);
    } else {
        return (0);
    }
}

int Thing::set_stats16 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats16 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats16 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats16 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats16 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats16 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats16 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats16--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats16 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats16++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats17
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats17 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats17);
    } else {
        return (0);
    }
}

int Thing::set_stats17 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats17 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats17 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats17 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats17 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats17 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats17 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats17--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats17 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats17++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats18
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats18 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats18);
    } else {
        return (0);
    }
}

int Thing::set_stats18 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats18 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats18 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats18 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats18 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats18 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats18 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats18--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats18 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats18++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats19
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats19 (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats19);
    } else {
        return (0);
    }
}

int Thing::set_stats19 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats19 = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats19 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats19 -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats19 (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats19 += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats19 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats19--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats19 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats19++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats_strength
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats_strength (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->stats_strength);
    } else {
        return (0);
    }
}

int Thing::set_stats_strength (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_strength = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_strength (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_strength -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_strength (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_strength += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_stats_strength (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_strength--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_stats_strength (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->stats_strength++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// owned_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_owned_count (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->owned_count);
    } else {
        return (0);
    }
}

int Thing::set_owned_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owned_count = v);
}

int Thing::decr_owned_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owned_count -= v);
}

int Thing::incr_owned_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owned_count += v);
}

int Thing::decr_owned_count (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owned_count--);
}

int Thing::incr_owned_count (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owned_count++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_lunge_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_lunge_begin (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_lunge_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_lunge_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_begin = v);
}

timestamp_t Thing::decr_timestamp_lunge_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_begin -= v);
}

timestamp_t Thing::incr_timestamp_lunge_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_begin += v);
}

timestamp_t Thing::decr_timestamp_lunge_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_begin--);
}

timestamp_t Thing::incr_timestamp_lunge_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_lunge_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_lunge_end (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_lunge_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_lunge_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_end = v);
}

timestamp_t Thing::decr_timestamp_lunge_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_end -= v);
}

timestamp_t Thing::incr_timestamp_lunge_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_end += v);
}

timestamp_t Thing::decr_timestamp_lunge_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_end--);
}

timestamp_t Thing::incr_timestamp_lunge_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_lunge_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_bounce_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_bounce_begin (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_bounce_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_bounce_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_begin = v);
}

timestamp_t Thing::decr_timestamp_bounce_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_begin -= v);
}

timestamp_t Thing::incr_timestamp_bounce_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_begin += v);
}

timestamp_t Thing::decr_timestamp_bounce_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_begin--);
}

timestamp_t Thing::incr_timestamp_bounce_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_bounce_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_bounce_end (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_bounce_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_bounce_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_end = v);
}

timestamp_t Thing::decr_timestamp_bounce_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_end -= v);
}

timestamp_t Thing::incr_timestamp_bounce_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_end += v);
}

timestamp_t Thing::decr_timestamp_bounce_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_end--);
}

timestamp_t Thing::incr_timestamp_bounce_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_fadeup_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_fadeup_begin (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_fadeup_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_fadeup_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_begin = v);
}

timestamp_t Thing::decr_timestamp_fadeup_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_begin -= v);
}

timestamp_t Thing::incr_timestamp_fadeup_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_begin += v);
}

timestamp_t Thing::decr_timestamp_fadeup_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_begin--);
}

timestamp_t Thing::incr_timestamp_fadeup_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_fadeup_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_fadeup_end (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_fadeup_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_fadeup_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_end = v);
}

timestamp_t Thing::decr_timestamp_fadeup_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_end -= v);
}

timestamp_t Thing::incr_timestamp_fadeup_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_end += v);
}

timestamp_t Thing::decr_timestamp_fadeup_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_end--);
}

timestamp_t Thing::incr_timestamp_fadeup_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_fadeup_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_last_attacked
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_last_attacked (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_last_attacked);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_last_attacked (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attacked = v);
}

timestamp_t Thing::decr_timestamp_last_attacked (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attacked -= v);
}

timestamp_t Thing::incr_timestamp_last_attacked (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attacked += v);
}

timestamp_t Thing::decr_timestamp_last_attacked (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attacked--);
}

timestamp_t Thing::incr_timestamp_last_attacked (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attacked++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_last_attack
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_last_attack (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_last_attack);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_last_attack (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attack = v);
}

timestamp_t Thing::decr_timestamp_last_attack (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attack -= v);
}

timestamp_t Thing::incr_timestamp_last_attack (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attack += v);
}

timestamp_t Thing::decr_timestamp_last_attack (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attack--);
}

timestamp_t Thing::incr_timestamp_last_attack (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_attack++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_flip_start
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_flip_start (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_flip_start);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_flip_start (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_flip_start = v);
}

timestamp_t Thing::decr_timestamp_flip_start (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_flip_start -= v);
}

timestamp_t Thing::incr_timestamp_flip_start (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_flip_start += v);
}

timestamp_t Thing::decr_timestamp_flip_start (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_flip_start--);
}

timestamp_t Thing::incr_timestamp_flip_start (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_flip_start++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_move_start
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_move_begin (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_move_begin);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_move_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_begin = v);
}

timestamp_t Thing::decr_timestamp_move_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_begin -= v);
}

timestamp_t Thing::incr_timestamp_move_begin (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_begin += v);
}

timestamp_t Thing::decr_timestamp_move_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_begin--);
}

timestamp_t Thing::incr_timestamp_move_begin (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_move_end
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_move_end (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_move_end);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_move_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_end = v);
}

timestamp_t Thing::decr_timestamp_move_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_end -= v);
}

timestamp_t Thing::incr_timestamp_move_end (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_end += v);
}

timestamp_t Thing::decr_timestamp_move_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_end--);
}

timestamp_t Thing::incr_timestamp_move_end (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_move_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_born
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_born (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_born);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_born (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_born = v);
}

timestamp_t Thing::decr_timestamp_born (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_born -= v);
}

timestamp_t Thing::incr_timestamp_born (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_born += v);
}

timestamp_t Thing::decr_timestamp_born (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_born--);
}

timestamp_t Thing::incr_timestamp_born (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_born++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_hunger_tick
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_hunger_tick (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_hunger_tick);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_hunger_tick (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_hunger_tick = v);
}

timestamp_t Thing::decr_timestamp_hunger_tick (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_hunger_tick -= v);
}

timestamp_t Thing::incr_timestamp_hunger_tick (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_hunger_tick += v);
}

timestamp_t Thing::decr_timestamp_hunger_tick (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_hunger_tick--);
}

timestamp_t Thing::incr_timestamp_hunger_tick (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_hunger_tick++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_ai_next
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_ai_next (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_ai_next);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_ai_next (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_ai_next = v);
}

timestamp_t Thing::decr_timestamp_ai_next (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_ai_next -= v);
}

timestamp_t Thing::incr_timestamp_ai_next (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_ai_next += v);
}

timestamp_t Thing::decr_timestamp_ai_next (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_ai_next--);
}

timestamp_t Thing::incr_timestamp_ai_next (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_ai_next++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_collision
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_collision (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_collision);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_collision (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_collision = v);
}

timestamp_t Thing::decr_timestamp_collision (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_collision -= v);
}

timestamp_t Thing::incr_timestamp_collision (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_collision += v);
}

timestamp_t Thing::decr_timestamp_collision (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_collision--);
}

timestamp_t Thing::incr_timestamp_collision (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_collision++);
}

////////////////////////////////////////////////////////////////////////////
// owner_id
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_owner_id (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->owner_id);
    } else {
        return (0);
    }
}

uint32_t Thing::set_owner_id (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owner_id = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_carry_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_weapon_id_carry_anim (void)
{_
    if (monstp) {
        return (monstp->weapon_id_carry_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_weapon_id_carry_anim (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->weapon_id_carry_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_use_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_weapon_id_use_anim (void)
{_
    if (monstp) {
        return (monstp->weapon_id_use_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_weapon_id_use_anim (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->weapon_id_use_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_tp_id
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_weapon_id (void)
{_
    if (monstp) {
        // con("get weapon %08X", monstp->weapon_id);
        return (monstp->weapon_id);
    } else {
        // con("get weapon id => none");
        return (0);
    }
}

uint32_t Thing::set_weapon_id (uint32_t v)
{_
    new_monst();
    // con("set weapon %08X", v);
    return (monstp->weapon_id = v);
}

////////////////////////////////////////////////////////////////////////////
// on_fire_id_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_on_fire_anim_id (void)
{_
    if (monstp) {
        return (monstp->on_fire_id_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_on_fire_anim_id (uint32_t v)
{_
    new_monst();
//con("%s %08X", __FUNCTION__, v);
    return (monstp->on_fire_id_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// on_fire_count
////////////////////////////////////////////////////////////////////////////
int Thing::get_on_fire_count (void)
{_
    if (monstp) {
        verify(monstp);
        return (monstp->on_fire_count);
    } else {
        return (0);
    }
}

int Thing::set_on_fire_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    if (v) {
        if (!monstp->on_fire_count) {
            set_on_fire();
        }
    } else {
        if (monstp->on_fire_count) {
            unset_on_fire();
        }
    }
    auto n = (monstp->on_fire_count = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_on_fire_count (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->on_fire_count -= v);
    if (!monstp->on_fire_count) {
        unset_on_fire();
    }
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_on_fire_count (int v)
{_
    new_monst();

//con("%s", __FUNCTION__);
    if (!monstp->on_fire_count) {
        set_on_fire();
    }
    auto n = (monstp->on_fire_count += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_on_fire_count (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->on_fire_count--);
    if (!monstp->on_fire_count) {
        unset_on_fire();
    }
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_on_fire_count (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    if (!monstp->on_fire_count) {
        set_on_fire();
    }
    auto n = (monstp->on_fire_count++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// interpolated_mid_at
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_interpolated_mid_at (void)
{_
    if (monstp) {
        if (monstp->interpolated_mid_at == fpoint(0, 0)) {
            return (mid_at);
        } else {
            return (monstp->interpolated_mid_at);
        }
    } else {
        return (mid_at);
    }
}

fpoint Thing::set_interpolated_mid_at (fpoint v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->interpolated_mid_at = v);
}
