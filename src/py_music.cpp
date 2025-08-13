//
// Copyright goblinhack@gmail.com
//

#include "my_gl.hpp"
#include "my_main.hpp"
#include "my_music.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include <string.h>  // do not remove
#include <strings.h> // do not remove

PyObject *music_load_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char    *file = nullptr;
  char    *name = nullptr;
  uint32_t rate = 44100;

  static char *kwlist[] = {(char *) "rate", (char *) "file", (char *) "name", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "Iss", kwlist, &rate, &file, &name)) {
    PY_ERR("music_load: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! file) {
    PY_ERR("music_load: Missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    PY_ERR("music_load: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("music_load(rate=%u, file=%s, name=%s)", rate, file, name);

  std::string filearg = file;
  std::string namearg = name;
  music_load(rate, filearg, namearg);

  Py_RETURN_TRUE;
}

PyObject *music_play_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();
  char *name = nullptr;

  static char *kwlist[] = {(char *) "name", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &name)) {
    PY_ERR("music_play: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! name) {
    PY_ERR("music_play: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("music_play(name=%s)", name);

  std::string namearg = name;

  if (! music_play(namearg)) {
    PY_ERR("music_play: Failed");
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *music_halt_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_NO_INDENT();

  PY_DBG("music_halt()");

  if (! music_halt()) {
    PY_ERR("music_halt: Failed");
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}
