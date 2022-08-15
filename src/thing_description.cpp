//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
#include "my_monst.hpp"
#include "my_python.hpp"
#include "my_random.hpp"
#include "my_thing.hpp"

//
// Python callback upon being tick
//
std::vector< std::string > Thing::on_get_text_long_description(void)
{
  std::vector< std::string > out;

  auto on_get_text_long_description = tp()->on_get_text_long_description_do();
  if (std::empty(on_get_text_long_description)) {
    return out;
  }

  auto t = split_tokens(on_get_text_long_description, '.');
  if (t.size() == 2) {
    auto        mod   = t[ 0 ];
    auto        fn    = t[ 1 ];
    std::size_t found = fn.find("()");
    if (found != std::string::npos) {
      fn = fn.replace(found, 2, "");
    }

    if (mod == "me") {
      mod = name();
    }

    auto owner = top_owner();
    dbg("Call %s.%s(owner=%s, item=%s, %d, %d)", mod.c_str(), fn.c_str(), owner ? owner->to_string().c_str() : "<>",
        to_string().c_str(), (unsigned int) curr_at.x, (unsigned int) curr_at.y);
    return py_call_std_vector_string_fn(mod.c_str(), fn.c_str(), owner ? owner->id.id : 0, id.id,
                                        (unsigned int) curr_at.x, (unsigned int) curr_at.y);
  }

  ERR("Bad on_get_text_long_description call [%s] expected mod:function, got %d elems",
      on_get_text_long_description.c_str(), (int) on_get_text_long_description.size());

  return out;
}

const std::string &Thing::on_get_text_long_description_do(void)
{
  TRACE_NO_INDENT();
  return (tp()->on_get_text_long_description_do());
}

const std::string Thing::text_long_description(void)
{
  TRACE_NO_INDENT();

  //
  // If python overrides, return that string
  //
  auto override_description = on_get_text_long_description_do();
  if (! std::empty(override_description)) {
    auto d = on_get_text_long_description();
    if (d.size()) {
      return d[ 0 ];
    }
  }

  return (tp()->text_long_description());
}

const std::string Thing::text_long_description2(void)
{
  TRACE_NO_INDENT();

  //
  // If python overrides, return that string
  //
  auto override_description = on_get_text_long_description_do();
  if (! std::empty(override_description)) {
    auto d = on_get_text_long_description();
    if (d.size() > 1) {
      return d[ 1 ];
    }
  }

  return (tp()->text_long_description2());
}

const std::string Thing::text_long_description3(void)
{
  TRACE_NO_INDENT();

  //
  // If python overrides, return that string
  //
  auto override_description = on_get_text_long_description_do();
  if (! std::empty(override_description)) {
    auto d = on_get_text_long_description();
    if (d.size() > 2) {
      return d[ 2 ];
    }
  }

  return (tp()->text_long_description3());
}

const std::string &Thing::text_short_description(void)
{
  TRACE_NO_INDENT();
  return (tp()->text_short_description());
}
