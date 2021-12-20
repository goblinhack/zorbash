//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_array_bounds_check.hpp"
#include "my_depth.hpp"
#include "my_dice.hpp"
#include "my_game.hpp"
#include "my_level.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"
#include "my_tile.hpp"
#include "my_vector_bounds_check.hpp"

static Tpidmap tp_ascend_dungeon;
static Tpidmap tp_ascend_sewer;
static Tpidmap tp_barrel;
static Tpidmap tp_blood;
static Tpidmap tp_blood_splatter;
static Tpidmap tp_bones;
static Tpidmap tp_brazier;
static Tpidmap tp_deco;
static Tpidmap tp_descend_dungeon;
static Tpidmap tp_descend_sewer;
static Tpidmap tp_dirt;
static Tpidmap tp_door;
static Tpidmap tp_dry_grass;
static Tpidmap tp_enchantstone;
static Tpidmap tp_ethereal_generator;
static Tpidmap tp_floor;
static Tpidmap tp_foilage;
static Tpidmap tp_food;
static Tpidmap tp_generator;
static Tpidmap tp_gold;
static Tpidmap tp_green_splatter;
static Tpidmap tp_item_class_a;
static Tpidmap tp_item_class_b;
static Tpidmap tp_item_class_c;
static Tpidmap tp_item_not_a_container_class_a;
static Tpidmap tp_item_not_a_container_class_b;
static Tpidmap tp_item_not_a_container_class_c;
static Tpidmap tp_key;
static Tpidmap tp_monst;
static Tpidmap tp_pink_splatter;
static Tpidmap tp_potion;
static Tpidmap tp_ring;
static Tpidmap tp_ring_class_a;
static Tpidmap tp_ring_class_b;
static Tpidmap tp_ring_class_c;
static Tpidmap tp_ripples;
static Tpidmap tp_rock;
static Tpidmap tp_secret_door;
static Tpidmap tp_sewer_wall;
static Tpidmap tp_skills;
static Tpidmap tp_skillstone;
static Tpidmap tp_spiderweb;
static Tpidmap tp_treasure;
static Tpidmap tp_wall_dungeon;
static Tpidmap tp_wand;
static Tpidmap tp_wand_class_a;
static Tpidmap tp_wand_class_b;
static Tpidmap tp_wand_class_c;
static Tpidmap tp_weapon;
static Tpidmap tp_weapon_class_a;
static Tpidmap tp_weapon_class_b;
static Tpidmap tp_weapon_class_c;

