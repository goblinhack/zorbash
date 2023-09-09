//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_globals_extra.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_thing.hpp"

//
// Dice
//

const Dice &Thing::spawn_group_size_dice(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_size_dice());
}

const std::string &Thing::spawn_group_size_dice_str(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_size_dice_str());
}

int Thing::spawn_group_size(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_size_dice().roll());
}

float Thing::distance_avoid_get(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_avoid());
}

int Thing::ai_resent_count(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_resent_count());
}

int Thing::is_obs_ai(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_ai());
}

int Thing::chance_d1000_shove(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_shove());
}

int Thing::chance_d10000_runic(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d10000_runic());
}

int Thing::chance_d1000_grapple(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_grapple());
}

int Thing::unused_chance1_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance1_d1000());
}

int Thing::unused_chance2_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance2_d1000());
}

int Thing::unused_chance3_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance3_d1000());
}

int Thing::unused_chance4_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance4_d1000());
}

int Thing::unused_chance5_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance5_d1000());
}

int Thing::unused_chance6_d1000(void)
{
  TRACE_NO_INDENT();
  return (tp()->unused_chance6_d1000());
}

int Thing::chance_d1000_melting(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_melting());
}

int Thing::chance_d10000_damaged(void)
{
  TRACE_NO_INDENT();

  int chance = tp()->chance_d10000_damaged();
  int e      = enchant_count_get();
  while (e-- > 0) {
    chance /= 2;
  }

  return chance;
}

int Thing::chance_d10000_crit(void)
{
  TRACE_NO_INDENT();

  int chance = tp()->chance_d10000_crit();
  int e      = enchant_count_get();
  while (e-- > 0) {
    chance *= 2;
  }

  return chance;
}

int Thing::is_able_to_shove(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_shove());
}

int Thing::is_able_to_grapple(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_grapple());
}

int Thing::effect_radius(void)
{
  TRACE_NO_INDENT();

  int radius = tp()->effect_radius();
  if (tp()->effect_has_blast_radius()) {
    radius += enchant_count_get();
  }
  return radius;
}

int Thing::blast_min_radius(void)
{
  TRACE_NO_INDENT();
  return (tp()->blast_min_radius());
}

int Thing::collision_hit_priority(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_priority());
}

int Thing::collision_check(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_check());
}

int Thing::gfx_ascii_shown(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_shown());
}

int Thing::gfx_pixelart_animated_can_hflip(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_animated_can_hflip());
}

int Thing::gfx_pixelart_animated_can_vflip(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_animated_can_vflip());
}

int Thing::gfx_pixelart_animated_no_dir(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_animated_no_dir());
}

int Thing::gfx_pixelart_attack_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_attack_anim());
}

