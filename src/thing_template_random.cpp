//
// Copyright goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_vector_bounds_check.hpp"

// begin sort marker1 {
static Tpidmap tp_ascend_dungeon;
static Tpidmap tp_ascend_sewer;
static Tpidmap tp_barrel;
static Tpidmap tp_bodypart[ BODYPART_MAX ];
static Tpidmap tp_bones;
static Tpidmap tp_brazier;
static Tpidmap tp_deco;
static Tpidmap tp_descend_dungeon;
static Tpidmap tp_descend_sewer;
static Tpidmap tp_dirt;
static Tpidmap tp_door;
static Tpidmap tp_ethereal_mob;
static Tpidmap tp_floor;
static Tpidmap tp_foliage;
static Tpidmap tp_food;
static Tpidmap tp_fungus_edible;
static Tpidmap tp_fungus_healing;
static Tpidmap tp_fungus_poison;
static Tpidmap tp_fungus_withered;
static Tpidmap tp_gold;
static Tpidmap tp_grass_dry;
static Tpidmap tp_grass_wet;
static Tpidmap tp_green_blood;
static Tpidmap tp_green_splatter;
static Tpidmap tp_item_class_A;
static Tpidmap tp_item_class_B;
static Tpidmap tp_item_class_C;
static Tpidmap tp_item_not_a_container_class_A;
static Tpidmap tp_item_not_a_container_class_B;
static Tpidmap tp_item_not_a_container_class_C;
static Tpidmap tp_key;
static Tpidmap tp_large_ripples;
static Tpidmap tp_magic_stone;
static Tpidmap tp_mob_class_A;
static Tpidmap tp_mob_class_B;
static Tpidmap tp_mob_class_C;
static Tpidmap tp_monst_class_A;
static Tpidmap tp_monst_class_B;
static Tpidmap tp_monst_class_C;
static Tpidmap tp_monst_class_D;
static Tpidmap tp_monst_class_E;
static Tpidmap tp_portal;
static Tpidmap tp_potion;
static Tpidmap tp_red_blood;
static Tpidmap tp_red_splatter;
static Tpidmap tp_ring;
static Tpidmap tp_ring_class_A;
static Tpidmap tp_ring_class_B;
static Tpidmap tp_ring_class_C;
static Tpidmap tp_rock;
static Tpidmap tp_runic_defensive_class_A;
static Tpidmap tp_runic_defensive_class_B;
static Tpidmap tp_runic_offensive_class_A;
static Tpidmap tp_runic_offensive_class_B;
static Tpidmap tp_secret_door;
static Tpidmap tp_sewer_wall;
static Tpidmap tp_skills;
static Tpidmap tp_small_ripples;
static Tpidmap tp_spells;
static Tpidmap tp_spiderweb;
static Tpidmap tp_staff;
static Tpidmap tp_staff_class_A;
static Tpidmap tp_staff_class_B;
static Tpidmap tp_staff_class_C;
static Tpidmap tp_trap;
static Tpidmap tp_treasure;
static Tpidmap tp_treasure_class_A;
static Tpidmap tp_treasure_class_B;
static Tpidmap tp_treasure_class_C;
static Tpidmap tp_wall_dungeon;
static Tpidmap tp_weapon;
static Tpidmap tp_weapon_class_A;
static Tpidmap tp_weapon_class_B;
static Tpidmap tp_weapon_class_C;
static Tpidmap tp_zorblin;
// end sort marker1 }

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
    if (tp->is_bones()) {
      tp_bones.push_back(tp);
    }
    if (tp->is_zorblin()) {
      tp_zorblin.push_back(tp);
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
    if (tp->is_ethereal_mob()) {
      tp_ethereal_mob.push_back(tp);
    }
    if (tp->is_floor_deco()) {
      tp_deco.push_back(tp);
    }
    if (tp->is_floor()) {
      tp_floor.push_back(tp);
    }
    if (tp->is_foliage()) {
      tp_foliage.push_back(tp);
    }
    if (tp->is_food()) {
      tp_food.push_back(tp);
    }
    if (tp->is_runic_offensive_class_A()) {
      tp_runic_offensive_class_A.push_back(tp);
    }
    if (tp->is_runic_defensive_class_A()) {
      tp_runic_defensive_class_A.push_back(tp);
    }
    if (tp->is_fungus_edible()) {
      tp_fungus_edible.push_back(tp);
    }
    if (tp->is_fungus_poison()) {
      tp_fungus_poison.push_back(tp);
    }
    if (tp->is_fungus_withered()) {
      tp_fungus_withered.push_back(tp);
    }
    if (tp->is_fungus_healing()) {
      tp_fungus_healing.push_back(tp);
    }
    if (tp->is_gold()) {
      tp_gold.push_back(tp);
    }
    if (tp->is_grass_dry()) {
      tp_grass_dry.push_back(tp);
    }
    if (tp->is_grass_wet()) {
      tp_grass_wet.push_back(tp);
    }
    if (tp->is_green_blood()) {
      tp_green_blood.push_back(tp);
    }
    if (tp->is_green_splatter()) {
      tp_green_splatter.push_back(tp);
    }
    if (tp->is_key()) {
      tp_key.push_back(tp);
    }
    if (tp->is_magic_stone()) {
      tp_magic_stone.push_back(tp);
    }
    if (tp->is_mob_class_A()) {
      tp_mob_class_A.push_back(tp);
    }
    if (tp->is_mob_class_B()) {
      tp_mob_class_B.push_back(tp);
    }
    if (tp->is_mob_class_C()) {
      tp_mob_class_C.push_back(tp);
    }
    if (tp->is_player_bodypart_eyes()) {
      tp_bodypart[ BODYPART_EYES ].push_back(tp);
    }
    if (tp->is_player_bodypart_face()) {
      tp_bodypart[ BODYPART_FACE ].push_back(tp);
    }
    if (tp->is_player_bodypart_hair()) {
      tp_bodypart[ BODYPART_HAIR ].push_back(tp);
    }
    if (tp->is_player_bodypart_hat()) {
      tp_bodypart[ BODYPART_HAT ].push_back(tp);
    }
    if (tp->is_player_bodypart_legs()) {
      tp_bodypart[ BODYPART_LEGS ].push_back(tp);
    }
    if (tp->is_player_bodypart_torso()) {
      tp_bodypart[ BODYPART_TORSO ].push_back(tp);
    }
    if (tp->is_portal()) {
      tp_portal.push_back(tp);
    }
    if (tp->is_potion()) {
      tp_potion.push_back(tp);
    }
    if (tp->is_red_blood()) {
      tp_red_blood.push_back(tp);
    }
    if (tp->is_red_splatter()) {
      tp_red_splatter.push_back(tp);
    }
    if (tp->is_spiderweb()) {
      tp_spiderweb.push_back(tp);
    }
    if (tp->is_trap()) {
      tp_trap.push_back(tp);
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
    if (tp->is_spell()) {
      tp_spells.push_back(tp);
    }
    if (tp->is_treasure_type()) {
      tp_treasure.push_back(tp);
    }

    if (! tp->is_minion()) {
      if (tp->is_monst_class_A()) {
        tp_monst_class_A.push_back(tp);
      }
      if (tp->is_monst_class_B()) {
        tp_monst_class_B.push_back(tp);
      }
      if (tp->is_monst_class_C()) {
        tp_monst_class_C.push_back(tp);
      }
      if (tp->is_monst_class_D()) {
        tp_monst_class_D.push_back(tp);
      }
      if (tp->is_monst_class_E()) {
        tp_monst_class_E.push_back(tp);
      }
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
    DIE("No things for type:tp_ascend_dungeon");
  }
  if (tp_ascend_sewer.empty()) {
    DIE("No things for type:tp_ascend_sewer");
  }
  if (tp_barrel.empty()) {
    DIE("No things for type:tp_barrel");
  }
  if (tp_bones.empty()) {
    DIE("No things for type:tp_bones");
  }
  if (tp_zorblin.empty()) {
    DIE("No things for type:tp_zorblin");
  }
  if (tp_brazier.empty()) {
    DIE("No things for type:tp_brazier");
  }
  if (tp_deco.empty()) {
    DIE("No things for type:tp_deco");
  }
  if (tp_descend_dungeon.empty()) {
    DIE("No things for type:tp_descend_dungeon");
  }
  if (tp_descend_sewer.empty()) {
    DIE("No things for type:tp_descend_sewer");
  }
  if (tp_dirt.empty()) {
    DIE("No things for type:tp_dirt");
  }
  if (tp_door.empty()) {
    DIE("No things for type:tp_door");
  }
  if (tp_ethereal_mob.empty()) {
    DIE("No things for type:tp_ethereal_mob");
  }
  if (tp_floor.empty()) {
    DIE("No things for type:tp_floor");
  }
  if (tp_foliage.empty()) {
    DIE("No things for type:tp_foliage");
  }
  if (tp_food.empty()) {
    DIE("No things for type:tp_food");
  }
  if (tp_gold.empty()) {
    DIE("No things for type:tp_gold");
  }
  if (tp_grass_dry.empty()) {
    DIE("No things for type:tp_grass_dry");
  }
  if (tp_grass_wet.empty()) {
    DIE("No things for type:tp_grass_wet");
  }
  if (tp_green_blood.empty()) {
    DIE("No things for type:tp_green_blood");
  }
  if (tp_green_splatter.empty()) {
    DIE("No things for type:tp_green_splatter");
  }
  if (tp_item_class_A.empty()) {
    DIE("No things for type:tp_item_class_A");
  }
  if (tp_item_class_B.empty()) {
    DIE("No things for type:tp_item_class_B");
  }
  if (tp_item_class_C.empty()) {
    DIE("No things for type:tp_item_class_C");
  }
  if (tp_item_not_a_container_class_A.empty()) {
    DIE("No things for type:tp_item_not_a_container_class_A");
  }
  if (tp_item_not_a_container_class_B.empty()) {
    DIE("No things for type:tp_item_not_a_container_class_B");
  }
  if (tp_item_not_a_container_class_C.empty()) {
    DIE("No things for type:tp_item_not_a_container_class_C");
  }
  if (tp_key.empty()) {
    DIE("No things for type:tp_key");
  }
  if (tp_large_ripples.empty()) {
    DIE("No things for type:tp_large_ripples");
  }
  if (tp_magic_stone.empty()) {
    DIE("No things for type:tp_magic_stone");
  }
  if (tp_monst_class_A.empty()) {
    DIE("No things for type:tp_monst_class_A");
  }
  if (tp_monst_class_B.empty()) {
    DIE("No things for type:tp_monst_class_B");
  }
  if (tp_monst_class_C.empty()) {
    DIE("No things for type:tp_monst_class_C");
  }
  if (tp_monst_class_D.empty()) {
    DIE("No things for type:tp_monst_class_D");
  }
  if (tp_monst_class_E.empty()) {
    DIE("No things for type:tp_monst_class_E");
  }
  if (tp_portal.empty()) {
    DIE("No things for type:tp_portal");
  }
  if (tp_potion.empty()) {
    DIE("No things for type:tp_potion");
  }
  if (tp_red_blood.empty()) {
    DIE("No things for type:tp_red_blood");
  }
  if (tp_red_splatter.empty()) {
    DIE("No things for type:tp_red_splatter");
  }
  if (tp_ring_class_A.empty()) {
    DIE("No things for type:tp_ring_class_A");
  }
  if (tp_ring_class_B.empty()) {
    DIE("No things for type:tp_ring_class_B");
  }
  if (tp_ring_class_C.empty()) {
    DIE("No things for type:tp_ring_class_C");
  }
  if (tp_ring.empty()) {
    DIE("No things for type:tp_ring");
  }
  if (tp_rock.empty()) {
    DIE("No things for type:tp_rock");
  }
  if (tp_secret_door.empty()) {
    DIE("No things for type:tp_secret_door");
  }
  if (tp_sewer_wall.empty()) {
    DIE("No things for type:tp_sewer_wall");
  }
  if (tp_skills.empty()) {
    DIE("No things for type:tp_skills");
  }
  if (tp_small_ripples.empty()) {
    DIE("No things for type:tp_small_ripples");
  }
  if (tp_spells.empty()) {
    CON("No things for type:tp_spells");
  }
  if (tp_spiderweb.empty()) {
    DIE("No things for type:tp_spiderweb");
  }
  if (tp_staff_class_A.empty()) {
    DIE("No things for type:tp_staff_class_A");
  }
  if (tp_staff_class_B.empty()) {
    DIE("No things for type:tp_staff_class_B");
  }
  if (tp_staff_class_C.empty()) {
    DIE("No things for type:tp_staff_class_C");
  }
  if (tp_staff.empty()) {
    DIE("No things for type:tp_staff");
  }
  if (tp_trap.empty()) {
    DIE("No things for type:tp_trap");
  }
  if (tp_treasure_class_A.empty()) {
    DIE("No things for type:tp_treasure_class_A");
  }
  if (tp_treasure_class_B.empty()) {
    DIE("No things for type:tp_treasure_class_B");
  }
  if (tp_treasure_class_C.empty()) {
    DIE("No things for type:tp_treasure_class_C");
  }
  if (tp_treasure.empty()) {
    DIE("No things for type:tp_treasure");
  }
  if (tp_wall_dungeon.empty()) {
    DIE("No things for type:tp_wall_dungeon");
  }
  if (tp_weapon_class_A.empty()) {
    DIE("No things for type:tp_weapon_class_A");
  }
  if (tp_weapon_class_B.empty()) {
    DIE("No things for type:tp_weapon_class_B");
  }
  if (tp_weapon_class_C.empty()) {
    DIE("No things for type:tp_weapon_class_C");
  }
  if (tp_weapon.empty()) {
    DIE("No things for type:tp_weapon");
  }
}

Tpp tp_get_with_rarity_filter(Tpidmap &m)
{
  TRACE_NO_INDENT();

  if (m.empty()) {
    return nullptr;
  }

  int tries = 1000;
  while (tries--) {
    auto roll   = pcg_random_range(0, 1000);
    int  tries2 = 1000;
    while (tries2--) {
      auto tp = get(m, pcg_rand() % m.size());
      //
      // 0  .. 800 comon
      // 800.. 900 uncomon
      // 900.. 950 rare
      // 950.. 990 very rare
      // 999       unique
      //
      if (roll < 800) {
        if (tp->rarity() != THING_RARITY_COMMON) {
          continue;
        }
        DBG("chose THING_RARITY_COMMON -- %s (roll %d)", tp->name().c_str(), roll);
      } else if (roll < 900) {
        if (tp->rarity() != THING_RARITY_UNCOMMON) {
          continue;
        }
        DBG("chose THING_RARITY_UNCOMMON -- %s (roll %d)", tp->name().c_str(), roll);
      } else if (roll < 950) {
        if (tp->rarity() != THING_RARITY_RARE) {
          continue;
        }
        DBG("chose THING_RARITY_RARE -- %s (roll %d)", tp->name().c_str(), roll);
      } else if (roll < 990) {
        if (tp->rarity() != THING_RARITY_VERY_RARE) {
          continue;
        }
        DBG("chose THING_RARITY_VERY_RARE -- %s (roll %d)", tp->name().c_str(), roll);
      } else if (roll == 999) {
        if (tp->rarity() != THING_RARITY_UNIQUE) {
          continue;
        }
        DBG("chose THING_RARITY_UNIQUE -- %s (roll %d)", tp->name().c_str(), roll);
      }
      return tp;
    }
  }

  //
  // Well, it can happen... Just choose one
  //
  LOG("Could not find a thing according to rarity");

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

Tpp tp_random_runic_offensive_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_runic_offensive_class_A.size())) {
    ERR("No runics found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_runic_offensive_class_A);
}

Tpp tp_random_runic_defensive_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_runic_defensive_class_A.size())) {
    ERR("No runics found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_runic_defensive_class_A);
}

Tpp tp_random_runic_offensive_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_runic_offensive_class_B.size())) {
    ERR("No runics found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_runic_offensive_class_B);
}

Tpp tp_random_runic_defensive_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_runic_defensive_class_B.size())) {
    ERR("No runics found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_runic_defensive_class_B);
}

Tpp tp_random_gold(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_gold.size())) {
    ERR("No gold found");
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

Tpp tp_random_monst_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_monst_class_A.size())) {
    ERR("No monst_class_A found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_monst_class_A);
}

Tpp tp_random_monst_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_monst_class_B.size())) {
    return tp_random_monst_class_A();
  }
  return tp_get_with_rarity_filter(tp_monst_class_B);
}

