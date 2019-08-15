//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include "my_game.h"
#include "my_color.h"
#include "my_dmap.h"
#include <list>

int Thing::ai_delay_after_moving_ms(void)                     
{ 
    return (tp_ai_delay_after_moving_ms(tp));
}

int Thing::ai_scent_distance(void)                            
{ 
    return (tp_ai_scent_distance(tp));
}

int Thing::bite_damage(void)                                  
{ 
    return (tp->bite_damage());
}

int Thing::collision_attack(void)                             
{ 
    return (tp_collision_attack(tp));
}

int Thing::collision_box(void)                                
{ 
    return (tp_collision_box(tp));
}

int Thing::collision_check(void)                              
{ 
    return (tp_collision_check(tp));
}

int Thing::collision_circle(void)                             
{ 
    return (tp_collision_circle(tp));
}

int Thing::collision_hit_priority(void)                       
{ 
    return (tp_collision_hit_priority(tp));
}

int Thing::does_nothing(void)                                 
{ 
    return (tp_does_nothing(tp));
}

int Thing::gfx_animated(void)                                 
{ 
    return (tp_gfx_animated(tp));
}

int Thing::gfx_animated_can_vflip(void)                       
{ 
    return (tp_gfx_animated_can_vflip(tp));
}

int Thing::gfx_animated_no_dir(void)                          
{ 
    return (tp_gfx_animated_no_dir(tp));
}

int Thing::gfx_bounce_on_move(void)                           
{ 
    return (tp_gfx_bounce_on_move(tp));
}

int Thing::gfx_can_hflip(void)                                
{ 
    return (tp_gfx_can_hflip(tp));
}

int Thing::gfx_is_an_animation_only(void)                     
{ 
    return (tp_gfx_is_an_animation_only(tp));
}

int Thing::gfx_is_floor_deco(void)                            
{ 
    return (tp_gfx_is_floor_deco(tp));
}

int Thing::gfx_is_wall_deco(void)                             
{ 
    return (tp_gfx_is_wall_deco(tp));
}

int Thing::gfx_is_weapon_carry_anim(void)                     
{ 
    return (tp_gfx_is_weapon_carry_anim(tp));
}

int Thing::gfx_is_weapon_use_anim(void)                       
{ 
    return (tp_gfx_is_weapon_use_anim(tp));
}

int Thing::gfx_large_shadow_caster(void)                      
{ 
    return (tp_gfx_large_shadow_caster(tp));
}

int Thing::gfx_outlined(void)                                 
{ 
    return (tp_gfx_outlined(tp));
}

int Thing::gfx_oversized_but_sitting_on_the_ground(void)      
{ 
    return (tp_gfx_oversized_but_sitting_on_the_ground(tp));
}

int Thing::gfx_small_shadow_caster(void)                      
{ 
    return (tp_gfx_small_shadow_caster(tp));
}

int Thing::hunger_at_health_pct(void)                         
{ 
    return (tp_hunger_at_health_pct(tp));
}

int Thing::hunger_clock_freq_ms(void)                         
{ 
    return (tp_hunger_clock_freq_ms(tp));
}

int Thing::hunger_constant(void)                              
{ 
    return (tp_hunger_constant(tp));
}

int Thing::hunger_initial_health_at(void)                     
{ 
    return (tp_hunger_initial_health_at(tp));
}

int Thing::hunger_starving_at_health_pct(void)                
{ 
    return (tp_hunger_starving_at_health_pct(tp));
}

int Thing::is_active(void)                                    
{ 
    return (tp_is_active(tp));
}

int Thing::is_attackable(void)                                
{ 
    return (tp_is_attackable(tp));
}

int Thing::is_bleeder(void)                                   
{ 
    return (tp_is_bleeder(tp));
}

int Thing::is_blood(void)                                     
{ 
    return (tp_is_blood(tp));
}

int Thing::is_combustable(void)                               
{ 
    return (tp_is_combustable(tp));
}

int Thing::is_corpse_on_death(void)                           
{ 
    return (tp_is_corpse_on_death(tp));
}

int Thing::is_corridor(void)                                  
{ 
    return (tp_is_corridor(tp));
}

