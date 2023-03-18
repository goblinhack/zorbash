//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_vector_bounds_check.hpp"

static Tpidmap tp_ascend_dungeon;
static Tpidmap tp_ascend_sewer;
static Tpidmap tp_barrel;
static Tpidmap tp_red_blood;
static Tpidmap tp_green_blood;
static Tpidmap tp_red_splatter;
static Tpidmap tp_bones;
static Tpidmap tp_brazier;
static Tpidmap tp_deco;
static Tpidmap tp_descend_dungeon;
static Tpidmap tp_descend_sewer;
static Tpidmap tp_dirt;
static Tpidmap tp_door;
static Tpidmap tp_dry_grass;
static Tpidmap tp_wet_grass;
static Tpidmap tp_enchantstone;
static Tpidmap tp_ethereal_mob;
static Tpidmap tp_floor;
static Tpidmap tp_foliage;
static Tpidmap tp_food;
static Tpidmap tp_mob;
static Tpidmap tp_trap;
static Tpidmap tp_gold;
static Tpidmap tp_green_splatter;
static Tpidmap tp_item_class_A;
static Tpidmap tp_item_class_B;
static Tpidmap tp_item_class_C;
static Tpidmap tp_item_not_a_container_class_A;
static Tpidmap tp_item_not_a_container_class_B;
static Tpidmap tp_item_not_a_container_class_C;
static Tpidmap tp_key;
static Tpidmap tp_potion;
static Tpidmap tp_ring;
static Tpidmap tp_ring_class_A;
static Tpidmap tp_ring_class_B;
static Tpidmap tp_ring_class_C;
static Tpidmap tp_small_ripples;
static Tpidmap tp_large_ripples;
static Tpidmap tp_rock;
static Tpidmap tp_secret_door;
static Tpidmap tp_sewer_wall;
static Tpidmap tp_skills;
static Tpidmap tp_skillstone;
static Tpidmap tp_spiderweb;
static Tpidmap tp_portal;
static Tpidmap tp_treasure;
static Tpidmap tp_wall_dungeon;
static Tpidmap tp_staff;
static Tpidmap tp_staff_class_A;
static Tpidmap tp_staff_class_B;
static Tpidmap tp_staff_class_C;
static Tpidmap tp_weapon;
static Tpidmap tp_weapon_class_A;
static Tpidmap tp_weapon_class_B;
static Tpidmap tp_weapon_class_C;
static Tpidmap tp_treasure_class_A;
static Tpidmap tp_treasure_class_B;
static Tpidmap tp_treasure_class_C;

