import zx
import tp

def on_use(me, what, target, x, y):
    zx.tp_spawn_at(target, "explosion1")
    zx.tp_spawn_radius_range(me, what, target, "wand_energy_effect")

def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_bag_item_height(2)
    x.set_bag_item_width(2)
    x.set_blast_max_radius(0)
    x.set_blast_min_radius(0)
    x.set_charge_count(5)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_burnable(True)
    x.set_is_collectable(True)
    x.set_is_combustible(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_droppable(True)
    x.set_is_flammable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_laser_target_select_automatically_when_chosen(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_spawner(True)
    x.set_is_treasure(True)
    x.set_is_treasure_class_b(True)
    x.set_is_usable(True)
    x.set_is_wand(True)
    x.set_laser_name("laser_energy")
    x.set_long_text_description("Discharges a powerful beam of energy upon an unwitting recipient...")
    x.set_normal_placement_rules(True)
    x.set_on_use_do("wand_energy.on_use()")
    x.set_range_max(7)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=yellow$A wand of energy.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", delay_ms=100)
    x.set_tile(tile=name + ".2", delay_ms=100)
    x.set_tile(tile=name + ".3", delay_ms=100)
    x.set_tile(tile=name + ".4", delay_ms=100)
    x.set_tile(tile=name + ".5", delay_ms=100)
    x.set_tile(tile=name + ".6", delay_ms=100)

    x.update()

def init():
    tp_init(name="wand_energy", text_name="wand of energy", short_text_name="wand.energy")

init()
