//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_python.h"
#include "my_main.h"
#include "my_callstack.h"
#include "my_ascii.h"

PyObject *text_size_ (PyObject *obj, PyObject *args, PyObject *keywds)
{_
  wchar_t *text = 0;

  static char *kwlist[] = {
    (char*) "text",
    0
  };

  if (!PyArg_ParseTupleAndKeywords(args, keywds, "u", kwlist, &text)) {
    ERR("text_size: Bad args");
    Py_RETURN_NONE;
  }

  if (!text) {
    ERR("No text");
    Py_RETURN_NONE;
  }

  std::wstring col = L"none";
  auto b = std::wstring(text);
  double w = ascii_strlen(b, &col);
  double h = 1;

  return (Py_BuildValue("ddu", w, h, col.c_str()));
}
