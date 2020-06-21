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

//
// Dice
//
const Dice& Thing::get_idle_tick_dice (void) const {_ return (tp()->idle_tick_dice()); }
const std::string& Thing::get_idle_tick_dice_str (void) const {_ return (tp()->idle_tick_dice_str()); }
int Thing::get_idle_tick (void) const {_ return (tp()->idle_tick_dice().roll()); }

const Dice& Thing::get_nutrition_dice (void) const {_ return (tp()->nutrition_dice()); }
const std::string& Thing::get_nutrition_dice_str (void) const {_ return (tp()->nutrition_dice_str()); }
int Thing::get_nutrition (void) const {_ return (tp()->nutrition_dice().roll()); }

const Dice& Thing::get_stats_attack_dice (void) const {_ return (tp()->stats_attack_dice()); }
const std::string& Thing::get_stats_attack_dice_str (void) const {_ return (tp()->stats_attack_dice_str()); }
int Thing::get_stats_attack (void) const {_ return (tp()->stats_attack_dice().roll()); }

const Dice& Thing::get_gold_value_dice (void) const {_ return (tp()->gold_value_dice()); }
const std::string& Thing::get_gold_value_dice_str (void) const {_ return (tp()->gold_value_dice_str()); }
int Thing::get_gold_value (void) const {_ return (tp()->gold_value_dice().roll()); }

const Dice& Thing::get_lifespan_dice (void) const {_ return (tp()->lifespan_dice()); }
const std::string& Thing::get_lifespan_dice_str (void) const {_ return (tp()->lifespan_dice_str()); }
int Thing::get_lifespan_initial (void) const {_ return (tp()->lifespan_dice().roll()); }

const Dice& Thing::get_resurrect_dice (void) const {_ return (tp()->resurrect_dice()); }
const std::string& Thing::get_resurrect_dice_str (void) const {_ return (tp()->resurrect_dice_str()); }
int Thing::get_resurrect (void) const {_ return (tp()->resurrect_dice().roll()); }
bool Thing::get_resurrect_success (void) const {_ return (tp()->resurrect_dice().crit_roll_minus_modifier()); }

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
        newptr(monstp->age_map, "age map");

        //
        // Setup random ages
        //
        auto age_map = monstp->age_map->val;
        for (auto y = 0; y < MAP_HEIGHT; y++) { 
            for (auto x = 0; x < MAP_WIDTH; x++) {
                set(age_map, x, y, (timestamp_t)myrand());
            }
        }
    }
}

