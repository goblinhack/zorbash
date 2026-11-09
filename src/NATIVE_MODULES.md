# Python removed: native thing/tile/sound/room modules

The game no longer embeds or depends on Python at run time. The ~925 python modules that used to be
loaded at startup are now plain C++ files.

## Layout

| Was                                      | Is now                                             |
|------------------------------------------|----------------------------------------------------|
| `python/things/amulets/amulet_endurance.py` | `src/things/amulets/amulet_endurance.cpp`       |
| `python/gfx.py`, `sound.py`, `level_biome_*.py`, `skill_tree.py`, ... | `src/modules/gfx.cpp`, ... (top level modules go in `modules/` because the old names clash with existing `src/*.cpp`) |
| `python/init.py` (plugin loader)         | `native_modules.cpp` (`native_init_all()`), called from `main.cpp` |
| `my` python module (`my.tile()`, `my.thing_msg()`, ...) | `namespace my` (`native_thing.cpp`, `native_level.cpp`, `native_tp.cpp`, `my_native_api.hpp`) |
| `py_call_void_fn("me", "on_hit", ...)`   | `native_call_void_fn(...)`, dispatching through the registry in `native_registry.cpp` |

`Makefile.base` already finds `.cpp` files recursively, so nothing needs registering with the build.
`-I.` was added to the compiler flags so files in subdirectories can `#include "my_native.hpp"`.

## What a converted module looks like

```cpp
namespace mod_things_amulets_amulet_endurance {

static void on_equip(uint32_t owner, uint32_t me, int x, int y) { ... }          // was: def on_equip(owner, me, x, y)
static void tp_init(const std::string &name, ...)                                // was: def tp_init(...)
{
  Tpp self = my::tp_load(name, text_long_name, text_short_name);
  self->gfx_ascii_shown_set(true);                                              // was: my.gfx_ascii_shown(self, True)
  my::tile(self, {.tile = name, .delay_ms = 100});                              // was: my.tile(self, tile=name, delay_ms=100)
  self->on_equip_do_set("me.on_equip()");
}

void module_init(void)    // was: the module body (`init()` at the bottom of the .py)
{
  native_register("amulet_endurance", "on_equip", 4, [](const int64_t *a) -> NativeRet { ... });
  init();
}
}
```

* Things cross the boundary as `uint32_t` thing ids, exactly as they did in python.
* `"me.on_hit()"` strings still work: `me` is the template name, the module is looked up in the registry by file name.
  Every module function whose parameters are all ints/thing ids is registered automatically by the generated code.
  For hand-written new modules, call `native_register(module, fn, nargs, thunk)` for each callback.
* Modules run in the same order the python loader used (sorted path), via `native_init_all()`.
* Imported helper modules (e.g. `gnome_all`, `skill_*0`) have a header next to the `.cpp` (`gnome_all.hpp`).

## Intentional behavior differences

1. **The in-game console no longer executes Python.** Unrecognised input now prints `Unknown command` instead of being
   passed to `py_exec()`. The "You can also enter python code here" hint was removed.
2. **`tp_init` runs once.** The old loader executed every module, but `py_add_module()` (first callback dispatch) imported it
   *again*, re-running `tp_init`. `my.tile()` appends, so ~340 modules that have callbacks and tiles ended up with their
   animation frame list duplicated after the first callback. That no longer happens.
3. A failed lookup (bad thing id etc.) still logs an error through `ERR()` and returns false/0/empty. Where python would then
   have raised (e.g. iterating the `None` returned by a failed `level_get_all`) and aborted the rest of the callback, the
   native code just sees an empty list and carries on. Only reachable on the error path.
4. `thing_get_followers` now actually returns the followers (it allocated a zero length list and failed on `PyList_SetItem`).
5. `random.choice` in `brazier` (cosmetic colour) uses the non-deterministic RNG, as python's unseeded `random` did.
6. `tp_update()` (a validity check with no effect) was dropped.

## Pre-existing data bugs found (preserved, not fixed)

* `things/spells/spell_of_haste.py` creates template `spell_of_haste` but wires `"me.on_use()"`; `me` resolves to the
  template name so the callback lookup fails (it failed the same way under python).
* `things/traps/trap_dart.py` sets `on_fall_do` to `me.on_fall()` but defines no `on_fall`.
* `things/dungeon/bridge.py` has a dead `else:` branch using an invalid `bot3_tile=` keyword (dropped).

## Build tooling

`build/ramdisk.py` still runs at build time, so a `python3` *interpreter* is a build-tool dependency (not Python headers or
libraries). `build/tidy_python.sh` was removed (it maintained the python templates). `build/windows/*` no longer bundles a
python runtime. `build/py2cpp/` holds the one-shot conversion tooling for reference; it is not used by the build.
