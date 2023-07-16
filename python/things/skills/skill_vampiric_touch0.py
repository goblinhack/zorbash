import my


def do_vampiric_touch(me, owner, hitter, real_hitter, x, y, damage, damage_reduction_percent):
    # my.con("me      {} {:X}".format(my.thing_name_get(me), me))
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("hitter  {} {:X}".format(my.thing_name_get(hitter), hitter))
    # my.con("rhitter {} {:X}".format(my.thing_name_get(real_hitter), real_hitter))

    if real_hitter == me:
        return damage

    if my.thing_is_undead(real_hitter):
        return damage

    dmg_reduction = 0

    if my.thing_is_monst(real_hitter):
        dmg_reduction = int(float(damage) / 100.0 * damage_reduction_percent)
        if dmg_reduction == 0:
            dmg_reduction = 1

    if dmg_reduction > 0:
        if owner and (my.thing_health(owner) < my.thing_health_max(owner)):

            health_boost = int(float(dmg_reduction) / 2.0)
            my.thing_health_incr(owner, health_boost)

            stamina_boost = dmg_reduction
            my.thing_stamina_incr(owner, stamina_boost)

            if my.thing_is_player(owner):
                if health_boost > 0:
                    real_hitter_name = my.thing_name_get(real_hitter)
                    my.thing_msg(owner, f"Vampiric touch heals you for {health_boost} and drains the {real_hitter_name} for {dmg_reduction} stamina.")
                elif stamina_boost > 0:
                    real_hitter_name = my.thing_name_get(real_hitter)
                    my.thing_msg(owner, f"Vampiric touch replenishes you for {stamina_boost} and drains the {real_hitter_name} for {dmg_reduction} stamina.")

        target = real_hitter
        my.thing_hit_dmg_stamina(me, me, target, dmg_reduction)

    return damage - dmg_reduction


def tp_init(self):
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_loggable(self, True)
    my.is_skill(self, True)
    my.is_tickable(self, True)
    my.on_owner_receive_dmg_acid_do(self, "me.on_owner_receive_dmg_acid()")
    my.on_owner_receive_dmg_bite_do(self, "me.on_owner_receive_dmg_bite()")
    my.on_owner_receive_dmg_claw_do(self, "me.on_owner_receive_dmg_claw()")
    my.on_owner_receive_dmg_cold_do(self, "me.on_owner_receive_dmg_cold()")
    my.on_owner_receive_dmg_crush_do(self, "me.on_owner_receive_dmg_crush()")
    my.on_owner_receive_dmg_digest_do(self, "me.on_owner_receive_dmg_digest()")
    my.on_owner_receive_dmg_drown_do(self, "me.on_owner_receive_dmg_drown()")
    my.on_owner_receive_dmg_energy_do(self, "me.on_owner_receive_dmg_energy()")
    my.on_owner_receive_dmg_fire_do(self, "me.on_owner_receive_dmg_fire()")
    my.on_owner_receive_dmg_heat_do(self, "me.on_owner_receive_dmg_heat()")
    my.on_owner_receive_dmg_lightning_do(self, "me.on_owner_receive_dmg_lightning()")
    my.on_owner_receive_dmg_melee_do(self, "me.on_owner_receive_dmg_melee()")
    my.on_owner_receive_dmg_missile_do(self, "me.on_owner_receive_dmg_missile()")
    my.on_owner_receive_dmg_nat_att_do(self, "me.on_owner_receive_dmg_nat_att()")
    my.on_owner_receive_dmg_necrosis_do(self, "me.on_owner_receive_dmg_necrosis()")
    my.on_owner_receive_dmg_poison_do(self, "me.on_owner_receive_dmg_poison()")
    my.on_owner_receive_dmg_stat_con_do(self, "me.on_owner_receive_dmg_stat_con()")
    my.on_owner_receive_dmg_stat_str_do(self, "me.on_owner_receive_dmg_stat_str()")
    my.skill_base_name(self, "skill_vampiric_touch")
    my.text_description_long2(self, "This is a powerful skill and whilst active, you will experience a powerful constitution and luck drain. Do vampires need luck anyway?")
    my.text_description_long3(self, "This skill is not effective against the undead. Also beware that certain types of damage, such as heat fire, lightning and drowning will be more potent whilst this skill is active.")
    my.text_description_long(self, "With this dark skill you are able to gain stamina and some health from the creature that attacked you, draining it for the same amount you recover")
    my.text_description_short(self, "vampiric touch.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker
    my.tile(self, tile="skill_vampiric_touch")
    my.tile(self, tile="skill_vampiric_touch_activated")
