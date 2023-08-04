import my
import gnome_all


def on_born(me, x, y):
    gnome_all.on_born(me, x, y)
    my.thing_carry(me, "dagger")
    my.thing_carry(me, "dart")
    my.thing_carry(me, "dart")
    my.thing_carry(me, "dart")
    my.thing_carry(me, "dart")
    my.thing_carry(me, "gold3")


def on_death_of_my_leader(me, x, y):
    if not my.thing_is_dead_or_dying(me):
        my.thing_msg(me, "The gnome thief cries out in tiny impotent rage!")


def on_stealing(me, victim, what, x, y):
    if my.py_pcg_random_range_inclusive(1, 100) < 100:
        if not my.thing_is_dead_or_dying(me):
            my.thing_msg(me, "The gnome thief cackles with glee and vanishes!")
        my.thing_teleport_randomly(me)
    else:
        if not my.thing_is_dead_or_dying(me):
            my.thing_msg(me, "The gnome thief cackles with glee!")


def tp_init(name, text_long_name):
    self = gnome_all.tp_init(name, text_long_name)
    # begin sort marker
    my.chance_d1000_carrier_of_treasure_class_B(self, 20)
    my.chance_d1000_steal_item(self, 500)
    my.health_initial_dice(self, "1d4+2")
    my.is_able_to_run_away_after_stealing(self, True)
    my.is_able_to_teleport_escape(self, True)
    my.is_biome_dungeon(self, True)
    my.is_cowardly(self, True)
    my.is_monst_class_A(self, True)
    my.on_born_do(self, "me.on_born()")
    my.on_stealing_do(self, "me.on_stealing()")
    my.on_you_nat_attack_attempt_do(self, "gnome_all.on_you_nat_attack_attempt()")
    my.teleport_distance(self, 20)
    my.text_description_long2(self, "This particular gnome is very adept at liberating items from their owners.")
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