int Thing::is_unused_flag1(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag1());
}
int Thing::is_unused_flag2(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag2());
}
int Thing::is_unused_flag3(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag3());
}
int Thing::is_unused_flag4(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag4());
}
int Thing::is_unused_flag5(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag5());
}
int Thing::is_unused_flag6(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag6());
}
int Thing::is_unused_flag7(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag7());
}
int Thing::is_unused_flag8(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag8());
}
int Thing::is_unused_flag9(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag9());
}
int Thing::is_unused_flag10(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag10());
}
int Thing::is_unused_flag11(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag11());
}
int Thing::is_unused_flag12(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag12());
}
int Thing::is_unused_flag13(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag13());
}
int Thing::is_unused_flag14(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag14());
}
int Thing::is_unused_flag15(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag15());
}
int Thing::is_unused_flag16(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag16());
}
int Thing::is_unused_flag17(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag17());
}
int Thing::is_unused_flag18(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag18());
}
int Thing::is_unused_flag19(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag19());
}
int Thing::is_unused_flag20(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag20());
}
int Thing::is_unused_flag21(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag21());
}
int Thing::is_unused_flag22(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag22());
}
int Thing::is_unused_flag23(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag23());
}
int Thing::is_unused_flag24(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag24());
}
int Thing::is_unused_flag25(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag25());
}
int Thing::is_unused_flag26(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag26());
}
int Thing::is_unused_flag27(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag27());
}
int Thing::is_unused_flag28(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag28());
}
int Thing::is_unused_flag29(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag29());
}
int Thing::is_unused_flag30(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag30());
}
int Thing::is_unused_flag31(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag31());
}
int Thing::is_unused_flag32(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag32());
}
int Thing::is_unused_flag33(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag33());
}
int Thing::is_unused_flag34(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag34());
}
int Thing::is_unused_flag35(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag35());
}
int Thing::is_unused_flag36(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag36());
}
int Thing::is_unused_flag37(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag37());
}
int Thing::is_unused_flag38(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag38());
}
int Thing::is_unused_flag39(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag39());
}
int Thing::is_unused_flag40(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag40());
}
int Thing::is_unused_flag41(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag41());
}
int Thing::is_unused_flag42(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag42());
}
int Thing::is_unused_flag43(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag43());
}
int Thing::is_unused_flag44(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag44());
}
int Thing::is_unused_flag45(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag45());
}
int Thing::is_unused_flag46(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag46());
}
int Thing::is_unused_flag47(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag47());
}
int Thing::is_unused_flag48(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag48());
}
int Thing::is_unused_flag49(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag49());
}
int Thing::is_unused_flag50(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag50());
}
int Thing::is_unused_flag51(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag51());
}
int Thing::is_unused_flag52(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag52());
}
int Thing::is_unused_flag53(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag53());
}
int Thing::is_unused_flag54(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag54());
}
int Thing::is_unused_flag55(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag55());
}
int Thing::is_unused_flag56(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag56());
}
int Thing::is_unused_flag57(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag57());
}
int Thing::is_unused_flag58(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag58());
}
int Thing::is_unused_flag59(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag59());
}
int Thing::is_unused_flag60(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag60());
}
int Thing::is_unused_flag61(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag61());
}
int Thing::is_unused_flag62(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag62());
}
int Thing::is_unused_flag63(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag63());
}
int Thing::is_unused_flag64(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag64());
}
int Thing::is_unused_flag65(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag65());
}
int Thing::is_unused_flag66(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag66());
}
int Thing::is_unused_flag67(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag67());
}
int Thing::is_unused_flag68(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag68());
}
int Thing::is_unused_flag69(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag69());
}
int Thing::is_unused_flag70(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag70());
}
int Thing::is_unused_flag71(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag71());
}
int Thing::is_unused_flag72(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag72());
}
int Thing::is_unused_flag73(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag73());
}
int Thing::is_unused_flag74(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag74());
}
int Thing::is_unused_flag75(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag75());
}
int Thing::is_unused_flag76(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag76());
}
int Thing::is_unused_flag77(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag77());
}
int Thing::is_unused_flag78(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag78());
}
int Thing::is_unused_flag79(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag79());
}
int Thing::is_unused_flag80(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag80());
}
int Thing::is_unused_flag81(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag81());
}
int Thing::is_unused_flag82(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag82());
}
int Thing::is_unused_flag83(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag83());
}
int Thing::is_unused_flag84(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag84());
}
int Thing::is_unused_flag85(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag85());
}
int Thing::is_unused_flag86(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag86());
}
int Thing::is_unused_flag87(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag87());
}
int Thing::is_able_to_see_in_magical_darkness(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_see_in_magical_darkness());
}
int Thing::is_shootable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shootable());
}
int Thing::is_able_to_have_a_runic_inscribed(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_have_a_runic_inscribed());
}
int Thing::is_runic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_runic());
}
int Thing::is_tentacleye(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tentacleye());
}
int Thing::is_mace(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mace());
}
int Thing::is_warhammer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_warhammer());
}
int Thing::is_spell_of_repulsion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spell_of_repulsion());
}
int Thing::is_immune_to_spell_of_repulsion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_spell_of_repulsion());
}
int Thing::is_immune_to_spell_of_beckoning(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_spell_of_beckoning());
}
int Thing::is_animation(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_animation());
}
int Thing::temperature_never_changes(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_never_changes());
}
int Thing::is_gas_explosion_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gas_explosion_blocker());
}
int Thing::is_able_to_break_out_of_spell_of_holding(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_spell_of_holding());
}
int Thing::is_spell_of_holding_barrier(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spell_of_holding_barrier());
}
int Thing::is_able_to_attack_totems(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_attack_totems());
}
int Thing::is_able_to_spell_cast(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_spell_cast());
}
int Thing::is_spell_of_holding(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spell_of_holding());
}
int Thing::is_spell_of_slowing(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spell_of_slowing());
}
int Thing::is_immune_to_spell_of_slowing(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_spell_of_slowing());
}
int Thing::is_immune_to_spell_of_holding(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_spell_of_holding());
}
int Thing::is_obs_spell_casting(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_spell_casting());
}
int Thing::is_zorblin(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_zorblin());
}
int Thing::is_turret(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_turret());
}
int Thing::is_totem(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_totem());
}
int Thing::is_crystal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_crystal());
}
int Thing::is_grass_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass_dead());
}
int Thing::is_grass_trampled(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_grass_trampled());
}
int Thing::is_immune_to_paralysis(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_immune_to_paralysis());
}
int Thing::is_holy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_holy());
}
int Thing::is_holy_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_holy_water());
}
int Thing::is_four_leaf_clover(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_four_leaf_clover());
}
int Thing::is_skeleton(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_skeleton());
}
int Thing::is_pointy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pointy());
}
int Thing::is_described_in_leftbar(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_described_in_leftbar());
}
int Thing::is_always_activated(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_always_activated());
}
int Thing::is_mummy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mummy());
}
int Thing::is_spell_of_beckoning(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spell_of_beckoning());
}
int Thing::is_kept_after_final_use(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_kept_after_final_use());
}
int Thing::is_duck(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_duck());
}
int Thing::spell_cost(void)
{
  TRACE_NO_INDENT();
  return (tp()->spell_cost());
}
int Thing::is_player_bodypart(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart());
}
int Thing::is_player_bodypart_legs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart_legs());
}
int Thing::is_player_bodypart_torso(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart_torso());
}
int Thing::is_player_bodypart_hair(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart_hair());
}
int Thing::is_player_bodypart_eyes(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart_eyes());
}
int Thing::is_player_bodypart_face(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart_face());
}
int Thing::is_player_bodypart_hat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_player_bodypart_hat());
}
int Thing::is_only_one_per_tile(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_only_one_per_tile());
}
int Thing::is_unused_flag142(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag142());
}
int Thing::is_auto_activated(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_activated());
}
int Thing::is_magic_stone(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_magic_stone());
}
int Thing::is_biome_flooded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_flooded());
}
int Thing::is_obj_spawning(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obj_spawning());
}
int Thing::is_obj_spawning_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obj_spawning_monst());
}
int Thing::is_able_to_eat_rotting_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_eat_rotting_food());
}
int Thing::is_able_to_eat_poisonous_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_eat_poisonous_food());
}
int Thing::is_able_to_eat_unpleasant_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_eat_unpleasant_food());
}
int Thing::is_biome_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_ice());
}
int Thing::is_biome_chasms(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_chasms());
}
int Thing::is_biome_lava(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_lava());
}
int Thing::is_rock_lava(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rock_lava());
}
int Thing::is_rock_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rock_ice());
}
int Thing::is_yeti(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_yeti());
}
int Thing::is_mantisman(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mantisman());
}
int Thing::is_iceman(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_iceman());
}
int Thing::is_molekin(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_molekin());
}
int Thing::is_rat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rat());
}
int Thing::is_scorpion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_scorpion());
}
int Thing::is_leech(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_leech());
}
int Thing::is_bloodbug(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bloodbug());
}
int Thing::is_death_hornet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_death_hornet());
}
int Thing::is_fairy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fairy());
}
int Thing::is_bearowl(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bearowl());
}
int Thing::is_centipede(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_centipede());
}
int Thing::is_herbivore(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_herbivore());
}
int Thing::is_sheep(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sheep());
}
int Thing::is_crab(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_crab());
}
int Thing::is_able_to_be_equipped(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_be_equipped());
}
int Thing::is_ant(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ant());
}
int Thing::is_bee(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bee());
}
int Thing::attack_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->attack_blood());
}
int Thing::is_eater_of_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_blood());
}
int Thing::environ_likes_lava(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_likes_lava());
}
int Thing::is_splatter(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_splatter());
}
int Thing::is_unused_flag179(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag179());
}
int Thing::is_goat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_goat());
}
int Thing::is_pressure_plate(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pressure_plate());
}
int Thing::is_trap(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_trap());
}
int Thing::is_cold_elemental(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cold_elemental());
}
int Thing::is_fire_elemental(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fire_elemental());
}
int Thing::is_very_intelligent(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_intelligent());
}
int Thing::is_made_of_rock(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_made_of_rock());
}
int Thing::is_piranha(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_piranha());
}
int Thing::is_unused_flag192(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_unused_flag192());
}

int Thing::is_magical_effect(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_magical_effect());
}

int Thing::is_able_to_be_teleported(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_be_teleported());
}