void Thing::delete_age_map (void)
{_
    if (monstp) {
        verify(monstp);
        if (monstp->age_map) {
            oldptr(monstp->age_map);
            delete monstp->age_map; 
            monstp->age_map = 0;
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

        auto dmap = monstp->dmap_scent->val;
        for (auto y = 0; y < MAP_HEIGHT; y++) { 
            for (auto x = 0; x < MAP_WIDTH; x++) {
                set(dmap, x, y, DMAP_IS_WALL);
            }
        }
    }
}

void Thing::delete_dmap_scent (void)
{_
    if (monstp) {
        verify(monstp);
        if (monstp->dmap_scent) {
            oldptr(monstp->dmap_scent);
            delete monstp->dmap_scent; 
            monstp->dmap_scent = 0;
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

std::size_t Thing::get_light_count (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->light.size());
    } else {
        return (0);
    }
}

void Thing::new_light (fpoint at, fpoint offset, float strength, color col)
{_
    new_monst();
    auto l = light_new(this, at, offset, strength, col);
    monstp->light.push_back(l);
    monstp->light_strength = strength;
    monstp->light_col = col;
}

void Thing::new_light (fpoint at, float strength, color col)
{_
    new_light(at, fpoint(0, 0), strength, col);
}

void Thing::delete_light (void)
{_
    if (monstp) {
        verify(monstp);
        for (auto& l : monstp->light) {
            delete l;
        }
    }
}

int Thing::ai_delay_after_moving_ms(void)
{_
    return (tp()->ai_delay_after_moving_ms());
}

int Thing::ai_scent_distance(void) const
{_
    return (tp()->ai_scent_distance());
}

int Thing::collision_attack(void) const
{_
    return (tp()->collision_attack());
}

int Thing::collision_box(void) const
{_
    return (tp()->collision_box());
}

int Thing::collision_check(void) const
{_
    return (tp()->collision_check());
}

int Thing::collision_circle(void) const
{_
    return (tp()->collision_circle());
}

int Thing::collision_hit_priority(void) const
{_
    return (tp()->collision_hit_priority());
}

int Thing::is_interesting(void) const
{_
    return (tp()->is_interesting());
}

int Thing::gfx_animated(void) const
{_
    return (tp()->gfx_animated());
}

int Thing::gfx_animated_can_vflip(void) const
{_
    return (tp()->gfx_animated_can_vflip());
}

int Thing::gfx_animated_no_dir(void) const
{_
    return (tp()->gfx_animated_no_dir());
}

int Thing::gfx_bounce_on_move(void) const
{_
    return (tp()->gfx_bounce_on_move());
}

int Thing::gfx_animated_can_hflip(void) const
{_
    return (tp()->gfx_animated_can_hflip());
}

int Thing::gfx_an_animation_only(void) const
{_
    return (tp()->gfx_an_animation_only());
}

int Thing::is_floor_deco(void) const
{_
    return (tp()->is_floor_deco());
}

int Thing::is_wall_deco(void) const
{_
    return (tp()->is_wall_deco());
}

int Thing::gfx_weapon_carry_anim(void) const
{_
    return (tp()->gfx_weapon_carry_anim());
}

int Thing::gfx_attack_anim(void) const
{_
    return (tp()->gfx_attack_anim());
}

int Thing::is_light_blocker(void) const
{_
    return (tp()->is_light_blocker());
}

int Thing::gfx_show_outlined(void) const
{_
    return (tp()->gfx_show_outlined());
}

int Thing::gfx_oversized_but_sitting_on_the_ground(void) const
{_
    return (tp()->gfx_oversized_but_sitting_on_the_ground());
}

int Thing::gfx_small_shadow_caster(void) const
{_
    return (tp()->gfx_small_shadow_caster());
}

int Thing::health_hunger_pct(void) const
{_
    return (tp()->stats_health_hunger_pct());
}

int Thing::hunger_clock_freq_ms(void) const
{_
    return (tp()->hunger_clock_freq_ms());
}

int Thing::is_hunger_insatiable(void) const
{_
    return (tp()->is_hunger_insatiable());
}

int Thing::health_initial(void) const
{_
    return (tp()->stats_health_initial());
}

int Thing::health_starving_pct(void) const
{_
    return (tp()->stats_health_starving_pct());
}

int Thing::is_active(void) const
{_
    return (tp()->is_active());
}

int Thing::is_attackable(void) const
{_
    return (tp()->is_attackable());
}

int Thing::is_bleeder(void) const
{_
    return (tp()->is_bleeder());
}

int Thing::is_blood(void) const
{_
    return (tp()->is_blood());
}

int Thing::is_combustible(void) const
{_
    return (tp()->is_combustible());
}

int Thing::is_corpse_on_death(void) const
{_
    return (tp()->is_corpse_on_death());
}

int Thing::is_corpse (void) const
{_
    return (is_dead && is_corpse_on_death());
}

int Thing::is_corridor(void) const
{_
    return (tp()->is_corridor());
}

int Thing::is_deep_water(void) const
{_
    return (tp()->is_deep_water());
}

int Thing::is_dirt(void) const
{_
    return (tp()->is_dirt());
}

int Thing::is_door(void) const
{_
    return (tp()->is_door());
}

int Thing::is_entrance(void) const
{_
    return (tp()->is_entrance());
}

int Thing::is_exit(void) const
{_
    return (tp()->is_exit());
}

int Thing::is_explosion(void) const
{_
    return (tp()->is_explosion());
}

int Thing::is_floor(void) const
{_
    return (tp()->is_floor());
}

int Thing::is_food(void) const
{_
    return (tp()->is_food());
}

int Thing::is_key(void) const
{_
    return (tp()->is_key());
}

int Thing::is_lava(void) const
{_
    return (tp()->is_lava());
}

int Thing::is_chasm(void) const
{_
    return (tp()->is_chasm());
}

int Thing::is_light_strength(void) const
{_
    return (tp()->is_light_strength());
}

int Thing::is_made_of_meat(void) const
{_
    return (tp()->is_made_of_meat());
}

int Thing::is_meat_eater(void) const
{_
    return (tp()->is_meat_eater());
}

int Thing::is_monst(void) const
{_
    return (tp()->is_monst());
}

int Thing::is_alive_monst(void) const
{_
    return (tp()->is_monst() && !is_dead);
}

int Thing::is_movable(void) const
{_
    return (tp()->is_movable());
}

int Thing::is_movement_blocking(void) const
{_
    return (tp()->is_movement_blocking());
}

int Thing::ai_obstacle(void) const
{_
    return (tp()->ai_obstacle());
}

int Thing::is_player(void) const
{_
    return (tp()->is_player());
}

int Thing::is_projectile(void) const
{_
    return (tp()->is_projectile());
}

int Thing::is_ripple(void) const
{_
    return (tp()->is_ripple());
}

int Thing::is_rock(void) const
{_
    return (tp()->is_rock());
}

int Thing::is_rrr1(void) const
{_
    return (tp()->is_rrr1());
}

int Thing::is_rrr10(void) const
{_
    return (tp()->is_rrr10());
}

int Thing::is_rrr11(void) const
{_
    return (tp()->is_rrr11());
}

int Thing::is_able_to_change_levels(void) const
{_
    return (tp()->is_able_to_change_levels());
}

int Thing::is_collected_as_gold(void) const
{_
    return (tp()->is_collected_as_gold());
}

int Thing::is_gold(void) const
{_
    return (tp()->is_gold());
}

int Thing::is_loggable_for_important_stuff(void) const
{_
    return (tp()->is_loggable_for_important_stuff());
}

int Thing::tick_catches_up_on_attack(void) const
{_
    return (tp()->tick_catches_up_on_attack());
}

int Thing::is_temporary(void) const
{_
    return (tp()->is_temporary());
}

int Thing::is_smoke(void) const
{_
    return (tp()->is_smoke());
}

int Thing::is_fire_hater(void) const
{_
    return (tp()->is_fire_hater());
}

int Thing::is_rrr2(void) const
{_
    return (tp()->is_rrr2());
}

int Thing::is_treasure(void) const
{_
    return (tp()->is_treasure());
}

int Thing::is_collectable(void) const
{_
    return (tp()->is_collectable());
}

int Thing::is_resurrectable(void) const
{_
    return (tp()->is_resurrectable());
}

int Thing::is_intelligent(void) const
{_
    return (tp()->is_intelligent());
}

int Thing::is_double_damage_from_fire(void) const
{_
    return (tp()->is_double_damage_from_fire());
}

int Thing::is_fire(void) const
{_
    return (tp()->is_fire());
}

int Thing::is_dead_on_shove(void) const
{_
    return (tp()->is_dead_on_shove());
}

int Thing::is_loggable_for_unimportant_stuff(void) const
{_
    return (tp()->is_loggable_for_unimportant_stuff());
}

int Thing::is_torch(void) const
{_
    return (tp()->is_torch());
}

int Thing::gfx_bounce_always(void) const
{_
    return (tp()->gfx_bounce_always());
}

int Thing::is_rrr3(void) const
{_
    return (tp()->is_rrr3());
}

int Thing::normal_placement_rules(void) const
{_
    return (tp()->normal_placement_rules());
}

int Thing::is_flammable(void) const
{_
    return (tp()->is_flammable());
}

int Thing::gfx_on_fire_anim(void) const
{_
    return (tp()->gfx_on_fire_anim());
}

int Thing::is_attack_shove_chance_d1000(void) const
{_
    return (tp()->is_attack_shove_chance_d1000());
}

int Thing::is_hazard(void) const
{_
    return (tp()->is_hazard());
}

int Thing::is_attack_shove(void) const
{_
    return (tp()->is_attack_shove());
}

int Thing::is_shovable(void) const
{_
    return (tp()->is_shovable());
}

int Thing::is_cursor_path(void) const
{_
    return (tp()->is_cursor_path());
}

int Thing::is_rrr4(void) const
{_
    return (tp()->is_rrr4());
}

int Thing::is_blood_splatter(void) const
{_
    return (tp()->is_blood_splatter());
}

int Thing::is_no_tile(void) const
{_
    return (tp()->is_no_tile());
}

int Thing::is_msg(void) const
{_
    return (tp()->is_msg());
}

int Thing::is_attack_lunge(void) const
{_
    return (tp()->is_attack_lunge());
}

int Thing::defence(void) const
{_
    return (tp()->stats_defence());
}

int Thing::is_secret_door(void) const
{_
    return (tp()->is_secret_door());
}

int Thing::is_cursor_can_hover_over(void) const
{_
    return (tp()->is_cursor_can_hover_over());
}

int Thing::is_cursor(void) const
{_
    return (tp()->is_cursor());
}

int Thing::is_rrr5(void) const
{_
    return (tp()->is_rrr5());
}

int Thing::gfx_dead_anim(void) const
{_
    return (tp()->gfx_dead_anim());
}

int Thing::is_rrr6(void) const
{_
    return (tp()->is_rrr6());
}

int Thing::is_rrr7(void) const
{_
    return (tp()->is_rrr7());
}

int Thing::is_rrr8(void) const
{_
    return (tp()->is_rrr8());
}

int Thing::is_rrr9(void) const
{_
    return (tp()->is_rrr9());
}

int Thing::is_undead(void) const
{_
    return (tp()->is_undead());
}

int Thing::is_wall(void) const
{_
    return (tp()->is_wall());
}

int Thing::is_water(void) const
{_
    return (tp()->is_water());
}

int Thing::is_water_dweller(void) const
{_
    return (tp()->is_water_dweller());
}

int Thing::is_water_hater(void) const
{_
    return (tp()->is_water_hater());
}

int Thing::is_weapon(void) const
{_
    return (tp()->is_weapon());
}

int Thing::weapon_damage(void) const
{_
    return (tp()->weapon_damage());
}

int Thing::weapon_use_delay_hundredths(void) const
{_
    return (tp()->weapon_use_delay_hundredths());
}

int Thing::weapon_use_distance(void) const
{_
    return (tp()->weapon_use_distance());
}

int Thing::z_depth(void) const
{_
    return (tp()->z_depth);
}

int Thing::z_prio(void) const
{_
    return (tp()->z_prio);
}

////////////////////////////////////////////////////////////////////////////
// lunge_to
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_lunge_to (void) const
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
float Thing::get_bounce_height (void) const
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
float Thing::get_bounce_fade (void) const
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
int Thing::get_bounce_count (void) const
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
float Thing::get_fadeup_height (void) const
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
float Thing::get_fadeup_fade (void) const
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
// wobble
////////////////////////////////////////////////////////////////////////////
float Thing::get_wobble (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->wobble);
    } else {
        return (0);
    }
}

