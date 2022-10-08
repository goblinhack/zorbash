//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_array_bounds_check.hpp"
#include "my_dungeon.hpp"
#include "my_game.hpp"
#include "my_globals.hpp"
#include "my_ptrcheck.hpp"
#include "my_random.hpp"
#include "my_sys.hpp"
#include "my_thing.hpp"
#include "my_thing_ai.hpp"
#include "my_thing_template.hpp"

static Tpidmap tp_biome_dungeon_monst_class_any;
static Tpidmap tp_biome_dungeon_monst_class_a;
static Tpidmap tp_biome_dungeon_monst_class_b;
static Tpidmap tp_biome_dungeon_monst_class_c;
static Tpidmap tp_biome_dungeon_monst_class_d;
static Tpidmap tp_biome_dungeon_monst_class_e;

static Tpp tp_random_biome_dungeon_monst_class_any(void);
static Tpp tp_random_biome_dungeon_monst_class_a(void);
static Tpp tp_random_biome_dungeon_monst_class_b(void);
static Tpp tp_random_biome_dungeon_monst_class_c(void);
static Tpp tp_random_biome_dungeon_monst_class_d(void);
static Tpp tp_random_biome_dungeon_monst_class_e(void);

Tpp Level::get_biome_dungeon_random_monst(Dungeonp d, point p)
{
  int difficulty_offset = 0;

  if (d) {
    if (d->is_monst_class_a(p.x, p.y)) {
      dbg2("INF: Need biome dungeon monst class a");
      difficulty_offset = 1;
    }
    if (d->is_monst_class_b(p.x, p.y)) {
      dbg2("INF: Need biome dungeon monst class b");
      difficulty_offset = 50;
    }
    if (d->is_monst_class_c(p.x, p.y)) {
      dbg2("INF: Need biome dungeon monst class c");
      difficulty_offset = 100;
    }
    if (d->is_monst_class_d(p.x, p.y)) {
      dbg2("INF: Need biome dungeon monst class d");
      difficulty_offset = 200;
    }
    if (d->is_monst_class_e(p.x, p.y)) {
      dbg2("INF: Need biome dungeon monst class e");
      difficulty_offset = 500;
    }
  }

  Tpp tp = nullptr;

  if (difficulty_offset) {
    if (d1000() < d1000_chance_of_creating_monst_class_a + difficulty_offset) {
      tp = tp_random_biome_dungeon_monst_class_a(p);
    }
    if (! tp && (d1000() < d1000_chance_of_creating_monst_class_b + difficulty_offset)) {
      tp = tp_random_biome_dungeon_monst_class_b(p);
    }
    if (! tp && (d1000() < d1000_chance_of_creating_monst_class_c + difficulty_offset)) {
      tp = tp_random_biome_dungeon_monst_class_c(p);
    }
    if (! tp && (d1000() < d1000_chance_of_creating_monst_class_d + difficulty_offset)) {
      tp = tp_random_biome_dungeon_monst_class_d(p);
    }
    if (! tp && (d1000() < d1000_chance_of_creating_monst_class_e + difficulty_offset)) {
      tp = tp_random_biome_dungeon_monst_class_e(p);
    }
  }

  return tp;
}

Tpp Level::get_biome_dungeon_random_monst(point p) { return get_biome_dungeon_random_monst(nullptr, p); }

Tpp Level::tp_random_biome_dungeon_monst_class_any(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      return nullptr;
    }
    auto tpp = ::tp_random_biome_dungeon_monst_class_any();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    return tpp;
  }
}

Tpp Level::tp_random_biome_dungeon_monst_class_a(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class A monst at %d,%d", p.x, p.y);
      return tp_random_biome_dungeon_monst_class_any(p);
    }

    auto tpp = ::tp_random_biome_dungeon_monst_class_a();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class A '%s'", tpp->text_short_capitalised().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_biome_dungeon_monst_class_b(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class B monst at %d,%d", p.x, p.y);
      return tp_random_biome_dungeon_monst_class_any(p);
    }

    auto tpp = ::tp_random_biome_dungeon_monst_class_b();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class B '%s'", tpp->text_short_capitalised().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_biome_dungeon_monst_class_c(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class C monst at %d,%d", p.x, p.y);
      return tp_random_biome_dungeon_monst_class_b(p);
    }

    auto tpp = ::tp_random_biome_dungeon_monst_class_c();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class C '%s'", tpp->text_short_capitalised().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_biome_dungeon_monst_class_d(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class D monst at %d,%d", p.x, p.y);
      return tp_random_biome_dungeon_monst_class_c(p);
    }

    auto tpp = ::tp_random_biome_dungeon_monst_class_d();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class D '%s'", tpp->text_short_capitalised().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_biome_dungeon_monst_class_e(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class E monst at %d,%d", p.x, p.y);
      return tp_random_biome_dungeon_monst_class_d(p);
    }

    auto tpp = ::tp_random_biome_dungeon_monst_class_e();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class E '%s'", tpp->text_short_capitalised().c_str());
    return tpp;
  }
}

static Tpp tp_random_biome_dungeon_monst_class_any(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_biome_dungeon_monst_class_any.size())) {
    ERR("No monsts found");
    return nullptr;
  }
  return tp_get_with_rarity_filter(tp_biome_dungeon_monst_class_any);
}

static Tpp tp_random_biome_dungeon_monst_class_a(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_biome_dungeon_monst_class_a.size())) {
    return tp_random_biome_dungeon_monst_class_any();
  }
  return tp_get_with_rarity_filter(tp_biome_dungeon_monst_class_a);
}

static Tpp tp_random_biome_dungeon_monst_class_b(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_biome_dungeon_monst_class_b.size())) {
    return tp_random_biome_dungeon_monst_class_a();
  }
  return tp_get_with_rarity_filter(tp_biome_dungeon_monst_class_b);
}

static Tpp tp_random_biome_dungeon_monst_class_c(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_biome_dungeon_monst_class_c.size())) {
    return tp_random_biome_dungeon_monst_class_b();
  }
  return tp_get_with_rarity_filter(tp_biome_dungeon_monst_class_c);
}

static Tpp tp_random_biome_dungeon_monst_class_d(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_biome_dungeon_monst_class_d.size())) {
    return tp_random_biome_dungeon_monst_class_c();
  }
  return tp_get_with_rarity_filter(tp_biome_dungeon_monst_class_d);
}

static Tpp tp_random_biome_dungeon_monst_class_e(void)
{
  TRACE_NO_INDENT();
  if (unlikely(! tp_biome_dungeon_monst_class_e.size())) {
    return tp_random_biome_dungeon_monst_class_d();
  }
  return tp_get_with_rarity_filter(tp_biome_dungeon_monst_class_e);
}

void tp_biome_dungeon_monst_class_add(Tpp tp)
{
  if (tp->is_monst()) {
    tp_biome_dungeon_monst_class_any.push_back(tp);
  }
  if (tp->is_monst_class_a()) {
    tp_biome_dungeon_monst_class_a.push_back(tp);
  }
  if (tp->is_monst_class_b()) {
    tp_biome_dungeon_monst_class_b.push_back(tp);
  }
  if (tp->is_monst_class_c()) {
    tp_biome_dungeon_monst_class_c.push_back(tp);
  }
  if (tp->is_monst_class_d()) {
    tp_biome_dungeon_monst_class_d.push_back(tp);
  }
  if (tp->is_monst_class_e()) {
    tp_biome_dungeon_monst_class_e.push_back(tp);
  }
}
