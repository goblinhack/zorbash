//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"
// REMOVED #include "my_py_thing.hpp"
// REMOVED #include "my_py_tp.hpp"
// REMOVED #include <frameobject.h>
#include <map>

#include "my_callstack.hpp"
#include "my_main.hpp"
// REMOVED #include "my_monst.hpp"
// REMOVED #include "my_ptrcheck.hpp"
#include "my_py_sdl.hpp"
// REMOVED #include "my_python.hpp"
// REMOVED #include "my_random.hpp"
#include "my_sdl_proto.hpp"
// REMOVED #include "my_sound.hpp"
// REMOVED #include "my_string.hpp"
// REMOVED #include "my_thing.hpp"
// REMOVED #include "my_thing_template.hpp"

PyObject *my_mod;

static std::string get_env(const char *env)
{
  auto t = std::getenv(env);
  if (t)
    return t;
  return "";
}

void py_init(char *argv[])
{
  TRACE_AND_INDENT();

  CON("INI: Python version is %s", PYVER);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  auto pythonpath = get_env("PYTHONPATH");
  CON("INI: PYTHONPATH is currently '%s'", pythonpath.c_str());
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  auto newpath = pythonpath;
  if (pythonpath.size()) {
    newpath += PATHSEP;
  }
  newpath += EXEC_PYTHONPATH;
  newpath += PATHSEP;
  newpath += EXEC_DIR;
  newpath += PATHSEP;
#ifdef INIT
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYVER;
  newpath += PATHSEP;
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYVER DIR_SEP "lib-dynload";
  newpath += PATHSEP;
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "lib" DIR_SEP "python" PYVER DIR_SEP "site-packages";
  newpath += PATHSEP;
  newpath += "C:" DIR_SEP "msys64" DIR_SEP "mingw64" DIR_SEP "bin";
#endif

  // Attempt to append to path.
  CON("INI: PYTHONPATH is now '%s'", newpath.c_str());
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //
#ifdef _WIN32
  _putenv_s("PYTHONPATH", newpath.c_str());
#else
  setenv("PYTHONPATH", newpath.c_str(), 1);
#endif

  CON("INI: Calling PyImport_AppendInittab");
  PyImport_AppendInittab("my", +py_my_module_create);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  CON("INI: Calling Py_Initialize");
  Py_Initialize();
  if (g_errored) {
    return;
  }

  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  py_add_to_path("python");
  py_add_to_path(".." DIR_SEP "python");
  py_add_to_path(GFX_PATH);
  py_add_to_path(DATA_PATH);
  py_add_to_path(EXEC_PYTHONPATH);
  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  DBG3("INI: Calling PyImport_ImportModule for my module");

  my_mod = PyImport_ImportModule("my");
  if (! my_mod) {
    py_err();
    ERR("Module my import failed");
    return;
  }

  py_my_module_add_stat_consts();

  DBG3("INI: Calling PyImport_ImportModule for init module");

  my_mod = PyImport_ImportModule("init");
  if (! my_mod) {
    py_err();
    ERR("Module init import failed");
    return;
  }

  sdl_flush_display();
  ////////////////////////////////////////////////////////////////////////////////////////////////////
}

PyObject *py_add_module(const char *mod)
{
  static std::map< std::string, PyObject * > py_mods;

  auto name = std::string(mod);
  auto pmod = py_mods[ name ];

  if (pmod != nullptr) {
    return pmod;
  }

  pmod = PyImport_ImportModule(mod);
  if (pmod == nullptr) {
    py_err();
    ERR("Module init '%s' import failed", mod);
    return nullptr;
  }
  py_mods[ name ] = pmod;

  return pmod;
}

void py_fini(void)
{
  TRACE_AND_INDENT();
  if (my_mod) {
    Py_Finalize();
  }
}
