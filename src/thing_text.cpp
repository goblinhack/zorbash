//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_sdl_proto.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"

std::string Thing::text_a_or_an(size_t max_len)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "";

  if (is_player() || is_monst()) {
    if (is_dead) {
      out += "a dead ";
    } else if (is_dying) {
      out += "a dying ";
    }
  }

  if (out == "") {
    auto prefix = tpp->text_a_or_an();
    if (prefix == "") {
      out = tpp->text_long_name();
    } else {
      out = prefix + " " + tpp->text_long_name();
    }
  } else {
    out += tpp->text_long_name();
  }

  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += ", your pet";
    }
  }

  if (max_len) {
    if (out.size() >= max_len) {
      ::abbreviate(out);
    }
  }

  return out;
}

std::string Thing::text_pluralize(size_t max_len)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);

  auto out = tpp->text_pluralize();

  if (out == "") {
    return tpp->text_long_name() + "s";
  }

  if (max_len) {
    if (out.size() >= max_len) {
      ::abbreviate(out);
    }
  }

  return out;
}

std::string Thing::text_apostrophize(size_t max_len)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);

  auto out = tpp->text_pluralize();

  if (out == "") {
    return tpp->text_long_name() + "'s";
  }

  if (max_len) {
    if (out.size() >= max_len) {
      ::abbreviate(out);
    }
  }

  return out;
}

enum {
  TEXT_INCLUDE_OWNER = 1,
  TEXT_EXCLUDE_DEATH = 2,
  TEXT_APOSTROPHIZE  = 4,
  TEXT_PLURALIZE     = 8,
};

std::string Thing::text_the(uint8_t flags)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "the ";

  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    out = "your ";
  }

  //
  // "the goblin's short sword" for example
  //
  auto t_o = top_owner();
  if (flags & TEXT_INCLUDE_OWNER) {
    out += t_o->text_apostrophize();
  }

  if (! (flags & TEXT_EXCLUDE_DEATH)) {
    if (is_player() || is_monst()) {
      if (is_dead) {
        if (is_undead()) {
          out += "extra dead ";
        } else {
          out += "dead ";
        }
      } else if (is_dying) {
        out += "dying ";
      }
    }

    if (is_frozen) {
      out += "frozen ";
    } else if (is_burnt) {
      out += "burnt ";
    } else if (tpp->charge_count() && ! charge_count()) {
      out += "spent ";
    }
  }

  //
  // Tamed?
  //
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }

  if (flags & TEXT_APOSTROPHIZE) {
    out += text_apostrophize();
  } else if (flags & TEXT_APOSTROPHIZE) {
    out += text_pluralize();
  } else {
    out += tpp->text_long_name();
  }

  if (tpp->is_spell()) {
    out += " spell";
  }

  if (tpp->is_skill()) {
    out += " skill";
  }

  return out;
}

std::string Thing::text_short_a_or_an(size_t max_len)
{
  TRACE_NO_INDENT();
  auto tpp = tp();
  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "";

  if (is_player() || is_monst()) {
    if (is_dead) {
      out += "a dead ";
    } else if (is_dying) {
      out += "a dying ";
    }
  }

  if (is_frozen) {
    out += "frozen ";
  } else if (is_burnt) {
    out += "burnt ";
  } else if (tpp->charge_count() && ! charge_count()) {
    out += "spent ";
  }

  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }

  if (out == "") {
    auto prefix = tpp->text_a_or_an();
    if (prefix == "") {
      out = tpp->text_short_name();
    } else {
      out = prefix + " " + tpp->text_short_name();
    }
  } else {
    out += tpp->text_short_name();
  }

  if (max_len) {
    if (out.size() >= max_len) {
      abbreviate(out);
    }
  }

  return out;
}

