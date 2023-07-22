//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_vector_bounds_check.hpp"

Tpnamemap tp_name_map;
Tpidmap   tp_id_map;

static uint8_t tp_init_done;

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find(const std::string &name)
{
  TRACE_NO_INDENT();

  auto result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) { return (result->second); }

  return nullptr;
}

std::vector< Tpp > tp_find_wildcard(const std::string &name)
{
  TRACE_NO_INDENT();

  std::vector< Tpp > out;
  auto               result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    out.push_back(result->second);
    return out;
  }

  if (name == "random_food") {
    out.push_back(tp_random_food());
    return out;
  }
  if (name == "random_gold") {
    out.push_back(tp_random_gold());
    return out;
  }
  if (name == "random_treasure") {
    out.push_back(tp_random_treasure());
    return out;
  }
  if (name == "random_item_class_A") {
    out.push_back(tp_random_item_class_A());
    return out;
  }
  if (name == "random_item_class_B") {
    out.push_back(tp_random_item_class_B());
    return out;
  }
  if (name == "random_item_class_C") {
    out.push_back(tp_random_item_class_C());
    return out;
  }
  if (name == "random_monst_class_A") {
    out.push_back(tp_random_monst_class_A());
    return out;
  }
  if (name == "random_monst_class_B") {
    out.push_back(tp_random_monst_class_B());
    return out;
  }
  if (name == "random_monst_class_C") {
    out.push_back(tp_random_monst_class_C());
    return out;
  }
  if (name == "random_monst_class_D") {
    out.push_back(tp_random_monst_class_D());
    return out;
  }
  if (name == "random_monst_class_E") {
    out.push_back(tp_random_monst_class_E());
    return out;
  }
  if (name == "random_item_not_a_container_class_A") {
    out.push_back(tp_random_item_not_a_container_class_A());
    return out;
  }
  if (name == "random_item_not_a_container_class_B") {
    out.push_back(tp_random_item_not_a_container_class_B());
    return out;
  }
  if (name == "random_item_not_a_container_class_C") {
    out.push_back(tp_random_item_not_a_container_class_C());
    return out;
  }
  if (name == "random_weapon_class_A") {
    out.push_back(tp_random_weapon_class_A());
    return out;
  }
  if (name == "random_weapon_class_B") {
    out.push_back(tp_random_weapon_class_B());
    return out;
  }
  if (name == "random_weapon_class_C") {
    out.push_back(tp_random_weapon_class_C());
    return out;
  }
  if (name == "random_treasure_class_A") {
    out.push_back(tp_random_treasure_class_A());
    return out;
  }
  if (name == "random_treasure_class_B") {
    out.push_back(tp_random_treasure_class_B());
    return out;
  }
  if (name == "random_treasure_class_C") {
    out.push_back(tp_random_treasure_class_C());
    return out;
  }
  if (name == "random_staff_class_A") {
    out.push_back(tp_random_staff_class_A());
    return out;
  }
  if (name == "random_staff_class_B") {
    out.push_back(tp_random_staff_class_B());
    return out;
  }
  if (name == "random_staff_class_C") {
    out.push_back(tp_random_staff_class_C());
    return out;
  }
  if (name == "random_ring_class_A") {
    out.push_back(tp_random_ring_class_A());
    return out;
  }
  if (name == "random_ring_class_B") {
    out.push_back(tp_random_ring_class_B());
    return out;
  }
  if (name == "random_ring_class_C") {
    out.push_back(tp_random_ring_class_C());
    return out;
  }
  if (name == "random_dirt") {
    out.push_back(tp_random_dirt());
    return out;
  }
  if (name == "random_grass_dry") {
    out.push_back(tp_random_grass_dry());
    return out;
  }
  if (name == "random_grass_wet") {
    out.push_back(tp_random_grass_wet());
    return out;
  }
  if (name == "random_fungus_edible") {
    out.push_back(tp_random_fungus_edible());
    return out;
  }
  if (name == "random_fungus_poison") {
    out.push_back(tp_random_fungus_poison());
    return out;
  }
  if (name == "random_fungus_withered") {
    out.push_back(tp_random_fungus_withered());
    return out;
  }
  if (name == "random_magic_stone") {
    out.push_back(tp_random_magic_stone());
    return out;
  }
  if (name == "random_foliage") {
    out.push_back(tp_random_foliage());
    return out;
  }
  if (name == "random_spiderweb") {
    out.push_back(tp_random_spiderweb());
    return out;
  }
  if (name == "random_portal") {
    out.push_back(tp_random_portal());
    return out;
  }
  if (name == "random_small_ripple") {
    out.push_back(tp_random_small_ripple());
    return out;
  }
  if (name == "random_large_ripple") {
    out.push_back(tp_random_large_ripple());
    return out;
  }
  if (name == "random_red_splatter") {
    out.push_back(tp_random_red_splatter());
    return out;
  }
  if (name == "random_green_splatter") {
    out.push_back(tp_random_green_splatter());
    return out;
  }
  if (name == "random_key") {
    out.push_back(tp_random_key());
    return out;
  }
  if (name == "random_potion") {
    out.push_back(tp_random_potion());
    return out;
  }
  if (name == "random_staff") {
    out.push_back(tp_random_staff());
    return out;
  }
  if (name == "random_ring") {
    out.push_back(tp_random_ring());
    return out;
  }
  if (name == "random_weapon") {
    out.push_back(tp_random_weapon());
    return out;
  }
  if (name == "random_ascend_dungeon") {
    out.push_back(tp_random_ascend_dungeon());
    return out;
  }
  if (name == "random_descend_dungeon") {
    out.push_back(tp_random_descend_dungeon());
    return out;
  }
  if (name == "random_brazier") {
    out.push_back(tp_random_brazier());
    return out;
  }
  if (name == "random_barrel") {
    out.push_back(tp_random_barrel());
    return out;
  }
  if (name == "random_door") {
    out.push_back(tp_random_door());
    return out;
  }
  if (name == "random_secret_door") {
    out.push_back(tp_random_secret_door());
    return out;
  }
  if (name == "random_mob") {
    out.push_back(tp_random_mob());
    return out;
  }
  if (name == "random_trap") {
    out.push_back(tp_random_trap());
    return out;
  }
  if (name == "random_ethereal_mob") {
    out.push_back(tp_random_ethereal_mob());
    return out;
  }
  if (name == "random_mob_challenge_class_A") {
    out.push_back(tp_random_mob_challenge_class_A());
    return out;
  }
  if (name == "random_mob_challenge_class_B") {
    out.push_back(tp_random_mob_challenge_class_B());
    return out;
  }
  if (name == "random_red_blood") {
    out.push_back(tp_random_red_blood());
    return out;
  }
  if (name == "random_green_blood") {
    out.push_back(tp_random_green_blood());
    return out;
  }
  if (name == "random_bones") {
    out.push_back(tp_random_bones());
    return out;
  }
  if (name == "random_wall_dungeon") {
    out.push_back(tp_random_wall_dungeon());
    return out;
  }
  if (name == "random_sewer_wall") {
    out.push_back(tp_random_sewer_wall());
    return out;
  }
  if (name == "random_rock") {
    out.push_back(tp_random_rock());
    return out;
  }
  if (name == "random_floor") {
    out.push_back(tp_random_floor());
    return out;
  }
  if (name == "random_deco") {
    out.push_back(tp_random_deco());
    return out;
  }
  if (name == "random_ascend_sewer") {
    out.push_back(tp_random_ascend_sewer());
    return out;
  }
  if (name == "random_descend_sewer") {
    out.push_back(tp_random_descend_sewer());
    return out;
  }

  //
  // Try matching patterns e.g. is_monst_class_B
  //
  for (auto &tp : tp_id_map) {
    if (tp->matches(name)) { out.push_back(tp); }
  }

  return out;
}

