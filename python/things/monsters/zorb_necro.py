import my
import zorb_all


def on_born(me, x, y):
    my.thing_msg(me, "Hello mortal!")
    my.thing_carry(me, "staff_energy")
    zorb_all.on_born(me, x, y)


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(leader):
        my.thing_msg(me, "The zorblin necromancer begins muttering some unknown words!")


def on_tick(owner, me, x, y):
    if my.py_pcg_random_range_inclusive(1, 100) < 90:
        return False

    risen = 0
    if my.thing_stat_con(me) > 1:
        followers = my.thing_all_followers_get(me)
        if followers is None:
            return False

        for follower in followers:
            if my.thing_is_dead_or_dying(follower):
                if my.thing_resurrect(follower, "arise"):
                    my.thing_stat_con_decr(me, 1)
                    my.thing_msg(me, "Arise my minion!")
                    my.thing_msg(follower, "Groan!")
                    if my.thing_stat_con(me) <= 1:
                        return True
                    risen += 1

    if risen > 0:
        return True
    return False


def on_death(me, x, y):
    followers = my.thing_all_followers_get(me)
    if followers is None:
        return False

    for follower in followers:
        if my.thing_is_resurrected_or_resurrecting(follower):
            my.thing_speaks(follower, "Free at last!")
            my.thing_perma_death(follower, "Leader died!")


def tp_init(name, text_long_name):
    self = zorb_all.tp_init(name, text_long_name)

    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_C(self, 1000)
    my.chance_d1000_shooting(self, 500)
    my.distance_avoid(self, 5)
    my.environ_hates_fire(self, 100)
    my.environ_hates_water(self, 100)
    my.health_initial_dice(self, "2d3+4")
    my.is_able_to_use_rings(self, True)
    my.is_able_to_use_staffs(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_cowardly(self, True)
    my.is_intelligent(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_zorblin(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_do(self, "me.on_death()")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_tick_do(self, "me.on_tick()")
    my.on_you_nat_attack_attempt_do(self, "zorb_all.on_you_nat_attack_attempt()")
    my.stat_dex(self, 6)
    my.stat_int(self, 14)
    my.stat_luck(self, 6)
    my.stat_psi(self, 14)
    my.stat_str(self, 6)
    my.text_description_long2(self, "This particular zorblin is learned in the dark arts. Withered of body, but sharp of mind, beware the abilities of this zorblin.")
    my.text_description_short(self, "A master of the darkest arts.")
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".6", delay_ms=delay, frame=6)
    my.tile(self,
            ascii_fg_char="Z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.4", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead.5", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_necro", text_long_name="zorblomancer")


init()
