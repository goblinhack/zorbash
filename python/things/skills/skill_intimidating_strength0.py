import my


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_auto_activated(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.skill_base_name(self, "skill_intimidating_strength")
    my.text_description_long(self, "No more will you cower on the dungeon beaches with your puny physique. With this skill, your muscles will bulge providing much needed strength bonuses on attacks, and shoving things into pits.")
    my.text_description_short(self, "intimidating strength.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_intimidating_strength_activated")
    my.tile(self, tile="skill_intimidating_strength")