std::string Thing::text_short_the(size_t max_len)
{
  TRACE_NO_INDENT();
  auto tpp = tp();

  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out = "the ";

  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    out = "your ";
  }

  if (is_dead) {
    if (is_undead()) {
      out += "extra dead ";
    } else if (is_dying) {
      out += "dying ";
    } else {
      out += "dead ";
    }
  }

  //
  // Tamed?
  //
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }

  out += tpp->text_short_name();

  if (max_len) {
    if (out.size() >= max_len) {
      abbreviate(out);
    }
  }

  return out;
}

std::string Thing::text_short_The(size_t max_len)
{
  TRACE_NO_INDENT();
  auto out = text_short_the(max_len);
  out[ 0 ] = toupper(out[ 0 ]);
  return out;
}

std::string Thing::text_A_or_An(size_t max_len)
{
  TRACE_NO_INDENT();
  auto out = text_short_a_or_an(max_len);
  out[ 0 ] = toupper(out[ 0 ]);
  return out;
}

//
// foo bar -> Foo Bar
//
std::string Thing::text_short_capitalized(size_t max_len)
{
  TRACE_NO_INDENT();
  std::string out = text_short_name(max_len);

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}

std::string Thing::text_long_capitalized(size_t max_len)
{
  TRACE_NO_INDENT();
  std::string out = text_long_name(max_len);

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}

std::string Thing::text_short_and_state_capitalized(size_t max_len)
{
  TRACE_NO_INDENT();
  auto tpp = tp();

  verify(MTYPE_THING, this);
  verify(MTYPE_TP, tpp);
  if (unlikely(! tpp)) {
    return ("<no name>");
  }

  std::string out;

  if (is_player() || is_monst()) {
    if (is_dead) {
      if (is_undead()) {
        out += "extra dead ";
      } else {
        out += "dead ";
      }
    } else if (is_dying) {
      out += "dying ";
    }
  }

  if (is_frozen) {
    out += "frozen ";
  } else if (is_burnt) {
    out += "burnt ";
  } else if (tpp->charge_count() && ! charge_count()) {
    out += "spent ";
  }

  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }

  out += text_short_name();

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  if (max_len) {
    if (out.size() >= max_len) {
      abbreviate(out);
    }
  }

  return out;
}

std::string Thing::text_long_and_state_capitalized(size_t max_len)
{
  TRACE_NO_INDENT();
  std::string out;

  if (is_player() || is_monst()) {
    if (is_dead) {
      if (is_undead()) {
        out += "extra dead ";
      } else {
        out += "dead ";
      }
    } else if (is_dying) {
      out += "dying ";
    }
  }

  //
  // Tamed?
  //
  auto l = leader();
  if (l && (l == level->player)) {
    if (is_not_shown_as_a_pet()) {
      //
      // Not really a pet
      //
    } else {
      out += "pet ";
    }
  }

  out += text_long_name();

  char *b          = (char *) out.c_str();
  char *e          = b + out.size();
  char *c          = b;
  bool  word_start = true;
  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  if (max_len) {
    if (out.size() >= max_len) {
      abbreviate(out);
    }
  }

  return out;
}

