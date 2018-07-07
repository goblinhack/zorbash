/*
 * Copyright (C) 2011-2020 goblinhack@gmail.com
 *
 * See the LICENSE file for license.
 */

#include <SDL.h>
#include "my_main.h"
#include "my_python.h"
#include "my_sdl.h"
#include "my_py_game.h"
#include "my_game.h"
#include "my_wid.h"
#include "my_time_util.h"
#include "my_tile.h"

PyObject *game_set_sound_volume_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.sound_volume)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_music_volume_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.music_volume)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_display_sync_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.display_sync)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_full_screen_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.full_screen)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz1_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz1)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz2_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz2)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz3_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz3)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz4_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz4)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz5_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz5)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz6_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz6)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz7_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz7)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz8_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz8)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz9_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz9)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz10_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz10)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz11_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz11)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz12_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz12)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz13_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz13)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz14_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz14)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz15_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz15)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz16_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz16)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz17_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz17)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz18_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz18)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz19_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz19)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz20_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz20)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz21_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz21)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz22_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz22)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz23_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz23)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz24_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz24)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz25_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz25)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz26_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz26)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz27_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz27)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz28_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz28)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz29_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz29)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz30_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz30)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz31_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz31)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz32_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz32)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz33_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz33)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz34_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz34)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz35_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz35)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz36_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz36)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz37_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz37)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz38_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz38)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz39_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz39)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz40_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz40)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz41_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz41)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz42_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz42)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz43_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz43)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz44_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz44)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz45_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz45)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz46_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz46)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz47_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz47)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz48_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz48)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz49_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz49)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz50_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz50)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz51_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz51)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz52_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz52)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz53_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz53)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz54_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz54)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz55_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz55)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz56_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz56)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz57_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz57)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz58_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz58)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz59_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz59)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz60_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz60)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz61_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz61)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz62_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz62)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz63_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz63)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz64_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz64)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz65_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz65)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz66_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz66)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz67_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz67)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz68_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz68)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz69_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz69)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz70_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz70)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz71_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz71)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz72_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz72)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz73_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz73)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz74_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz74)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz75_ (PyObject *obj, PyObject *args,
                                 PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz75)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz76_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz76)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_zzz77_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.zzz77)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_move_left_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    game.map_wanted_at.x --;
    if (game.map_wanted_at.x < 0) {
        game.map_wanted_at.x = 0;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_move_right_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    game.map_wanted_at.x ++;
    if (game.map_wanted_at.x >= MAP_WIDTH - TILES_ACROSS) {
        game.map_wanted_at.x = MAP_WIDTH - TILES_ACROSS;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_move_up_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    game.map_wanted_at.y --;
    if (game.map_wanted_at.y < 0) {
        game.map_wanted_at.y = 0;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_move_down_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    game.map_wanted_at.y ++;
    if (game.map_wanted_at.y >= MAP_HEIGHT - TILES_DOWN) {
        game.map_wanted_at.y = MAP_HEIGHT - TILES_DOWN;
    }

    Py_RETURN_NONE;
}

PyObject *game_set_sdl_delay_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
    static char *kwlist[] = {(char*) "value", 0};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "d", kwlist,
                                     &game.sdl_delay)) {
        Py_RETURN_NONE;
    }

    Py_RETURN_NONE;
}

PY_BODY_VOID_FN(game_map_create)
PY_BODY_VOID_FN(game_map_created)
PY_BODY_VOID_FN(game_map_destroy)
