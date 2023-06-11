//
// Copyright Neil McGill, goblinhack@gmail.com
//

#include "my_callstack.hpp"
#include "my_main.hpp"
#include "my_ptrcheck.hpp"
#include "my_py_sdl.hpp"
#include "my_string.hpp"

void py_exec(const char *str)
{
  TRACE_AND_INDENT();
  char stdOutErr[]
      = "import sys\n\
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

  //
  // Windows hack
  //
  auto tmp  = strsub(path, "\\", "@@@@", "path");
  auto tmp2 = strsub(tmp, "@@@@", "\\\\", "path");

  CON("INI: Add python path: %s", path);
  flush_the_console();

  //
  // NOTE: PySys_SetPath is deprecated.
  //
  std::string cmd = "import sys\n";
  cmd += "sys.path.append(\"";
  cmd += std::string(tmp2);
  cmd += "\")\n";
  PyRun_SimpleString(cmd.c_str());

  myfree(tmp);
  myfree(tmp2);
}
