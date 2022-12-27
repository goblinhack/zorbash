import my
import tp

self = None


def on_use(owner, skill, target, x, y):

    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health(owner)))
    # my.topcon("skill  {} {}".format(my.thing_name_get(skill), my.thing_health(skill)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health(target)))

    my.thing_stamina_decr(owner, 1)

    attack = my.thing_attack_num_get(owner)
    if attack == 0:
        return

    my.spawn_using_items_radius_range(owner, skill, target, "skill_secondary_attack_effect")

    enchant = my.thing_enchant_count_get(skill)
    dmg = my.thing_dmg_current(owner)
    dmg = int(dmg / 2) + enchant
    if (dmg == 0):
        dmg = 1
    my.topcon("dmg {}".format(dmg))
    my.thing_dmg_current_set(owner, dmg)


def tp_init(name, text_long_name):
    global self
    self = tp.Tp(name, text_long_name)
    # begin sort marker

    my.attacks_per_round(self, 2)
    my.gfx_ascii_shown(self, True)
    my.is_enchantable(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.on_use_do(self, "me.on_use()")
    my.stat_str_mod(self, 1)
    my.text_description_enchant(self, "+1 DMG")
    my.text_description_long2(self, "Each enchant will add one to the damage.")
    my.text_description_long(self, "With this skill you gain a secondary attack. The additional attack will be 50 percent of the initial attack")
    my.text_description_short(self, "Secondary attack skill.")
    my.text_skill(self, "Secondary attack")
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
    tp_init(name="skill_secondary_attack", text_long_name="secondary attack skill")


init()