void Thing::set_wobble (float v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->wobble = v;
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
std::string Thing::get_msg (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->msg);
    } else {
        return ("");
    }
}

void Thing::set_msg (const std::string& v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    monstp->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
int Thing::get_submerged_offset (void) const
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
int Thing::get_gold (void) const
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
uint32_t Thing::get_tick (void) const
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
int Thing::get_stats_health (void) const
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
int Thing::get_stats_health_max (void) const
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
int Thing::get_stats_defence (void) const
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
int Thing::get_stats_defence_max (void) const
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
// attack_rate_tenths
////////////////////////////////////////////////////////////////////////////
int Thing::get_tick_rate_tenths (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->tick_rate_tenths);
    } else {
        return (0);
    }
}

int Thing::set_tick_rate_tenths (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick_rate_tenths = v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_tick_rate_tenths (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick_rate_tenths -= v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_tick_rate_tenths (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick_rate_tenths += v);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::decr_tick_rate_tenths (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick_rate_tenths--);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

int Thing::incr_tick_rate_tenths (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    auto n = (monstp->tick_rate_tenths++);
    if (is_player()) { game_status_wid_init(); }
    return (n);
}

////////////////////////////////////////////////////////////////////////////
// stats01
////////////////////////////////////////////////////////////////////////////
int Thing::get_stats01 (void) const
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
int Thing::get_stats02 (void) const
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
int Thing::get_stats03 (void) const
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
int Thing::get_stats04 (void) const
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
int Thing::get_stats05 (void) const
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
int Thing::get_stats06 (void) const
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
int Thing::get_stats07 (void) const
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
int Thing::get_stats08 (void) const
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
int Thing::get_stats09 (void) const
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
int Thing::get_stats10 (void) const
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
int Thing::get_stats11 (void) const
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
int Thing::get_stats12 (void) const
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
int Thing::get_stats13 (void) const
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
int Thing::get_stats14 (void) const
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
int Thing::get_stats15 (void) const
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
int Thing::get_stats16 (void) const
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
int Thing::get_stats17 (void) const
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
int Thing::get_stats18 (void) const
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
int Thing::get_stats19 (void) const
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
int Thing::get_stats_strength (void) const
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
int Thing::get_owned_count (void) const
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
// lifespan
////////////////////////////////////////////////////////////////////////////
int Thing::get_lifespan (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->lifespan);
    } else {
        return (0);
    }
}

