//
// Copyright goblinhack@gmail.com
// See the README.md file for license info.
//

#include <algorithm>
#include "my_sys.h"
#include "my_level.h"
#include "my_dmap.h"
#include "my_math.h"
#include "my_thing.h"
#include "my_thing_template.h"
#include "my_sprintf.h"
#include "my_random.h"
#include "my_monst.h"
#include "my_array_bounds_check.h"
#include "my_ptrcheck.h"

///////////////////////////////////////////////////////////////////////////
// melee
///////////////////////////////////////////////////////////////////////////
const Dice& Thing::get_damage_melee_dice (void) const {_ 
    return (tp()->get_damage_melee_dice()); 
}

const std::string& Thing::get_damage_melee_dice_str (void) const {_ 
    return (tp()->get_damage_melee_dice_str()); 
}

int Thing::get_damage_melee (void) const {_ 
    return (tp()->get_damage_melee_dice().roll()); 
}

///////////////////////////////////////////////////////////////////////////
// bite
///////////////////////////////////////////////////////////////////////////
const Dice& Thing::get_damage_bite_dice (void) const {_ 
    return (tp()->get_damage_bite_dice()); 
}

const std::string& Thing::get_damage_bite_dice_str (void) const {_ 
    return (tp()->get_damage_bite_dice_str()); 
}

int Thing::get_damage_bite (void) const {_ 
    return (tp()->get_damage_bite_dice().roll()); 
}

///////////////////////////////////////////////////////////////////////////
// misc
///////////////////////////////////////////////////////////////////////////
int Thing::get_damage_max (void)
{_
    auto max_damage = get_damage_bite_dice().max_roll();
    max_damage = std::max(max_damage, get_damage_melee_dice().max_roll());
    return max_damage;
}

int Thing::get_damage_min (void)
{_
    auto min_damage = get_damage_bite_dice().min_roll();
    min_damage = std::min(min_damage, get_damage_melee_dice().min_roll());
    return min_damage;
}