int Thing::is_deep_water(void)                                
{ 
    return (tp_is_deep_water(tp));
}

int Thing::is_dirt(void)                                      
{ 
    return (tp_is_dirt(tp));
}

int Thing::is_door(void)                                      
{ 
    return (tp_is_door(tp));
}

int Thing::is_entrance(void)                                  
{ 
    return (tp_is_entrance(tp));
}

int Thing::is_exit(void)                                      
{ 
    return (tp_is_exit(tp));
}

int Thing::is_explosion(void)                                 
{ 
    return (tp_is_explosion(tp));
}

int Thing::is_floor(void)                                     
{ 
    return (tp_is_floor(tp));
}

int Thing::is_food(void)                                      
{ 
    return (tp_is_food(tp));
}

int Thing::is_grass(void)                                     
{ 
    return (tp_is_grass(tp));
}

int Thing::is_gravel(void)                                    
{ 
    return (tp_is_gravel(tp));
}

int Thing::is_key(void)                                       
{ 
    return (tp_is_key(tp));
}

int Thing::is_lava(void)                                      
{ 
    return (tp_is_lava(tp));
}

int Thing::is_light_strength(void)                            
{ 
    return (tp_is_light_strength(tp));
}

int Thing::is_made_of_meat(void)                              
{ 
    return (tp_is_made_of_meat(tp));
}

int Thing::is_meat_eater(void)                                
{ 
    return (tp_is_meat_eater(tp));
}

int Thing::is_monst(void)                                     
{ 
    return (tp_is_monst(tp));
}

int Thing::is_movable(void)                                   
{ 
    return (tp_is_movable(tp));
}

int Thing::is_movement_blocking(void)                         
{ 
    return (tp_is_movement_blocking(tp));
}

int Thing::is_obstacle(void)                                  
{ 
    return (tp_is_obstacle(tp));
}

int Thing::is_player(void)                                    
{ 
    return (tp_is_player(tp));
}

int Thing::is_projectile(void)                                
{ 
    return (tp_is_projectile(tp));
}

int Thing::is_ripple(void)                                    
{ 
    return (tp_is_ripple(tp));
}

int Thing::is_rock(void)                                      
{ 
    return (tp_is_rock(tp));
}

int Thing::is_rrr1(void)                                      
{ 
    return (tp_is_rrr1(tp));
}

int Thing::is_rrr10(void)                                     
{ 
    return (tp_is_rrr10(tp));
}

int Thing::is_rrr11(void)                                     
{ 
    return (tp_is_rrr11(tp));
}

int Thing::is_rrr12(void)                                     
{ 
    return (tp_is_rrr12(tp));
}

int Thing::is_rrr13(void)                                     
{ 
    return (tp_is_rrr13(tp));
}

int Thing::is_rrr14(void)                                     
{ 
    return (tp_is_rrr14(tp));
}

int Thing::is_rrr15(void)                                     
{ 
    return (tp_is_rrr15(tp));
}

int Thing::is_rrr16(void)                                     
{ 
    return (tp_is_rrr16(tp));
}

int Thing::is_rrr17(void)                                     
{ 
    return (tp_is_rrr17(tp));
}

int Thing::is_rrr18(void)                                     
{ 
    return (tp_is_rrr18(tp));
}

int Thing::is_rrr19(void)                                     
{ 
    return (tp_is_rrr19(tp));
}

int Thing::is_rrr2(void)                                      
{ 
    return (tp_is_rrr2(tp));
}

int Thing::is_rrr20(void)                                     
{ 
    return (tp_is_rrr20(tp));
}

int Thing::is_rrr21(void)                                     
{ 
    return (tp_is_rrr21(tp));
}

int Thing::is_rrr22(void)                                     
{ 
    return (tp_is_rrr22(tp));
}

int Thing::is_rrr23(void)                                     
{ 
    return (tp_is_rrr23(tp));
}

int Thing::is_rrr24(void)                                     
{ 
    return (tp_is_rrr24(tp));
}

int Thing::is_rrr25(void)                                     
{ 
    return (tp_is_rrr25(tp));
}

