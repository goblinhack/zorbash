import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.on_tick_when_deactivated_do(self, "me.on_tick_when_deactivated()")
    my.on_use_skill_do(self, "me.on_use_skill()")
    my.skill_base_name(self, "skill_primal_rage")
    my.text_description_long2(self, "When raging your stamina will drain rapidly.")
    my.text_description_long(self, "Engage your primal spirit with the ability to rage when low on health. In such a state of frenzy you will gain strength, to-hit and damage bonuses.")
    my.text_description_short(self, "primal rage skill.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_primal_rage")
    my.tile(self, tile="skill_primal_rage_activated")