void tp_random_init(void)
{
  TRACE_NO_INDENT();
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
    if (tp->is_trap()) {
      tp_trap.push_back(tp);
    }
    if (tp->is_red_blood()) {
      tp_red_blood.push_back(tp);
    }
    if (tp->is_green_blood()) {
      tp_green_blood.push_back(tp);
    }
    if (tp->is_red_splatter()) {
      tp_red_splatter.push_back(tp);
    }
    if (tp->is_green_splatter()) {
      tp_green_splatter.push_back(tp);
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
    if (tp->is_wet_grass()) {
      tp_wet_grass.push_back(tp);
    }
    if (tp->is_enchantstone()) {
      tp_enchantstone.push_back(tp);
    }
    if (tp->is_skillstone()) {
      tp_skillstone.push_back(tp);
    }
    if (tp->is_ethereal_mob()) {
      tp_ethereal_mob.push_back(tp);
    }
    if (tp->is_floor()) {
      tp_floor.push_back(tp);
    }
    if (tp->is_floor_deco()) {
      tp_deco.push_back(tp);
    }
    if (tp->is_foliage()) {
      tp_foliage.push_back(tp);
    }
    if (tp->is_spiderweb()) {
      tp_spiderweb.push_back(tp);
    }
    if (tp->is_portal()) {
      tp_portal.push_back(tp);
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
    if (tp->is_mob()) {
      tp_mob.push_back(tp);
    }
    if (tp->is_potion()) {
      tp_potion.push_back(tp);
    }
    if (tp->is_ripple()) {
      if (tp->thing_size() < THING_SIZE_NORMAL) {
        tp_small_ripples.push_back(tp);
      } else {
        tp_large_ripples.push_back(tp);
      }
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
      if (tp->is_treasure_class_A()) {
        tp_item_class_A.push_back(tp);
      }
      if (tp->is_treasure_class_B()) {
        tp_item_class_B.push_back(tp);
      }
      if (tp->is_treasure_class_C()) {
        tp_item_class_C.push_back(tp);
      }
      if (tp->is_weapon_class_A()) {
        tp_item_class_A.push_back(tp);
      }
      if (tp->is_weapon_class_B()) {
        tp_item_class_B.push_back(tp);
      }
      if (tp->is_weapon_class_C()) {
        tp_item_class_C.push_back(tp);
      }
    } else {
      if (tp->is_treasure_class_A()) {
        tp_item_class_A.push_back(tp);
      }
      if (tp->is_treasure_class_B()) {
        tp_item_class_B.push_back(tp);
      }
      if (tp->is_treasure_class_C()) {
        tp_item_class_C.push_back(tp);
      }
      if (tp->is_treasure_class_A()) {
        tp_item_not_a_container_class_A.push_back(tp);
      }
      if (tp->is_treasure_class_B()) {
        tp_item_not_a_container_class_B.push_back(tp);
      }
      if (tp->is_treasure_class_C()) {
        tp_item_not_a_container_class_C.push_back(tp);
      }
      if (tp->is_weapon_class_A()) {
        tp_item_class_A.push_back(tp);
      }
      if (tp->is_weapon_class_B()) {
        tp_item_class_B.push_back(tp);
      }
      if (tp->is_weapon_class_C()) {
        tp_item_class_C.push_back(tp);
      }
      if (tp->is_weapon_class_A()) {
        tp_item_not_a_container_class_A.push_back(tp);
      }
      if (tp->is_weapon_class_B()) {
        tp_item_not_a_container_class_B.push_back(tp);
      }
      if (tp->is_weapon_class_C()) {
        tp_item_not_a_container_class_C.push_back(tp);
      }
    }

    if (tp->is_wall_dungeon()) {
      tp_wall_dungeon.push_back(tp);
    }
    if (tp->is_ring()) {
      tp_ring.push_back(tp);
    }
    if (tp->is_weapon()) {
      tp_weapon.push_back(tp);
    }

    if (tp->is_weapon()) {
      if (tp->is_weapon_class_A()) {
        tp_weapon_class_A.push_back(tp);
      }
      if (tp->is_weapon_class_B()) {
        tp_weapon_class_B.push_back(tp);
      }
      if (tp->is_weapon_class_C()) {
        tp_weapon_class_C.push_back(tp);
      }
    }

    if (tp->is_treasure_class_A()) {
      tp_treasure_class_A.push_back(tp);
    }
    if (tp->is_treasure_class_B()) {
      tp_treasure_class_B.push_back(tp);
    }
    if (tp->is_treasure_class_C()) {
      tp_treasure_class_C.push_back(tp);
    }

    if (tp->is_staff()) {
      tp_staff.push_back(tp);
    }
    if (tp->is_staff()) {
      if (tp->is_treasure_class_A()) {
        tp_staff_class_A.push_back(tp);
      }
      if (tp->is_treasure_class_B()) {
        tp_staff_class_B.push_back(tp);
      }
      if (tp->is_treasure_class_C()) {
        tp_staff_class_C.push_back(tp);
      }
    }

    if (tp->is_ring()) {
      if (tp->is_treasure_class_A()) {
        tp_ring_class_A.push_back(tp);
      }
      if (tp->is_treasure_class_B()) {
        tp_ring_class_B.push_back(tp);
      }
      if (tp->is_treasure_class_C()) {
        tp_ring_class_C.push_back(tp);
      }
    }

    if (! tp->is_minion()) {
      if (tp->is_monst() || tp->is_monst_pack()) {
        tp_monst_add(tp);
      }
    }
  }

  if (tp_ascend_dungeon.empty()) {
    DIE("No things for type:tp_ascend_dungeon.empty");
  }
  if (tp_ascend_sewer.empty()) {
    DIE("No things for type:tp_ascend_sewer.empty");
  }
  if (tp_barrel.empty()) {
    DIE("No things for type:tp_barrel.empty");
  }
  if (tp_red_blood.empty()) {
    DIE("No things for type:tp_red_blood.empty");
  }
  if (tp_green_blood.empty()) {
    DIE("No things for type:tp_green_blood.empty");
  }
  if (tp_red_splatter.empty()) {
    DIE("No things for type:tp_red_splatter.empty");
  }
  if (tp_bones.empty()) {
    DIE("No things for type:tp_bones.empty");
  }
  if (tp_brazier.empty()) {
    DIE("No things for type:tp_brazier.empty");
  }
  if (tp_deco.empty()) {
    DIE("No things for type:tp_deco.empty");
  }
  if (tp_descend_dungeon.empty()) {
    DIE("No things for type:tp_descend_dungeon.empty");
  }
  if (tp_descend_sewer.empty()) {
    DIE("No things for type:tp_descend_sewer.empty");
  }
  if (tp_dirt.empty()) {
    DIE("No things for type:tp_dirt.empty");
  }
  if (tp_door.empty()) {
    DIE("No things for type:tp_door.empty");
  }
  if (tp_dry_grass.empty()) {
    DIE("No things for type:tp_dry_grass.empty");
  }
  if (tp_wet_grass.empty()) {
    DIE("No things for type:tp_wet_grass.empty");
  }
  if (tp_enchantstone.empty()) {
    DIE("No things for type:tp_enchantstone.empty");
  }
  if (tp_ethereal_mob.empty()) {
    DIE("No things for type:tp_ethereal_mob.empty");
  }
  if (tp_floor.empty()) {
    DIE("No things for type:tp_floor.empty");
  }
  if (tp_foliage.empty()) {
    DIE("No things for type:tp_foliage.empty");
  }
  if (tp_food.empty()) {
    DIE("No things for type:tp_food.empty");
  }
  if (tp_mob.empty()) {
    DIE("No things for type:tp_mob.empty");
  }
  if (tp_trap.empty()) {
    DIE("No things for type:tp_trap.empty");
  }
  if (tp_gold.empty()) {
    DIE("No things for type:tp_gold.empty");
  }
  if (tp_green_splatter.empty()) {
    DIE("No things for type:tp_green_splatter.empty");
  }
  if (tp_item_class_A.empty()) {
    DIE("No things for type:tp_item_class_A.empty");
  }
  if (tp_item_class_B.empty()) {
    DIE("No things for type:tp_item_class_B.empty");
  }
  if (tp_item_class_C.empty()) {
    DIE("No things for type:tp_item_class_C.empty");
  }
  if (tp_item_not_a_container_class_A.empty()) {
    DIE("No things for type:tp_item_not_a_container_class_A.empty");
  }
  if (tp_item_not_a_container_class_B.empty()) {
    DIE("No things for type:tp_item_not_a_container_class_B.empty");
  }
  if (tp_item_not_a_container_class_C.empty()) {
    DIE("No things for type:tp_item_not_a_container_class_C.empty");
  }
  if (tp_key.empty()) {
    DIE("No things for type:tp_key.empty");
  }
  if (tp_potion.empty()) {
    DIE("No things for type:tp_potion.empty");
  }
  if (tp_ring.empty()) {
    DIE("No things for type:tp_ring.empty");
  }
  if (tp_ring_class_A.empty()) {
    DIE("No things for type:tp_ring_class_A.empty");
  }
  if (tp_ring_class_B.empty()) {
    DIE("No things for type:tp_ring_class_B.empty");
  }
  if (tp_ring_class_C.empty()) {
    DIE("No things for type:tp_ring_class_C.empty");
  }
  if (tp_small_ripples.empty()) {
    DIE("No things for type:tp_small_ripples.empty");
  }
  if (tp_large_ripples.empty()) {
    DIE("No things for type:tp_large_ripples.empty");
  }
  if (tp_rock.empty()) {
    DIE("No things for type:tp_rock.empty");
  }
  if (tp_secret_door.empty()) {
    DIE("No things for type:tp_secret_door.empty");
  }
  if (tp_sewer_wall.empty()) {
    DIE("No things for type:tp_sewer_wall.empty");
  }
  if (tp_skills.empty()) {
    DIE("No things for type:tp_skills.empty");
  }
  if (tp_skillstone.empty()) {
    DIE("No things for type:tp_skillstone.empty");
  }
  if (tp_spiderweb.empty()) {
    DIE("No things for type:tp_spiderweb.empty");
  }
  if (tp_portal.empty()) {
    DIE("No things for type:tp_portal.empty");
  }
  if (tp_treasure.empty()) {
    DIE("No things for type:tp_treasure.empty");
  }
  if (tp_wall_dungeon.empty()) {
    DIE("No things for type:tp_wall_dungeon.empty");
  }
  if (tp_staff.empty()) {
    DIE("No things for type:tp_staff.empty");
  }
  if (tp_staff_class_A.empty()) {
    DIE("No things for type:tp_staff_class_A.empty");
  }
  if (tp_staff_class_B.empty()) {
    DIE("No things for type:tp_staff_class_B.empty");
  }
  if (tp_staff_class_C.empty()) {
    DIE("No things for type:tp_staff_class_C.empty");
  }
  if (tp_weapon.empty()) {
    DIE("No things for type:tp_weapon.empty");
  }
  if (tp_weapon_class_A.empty()) {
    DIE("No things for type:tp_weapon_class_A.empty");
  }
  if (tp_weapon_class_B.empty()) {
    DIE("No things for type:tp_weapon_class_B.empty");
  }
  if (tp_weapon_class_C.empty()) {
    DIE("No things for type:tp_weapon_class_C.empty");
  }
  if (tp_treasure_class_A.empty()) {
    DIE("No things for type:tp_treasure_class_A.empty");
  }
  if (tp_treasure_class_B.empty()) {
    DIE("No things for type:tp_treasure_class_B.empty");
  }
  if (tp_treasure_class_C.empty()) {
    DIE("No things for type:tp_treasure_class_C.empty");
  }
}

Tpp tp_get_with_rarity_filter(Tpidmap &m)
{
  TRACE_NO_INDENT();

  if (m.empty()) {
    return nullptr;
  }

  int tries = 100;
  while (tries--) {
    auto r      = pcg_random_range(0, 1000);
    int  tries2 = 100;
    while (tries2--) {
      auto tp = get(m, pcg_rand() % m.size());
      if (r < 500) {
        if (tp->rarity() != THING_RARITY_COMMON) {
          continue;
        }
        // CON("chose THING_RARITY_COMMON -- %s", tp->name().c_str());
      } else if (r < 800) {
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
  }
  ERR("Could not find a thing according to rarity");
  return get(m, pcg_rand() % m.size());
}

static Tpp tp_get_with_no_rarity_filter(Tpidmap &m)
{
  TRACE_NO_INDENT();

  int tries = 1000;
  while (tries-- > 0) {
    auto index = pcg_rand() % m.size();
    auto tp    = get(m, index);
    if (! tp) {
      break;
    }

    //
    // If this thing has a limited chance of appearing, roll the dice.
    //
    auto chance = tp->chance_d1000_appearing();
    if (chance) {
      auto roll = d1000();
      if (roll < chance) {
        return tp;
      }
    } else {
      return tp;
    }
  }

  //
  // Give in and return the first we find.
  //
  auto index = pcg_rand() % m.size();
  auto tp    = get(m, index);
  return tp;
}

Tpp tp_random_food(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_food.size())) {
    ERR("No foods found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_food);
}

Tpp tp_random_gold(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_gold.size())) {
    ERR("No golds found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_gold);
}

Tpp tp_random_treasure(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_treasure.size())) {
    ERR("No treasures found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_treasure);
}

Tpp tp_random_item_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_item_class_A.size())) {
    ERR("No item_class_A found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_class_A);
}

Tpp tp_random_item_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_item_class_B.size())) {
    return tp_random_item_class_A();
  }
  return tp_get_with_rarity_filter(tp_item_class_B);
}

