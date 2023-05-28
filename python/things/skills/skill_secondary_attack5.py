import my
import tp

self = None


def on_tick(owner, skill, x, y):
    if my.pcg_randint(1, 100) < 10:
        my.thing_stamina_decr(owner, 1)
    return False  # didn't do anything


def on_use(owner, skill, target, x, y):
    attack = my.thing_attack_num_get(owner)
    if attack == 0:
        return

    my.spawn_using_items_radius_range(owner, skill, target, "skill_secondary_attack_effect")

    dmg = my.thing_dmg_current(owner)
    if (dmg == 0):
        dmg = 1
    my.thing_dmg_current_set(owner, dmg)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker

    my.dmg_num_of_attacks(self, 2)
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_tick_do(self, "me.on_tick()")
    my.on_use_do(self, "me.on_use()")
    my.skill_base_name(self, "skill_secondary_attack")
    my.skill_replaces(self, "skill_secondary_attack4")
    my.stat_def_bonus(self, -4)
    my.stat_str_bonus(self, 4)
    my.text_description_long(self, "With this skill you gain a secondary attack.")
    my.text_description_long2(self, "The additional attack will be 100 percent of the initial attack.")
    my.text_description_long3(self, "When activated, 10 percent chance of draining stamina per move.")
    my.text_description_short(self, "Double strike skill.")
    my.text_description_very_short(self, "SecAtck 5")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_secondary_attack")
    my.tile(self, tile="skill_secondary_attack_activated")
    my.tp_update(self)


def init():
    tp_init(name="skill_secondary_attack5", text_long_name="secondary attack skill 5", text_short_name="Secondry Attack 5")


init()