int Thing::set_lifespan (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->lifespan = v);
}

int Thing::decr_lifespan (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->lifespan -= v);
}

int Thing::incr_lifespan (int v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->lifespan += v);
}

int Thing::decr_lifespan (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->lifespan--);
}

int Thing::incr_lifespan (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->lifespan++);
}

////////////////////////////////////////////////////////////////////////////
// tick_last_did_something
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_tick_last_did_something (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->tick_last_did_something);
    } else {
        return (0);
    }
}

uint32_t Thing::set_tick_last_did_something (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->tick_last_did_something = v);
}

uint32_t Thing::decr_tick_last_did_something (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->tick_last_did_something -= v);
}

uint32_t Thing::incr_tick_last_did_something (uint32_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->tick_last_did_something += v);
}

uint32_t Thing::decr_tick_last_did_something (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->tick_last_did_something--);
}

uint32_t Thing::incr_tick_last_did_something (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->tick_last_did_something++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_lunge_begin
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_lunge_begin (void) const
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
timestamp_t Thing::get_timestamp_lunge_end (void) const
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
timestamp_t Thing::get_timestamp_bounce_begin (void) const
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
timestamp_t Thing::get_timestamp_bounce_end (void) const
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
timestamp_t Thing::get_timestamp_fadeup_begin (void) const
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
timestamp_t Thing::get_timestamp_fadeup_end (void) const
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
// timestamp_last_ticked
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_last_ticked (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_last_ticked);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_last_ticked (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_ticked = v);
}