Tpp tp_random_item_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_item_class_C.size())) {
    return tp_random_item_class_B();
  }
  return tp_get_with_rarity_filter(tp_item_class_C);
}

Tpp tp_random_item_not_a_container_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_item_not_a_container_class_A.size())) {
    ERR("No item_not_a_container_class_A found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_item_not_a_container_class_A);
}

Tpp tp_random_item_not_a_container_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_item_not_a_container_class_B.size())) {
    return tp_random_item_not_a_container_class_A();
  }
  return tp_get_with_rarity_filter(tp_item_not_a_container_class_B);
}

Tpp tp_random_item_not_a_container_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_item_not_a_container_class_C.size())) {
    return tp_random_item_not_a_container_class_B();
  }
  return tp_get_with_rarity_filter(tp_item_not_a_container_class_C);
}

Tpp tp_random_weapon_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_weapon_class_A.size())) {
    return tp_random_weapon();
  }
  return tp_get_with_rarity_filter(tp_weapon_class_A);
}

Tpp tp_random_weapon_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_weapon_class_B.size())) {
    return tp_random_weapon_class_A();
  }
  return tp_get_with_rarity_filter(tp_weapon_class_B);
}

Tpp tp_random_weapon_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_weapon_class_C.size())) {
    return tp_random_weapon_class_B();
  }
  return tp_get_with_rarity_filter(tp_weapon_class_C);
}

