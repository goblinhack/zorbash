//
// Copyright goblinhack@gmail.com
//
// Converted from python/things/player/player.py
//

#include "my_native.hpp"

namespace mod_things_player_player {

static std::string random_title(void);
static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage);
static void on_you_nat_attack_attempt(uint32_t me, int x, int y);
static void on_born(uint32_t me, int x, int y);
static void on_fall_begin(uint32_t me, int x, int y);
static void on_death(uint32_t me, int x, int y);
static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name, const std::string &title);
static void init(void);

static std::string random_title(void)
{
  int a = 0;
  int b = 0;
  int c = 0;
  std::vector< std::string > names1;
  std::vector< std::string > names2;
  std::vector< std::string > title;
  title = std::vector< std::string >{"ser", "ser"};
  names1 = std::vector< std::string >{
      "dead",
      "disco",
      "giant",
      "blood",
      "swift",
      "dim",
      "bright",
      "wolf",
      "moor",
      "ape",
      "sorrow",
      "goblin",
      "holy",
      "basil",
      "york",
      "short",
      "tall",
      "wide",
      "slim",
    };
  names2 = std::vector< std::string >{
      "pool",
      "smith",
      "spike",
      "mercy",
      "thirst",
      "mare",
      "ness",
      "anvil",
      "max",
      "dragon",
      "heart",
      "bane",
      "rose",
      "pond",
      "scum",
      "bob",
      "hack",
      "might",
      "grace",
      "brush",
      "wood",
      "worm",
      "able",
      "rock",
      "shock",
      "fire",
      "iceice",
    };
  a = my::pcg_random_inclusive(0, (((int) title.size()) - 1));
  b = my::pcg_random_inclusive(0, (((int) names1.size()) - 1));
  c = my::pcg_random_inclusive(0, (((int) names2.size()) - 1));
  return (((title.at(a) + " ") + names1.at(b)) + names2.at(c));
}

static void on_hit_and_still_alive(uint32_t me, uint32_t hitter, uint32_t real_hitter, int x, int y, int crit, int damage)
{
  if ((damage <= 5)) {
    my::thing_sound_play_channel(me, CHANNEL_IMPACT, ((std::string("player_hit") + std::to_string(my::non_pcg_random_inclusive(1, 4)))).c_str());
  } else {
    my::thing_sound_play_channel(me, CHANNEL_IMPACT, "player_hit5");
  }
}

static void on_you_nat_attack_attempt(uint32_t me, int x, int y)
{
  my::sound_play("player_punch");
}

static void on_born(uint32_t me, int x, int y)
{
}

static void on_fall_begin(uint32_t me, int x, int y)
{
  my::thing_msg(me, "Aaargh!");
  my::thing_sound_play_channel(me, CHANNEL_IMPACT, "fall");
}

