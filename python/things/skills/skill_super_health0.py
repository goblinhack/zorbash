import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_always_activated(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_owner_rcv_dmg_cold_do(self, "me.on_owner_rcv_dmg_cold()")
    my.on_owner_rcv_dmg_necrosis_do(self, "me.on_owner_rcv_dmg_necrosis()")
    my.on_owner_rcv_dmg_poison_do(self, "me.on_owner_rcv_dmg_poison()")
    my.on_owner_rcv_dmg_stat_con_do(self, "me.on_owner_rcv_dmg_stat_con()")
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.skill_base_name(self, "skill_super_health")
    my.text_description_long2(self, "You will gain damage reduction from cold, poison and draining.")
    my.text_description_long3(self, "Overall, this skill will make you sickeningly healthy and the envy of all that visit the dungeon gym.")
    my.text_description_long(self, "With this skill you are able to heal yourself quickly with no impact on stamina and recover from exhaustion quicker.")
    my.text_description_short(self, "annoyingly good health.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_super_health")
    my.tile(self, tile="skill_super_health_activated")