void tp_random_init(void)
{
  TRACE_AND_INDENT();
  for (auto &tp : tp_id_map) {
    if (tp->is_ascend_dungeon()) {
      tp_ascend_dungeon.push_back(tp);
    }
    if (tp->is_ascend_sewer()) {
      tp_ascend_sewer.push_back(tp);
    }
    if (tp->is_barrel()) {
      tp_barrel.push_back(tp);
    }
    if (tp->is_blood()) {
      tp_blood.push_back(tp);
    }
    if (tp->is_blood_splatter()) {
      tp_blood_splatter.push_back(tp);
    }
    if (tp->is_green_splatter()) {
      tp_green_splatter.push_back(tp);
    }
    if (tp->is_pink_splatter()) {
      tp_pink_splatter.push_back(tp);
    }
    if (tp->is_bones()) {
      tp_bones.push_back(tp);
    }
    if (tp->is_brazier()) {
      tp_brazier.push_back(tp);
    }
    if (tp->is_descend_dungeon()) {
      tp_descend_dungeon.push_back(tp);
    }
    if (tp->is_descend_sewer()) {
      tp_descend_sewer.push_back(tp);
    }
    if (tp->is_dirt()) {
      tp_dirt.push_back(tp);
    }
    if (tp->is_door()) {
      tp_door.push_back(tp);
    }
    if (tp->is_dry_grass()) {
      tp_dry_grass.push_back(tp);
    }
    if (tp->is_enchantstone()) {
      tp_enchantstone.push_back(tp);
    }
    if (tp->is_skillstone()) {
      tp_skillstone.push_back(tp);
    }
    if (tp->is_ethereal_minion_generator()) {
      tp_ethereal_generator.push_back(tp);
    }
    if (tp->is_floor()) {
      tp_floor.push_back(tp);
    }
    if (tp->is_floor_deco()) {
      tp_deco.push_back(tp);
    }
    if (tp->is_foilage()) {
      tp_foilage.push_back(tp);
    }
    if (tp->is_spiderweb()) {
      tp_spiderweb.push_back(tp);
    }
    if (tp->is_food()) {
      tp_food.push_back(tp);
    }
    if (tp->is_gold()) {
      tp_gold.push_back(tp);
    }
    if (tp->is_key()) {
      tp_key.push_back(tp);
    }
    if (tp->is_minion_generator()) {
      tp_generator.push_back(tp);
    }
    if (tp->is_potion()) {
      tp_potion.push_back(tp);
    }
    if (tp->is_ripple()) {
      tp_ripples.push_back(tp);
    }
    if (tp->is_rock()) {
      tp_rock.push_back(tp);
    }
    if (tp->is_secret_door()) {
      tp_secret_door.push_back(tp);
    }
    if (tp->is_sewer_wall()) {
      tp_sewer_wall.push_back(tp);
    }
    if (tp->is_skill()) {
      tp_skills.push_back(tp);
    }
    if (tp->is_treasure_type()) {
      tp_treasure.push_back(tp);
    }

    //
    // Keep bags and treasure chests seperate so we don't end up with
    // chests containing chests forever
    //
    if (tp->is_bag_item_container()) {
      if (tp->is_treasure_class_a()) {
        tp_item_class_a.push_back(tp);
      }
      if (tp->is_treasure_class_b()) {
        tp_item_class_b.push_back(tp);
      }
      if (tp->is_treasure_class_c()) {
        tp_item_class_c.push_back(tp);
      }
    } else {
      if (tp->is_treasure_class_a()) {
        tp_item_class_a.push_back(tp);
      }
      if (tp->is_treasure_class_b()) {
        tp_item_class_b.push_back(tp);
      }
      if (tp->is_treasure_class_c()) {
        tp_item_class_c.push_back(tp);
      }
      if (tp->is_treasure_class_a()) {
        tp_item_not_a_container_class_a.push_back(tp);
      }
      if (tp->is_treasure_class_b()) {
        tp_item_not_a_container_class_b.push_back(tp);
      }
      if (tp->is_treasure_class_c()) {
        tp_item_not_a_container_class_c.push_back(tp);
      }
    }

    if (tp->is_wall_dungeon()) {
      tp_wall_dungeon.push_back(tp);
    }
    if (tp->is_wand()) {
      tp_wand.push_back(tp);
    }
    if (tp->is_ring()) {
      tp_ring.push_back(tp);
    }
    if (tp->is_weapon()) {
      tp_weapon.push_back(tp);
    }

    if (tp->is_weapon()) {
      if (tp->is_treasure_class_a()) {
        tp_weapon_class_a.push_back(tp);
      }
      if (tp->is_treasure_class_b()) {
        tp_weapon_class_b.push_back(tp);
      }
      if (tp->is_treasure_class_c()) {
        tp_weapon_class_c.push_back(tp);
      }
    }

    if (tp->is_wand()) {
      if (tp->is_treasure_class_a()) {
        tp_wand_class_a.push_back(tp);
      }
      if (tp->is_treasure_class_b()) {
        tp_wand_class_b.push_back(tp);
      }
      if (tp->is_treasure_class_c()) {
        tp_wand_class_c.push_back(tp);
      }
    }

    if (tp->is_ring()) {
      if (tp->is_treasure_class_a()) {
        tp_ring_class_a.push_back(tp);
      }
      if (tp->is_treasure_class_b()) {
        tp_ring_class_b.push_back(tp);
      }
      if (tp->is_treasure_class_c()) {
        tp_ring_class_c.push_back(tp);
      }
    }

    if (! tp->is_minion()) {
      if (tp->is_monst()) {
        tp_monst.push_back(tp);
      }
    }
  }
}

