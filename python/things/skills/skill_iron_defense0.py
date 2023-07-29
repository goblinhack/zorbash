import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.skill_base_name(self, "skill_iron_defense")
    my.text_description_long(self, "This skill allows you to focus all your energies purely on defense.")
    my.text_description_short(self, "Iron defense skill.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_iron_defense")
    my.tile(self, tile="skill_iron_defense_activated")
