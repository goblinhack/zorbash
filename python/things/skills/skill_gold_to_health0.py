import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.skill_base_name(self, "skill_gold_to_health")
    my.text_description_long2(self, "When in use, your skin glows radiantly. However you will also feel sluggish and less dextrous than normal.")
    my.text_description_long(self, "With this skill you are able to trans-mutate your hard earned gold into life giving health energy.")
    my.text_description_short(self, "golden health skill.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_gold_to_health")
    my.tile(self, tile="skill_gold_to_health_activated")
