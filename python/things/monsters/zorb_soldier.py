import my
import zorb_all


def on_born(me, x, y):
    zorb_all.on_born(me, x, y)


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin soldier cries out in rage!")


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin soldier cries out in anguish!")


def tp_init(name, text_long_name):
    self = zorb_all.tp_init(name, text_long_name)
    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_A(self, 20)
    my.chance_d1000_carrier_of_weapon_class_A(self, 1000)
    my.health_initial_dice(self, "2d8+2")
    my.is_able_to_freeze(self, True)
    my.is_able_to_use_armor(self, True)
    my.is_able_to_use_weapons(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_daring(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_A(self, True)
    my.is_zorblin(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_death_of_my_leader_do(self, "me.on_death_of_my_leader()")
    my.on_you_nat_attack_attempt_do(self, "zorb_all.on_you_nat_attack_attempt()")
    my.stat_psi(self, 10)
    my.stat_str(self, 10)
    my.text_description_long2(self, "This particular zorblin is a battle hardened veteran of many wars.")
    my.text_description_short(self, "A grizzled war-weary soldier.")
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
    tp_init(name="zorb_soldier", text_long_name="zorblin soldier")


init()
