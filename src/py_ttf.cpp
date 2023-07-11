//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_ascii.hpp"
#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_python.hpp"

PyObject *text_size_(PyObject *obj, PyObject *args, PyObject *keywds)
{
  TRACE_AND_INDENT();
  wchar_t *text = nullptr;

  static char *kwlist[] = {(char *) "text", nullptr};

  TRACE_NO_INDENT();
  if (! PyArg_ParseTupleAndKeywords(args, keywds, "u", kwlist, &text)) {
    ERR("text_size: Bad args");
    Py_RETURN_NONE;
  }

  if (! text) {
    ERR("No text");
    Py_RETURN_NONE;
  }

  std::wstring col = L"none";
  auto         b   = std::wstring(text);
  double       w   = ascii_strlen(b, &col);
  double       h   = 1;

  return (Py_BuildValue("ddu", w, h, col.c_str()));
}
