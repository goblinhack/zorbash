import my
import tp

mytp = None


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_get_charge_count(me) < my.thing_get_initial_charge_count(me):
        my.thing_incr_charge_count(me, 1)
        owner = my.thing_get_top_owner_id(me)
        if my.thing_is_player(owner):
            my.thing_msg(me, f"%%fg=gold$The {my.thing_get_name(me)} pulses.%%fg=reset$")


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_get_name(owner), my.thing_get_health(owner)))
    # my.topcon("item   {} {}".format(my.thing_get_name(item), my.thing_get_health(item)))
    # my.topcon("target {} {}".format(my.thing_get_name(target), my.thing_get_health(target)))
    damage = my.thing_get_damage_energy(item)
    enchant = my.thing_get_enchant(item)
    my.thing_set_current_damage(owner, damage + enchant)


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
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The wand glows.")
    my.thing_incr_charge_count(me, 5)


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_charge_count(5)
    mytp.set_collision_hit_priority(5)
    mytp.set_damage_energy_chance_d1000(1000)
    mytp.set_damage_energy_dice("1d6+6")
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_enchant_max(2)
    mytp.set_equip_carry_anim("wand_energy_carry")
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("200")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_burnable(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_item_magical(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_spawner(True)
    mytp.set_is_target_auto_select(True)
    mytp.set_is_tickable(True)  # So it can interact with fire
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_very_combustible(True)
    mytp.set_is_wand(True)
    mytp.set_is_wooden(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_laser_name("laser_energy")
    mytp.set_long_text_description("Discharges a powerful beam of energy upon an unwitting recipient...")
    mytp.set_noise_decibels(5)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("me.on_enchant()")
    mytp.set_on_fall_do("me.on_fall()")
    mytp.set_on_final_use_do("me.on_final_use()")
    mytp.set_on_idle_tick_frequency_dice("1d200+200:me.on_idle()")
    mytp.set_on_use_do("me.on_use()")
    mytp.set_on_you_are_hit_and_now_dead_do("me.on_you_are_hit_and_now_dead()")
    mytp.set_on_you_are_on_fire_do("me.on_fire()")
    mytp.set_range_max(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A wand of energy.")
    mytp.set_text_enchant("+5 charges, +1 damage")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", delay_ms=100)
    mytp.set_tile(tile=name + ".2", delay_ms=100)
    mytp.set_tile(tile=name + ".3", delay_ms=100)
    mytp.set_tile(tile=name + ".4", delay_ms=100)
    mytp.set_tile(tile=name + ".5", delay_ms=100)
    mytp.set_tile(tile=name + ".6", delay_ms=100)

    mytp.update()


def init():
    tp_init(
        name="wand_energy",
        text_name="wand of dept of energy",
        short_text_name="wand of energy",
    )


init()