static Tpp tp_get_with_rarity_filter(Tpidmap &m)
{
  TRACE_AND_INDENT();
  int tries = 10000;
  while (tries--) {
    auto tp = get(m, pcg_rand() % m.size());
    auto r  = pcg_random_range(0, 1000);
    if (r < 800) {
      if (tp->rarity() != THING_RARITY_COMMON) {
        continue;
      }
      // CON("chose THING_RARITY_COMMON -- %s", tp->name().c_str());
    } else if (r < 900) {
      if (tp->rarity() != THING_RARITY_UNCOMMON) {
        continue;
      }
      // CON("chose THING_RARITY_UNCOMMON -- %s", tp->name().c_str());
    } else if (r < 950) {
      if (tp->rarity() != THING_RARITY_RARE) {
        continue;
      }
      // CON("chose THING_RARITY_RARE -- %s", tp->name().c_str());
    } else if (r < 990) {
      if (tp->rarity() != THING_RARITY_VERY_RARE) {
        continue;
      }
      // CON("chose THING_RARITY_VERY_RARE -- %s", tp->name().c_str());
    } else if (r == 999) {
      if (tp->rarity() != THING_RARITY_UNIQUE) {
        continue;
      }
      // CON("chose THING_RARITY_UNIQUE -- %s", tp->name().c_str());
    }
    return tp;
  }
  ERR("Could not find a thing according to rarity");
  return get(m, pcg_rand() % m.size());
}

static Tpp tp_get_with_no_rarity_filter(Tpidmap &m)
{
  TRACE_AND_INDENT();
  return get(m, pcg_rand() % m.size());
}

Tpp tp_random_monst(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_monst.size())) {
    ERR("No monsts found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_monst);
}

Tpp tp_random_monst_easy(void)
{
  TRACE_AND_INDENT();
  return tp_random_monst();
}

Tpp tp_random_monst_med(void)
{
  TRACE_AND_INDENT();
  return tp_random_monst();
}

Tpp tp_random_monst_hard(void)
{
  TRACE_AND_INDENT();
  return tp_random_monst();
}

Tpp Level::tp_random_monst(const point &p)
{
  TRACE_AND_INDENT();
  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      return nullptr;
    }
    auto tpp = ::tp_random_monst();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    return tpp;
  }
}

Tpp Level::tp_random_monst_easy(const point &p)
{
  TRACE_AND_INDENT();
  Thingp current_player      = player;
  int    player_danger_level = 0;

  if (! current_player) {
    //
    // Try the current level
    //
    if (game->level) {
      current_player = game->level->player;
    }
  }

  if (current_player) {
    player_danger_level = current_player->get_danger_initial_level();

    //
    // Increase the danger level of the parent as we go deeper
    //
    player_danger_level += num() * 10;
  }

  if (! player_danger_level) {
    player_danger_level = 100;
  }

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place easy monst at %d,%d", p.x, p.y);
      return tp_random_monst(p);
    }
    auto tpp = ::tp_random_monst();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    if (player_danger_level) {
      if (tpp->get_danger_level() > player_danger_level) {
        continue;
      }
    }

    con("DGN: Placed easy monster '%s' difficulty %d (mine %d)", tpp->short_text_capitalized().c_str(),
        tpp->get_danger_level(), player_danger_level);
    return tpp;
  }
}

Tpp Level::tp_random_monst_med(const point &p)
{
  TRACE_AND_INDENT();
  Thingp current_player      = player;
  int    player_danger_level = 0;

  if (! current_player) {
    //
    // Try the current level
    //
    if (game->level) {
      current_player = game->level->player;
    }
  }

  if (current_player) {
    player_danger_level = current_player->get_danger_initial_level();

    //
    // Increase the danger level of the parent as we go deeper
    //
    player_danger_level += num() * 10;
  }

  if (! player_danger_level) {
    player_danger_level = 100;
  }

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place medium monst at %d,%d", p.x, p.y);
      return tp_random_monst(p);
    }
    auto tpp = ::tp_random_monst();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    if (player_danger_level) {
      if (tpp->get_danger_level() < (int) ((float) player_danger_level * 1.0)) {
        continue;
      }
      if (tpp->get_danger_level() > (int) ((float) player_danger_level * 1.5)) {
        continue;
      }
    }

    con("DGN: Placed medium monster '%s' difficulty %d (mine %d)", tpp->short_text_capitalized().c_str(),
        tpp->get_danger_level(), player_danger_level);
    return tpp;
  }
}

