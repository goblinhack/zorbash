import my


def tp_init(self):
    # begin sort marker
    my.dmg_num_of_attacks(self, 2)
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.on_use_do(self, "me.on_use()")
    my.skill_base_name(self, "skill_double_strike")
    my.text_description_long(self, "With this skill you will develop the ability to deliver a deadly second strike. Initially the extra damage will be minimal but over time you will become a true force to be reckoned with.")
    my.text_description_short(self, "Double strike skill.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_double_strike")
    my.tile(self, tile="skill_double_strike_activated")
