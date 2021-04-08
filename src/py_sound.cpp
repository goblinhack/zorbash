//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <strings.h> // do not remove
#include <string.h> // do not remove
#include "my_sys.h"
#include "my_gl.h"
#include "my_python.h"
#include "my_sound.h"
#include "my_main.h"

PyObject *sound_load_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *file = 0;
    char *name = 0;
    float volume = 0;

    static char *kwlist[] = {(char*)"volume", (char*) "file", (char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "fss", kwlist, 
                                     &volume, &file, &name)) {
        ERR("sound_load: bad arguments");
        Py_RETURN_FALSE;
    }

    if (!file) {
        ERR("sound_load: missing file attr");
        Py_RETURN_FALSE;
    }

    if (!name) {
        ERR("sound_load: missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("sound_load(volume=%f, file=%s, name=%s)", volume, file, name);

    std::string filearg = file;
    std::string namearg = name;
    sound_load(volume, filearg, namearg);

    Py_RETURN_TRUE;
}

PyObject *sound_play_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *name = 0;

    static char *kwlist[] = {(char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s", kwlist, &name)) {
        ERR("sound_play: bad arguments");
        Py_RETURN_FALSE;
    }

    if (!name) {
        ERR("sound_play: missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("sound_play(name=%s)", name);

    std::string namearg = name;
    if (!sound_play(namearg)) {
        Py_RETURN_FALSE;
    }

    Py_RETURN_TRUE;
}

PyObject *sound_play_channel_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    char *name = 0;
    int channel = 0;

    static char *kwlist[] = {(char*) "channel", (char*) "name", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "is", kwlist, &channel, &name)) {
        ERR("sound_play_channel: bad arguments");
        Py_RETURN_FALSE;
    }

    if (!name) {
        ERR("sound_play_channel: missing name attr");
        Py_RETURN_FALSE;
    }

    PY_DBG("sound_play_channel(channel=%d, name=%s)", channel, name);

    std::string namearg = name;
    if (!sound_play_channel(channel, namearg)) {
        Py_RETURN_FALSE;
    }

    Py_RETURN_TRUE;
}
