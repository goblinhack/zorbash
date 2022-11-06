//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_sdl.hpp"
#include "my_python.hpp"
#include "my_sys.hpp"
#include <SDL.h>

/*
 * Borrowed from https://github.com/holtrop/pysdl2
 */
PYFUNC(SDLGetKeyState, "get a snapshot of the current keyboard state")
{
  TRACE_AND_INDENT();
  int            numkeys;
  const uint8_t *keys = SDL_GetKeyboardState(&numkeys);

  PyObject *lst = PyList_New(numkeys);

  for (int i = 0; i < numkeys; i++) {
    PyList_SetItem(lst, i, Py_BuildValue("i", keys[ i ]));
  }

  return lst;
}
