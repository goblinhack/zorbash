import my
import tp

self = None


def on_tick_when_activated(owner, skill, x, y):
    if not owner:
        return False  # did nothing

    if my.thing_stamina(owner) >= my.thing_stamina_max(owner):
        return False  # did nothing

    if owner and my.pcg_randint(1, 100) < 40:
        my.thing_stamina_incr(owner, 1)
        return False  # did nothing

    return False  # did nothing


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_auto_activated(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_when_activated_do(self, "me.on_tick_when_activated()")
    my.skill_base_name(self, "skill_artful_dodging")
    my.skill_replaces(self, "skill_artful_dodging3")
    my.stat_def_bonus(self, 3)
    my.stat_dex_bonus(self, 3)
    my.text_description_long2(self, "As a result of your training you will be able to recover stamina with a 40 percent chance per move.")
    my.text_description_long(self, "Artfully dodging blows that rain down upon you with enhanced defense and dexterity bonuses.")
    my.text_description_short(self, "Artful dodging skill.")
    my.text_description_very_short(self, "ArtDodge4")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_artful_dodging_activated")
    my.tile(self, tile="skill_artful_dodging")
    my.tp_update(self)


def init():
    tp_init(name="skill_artful_dodging4", text_long_name="artful dodging 4", text_short_name="artful dodging 4")


init()
