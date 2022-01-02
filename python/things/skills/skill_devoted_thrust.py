import my
import tp

mytp = None


def on_use(owner, skill, target, x, y):
    my.level_spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    # my.topcon("owner  {} {}".format(my.thing_get_name(owner), my.thing_get_health(owner)))
    # my.topcon("skill  {} {}".format(my.thing_get_name(skill), my.thing_get_health(skill)))
    # my.topcon("target {} {}".format(my.thing_get_name(target), my.thing_get_health(target)))
    bonus = int(my.thing_get_stamina(owner) / 2)

    enchant = my.thing_get_enchant(skill)
    bonus += int((bonus / 10) * enchant)

    if bonus > 1:
        if my.thing_is_player(owner):
            my.topcon(f"%%fg=yellow$You strike with a mighty thrust of {bonus}.%%fg=reset$")
        my.thing_incr_current_damage(owner, bonus)
        my.thing_decr_stamina(owner, bonus)
    else:
        if my.thing_is_player(owner):
            my.topcon("You run out of devotion.")
        my.thing_skill_deactivate(owner, skill)


def tp_inti(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)

    mytp.set_enchant_max(2)
    mytp.set_is_enchantable(True)
    mytp.set_is_loggable(True)
    mytp.set_is_skill(True)
    mytp.set_long_text_description("Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away. Each enchant will add 10 percent to the damage, but will take the additional bonus off your stamina. Additional strength bonus of +1")
    mytp.set_on_use_do("me.on_use()")
    mytp.set_stat_str_mod(1)
    mytp.set_text_description("Devoted thrust skill.")
    mytp.set_text_enchant("+10 percent damage")
    mytp.set_text_skill("Redirect health to damage, costing stamina")
    mytp.set_tile(tile=name)
    mytp.set_tile(tile=name + "_activated")
    mytp.set_tile(tile=name + "_inactive")
    # mytp.set_z_prio(my.MAP_PRIO_NORMAL) # End marker for fixup.sh
    mytp.update()


def init():
    tp_inti(name="skill_devoted_thrust", text_name="devoted thrust")


init()