int Thing::is_portal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_portal());
}
int Thing::is_able_to_run_away_after_stealing(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_run_away_after_stealing());
}

int Thing::gfx_pixelart_flickers(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_flickers());
}

int Thing::gfx_glows(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_glows());
}

int Thing::gfx_pixelart_health_bar_autohide(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_health_bar_autohide());
}

int Thing::gfx_pixelart_health_bar_shown(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_health_bar_shown());
}

int Thing::gfx_pixelart_shadow_long(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_long());
}

int Thing::gfx_on_fire_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_on_fire_anim());
}

int Thing::gfx_pixelart_oversized_and_on_floor(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_oversized_and_on_floor());
}

int Thing::gfx_pixelart_shadow_short(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_short());
}

int Thing::gfx_pixelart_shown_in_bg(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shown_in_bg());
}

int Thing::gfx_pixelart_show_outlined(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_show_outlined());
}

int Thing::gfx_pixelart_shadow_solid(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_solid());
}

int Thing::gfx_pixelart_shadow_very_short(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow_very_short());
}

int Thing::gfx_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_water());
}

int Thing::gfx_pixelart_equip_carry_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_equip_carry_anim());
}

int Thing::environ_dislikes_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_dislikes_acid());
}

int Thing::environ_dislikes_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_dislikes_fire());
}

int Thing::environ_dislikes_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_dislikes_cold());
}

int Thing::environ_dislikes_poison(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_dislikes_poison());
}

int Thing::environ_dislikes_necrosis(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_dislikes_necrosis());
}

int Thing::environ_dislikes_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_dislikes_water());
}

int Thing::environ_hates_acid(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_hates_acid());
}

int Thing::environ_hates_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_hates_fire());
}

int Thing::environ_hates_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_hates_cold());
}

int Thing::environ_hates_poison(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_hates_poison());
}

int Thing::environ_hates_necrosis(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_hates_necrosis());
}

int Thing::environ_hates_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_hates_water());
}

int Thing::is_able_to_change_levels(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_change_levels());
}

int Thing::is_able_to_fall(void)
{
  TRACE_NO_INDENT();

  //
  // Dead bats fall...
  //
  if (is_dead) {
    if (is_corpse_on_death()) {
      return true;
    }
  }

  return (tp()->is_able_to_fall());
}

int Thing::is_able_to_see_through_doors(void)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_see_through_doors()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_see_through_doors());
}

int Thing::is_able_to_walk_through_walls(void)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_walk_through_walls()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_walk_through_walls());
}

int Thing::is_alive_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst() && ! is_dead);
}

int Thing::is_alive_on_end_of_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_alive_on_end_of_anim());
}

int Thing::is_always_hit(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_always_hit());
}

int Thing::is_ascend_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ascend_dungeon());
}

int Thing::is_ascend_sewer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ascend_sewer());
}

int Thing::is_auto_collect_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_collect_item());
}

int Thing::is_bag_item_container(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag_item_container());
}

int Thing::is_bag_item_not_stackable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag_item_not_stackable());
}

int Thing::is_bag_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag_item());
}

int Thing::is_bag(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bag());
}

int Thing::is_barrel(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_barrel());
}

int Thing::is_bleeder(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bleeder());
}

int Thing::is_red_splatter(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_splatter());
}

int Thing::is_red_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_blood());
}

int Thing::is_blood(void) { return is_red_blood() || is_green_blood(); }

int Thing::is_bones(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bones());
}

int Thing::is_brazier(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_brazier());
}

int Thing::is_bridge(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_bridge());
}

int Thing::is_burnable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_burnable());
}

int Thing::chance_d1000_carrier_of_treasure_class_A(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_carrier_of_treasure_class_A());
}

int Thing::chance_d1000_carrier_of_treasure_class_B(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_carrier_of_treasure_class_B());
}

int Thing::chance_d1000_carrier_of_treasure_class_C(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_carrier_of_treasure_class_C());
}

int Thing::chance_d1000_carrier_of_weapon_class_A(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_carrier_of_weapon_class_A());
}

int Thing::chance_d1000_carrier_of_weapon_class_B(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_carrier_of_weapon_class_B());
}

int Thing::chance_d1000_carrier_of_weapon_class_C(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_carrier_of_weapon_class_C());
}

int Thing::is_chasm(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_chasm());
}

int Thing::is_collectable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collectable());
}

int Thing::is_collected_as_keys(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_collected_as_keys());
}

int Thing::is_combustible(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_combustible());
}

int Thing::is_corpse_on_death(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_corpse_on_death());
}

int Thing::is_corpse(void)
{
  TRACE_NO_INDENT();
  return (is_dead && is_corpse_on_death());
}

int Thing::is_corridor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_corridor());
}

int Thing::is_critical_to_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_critical_to_level());
}

int Thing::is_cursor_can_hover_over_needs_confirm(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_can_hover_over_needs_confirm());
}

int Thing::is_cursor_can_hover_over(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_can_hover_over());
}

int Thing::is_cursor_path(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path());
}

int Thing::is_cursor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor());
}

int Thing::is_dead_on_end_of_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dead_on_end_of_anim());
}

int Thing::is_dead_on_shove(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dead_on_shove());
}

int Thing::is_dead_or_dying(void)
{
  TRACE_NO_INDENT();
  return is_dead || is_dying;
}

int Thing::is_dead_check(void)
{
  TRACE_NO_INDENT();
  return is_dead;
}

int Thing::is_frozen_check(void)
{
  TRACE_NO_INDENT();
  return is_frozen;
}

int Thing::is_burnt_check(void)
{
  TRACE_NO_INDENT();
  return is_burnt;
}

int Thing::is_debug_path(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_debug_path());
}

int Thing::is_debug_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_debug_type());
}

int Thing::is_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_deep_water());
}

int Thing::is_descend_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_descend_dungeon());
}

int Thing::is_descend_sewer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_descend_sewer());
}

int Thing::is_described_when_hovering_over(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_described_when_hovering_over());
}

int Thing::is_dirt(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dirt());
}

int Thing::is_door(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_door());
}

int Thing::is_droppable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_droppable());
}

int Thing::is_enchantable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_enchantable());
}

int Thing::is_enchantstone(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_enchantstone());
}

int Thing::is_ethereal_mob(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ethereal_mob());
}

int Thing::is_ethereal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ethereal());
}

int Thing::is_explosion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_explosion());
}

int Thing::is_cursor_path_hazard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path_hazard());
}

int Thing::is_cursor_path_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cursor_path_blocker());
}

int Thing::is_heavy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_heavy());
}

int Thing::is_fearless(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fearless());
}

int Thing::is_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_fire());
}

int Thing::is_floating(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_floating());
}

int Thing::is_floor_deco(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_floor_deco());
}

int Thing::is_floor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_floor());
}

