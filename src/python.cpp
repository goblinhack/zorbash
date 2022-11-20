//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_py_level.hpp"
#include "my_py_thing.hpp"
#include "my_py_tp.hpp"
#include <frameobject.h>
#include <map>

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_monst.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_sdl.hpp"
#include "my_python.hpp"
#include "my_sdl_event.hpp"
#include "my_sound.hpp"
#include "my_string.hpp"
#include "my_thing.hpp"
#include "my_thing_template.hpp"

void py_exec(const char *str)
{
  TRACE_AND_INDENT();
  char stdOutErr[] =
      "import sys\n\
import my\n\
class CatchOutErr:\n\
  def __init__(self):\n\
    self.value = ''\n\
  def write(self, txt):\n\
    self.value += txt\n\
catchOutErr = CatchOutErr()\n\
sys.stdout = catchOutErr\n\
sys.stderr = catchOutErr\n\
";

  PyObject *pModule = PyImport_AddModule("__main__");
  py_err();

  LOG("EXEC: [%s]", str);
  PyRun_SimpleString(stdOutErr);
  py_err();

  PyRun_SimpleString(str);
  py_err();

  PyObject *catcher = PyObject_GetAttrString(pModule, "catchOutErr");
  py_err();

  if (catcher) {
    PyObject *output = PyObject_GetAttrString(catcher, "value");
    py_err();

    char *text = py_obj_to_string(output);
    if (text) {
      strchopc(text, '\n');
      CON("%s", text);
      myfree(text);
    }
  } else {
    CON("no output");
  }
}

void py_add_to_path(const char *path)
{
  TRACE_AND_INDENT();
  PyObject *py_cur_path, *py_item;
  char     *new_path;
  int       wc_len, i;
  wchar_t  *wc_new_path;
  char     *item;

  DBG3("Current system python path: (adding %s)", path);

  new_path    = dupstr(path, __FUNCTION__);
  py_cur_path = PySys_GetObject("path");

  for (i = 0; i < PyList_Size(py_cur_path); i++) {
    char *tmp = strappend(new_path, PATHSEP);
    myfree(new_path);
    new_path = tmp;

    py_item = PyList_GetItem(py_cur_path, i);

    if (! PyUnicode_Check(py_item)) {
      continue;
    }

    item = py_obj_to_string(py_item);
    if (! item) {
      continue;
    }

    DBG3("  %s", item);

    tmp = strappend(new_path, item);
    myfree(new_path);
    new_path = tmp;

    myfree(item);
  }

  /* Convert to wide chars. */
  wc_len = sizeof(wchar_t) * (strlen(new_path) + 1);

  wc_new_path = (wchar_t *) myzalloc(wc_len, "wchar str");
  if (! wc_new_path) {
    ERR("Path alloc fail");
  }

  DBG3("Set python path: %s", new_path);

  mbstowcs(wc_new_path, new_path, wc_len);
  PySys_SetPath(wc_new_path);
  myfree(new_path);
  myfree(wc_new_path);
}
