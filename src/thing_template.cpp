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

  if (unlikely(result != tp_name_map.end())) {
    return (result->second);
  }

  return nullptr;
}

Tpp tp_find_wildcard(const std::string &name)
{
  TRACE_NO_INDENT();

  auto result = tp_name_map.find(name);

  if (unlikely(result != tp_name_map.end())) {
    return (result->second);
  }

  if (name == "random_food") {
    return tp_random_food();
  }
  if (name == "random_gold") {
    return tp_random_gold();
  }
  if (name == "random_treasure") {
    return tp_random_treasure();
  }
  if (name == "random_item_class_A") {
    return tp_random_item_class_A();
  }
  if (name == "random_item_class_B") {
    return tp_random_item_class_B();
  }
  if (name == "random_item_class_C") {
    return tp_random_item_class_C();
  }
  if (name == "random_monst_class_A") {
    return tp_random_monst_class_A();
  }
  if (name == "random_monst_class_B") {
    return tp_random_monst_class_B();
  }
  if (name == "random_monst_class_C") {
    return tp_random_monst_class_C();
  }
  if (name == "random_monst_class_D") {
    return tp_random_monst_class_D();
  }
  if (name == "random_monst_class_E") {
    return tp_random_monst_class_E();
  }
  if (name == "random_item_not_a_container_class_A") {
    return tp_random_item_not_a_container_class_A();
  }
  if (name == "random_item_not_a_container_class_B") {
    return tp_random_item_not_a_container_class_B();
  }
  if (name == "random_item_not_a_container_class_C") {
    return tp_random_item_not_a_container_class_C();
  }
  if (name == "random_weapon_class_A") {
    return tp_random_weapon_class_A();
  }
  if (name == "random_weapon_class_B") {
    return tp_random_weapon_class_B();
  }
  if (name == "random_weapon_class_C") {
    return tp_random_weapon_class_C();
  }
  if (name == "random_treasure_class_A") {
    return tp_random_treasure_class_A();
  }
  if (name == "random_treasure_class_B") {
    return tp_random_treasure_class_B();
  }
  if (name == "random_treasure_class_C") {
    return tp_random_treasure_class_C();
  }
  if (name == "random_staff_class_A") {
    return tp_random_staff_class_A();
  }
  if (name == "random_staff_class_B") {
    return tp_random_staff_class_B();
  }
  if (name == "random_staff_class_C") {
    return tp_random_staff_class_C();
  }
  if (name == "random_ring_class_A") {
    return tp_random_ring_class_A();
  }
  if (name == "random_ring_class_B") {
    return tp_random_ring_class_B();
  }
  if (name == "random_ring_class_C") {
    return tp_random_ring_class_C();
  }
  if (name == "random_dirt") {
    return tp_random_dirt();
  }
  if (name == "random_dry_grass") {
    return tp_random_dry_grass();
  }
  if (name == "random_wet_grass") {
    return tp_random_wet_grass();
  }
  if (name == "random_enchantstone") {
    return tp_random_enchantstone();
  }
  if (name == "random_skillstone") {
    return tp_random_skillstone();
  }
  if (name == "random_foliage") {
    return tp_random_foliage();
  }
  if (name == "random_spiderweb") {
    return tp_random_spiderweb();
  }
  if (name == "random_portal") {
    return tp_random_portal();
  }
  if (name == "random_small_ripple") {
    return tp_random_small_ripple();
  }
  if (name == "random_large_ripple") {
    return tp_random_large_ripple();
  }
  if (name == "random_red_splatter") {
    return tp_random_red_splatter();
  }
  if (name == "random_green_splatter") {
    return tp_random_green_splatter();
  }
  if (name == "random_key") {
    return tp_random_key();
  }
  if (name == "random_potion") {
    return tp_random_potion();
  }
  if (name == "random_staff") {
    return tp_random_staff();
  }
  if (name == "random_ring") {
    return tp_random_ring();
  }
  if (name == "random_weapon") {
    return tp_random_weapon();
  }
  if (name == "random_ascend_dungeon") {
    return tp_random_ascend_dungeon();
  }
  if (name == "random_descend_dungeon") {
    return tp_random_descend_dungeon();
  }
  if (name == "random_brazier") {
    return tp_random_brazier();
  }
  if (name == "random_barrel") {
    return tp_random_barrel();
  }
  if (name == "random_door") {
    return tp_random_door();
  }
  if (name == "random_secret_door") {
    return tp_random_secret_door();
  }
  if (name == "random_mob") {
    return tp_random_mob();
  }
  if (name == "random_trap") {
    return tp_random_trap();
  }
  if (name == "random_ethereal_mob") {
    return tp_random_ethereal_mob();
  }
  if (name == "random_mob_challenge_class_A") {
    return tp_random_mob_challenge_class_A();
  }
  if (name == "random_mob_challenge_class_B") {
    return tp_random_mob_challenge_class_B();
  }
  if (name == "random_red_blood") {
    return tp_random_red_blood();
  }
  if (name == "random_green_blood") {
    return tp_random_green_blood();
  }
  if (name == "random_bones") {
    return tp_random_bones();
  }
  if (name == "random_wall_dungeon") {
    return tp_random_wall_dungeon();
  }
  if (name == "random_sewer_wall") {
    return tp_random_sewer_wall();
  }
  if (name == "random_rock") {
    return tp_random_rock();
  }
  if (name == "random_floor") {
    return tp_random_floor();
  }
  if (name == "random_deco") {
    return tp_random_deco();
  }
  if (name == "random_ascend_sewer") {
    return tp_random_ascend_sewer();
  }
  if (name == "random_descend_sewer") {
    return tp_random_descend_sewer();
  }

  //
  // Try matching patterns e.g. is_monst_class_B
  //
  for (auto &tp : tp_id_map) {
    if (tp->matches(name)) {
      return tp;
    }
  }

  return nullptr;
}

Tpp tp_find(uint32_t id)
{
  TRACE_NO_INDENT();
  auto result = get(tp_id_map, id - 1);
  if (! result) {
    ERR("Thing template %" PRIX32 " not found", id);
  }

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
  if (tp_init_done) {
    tp_init_done = false;
  }
  for (auto &tp : tp_name_map) {
    delete tp.second;
  }
}

Tpp tp_load(int id, std::string const &name, const std::string &text_long_name, const std::string &text_short_name)
{
  TRACE_NO_INDENT();
  if (tp_find(name)) {
    ERR("Thing template name [%s] already loaded", name.c_str());
  }

  auto tp = new Tp();
  tp->name_set(name);
  tp->text_long_name_set(text_long_name);
  tp->text_short_name_set(text_short_name);

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (! result.second) {
    ERR("Thing insert name [%s] failed", name.c_str());
  }

  tp_id_map.push_back(tp);
  tp->id = tp_id_map.size();

  return tp;
}

Tilep tp_first_tile(Tpp tp)
{
  TRACE_NO_INDENT();
  auto tiles = &tp->tiles;

  if (! tiles || tiles->empty()) {
    ERR("Tp %s has no tiles", tp->name().c_str());
  }

  //
  // Get the first anim tile.
  //
  return (tile_first(tiles));
}
