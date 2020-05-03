//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

// REMOVED #include <SDL.h>
#include "my_main.h"
#include "my_gl.h"
#include "my_python.h"
// REMOVED #include "my_sdl.h"
#include "my_tex.h"
// REMOVED #include "my_pixel.h"

PyObject *tex_load_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *a = 0;
    char *b = 0;

    static char *kwlist[] = {(char*) "file", (char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "ss", kwlist, &a, &b)) {
        Py_RETURN_NONE;
    }

    if (!a) {
        ERR("tex_load, missing file attr");
        Py_RETURN_NONE;
    }

    if (!b) {
        ERR("tex_load, missing name attr");
        Py_RETURN_NONE;
    }

    DBG("Python: tex_load(file=%s, name=%s)", a, b);

    tex_load(a, b, GL_NEAREST);

    Py_RETURN_NONE;
}
