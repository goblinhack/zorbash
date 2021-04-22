//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_ptrcheck.h"

std::string Thing::text_a_or_an (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "";

    if (is_dead) {
        out += "a dead ";
    }

    if (out == "") {
        auto prefix = tpp->text_a_or_an();
        if (prefix == "") {
            out = tpp->text_name();
        } else {
            out = prefix + " " + tpp->text_name();
        }
    } else {
        out += tpp->text_name();
    }

    return (out);
}

std::string Thing::text_the (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "the ";

    if (is_dead) {
        if (is_undead()) {
            out += "extra dead ";
        } else {
            out += "dead ";
        }
    }

    out += tpp->text_name();

    return (out);
}

std::string Thing::text_The (void) const
{_
    auto out = text_the();
    out[0] = toupper(out[0]);
    return (out);
}

std::string Thing::short_text_a_or_an (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "";

    if (is_dead) {
        out += "a dead ";
    }

    if (out == "") {
        auto prefix = tpp->text_a_or_an();
        if (prefix == "") {
            out = tpp->short_text_name();
        } else {
            out = prefix + " " + tpp->short_text_name();
        }
    } else {
        out += tpp->short_text_name();
    }

    return (out);
}

std::string Thing::short_text_the (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "the ";

    if (is_dead) {
        if (is_undead()) {
            out += "extra dead ";
        } else {
            out += "dead ";
        }
    }

    out += tpp->short_text_name();

    return (out);
}

std::string Thing::short_text_The (void) const
{_
    auto out = short_text_the();
    out[0] = toupper(out[0]);
    return (out);
}

//
// foo bar -> Foo Bar
//
std::string Thing::short_text_capitalized (void) const
{_
    std::string out = tp()->short_text_name();
    char *b = (char*)out.c_str();
    char *e = b + out.size();
    char *c = b;
    bool word_start = true;
    while (c < e) {
        if (word_start) {
            if (islower(*c)) {
                *c = toupper(*c);
            }
            word_start = false;
        } else if (*c == ' ') {
            word_start = true;
        }
        
        c++;
    }
    return out;
}
