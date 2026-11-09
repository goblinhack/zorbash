//
// Copyright goblinhack@gmail.com
//
// Registry of native event callbacks, replacing the python module lookup by name.
//

#include "my_native.hpp"

#include "my_callstack.hpp"
#include "my_game.hpp"
#include "my_main.hpp"

#include <string_view>
#include <unordered_map>

namespace {

struct StringHash {
  using is_transparent = void;
  size_t operator()(std::string_view sv) const { return std::hash< std::string_view > {}(sv); }
};

struct NativeEntry {
  int      nargs {};
  NativeFn fn;
};

using FnTable     = std::unordered_map< std::string, NativeEntry, StringHash, std::equal_to<> >;
using ModuleTable = std::unordered_map< std::string, FnTable, StringHash, std::equal_to<> >;

ModuleTable &native_modules(void)
{
  static ModuleTable modules;
  return modules;
}

} // namespace

void native_register(const char *module, const char *name, int nargs, NativeFn fn)
{
  TRACE_NO_INDENT();

  auto &entry = native_modules()[ module ][ name ];
  if (entry.fn) {
    ERR("Native callback %s.%s registered more than once", module, name);
    return;
  }

  entry.nargs = nargs;
  entry.fn    = std::move(fn);
}

NativeRet native_dispatch(const char *module, const char *name, const int64_t *args, int nargs)
{
  TRACE_NO_INDENT();

  auto &modules = native_modules();

  auto m = modules.find(std::string_view(module));
  if (m == modules.end()) {
    ERR("Native callback: no such module '%s' (calling %s)", module, name);
    return {};
  }

  auto f = m->second.find(std::string_view(name));
  if (f == m->second.end()) {
    ERR("Native callback: module '%s' has no function '%s'", module, name);
    return {};
  }

  if (f->second.nargs != nargs) {
    ERR("Native callback: %s.%s takes %d arguments but was called with %d", module, name, f->second.nargs, nargs);
    return {};
  }

  return f->second.fn(args);
}

void native_init(void)
{
  TRACE_NO_INDENT();

  native_init_all();
}
