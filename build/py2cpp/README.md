# py2cpp - historical conversion tooling (optional, not part of the build)

The game no longer embeds Python. Everything in `src/things/` and `src/modules/` was generated
**once** from the former `python/` tree by `py2cpp.py`; those C++ files are now the source of truth
and are meant to be edited by hand. Nothing here is used by `make`.

It is kept so the conversion can be audited or reproduced. To re-run it you need the *original*
`python/` tree and the *original* (pre-conversion) `src/py_*.cpp` files, neither of which is in this
repository any more, and the paths inside the scripts point at scratch locations (`/tmp/orig`, ...).

* `py2cpp.py`            - AST based python -> C++ translator for the restricted python subset the modules used.
                           Fails loudly (raises `Unsupported`) rather than guessing.
* `gen_native_api.py`,
  `gen_native_tp.py`,
  `native_manual.cpp.in` - one-shot generators for `src/native_thing.cpp`, `native_level.cpp`, `native_tp.cpp`.
* `apitable.json`        - signatures of the `my::` API used by the translator.
* `harness/`             - differential tests: the original python modules are run against a recording mock of the
                           python `my` module, the generated C++ against a recording fake of the native layer, and the
                           call logs / return values are compared. Needs SDL stubs to build outside the real toolchain.