Tpp tp_random_monst_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_monst_class_C.size())) {
    return tp_random_monst_class_B();
  }
  return tp_get_with_rarity_filter(tp_monst_class_C);
}

Tpp tp_random_monst_class_D(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_monst_class_D.size())) {
    return tp_random_monst_class_C();
  }
  return tp_get_with_rarity_filter(tp_monst_class_D);
}

Tpp tp_random_monst_class_E(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_monst_class_E.size())) {
    return tp_random_monst_class_D();
  }
  return tp_get_with_rarity_filter(tp_monst_class_E);
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
    ERR("No dirt found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_dirt);
}

Tpp tp_random_grass_dry(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_grass_dry.size())) {
    ERR("No grass_dry found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_grass_dry);
}

Tpp tp_random_grass_wet(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_grass_wet.size())) {
    ERR("No grass_wet found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_grass_wet);
}

Tpp tp_random_fungus_edible(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_fungus_edible.size())) {
    ERR("No fungus_edible found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_fungus_edible);
}

Tpp tp_random_fungus_poison(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_fungus_poison.size())) {
    ERR("No fungus_poison found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_fungus_poison);
}

Tpp tp_random_fungus_withered(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_fungus_withered.size())) {
    ERR("No fungus_withered found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_fungus_withered);
}

Tpp tp_random_fungus_healing(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_fungus_healing.size())) {
    ERR("No fungus_healing found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_fungus_healing);
}

Tpp tp_random_magic_stone(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_magic_stone.size())) {
    ERR("No enchantstones found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_magic_stone);
}

Tpp tp_random_foliage(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_foliage.size())) {
    ERR("No foliage found");
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

Tpp tp_random_mob_class_A(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_mob_class_A.size())) {
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_mob_class_A);
}

