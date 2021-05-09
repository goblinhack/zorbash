import zx
import tp

mytp = None

def on_use(owner, skill, target, x, y):
    zx.level_spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    #zx.topcon("owner  {} {}".format(zx.thing_get_name(owner), zx.thing_get_health(owner)))
    #zx.topcon("skill  {} {}".format(zx.thing_get_name(skill), zx.thing_get_health(skill)))
    #zx.topcon("target {} {}".format(zx.thing_get_name(target), zx.thing_get_health(target)))
    bonus = int(zx.thing_get_stamina(owner) / 2)

    enchant = zx.thing_get_enchant(skill)
    bonus += int((bonus / 10) * enchant)

    if bonus > 1:
        if zx.if_matches(owner, "is_player"):
            zx.topcon("%%fg=yellow$You strike with a mighty thrust of {}.%%fg=reset$".format(bonus))
        zx.thing_incr_current_damage(owner, bonus)
        zx.thing_decr_stamina(owner, bonus)
    else:
        if zx.if_matches(owner, "is_player"):
            zx.topcon("You run out of devotion.")
        zx.thing_skill_deactivate(owner, skill)

def skill_devoted_thrust_init(name, text_name):
    global mytp
    mytp = tp.Tp(name, text_name)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_skill(True)
    mytp.set_is_enchantable(True)
    mytp.set_enchant_max(2)
    mytp.set_text_enchant("+10 percent damage")
    mytp.set_text_skill("Redirect health to damage, costing stamina");
    mytp.set_long_text_description("Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away. Each enchant will add 10 percent to the damage, but will take the additional bonus off your stamina.")
    mytp.set_on_use_do("skill_devoted_thrust.on_use()")
    mytp.set_text_description("Devoted thrust skill.")
    mytp.set_tile(tile=name)
    mytp.set_tile(tile=name + "_inactive")
    mytp.set_tile(tile=name + "_activated")
    mytp.update()

def init():
    skill_devoted_thrust_init(name="skill_devoted_thrust", text_name="devoted thrust")

init()
