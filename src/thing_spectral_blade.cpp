#include "my_array_bounds_check.hpp"
#include "my_game.hpp"
#include "my_thing.hpp"

int Thing::is_spectral_blade(void)
{
  TRACE_NO_INDENT();
  return (tp()->is_spectral_blade());
}
