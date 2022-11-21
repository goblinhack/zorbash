//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_game.hpp"
// REMOVED #include "my_main.hpp"
#include "my_python.hpp"
#include "my_sound.hpp"
// REMOVED #include "my_sys.hpp"
// REMOVED #include "my_thing.hpp"
#include <string.h>  // do not remove
#include <strings.h> // do not remove

PyObject *sound_load_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *file   = nullptr;
  char *name   = nullptr;
  float volume = 0;

  static char *kwlist[] = {(char *) "volume", (char *) "file", (char *) "name", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "fss", kwlist, &volume, &file, &name)) {
    ERR("sound_load: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! file) {
    ERR("sound_load: Missing file attr");
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("sound_load: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("sound_load(volume=%f, file=%s, name=%s)", volume, file, name);

  std::string filearg = file;
  std::string alias   = name;
  sound_load(volume, filearg, alias);

  Py_RETURN_TRUE;
}

PyObject *sound_play_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *name = nullptr;

  static char *kwlist[] = {(char *) "name", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &name)) {
    ERR("sound_play: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("sound_play: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("sound_play(name=%s)", name);

  std::string alias = name;
  if (! sound_play(alias)) {
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}

PyObject *sound_play_channel_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  char *name    = nullptr;
  int   channel = 0;

  static char *kwlist[] = {(char *) "channel", (char *) "name", nullptr};

  if (! PyArg_ParseTupleAndKeywords(args, keywds, "is", kwlist, &channel, &name)) {
    ERR("sound_play_channel: Bad arguments");
    Py_RETURN_FALSE;
  }

  if (! name) {
    ERR("sound_play_channel: Missing name attr");
    Py_RETURN_FALSE;
  }

  PY_DBG("sound_play_channel(channel=%d, name=%s)", channel, name);

  std::string alias = name;
  if (! sound_play_channel(channel, alias)) {
    Py_RETURN_FALSE;
  }

  Py_RETURN_TRUE;
}
