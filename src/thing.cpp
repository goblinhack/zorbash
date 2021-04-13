//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include "my_sys.h"
#include "my_level.h"
#include "my_thing.h"
#include "my_monst.h"
#include "my_ptrcheck.h"

const Tpp Thing::tp_or_update(void)
{
    if (likely(mytp != nullptr)) {
        return (mytp);
    }
    if (unlikely(tp_id == -1)) {
        return (nullptr);
    }
    mytp = tp_id_map[tp_id - 1];
    return (mytp);
}

const Tpp Thing::tp(void) const
{
    if (likely(mytp != nullptr)) {
        return (mytp);
    }
    if (unlikely(tp_id == -1)) {
        err("no tp set for tp_id %d", tp_id);
        return (nullptr);
    }

    //
    // Means a missing call to tp_or_update
    //
    if (tp_id_map[tp_id - 1]) {
        ERR("no tp has been set yet for tp_id %d", tp_id);
    } else {
        DIE("no tp has been set for invalid tp_id %d", tp_id);
    }
    return (nullptr);
}

uint8_t Thing::z_prio (void) const
{
    return (tp()->z_prio);
}

std::size_t Thing::get_light_count (void) const
{
    if (likely(monstp != nullptr)) {
        verify(monstp);
        return (monstp->light.size());
    } else {
        return (0);
    }
}

const ThingId& Thing::get_immediate_owner_id (void) const
{_
    if (likely(monstp != nullptr)) {
        verify(monstp);
        return (monstp->owner_id);
    } else {
        return (NoThingId);
    }
}

const ThingId& Thing::set_owner_id (const ThingId &v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->owner_id = v);
}

const ThingId& Thing::get_immediate_minion_owner_id (void) const
{_
    if (likely(monstp != nullptr)) {
        verify(monstp);
        return (monstp->minion_owner_id);
    } else {
        return (NoThingId);
    }
}

const ThingId& Thing::set_minion_owner_id (const ThingId &v)
{_
    new_monst();
//con("%s", __FUNCTION__);
    return (monstp->minion_owner_id = v);
}

const ThingId& Thing::get_immediate_spawned_owner_id (void) const
{_
    if (likely(monstp != nullptr)) {
        verify(monstp);
LOG("%s get %d", __FUNCTION__, monstp->spawner_owner_id.id);
        return (monstp->spawner_owner_id);
    } else {
        return (NoThingId);
    }
}

const ThingId& Thing::set_spawned_owner_id (const ThingId &v)
{_
    new_monst();
//con("%s", __FUNCTION__);
LOG("%s set %d", __FUNCTION__, v.id);
    return (monstp->spawner_owner_id = v);
}

const fpoint &Thing::get_interpolated_mid_at (void) const
{_
    return (interpolated_mid_at);
}

void Thing::set_interpolated_mid_at (fpoint v)
{_
//con("%s", __FUNCTION__);
    interpolated_mid_at = v;
}
