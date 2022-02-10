//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_dice.hpp"
#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"

//
// Templates can be assigned dynamic IDs - however the levels are more reproducable it
// they have fixed numbers. This list helps to achieve that. It is optional for a template
// to be in this list
//
std::initializer_list< std::string > tps = {
    "", // ID 0 means unused
    "acid1",
    "ai_path1",
    "ai_path2",
    "armor_fish_scale",
    "armor_fish_scale_carry",
    "armor_lather",
    "armor_lather_carry",
    "armor_lathered",
    "armor_lathered_carry",
    "armor_leather",
    "armor_leather_carry",
    "armor_lime_scale",
    "armor_lime_scale_carry",
    "ascend_sewer1",
    "ascend_sewer2",
    "ascend_sewer3",
    "ascend_sewer4",
    "attack_claws",
    "attack_punch",
    "axe",
    "axe_carry",
    "axe_swing",
    "bag_l",
    "bag_s",
    "barrel",
    "bat_greater",
    "bat_lesser",
    "bat_minion",
    "belcher",
    "bones.1",
    "bones.2",
    "bones.3",
    "bones.4",
    "bones.5",
    "bones.6",
    "boots_fluffy",
    "brazier1",
    "bridge_lr",
    "bridge_ud",
    "bridge_x",
    "buff_aquatic",
    "buff_poison_resist",
    "buff_slippery",
    "chasm1",
    "chest1",
    "cleaner",
    "coffin_mob",
    "corridor1",
    "corridor2",
    "cursor",
    "cursor_path",
    "cursor_select",
    "cursor_select_fail",
    "cursor_select_fail_path",
    "cursor_select_path",
    "cutlass",
    "cutlass_carry",
    "cutlass_swing",
    "debuff_necrotized",
    "debuff_poisoned",
    "debug_path",
    "deep_water1",
    "descend_sewer1",
    "descend_sewer2",
    "descend_sewer3",
    "descend_sewer4",
    "descend_sewer5",
    "dirt1",
    "dirt2",
    "dirt3",
    "door_metal",
    "door_secret",
    "door_wood",
    "dry_grass",
    "dry_grass_dead",
    "dry_grass_trampled",
    "enchantstone",
    "entrance",
    "exit1",
    "explosion_destroy_floor",
    "explosion_major",
    "explosion_minor",
    "fire",
    "floor1",
    "floor10",
    "floor11",
    "floor2",
    "floor3",
    "floor4",
    "floor5",
    "floor6",
    "floor7",
    "floor8",
    "floor9",
    "floor_green_blood1",
    "floor_green_blood2",
    "floor_green_blood3",
    "floor_green_blood4",
    "floor_green_blood5",
    "floor_green_blood6",
    "floor_green_blood7",
    "floor_green_blood8",
    "floor_pink_blood1",
    "floor_pink_blood2",
    "floor_pink_blood3",
    "floor_pink_blood4",
    "floor_pink_blood5",
    "floor_pink_blood6",
    "floor_pink_blood7",
    "floor_pink_blood8",
    "floor_red_blood1",
    "floor_red_blood2",
    "floor_red_blood3",
    "floor_red_blood4",
    "floor_red_blood5",
    "floor_red_blood6",
    "floor_red_blood7",
    "floor_red_blood8",
    "foilage",
    "food_apple1",
    "food_apple2",
    "food_apple_cider",
    "food_applepie",
    "food_aubergine",
    "food_bacon",
    "food_baguette",
    "food_beer1",
    "food_beer2",
    "food_cheesecake",
    "food_cherry",
    "food_chicken",
    "food_chocolate_bar",
    "food_cookie",
    "food_custardpie",
    "food_durian",
    "food_eggs",
    "food_fish",
    "food_flagon_ale",
    "food_frog",
    "food_gherkin",
    "food_ginger",
    "food_greenpepper",
    "food_honey",
    "food_hotsauce",
    "food_lemonpie",
    "food_melon1",
    "food_melon2",
    "food_onion",
    "food_orange_slices",
    "food_peach",
    "food_pickled_eggs",
    "food_pickledeyes",
    "food_pineapple",
    "food_potato",
    "food_pottedmeat",
    "food_pretzel",
    "food_redpepper",
    "food_roastchicken",
    "food_salami",
    "food_salmon",
    "food_sardines",
    "food_sirloin",
    "food_somekindofmeat",
    "food_steak",
    "food_strawberry",
    "food_sushi1",
    "food_sushi2",
    "food_tomato",
    "food_turnip",
    "food_watermelon",
    "food_wine",
    "gargoyle_moving",
    "gargoyle_podium",
    "gargoyle_static",
    "gem_amber",
    "gem_amethyst",
    "gem_aventurine",
    "gem_diamond",
    "gem_emerald",
    "gem_ruby",
    "gem_sapphire",
    "gem_topaz",
    "ghost",
    "ghost_explosion",
    "ghost_minion",
    "ghost_mob",
    "gold1",
    "gold2",
    "gold3",
    "gold4",
    "gold5",
    "gold6",
    "green_splatter",
    "jelly_baby",
    "jelly_parent",
    "key",
    "laser_descent",
    "laser_energy",
    "laser_light",
    "laser_light_fork",
    "lava",
    "map_beast",
    "map_treasure",
    "mob_explosion",
    "msg",
    "mummy",
    "pillar1",
    "pink_splatter",
    "player1",
    "player2",
    "pot_health",
    "pot_health_effect",
    "projectile_cold",
    "projectile_fire",
    "projectile_web",
    "rat_giant",
    "reaper",
    "red_splatter",
    "ring_poison_resist",
    "ring_poison_resist_carry",
    "ripple1",
    "ripple2",
    "rock1",
    "scythe",
    "scythe_carry",
    "scythe_swing",
    "sewer_wall",
    "shield_wooden",
    "shield_wooden_carry",
    "shield_wooden_scale",
    "shield_wooden_scale_carry",
    "shield_woodon",
    "shield_woodon_carry",
    "shield_woodon_scale",
    "shield_woodon_scale_carry",
    "skeleton",
    "skel_fire",
    "skel_giant",
    "skel_minion",
    "skel_minion_fire",
    "skel_minion_wander",
    "skel_mob",
    "skill_devoted_thrust",
    "skill_devoted_thrust_effect",
    "skillstone",
    "small_fire",
    "smoke",
    "spider_giant",
    "spiderweb",
    "sword1",
    "sword1_carry",
    "sword1_rusty",
    "sword1_rusty_carry",
    "sword1_rusty_swing",
    "sword1_swing",
    "sword1_wood",
    "sword1_wood_carry",
    "sword1_wood_swing",
    "tentacleye",
    "the_grid",
    "thunderstone",
    "torch",
    "wall_dungeon.1",
    "wall_dungeon.10",
    "wall_dungeon.11",
    "wall_dungeon.12",
    "wall_dungeon.2",
    "wall_dungeon.3",
    "wall_dungeon.4",
    "wall_dungeon.5",
    "wall_dungeon.6",
    "wall_dungeon.7",
    "wall_dungeon.8",
    "wall_dungeon.9",
    "wall_floor1",
    "wand_cold",
    "wand_cold_carry",
    "wand_descent",
    "wand_descent_carry",
    "wand_energy",
    "wand_energy_carry",
    "wand_fire",
    "wand_fire_carry",
    "wand_lightning",
    "wand_lightning_carry",
    "water1",
    "webball",
    "wet_grass",
    "zoblin",
    "zorb_captain",
    "zorb_eldster",
    "zorb_necro",
    "zorb_pack",
    "zorb_pirate",
    "zorb_priest",
    "zorb_single",
    "zorb_soldier",
    "zorb_wizard",
};

static std::map< std::string, int > tp_preferred_id;

//
// Assign template IDs
//
void tp_get_id(const std::string &tp_name, int *id_out)
{
  static const std::vector< std::string > tp_arr(tps);

  static int  id;
  static bool init;

  //
  // Assign static IDs
  //
  if (! init) {
    init = true;
    for (auto t : tp_arr) {
      tp_preferred_id[ t ] = id++;
    }
  }

  //
  // Previously known
  //
  if (tp_preferred_id.find(tp_name) == tp_preferred_id.end()) {
    tp_preferred_id[ tp_name ] = *id_out = ++id;
    CON("*** Thing template not found %s. Please edit thing_template_ids.cpp and add it. ***", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}