Tpp Level::tp_random_monst_hard(const point &p)
{
  TRACE_AND_INDENT();
  Thingp current_player      = player;
  int    player_danger_level = 0;
  if (! current_player) {
    //
    // Try the current level
    //
    if (game->level) {
      current_player = game->level->player;
    }
  }

  if (current_player) {
    player_danger_level = current_player->get_danger_initial_level();

    //
    // Increase the danger level of the parent as we go deeper
    //
    player_danger_level += num() * 10;
  }

  if (! player_danger_level) {
    player_danger_level = 100;
  }

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place hard monst at %d,%d", p.x, p.y);
      return tp_random_monst(p);
    }
    auto tpp = ::tp_random_monst();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    if (player_danger_level) {
      if (tpp->get_danger_level() < (int) ((float) player_danger_level * 1.0)) {
        continue;
      }
      if (tpp->get_danger_level() > (int) ((float) player_danger_level * 2.0)) {
        continue;
      }
    }

    con("DGN: Placed hard monster '%s' difficulty %d (mine %d)", tpp->short_text_capitalized().c_str(),
        tpp->get_danger_level(), player_danger_level);
    return tpp;
  }
}

Tpp tp_random_food(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_food.size())) {
    ERR("No foods found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_food);
}

Tpp tp_random_gold(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_gold.size())) {
    ERR("No golds found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_gold);
}

Tpp tp_random_treasure(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_treasure.size())) {
    ERR("No treasures found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_treasure);
}

Tpp tp_random_item_class_a(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_item_class_a.size())) {
    ERR("No item_class_a found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_class_a);
}

Tpp tp_random_item_class_b(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_item_class_b.size())) {
    ERR("No item_class_b found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_class_b);
}

Tpp tp_random_item_class_c(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_item_class_c.size())) {
    ERR("No item_class_c found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_class_c);
}

Tpp tp_random_item_not_a_container_class_a(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_item_not_a_container_class_a.size())) {
    ERR("No item_not_a_container_class_a found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_not_a_container_class_a);
}

Tpp tp_random_item_not_a_container_class_b(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_item_not_a_container_class_b.size())) {
    ERR("No item_not_a_container_class_b found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_not_a_container_class_b);
}

Tpp tp_random_item_not_a_container_class_c(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_item_not_a_container_class_c.size())) {
    ERR("No item_not_a_container_class_c found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_not_a_container_class_c);
}

Tpp tp_random_weapon_class_a(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_weapon_class_a.size())) {
    return tp_random_weapon();
  }
  return tp_get_with_rarity_filter(tp_weapon_class_a);
}

Tpp tp_random_weapon_class_b(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_weapon_class_b.size())) {
    return tp_random_weapon_class_a();
  }
  return tp_get_with_rarity_filter(tp_weapon_class_b);
}

Tpp tp_random_weapon_class_c(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_weapon_class_c.size())) {
    return tp_random_weapon_class_b();
  }
  return tp_get_with_rarity_filter(tp_weapon_class_c);
}

Tpp tp_random_wand_class_a(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_wand_class_a.size())) {
    return tp_random_wand();
  }
  return tp_get_with_rarity_filter(tp_wand_class_a);
}

Tpp tp_random_wand_class_b(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_wand_class_b.size())) {
    return tp_random_wand_class_a();
  }
  return tp_get_with_rarity_filter(tp_wand_class_b);
}

Tpp tp_random_wand_class_c(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_wand_class_c.size())) {
    return tp_random_wand_class_b();
  }
  return tp_get_with_rarity_filter(tp_wand_class_c);
}

Tpp tp_random_ring_class_a(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ring_class_a.size())) {
    return tp_random_ring();
  }
  return tp_get_with_rarity_filter(tp_ring_class_a);
}

Tpp tp_random_ring_class_b(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ring_class_b.size())) {
    return tp_random_ring_class_a();
  }
  return tp_get_with_rarity_filter(tp_ring_class_b);
}

Tpp tp_random_ring_class_c(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ring_class_c.size())) {
    return tp_random_ring_class_b();
  }
  return tp_get_with_rarity_filter(tp_ring_class_c);
}

