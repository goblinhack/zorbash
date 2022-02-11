import my
import tp

mytp = None


def on_use(owner, skill, target, x, y):
    my.level_spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    bonus = int(my.thing_get_stamina(owner) / 2)

    enchant = my.thing_get_enchant(skill)
    bonus += int((bonus / 10) * enchant)

    if bonus > 1:
        if my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=yellow$You strike with a mighty thrust of {bonus}.%%fg=reset$")
        my.thing_incr_current_damage(owner, bonus)
        my.thing_decr_stamina(owner, bonus)
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You run out of devotion.")
        my.thing_skill_deactivate(owner, skill)


def tp_inti(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    my.tp_set_enchant_max(mytp, 2)
    my.tp_set_is_enchantable(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_skill(mytp, True)
    my.tp_set_long_text_description(mytp, "Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away. Each enchant will add 10 percent to the damage, but will take the additional bonus off your stamina. Additional strength bonus of +1")
    my.tp_set_on_use_do(mytp, "me.on_use()")
    my.tp_set_stat_str_mod(mytp, 1)
    my.tp_set_text_description(mytp, "Devoted thrust skill.")
    my.tp_set_text_enchant(mytp, "+10 percent damage")
    my.tp_set_text_skill(mytp, "Redirect health to damage, costing stamina")
    my.tp_set_tile(mytp, tile=name)
    my.tp_set_tile(mytp, tile=name + "_activated")
    my.tp_set_tile(mytp, tile=name + "_inactive")
    # my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    my.tp_update(mytp, )


def init():
    tp_inti(name="skill_devoted_thrust", text_name="devoted thrust")


init()
