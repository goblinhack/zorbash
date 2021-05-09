import zx
import tp

def on_use(owner, skill, target, x, y):
    zx.level_spawn_using_items_radius_range(owner, skill, target, "skill_devoted_thrust_effect")
    #zx.topcon("owner  {} {}".format(zx.thing_get_name(owner), zx.thing_get_health(owner)))
    #zx.topcon("skill  {} {}".format(zx.thing_get_name(skill), zx.thing_get_health(skill)))
    #zx.topcon("target {} {}".format(zx.thing_get_name(target), zx.thing_get_health(target)))
    bonus = int(zx.thing_get_stamina(owner) / 2)
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
    x = tp.Tp(name, text_name)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_skill(True)
    x.set_is_enchantable(True)
    x.set_enchant_max(2)
    x.set_text_enchant("increase damage by 50%")
    x.set_long_text_description("Uses half of your stamina points up in one mighty strike.\n\nCan be used multiple times, but beware, your stamina will rapidly drop to zero and you may end up unable to attack or jump away.")
    x.set_on_use_do("skill_devoted_thrust.on_use()")
    x.set_text_description("Devoted thrust skill.")
    x.set_tile(tile=name)
    x.set_tile(tile=name + "_inactive")
    x.set_tile(tile=name + "_activated")
    x.update()

def init():
    skill_devoted_thrust_init(name="skill_devoted_thrust", text_name="devoted thrust")

init()