static void on_death(uint32_t me, int x, int y)
{
  int a = 0;
  std::vector< std::string > messages;
  messages = std::vector< std::string >{
      "A grave is a place where the dead are laid to await the coming of the medical student - Ambrose Bierce.",
      "All tragedies are finished by a death, all comedies by a marriage - Lord Byron.",
      "Always go to other people's funerals, otherwise they won't come to yours - Yogi Berra.",
      "At my age flowers scare me - George Burns.",
      "Death is a delightful hiding place for weary men - Herodotus.",
      "Death is a very narrow theme, but it reaches a wide audience - Socrates.",
      "Death is just nature's way of telling you to slow down - Dick Sharples.",
      "Death was nature's way of telling you to slow down - Terry Pratchett.",
      "Don't send me flowers when I'm dead. If you like me, send them while I'm alive - Brian Clough.",
      "Dying is a very dull, dreary affair, and my advice to you is to have nothing to do with it - Somerset Maugham.",
      "Dying is easy; it's living that scares me to death - Annie Lennox.",
      "Either he's dead or my watch has stopped - Groucho Marx.",
      "Fear of death increases in exact proportion to increase in wealth - Ernest Hemingway.",
      "For three days after death, hair and nails continue to grow but phone calls taper off - Johnny Carson.",
      "He is one of those people who would be enormously improved by death - HH Munro.",
      "He was a great patriot, a humanitarian, a loyal friend, provided of course, he really is dead - Voltaire.",
      "I am prepared to meet my maker. Whether my maker is prepared to meet me is another matter - Winston Churchill.",
      "I can't afford to die; I'd lose too much money - George Burns.",
      "I do not fear death. I had been dead for billions of years before I was born and had not suffered the slightest inconvenience - Mark Twain.",
      "I don't mind dying, the trouble is you feel so stiff the next day - George Axlerod.",
      "I don't want to achieve immortality through my work, I want to achieve it through not dying - Woody Allen.",
      "If you die in an elevator, be sure to push the UP button - Sam Levenson.",
      "I get my daily paper, look at the obituaries page and if I'm not there I carry on as usual - Mark Twain.",
      "I have never killed a man, but I have read many obituaries with great pleasure - Clarence Darrow.",
      "I intend to live forever or die trying - Groucho Marx.",
      "I like sleeping; it's like death without the commitment - Unknown.",
      "I'm always relieved when someone is delivering a eulogy and I realize that I'm listening to it - George Carlin.",
      "Immortality... a fate worse than death - Edgar A Shoaff.",
      "I'm not afraid to die, I just don't want to be there when it happens - Woody Allen.",
      "I'm very pleased to be here. At my age I'm very pleased to be anywhere - George Burns.",
      "In this world, nothing can be certain, except death and taxes - Benjamin Franklin.",
      "It's funny how most people love the dead, once you're dead your made for life - Jimi Hendrix.",
      "I've looked that old scoundrel death in the eyes many times but this time I think he has me on the ropes - Douglas MacArthur.",
      "Life is hard. Then you die. Then they throw dirt in your face. Then the worms eat you. Be grateful if it happens in that order - David Gerrold.",
      "Millions long for immortality who don't know what to do with themselves on a rainy Sunday afternoon - Susan Ertz.",
      "My luck is so bad that if I bought a cemetery, people would stop dying - Ed Furgol.",
      "On the plus side, death is one of the few things that can be done as easily lying down - Woody Allen.",
      "Self-decapitation is an extremely difficult, not to say dangerous, thing to attempt - WS Gilbert.",
      "Some men are alive simply because it is against the law to kill them - EW Howe.",
      "The reports of my death have been greatly exaggerated - Mark Twain.",
      "The trouble with quotes about death is that all of them are made by people who are still alive - Joshua Burns.",
      "When I came back to Dublin I was court-martialed in my absence and sentenced to death in my absence, so I said they could shoot me in my absence - Brendan Behan.",
      "When I die, I hope to go to heaven, whatever the hell that is - Ayn Rand.",
      "When I die, I'm leaving my body to science fiction - Steven Wright.",
      "When I die, I want my body to be donated for research, but more specifically, to a scientist who is working on bringing dead bodies back to life - Nikhil Saluja.",
      "You know you're old when the candles cost more than the cake - Bob Hope.",
      "And I thought you were tough...",
      "Are you paid to play this\? You shouldn't be.",
      "Awful. Just awful.",
      "Believe in yourself more. Someone has to.",
      "Congratulations, you are dead!",
      "Congratulations, you died!",
      "Dead, what\? When\?",
      "Don't give up. But please give up on this game.",
      "Don't play games as a career.",
      "Epic fail.",
      "Goodbye cruel world.",
      "Good try I suppose.",
      "Hmm you seem to be dead.",
      "I had such high hopes for you.",
      "I hate to inquire, but are you dead\?",
      "I have a goat plays better than you.",
      "In this dungeon the only certainty is death...",
      "Is that the best you could do\?",
      "Is this your first game. Ever\?",
      "Just give me a minute to recover my breath...",
      "Just stop playing. You'll never win.",
      "Let your pet pigeon play next time instead.",
      "Life was hard. Take it easy now...",
      "LOL.",
      "My pet kakapo plays better than that.",
      "My pet pigeon could do better.",
      "Not sure how that happened. It was going so well...",
      "Sinner, you are expired.",
      "Stick to knitting.",
      "Stick to sudoko.",
      "That could have gone a lot worse...",
      "The Gods are disappointed in you...",
      "This isn't pong you know\?",
      "Time to rest in the fjords with your parrot!",
      "Try 3D Monster Maze instead.",
      "Try tetris instead\?",
      "Was a noble pursuit.",
      "Welcome to the afterlife!",
      "Well, that could have been worse.",
      "Worst game ever.",
      "You are as lifeless as a Norweigian blue.",
      "You are at rest, sort of.",
      "You are in a better place.",
      "You are off to the happy hunting ground.",
      "You are profoundly and very dead.",
      "You are pushing up ze daisies now.",
      "You are six feet under.",
      "You bade farewell to life.",
      "You bit the dust.",
      "You bought the farm.",
      "You came to a sticky and pointless end.",
      "You checked out.",
      "You croaked it.",
      "You crossed the great divide.",
      "You died horribly.",
      "You disssapoint me.",
      "You fell off the perch.",
      "You find yourself sadly departed.",
      "You fought bravely...",
      "You gave up the ghost.",
      "You had your final summons.",
      "You have gone to a better place.",
      "You hear the sound of monsters laughing...",
      "You joined the choir invisible.",
      "You kicked the bucket.",
      "You left the mortal coil.",
      "You paid the piper.",
      "You passed on.",
      "You popped your clogs.",
      "You reached your final destination.",
      "Your god told you to slow down.",
      "Your number was up.",
      "You seem to be suddenly expired.",
      "You slipped away.",
      "You snuffed it.",
      "You tried. Well done. I really mean it. Maybe.",
      "You wave farewell to the monsters.",
      "You went to meet your maker. It was not impressed.",
      "You went to the restaurant at the end of the universe.",
      "You went to the spirit in the sky.",
    };
  a = my::pcg_random_inclusive(0, (((int) messages.size()) - 1));
  my::topcon(((std::string(messages.at(a)))).c_str());
}