int Thing::is_rrr26(void)                                     
{ 
    return (tp_is_rrr26(tp));
}

int Thing::is_rrr27(void)                                     
{ 
    return (tp_is_rrr27(tp));
}

int Thing::is_rrr28(void)                                     
{ 
    return (tp_is_rrr28(tp));
}

int Thing::is_rrr29(void)                                     
{ 
    return (tp_is_rrr29(tp));
}

int Thing::is_rrr3(void)                                      
{ 
    return (tp_is_rrr3(tp));
}

int Thing::is_rrr30(void)                                     
{ 
    return (tp_is_rrr30(tp));
}

int Thing::is_rrr31(void)                                     
{ 
    return (tp_is_rrr31(tp));
}

int Thing::is_rrr32(void)                                     
{ 
    return (tp_is_rrr32(tp));
}

int Thing::is_rrr33(void)                                     
{ 
    return (tp_is_rrr33(tp));
}

int Thing::is_rrr34(void)                                     
{ 
    return (tp_is_rrr34(tp));
}

int Thing::is_rrr35(void)                                     
{ 
    return (tp_is_rrr35(tp));
}

int Thing::is_rrr36(void)                                     
{ 
    return (tp_is_rrr36(tp));
}

int Thing::is_rrr37(void)                                     
{ 
    return (tp_is_rrr37(tp));
}

int Thing::is_rrr38(void)                                     
{ 
    return (tp_is_rrr38(tp));
}

int Thing::is_rrr39(void)                                     
{ 
    return (tp_is_rrr39(tp));
}

int Thing::is_rrr4(void)                                      
{ 
    return (tp_is_rrr4(tp));
}

int Thing::is_rrr40(void)                                     
{ 
    return (tp_is_rrr40(tp));
}

int Thing::is_rrr41(void)                                     
{ 
    return (tp_is_rrr41(tp));
}

int Thing::is_rrr42(void)                                     
{ 
    return (tp_is_rrr42(tp));
}

int Thing::is_rrr43(void)                                     
{ 
    return (tp_is_rrr43(tp));
}

int Thing::is_rrr44(void)                                     
{ 
    return (tp_is_rrr44(tp));
}

int Thing::is_rrr45(void)                                     
{ 
    return (tp_is_rrr45(tp));
}

int Thing::is_rrr46(void)                                     
{ 
    return (tp_is_rrr46(tp));
}

int Thing::is_rrr47(void)                                     
{ 
    return (tp_is_rrr47(tp));
}

int Thing::is_rrr48(void)                                     
{ 
    return (tp_is_rrr48(tp));
}

int Thing::is_rrr49(void)                                     
{ 
    return (tp_is_rrr49(tp));
}

int Thing::is_rrr5(void)                                      
{ 
    return (tp_is_rrr5(tp));
}

int Thing::is_rrr50(void)                                     
{ 
    return (tp_is_rrr50(tp));
}

int Thing::is_rrr6(void)                                      
{ 
    return (tp_is_rrr6(tp));
}

int Thing::is_rrr7(void)                                      
{ 
    return (tp_is_rrr7(tp));
}

int Thing::is_rrr8(void)                                      
{ 
    return (tp_is_rrr8(tp));
}

int Thing::is_rrr9(void)                                      
{ 
    return (tp_is_rrr9(tp));
}

int Thing::is_snow(void)                                      
{ 
    return (tp_is_snow(tp));
}

int Thing::is_soil(void)                                      
{ 
    return (tp_is_soil(tp));
}

int Thing::is_undead(void)                                    
{ 
    return (tp_is_undead(tp));
}

int Thing::is_wall(void)                                      
{ 
    return (tp_is_wall(tp));
}

int Thing::is_water(void)                                     
{ 
    return (tp_is_water(tp));
}

int Thing::is_water_dweller(void)                             
{ 
    return (tp_is_water_dweller(tp));
}

int Thing::is_water_hater(void)                               
{ 
    return (tp_is_water_hater(tp));
}

int Thing::is_weapon(void)                                    
{ 
    return (tp_is_weapon(tp));
}

