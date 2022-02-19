import my
import tp

self = None


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_charge_count_get(me) < my.thing_initial_charge_count_get(me):
        my.thing_charge_count_incr(me, 1)
        owner = my.thing_top_owner_id_get(me)
        if my.thing_is_player(owner):
            my.thing_msg(me, f"%%fg=gold$The {my.thing_name_get(me)} pulses.%%fg=reset$")


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health_get(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health_get(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health_get(target)))
    damage = my.thing_damage_energy(item)
    enchant = my.thing_enchant_get(item)
    my.thing_damage_current_set(owner, damage + enchant)


def on_final_use(owner, item, target, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(owner, "The wand fades away into nothingness.")


def explode(me, x, y):
    my.thing_msg(me, "The wand of energy explodes in a blaze of power.")
    my.level_spawn_at_thing(me, "explosion_minor")
    my.level_spawn_fire_around_thing(me, "fire")
    my.thing_dead(me, "exploded")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The wand glows.")
    my.thing_charge_count_incr(me, 5)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.charge_count(self, 5)
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.damage_energy_chance_d1000(self, 1000)
    my.damage_energy_dice(self, "1d6+6")
    my.enchant_max(self, 2)
    my.equip_carry_anim(self, "wand_energy_carry")
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.gold_value_dice(self, "200")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_item_magical(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_spawner(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_very_combustible(self, True)
    my.is_victim_select(self, True)
    my.is_wand(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.laser_name(self, "laser_energy")
    my.long_text_description(self, "Discharges a powerful beam of energy upon an unwitting recipient...")
    my.noise_on_moving_or_being_carried(self, 5)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_fall_do(self, "me.on_fall()")
    my.on_final_use_do(self, "me.on_final_use()")
    my.on_idle_tick_freq_dice(self, "1d200+200:me.on_idle()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.range_max(self, 7)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A wand of energy.")
    my.text_enchant(self, "+5 CHARGE, +1 DMG")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name + ".1", delay_ms=100)
    my.tile(self, tile=name + ".2", delay_ms=100)
    my.tile(self, tile=name + ".3", delay_ms=100)
    my.tile(self, tile=name + ".4", delay_ms=100)
    my.tile(self, tile=name + ".5", delay_ms=100)
    my.tile(self, tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(
        name="wand_energy",
        text_name="wand of dept of energy",
        short_text_name="wand of energy",
    )


init()
