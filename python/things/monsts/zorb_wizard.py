import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_speaks(me, "The zorblin wizard curses darkly in rage!")


def on_born(me, x, y):
    my.thing_carry(me, "wand_fire")


def tp_init(name, text_name):
    self = zorb_all.tp_init(name, text_name)
    my.long_text_description_extra(self, "This particular zorblin is learned in the dark zorbliny arts. They worship their dark lord who lives in his dark lair. They also prefer dark chocolate.")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.on_born_do(self, "me.on_born()")
    my.text_description(self, "A master of the dark zorbliny arts.")
    my.is_carrier_of_treasure_class_b(self, True)
    my.stat_str(self, 8)
    my.is_monst_class_c(self, True)
    my.is_biome_dungeon(self, True)
    my.distance_avoid(self, 5)
    my.health_initial_dice(self, "2d4+4")
    my.is_able_to_use_wands_or_staffs(self, True)
    my.is_intelligent(self, True)
    my.is_able_to_use_rings(self, True)

    delay = 300
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".1", delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".2", delay_ms=delay, frame=2)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".3", delay_ms=delay, frame=3)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".4", delay_ms=delay, frame=4)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".5", delay_ms=delay, frame=5)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".6", delay_ms=delay, frame=6)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.4", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="m", ascii_bg_col="", ascii_fg_col="white",
            tile=name + ".dead.5", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_wizard", text_name="zorblin wizard")


init()
