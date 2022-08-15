import my
import zorb_all


def on_death_of_a_follower(me, leader, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The zorblin priest prays for the departed!")


def on_born(me, x, y):
    my.thing_carry(me, "wand_fire")


def tp_init(name, text_long_name):
    self = zorb_all.tp_init(name, text_long_name)
    my.text_long_description2(self, "This particular zorblin is well trained in the martial arts and prefers to fight bare fisted.")
    my.on_death_of_a_follower_do(self, "me.on_death_of_a_follower()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.on_born_do(self, "me.on_born()")
    my.text_short_description(self, "A master in physical punishment.")
    my.stat_str(self, 12)
    my.distance_avoid(self, 5)
    my.text_hits(self, "hits")
    my.gfx_anim_use(self, "attack_punch")
    my.damage_nat_att_type(self, "punch")
    my.is_monst_class_b(self, True)
    my.is_biome_dungeon(self, True)
    my.damage_nat_att_dice(self, "2d6+2")
    my.health_initial_dice(self, "2d10+4")
    my.is_intelligent(self, True)

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
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".1", is_sleeping=True, delay_ms=delay, frame=1)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".2", is_sleeping=True, delay_ms=delay, frame=2)

    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".dead.1", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".dead.2", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".dead.3", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".dead.4", is_dead=True, delay_ms=delay)
    my.tile(self,
            ascii_fg_char="z", ascii_bg_col_name="", ascii_fg_col_name="green",
            tile=name + ".dead.5", is_dead=True, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="zorb_priest", text_long_name="zorblin priest")


init()
