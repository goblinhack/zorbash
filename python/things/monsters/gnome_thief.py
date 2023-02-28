import my
import gnome_all


def on_born(me, x, y):
    gnome_all.on_born(me, x, y)


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The gnome thief cries out in tiny impotent rage!")


def tp_init(name, text_long_name):
    self = gnome_all.tp_init(name, text_long_name)
    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_B(self, 20)
    my.chance_d1000_steal_item(self, 500)
    my.health_initial_dice(self, "1d4+2")
    my.is_able_to_teleport_escape(self, True)
    my.is_biome_dungeon(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_A(self, True)
    my.is_cowardly(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_death_of_my_leader_do(self, "me.on_death_of_my_leader()")
    my.on_you_nat_att_do(self, "gnome_all.on_you_nat_att()")
    my.text_description_long2(self, "This particular gnome is very adept at liberating items from their owners.0")
    my.text_description_short(self, "A sneaky gnome thief.")
    # end sort marker

    delay = 300
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="g", ascii_bg_col_name="", ascii_fg_col_name="gray30",
            tile=name + ".dead", is_dead=True, delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="gnome_thief", text_long_name="gnome thief")


init()
