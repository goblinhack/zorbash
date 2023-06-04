import my
import tp
import skill_vampiric_touch0

self = None


def on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage):
    return skill_vampiric_touch0.do_vampiric_touch(me, owner, hitter, real_hitter, x, y, damage, 20)


def on_owner_receive_dmg_melee(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_poison(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_drown(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage * 2)


def on_owner_receive_dmg_bite(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_claw(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_cold(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_fire(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage * 2)


def on_owner_receive_dmg_heat(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage * 2)


def on_owner_receive_dmg_crush(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_missile(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_lightning(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage * 2)


def on_owner_receive_dmg_energy(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_acid(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_digest(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_nat_att(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_receive_dmg(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_receive_dmg_stat_str(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def on_owner_receive_dmg_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    return damage


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.stat_con_bonus(self, -5)
    my.stat_luck_bonus(self, -5)
    my.skill_replaces(self, "skill_vampiric_touch1")
    my.text_description_long4(self, "Damage reduction is 20 percent of damage dealt. Of that, the damage reduction will be applied to your stamina, and conversely will drain the attacker for the same amount. Health will improve at 50 percent of the damage reduction")
    my.text_description_very_short(self, "VamTouch2")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    skill_vampiric_touch0.tp_init(self)
    my.tp_update(self)


def init():
    tp_init(name="skill_vampiric_touch2", text_long_name="vampiric touch 2", text_short_name="vampiric touch 2")


init()
