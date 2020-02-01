//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#include <sys/param.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#include "my_main.h"
#include "my_dir.h"
#include "my_string.h"

/*
 * Does the requested dir exist?
 */
uint8_t dir_exists (const char *indir)
{_
    struct stat buf;
    char *dir;
    uint8_t rc;

    /*
     * msys is crap and unless you remove the / from the end of the name
     * will not think it is a dir.
     */
    dir = dupstr(indir, "dir");
    strchopc(dir, DIR_SEP_CHAR);

    rc = 0;
    if (stat(dir, &buf) >= 0) {
        rc = S_ISDIR(buf. st_mode);
    }

    myfree(dir);

    return (rc);
}

/*
 * Given a directory, find out what ./ is.
 */
char *dir_dot (void)
{_
    static char buf[MAXPATHLEN];

    dospath2unix(getcwd(buf, sizeof(buf)));

    return (buf);
}

/*
 * Remove \ and change to /
 * Given a directory, find out what ../ is.
 */
char *dir_dotdot (char *s)
{_
    uint32_t size;
    char *end;

    size = (uint32_t)strlen(s);
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
char *dospath2unix (char *in)
{_
    char *s = in;

    while (*s) {
        if (*s == '\\') {
            *s = '/';
        }

        s++;
    }

    return (in);
}
