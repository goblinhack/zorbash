/*
 * Copyright goblinhack@gmail.com
 * See the README file for license info.
 */

#include <libgen.h>
#include <string>
#include <sstream>

#include "my_main.h"
#include "my_sdl.h"
#include "my_thing_template.h"

std::wstring string_to_wstring(const std::string& s);
std::string wstring_to_string(const std::wstring& s);

std::wstring string_to_wstring (const std::string& s)
{
    std::wstring temp(s.length(), L' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp; 
}

std::string wstring_to_string (const std::wstring& s)
{
    std::string temp(s.length(), ' ');
    std::copy(s.begin(), s.end(), temp.begin());
    return temp; 
}

// #define HEX_DUMP_WIDTH (MAXSTR / 2)
#define HEX_DUMP_WIDTH (16)

/*
 * Replace chars in replace_set with replace_with.
 */
void
strrepc (char *s, const char *replace_set, char replace_with)
{_
    char *c;

    for (c = s; *c; c++) {
        if (strchr(replace_set, *c)) {
            *c = replace_with;
        }
    }
}

/*
 * return a part of a string.
 *
 * substr("foo.zip", -4, 4) -> "zip"
 */
char *substr (const char *in, int32_t pos, int32_t len)
{_
    int32_t slen;
    char *out;

    if (!in) {
        return (0);
    }

    slen = (uint32_t)strlen(in);

    /*
     * Negative positions from the end.
     */
    if (pos < 0) {
        pos = slen + pos;
    }

    if (pos < 0) {
        pos = 0;
    }

    if (len < 0) {
        len = 0;
    }

    if (pos > slen) {
        pos = slen;
    }

    if (len > slen - pos) {
        len = slen - pos;
    }

    out = (__typeof__(out)) mymalloc(len + sizeof((char)'\0'), "substr");
    if (!out) {
        return (0);
    }

    memcpy(out, &(in[pos]), len);
    out[len] = '\0';

    return (out);
}

/*
 * Replace part of a string with another.
 *
 * strsub("foo.zip", ".zip", ""); -> "foo"
 */
char *strsub (const char *in, const char *old, const char *replace_with)
{_
    char *buf;
    const char *at;
    int32_t newlen;
    int32_t oldlen;
    int32_t len;

    if (!in || !old || !replace_with) {
        return (0);
    }

    at = strstr(in, old);
    if (!at) {
        buf = dupstr(in, __FUNCTION__);
        return (buf);
    }

    oldlen = (uint32_t)strlen(old);
    newlen = (uint32_t)strlen(replace_with);

    len = (uint32_t)strlen(in) - oldlen + newlen;
    buf = (__typeof__(buf)) myzalloc(len + sizeof((char)'\0'), "strsub 2");
    if (!buf) {
        return (0);
    }

    *buf = '\0';
    strlcpy_(buf, in, at - in + 1);
    strcat(buf, replace_with);
    strcat(buf, at + oldlen);

    return (buf);
}

/*
 * Add onto the end of a string.
 *
 * strsub("foo", ".zip"); -> "foo.zip"
 */
char *strappend (const char *in, const char *append)
{_
    char *buf;
    int32_t newlen;
    int32_t len;

    if (!in || !append) {
        return (0);
    }

    newlen = (uint32_t)strlen(append);
    len = (uint32_t)strlen(in) + newlen;
    buf = (__typeof__(buf)) myzalloc(len + sizeof((char)'\0'), "strappend");
    if (!buf) {
        return (0);
    }

    strcpy(buf, in);
    strcat(buf, append);

    return (buf);
}

/*
 * Add onto the start of a string.
 *
 * strsub("foo", "bar"); -> "barfoo"
 */
char *strprepend (const char *in, const char *prepend)
{_
    char *buf;
    int32_t newlen;
    int32_t len;

    if (!in || !prepend) {
        return (0);
    }

    newlen = (uint32_t)strlen(prepend);
    len = (uint32_t)strlen(in) + newlen;
    buf = (__typeof__(buf)) myzalloc(len + sizeof((char)'\0'), "strprepend");
    if (!buf) {
        return (0);
    }

    strcpy(buf, prepend);
    strcat(buf, in);

    return (buf);
}

/*
 * Return the common matching length of two strings.
 */
uint32_t
strcommon (const char *a, const char *b)
{_
    const char *o;

    o = a;

    while ((*a == *b) && *a) { a++; b++; }

    return (uint32_t)(a - o);
}

/*
 * Removes trailing whitespace.
 */
void strchop (char *s)
{_
    uint32_t size;
    char *end;

    size = (uint32_t)strlen(s);
    if (!size) {
        return;
    }

    end = s + size - 1;
    while ((end >= s) && (*end == ' ')) {
        end--;
    }

    *(end + 1) = '\0';
}

/*
 * Removes trailing characters.
 */
void strchopc (char *s, char c)
{_
    uint32_t size;
    char *end;

    size = (uint32_t)strlen(s);
    if (!size) {
        return;
    }

    end = s + size - 1;
    while ((end >= s) && (*end == c)) {
        end--;
    }

    *(end + 1) = '\0';
}

int32_t strisregexp (const char *in)
{_
    const char *a = in;
    char c;

    while ((c = *a++)) {
        switch (c) {
        case '[': return (1);
        case ']': return (1);
        case '{': return (1);
        case '}': return (1);
        case '+': return (1);
        case '$': return (1);
        case '^': return (1);
        case '-': return (1);
        case '*': return (1);
        }
    }

    return (false);
}

size_t strlcpy_ (char *dst, const char *src, size_t maxlen)
{_
    size_t srclen = strlen(src);
    if ( maxlen > 0 ) {
        uint32_t len = std::min(srclen, maxlen-1);
        memcpy(dst, src, len);
        dst[len] = '\0';
    }
    return (srclen);
}

size_t strlcat_ (char *dst, const char *src, size_t maxlen)
{_
    uint32_t dstlen = strlen(dst);
    uint32_t srclen = strlen(src);
    if ( dstlen < maxlen ) {
        strlcpy_(dst+dstlen, src, maxlen-dstlen);
    }
    return (dstlen+srclen);
}

/*
 * Shrink a string by the space needed for its escape characters.
 */
void strnoescape (char *uncompressed)
{_
    char * t = uncompressed;
    char * s = uncompressed;
    char c;

    while ((c = *s++)) {
        if (c != '\\') {
            *t++ = c;
            continue;
        }

        switch (*s++) {
            case 'n':
                *t++ = '\n';
                break;
            case 't':
                *t++ = '\t';
                break;
            case '%':
                *t++ = '%';
                break;
            case '#':
                *t++ = '@';
                break;
            case '\"':
                *t++ = '\"';
                break;
            case '\'':
                *t++ = '\'';
                break;
            case '\\':
                *t++ = '\\';
                break;
            default: {
                char *o = s - 1;
                char orig;

                while (isdigit(*s)) { s++; }

                orig = *s;
                *s = '\0';
                *t++ = atoi(o);
                *s = orig;
                break;
            }
        }
    }
    *t = '\0';
}

static const char *dynvprintf_ (const char *fmt, va_list args)
{_
    static char buf[MAXSTR];

    buf[0] = '\0';
    vsnprintf(buf, sizeof(buf), fmt, args);

    return (buf);
}

/*
 * dynamically allocate a printf formatted string. e.g.
 * dynprintf("%sbar", "foo"); => "foobar"
 */
char *dynprintf (const char *fmt, ...)
{_
    const char *ret;
    va_list args;

    va_start(args, fmt);
    ret = dynvprintf_(fmt, args);
    va_end(args);

    return (dupstr(ret, __FUNCTION__));
}

char *dynvprintf (const char *fmt, va_list args)
{_
    static char buf[MAXSTR];

    buf[0] = '\0';
    vsnprintf(buf, sizeof(buf), fmt, args);

    return (dupstr(buf, __FUNCTION__));
}

/*
 * mybasename
 *
 * A safe wrapper for basename to avoid modifications to the input string.
 */
std::string mybasename (const char *in, const char *who)
{_
    char *tmp = dupstr(in, who);
    std::string tmp2(basename(tmp));
    myfree(tmp);

    return (tmp2);
}

/*
 * hex_dump
 *
 * Returns false if we finished with an empty block.
 */
uint8_t hex_dump (void *addr, uint64_t offset, uint64_t len)
{_
    uint8_t skipping_blanks = false;
    uint8_t empty[HEX_DUMP_WIDTH] = {0};
    uint8_t buf[HEX_DUMP_WIDTH + 1];
    uint8_t *pc = (__typeof__(pc)) addr;
    uint64_t i;
    uint32_t x;

    if (!len) {
        return (false);
    }

    for (i = 0, x = 0; i < len; i++, x++) {
        if ((i % HEX_DUMP_WIDTH) == 0) {
            if (!skipping_blanks) {
                if (i != 0) {
                    printf(" |%*s|\n", HEX_DUMP_WIDTH, buf);
                }
            }

            /*
             * Skip blank blocks.
             */
            if (!memcmp(pc + i, empty, sizeof(empty))) {
                i += HEX_DUMP_WIDTH - 1;
                skipping_blanks = true;
                buf[0] = '\0';
                continue;
            }

            printf("  %08X ", (uint32_t)(i + offset));

            x = 0;
        }

        if (x && (((i % (HEX_DUMP_WIDTH/2))) == 0)) {
            printf(" ");
        }

        skipping_blanks = false;

        printf(" %02X", pc[i]);

        if ((pc[i] < ' ') || (pc[i] > '~')) {
            buf[i % HEX_DUMP_WIDTH] = '.';
        } else {
            buf[i % HEX_DUMP_WIDTH] = pc[i];
        }

        buf[(i % HEX_DUMP_WIDTH) + 1] = '\0';
    }

    if (!buf[0]) {
        if (skipping_blanks) {
            printf("  *\n");
        }

        return (false);
    }

    while ((i % HEX_DUMP_WIDTH) != 0) {
        printf ("   ");

        if (i && (((i % (HEX_DUMP_WIDTH/2))) == 0)) {
            printf (" ");
        }

        i++;
    }

    printf(" |%*s|\n", -HEX_DUMP_WIDTH, buf);

    return (true);
}

/*
 * hex_dump_log
 *
 * As above but logs to the buffer
 */
uint8_t hex_dump_log (void *addr, uint64_t offset, uint64_t len)
{_
    uint8_t skipping_blanks = false;
    uint8_t empty[HEX_DUMP_WIDTH] = {0};
    uint8_t buf[HEX_DUMP_WIDTH + 1];
    uint8_t *pc = (__typeof__(pc)) addr;
    uint64_t i;
    uint32_t x;

    if (!len) {
        return (false);
    }

    for (i = 0, x = 0; i < len; i++, x++) {
        if ((i % HEX_DUMP_WIDTH) == 0) {
            if (!skipping_blanks) {
                if (i != 0) {
                    LOGS(" |%*s|\n", HEX_DUMP_WIDTH, buf);
                }
            }

            /*
             * Skip blank blocks.
             */
            if (!memcmp(pc + i, empty, sizeof(empty))) {
                i += HEX_DUMP_WIDTH - 1;
                skipping_blanks = true;
                buf[0] = '\0';
                continue;
            }

            LOGS("  %08X ", (uint32_t)(i + offset));

            x = 0;
        }

#if 0
        if (x && (((i % (HEX_DUMP_WIDTH/2))) == 0)) {
            LOGS(" ");
        }
#endif

        skipping_blanks = false;

        LOGS(" %02X", pc[i]);

        if ((pc[i] < ' ') || (pc[i] > '~')) {
            buf[i % HEX_DUMP_WIDTH] = '.';
        } else {
            buf[i % HEX_DUMP_WIDTH] = pc[i];
        }

        buf[(i % HEX_DUMP_WIDTH) + 1] = '\0';
    }

    if (!buf[0]) {
        if (skipping_blanks) {
            LOGS("  *\n");
        }

        return (false);
    }

    while ((i % HEX_DUMP_WIDTH) != 0) {
        LOGS ("   ");

        if (i && (((i % (HEX_DUMP_WIDTH/2))) == 0)) {
            LOGS (" ");
        }

        i++;
    }

    LOGS(" |%*s|\n", -HEX_DUMP_WIDTH, buf);

    return (true);
}

/*-
 * Copyright (c) 1990, 1993
 *      The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Find the first occurrence of find in s, ignore case.
 */
char *
strcasestr_ (const char *s, const char*find)
{_
        char c, sc;
        size_t len;

        if ((c = *find++) != 0) {
                c = tolower((unsigned char)c);
                len = strlen(find);
                do {
                        do {
                                if ((sc = *s++) == 0)
                                        return (NULL);
                        } while ((char)tolower((unsigned char)sc) != c);
                } while (strncasecmp(s, find, len) != 0);
                s--;
        }
        return ((char *)s);
}

/*
 * From AMD apparently
 *
 * http://stackoverflow.com/questions/271971/how-can-i-improve-replace-sprintf-which-ive-measured-to-be-a-performance-hotsp
 */
void itoa05 (char *string, unsigned int value)
{_
   *string++ = '0' + ((value = value * 26844 + 12) >> 28);
   *string++ = '0' + ((value = ((value & 0x0FFFFFFF)) * 10) >> 28);
   *string++ = '0' + ((value = ((value & 0x0FFFFFFF)) * 10) >> 28);
   *string++ = '0' + ((value = ((value & 0x0FFFFFFF)) * 10) >> 28);
   *string++ = '0' + ((value = ((value & 0x0FFFFFFF)) * 10) >> 28);
   *string++ = 0;
}

/*
 * Split a string "like\nthis" into "like" and "this". e.g.:
 *
 * split("To support multiple versions, the program named perl now just selects the real version of Perl to run, and the program named a2p now just selects the real version of the awk-to-perl translator to run, depending on various settings.  The current supported versions are 5.8.8 (provided for back-ward-compatibility with the Perl 5.8 family) and 5.10.0, with the default being 5.10.0. ", 80);
 *
 * yields:
 *
"To support multiple versions, the program named perl now just selects the real"
"version of Perl to run, and the program named a2p now just selects the real"
"version of the awk-to-perl translator to run, depending on various settings."
"The current supported versions are 5.8.8 (provided for back-ward-compatibility"
"with the Perl 5.8 family) and 5.10.0, with the default being 5.10.0."
 */
shared_vector_string split (const char *text, uint32_t max_line_len)
{_
    uint8_t found_format_string;
    const char *line_start;
    const char *line_end;
    uint32_t line_len;
    char c;
    const char *const text_start = text;

    if (!text) {
        return (0);
    }

    auto result = std::make_shared< std::vector< std::string > > ();

    for (;/*ever*/;) {
        line_len = 0;
        line_start = text;

        /*
         * The first newline is used as a split char. Two newlines means one
         * of them is forced.
         */
        if (text != text_start) {
            if (*text == '\n') {
                text++;
            }
        }

        while (*text == ' ') {
            text++;
        }

        /*
         * Read in as much of the line we can up to the line length.
         */
        found_format_string = false;

        while (line_len < max_line_len) {
            c = *text;
            line_len++;

            if (c == '%') {
                if (!found_format_string) {
                    found_format_string = true;
                } else if (found_format_string) {
                    text++;
                    if (!strncmp(text, "fg=", 3)) {
                        text += 3;
                        line_len -= 2; /* for the %% */
                        (void) string2color(&text);
                        found_format_string = false;
                        continue;
                    } else if (!strncmp(text, "tp=", 3)) {
                        text += 3;
                        line_len -= 2; /* for the %% */
                        (void) string2tp(&text);
                        found_format_string = false;
                        continue;
                    } else if (!strncmp(text, "tex=", 4)) {
                        text += 4;
                        line_len -= 2; /* for the %% */
                        (void) string2tex(&text);
                        found_format_string = false;
                        continue;
                    } else if (!strncmp(text, "tile=", 5)) {
                        text += 5;
                        line_len -= 2; /* for the %% */
                        (void) string2tile(&text);
                        found_format_string = false;
                        continue;
                    } else {
                        text--;
                    }

                    found_format_string = false;
                }
            } else if (c == '\n') {
                break;
            } else if (c == '\0') {
                break;
            }

            text++;
        }

        line_end = text;

        /*
         * Step back looking for a word break.
         */
        if (line_len >= max_line_len) {
            while ((line_end > line_start) &&
                    ((*line_end != ' ') &&
                    (*line_end != '\0') &&
                    (*line_end != '\n'))) {
                line_end--;
            }
        }

        while (line_end > line_start) {
            if (*(line_end - 1) == ' ') {
                line_end--;
                continue;
            }
            break;
        }

        if (line_end == line_start) {
            line_end = text;
        }

        /*
         * Skip leading junk.
         */
        while (line_start < line_end) {
            if ((*line_start == '\n')) {
                line_start++;
                continue;
            }

            if (*line_start == ' ') {
                line_start++;
                continue;
            }
            break;
        }

        line_len = (uint32_t)(line_end - line_start);
        char tmp[line_len + 1];
        strlcpy_(tmp, line_start, line_len + 1);

        result->push_back(tmp);

        text = line_end;
        if (!*text) {
            break;
        }

        if (text == text_start) {
            if (line_len == 0) {
                text++;
            }
        }
    }

    return (result);
}

shared_vector_string split (const std::string &text, uint32_t max_line_len)
{_
    uint8_t found_format_string;
    uint32_t line_len;
    char c;
    auto text_start = text.begin();
    auto text_iter = text_start;
    auto line_start = text_start;
    auto line_end = text_start;

    if (!text.length()) {
        return (0);
    }

    auto result = std::make_shared< std::vector< std::string > > ();

    for (;/*ever*/;) {
        line_len = 0;
        line_start = text_iter;

        /*
         * The first newline is used as a split char. Two newlines means one
         * of them is forced.
         */
        if (text_iter != text_start) {
            if (*text_iter == '\n') {
                text_iter++;
            }
        }

        while (*text_iter == ' ') {
            text_iter++;
        }

        /*
         * Read in as much of the line we can up to the line length.
         */
        found_format_string = false;

        while (line_len < max_line_len) {
            c = *text_iter;
            line_len++;

            if (c == '%') {
                if (!found_format_string) {
                    found_format_string = true;
                } else if (found_format_string) {
                    text_iter++;
                    if (std::string(text_iter, text_iter + 3) == "fg=") {
                        text_iter += 3;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::string(text_iter, text.end());

                        int len = 0;
                        (void) string2color(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else if (std::string(text_iter, text_iter + 3) == "tp=") {
                        text_iter += 3;
                        line_len -= 2; /* for the %% */

                        auto tmp = std::string(text_iter, text.end());

                        int len = 0;
                        (void) string2tp(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else if (std::string(text_iter, text_iter + 4) == "tex=") {
                        text_iter += 4;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::string(text_iter, text.end());

                        int len = 0;
                        (void) string2tex(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else if (std::string(text_iter, text_iter + 5) == "tile=") {
                        text_iter += 5;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::string(text_iter, text.end());

                        int len = 0;
                        (void) string2tile(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else {
                        text_iter--;
                    }

                    found_format_string = false;
                }
            } else if (c == '\n') {
                break;
            } else if (c == '\0') {
                break;
            }

            text_iter++;
        }

        line_end = text_iter;

        /*
         * Step back looking for a word break.
         */
        if (line_len >= max_line_len) {
            while ((line_end > line_start) &&
                    ((*line_end != ' ') &&
                    (*line_end != '\0') &&
                    (*line_end != '\n'))) {
                line_end--;
            }
        }

        while (line_end > line_start) {
            if (*(line_end - 1) == ' ') {
                line_end--;
                continue;
            }
            break;
        }

        if (line_end == line_start) {
            line_end = text_iter;
        }

        /*
         * Skip leading junk.
         */
        while (line_start < line_end) {
            if (*line_start == '\n') {
                line_start++;
                continue;
            }

            if (*line_start == ' ') {
                line_start++;
                continue;
            }
            break;
        }

        line_len = (uint32_t)(line_end - line_start);
        auto tmp = std::string(line_start, line_start + line_len);

        result->push_back(tmp);

        text_iter = line_end;
        if (!*text_iter) {
            break;
        }

        if (text_iter == text_start) {
            if (line_len == 0) {
                text_iter++;
            }
        }
    }

    return (result);
}

shared_vector_wstring split (const std::wstring &text, uint32_t max_line_len)
{_
    uint8_t found_format_string;
    uint32_t line_len;
    char c;
    auto text_start = text.begin();
    auto text_iter = text_start;
    auto line_start = text_start;
    auto line_end = text_start;

    if (!text.length()) {
        return (0);
    }

    auto result = std::make_shared< std::vector< std::wstring > > ();

    for (;/*ever*/;) {
        line_len = 0;
        line_start = text_iter;

        /*
         * The first newline is used as a split char. Two newlines means one
         * of them is forced.
         */
        if (text_iter != text_start) {
            if (*text_iter == '\n') {
                text_iter++;
            }
        }

        while (*text_iter == ' ') {
            text_iter++;
        }

        /*
         * Read in as much of the line we can up to the line length.
         */
        found_format_string = false;

        while (line_len < max_line_len) {
            c = *text_iter;
            line_len++;

            if (c == '%') {
                if (!found_format_string) {
                    found_format_string = true;
                } else if (found_format_string) {
                    text_iter++;
                    if (std::wstring(text_iter, text_iter + 3) == L"fg=") {
                        text_iter += 3;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::wstring(text_iter, text.end());

                        int len = 0;
                        (void) string2color(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else if (std::wstring(text_iter, text_iter + 3) == L"tp=") {
                        text_iter += 3;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::wstring(text_iter, text.end());

                        int len = 0;
                        (void) string2tp(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else if (std::wstring(text_iter, text_iter + 4) == L"tex=") {
                        text_iter += 4;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::wstring(text_iter, text.end());

                        int len = 0;
                        (void) string2tex(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else if (std::wstring(text_iter, text_iter + 5) == L"tile=") {
                        text_iter += 5;
                        line_len -= 2; /* for the %% */
                        auto tmp = std::wstring(text_iter, text.end());

                        int len = 0;
                        (void) string2tile(tmp, &len);
                        text_iter += len + 1;

                        found_format_string = false;
                        continue;
                    } else {
                        text_iter--;
                    }

                    found_format_string = false;
                }
            } else if (c == '\n') {
                break;
            } else if (c == '\0') {
                break;
            }

            text_iter++;
        }

        line_end = text_iter;

        /*
         * Step back looking for a word break.
         */
        if (line_len >= max_line_len) {
            while ((line_end > line_start) &&
                    ((*line_end != ' ') &&
                    (*line_end != '\0') &&
                    (*line_end != '\n'))) {
                line_end--;
            }
        }

        while (line_end > line_start) {
            if (*(line_end - 1) == ' ') {
                line_end--;
                continue;
            }
            break;
        }

        if (line_end == line_start) {
            line_end = text_iter;
        }

        /*
         * Skip leading junk.
         */
        while (line_start < line_end) {
            if (*line_start == '\n') {
                line_start++;
                continue;
            }

            if (*line_start == ' ') {
                line_start++;
                continue;
            }
            break;
        }

        line_len = (uint32_t)(line_end - line_start);
        auto tmp = std::wstring(line_start, line_start + line_len);

        result->push_back(tmp);

        text_iter = line_end;
        if (!*text_iter) {
            break;
        }

        if (text_iter == text_start) {
            if (line_len == 0) {
                text_iter++;
            }
        }
    }

    return (result);
}

Tpp string2tp (const char **s)
{_
    static char tmp[MAXSTR];
    static const char *eo_tmp = tmp + MAXSTR;
    const char *c = *s;
    char *t = tmp;

    while (t < eo_tmp) {
        if ((*c == '\0') || (*c == '$')) {
            break;
        }

        *t++ = *c++;
    }

    if (c == eo_tmp) {
        DIE("tp name %s is too long", tmp);
        return (0);
    }

    *t++ = '\0';
    *s += (t - tmp);

    Tpp tp = tp_find(tmp);
    if (!tp) {
        DIE("tp name [%s] not found", tmp);
    }

    return (tp);
}

Tpp string2tp (std::string &s, int *len)
{_
    auto iter = s.begin();
    std::string out;

    while (iter != s.end()) {
        auto c = *iter;

        if ((c == '\0') || (c == '$')) {
            break;
        }

        out += c;
        iter++;
    }

    if (len) {
        *len = iter - s.begin();
    }

    if (iter == s.end()) {
        DIE("tp name %s is too long", out.c_str());
        return (0);
    }

    Tpp tp = tp_find(out);
    if (!tp) {
        DIE("tp name [%s] not found", out.c_str());
    }

    return (tp);
}

Tpp string2tp (std::wstring &s, int *len)
{_
    auto v = wstring_to_string(s);
    return (string2tp(v, len));
}

/*
 * size, the returned size of the buffer. Can be given initially to force
 * alloc of a given buffer size. Else a default size is used.
 *
 * used, optional pointer to avoid the need to do strlen when appending to the
 * string.
 *
 * str, returned pointer for the new string
 *
 * returns 0 on success
 */
int32_t snprintf_realloc (char **str,
                          int32_t *size, int32_t *used,
                          const char *fmt, ...)
{_
    int32_t freespace;
    int32_t needspace;
    int32_t usedspace;
    va_list ap;
    char *tmp;

    if (!str) {
        return (-1);
    }

    if (!size) {
        return (-1);
    }

    if (!*str) {
        if (!*size) {
            *size = 128;
        }

        if (used) {
            *used = 0;
        }

        *str = (char*) mymalloc(*size, "sprintf alloc");
        if (!*str) {
            *size = 0;
            return (-1);
        }

        *str[0] = '\0';
    }

    if (!used || !*used) {
        usedspace = (uint32_t)strlen(*str);
    } else {
        usedspace = *used;
    }

    char add[MAXSTR];
    va_start(ap, fmt);
    vsnprintf(add, sizeof(add) - 1, fmt, ap);
    va_end(ap);
    add[MAXSTR-1] = '\0';

    needspace = strlen(add);

    for (;/*ever*/;) {
        freespace = *size - usedspace;

        if (needspace < freespace) {
            if (used) {
                *used += needspace;
            }
            strcat(*str, add);

            return (0);
        }

        (*size) *= 2;

        tmp = (char*) myrealloc(*str, *size, "sprintf realloc");
        if (!tmp) {
            free (*str);
            *str = 0;
            *size = 0;
            return (-1);
        }

        *str = tmp;
    }
}

#include <string>

std::string string_sprintf (const char *format, ...)
{_
    va_list args;
    char *buf;

    va_start(args, format);

    if (vasprintf(&buf, format, args) == -1) {
        throw std::bad_alloc();
    }

    std::string ret = buf;
    free(buf);

    va_end(args);

    return (ret);
}

std::vector<std::string> split_tokens(const std::string &s, 
                                      const char delimiter)
{
   std::string token;
   std::istringstream s_stream(s);
   std::vector<std::string> tokens;
   while (std::getline(s_stream, token, delimiter)) {
       tokens.push_back(token);
   }
   return tokens;
}