Tpp tp_random_treasure_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_treasure_class_A.size())) {
    return tp_random_treasure();
  }
  return tp_get_with_rarity_filter(tp_treasure_class_A);
}

Tpp tp_random_treasure_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_treasure_class_B.size())) {
    return tp_random_treasure_class_A();
  }
  return tp_get_with_rarity_filter(tp_treasure_class_B);
}

Tpp tp_random_treasure_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_treasure_class_C.size())) {
    return tp_random_treasure_class_B();
  }
  return tp_get_with_rarity_filter(tp_treasure_class_C);
}

Tpp tp_random_staff_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_staff_class_A.size())) {
    return tp_random_staff();
  }
  return tp_get_with_rarity_filter(tp_staff_class_A);
}

Tpp tp_random_staff_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_staff_class_B.size())) {
    return tp_random_staff_class_A();
  }
  return tp_get_with_rarity_filter(tp_staff_class_B);
}

Tpp tp_random_staff_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_staff_class_C.size())) {
    return tp_random_staff_class_B();
  }
  return tp_get_with_rarity_filter(tp_staff_class_C);
}

Tpp tp_random_ring_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ring_class_A.size())) {
    return tp_random_ring();
  }
  return tp_get_with_rarity_filter(tp_ring_class_A);
}

Tpp tp_random_ring_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ring_class_B.size())) {
    return tp_random_ring_class_A();
  }
  return tp_get_with_rarity_filter(tp_ring_class_B);
}