void Thing::show_botcon_description(void)
{
  TRACE_NO_INDENT();
  auto text = text_description_short();

  //
  // Show mimics?
  //
  if (pcg_random_allowed) {
    if (is_mimic()) {
      if (level->player) {
        if (d20() < level->player->stat_psi_total()) {
          text += " %%fg=orange$(I have a bad feeling about this)%%fg=reset$";
        }
      }
    }
  }

  bool skip_showing_keys_to_use = true;
  switch (game->state) {
    case Game::STATE_CHOOSING_LEVEL : return;
    case Game::STATE_NORMAL : skip_showing_keys_to_use = false; break;
    case Game::STATE_INVENTORY : // Currently managing inventory
      skip_showing_keys_to_use = false;
      break;
    case Game::STATE_COLLECTING_ITEMS : // Collecting en masse from the level
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_ENCHANTING_ITEMS : skip_showing_keys_to_use = true; break;
    case Game::STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_CHOOSING_SKILLS : // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_CHOOSING_SPELLS : // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_LOAD_MENU : skip_showing_keys_to_use = true; break;
    case Game::STATE_SAVE_MENU : skip_showing_keys_to_use = true; break;
    case Game::STATE_QUIT_MENU : skip_showing_keys_to_use = true; break;
    case Game::STATE_KEYBOARD_MENU : skip_showing_keys_to_use = true; break;
    default : ERR("Unhandled game state"); break;
  }

  //
  // Want to show that you can drop a bag if you select it.
  //
  if (immediate_owner()) {
    if (is_droppable()) {
      text += " %%fg=orange$" + ::to_string(game->config.key_drop) + "%%fg=reset$ to drop.";
    }
  }

  //
  // Unless a bag.
  //
  if (skip_showing_keys_to_use) {
    if (text.empty()) {
      return;
    }

    BOTCON("%s", text.c_str());
    return;
  }

  if (is_weapon()) {
    text += " Damage %%fg=red$" + tp()->dmg_melee_dice_str() + "%%fg=reset$.";
  }

  if (is_poisonous_danger_level()) {
    text += " Poisons. ";
  }

  if (is_necrotic_danger_level()) {
    text += " Necrotic. ";
  }

  if (immediate_owner()) {
    if (is_usable()) {
      if (is_food()) {
        text += " %%fg=green$" + ::to_string(game->config.key_eat) + "%%fg=reset$ to eat.";
      } else if (is_potion()) {
        text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to drink.";
      } else if (is_staff()) {
        text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to use.";
      } else if (is_ring()) {
        text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to wear.";
      } else {
        text += " %%fg=cyan$" + ::to_string(game->config.key_use) + "%%fg=reset$ to use.";
      }
    }

    if (is_throwable() && ! is_auto_throw()) {
      text += " %%fg=purple$" + ::to_string(game->config.key_throw) + "%%fg=reset$ to throw.";
    }

    if (is_bag_item_container()) {
      text += " Use mouse to drag items.";
    }
  }

  if (is_on_fire()) {
    if (is_alive_monst() || is_player()) {
      text += " %%fg=red$Is on fire!";
    }
  }

  if (! is_hidden) {
    if (is_collectable() && level->player) {
      if (curr_at == level->player->curr_at) {
        auto k = ::to_string(game->config.key_wait_or_collect);
        if (k == ".") {
          text += " Press %%fg=yellow$" + k + "%%fg=reset$ or click to collect.";
        } else {
          text += " %%fg=yellow$" + k + "%%fg=reset$ or click to collect.";
        }
      }
    }
  }

  if (text.size()) {
    if ((text[ text.size() - 1 ] == '.') || (text[ text.size() - 1 ] == '!')) {
      BOTCON("%s", text.c_str());
    } else {
      BOTCON("%s.", text.c_str());
    }
  }
}