timestamp_t Thing::decr_timestamp_last_ticked (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_ticked -= v);
}

timestamp_t Thing::incr_timestamp_last_ticked (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_ticked += v);
}

timestamp_t Thing::decr_timestamp_last_ticked (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_ticked--);
}

timestamp_t Thing::incr_timestamp_last_ticked (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_ticked++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_last_tick
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_last_tick (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_last_tick);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_last_tick (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_tick = v);
}

timestamp_t Thing::decr_timestamp_last_tick (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_tick -= v);
}

timestamp_t Thing::incr_timestamp_last_tick (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_tick += v);
}

timestamp_t Thing::decr_timestamp_last_tick (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_tick--);
}

timestamp_t Thing::incr_timestamp_last_tick (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_last_tick++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_flip_start
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_flip_start (void) const
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
timestamp_t Thing::get_timestamp_move_begin (void) const
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
timestamp_t Thing::get_timestamp_move_end (void) const
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
timestamp_t Thing::get_timestamp_born (void) const
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
timestamp_t Thing::get_timestamp_hunger_tick (void) const
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
// timestamp_UNUSED1
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_UNUSED1 (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_UNUSED1);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_UNUSED1 (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED1 = v);
}

timestamp_t Thing::decr_timestamp_UNUSED1 (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED1 -= v);
}

timestamp_t Thing::incr_timestamp_UNUSED1 (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED1 += v);
}

timestamp_t Thing::decr_timestamp_UNUSED1 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED1--);
}