int Thing::is_eater_of_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_food());
}

int Thing::is_food(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_food());
}

int Thing::is_hazard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_hazard());
}

int Thing::is_hittable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_hittable());
}

int Thing::is_humanoid(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_humanoid());
}

int Thing::is_very_hard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_hard());
}

int Thing::is_intelligent(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_intelligent());
}

int Thing::is_interesting(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_interesting());
}

int Thing::is_item_carrier(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_carrier());
}

int Thing::is_thief(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_thief());
}

int Thing::is_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item());
}

int Thing::is_eater_of_slime(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_slime());
}

int Thing::is_slime(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_slime());
}

int Thing::chance_d1000_jump_randomly(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_jump_randomly());
}

int Thing::chance_d1000_jump_onto(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_jump_onto());
}

int Thing::chance_d1000_jump_on_low_hp(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_jump_on_low_hp());
}

int Thing::is_able_to_jump(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump());
}

int Thing::is_able_to_collect_keys(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_collect_keys());
}

int Thing::is_key(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_key());
}

int Thing::is_destroyed_on_hit_or_miss(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_destroyed_on_hit_or_miss());
}

int Thing::is_destroyed_on_hitting(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_destroyed_on_hitting());
}

int Thing::is_laser(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_laser());
}

int Thing::is_lava(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_lava());
}

int Thing::is_light_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_light_blocker());
}

int Thing::is_light_blocker_for_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_light_blocker_for_monst());
}

int Thing::is_gas_blocker(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gas_blocker());
}

int Thing::is_living(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_living());
}

int Thing::is_loggable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_loggable());
}

int Thing::is_eater_of_meat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_meat());
}

int Thing::is_meat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_meat());
}

int Thing::is_mob(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob());
}

int Thing::is_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst());
}

int Thing::is_obs_wall_or_door(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_wall_or_door());
}

int Thing::is_obs_destructable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_destructable());
}

int Thing::is_msg(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg());
}

int Thing::is_no_tile(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_no_tile());
}

int Thing::is_openable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_openable());
}

int Thing::is_player(void)
{
  TRACE_NO_INDENT();
  return (is_the_player);
}

int Thing::is_poisonous_danger_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_poisonous_danger_level());
}

int Thing::is_necrotic_danger_level(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_necrotic_danger_level());
}

int Thing::is_eater_of_potions(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_potions());
}

int Thing::is_potion(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_potion());
}

int Thing::is_projectile(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_projectile());
}

int Thing::is_removable_if_out_of_slots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_removable_if_out_of_slots());
}

int Thing::is_ripple(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ripple());
}

int Thing::is_rock(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rock());
}

int Thing::is_able_to_jump_escape(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_escape());
}

int Thing::is_able_to_follow(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_follow());
}

int Thing::distance_leader_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_leader_max());
}

int Thing::distance_recruitment_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_recruitment_max());
}

float Thing::distance_recruitment_max_float(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_recruitment_max());
}

int Thing::spawn_group_radius(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_group_radius());
}

int Thing::is_able_to_use_weapons(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_weapons());
}

int Thing::is_corpse_with_bones(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_corpse_with_bones());
}

int Thing::is_green_splatter(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_splatter());
}

int Thing::is_gnome(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gnome());
}

int Thing::is_ettin(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ettin());
}

int Thing::is_golem(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_golem());
}

int Thing::is_demon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_demon());
}

int Thing::is_ogre(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ogre());
}

int Thing::is_troll(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_troll());
}

int Thing::is_mimic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mimic());
}

int Thing::effect_has_blast_radius(void)
{
  TRACE_NO_INDENT();
  return (tp()->effect_has_blast_radius());
}

int Thing::is_enchantable_as_a_group(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_enchantable_as_a_group());
}

int Thing::is_able_to_teleport_attack(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_teleport_attack());
}

int Thing::is_obsidian(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obsidian());
}

int Thing::is_cautious(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cautious());
}

int Thing::is_ranged_weapon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ranged_weapon());
}

int Thing::is_able_to_use_ranged_weapons(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_ranged_weapons());
}

int Thing::is_aerodynamic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_aerodynamic());
}

int Thing::is_light(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_light());
}

int Thing::is_missile(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_missile());
}

int Thing::is_thrown_as_a_weapon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_thrown_as_a_weapon());
}

int Thing::is_able_to_shoot_at_close_range(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_shoot_at_close_range());
}

int Thing::gfx_pixelart_show_highlighted(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_show_highlighted());
}

int Thing::gfx_pixelart_show_square_outlined(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_show_square_outlined());
}

int Thing::is_able_to_see_invisible(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_see_invisible());
}

int Thing::is_lightning(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_lightning());
}

int Thing::gfx_ascii_color_bg_unchanged_by_lights(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_color_bg_unchanged_by_lights());
}

int Thing::gfx_ascii_color_fg_unchanged_by_lights(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_color_fg_unchanged_by_lights());
}

int Thing::gfx_pixelart_oversized_and_centered(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_oversized_and_centered());
}

int Thing::is_limb(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_limb());
}

int Thing::is_msg_allowed_is_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg_allowed_is_dead());
}

int Thing::is_obs_shooting(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_shooting());
}

int Thing::is_msg_allowed_senses_danger(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg_allowed_senses_danger());
}

int Thing::is_msg_allowed_hears_something(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg_allowed_hears_something());
}

int Thing::gfx_pixelart_submergible(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_submergible());
}

int Thing::is_obs_jump_end(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_jump_end());
}

int Thing::is_obs_spawn_monst(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_spawn_monst());
}

int Thing::is_obs_spawn(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_spawn());
}

int Thing::gfx_pixelart_reflection(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_reflection());
}

int Thing::gfx_pixelart_shadow(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_shadow());
}

int Thing::is_able_to_be_surprised(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_be_surprised());
}

int Thing::is_msg_allowed_is_surprised(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg_allowed_is_surprised());
}

int Thing::is_obs_shoving(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_shoving());
}

int Thing::is_always_submerged_in_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_always_submerged_in_water());
}

int Thing::environ_likes_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_likes_deep_water());
}

int Thing::environ_likes_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->environ_likes_shallow_water());
}

int Thing::is_biome_unused(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_unused());
}

int Thing::is_biome_sewer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_sewer());
}

int Thing::is_swimmer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_swimmer());
}

int Thing::consume_per_bite_amount(void)
{
  TRACE_NO_INDENT();
  return (tp()->consume_per_bite_amount());
}

int Thing::is_able_to_live_out_of_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_live_out_of_water());
}

int Thing::is_able_to_rest(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_rest());
}

int Thing::is_msg_allowed_is_wounded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg_allowed_is_wounded());
}