int Thing::weapon_damage(void)                                
{ 
    return (tp_weapon_damage(tp));
}

int Thing::weapon_use_delay_hundredths(void)                  
{ 
    return (tp_weapon_use_delay_hundredths(tp));
}

int Thing::weapon_use_distance(void)                          
{ 
    return (tp_weapon_use_distance(tp));
}

int Thing::z_depth(void)                                      
{ 
    return (tp_z_depth(tp));
}

std::string Thing::bite_damage_hd(void)                       
{ 
    return (tp_bite_damage_hd(tp));
}

std::string Thing::is_nutrition_hd(void)                      
{ 
    return (tp_is_nutrition_hd(tp));
}

int Thing::is_nutrition(void)                      
{ 
    { return (tp->is_nutrition()); }
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
    monst->bounce_count = v;
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
    monst->rot = v;
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
    return (monst->gold = v);
}

int Thing::decr_gold (int v)
{
    new_monst();
    return (monst->gold -= v);
}

int Thing::incr_gold (int v)
{
    new_monst();
    return (monst->gold += v);
}

int Thing::decr_gold (void)
{
    new_monst();
    return (monst->gold--);
}

int Thing::incr_gold (void)
{
    new_monst();
    return (monst->gold++);
}

////////////////////////////////////////////////////////////////////////////
// health
////////////////////////////////////////////////////////////////////////////
int Thing::get_health (void)
{
    if (monst) { 
        return (monst->health);
    } else {
        return (0);
    }
}

int Thing::set_health (int v)
{
    new_monst();
    return (monst->health = v);
}

int Thing::decr_health (int v)
{
    new_monst();
    return (monst->health -= v);
}

int Thing::incr_health (int v)
{
    new_monst();
    return (monst->health += v);
}

int Thing::decr_health (void)
{
    new_monst();
    return (monst->health--);
}

int Thing::incr_health (void)
{
    new_monst();
    return (monst->health++);
}

////////////////////////////////////////////////////////////////////////////
// health_max
////////////////////////////////////////////////////////////////////////////
int Thing::get_health_max (void)
{
    if (monst) { 
        return (monst->health_max);
    } else {
        return (0);
    }
}

int Thing::set_health_max (int v)
{
    new_monst();
    return (monst->health_max = v);
}

int Thing::decr_health_max (int v)
{
    new_monst();
    return (monst->health_max -= v);
}

int Thing::incr_health_max (int v)
{
    new_monst();
    return (monst->health_max += v);
}

int Thing::decr_health_max (void)
{
    new_monst();
    return (monst->health_max--);
}

int Thing::incr_health_max (void)
{
    new_monst();
    return (monst->health_max++);
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
    return (monst->owned_count = v);
}

int Thing::decr_owned_count (int v)
{
    new_monst();
    return (monst->owned_count -= v);
}

int Thing::incr_owned_count (int v)
{
    new_monst();
    return (monst->owned_count += v);
}

int Thing::decr_owned_count (void)
{
    new_monst();
    return (monst->owned_count--);
}

