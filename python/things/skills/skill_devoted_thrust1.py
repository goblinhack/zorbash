import my
import tp

self = None


def on_tick(owner, skill, x, y):
    if owner and my.pcg_randint(1, 100) < 10:
        my.thing_stamina_decr(owner, 1)
    return False  # didn't do anything


def on_use(owner, skill, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("skill  {} {}".format(my.thing_name_get(skill), my.thing_health(skill)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))
    my.spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    bonus = int(my.thing_stamina(owner) / 10) * 2

    if bonus > 1:
        if my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=yellow$You strike with a mighty thrust of {bonus} additional damage.%%fg=reset$")
        my.thing_dmg_current_incr(owner, bonus)
        my.thing_stamina_decr(owner, bonus)
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You run out of devotion.")
        my.thing_skill_deactivate(owner, skill)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_do(self, "me.on_tick()")
    my.on_use_do(self, "me.on_use()")
    my.skill_base_name(self, "skill_devoted_thrust")
    my.stat_def_bonus(self, -1)
    my.stat_str_bonus(self, 1)
    my.text_description_long(self, "Uses 20 percent of your stamina points up in one mighty strike.")
    my.text_description_long3(self, "When activated, 10 percent chance of draining stamina per move.")
    my.text_description_short(self, "Devoted thrust skill.")
    my.text_description_very_short(self, "DevtThr 1")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_devoted_thrust")
    my.tile(self, tile="skill_devoted_thrust_activated")
    my.tp_update(self)


def init():
    tp_init(name="skill_devoted_thrust1", text_long_name="devoted thrust 1", text_short_name="devoted thrust 1")


init()