static void tp_init(const std::string &name, const std::string &text_long_name, const std::string &text_short_name, const std::string &title)
{
  int delay = 0;
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->aggression_pct_set(25);
  self->ai_detect_secret_doors_set(true);
  self->ai_resent_count_set(20);
  self->ai_wanderer_set(true);
  self->attack_undead_set(true);
  self->capacity_height_set(20);
  self->capacity_width_set(20);
  self->chance_d1000_shooting_avoid_friends_set(90);
  self->chance_d1000_shove_set(50);
  self->collision_check_set(true);
  self->collision_hit_priority_set(20);
  self->collision_hit_priority_set(6);
  self->distance_avoid_set(3);
  self->distance_spell_cast_set(7);
  self->distance_throw_set(5);
  self->distance_vision_set(10);
  self->dmg_limited_per_tick_set(true);
  self->dmg_nat_att_dice_set("1d3");
  self->dmg_nat_att_type_set("punch");
  self->environ_dislikes_acid_set(100);
  self->environ_dislikes_fire_set(10);
  self->environ_dislikes_poison_set(100);
  self->gfx_anim_use_set("attack_punch");
  self->gfx_ascii_shown_set(true);
  self->gfx_pixelart_animated_can_hflip_set(true);
  self->gfx_pixelart_animated_set(true);
  self->gfx_pixelart_bounce_on_move_set(true);
  self->gfx_pixelart_flickers_set(true);
  self->gfx_pixelart_reflection_set(true);
  self->gfx_pixelart_show_outlined_set(true);
  self->gfx_pixelart_show_square_outlined_set(true);
  self->gfx_pixelart_submergible_set(true);
  self->gfx_pixelart_wobbles_when_hit_set(true);
  self->health_initial_dice_set("100");
  self->hunger_clock_tick_freq_set(10);
  self->hunger_is_hunger_level_hungry_at_pct_set(50);
  self->hunger_is_hunger_level_starving_at_pct_set(10);
  self->is_able_to_attack_mobs_set(true);
  self->is_able_to_attack_totems_set(true);
  self->is_able_to_be_surprised_set(true);
  self->is_able_to_be_teleported_set(true);
  self->is_able_to_break_down_doors_set(true);
  self->is_able_to_break_out_of_crystal_set(true);
  self->is_able_to_break_out_of_ice_set(true);
  self->is_able_to_break_out_of_webs_set(true);
  self->is_able_to_change_levels_set(true);
  self->is_able_to_collect_keys_set(true);
  self->is_able_to_enchant_items_set(true);
  self->is_able_to_fall_set(true);
  self->is_able_to_freeze_set(true);
  self->is_able_to_jump_set(true);
  self->is_able_to_learn_skills_set(true);
  self->is_able_to_lunge_set(true);
  self->is_able_to_move_diagonally_set(true);
  self->is_able_to_open_doors_set(true);
  self->is_able_to_rest_set(true);
  self->is_able_to_shove_set(true);
  self->is_able_to_spell_cast_set(true);
  self->is_able_to_tire_set(true);
  self->is_able_to_use_amulet_set(true);
  self->is_able_to_use_armor_set(true);
  self->is_able_to_use_boots_set(true);
  self->is_able_to_use_cloak_set(true);
  self->is_able_to_use_gauntlet_set(true);
  self->is_able_to_use_helmet_set(true);
  self->is_able_to_use_rings_set(true);
  self->is_able_to_use_shield_set(true);
  self->is_able_to_use_staffs_set(true);
  self->is_able_to_use_weapons_set(true);
  self->is_air_breather_set(true);
  self->is_attackable_by_monst_set(true);
  self->is_biome_chasms_set(true);
  self->is_biome_dungeon_set(true);
  self->is_biome_ice_set(true);
  self->is_biome_lava_set(true);
  self->is_biome_sewer_set(true);
  self->is_biome_swamp_set(true);
  self->is_bleeder_set(true);
  self->is_buffable_set(true);
  self->is_burnable_set(true);
  self->is_corpse_on_death_set(true);
  self->is_corpse_with_bones_set(true);
  self->is_crushable_set(true);
  self->is_described_in_leftbar_set(true);
  self->is_described_when_hovering_over_set(true);
  self->is_eater_of_food_set(true);
  self->is_exit_finder_set(true);
  self->is_explorer_set(true);
  self->is_humanoid_set(true);
  self->is_immune_to_spell_of_sanctuary_set(true);
  self->is_interesting_set(true);
  self->is_item_collector_set(true);
  self->is_living_set(true);
  self->is_loggable_set(true);
  self->is_meat_set(true);
  self->is_moveable_set(true);
  self->is_player_set(true);
  self->is_red_blooded_set(true);
  self->is_shootable_set(true);
  self->is_shovable_set(true);
  self->is_tickable_set(true);
  self->jump_distance_set(2);
  self->light_dist_set(10);
  self->magic_set(10);
  self->move_speed_set(100);
  self->noise_additional_on_jump_end_set(20);
  self->noise_decibels_hearing_set(30);
  self->noise_on_moving_set(50);
  self->nutrition_dice_set("2d10");
  self->on_born_do_set("player.on_born()");
  self->on_death_do_set("player.on_death()");
  self->on_fall_begin_do_set("player.on_fall_begin()");
  self->on_hit_and_still_alive_do_set("player.on_hit_and_still_alive()");
  self->on_you_nat_attack_attempt_do_set("player.on_you_nat_attack_attempt()");
  self->stamina_set(100);
  self->stat_att_penalty_when_idle_max_set(0);
  self->stat_att_penalty_when_idle_set(0);
  self->stat_att_penalty_when_in_deep_water_set(5);
  self->stat_att_penalty_when_in_shallow_water_set(2);
  self->stat_att_penalty_when_stuck_max_set(2);
  self->stat_att_penalty_when_stuck_set(1);
  self->stat_def_penalty_when_idle_max_set(5);
  self->stat_def_penalty_when_idle_set(5);
  self->stat_def_penalty_when_in_deep_water_set(5);
  self->stat_def_penalty_when_in_shallow_water_set(2);
  self->stat_def_penalty_when_stuck_max_set(15);
  self->temperature_max_set(50);
  self->temperature_min_set(0);
  self->temperature_set(20);
  self->temperature_sensitive_set(true);
  self->temperature_sensitive_to_sudden_changes_set(true);
  self->text_a_or_an_set("the");
  self->text_pluralize_set("players");
  self->text_apostrophize_set("player's");
  self->text_description_long_set("A most noble adventurer of no particular race, gender or creed. Devoid of fear and stout of heart.");
  self->text_description_short_set("Our most noble adventurer. Press 'h' for help.");
  self->text_hits_set("hits");
  self->text_title_set(title);
  self->thing_size_set(THING_SIZE_NORMAL);
  self->tick_prio_set(MAP_TICK_PRIO_HIGH);
  self->z_depth_set(MAP_DEPTH_OBJ);
  self->z_prio_set(MAP_Z_PRIO_PLAYER_TORSO);
  delay = 900;
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_moving = true, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_moving = true, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_moving = true, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_moving = true, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_dir_left = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_dir_up = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_dir_down = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_dir_right = true});
  my::tile(self, {.tile = (name + ".1"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 1, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".2"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 2, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".3"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 3, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".4"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 4, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".5"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 5, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".6"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "pink", .delay_ms = delay, .frame = 6, .is_dir_none = true});
  my::tile(self, {.tile = (name + ".dead"), .ascii_fg_char = "@", .ascii_bg_col_name = "", .ascii_fg_col_name = "grey", .is_dead = true});
}

static void init(void)
{
  tp_init("player1", "noble warrior", "you", random_title());
}

void module_init(void)
{
  native_register("player", "on_hit_and_still_alive", 7, [](const int64_t *a) -> NativeRet { (void) a; on_hit_and_still_alive((uint32_t) a[0], (uint32_t) a[1], (uint32_t) a[2], (int) a[3], (int) a[4], (int) a[5], (int) a[6]); return NativeRet {}; });
  native_register("player", "on_you_nat_attack_attempt", 3, [](const int64_t *a) -> NativeRet { (void) a; on_you_nat_attack_attempt((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("player", "on_born", 3, [](const int64_t *a) -> NativeRet { (void) a; on_born((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("player", "on_fall_begin", 3, [](const int64_t *a) -> NativeRet { (void) a; on_fall_begin((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  native_register("player", "on_death", 3, [](const int64_t *a) -> NativeRet { (void) a; on_death((uint32_t) a[0], (int) a[1], (int) a[2]); return NativeRet {}; });
  init();
}

} // namespace mod_things_player_player