Tpp tp_random_mob_class_B(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_mob_class_B.size())) {
    return tp_random_mob_class_A();
  }
  return tp_get_with_rarity_filter(tp_mob_class_B);
}

Tpp tp_random_mob_class_C(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_mob_class_C.size())) {
    return tp_random_mob_class_B();
  }
  return tp_get_with_rarity_filter(tp_mob_class_C);
}

Tpp tp_random_ethereal_mob(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_ethereal_mob.size())) {
    ERR("No ethereal mob found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_ethereal_mob);
}

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

Tpp tp_random_zorblin(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_zorblin.size())) {
    ERR("No zorblin found");
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_zorblin);
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

const Tpidmap &tp_get_spells(void)
{
  TRACE_NO_INDENT();
  return tp_spells;
}

Tpp tp_random_bodypart(int bodypart)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_bodypart[ bodypart ].size())) {
    return nullptr;
  }
  return tp_get_with_no_rarity_filter(tp_bodypart[ bodypart ]);
}

static Tpp tp_get_bodypart(const int bodypart, const std::string &which, int step)
{
  TRACE_NO_INDENT();

  int  index = 0;
  bool found {};

  for (auto b : tp_bodypart[ bodypart ]) {
    if (b->name() == which) {
      found = true;
      break;
    }
    index++;
  }

  if (! found) {
    index = 0;
  }

  index += step;

  if (index < 0) {
    index = (int) tp_bodypart[ bodypart ].size() - 1;
  }

  if (index >= (int) tp_bodypart[ bodypart ].size()) {
    index = 0;
  }

  return tp_bodypart[ bodypart ][ index ];
}

Tpp tp_get_next_bodypart(int bodypart, const std::string &which)
{
  TRACE_NO_INDENT();
  return tp_get_bodypart(bodypart, which, 1);
}

Tpp tp_get_prev_bodypart(int bodypart, const std::string &which)
{
  TRACE_NO_INDENT();
  return tp_get_bodypart(bodypart, which, -1);
}
