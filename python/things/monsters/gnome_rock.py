import my
import gnome_all


def on_born(me, x, y):
    gnome_all.on_born(me, x, y)
    my.thing_carry(me, "gold4")
    my.thing_carry(me, "rock")
    my.thing_carry(me, "rock")
    my.thing_carry(me, "rock")


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The rock gnome cries out in tiny impotent rage!")


def tp_init(name, text_long_name):
    self = gnome_all.tp_init(name, text_long_name)
    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_B(self, 20)
    my.dmg_nat_att_dice(self, "1d6+1")
    my.dmg_nat_att_type(self, "gravel")
    my.health_initial_dice(self, "1d6+4")
    my.is_biome_dungeon(self, True)
    my.is_daring(self, True)
    my.is_hard(self, True)
    my.is_heavy(self, True)
    my.is_made_of_rock(self, True)
    my.is_monst_class_B(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_you_nat_att_do(self, "gnome_all.on_you_nat_att()")
    my.stat_def(self, 14)
    my.stat_dex(self, 6)
    my.stat_str(self, 12)
    my.text_description_long2(self, "This particular gnome is a rock gnome. Having spent so long underground, these gnomes have developed a dusty, rock like skin and a personality to match. This all makes them exceptionally tough to hit.")
    my.text_description_short(self, "An ignaceous rock gnome.")
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".5", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".6", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".7", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray60",
            tile=name + ".8", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gnome_rock", text_long_name="rock gnome")


init()
