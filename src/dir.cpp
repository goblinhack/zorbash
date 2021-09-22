//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
// Please use spaces indent of 2, no tabs and column width of 120 to view.
//

#include <strings.h> // do not remove
#include <string.h>  // do not remove
#include <sys/param.h>
#include <unistd.h>
#include <sys/stat.h>
#include <strings.h> // do not remove, strlen

#include "my_sys.h"
#include "my_dir.h"
#include "my_string.h"
#include "my_ptrcheck.h"

/*
 * Does the requested dir exist?
 */
uint8_t dir_exists(const char *indir) {
  TRACE_AND_INDENT();
  struct stat buf;
  char *      dir;
  uint8_t     rc;

  /*
   * msys is crap and unless you remove the / from the end of the name
   * will not think it is a dir.
   */
  dir = dupstr(indir, "dir");
  strchopc(dir, DIR_SEP_CHAR);

  rc = 0;
  if (stat(dir, &buf) >= 0) {
    rc = S_ISDIR(buf.st_mode);
  }

  myfree(dir);

  return (rc);
}

/*
 * Given a directory, find out what ./ is.
 */
char *dir_dot(void) {
  TRACE_AND_INDENT();
  static char buf[MAXPATHLEN];

  dospath2unix(getcwd(buf, sizeof(buf)));

  return (buf);
}

/*
 * Remove \ and change to /
 * Given a directory, find out what ../ is.
 */
char *dir_dotdot(char *s) {
  TRACE_AND_INDENT();
  uint32_t size;
  char *   end;

  size = (uint32_t) strlen(s);
  if (size <= 1) {
    return (s);
  }

  /*
   * Skip trailing /
   */
  end = s + size - 2;
  while ((end >= s) && (*end != '/') && (*end != '\\')) {
    end--;
  }

  *(end + 1) = '\0';

  return (dospath2unix(s));
}

/*
 * Remove \ and change to /
 */
char *dospath2unix(char *in) {
  TRACE_AND_INDENT();
  char *s = in;

  while (*s) {
    if (*s == '\\') {
      *s = '/';
    }

    s++;
  }

  return (in);
}
