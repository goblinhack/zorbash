import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_auto_activated(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.skill_base_name(self, "skill_artful_dodging")
    my.skill_base_name(self, "skill_devoted_thrust")
    my.text_description_long2(self, "As part of your training you will receive enhanced dexterity and defensive bonuses and the ability to recover stamina more quickly.")
    my.text_description_long(self, "This skill allows you to artfully dodge blows that rains down upon you with cat-like reflexes.")
    my.text_description_short(self, "Artful dodging skill.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_artful_dodging")
    my.tile(self, tile="skill_artful_dodging_activated")
