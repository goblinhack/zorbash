//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"

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
    "amulet_endurance",
    "amulet_endurance_carry",
    "amulet_healing",
    "amulet_healing_carry",
    "amulet_peeking",
    "amulet_peeking_carry",
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
    "ascend_dungeon",
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
    "basalt",
    "bat_greater",
    "bat_lesser",
    "bat_minion",
    "belcher",
    "blob",
    "block_of_ice",
    "bones.1",
    "bones.2",
    "bones.3",
    "bones.4",
    "bones.5",
    "bones.6",
    "boots_fluffy",
    "boots_fluffy_carry",
    "boots_haste",
    "boots_haste_carry",
    "boots_jumping",
    "boots_jumping_carry",
    "boots_silence",
    "boots_silence_carry",
    "boots_teleport",
    "boots_teleport_carry",
    "boots_teleport_emer",
    "boots_teleport_emer_carry",
    "brazier",
    "bridge_lr",
    "bridge_ud",
    "bridge_x",
    "buff_full",
    "buff_is_invisible",
    "buff_is_immune_to_cold",
    "buff_is_immune_to_fire",
    "buff_is_immune_to_negation",
    "buff_is_immune_to_poison",
    "buff_is_immune_to_water",
    "buff_missile_protection",
    "buff_slippery",
    "buff_undead_protection",
    "cement_man",
    "chasm1",
    "chest1",
    "cleaner",
    "cloak_fire",
    "cloak_fire_carry",
    "cloak_protection",
    "cloak_protection_carry",
    "cloak_stone",
    "cloak_stone_carry",
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
    "dagger",
    "dagger_carry",
    "dagger_swing",
    "debuff_hungry",
    "debuff_necrotized",
    "debuff_poisoned",
    "debuff_starving",
    "debug_path",
    "deep_water",
    "descend_sewer1",
    "descend_sewer2",
    "descend_sewer3",
    "descend_sewer4",
    "descend_sewer5",
    "dirt1",
    "dirt2",
    "dirt3",
    "dogman",
    "door_metal",
    "door_secret",
    "door_wood",
    "double_shovel",
    "double_shovel_carry",
    "double_shovel_swing",
    "dry_grass",
    "dry_grass_dead",
    "dry_grass_trampled",
    "eel",
    "enchantstone",
    "exit1",
    "explosion_cold",
    "explosion_destroy_floor",
    "explosion_fire",
    "explosion_major",
    "fire",
    "flameskull",
    "flesh_golem",
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
    "floor_red_blood1",
    "floor_red_blood2",
    "floor_red_blood3",
    "floor_red_blood4",
    "floor_red_blood5",
    "floor_red_blood6",
    "floor_red_blood7",
    "floor_red_blood8",
    "foliage",
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
    "four_leaf_clover",
    "gargoyle_moving",
    "gargoyle_podium",
    "gargoyle_static",
    "gauntlets_lion",
    "gauntlets_lion_carry",
    "gauntlets_shoving",
    "gauntlets_shoving_carry",
    "gauntlets_war",
    "gauntlets_war_carry",
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
    "goldfish",
    "green_splatter",
    "horseshoe",
    "jelly_baby",
    "jelly_parent",
    "key",
    "key_crystal",
    "key_golden",
    "key_pair",
    "key_penta",
    "kraken",
    "kraken_tentacle",
    "laser_energy",
    "lava",
    "lizardkin",
    "magical_effect",
    "map_beast",
    "map_treasure",
    "medal_of_valor",
    "mob_explosion",
    "msg",
    "mummy",
    "mummy_necro",
    "mummy_pack",
    "pike",
    "pike_carry",
    "pike_swing",
    "pillar",
    "pirhana",
    "pirhana_giant",
    "pirhana_giant_pack",
    "pirhana_pack",
    "player1",
    "player2",
    "potion_effect",
    "potion_health",
    "potion_invisibility",
    "projectile_acid",
    "projectile_web",
    "rat_giant",
    "reaper",
    "red_splatter",
    "ring_is_immune_to_cold",
    "ring_is_immune_to_cold_carry",
    "ring_is_immune_to_fire",
    "ring_is_immune_to_fire_carry",
    "ring_is_immune_to_negation",
    "ring_is_immune_to_negation_carry",
    "ring_is_immune_to_poison",
    "ring_is_immune_to_poison_carry",
    "ring_shield",
    "ring_shield_carry",
    "ripple_large1",
    "ripple_large2",
    "ripple_small1",
    "ripple_small2",
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
    "shovel",
    "shovel_carry",
    "shovel_swing",
    "skeleton",
    "skel_fire",
    "skel_giant",
    "skel_minion",
    "skel_minion_fire",
    "skel_minion_wander",
    "skel_mob",
    "skill_devoted_thrust",
    "skill_devoted_thrust_effect",
    "skill_secondary_attack",
    "skill_secondary_attack_effect",
    "skillstone",
    "small_fire",
    "smoke",
    "snake_asp",
    "snake_dreadfire",
    "snake_viper",
    "spider_giant",
    "spiderweb",
    "staff_cold",
    "staff_cold_carry",
    "staff_cold_projectile",
    "staff_descent",
    "staff_descent_carry",
    "staff_descent_laser",
    "staff_descent_radial",
    "staff_energy",
    "staff_energy_carry",
    "staff_fire",
    "staff_fire_carry",
    "staff_fire_projectile",
    "staff_lightning",
    "staff_lightning_carry",
    "staff_lightning_laser",
    "staff_lightning_laser_fork",
    "staff_negation",
    "staff_negation_carry",
    "staff_negation_laser",
    "staff_negation_radial",
    "steam",
    "sword",
    "sword_carry",
    "sword_draining",
    "sword_draining_carry",
    "sword_draining_swing",
    "sword_plutonium",
    "sword_plutonium_carry",
    "sword_plutonium_swing",
    "sword_rusty",
    "sword_rusty_carry",
    "sword_rusty_swing",
    "sword_swing",
    "sword_wood",
    "sword_wood_carry",
    "sword_wood_swing",
    "teleport_in",
    "teleport_out",
    "teletoad",
    "tentacleye",
    "the_grid",
    "thunderstone",
    "torch",
    "vampire_rose",
    "vampire_rose_stem1",
    "vampire_rose_stem2",
    "very_broadsword",
    "very_broadsword_carry",
    "very_broadsword_swing",
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
    "water",
    "webball",
    "wet_grass1",
    "wet_grass2",
    "wet_grass3",
    "wet_grass4",
    "wet_grass5",
    "wet_grass6",
    "wooden_cross",
    "wooden_cross_carry",
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
