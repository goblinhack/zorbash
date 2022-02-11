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
            my.thing_msg(owner, f"%%fg=blue$The {my.thing_get_name(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    my.thing_msg(me, "The wand of descent explodes. The earth tremors.")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_dead(me, "exploded")


def on_final_use(owner, item, target, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(owner, "The wand crumbles into dust.")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(mytp, 2)
    my.tp_set_charge_count(mytp, 3)
    my.tp_set_collision_hit_priority(mytp, 5)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_equip_carry_anim(mytp, "wand_descent_carry")
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_gold_value_dice(mytp, "500")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_item_magical(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_spawner(mytp, True)
    my.tp_set_is_target_auto_select(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # So it can interact with fire
    my.tp_set_is_treasure_class_c(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_is_very_combustible(mytp, True)
    my.tp_set_is_wand(mytp, True)
    my.tp_set_is_wooden(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_laser_name(mytp, "laser_descent")
    my.tp_set_long_text_description(mytp, "This most dangerous wand can transport its target to the next level by the most efficacious means possible...")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 5)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_fall_do(mytp, "me.on_fall()")
    my.tp_set_on_final_use_do(mytp, "me.on_final_use()")
    my.tp_set_on_idle_tick_frequency_dice(mytp, "1d1000+200:me.on_idle()")
    my.tp_set_on_you_are_hit_and_now_dead_do(mytp, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_on_you_are_on_fire_do(mytp, "me.on_fire()")
    my.tp_set_range_max(mytp, 7)
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A wand of descent.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=100)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=100)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="wand_descent",
        text_name="wand of sudden descent",
        short_text_name="wand of descent",
    )


init()