std::vector< Tpp > tp_find_wildcard(Levelp l, point p, const std::string &name)
{
  TRACE_NO_INDENT();

  std::vector< Tpp > out;

  auto result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    out.push_back(result->second);
    return out;
  }

  if (name == "random_monst_class_A") {
    out.push_back(l->get_random_monst(p, MONST_CLASS_A));
    return out;
  }
  if (name == "random_monst_class_B") {
    out.push_back(l->get_random_monst(p, MONST_CLASS_B));
    return out;
  }
  if (name == "random_monst_class_C") {
    out.push_back(l->get_random_monst(p, MONST_CLASS_C));
    return out;
  }
  if (name == "random_monst_class_D") {
    out.push_back(l->get_random_monst(p, MONST_CLASS_D));
    return out;
  }
  if (name == "random_monst_class_E") {
    out.push_back(l->get_random_monst(p, MONST_CLASS_E));
    return out;
  }

  return tp_find_wildcard(name);
}

Tpp tp_find(uint32_t id)
{
  TRACE_NO_INDENT();
  auto result = get(tp_id_map, id - 1);
  if (! result) { ERR("Thing template %" PRIX32 " not found", id); }

  return result;
}

uint8_t tp_init(void)
{
  TRACE_NO_INDENT();
  tp_init_done = true;

  tp_random_init();
  tp_fixup();
  tp_assign_allies();

  return true;
}

void tp_fini(void)
{
  TRACE_NO_INDENT();
  if (tp_init_done) { tp_init_done = false; }
  for (auto &tp : tp_name_map) {
    delete tp.second;
  }
}

Tpp tp_load(int id, std::string const &name, const std::string &text_long_name, const std::string &text_short_name)
{
  TRACE_NO_INDENT();
  if (tp_find(name)) { ERR("Thing template name [%s] already loaded", name.c_str()); }

  auto tp = new Tp();
  tp->name_set(name);
  tp->text_long_name_set(text_long_name);
  tp->text_short_name_set(text_short_name);

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (! result.second) { ERR("Thing insert name [%s] failed", name.c_str()); }

  tp_id_map.push_back(tp);
  tp->id = tp_id_map.size();

  return tp;
}

Tilep tp_first_tile(Tpp tp)
{
  TRACE_NO_INDENT();
  auto tiles = &tp->tiles;

  if (! tiles || tiles->empty()) { ERR("Tp %s has no tiles", tp->name().c_str()); }

  //
  // Get the first anim tile.
  //
  return (tile_first(tiles));
}