void Tp::show_botcon_description(void)
{
  TRACE_NO_INDENT();
  auto text = text_description_short();

  bool skip_showing_keys_to_use = true;
  switch (game->state) {
    case Game::STATE_CHOOSING_LEVEL : return;
    case Game::STATE_NORMAL : skip_showing_keys_to_use = false; break;
    case Game::STATE_INVENTORY : // Currently managing inventory
      skip_showing_keys_to_use = false;
      break;
    case Game::STATE_COLLECTING_ITEMS : // Collecting en masse from the level
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_ENCHANTING_ITEMS : skip_showing_keys_to_use = true; break;
    case Game::STATE_CHOOSING_TARGET : // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_CHOOSING_SKILLS : // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_CHOOSING_SPELLS : // Looking to somewhere to throw at
      skip_showing_keys_to_use = true;
      break;
    case Game::STATE_LOAD_MENU : skip_showing_keys_to_use = true; break;
    case Game::STATE_SAVE_MENU : skip_showing_keys_to_use = true; break;
    case Game::STATE_QUIT_MENU : skip_showing_keys_to_use = true; break;
    case Game::STATE_KEYBOARD_MENU : skip_showing_keys_to_use = true; break;
    default : ERR("Unhandled game state"); break;
  }

  //
  // Want to show that you can drop a bag if you select it.
  //
  if (is_droppable()) {
    text += " %%fg=orange$" + ::to_string(game->config.key_drop) + "%%fg=reset$ to drop.";
  }

  //
  // Unless a bag.
  //
  if (skip_showing_keys_to_use) {
    if (text.empty()) {
      return;
    }
    BOTCON("%s", text.c_str());
    return;
  }

  if (is_weapon()) {
    text += " Damage %%fg=red$" + dmg_melee_dice_str() + "%%fg=reset$.";
  }

  if (is_poisonous_danger_level()) {
    text += " Poisons. ";
  }

  if (is_necrotic_danger_level()) {
    text += " Necrotic. ";
  }

  if (is_usable()) {
    if (is_food()) {
      text += " %%fg=green$" + ::to_string(game->config.key_eat) + "%%fg=reset$ to eat.";
    } else if (is_potion()) {
      text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to drink.";
    } else if (is_staff()) {
      text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to use.";
    } else if (is_ring()) {
      text += " %%fg=green$" + ::to_string(game->config.key_use) + "%%fg=reset$ to wear.";
    } else {
      text += " %%fg=cyan$" + ::to_string(game->config.key_use) + "%%fg=reset$ to use.";
    }
  }

  if (is_throwable() && ! is_auto_throw()) {
    text += " %%fg=purple$" + ::to_string(game->config.key_throw) + "%%fg=reset$ to throw.";
  }

  if (is_bag_item_container()) {
    text += " Use mouse to drag items.";
  }

  if (text.size()) {
    if ((text[ text.size() - 1 ] == '.') || (text[ text.size() - 1 ] == '!')) {
      BOTCON("%s", text.c_str());
    } else {
      BOTCON("%s.", text.c_str());
    }
  }
}

const std::string Thing::text_long_name(size_t max_len)
{
  TRACE_NO_INDENT();

  std::string out;
  if (is_mimic() && ! is_sleeping) {
    out = tp()->text_real_name();
  } else {
    out = tp()->text_long_name();
  }

  if (enchant_count_get()) {
    out += " +" + std::to_string(enchant_count_get());
  }

  if (max_len) {
    if (out.size() >= max_len) {
      abbreviate(out);
    }
  }

  return out;
}

const std::string Thing::text_short_name(size_t max_len)
{
  TRACE_NO_INDENT();

  std::string out;
  if (is_mimic() && ! is_sleeping) {
    out = tp()->text_real_name();
  } else {
    out = tp()->text_short_name();
  }

  if (enchant_count_get()) {
    out += " +" + std::to_string(enchant_count_get());
  }

  if (max_len) {
    if (out.size() >= max_len) {
      abbreviate(out);
    }
  }

  return out;
}

std::string Tp::text_a_or_an(void) const { return _text_a_or_an; }
std::string Tp::text_pluralize(void) const { return _text_pluralize; }
std::string Tp::text_apostrophize(void) const { return _text_apostrophize; }

//
// foo bar -> Foo Bar
//
std::string Tp::text_short_capitalized(void) const
{
  TRACE_NO_INDENT();

  std::string out        = text_short_name();
  char       *b          = (char *) out.c_str();
  char       *e          = b + out.size();
  char       *c          = b;
  bool        word_start = true;

  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}

//
// foo bar -> Foo Bar
//
std::string Tp::text_long_capitalized(void) const
{
  TRACE_NO_INDENT();

  std::string out        = text_long_name();
  char       *b          = (char *) out.c_str();
  char       *e          = b + out.size();
  char       *c          = b;
  bool        word_start = true;

  while (c < e) {
    if (word_start) {
      if (islower(*c)) {
        *c = toupper(*c);
      }
      word_start = false;
    } else if (*c == ' ') {
      word_start = true;
    }

    c++;
  }

  return out;
}