int Thing::is_msg_allowed_is_seen(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_msg_allowed_is_seen());
}

int Thing::is_internal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_internal());
}

int Thing::is_eater_of_helmets(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_helmets());
}

int Thing::is_eater_of_amulets(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_amulets());
}

int Thing::is_eater_of_weapons(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_weapons());
}

int Thing::is_eater_of_boots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_boots());
}

int Thing::is_eater_of_gauntlets(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_gauntlets());
}

int Thing::is_eater_of_cloaks(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_cloaks());
}

int Thing::is_eater_of_shields(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_shields());
}

int Thing::is_eater_of_rings(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_rings());
}

int Thing::is_eater_of_staffs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_staffs());
}

int Thing::is_eater_of_armor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_armor());
}

int Thing::is_cowardly(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cowardly());
}

int Thing::chance_d1000_appearing(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_appearing());
}

int Thing::chance_d10000_set_on_fire(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d10000_set_on_fire());
}

int Thing::is_obs_throwing(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_throwing());
}

int Thing::is_gelatinous(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gelatinous());
}

int Thing::is_steam(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_steam());
}

int Thing::is_basalt(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_basalt());
}

int Thing::is_shovable_and_sticky(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shovable_and_sticky());
}

int Thing::is_block_of_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_block_of_ice());
}

int Thing::is_able_to_break_out_of_ice(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_ice());
}

int Thing::is_brittle(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_brittle());
}

int Thing::is_tentacle(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tentacle());
}

int Thing::is_able_to_swim(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_swim());
}

int Thing::gfx_ascii_shown_as_gray_in_shadow(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_shown_as_gray_in_shadow());
}

int Thing::gfx_ascii_shown_in_bg(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_shown_in_bg());
}

int Thing::gfx_ascii_fade_with_dist(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_ascii_fade_with_dist());
}

int Thing::is_obs_jumping(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_jumping());
}

int Thing::tick_prio(void)
{
  TRACE_NO_INDENT();
  return (tp()->tick_prio());
}

int Thing::is_dagger(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dagger());
}

int Thing::is_lifeless(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_lifeless());
}

int Thing::is_key_special(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_key_special());
}

int Thing::is_crystalline(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_crystalline());
}

int Thing::is_tireless(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tireless());
}

int Thing::is_snake(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_snake());
}

int Thing::is_item_targeted(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_targeted());
}

int Thing::chance_d1000_teleport_self(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_teleport_self());
}

int Thing::chance_d1000_teleport_attack(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_teleport_attack());
}

int Thing::teleport_distance(void)
{
  TRACE_NO_INDENT();
  return (tp()->teleport_distance());
}

int Thing::is_able_to_teleport_self(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_teleport_self());
}

int Thing::is_able_to_teleport_without_tiring(void)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_teleport_without_tiring()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_teleport_without_tiring());
}

int Thing::is_able_to_teleport_escape(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_teleport_escape());
}

int Thing::is_daring(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_daring());
}

int Thing::is_monst_pack(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_pack());
}

int Thing::is_pillar(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_pillar());
}

int Thing::collision_hit_two_tiles_ahead(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_two_tiles_ahead());
}

int Thing::is_flat(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_flat());
}

int Thing::is_target_radial(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_target_radial());
}

int Thing::is_staff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_staff());
}

int Thing::collision_hit_adj(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_adj());
}

int Thing::collision_hit_180(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_180());
}

int Thing::collision_hit_360(void)
{
  TRACE_NO_INDENT();
  return (tp()->collision_hit_360());
}

int Thing::is_dead_on_falling(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_dead_on_falling());
}

int Thing::temperature_sensitive(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_sensitive());
}

int Thing::is_cold(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cold());
}

int Thing::temperature_sensitive_to_sudden_changes(void)
{
  TRACE_NO_INDENT();
  return (tp()->temperature_sensitive_to_sudden_changes());
}

int Thing::is_very_heavy(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_heavy());
}

int Thing::gfx_pixelart_health_bar_only_when_awake(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_health_bar_only_when_awake());
}

int Thing::gfx_pixelart_show_asleep_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_show_asleep_anim());
}

int Thing::is_air_breather(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_air_breather());
}

int Thing::is_obs_when_dead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_obs_when_dead());
}

int Thing::is_green_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_blood());
}

int Thing::is_biome_swamp(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_swamp());
}

int Thing::is_biome_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_biome_dungeon());
}

int Thing::is_treasure(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure());
}

int Thing::is_monst_class_E(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_E());
}

int Thing::is_eater_of_green_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_green_blood());
}

int Thing::is_mob_class_A(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob_class_A());
}

int Thing::is_mob_class_B(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob_class_B());
}

int Thing::is_mob_class_C(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_mob_class_C());
}

int Thing::is_monst_class_D(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_D());
}

int Thing::is_monst_class_C(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_C());
}

int Thing::is_monst_class_B(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_B());
}

int Thing::is_monst_class_A(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_monst_class_A());
}

int Thing::stat_att_penalty_when_in_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_in_deep_water());
}

int Thing::stat_att_penalty_when_in_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_in_shallow_water());
}

int Thing::stat_att_penalty_when_stuck(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_stuck());
}

int Thing::stat_att_penalty_when_stuck_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_att_penalty_when_stuck_max());
}

int Thing::stat_def_penalty_when_stuck_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_stuck_max());
}

int Thing::stat_def_penalty_when_in_deep_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_in_deep_water());
}

int Thing::stat_def_penalty_when_in_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_in_shallow_water());
}

int Thing::stat_def_penalty_when_stuck(void)
{
  TRACE_NO_INDENT();
  return (tp()->stat_def_penalty_when_stuck());
}

int Thing::is_able_to_melt(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_melt());
}

int Thing::is_amulet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_amulet());
}

int Thing::is_helmet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_helmet());
}

int Thing::is_boots(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_boots());
}

int Thing::is_shield(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shield());
}

int Thing::is_cloak(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_cloak());
}

int Thing::is_gauntlet(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_gauntlet());
}

int Thing::is_hard(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_hard());
}

int Thing::is_red_blooded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_red_blooded());
}

int Thing::is_green_blooded(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_green_blooded());
}

int Thing::is_able_to_jump_without_tiring(void)
{
  TRACE_NO_INDENT();

  TRACE_NO_INDENT();
  FOR_ALL_EQUIP(e)
  {
    auto iter = equip_get(e);
    if (iter) {
      if (iter->is_able_to_jump_without_tiring()) {
        return true;
      }
    }
  }

  return (tp()->is_able_to_jump_without_tiring());
}

int Thing::is_spider(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spider());
}

int Thing::is_able_to_jump_attack(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_attack());
}

int Thing::is_able_to_jump_onto(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_jump_onto());
}

