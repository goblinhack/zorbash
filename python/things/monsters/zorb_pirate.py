import my
import zorb_all


def on_born(me, x, y):
    my.thing_carry(me, "map_treasure")
    my.thing_carry(me, "gold6")
    my.thing_carry(me, "cutlass")
    zorb_all.on_born(me, x, y)


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin pirate cries out: Aaar!")


def tp_init(name, text_long_name):
    self = zorb_all.tp_init(name, text_long_name)
    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_C(self, 1000)
    my.health_initial_dice(self, "2d10")
    my.health_initial_dice(self, "2d10+4")
    my.is_able_to_freeze(self, True)
    my.is_able_to_use_weapons(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_ice(self, True)
    my.is_daring(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_zorblin(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_you_nat_attack_attempt_do(self, "zorb_all.on_you_nat_attack_attempt()")
    my.stat_psi(self, 11)
    my.stat_str(self, 14)
    my.text_description_long2(self, "This particular zorblin was once a ruthless adventurer who plundered the seas in their mighty pirate ship, but due to a series of unfortunate events finds themselves wandering this dungeon looking for the odd piece of eight.")
    my.text_description_short(self, "A one-eyed pirate zorblin.")
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
    tp_init(name="zorb_pirate", text_long_name="zorblin pirate")


init()
