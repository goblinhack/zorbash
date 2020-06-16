//
// Copyright goblinhack@gmail.com
// See the README file for license info.
//

#pragma once
#ifndef _MY_THING_ID_H_
#define _MY_THING_ID_H_

using ThingId = struct ThingId_ {
public:
    uint32_t id {};
    ThingId_ (uint32_t id) : id(id) {}
    ThingId_ () {}

    bool operator< (const ThingId_& rhs) const {
        return (id < rhs.id);
    }
    bool operator! () const {
        return id == 0;
    }
    bool operator== (const ThingId_& rhs) const {
        return (id == rhs.id);
    }
    bool operator!= (const ThingId_& rhs) const {
        return (id != rhs.id);
    }
    bool ok (void) const {
        return id != 0;
    }
};

#endif
