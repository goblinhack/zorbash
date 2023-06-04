import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.skill_base_name(self, "skill_healing")
    my.text_description_long(self, "With this skill you are able to heal yourself quickly at the expense of your stamina.")
    my.text_description_short(self, "Accelerated healing.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_healing_activated")
    my.tile(self, tile="skill_healing")
