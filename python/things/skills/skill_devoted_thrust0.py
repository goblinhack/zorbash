import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.on_use_do(self, "me.on_use()")
    my.skill_base_name(self, "skill_devoted_thrust")
    my.text_description_long2(self, "The Devoted Thrust skill directs your stamina into sheer vanquishing power.")
    my.text_description_long3(self, "Be warned that at high levels of this skill, you will become drained very quickly and may render yourself unable to move or jump, or escape a trap.")
    my.text_description_long(self, "With devotion to the god, gods, or whatever it is that you worship, you willingly sacrifice life energy in the pursuit of maximal damage.")
    my.text_description_short(self, "Devoted thrust skill.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.tile(self, tile="skill_devoted_thrust")
    my.tile(self, tile="skill_devoted_thrust_activated")
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