int Thing::is_crushable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_crushable());
}

int Thing::chance_d1000_shooting_avoid_friends(void)
{
  TRACE_NO_INDENT();
  return tp()->chance_d1000_shooting_avoid_friends();
}

int Thing::chance_d1000_shooting(void)
{
  TRACE_NO_INDENT();
  return tp()->chance_d1000_shooting();
}

int Thing::is_able_to_see_in_the_dark(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_see_in_the_dark());
}

int Thing::gfx_pixelart_anim_synced_with_owner(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_pixelart_anim_synced_with_owner());
}

int Thing::is_magical(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_magical());
}

int Thing::is_able_to_use_armor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_armor());
}

int Thing::is_ring(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_ring());
}

int Thing::is_auto_equipped(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_equipped());
}

int Thing::is_buff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_buff());
}

int Thing::is_debuff(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_debuff());
}

int Thing::is_eater_of_red_blood(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_red_blood());
}

int Thing::is_slippery(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_slippery());
}

int Thing::ai_detect_secret_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_detect_secret_doors());
}

int Thing::is_able_to_break_down_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_down_doors());
}

int Thing::is_able_to_break_out_of_webs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_break_out_of_webs());
}

int Thing::is_able_to_open_doors(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_open_doors());
}

int Thing::is_exit_finder(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_exit_finder());
}

int Thing::is_explorer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_explorer());
}

int Thing::is_rusty(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_rusty());
}

int Thing::is_armor(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_armor());
}

int Thing::is_able_to_learn_skills(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_learn_skills());
}

int Thing::is_able_to_learn_spells(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_learn_spells());
}

int Thing::is_able_to_enchant_items(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_enchant_items());
}

int Thing::ai_wanderer(void)
{
  TRACE_NO_INDENT();
  return (tp()->ai_wanderer());
}

int Thing::is_organic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_organic());
}

int Thing::is_glass(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_glass());
}

int Thing::is_item_organic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_organic());
}

int Thing::is_metal(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_metal());
}

int Thing::is_wooden(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wooden());
}

int Thing::is_flying(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_flying());
}

int Thing::is_engulfer(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_engulfer());
}

int Thing::is_health_booster(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_health_booster());
}

int Thing::is_map_beast(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_map_beast());
}

int Thing::is_map_treasure(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_map_treasure());
}

int Thing::is_able_to_use_staffs(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_staffs());
}

int Thing::is_aquatic(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_aquatic());
}

int Thing::is_secret_door(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_secret_door());
}

int Thing::is_sewer_wall(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sewer_wall());
}

int Thing::is_shallow_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shallow_water());
}

int Thing::is_shovable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shovable());
}

int Thing::is_skillstone(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_skillstone());
}

int Thing::is_skill(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_skill());
}

int Thing::is_spellbook(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spellbook());
}

int Thing::is_spell(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spell());
}

int Thing::is_smoke(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_smoke());
}

int Thing::is_soft(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_soft());
}

int Thing::is_able_to_spawn_things(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_spawn_things());
}

int Thing::is_spiderweb(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spiderweb());
}

int Thing::is_able_to_tire(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_tire());
}

int Thing::chance_d1000_steal_item(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_steal_item());
}

int Thing::chance_d1000_attack_engulf(void)
{
  TRACE_NO_INDENT();
  return (tp()->chance_d1000_attack_engulf());
}

int Thing::is_sticky(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sticky());
}

int Thing::is_sword(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_sword());
}

int Thing::is_target_select(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_target_select());
}

int Thing::is_throwable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_throwable());
}

int Thing::is_auto_throw(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_throw());
}

int Thing::is_tickable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tickable());
}

int Thing::is_tmp_thing(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_tmp_thing());
}

int Thing::is_torch(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_torch());
}

int Thing::is_treasure_class_A(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_class_A());
}

int Thing::is_treasure_class_B(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_class_B());
}

int Thing::is_treasure_class_C(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_class_C());
}

int Thing::is_weapon_class_A(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon_class_A());
}

int Thing::is_weapon_class_B(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon_class_B());
}

int Thing::is_weapon_class_C(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon_class_C());
}

int Thing::is_treasure_chest(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_chest());
}

int Thing::is_item_collector(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_item_collector());
}

int Thing::is_eater_of_treasure(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_treasure());
}

int Thing::is_treasure_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_treasure_type());
}

int Thing::is_undead(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_undead());
}

int Thing::is_usable(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_usable());
}

int Thing::is_auto_use(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_auto_use());
}

int Thing::is_used_when_thrown(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_used_when_thrown());
}

int Thing::is_very_combustible(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_very_combustible());
}

int Thing::is_wall_dungeon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wall_dungeon());
}

int Thing::is_wall(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_wall());
}

int Thing::is_eater_of_magical_items(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_eater_of_magical_items());
}

int Thing::is_weapon(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_weapon());
}

int Thing::is_able_to_use_rings(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_able_to_use_rings());
}

float Thing::distance_minion_from_mob_max_float(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_minion_from_mob_max());
}

float Thing::distance_leader_max_float(void)
{
  TRACE_NO_INDENT();
  return (tp()->distance_leader_max());
}

int Thing::normal_placement_rules(void)
{
  TRACE_NO_INDENT();
  return (tp()->normal_placement_rules());
}

int Thing::on_death_drop_all_items(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_drop_all_items());
}

int Thing::on_death_is_open(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_is_open());
}

int Thing::range_max(void)
{
  TRACE_NO_INDENT();
  return (tp()->range_max());
}

int Thing::is_water(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_shallow_water() || tp()->is_deep_water());
}

void Thing::new_infop(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _infop)) {
    _infop = new ThingInfo();
    // uncomment to see who allocates things
    // err("New monst info");
    newptr(MTYPE_INFOP, _infop, "ThingInfo");

    if (mytp && (tp_id != -1)) {
      //
      // Walls and rock can be destroyed, hence no checks
      //
      if (is_msg() || is_cursor()) {
        //
        // Cursor needs to move
        //
      } else if (is_dirt() || is_internal() || is_floor() || is_corridor()) {
        die("Unexpectedly needs info monst struct");
      }
    }
  }
}

void Thing::new_itemsp(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _itemsp)) {
    _itemsp = new ThingItem();
    // uncomment to see who allocates things
    // err("New monst item");
    newptr(MTYPE_ITEMP, _itemsp, "ThingItem");

    if (mytp && (tp_id != -1)) {
      //
      // Walls and rock can be destroyed, hence no checks
      //
      if (is_wall() || is_dirt() || is_internal() || is_floor() || is_corridor()) {
        die("Unexpectedly needs item monst struct");
      }
    }
  }
}