int Thing::incr_owned_count (void)
{
    new_monst();
    return (monst->owned_count++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_bounce_begin
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_bounce_begin (void)
{
    if (monst) { 
        return (monst->timestamp_bounce_begin);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_bounce_begin (uint32_t v)
{
    new_monst();
    return (monst->timestamp_bounce_begin = v);
}

uint32_t Thing::decr_timestamp_bounce_begin (uint32_t v)
{
    new_monst();
    return (monst->timestamp_bounce_begin -= v);
}

uint32_t Thing::incr_timestamp_bounce_begin (uint32_t v)
{
    new_monst();
    return (monst->timestamp_bounce_begin += v);
}

uint32_t Thing::decr_timestamp_bounce_begin (void)
{
    new_monst();
    return (monst->timestamp_bounce_begin--);
}

uint32_t Thing::incr_timestamp_bounce_begin (void)
{
    new_monst();
    return (monst->timestamp_bounce_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_bounce_end
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_bounce_end (void)
{
    if (monst) { 
        return (monst->timestamp_bounce_end);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_bounce_end (uint32_t v)
{
    new_monst();
    return (monst->timestamp_bounce_end = v);
}

uint32_t Thing::decr_timestamp_bounce_end (uint32_t v)
{
    new_monst();
    return (monst->timestamp_bounce_end -= v);
}

uint32_t Thing::incr_timestamp_bounce_end (uint32_t v)
{
    new_monst();
    return (monst->timestamp_bounce_end += v);
}

uint32_t Thing::decr_timestamp_bounce_end (void)
{
    new_monst();
    return (monst->timestamp_bounce_end--);
}

uint32_t Thing::incr_timestamp_bounce_end (void)
{
    new_monst();
    return (monst->timestamp_bounce_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_last_i_was_hit
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_last_i_was_hit (void)
{
    if (monst) { 
        return (monst->timestamp_last_i_was_hit);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_last_i_was_hit (uint32_t v)
{
    new_monst();
    return (monst->timestamp_last_i_was_hit = v);
}

uint32_t Thing::decr_timestamp_last_i_was_hit (uint32_t v)
{
    new_monst();
    return (monst->timestamp_last_i_was_hit -= v);
}

uint32_t Thing::incr_timestamp_last_i_was_hit (uint32_t v)
{
    new_monst();
    return (monst->timestamp_last_i_was_hit += v);
}

uint32_t Thing::decr_timestamp_last_i_was_hit (void)
{
    new_monst();
    return (monst->timestamp_last_i_was_hit--);
}

uint32_t Thing::incr_timestamp_last_i_was_hit (void)
{
    new_monst();
    return (monst->timestamp_last_i_was_hit++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_flip_start
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_flip_start (void)
{
    if (monst) { 
        return (monst->timestamp_flip_start);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_flip_start (uint32_t v)
{
    new_monst();
    return (monst->timestamp_flip_start = v);
}

uint32_t Thing::decr_timestamp_flip_start (uint32_t v)
{
    new_monst();
    return (monst->timestamp_flip_start -= v);
}

uint32_t Thing::incr_timestamp_flip_start (uint32_t v)
{
    new_monst();
    return (monst->timestamp_flip_start += v);
}

uint32_t Thing::decr_timestamp_flip_start (void)
{
    new_monst();
    return (monst->timestamp_flip_start--);
}

uint32_t Thing::incr_timestamp_flip_start (void)
{
    new_monst();
    return (monst->timestamp_flip_start++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_move_start
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_move_begin (void)
{
    if (monst) { 
        return (monst->timestamp_move_begin);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_move_begin (uint32_t v)
{
    new_monst();
    return (monst->timestamp_move_begin = v);
}

uint32_t Thing::decr_timestamp_move_begin (uint32_t v)
{
    new_monst();
    return (monst->timestamp_move_begin -= v);
}

uint32_t Thing::incr_timestamp_move_begin (uint32_t v)
{
    new_monst();
    return (monst->timestamp_move_begin += v);
}

uint32_t Thing::decr_timestamp_move_begin (void)
{
    new_monst();
    return (monst->timestamp_move_begin--);
}

uint32_t Thing::incr_timestamp_move_begin (void)
{
    new_monst();
    return (monst->timestamp_move_begin++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_move_end
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_move_end (void)
{
    if (monst) { 
        return (monst->timestamp_move_end);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_move_end (uint32_t v)
{
    new_monst();
    return (monst->timestamp_move_end = v);
}

uint32_t Thing::decr_timestamp_move_end (uint32_t v)
{
    new_monst();
    return (monst->timestamp_move_end -= v);
}

uint32_t Thing::incr_timestamp_move_end (uint32_t v)
{
    new_monst();
    return (monst->timestamp_move_end += v);
}

uint32_t Thing::decr_timestamp_move_end (void)
{
    new_monst();
    return (monst->timestamp_move_end--);
}

uint32_t Thing::incr_timestamp_move_end (void)
{
    new_monst();
    return (monst->timestamp_move_end++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_born
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_born (void)
{
    if (monst) { 
        return (monst->timestamp_born);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_born (uint32_t v)
{
    new_monst();
    return (monst->timestamp_born = v);
}

uint32_t Thing::decr_timestamp_born (uint32_t v)
{
    new_monst();
    return (monst->timestamp_born -= v);
}

uint32_t Thing::incr_timestamp_born (uint32_t v)
{
    new_monst();
    return (monst->timestamp_born += v);
}

uint32_t Thing::decr_timestamp_born (void)
{
    new_monst();
    return (monst->timestamp_born--);
}

uint32_t Thing::incr_timestamp_born (void)
{
    new_monst();
    return (monst->timestamp_born++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_hunger_tick
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_hunger_tick (void)
{
    if (monst) { 
        return (monst->timestamp_hunger_tick);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_hunger_tick (uint32_t v)
{
    new_monst();
    return (monst->timestamp_hunger_tick = v);
}

uint32_t Thing::decr_timestamp_hunger_tick (uint32_t v)
{
    new_monst();
    return (monst->timestamp_hunger_tick -= v);
}

uint32_t Thing::incr_timestamp_hunger_tick (uint32_t v)
{
    new_monst();
    return (monst->timestamp_hunger_tick += v);
}

uint32_t Thing::decr_timestamp_hunger_tick (void)
{
    new_monst();
    return (monst->timestamp_hunger_tick--);
}

uint32_t Thing::incr_timestamp_hunger_tick (void)
{
    new_monst();
    return (monst->timestamp_hunger_tick++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_ai_next
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_ai_next (void)
{
    if (monst) { 
        return (monst->timestamp_ai_next);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_ai_next (uint32_t v)
{
    new_monst();
    return (monst->timestamp_ai_next = v);
}

uint32_t Thing::decr_timestamp_ai_next (uint32_t v)
{
    new_monst();
    return (monst->timestamp_ai_next -= v);
}

uint32_t Thing::incr_timestamp_ai_next (uint32_t v)
{
    new_monst();
    return (monst->timestamp_ai_next += v);
}

uint32_t Thing::decr_timestamp_ai_next (void)
{
    new_monst();
    return (monst->timestamp_ai_next--);
}

uint32_t Thing::incr_timestamp_ai_next (void)
{
    new_monst();
    return (monst->timestamp_ai_next++);
}

////////////////////////////////////////////////////////////////////////////
// timestamp_collision
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_timestamp_collision (void)
{
    if (monst) { 
        return (monst->timestamp_collision);
    } else {
        return (0);
    }
}

uint32_t Thing::set_timestamp_collision (uint32_t v)
{
    new_monst();
    return (monst->timestamp_collision = v);
}

uint32_t Thing::decr_timestamp_collision (uint32_t v)
{
    new_monst();
    return (monst->timestamp_collision -= v);
}

uint32_t Thing::incr_timestamp_collision (uint32_t v)
{
    new_monst();
    return (monst->timestamp_collision += v);
}

uint32_t Thing::decr_timestamp_collision (void)
{
    new_monst();
    return (monst->timestamp_collision--);
}

uint32_t Thing::incr_timestamp_collision (void)
{
    new_monst();
    return (monst->timestamp_collision++);
}

////////////////////////////////////////////////////////////////////////////
// id_owner
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_id_owner (void)
{
    if (monst) { 
        return (monst->id_owner);
    } else {
        return (0);
    }
}

uint32_t Thing::set_id_owner (uint32_t v)
{
    new_monst();
    return (monst->id_owner = v);
}

////////////////////////////////////////////////////////////////////////////
// id_weapon_carry_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_id_weapon_carry_anim (void)
{
    if (monst) { 
        return (monst->id_weapon_carry_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_id_weapon_carry_anim (uint32_t v)
{
    new_monst();
    return (monst->id_weapon_carry_anim = v);
}

////////////////////////////////////////////////////////////////////////////
// id_weapon_use_anim
////////////////////////////////////////////////////////////////////////////
uint32_t Thing::get_id_weapon_use_anim (void)
{
    if (monst) { 
        return (monst->id_weapon_use_anim);
    } else {
        return (0);
    }
}

uint32_t Thing::set_id_weapon_use_anim (uint32_t v)
{
    new_monst();
    return (monst->id_weapon_use_anim = v);
}
