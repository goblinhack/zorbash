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
    "acid_blob",
    "ai_path1",
    "ai_path2",
    "amulet_endurance",
    "amulet_endurance_carry",
    "amulet_healing",
    "amulet_healing_carry",
    "amulet_mindseeing",
    "amulet_mindseeing_carry",
    "amulet_peeking",
    "amulet_peeking_carry",
    "amulet_teleport_attack",
    "amulet_teleport_attack_carry",
    "apple1",
    "apple2",
    "apple_cider",
    "applepie",
    "armor_crystal",
    "armor_crystal_carry",
    "armor_dragon",
    "armor_dragon_carry",
    "armor_fish_scale",
    "armor_fish_scale_carry",
    "armor_golden",
    "armor_golden_carry",
    "armor_lather",
    "armor_lather_carry",
    "armor_lathered",
    "armor_lathered_carry",
    "armor_leather",
    "armor_leather_carry",
    "armor_lime_scale",
    "armor_lime_scale_carry",
    "armor_obsidian",
    "armor_obsidian_carry",
    "armor_plate",
    "armor_plate_carry",
    "armor_slime",
    "armor_slime_carry",
    "armor_unobtanium",
    "armor_unobtanium_carry",
    "ascend_dungeon",
    "ascend_sewer1",
    "ascend_sewer2",
    "ascend_sewer3",
    "ascend_sewer4",
    "attack_green",
    "attack_major_green",
    "attack_major_orange",
    "attack_major_red",
    "attack_orange",
    "attack_punch",
    "attack_red",
    "aubergine",
    "axe",
    "axe_carry",
    "axe_swing",
    "bacon",
    "bag_large",
    "bag_small",
    "baguette",
    "barrel",
    "basalt",
    "bat_greater",
    "bat_lesser",
    "bat_minion",
    "bearowl",
    "bear_undead",
    "beer1",
    "beer2",
    "belcher",
    "blinkcat",
    "block_of_crystal",
    "block_of_ice",
    "bloodbug",
    "bodypart_eyes1",
    "bodypart_eyes10",
    "bodypart_eyes11",
    "bodypart_eyes12",
    "bodypart_eyes13",
    "bodypart_eyes14",
    "bodypart_eyes15",
    "bodypart_eyes16",
    "bodypart_eyes17",
    "bodypart_eyes18",
    "bodypart_eyes19",
    "bodypart_eyes2",
    "bodypart_eyes20",
    "bodypart_eyes21",
    "bodypart_eyes22",
    "bodypart_eyes23",
    "bodypart_eyes24",
    "bodypart_eyes25",
    "bodypart_eyes26",
    "bodypart_eyes27",
    "bodypart_eyes3",
    "bodypart_eyes4",
    "bodypart_eyes5",
    "bodypart_eyes6",
    "bodypart_eyes7",
    "bodypart_eyes8",
    "bodypart_eyes9",
    "bodypart_face1",
    "bodypart_face10",
    "bodypart_face11",
    "bodypart_face12",
    "bodypart_face13",
    "bodypart_face14",
    "bodypart_face15",
    "bodypart_face16",
    "bodypart_face17",
    "bodypart_face18",
    "bodypart_face19",
    "bodypart_face2",
    "bodypart_face20",
    "bodypart_face21",
    "bodypart_face22",
    "bodypart_face23",
    "bodypart_face24",
    "bodypart_face25",
    "bodypart_face26",
    "bodypart_face27",
    "bodypart_face3",
    "bodypart_face4",
    "bodypart_face5",
    "bodypart_face6",
    "bodypart_face7",
    "bodypart_face8",
    "bodypart_face9",
    "bodypart_hair0",
    "bodypart_hair1",
    "bodypart_hair10",
    "bodypart_hair11",
    "bodypart_hair12",
    "bodypart_hair13",
    "bodypart_hair14",
    "bodypart_hair15",
    "bodypart_hair16",
    "bodypart_hair17",
    "bodypart_hair18",
    "bodypart_hair19",
    "bodypart_hair2",
    "bodypart_hair20",
    "bodypart_hair21",
    "bodypart_hair22",
    "bodypart_hair23",
    "bodypart_hair24",
    "bodypart_hair25",
    "bodypart_hair26",
    "bodypart_hair27",
    "bodypart_hair3",
    "bodypart_hair4",
    "bodypart_hair5",
    "bodypart_hair6",
    "bodypart_hair7",
    "bodypart_hair8",
    "bodypart_hair9",
    "bodypart_hat0",
    "bodypart_hat1",
    "bodypart_hat10",
    "bodypart_hat11",
    "bodypart_hat12",
    "bodypart_hat13",
    "bodypart_hat14",
    "bodypart_hat15",
    "bodypart_hat16",
    "bodypart_hat17",
    "bodypart_hat18",
    "bodypart_hat19",
    "bodypart_hat2",
    "bodypart_hat20",
    "bodypart_hat21",
    "bodypart_hat22",
    "bodypart_hat23",
    "bodypart_hat24",
    "bodypart_hat25",
    "bodypart_hat26",
    "bodypart_hat27",
    "bodypart_hat3",
    "bodypart_hat4",
    "bodypart_hat5",
    "bodypart_hat6",
    "bodypart_hat7",
    "bodypart_hat8",
    "bodypart_hat9",
    "bodypart_legs1",
    "bodypart_legs10",
    "bodypart_legs11",
    "bodypart_legs12",
    "bodypart_legs13",
    "bodypart_legs14",
    "bodypart_legs15",
    "bodypart_legs16",
    "bodypart_legs17",
    "bodypart_legs18",
    "bodypart_legs19",
    "bodypart_legs2",
    "bodypart_legs20",
    "bodypart_legs21",
    "bodypart_legs22",
    "bodypart_legs23",
    "bodypart_legs24",
    "bodypart_legs25",
    "bodypart_legs26",
    "bodypart_legs27",
    "bodypart_legs3",
    "bodypart_legs4",
    "bodypart_legs5",
    "bodypart_legs6",
    "bodypart_legs7",
    "bodypart_legs8",
    "bodypart_legs9",
    "bodypart_torso1",
    "bodypart_torso10",
    "bodypart_torso11",
    "bodypart_torso12",
    "bodypart_torso13",
    "bodypart_torso14",
    "bodypart_torso15",
    "bodypart_torso16",
    "bodypart_torso17",
    "bodypart_torso18",
    "bodypart_torso19",
    "bodypart_torso2",
    "bodypart_torso20",
    "bodypart_torso21",
    "bodypart_torso22",
    "bodypart_torso23",
    "bodypart_torso24",
    "bodypart_torso25",
    "bodypart_torso26",
    "bodypart_torso27",
    "bodypart_torso3",
    "bodypart_torso4",
    "bodypart_torso5",
    "bodypart_torso6",
    "bodypart_torso7",
    "bodypart_torso8",
    "bodypart_torso9",
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
    "buff_permanent_double_damage",
    "buff_permanent_immune_to_cold",
    "buff_permanent_immune_to_fire",
    "buff_permanent_immune_to_negation",
    "buff_permanent_immune_to_poison",
    "buff_permanent_immune_to_teleport_attack",
    "buff_permanent_immune_to_water",
    "buff_permanent_missile_protection",
    "buff_permanent_multiplicity",
    "buff_permanent_raging",
    "buff_permanent_slime_protection",
    "buff_permanent_slippery",
    "buff_permanent_undead_protection",
    "buff_permanent_vorpal",
    "buff_status_full",
    "buff_temporary_floating",
    "buff_temporary_hasted",
    "buff_temporary_immune_to_fire",
    "buff_temporary_invisible",
    "buff_temporary_telepathy",
    "carcas_creeper",
    "centipede",
    "chasm1",
    "cheesecake",
    "cherry",
    "chest1",
    "chest2",
    "chicken",
    "chocolate_bar",
    "cleaner",
    "cloak_fire",
    "cloak_fire_carry",
    "cloak_protection",
    "cloak_protection_carry",
    "cloak_slime",
    "cloak_slime_carry",
    "cloak_stone",
    "cloak_stone_carry",
    "coffin_mob",
    "cookie",
    "corridor1",
    "corridor2",
    "crab_sewer",
    "crystal1",
    "crystal2",
    "crystal3",
    "crystal4",
    "crystal5",
    "crystal6",
    "crystal7",
    "crystal_explosion",
    "cthulite",
    "cursor",
    "cursor_hazard",
    "cursor_hazard_path",
    "cursor_path",
    "cursor_select",
    "cursor_select_fail",
    "cursor_select_fail_path",
    "cursor_select_path",
    "custardpie",
    "cutlass",
    "cutlass_carry",
    "cutlass_swing",
    "cyclops",
    "dagger",
    "dagger_carry",
    "dagger_swing",
    "dart",
    "dart_confusion",
    "dart_metal",
    "dart_paralysis",
    "dart_poison",
    "death_hornet",
    "debuff_status_blinded",
    "debuff_status_confused",
    "debuff_status_entranced",
    "debuff_status_hungry",
    "debuff_status_necrotized",
    "debuff_status_paralysis",
    "debuff_status_poisoned",
    "debuff_status_starving",
    "debuff_status_stuck",
    "debuff_temporary_immolation",
    "debuff_temporary_ooze",
    "debuff_temporary_slow",
    "debug_path",
    "deep_water",
    "demon_fire",
    "descend_sewer1",
    "descend_sewer2",
    "descend_sewer3",
    "descend_sewer4",
    "descend_sewer5",
    "dirt1",
    "dirt2",
    "dirt3",
    "dog",
    "dogman",
    "door_metal",
    "door_secret",
    "door_wood",
    "double_shovel",
    "double_shovel_carry",
    "double_shovel_swing",
    "duck1",
    "duck2",
    "duck3",
    "durian",
    "eel",
    "eggs",
    "electric_eel",
    "enchantstone",
    "ettin",
    "exit1",
    "explosion_cold",
    "explosion_destroy_floor",
    "explosion_destroy_wall",
    "explosion_fire",
    "explosion_major",
    "explosion_shattering",
    "fire",
    "firefox",
    "fish",
    "flagon_ale",
    "flameskull",
    "fleshbee",
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
    "floor_ice1",
    "floor_lava1",
    "floor_red_blood1",
    "floor_red_blood2",
    "floor_red_blood3",
    "floor_red_blood4",
    "floor_red_blood5",
    "floor_red_blood6",
    "floor_red_blood7",
    "floor_red_blood8",
    "foliage",
    "foliage_large",
    "foliage_sickly",
    "foliage_sickly_large",
    "four_leaf_clover",
    "frog",
    "fungus_edible_1",
    "fungus_edible_10",
    "fungus_edible_11",
    "fungus_edible_12",
    "fungus_edible_13",
    "fungus_edible_14",
    "fungus_edible_15",
    "fungus_edible_16",
    "fungus_edible_17",
    "fungus_edible_18",
    "fungus_edible_2",
    "fungus_edible_3",
    "fungus_edible_4",
    "fungus_edible_5",
    "fungus_edible_6",
    "fungus_edible_7",
    "fungus_edible_8",
    "fungus_edible_9",
    "fungus_healing",
    "fungus_poison_1",
    "fungus_poison_10",
    "fungus_poison_11",
    "fungus_poison_12",
    "fungus_poison_13",
    "fungus_poison_14",
    "fungus_poison_15",
    "fungus_poison_16",
    "fungus_poison_17",
    "fungus_poison_18",
    "fungus_poison_2",
    "fungus_poison_3",
    "fungus_poison_4",
    "fungus_poison_5",
    "fungus_poison_6",
    "fungus_poison_7",
    "fungus_poison_8",
    "fungus_poison_9",
    "fungus_withered_1",
    "fungus_withered_10",
    "fungus_withered_11",
    "fungus_withered_12",
    "fungus_withered_13",
    "fungus_withered_14",
    "fungus_withered_15",
    "fungus_withered_16",
    "fungus_withered_17",
    "fungus_withered_18",
    "fungus_withered_2",
    "fungus_withered_3",
    "fungus_withered_4",
    "fungus_withered_5",
    "fungus_withered_6",
    "fungus_withered_7",
    "fungus_withered_8",
    "fungus_withered_9",
    "gargoyle_baby",
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
    "gherkin",
    "ghost",
    "ghost_explosion",
    "ghost_minion",
    "ghost_mob",
    "ginger",
    "gloat",
    "gnoll",
    "gnoll_pack",
    "gnome_all",
    "gnome_dwarf",
    "gnome_knight",
    "gnome_rock",
    "gnome_thief",
    "goat_battle",
    "goat_demon",
    "gold1",
    "gold2",
    "gold3",
    "gold4",
    "gold5",
    "gold6",
    "goldfish",
    "golem_cement",
    "golem_flesh",
    "grass_dry",
    "grass_dry_dead",
    "grass_dry_trampled",
    "grass_wet1",
    "grass_wet2",
    "grass_wet3",
    "grass_wet4",
    "grass_wet5",
    "grass_wet6",
    "grass_wet_trampled1",
    "grass_wet_trampled2",
    "grass_wet_trampled3",
    "grass_wet_trampled4",
    "grass_wet_trampled5",
    "grass_wet_trampled6",
    "greenpepper",
    "green_splatter",
    "hellpup",
    "holy_water",
    "honey",
    "horseshoe",
    "hotsauce",
    "iceman",
    "jackalope",
    "key",
    "key_crystal",
    "key_golden",
    "key_pair",
    "key_penta",
    "kraken",
    "kraken_tentacle",
    "laser_discord",
    "laser_energy",
    "laser_entrancement",
    "laser_haste",
    "laser_healing",
    "laser_lightning",
    "laser_lightning_fork",
    "laser_magic_effect",
    "laser_negation",
    "laser_slowness",
    "lava",
    "lava_ant",
    "leech_giant",
    "lemonpie",
    "mace",
    "mace_carry",
    "mace_swing",
    "magical_effect",
    "mantisman",
    "map_beast",
    "map_treasure",
    "meatfairy",
    "medal_of_valor",
    "melon1",
    "melon2",
    "mimic_awake",
    "mimic_sleeping",
    "mob_explosion",
    "molekin",
    "moresquito",
    "msg",
    "mummy",
    "mummy_necro",
    "mummy_pack",
    "murder_bunny",
    "narhornet",
    "ogre",
    "ogre_totem",
    "onion",
    "ooze",
    "orange_slices",
    "peach",
    "pickled_eggs",
    "pickledeyes",
    "pike",
    "pike_carry",
    "pike_swing",
    "pillar",
    "pineapple",
    "piranha",
    "piranha_giant",
    "piranha_giant_pack",
    "piranha_pack",
    "player1",
    "player2",
    "portable_hole",
    "portal",
    "potato",
    "potion_confusion",
    "potion_darkness",
    "potion_descent",
    "potion_effect",
    "potion_fire_immunity",
    "potion_haste",
    "potion_immolation",
    "potion_invigoration",
    "potion_invisibility",
    "potion_levitation",
    "potion_life",
    "potion_ooze",
    "potion_poison",
    "potion_strength",
    "potion_telepathy",
    "pottedmeat",
    "pretzel",
    "projectile_acid",
    "projectile_cold",
    "projectile_dart",
    "projectile_dart_confusion",
    "projectile_dart_metal",
    "projectile_dart_paralysis",
    "projectile_dart_poison",
    "projectile_fire",
    "projectile_magical_effect",
    "projectile_magic_missile",
    "projectile_poison",
    "projectile_rock",
    "projectile_web",
    "pudding_baby",
    "pudding_parent",
    "pyrolizard",
    "rat_giant",
    "rat_large",
    "reaper",
    "redpepper",
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
    "roastchicken",
    "rock",
    "rock1",
    "rock2",
    "rock_ice1",
    "rock_lava1",
    "salami",
    "salmon",
    "sardines",
    "scorpion",
    "scorpion_colossal",
    "scorpion_death",
    "scythe",
    "scythe_carry",
    "scythe_swing",
    "sentry_orb_energy",
    "sentry_orb_fire",
    "sewer_wall",
    "sheep",
    "shield_eagle",
    "shield_eagle_carry",
    "shield_obsidian",
    "shield_obsidian_carry",
    "shield_tower",
    "shield_tower2",
    "shield_tower2_carry",
    "shield_tower_carry",
    "shield_wooden",
    "shield_wooden_carry",
    "shield_woodon",
    "shield_woodon_carry",
    "shovel",
    "shovel_carry",
    "shovel_swing",
    "sirloin",
    "skeleton",
    "skel_fire",
    "skel_giant",
    "skel_minion",
    "skel_minion_fire",
    "skel_minion_wander",
    "skel_mob",
    "skill_artful_dodging1",
    "skill_artful_dodging2",
    "skill_artful_dodging3",
    "skill_artful_dodging4",
    "skill_artful_dodging5",
    "skill_devoted_thrust1",
    "skill_devoted_thrust2",
    "skill_devoted_thrust3",
    "skill_devoted_thrust4",
    "skill_devoted_thrust5",
    "skill_devoted_thrust_effect",
    "skill_double_strike1",
    "skill_double_strike2",
    "skill_double_strike3",
    "skill_double_strike4",
    "skill_double_strike5",
    "skill_double_strike_effect",
    "skill_gold_to_health1",
    "skill_gold_to_health2",
    "skill_gold_to_health3",
    "skill_gold_to_health4",
    "skill_gold_to_health5",
    "skill_gold_to_health_effect",
    "skill_healing1",
    "skill_healing2",
    "skill_healing3",
    "skill_healing4",
    "skill_healing5",
    "skill_intimidating_strength1",
    "skill_intimidating_strength2",
    "skill_intimidating_strength3",
    "skill_intimidating_strength4",
    "skill_intimidating_strength5",
    "skill_iron_defense1",
    "skill_iron_defense2",
    "skill_iron_defense3",
    "skill_iron_defense4",
    "skill_iron_defense5",
    "skill_power_attack1",
    "skill_power_attack2",
    "skill_power_attack3",
    "skill_power_attack4",
    "skill_power_attack5",
    "skill_primal_rage1",
    "skill_primal_rage2",
    "skill_primal_rage3",
    "skill_primal_rage4",
    "skill_primal_rage5",
    "skill_primal_rage_effect",
    "skillstone",
    "skill_super_health1",
    "skill_super_health2",
    "skill_super_health3",
    "skill_super_health4",
    "skill_super_health5",
    "skill_vampiric_touch1",
    "skill_vampiric_touch2",
    "skill_vampiric_touch3",
    "skill_vampiric_touch4",
    "skill_vampiric_touch5",
    "slime_baby",
    "slime_parent",
    "sluud",
    "sluud_dark",
    "sluud_pack",
    "small_fire",
    "smoke",
    "snake_asp",
    "snake_dreadfire",
    "snake_viper",
    "somekindofmeat",
    "spectral_blade",
    "spectral_blade_companion",
    "spectral_blade_minion",
    "spectral_mob",
    "spellbook1",
    "spellbook2",
    "spellbook3",
    "spellbook4",
    "spellbook5",
    "spell_of_beckoning",
    "spell_of_dominate_monst1",
    "spell_of_dominate_monst2",
    "spell_of_dominate_monst3",
    "spell_of_dominate_monst4",
    "spell_of_dominate_monst5",
    "spell_of_hasted",
    "spell_of_holding",
    "spell_of_holding_barrier",
    "spell_of_magic_missile",
    "spell_of_protection",
    "spell_of_protection_barrier",
    "spell_of_repulsion",
    "spell_of_sanctuary",
    "spell_of_sanctuary_barrier",
    "spell_of_slowness",
    "spell_of_summon_food",
    "spell_of_summon_monst1",
    "spell_of_summon_monst2",
    "spell_of_summon_monst3",
    "spell_of_summon_monst4",
    "spell_of_summon_monst5",
    "spell_of_summon_rock",
    "spider_bone",
    "spider_brown",
    "spider_flux",
    "spider_giant",
    "spider_onyx_widow",
    "spider_para",
    "spiderweb",
    "staff_beckoning",
    "staff_beckoning_carry",
    "staff_blinking",
    "staff_blinking_carry",
    "staff_cold",
    "staff_cold_carry",
    "staff_conjuration",
    "staff_conjuration_carry",
    "staff_descent",
    "staff_descent_carry",
    "staff_descent_laser",
    "staff_discord",
    "staff_discord_carry",
    "staff_domination",
    "staff_domination_carry",
    "staff_energy",
    "staff_energy_carry",
    "staff_energy_laser",
    "staff_entrancement",
    "staff_entrancement_carry",
    "staff_fire",
    "staff_fire_carry",
    "staff_haste",
    "staff_haste_carry",
    "staff_healing",
    "staff_healing_carry",
    "staff_holding",
    "staff_holding_carry",
    "staff_lightning",
    "staff_lightning_carry",
    "staff_negation",
    "staff_negation_carry",
    "staff_obstruction",
    "staff_obstruction_carry",
    "staff_plenty",
    "staff_plenty_carry",
    "staff_poison",
    "staff_poison_carry",
    "staff_projectile_cold",
    "staff_projectile_fire",
    "staff_projectile_obstruction",
    "staff_projectile_poison",
    "staff_protection",
    "staff_protection_carry",
    "staff_repulsion",
    "staff_repulsion_carry",
    "staff_sanctuary",
    "staff_sanctuary_carry",
    "staff_shattering",
    "staff_shattering_carry",
    "staff_shattering_laser",
    "staff_slowness",
    "staff_slowness_carry",
    "staff_tunneling",
    "staff_tunneling_carry",
    "staff_tunneling_laser",
    "steak",
    "steam",
    "strawberry",
    "sushi1",
    "sushi2",
    "sword",
    "sword_carry",
    "sword_darkness",
    "sword_darkness_carry",
    "sword_darkness_swing",
    "sword_draining",
    "sword_draining_carry",
    "sword_draining_swing",
    "sword_duck_summoning",
    "sword_duck_summoning_carry",
    "sword_duck_summoning_swing",
    "sword_holy",
    "sword_holy_carry",
    "sword_holy_swing",
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
    "tentacle_horror",
    "tentacleye",
    "the_grid",
    "thunderstone",
    "thylacine",
    "tomato",
    "torch",
    "trap_blinded",
    "trap_confusion",
    "trap_dart",
    "trap_dart_poison",
    "trap_monster",
    "trap_paralysis",
    "trap_pressure_plate_gas1",
    "trap_pressure_plate_gas2",
    "trap_pressure_plate_gas3",
    "trap_pressure_plate_gas4",
    "troll_fire",
    "troll_stone",
    "turnip",
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
    "warhammer",
    "warhammer_carry",
    "warhammer_swing",
    "water",
    "waterlemon",
    "webball",
    "wine",
    "wooden_cross",
    "wooden_cross_carry",
    "yeti",
    "zoblin",
    "zoblin_minion",
    "zob_mob",
    "zorb_all",
    "zorb_captain",
    "zorb_eldster",
    "zorb_necro",
    "zorb_pack",
    "zorb_pirate",
    "zorb_priest",
    "zorb_single",
    "zorb_soldier",
    "zorb_totem",
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
    CON("*** Thing template not found [%s] Please edit thing_template_ids.cpp and add it. ***", tp_name.c_str());
    return;
  }

  *id_out = tp_preferred_id[ tp_name ];
}