void Thing::new_aip(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _aip)) {
    _aip = new ThingAi();
    // uncomment to see who allocates things
    // err("New monst ai");
    newptr(MTYPE_AIP, _aip, "ThingAi");
  }
}

ThingInfop Thing::get_or_alloc_infop(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _infop)) {
    new_infop();
  }
  //
  // Called a lot and is hence expensive, so debug level 3
  //
  IF_DEBUG3 { verify(MTYPE_INFOP, _infop); }
  return _infop;
}

ThingItemsp Thing::get_or_alloc_itemsp(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _itemsp)) {
    new_itemsp();
  }
  //
  // Called a lot and is hence expensive, so debug level 3
  //
  IF_DEBUG3 { verify(MTYPE_ITEMP, _itemsp); }
  return _itemsp;
}

ThingAip Thing::get_or_alloc_aip(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! _aip)) {
    new_aip();
  }
  //
  // Called a lot and is hence expensive, so debug level 3
  //
  IF_DEBUG3 { verify(MTYPE_AIP, _aip); }
  return _aip;
}

////////////////////////////////////////////////////////////////////////////
// age_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::age_map_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->age_map);
}

void Thing::clear_age_map(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->age_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// dmap_can_see_old
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::dmap_can_see_old_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->dmap_can_see_old);
}

void Thing::clear_dmap_can_see_old(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->dmap_can_see_old.val = {};
}

////////////////////////////////////////////////////////////////////////////
// interrupt_map
////////////////////////////////////////////////////////////////////////////
AgeMap *Thing::interrupt_map_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->interrupt_map);
}

void Thing::clear_interrupt_map(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->interrupt_map.val = {};
}

////////////////////////////////////////////////////////////////////////////
// _dmap_can_see
////////////////////////////////////////////////////////////////////////////
Dmap *Thing::dmap_can_see_get(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->dmap_can_see);
}

void Thing::clear_dmap_can_see(void)
{
  TRACE_NO_INDENT();
  new_aip();

  for (auto y = 0; y < MAP_HEIGHT; y++) {
    for (auto x = 0; x < MAP_WIDTH; x++) {
      set(aip()->dmap_can_see.val, x, y, DMAP_IS_WALL);
    }
  }
}

////////////////////////////////////////////////////////////////////////////
// can_see_currently
////////////////////////////////////////////////////////////////////////////
FovMap *Thing::can_see_currently(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->can_see_currently);
}

void Thing::clear_can_see_currently(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->can_see_currently.can_see = {};
}

////////////////////////////////////////////////////////////////////////////
// can_see_ever
////////////////////////////////////////////////////////////////////////////
FovMap *Thing::can_see_ever(void)
{
  TRACE_NO_INDENT();
  new_aip();
  return (&aip()->can_see_ever);
}

void Thing::clear_can_see_ever(void)
{
  TRACE_NO_INDENT();
  new_aip();
  aip()->can_see_ever.can_see = {};
}

int Thing::item_height(void)
{
  TRACE_NO_INDENT();
  return (tp()->item_height());
}

int Thing::item_width(void)
{
  TRACE_NO_INDENT();
  return (tp()->item_width());
}

int Thing::capacity_height(void)
{
  TRACE_NO_INDENT();
  new_infop();
  if (infop()->capacity_height) {
    return infop()->capacity_height;
  }
  return (tp()->capacity_height());
}

int Thing::capacity_width(void)
{
  TRACE_NO_INDENT();
  new_infop();
  if (infop()->capacity_width) {
    return infop()->capacity_width;
  }
  return (tp()->capacity_width());
}

int Thing::thing_size(void)
{
  TRACE_NO_INDENT();
  return (tp()->thing_size());
}

int Thing::rarity(void)
{
  TRACE_NO_INDENT();
  return (tp()->rarity());
}

////////////////////////////////////////////////////////////////////////////
// msg
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::msg_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->msg);
  }
  static std::string empty;
  return empty;
}

void Thing::msg_set(const std::string &v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->msg = v;
}

////////////////////////////////////////////////////////////////////////////
// dead_reason
////////////////////////////////////////////////////////////////////////////
const std::string &Thing::dead_reason_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->dead_reason);
  }
  static std::string empty;
  return empty;
}

void Thing::dead_reason_set(const std::string &v)
{
  TRACE_NO_INDENT();
  if (! maybe_infop()) {
    return;
  }
  new_infop();
  infop()->dead_reason = v;
}

////////////////////////////////////////////////////////////////////////////
// submerged_offset
////////////////////////////////////////////////////////////////////////////
int Thing::submerged_offset_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    //
    // Floating when dead?
    //
    if (is_dead) {
      return (infop()->submerged_offset / 2);
    }

    return (infop()->submerged_offset);
  }
  return 0;
}

void Thing::submerged_offset_set(int v)
{
  TRACE_NO_INDENT();
  new_infop();
  infop()->submerged_offset = v;
}

////////////////////////////////////////////////////////////////////////////
// stats02
////////////////////////////////////////////////////////////////////////////
int Thing::stats02(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats02);
  }
  return 0;
}

int Thing::stats02_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02 = v);
  return n;
}

int Thing::stats02_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02 -= v);
  return n;
}

int Thing::stats02_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02 += v);
  return n;
}

int Thing::stats02_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02--);
  return n;
}

int Thing::stats02_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats02++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stats03
////////////////////////////////////////////////////////////////////////////
int Thing::stats03(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats03);
  }
  return 0;
}

int Thing::stats03_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03 = v);
  return n;
}

int Thing::stats03_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03 -= v);
  return n;
}

int Thing::stats03_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03 += v);
  return n;
}

int Thing::stats03_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03--);
  return n;
}

int Thing::stats03_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats03++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stats04
////////////////////////////////////////////////////////////////////////////
int Thing::stats04(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats04);
  }
  return 0;
}

int Thing::stats04_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04 = v);
  return n;
}

int Thing::stats04_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04 -= v);
  return n;
}

int Thing::stats04_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04 += v);
  return n;
}

int Thing::stats04_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04--);
  return n;
}

int Thing::stats04_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats04++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stats05
////////////////////////////////////////////////////////////////////////////
int Thing::stats05(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats05);
  }
  return 0;
}

int Thing::stats05_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05 = v);
  return n;
}

int Thing::stats05_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05 -= v);
  return n;
}

int Thing::stats05_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05 += v);
  return n;
}

int Thing::stats05_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05--);
  return n;
}

int Thing::stats05_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats05++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stats06
////////////////////////////////////////////////////////////////////////////
int Thing::stats06(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats06);
  }
  return 0;
}

int Thing::stats06_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06 = v);
  return n;
}

int Thing::stats06_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06 -= v);
  return n;
}

int Thing::stats06_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06 += v);
  return n;
}

