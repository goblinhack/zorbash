//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_level.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_thing_template.hpp"
#include "my_vector_bounds_check.hpp"

Tpnamemap tp_name_map;
Tpidmap   tp_id_map;

static uint8_t tp_init_done;

Tp::Tp(void) { newptr(MTYPE_TP, this, "Tp"); }

Tp::~Tp(void) { oldptr(MTYPE_TP, this); }

Tpp tp_find(const std::string &name)
{
  TRACE_AND_INDENT();
  auto result = tp_name_map.find(name);

  if (unlikely(result == tp_name_map.end())) {
    return 0;
  }

  return (result->second);
}

Tpp tp_find(uint32_t id)
{
  TRACE_AND_INDENT();
  auto result = get(tp_id_map, id - 1);
  if (! result) {
    ERR("Thing template %" PRIX32 " not found", id);
  }

  return (result);
}

uint8_t tp_init(void)
{
  TRACE_AND_INDENT();
  tp_init_done = true;

  tp_random_init();
  tp_fixup();
  tp_assign_allies();

  return true;
}

void tp_fini(void)
{
  TRACE_AND_INDENT();
  if (tp_init_done) {
    tp_init_done = false;
  }
  for (auto &tp : tp_name_map) {
    delete tp.second;
  }
}

Tpp tp_load(int id, std::string const &name, const std::string &text_long_name, const std::string &text_short_name)
{
  TRACE_AND_INDENT();
  if (tp_find(name)) {
    ERR("Thing template name [%s] already used", name.c_str());
  }

  auto tp = new Tp();
  tp->name_set(name);
  tp->text_long_name_set(text_long_name);
  tp->text_short_name_set(text_short_name);

  auto result = tp_name_map.insert(std::make_pair(name, tp));
  if (result.second == false) {
    ERR("Thing insert name [%s] failed", name.c_str());
  }

  tp_id_map.push_back(tp);
  tp->id = tp_id_map.size();

  return (tp);
}

Tilep tp_first_tile(Tpp tp)
{
  TRACE_AND_INDENT();
  auto tiles = &tp->tiles;

  if (! tiles || tiles->empty()) {
    ERR("Tp %s has no tiles", tp->name().c_str());
  }

  //
  // Get the first anim tile.
  //
  return (tile_first(tiles));
}
