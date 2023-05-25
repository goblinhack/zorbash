import my
import tp

self = None


def on_tick(owner, skill, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("skill  {} {}".format(my.thing_name_get(skill), my.thing_health(skill)))

    if my.thing_gold(owner) <= 0:
        return False  # did nothing

    if my.thing_health(owner) >= my.thing_health_max(owner):
        return False  # did nothing

    my.thing_gold_decr(owner, 1)
    my.spawn_using_items_radius_range(owner, skill, owner, "skill_gold_to_health_effect")
    my.thing_sound_play_channel(owner, my.CHANNEL_WEAPON, "coindrop")
    return False  # did nothing


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_do(self, "me.on_tick()")
    my.skill_base_name(self, "skill_gold_to_health")
    my.stat_dex_bonus(self, -1)
    my.stat_str_bonus(self, 1)
    my.text_description_long(self, "With this skill you are able to trans-mutate gold into life giving health.")
    my.text_description_short(self, "Golden health skill.")
    my.text_description_very_short(self, "GldToHp 1")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self,
            tile=name)
    my.tile(self,
            tile=name + "_activated")
    my.tile(self,
            tile=name + "_inactive")
    my.tp_update(self)


def init():
    tp_init(name="skill_gold_to_health", text_long_name="gold to health skill", text_short_name="Gold To Health 1")


init()