int Thing::stats06_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06--);
  return n;
}

int Thing::stats06_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats06++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stats07
////////////////////////////////////////////////////////////////////////////
int Thing::stats07(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats07);
  }
  return 0;
}

int Thing::stats07_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07 = v);
  return n;
}

int Thing::stats07_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07 -= v);
  return n;
}

int Thing::stats07_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07 += v);
  return n;
}

int Thing::stats07_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07--);
  return n;
}

int Thing::stats07_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats07++);
  return n;
}

////////////////////////////////////////////////////////////////////////////
// stats09
////////////////////////////////////////////////////////////////////////////
int Thing::stats09(void)
{
  TRACE_NO_INDENT();
  if (maybe_infop()) {
    return (infop()->stats09);
  }
  return 0;
}

int Thing::stats09_set(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09 = v);
  return n;
}

int Thing::stats09_decr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09 -= v);
  return n;
}

int Thing::stats09_incr(int v)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09 += v);
  return n;
}

int Thing::stats09_decr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09--);
  return n;
}

int Thing::stats09_incr(void)
{
  TRACE_NO_INDENT();
  if (is_player()) {
    game->set_request_to_remake_rightbar();
  }
  new_infop();
  auto n = (infop()->stats09++);
  return n;
}

const std::string &Thing::text_unused1(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused1());
}

const std::string &Thing::text_unused2(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused2());
}

const std::string &Thing::name(void)
{
  TRACE_NO_INDENT();
  return (tp()->name());
}

const std::string &Thing::on_polymorphed_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_polymorphed_do());
}

const std::string &Thing::on_you_nat_attack_attempt_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_nat_attack_attempt_do());
}

const std::string &Thing::on_you_nat_attack_success_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_nat_attack_success_do());
}

const std::string &Thing::on_resting_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_resting_do());
}

const std::string &Thing::on_waiting_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_waiting_do());
}

const std::string &Thing::on_stuck_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_stuck_do());
}

const std::string &Thing::on_death_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_do());
}

const std::string &Thing::on_awake_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_awake_do());
}

const std::string &Thing::on_enchant_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_enchant_do());
}

const std::string &Thing::on_thrown_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_thrown_do());
}

const std::string &Thing::on_targeted_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_targeted_do());
}

const std::string &Thing::on_targeted_radially_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_targeted_radially_do());
}

const std::string &Thing::on_dropped_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_dropped_do());
}

const std::string &Thing::on_fall_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_fall_do());
}

const std::string &Thing::on_fall_begin_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_fall_begin_do());
}

const std::string &Thing::on_jump_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_jump_do());
}

const std::string &Thing::on_you_are_on_fire_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_on_fire_do());
}

const std::string &Thing::on_want_to_shoot_at_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_want_to_shoot_at_do());
}

const std::string &Thing::on_hit_and_still_alive_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_hit_and_still_alive_do());
}

const std::string &Thing::on_hit_and_now_dead_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_hit_and_now_dead_do());
}

const std::string &Thing::on_hit_dodge_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_hit_dodge_do());
}

const std::string &Thing::on_tick_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_tick_do());
}

const std::string &Thing::on_tick_when_deactivated_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_tick_when_deactivated_do());
}

const std::string &Thing::on_tick_when_activated_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_tick_when_activated_do());
}

const std::string &Thing::on_use_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_use_do());
}

const std::string &Thing::on_use_skill_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_use_skill_do());
}

const std::string &Thing::on_swing_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_swing_do());
}

const std::string &Thing::on_final_use_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_final_use_do());
}

const std::string &Thing::on_equip_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_equip_do());
}

const std::string &Thing::on_unequip_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_unequip_do());
}

const std::string &Thing::on_owner_add_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_add_do());
}

const std::string &Thing::on_owner_unset_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_owner_unset_do());
}

const std::string &Thing::on_you_are_declared_a_follower_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_declared_a_follower_do());
}

const std::string &Thing::on_death_of_a_follower_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_of_a_follower_do());
}

const std::string &Thing::on_you_are_declared_leader_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_you_are_declared_leader_do());
}

const std::string &Thing::on_death_of_my_leader_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_death_of_my_leader_do());
}

const std::string &Thing::gfx_targeted_projectile(void)
{
  TRACE_NO_INDENT();
  return (tp()->gfx_targeted_projectile());
}

const std::string &Thing::spawn_on_shoved(void)
{
  TRACE_NO_INDENT();
  return (tp()->spawn_on_shoved());
}

const std::string &Thing::str1(void)
{
  TRACE_NO_INDENT();
  return (tp()->str1());
}

const std::string &Thing::str2(void)
{
  TRACE_NO_INDENT();
  return (tp()->str2());
}

const std::string &Thing::str4(void)
{
  TRACE_NO_INDENT();
  return (tp()->str4());
}

const std::string &Thing::is_allied_with(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_allied_with());
}

const std::string &Thing::text_description_enchant(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_description_enchant());
}

const std::string &Thing::text_hits(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_hits());
}

const std::string &Thing::text_real_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_real_name());
}

const std::string &Thing::dmg_nat_att_type(void)
{
  TRACE_NO_INDENT();
  return (tp()->dmg_nat_att_type());
}

const std::string &Thing::skill_base_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->skill_base_name());
}

const std::string &Thing::skill_replaces(void)
{
  TRACE_NO_INDENT();
  return (tp()->skill_replaces());
}

const std::string &Thing::spell_base_name(void)
{
  TRACE_NO_INDENT();
  return (tp()->spell_base_name());
}

const std::string &Thing::spell_replaces(void)
{
  TRACE_NO_INDENT();
  return (tp()->spell_replaces());
}

const std::string &Thing::text_debuff(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_debuff());
}

const std::string &Thing::text_unused3(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused3());
}

const std::string &Thing::text_title(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_title());
}

const std::string &Thing::text_unused(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_unused());
}

const std::string &Thing::equip_carry_anim(void)
{
  TRACE_NO_INDENT();
  return (tp()->equip_carry_anim());
}

std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *Thing::bag_get(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (&itemsp()->bag);
  }
  //
  // Watch out here as lasers can have owners and do not live in bags.
  //
  dbg("No bag");
  return nullptr;
}

const std::array< std::array< ThingId, MAX_BAG_HEIGHT >, MAX_BAG_WIDTH > *Thing::stat_const_bag(void)
{
  TRACE_NO_INDENT();
  if (maybe_itemsp()) {
    return (&itemsp()->bag);
  }
  //
  // Watch out here as lasers can have owners and do not live in bags.
  //
  dbg("No bag");
  return nullptr;
}

const std::string &Thing::title(void)
{
  if (g_opt_player_name.empty()) {
    return text_title();
  }
  return g_opt_player_name;
}
