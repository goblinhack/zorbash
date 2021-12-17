import my
import tp


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_get_charge_count(me) < my.thing_get_initial_charge_count(me):
        my.thing_incr_charge_count(me, 1)
        owner = my.thing_get_top_owner_id(me)
        if my.thing_is_player(owner):
            my.topcon(f"%%fg=orange$The {my.thing_get_name(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    my.thing_msg(me, "The wand of fire explodes, predictably in a fireball.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_at_thing(me, "fire")
    my.thing_kill(me, "exploded")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_charge_count(5)
    mytp.set_damage_fire_chance_d1000(1000)
    mytp.set_damage_fire_dice("1d8+6")
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_environ_avoids_water(100)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("300")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_item_magical(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_target_auto_select(True)
    mytp.set_is_tickable(True)  # So it can interact with fire
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_very_combustible(True)
    mytp.set_is_wand(True)
    mytp.set_is_wooden(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Discharges a powerful blast of fire upon an unwitting recipient...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_fall_do("me.on_fall()")
    mytp.set_on_idle_dice("1d200+200:me.on_idle()")
    mytp.set_on_you_are_hit_and_now_dead_do("me.on_you_are_hit_and_now_dead()")
    mytp.set_on_you_are_on_fire_do("me.on_fire()")
    mytp.set_projectile_name("projectile_fire")
    mytp.set_range_max(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A wand of fire.")
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
    tp_init(name="wand_fire", text_name="wand of fire", short_text_name="wand of fire")


init()
