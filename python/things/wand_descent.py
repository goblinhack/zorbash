import zx
import tp

def on_idle(me, x, y):
    if zx.thing_get_charge_count(me) < zx.thing_get_initial_charge_count(me):
        zx.thing_incr_charge_count(me, 1)
        owner = zx.thing_get_top_owner_id(me)
        if zx.thing_is_player(owner):
            zx.topcon("%%fg=blue$The {} pulses.%%fg=reset$".format(
                zx.thing_get_name(me)))

def explode(me, x, y):
    zx.thing_msg(me, "The wand of descent explodes. The earth tremors.")
    zx.level_spawn_at_thing(me, "explosion_major")
    zx.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    zx.thing_killed(me, "exploded")

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    explode(me, x, y)

def on_fire(me, x, y):
    explode(me, x, y)

def on_fall(me, x, y):
    explode(me, x, y)

def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_item_height(2)
    mytp.set_item_width(2)
    mytp.set_blast_max_radius(2)
    mytp.set_blast_min_radius(0)
    mytp.set_charge_count(3)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(5)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True) # So it can interact with fire
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_spawner(True)
    mytp.set_is_target_select_automatically_when_chosen(True)
    mytp.set_is_treasure_class_c(True)
    mytp.set_is_treasure(True)
    mytp.set_is_usable(True)
    mytp.set_is_very_combustible(True)
    mytp.set_is_wand(True)
    mytp.set_laser_name("laser_descent")
    mytp.set_long_text_description("This most dangerous wand can transport its target to the next level by the most efficacious means possible...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_fall_do("wand_descent.on_fall()")
    mytp.set_on_fire_do("wand_descent.on_fire()")
    mytp.set_on_hit_do("wand_descent.on_hit()")
    mytp.set_on_idle_dice("1d1000+200:wand_descent.on_idle()")
    mytp.set_range_max(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=cyan$A wand of descent.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", delay_ms=100)
    mytp.set_tile(tile=name + ".2", delay_ms=100)
    mytp.set_tile(tile=name + ".3", delay_ms=100)
    mytp.set_tile(tile=name + ".4", delay_ms=100)
    mytp.set_tile(tile=name + ".5", delay_ms=100)
    mytp.set_tile(tile=name + ".6", delay_ms=100)

    mytp.update()

def init():
    tp_init(name="wand_descent", text_name="wand of descent", short_text_name="wand.descent")

init()
