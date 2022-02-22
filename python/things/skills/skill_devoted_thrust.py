import my
import tp

self = None


def on_use(owner, skill, target, x, y):
    my.level_spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    bonus = int(my.thing_stamina_get(owner) / 2)

    enchant = my.thing_enchant_get(skill)
    bonus += int((bonus / 10) * enchant)

    if bonus > 1:
        if my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=yellow$You strike with a mighty thrust of {bonus}.%%fg=reset$")
        my.thing_damage_current_incr(owner, bonus)
        my.thing_stamina_decr(owner, bonus)
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You run out of devotion.")
        my.thing_skill_deactivate(owner, skill)


def tp_inti(name, text_name):
    global self
    self = tp.Tp(name, text_name)

    my.is_enchantable(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.long_text_description(self, "Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away. Each enchant will add 10 percent to the damage, but will take the additional bonus off your stamina. Additional strength bonus of +1")
    my.on_use_do(self, "me.on_use()")
    my.stat_str_mod(self, 1)
    my.text_description(self, "Devoted thrust skill.")
    my.text_enchant(self, "+10 percent DMG")
    my.text_skill(self, "Redirect health to damage, costing stamina")
    my.tile(self, tile=name)
    my.tile(self, tile=name + "_activated")
    my.tile(self, tile=name + "_inactive")
    # my.z_prio(self, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(self)


def init():
    tp_inti(name="skill_devoted_thrust", text_name="devoted thrust")


init()
