//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <strings.h> // do not remove
#include <string.h> // do not remove
#include "my_sys.h"
#include "my_gl.h"
#include "my_python.h"
#include "my_music.h"
#include "my_main.h"

PyObject *music_load_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *file = 0;
    char *name = 0;
    uint32_t rate = 44100;

    static char *kwlist[] = {(char*)"rate", (char*) "file", (char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Iss", kwlist,
                                     &rate, &file, &name)) {
        ERR("music_load: Bad arguments");
        Py_RETURN_FALSE;
    }

    if (!file) {
        ERR("music_load: Missing file attr");
        Py_RETURN_FALSE;
    }

    if (!name) {
        ERR("music_load: Missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("music_load(rate=%u, file=%s, name=%s)", rate, file, name);

    std::string filearg = file;
    std::string namearg = name;
    music_load(rate, filearg, namearg);

    Py_RETURN_TRUE;
}

PyObject *music_play_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *name = 0;

    static char *kwlist[] = {(char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &name)) {
        ERR("music_play: Bad arguments");
        Py_RETURN_FALSE;
    }

    if (!name) {
        ERR("music_play: Missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("music_play(name=%s)", name);

    std::string namearg = name;

    if (!music_play(namearg)) {
        ERR("music_play: Failed");
        Py_RETURN_FALSE;
    }

    Py_RETURN_TRUE;
}
