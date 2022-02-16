//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

// REMOVED #include "my_dice.hpp"
#include "my_game.hpp"
// REMOVED #include "my_random.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_thing.hpp"
#include "my_thing_template.hpp"
// REMOVED #include "my_tile.hpp"
// REMOVED #include "my_vector_bounds_check.hpp"

Tpp Level::tp_random_monst(const point p)
{
  TRACE_NO_INDENT();
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

Tpp Level::tp_random_monst_class_a(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class A monst at %d,%d", p.x, p.y);
      return tp_random_monst(p);
    }

    auto tpp = ::tp_random_monst_class_a();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class A '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_monst_class_b(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class B monst at %d,%d", p.x, p.y);
      return tp_random_monst(p);
    }

    auto tpp = ::tp_random_monst_class_b();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class B '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_monst_class_c(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class C monst at %d,%d", p.x, p.y);
      return tp_random_monst_class_b(p);
    }

    auto tpp = ::tp_random_monst_class_c();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class C '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_monst_class_d(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class D monst at %d,%d", p.x, p.y);
      return tp_random_monst_class_c(p);
    }

    auto tpp = ::tp_random_monst_class_d();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class D '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_monst_class_e(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class E monst at %d,%d", p.x, p.y);
      return tp_random_monst_class_d(p);
    }

    auto tpp = ::tp_random_monst_class_e();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed monster class E '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_treasure_class_a(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class A treasure at %d,%d", p.x, p.y);
      return nullptr;
    }

    auto tpp = ::tp_random_treasure_class_a();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed treasure class A '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_treasure_class_b(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class B treasure at %d,%d", p.x, p.y);
      return tp_random_treasure_class_a(p);
    }

    auto tpp = ::tp_random_treasure_class_b();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed treasure class B '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_treasure_class_c(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class C treasure at %d,%d", p.x, p.y);
      return tp_random_treasure_class_b(p);
    }

    auto tpp = ::tp_random_treasure_class_c();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed treasure class C '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_weapon_class_a(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class A weapon at %d,%d", p.x, p.y);
      return ::tp_random_weapon();
    }

    auto tpp = ::tp_random_weapon_class_a();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed weapon class A '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_weapon_class_b(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class B weapon at %d,%d", p.x, p.y);
      return tp_random_weapon_class_a(p);
    }

    auto tpp = ::tp_random_weapon_class_b();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed weapon class B '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_weapon_class_c(const point p)
{
  TRACE_NO_INDENT();

  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      CON("Cannot place class C weapon at %d,%d", p.x, p.y);
      return tp_random_weapon_class_b(p);
    }

    auto tpp = ::tp_random_weapon_class_c();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }

    dbg("INF: Placed weapon class C '%s'", tpp->short_text_capitalise().c_str());
    return tpp;
  }
}

Tpp Level::tp_random_mob(const point p)
{
  TRACE_NO_INDENT();
  auto tries = 0U;
  for (;;) {
    if (tries++ > 10000) {
      return nullptr;
    }
    auto tpp = ::tp_random_mob();
    if (tpp->is_disliked_by_me(this, p)) {
      continue;
    }
    return tpp;
  }
}

Tpp Level::tp_random_mob_challenge_class_a(const point p)
{
  TRACE_NO_INDENT();
  return tp_random_mob(p);
}

Tpp Level::tp_random_mob_challenge_class_b(const point p)
{
  TRACE_NO_INDENT();
  return tp_random_mob(p);
}
