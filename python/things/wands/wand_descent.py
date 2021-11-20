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
            my.topcon("%%fg=blue$The {} pulses.%%fg=reset$".format(
                my.thing_get_name(me)))

def explode(me, x, y):
    my.thing_msg(me, "The wand of descent explodes. The earth tremors.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_defeated(me, "exploded")

def on_final_use(owner, item, target, x, y):
    if my.thing_is_player(owner):
        my.topcon("The wand crumbles into dust.")

def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, damage):
    explode(me, x, y)

def on_fire(me, x, y):
    explode(me, x, y)

def on_fall(me, x, y):
    explode(me, x, y)

def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_blast_max_radius(2)
    mytp.set_blast_min_radius(0)
    mytp.set_charge_count(3)
    mytp.set_collision_hit_priority(5)
    mytp.set_environ_damage_doubled_from_fire(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("500")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_item_magical(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_spawner(True)
    mytp.set_is_target_auto_select(True)
    mytp.set_is_tickable(True) # So it can interact with fire
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_is_very_combustible(True)
    mytp.set_is_wand(True)
    mytp.set_is_wooden(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_laser_name("laser_descent")
    mytp.set_long_text_description("This most dangerous wand can transport its target to the next level by the most efficacious means possible...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_fall_do("wand_descent.on_fall()")
    mytp.set_on_final_use_do("wand_descent.on_final_use()")
    mytp.set_on_idle_dice("1d1000+200:wand_descent.on_idle()")
    mytp.set_on_you_are_hit_do("wand_descent.on_you_are_hit()")
    mytp.set_on_you_are_on_fire_do("wand_descent.on_fire()")
    mytp.set_range_max(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=cyan$A wand of descent.")
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
    tp_init(name="wand_descent", text_name="wand of sudden descent", short_text_name="wand.descent")

init()
