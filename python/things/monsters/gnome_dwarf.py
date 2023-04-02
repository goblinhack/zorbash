import my
import gnome_all


def on_born(me, x, y):
    gnome_all.on_born(me, x, y)
    my.thing_carry(me, "gold4")


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The gnorf cries out in tiny impotent rage!")


def tp_init(name, text_long_name):
    self = gnome_all.tp_init(name, text_long_name)
    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_B(self, 20)
    my.dmg_nat_att_dice(self, "1d4+1")
    my.dmg_nat_att_type(self, "chop")
    my.health_initial_dice(self, "1d6+4")
    my.is_able_to_run_away_after_stealing(self, True)
    my.is_able_to_teleport_escape(self, True)
    my.is_biome_dungeon(self, True)
    my.is_daring(self, True)
    my.is_monst_class_A(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_you_nat_attack_attempt_do(self, "gnome_all.on_you_nat_attack_attempt()")
    my.stat_def(self, 12)
    my.stat_dex(self, 8)
    my.stat_luck(self, 10)
    my.stat_str(self, 8)
    my.text_description_long2(self, "This particular gnome is a dwarfish gnome hybrid. How did this come about? Best not to ask. As a result, this gnome prefers the use of a small axe.")
    my.text_description_long3(self, "Gnorfs are stouter and far stronger than normal gnomes with excellent defensive and offensive abilities. Do not underestimate them and definitely do not laugh at their red hats. The red is blood.")
    my.text_description_short(self, "A stalwart gnorf.")
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gnome_dwarf", text_long_name="gnorf")


init()
