import my


def on_targeted(me, x, y, bonus):
    owner = my.thing_top_owner_id_get(me)
    if not owner:
        return

    existing_mental_load = 0
    for f in my.thing_get_followers(me):
        existing_mental_load += my.thing_stat_int_bonus(f)

    bonus -= existing_mental_load
    bonus += my.thing_stat_psi_bonus(me)

    for it in my.level_get_all(me, x, y):
        if not my.thing_is_monst(it):
            continue

        if my.thing_is_dead(it):
            my.thing_msg(me, f"The {my.thing_name_get(it)}'s mind is beyond your powers.")
            continue

        if my.thing_is_ethereal(it):
            my.thing_msg(me, f"The {my.thing_name_get(it)}'s mind evades your grasp.")
            continue

        roll = my.py_pcg_random_range_inclusive(1, 20)
        # my.topcon("roll {} + {} vs {}".format(roll, bonus, my.thing_stat_int(it) + my.thing_stat_psi_bonus(it)))
        if roll + bonus > my.thing_stat_int(it) + my.thing_stat_psi_bonus(it):
            if my.thing_set_leader(it, owner):
                my.thing_msg(me, f"The {my.thing_name_get(it)}'s mind is beholden to you.")
            else:
                my.thing_msg(me, f"The {my.thing_name_get(it)} cannot be possessed.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(it)} fends off your mental attack.")