Tpp tp_random_ring_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ring_class_C.size())) {
    return tp_random_ring_class_B();
  }
  return tp_get_with_rarity_filter(tp_ring_class_C);
}

Tpp tp_random_dirt(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_dirt.size())) {
    ERR("No dirts found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_dirt);
}

Tpp tp_random_dry_grass(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_dry_grass.size())) {
    ERR("No dry_grass found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_dry_grass);
}

Tpp tp_random_wet_grass(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_wet_grass.size())) {
    ERR("No wet_grass found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_wet_grass);
}

Tpp tp_random_enchantstone(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_enchantstone.size())) {
    ERR("No enchantstones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_enchantstone);
}

Tpp tp_random_skillstone(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_skillstone.size())) {
    ERR("No skillstones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_skillstone);
}

Tpp tp_random_foliage(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_foliage.size())) {
    ERR("No foliages found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_foliage);
}

Tpp tp_random_spiderweb(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_spiderweb.size())) {
    ERR("No spiderwebs found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_spiderweb);
}

Tpp tp_random_portal(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_portal.size())) {
    ERR("No portals found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_portal);
}

Tpp tp_random_small_ripple(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_small_ripples.size())) {
    ERR("No small_ripples found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_small_ripples);
}

Tpp tp_random_large_ripple(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_large_ripples.size())) {
    ERR("No large_ripples found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_large_ripples);
}

Tpp tp_random_red_splatter(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_red_splatter.size())) {
    ERR("No red_splatter found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_red_splatter);
}

Tpp tp_random_green_splatter(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_green_splatter.size())) {
    ERR("No green_splatter found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_green_splatter);
}

Tpp tp_random_key(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_key.size())) {
    ERR("No key found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_key);
}

Tpp tp_random_potion(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_potion.size())) {
    ERR("No potion found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_potion);
}

Tpp tp_random_staff(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_staff.size())) {
    ERR("No staff found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_staff);
}

Tpp tp_random_ring(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ring.size())) {
    ERR("No ring found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_ring);
}

Tpp tp_random_weapon(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_weapon.size())) {
    ERR("No weapon found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_weapon);
}

Tpp tp_random_ascend_dungeon(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ascend_dungeon.size())) {
    ERR("No entrance found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_ascend_dungeon);
}

Tpp tp_random_descend_dungeon(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_descend_dungeon.size())) {
    ERR("No exit found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_descend_dungeon);
}

Tpp tp_random_brazier(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_brazier.size())) {
    ERR("No brazier found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_brazier);
}

Tpp tp_random_barrel(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_barrel.size())) {
    ERR("No barrel found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_barrel);
}

Tpp tp_random_trap(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_trap.size())) {
    ERR("No trap found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_trap);
}

Tpp tp_random_door(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_door.size())) {
    ERR("No door found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_door);
}

Tpp tp_random_secret_door(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_secret_door.size())) {
    ERR("No secret_door found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_secret_door);
}

Tpp tp_random_mob(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_mob.size())) {
    ERR("No mob found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_mob);
}

Tpp tp_random_ethereal_mob(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ethereal_mob.size())) {
    ERR("No mob found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_ethereal_mob);
}

Tpp tp_random_mob_challenge_class_A(void) { return tp_random_mob(); }

Tpp tp_random_mob_challenge_class_B(void) { return tp_random_mob(); }

Tpp tp_random_red_blood(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_red_blood.size())) {
    ERR("No red blood found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_red_blood);
}

Tpp tp_random_green_blood(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_green_blood.size())) {
    ERR("No green blood found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_green_blood);
}

Tpp tp_random_bones(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_bones.size())) {
    ERR("No bones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_bones);
}

Tpp tp_random_wall_dungeon(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_wall_dungeon.size())) {
    ERR("No dungeon walls found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_wall_dungeon);
}

Tpp tp_random_sewer_wall(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_sewer_wall.size())) {
    ERR("No sewer walls found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_sewer_wall);
}

Tpp tp_random_rock(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_rock.size())) {
    ERR("No rocks found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_rock);
}

Tpp tp_random_floor(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_floor.size())) {
    ERR("No floors found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_floor);
}

Tpp tp_random_deco(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_deco.size())) {
    ERR("No decos found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_deco);
}

Tpp tp_random_ascend_sewer(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ascend_sewer.size())) {
    ERR("No sewer entrances found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_ascend_sewer);
}

Tpp tp_random_descend_sewer(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_descend_sewer.size())) {
    ERR("No sewer exits found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_descend_sewer);
}

const Tpidmap &tp_get_skills(void)
{
  TRACE_NO_INDENT();
  return tp_skills;
}