Tpp tp_random_dirt(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_dirt.size())) {
    ERR("No dirts found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_dirt);
}

Tpp tp_random_dry_grass(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_dry_grass.size())) {
    ERR("No dry_grass found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_dry_grass);
}

Tpp tp_random_enchantstone(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_enchantstone.size())) {
    ERR("No enchantstones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_enchantstone);
}

Tpp tp_random_skillstone(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_skillstone.size())) {
    ERR("No skillstones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_skillstone);
}

Tpp tp_random_foilage(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_foilage.size())) {
    ERR("No foilages found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_foilage);
}

Tpp tp_random_spiderweb(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_spiderweb.size())) {
    ERR("No spiderwebs found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_spiderweb);
}

Tpp tp_random_ripple(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ripples.size())) {
    ERR("No ripples found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_ripples);
}

Tpp tp_random_blood_splatter(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_blood_splatter.size())) {
    ERR("No blood_splatter found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_blood_splatter);
}

Tpp tp_random_green_splatter(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_green_splatter.size())) {
    ERR("No green_splatter found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_green_splatter);
}

Tpp tp_random_pink_splatter(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_pink_splatter.size())) {
    ERR("No pink_splatter found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_pink_splatter);
}

Tpp tp_random_key(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_key.size())) {
    ERR("No key found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_key);
}

Tpp tp_random_potion(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_potion.size())) {
    ERR("No potion found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_potion);
}

Tpp tp_random_wand(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_wand.size())) {
    ERR("No wand found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_wand);
}

Tpp tp_random_ring(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ring.size())) {
    ERR("No ring found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_ring);
}

Tpp tp_random_weapon(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_weapon.size())) {
    ERR("No weapon found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_weapon);
}

Tpp tp_random_ascend_dungeon(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ascend_dungeon.size())) {
    ERR("No entrance found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_ascend_dungeon);
}

Tpp tp_random_descend_dungeon(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_descend_dungeon.size())) {
    ERR("No exit found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_descend_dungeon);
}

Tpp tp_random_brazier(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_brazier.size())) {
    ERR("No brazier found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_brazier);
}

Tpp tp_random_barrel(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_barrel.size())) {
    ERR("No barrel found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_barrel);
}

Tpp tp_random_door(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_door.size())) {
    ERR("No door found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_door);
}

Tpp tp_random_secret_door(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_secret_door.size())) {
    ERR("No secret_door found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_secret_door);
}

Tpp tp_random_minion_generator(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_generator.size())) {
    ERR("No generator found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_generator);
}

Tpp tp_random_ethereal_minion_generator(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ethereal_generator.size())) {
    ERR("No generator found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_ethereal_generator);
}

Tpp tp_random_minion_generator_easy(void) { return tp_random_minion_generator(); }

Tpp tp_random_minion_generator_hard(void) { return tp_random_minion_generator(); }

Tpp Level::tp_random_minion_generator(const point &p)
{
  TRACE_AND_INDENT();
  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      return nullptr;
    }
    auto tpp = ::tp_random_minion_generator();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }
    return tpp;
  }
}

Tpp Level::tp_random_minion_generator_easy(const point &p)
{
  TRACE_AND_INDENT();
  return tp_random_minion_generator(p);
}

Tpp Level::tp_random_minion_generator_hard(const point &p)
{
  TRACE_AND_INDENT();
  return tp_random_minion_generator(p);
}

Tpp tp_random_blood(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_blood.size())) {
    ERR("No bloods found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_blood);
}

Tpp tp_random_bones(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_bones.size())) {
    ERR("No bones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_bones);
}

Tpp tp_random_wall_dungeon(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_wall_dungeon.size())) {
    ERR("No dungeon walls found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_wall_dungeon);
}

Tpp tp_random_sewer_wall(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_sewer_wall.size())) {
    ERR("No sewer walls found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_sewer_wall);
}

Tpp tp_random_rock(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_rock.size())) {
    ERR("No rocks found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_rock);
}

Tpp tp_random_floor(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_floor.size())) {
    ERR("No floors found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_floor);
}

Tpp tp_random_deco(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_deco.size())) {
    ERR("No decos found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_deco);
}

Tpp tp_random_ascend_sewer(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_ascend_sewer.size())) {
    ERR("No sewer entrances found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_ascend_sewer);
}

Tpp tp_random_descend_sewer(void)
{
  TRACE_AND_INDENT();
  if (unlikely(! tp_descend_sewer.size())) {
    ERR("No sewer exits found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_descend_sewer);
}

const Tpidmap &tp_get_skills(void)
{
  TRACE_AND_INDENT();
  return tp_skills;
}
