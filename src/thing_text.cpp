//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_main.h"
#include "my_level.h"
#include "my_depth.h"
#include "my_color.h"
#include "my_dmap.h"
#include "my_sprintf.h"
#include "my_thing.h"

std::string Thing::text_a_or_an (void) const
{_
    auto tpp = tp();
    verify(this);
    verify(tpp);
    if (unlikely(!tpp)) {
        return ("<no name>");
    }

    std::string out = "";

    if (is_undead()) {
        out += "an undead ";
    } else {
        if (is_dead) {
            out += "a dead ";
        }
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

    if (is_undead()) {
        out += "undead ";
    } else {
        if (is_dead) {
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
