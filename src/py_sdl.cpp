//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include "my_sys.h"
#include "my_python.h"
#include "my_py_sdl.h"
#include <SDL.h>

/*
 * Borrowed from https://github.com/holtrop/pysdl2
 */
PYFUNC(SDLGetKeyState, "get a snapshot of the current keyboard state")
{ TRACE_AND_INDENT();
  int numkeys;
  const uint8_t *keys = SDL_GetKeyboardState(&numkeys);

  PyObject *lst = PyList_New(numkeys);

  for (int i = 0; i < numkeys; i++) {
    PyList_SetItem(lst, i, Py_BuildValue("i", keys[i]));
  }

  return (lst);
}