timestamp_t Thing::incr_timestamp_UNUSED1 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED1++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_UNUSED2
////////////////////////////////////////////////////////////////////////////
timestamp_t Thing::get_timestamp_UNUSED2 (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->timestamp_UNUSED2);
    } else {
        return (0);
    }
}

timestamp_t Thing::set_timestamp_UNUSED2 (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED2 = v);
}

timestamp_t Thing::decr_timestamp_UNUSED2 (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED2 -= v);
}

timestamp_t Thing::incr_timestamp_UNUSED2 (timestamp_t v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED2 += v);
}

timestamp_t Thing::decr_timestamp_UNUSED2 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED2--);
}

timestamp_t Thing::incr_timestamp_UNUSED2 (void)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->timestamp_UNUSED2++);
}

////////////////////////////////////////////////////////////////////////////
// owner_id
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_owner_id (void) const
{_
    if (monstp) {
        verify(monstp);
        return (monstp->owner_id);
    } else {
        return (0);
    }
}

ThingId Thing::set_owner_id (ThingId v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owner_id = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_carry_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_weapon_id_carry_anim (void) const
{_
    if (monstp) {
        return (monstp->weapon_id_carry_anim);
    } else {
        return (0);
    }
}

ThingId Thing::set_weapon_id_carry_anim (ThingId v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->weapon_id_carry_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_id_use_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_weapon_id_use_anim (void) const
{_
    if (monstp) {
        return (monstp->weapon_id_use_anim);
    } else {
        return (0);
    }
}

ThingId Thing::set_weapon_id_use_anim (ThingId v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->weapon_id_use_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// weapon_tp_id
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_weapon_id (void) const
{_
    if (monstp) {
        // con("get weapon %" PRIx32 "", monstp->weapon_id);
        return (monstp->weapon_id);
    } else {
        // con("get weapon id => none");
        return (0);
    }
}

ThingId Thing::set_weapon_id (ThingId v)
{_
    new_monst();
    // con("set weapon %" PRIx32 "", v);
    return (monstp->weapon_id = v);
}

////////////////////////////////////////////////////////////////////////////
// on_fire_id_anim
////////////////////////////////////////////////////////////////////////////
ThingId Thing::get_on_fire_anim_id (void) const
{_
    if (monstp) {
        return (monstp->on_fire_id_anim);
    } else {
        return (0);
    }
}

ThingId Thing::set_on_fire_anim_id (ThingId v)
{_
    new_monst();
//con("%s %" PRIx32 "", __FUNCTION__, v);
    return (monstp->on_fire_id_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// interpolated_mid_at
////////////////////////////////////////////////////////////////////////////
fpoint Thing::get_interpolated_mid_at (void) const
{_
    if (monstp) {
        return (monstp->interpolated_mid_at);
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

const std::string& Thing::str1 (void) const {_ return (tp()->str1()); }
const std::string& Thing::str2 (void) const {_ return (tp()->str2()); }
const std::string& Thing::str3 (void) const {_ return (tp()->str3()); }
const std::string& Thing::str4 (void) const {_ return (tp()->str4()); }
const std::string& Thing::str5 (void) const {_ return (tp()->str5()); }
const std::string& Thing::str6 (void) const {_ return (tp()->str6()); }
const std::string& Thing::str7 (void) const {_ return (tp()->str7()); }
const std::string& Thing::str8 (void) const {_ return (tp()->str8()); }
const std::string& Thing::str9 (void) const {_ return (tp()->str9()); }
const std::string& Thing::str10 (void) const {_ return (tp()->str10()); }
const std::string& Thing::str11 (void) const {_ return (tp()->str11()); }
const std::string& Thing::str12 (void) const {_ return (tp()->str12()); }
const std::string& Thing::text_hits (void) const {_ return (tp()->text_hits()); }
const std::string& Thing::spawn_on_death (void) const {_ return (tp()->spawn_on_death()); }
const std::string& Thing::text_name (void) const {_ return (tp()->text_name()); }
const std::string& Thing::light_color (void) const {_ return (tp()->light_color()); }
const std::string& Thing::weapon_carry_anim (void) const {_ return (tp()->weapon_carry_anim()); }
const std::string& Thing::weapon_use_anim (void) const {_ return (tp()->weapon_use_anim()); }
