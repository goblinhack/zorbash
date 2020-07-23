import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_attackable_by_player(True)
    x.set_is_combustible(True)
    x.set_is_corpse_on_death(True)
    x.set_is_cursor_can_hover_over(True)
    x.set_is_door(True)
    x.set_is_gfx_health_bar_shown_only_when_injured(True)
    x.set_is_open_on_death(True)
    x.set_is_double_damage_from_fire(True)
    x.set_is_fire_hater(100)
    x.set_is_flammable(True)
    x.set_is_interesting(True)
    x.set_is_light_blocker(True)
    x.set_is_movement_blocking_hard(True)
    x.set_is_sidebar_item(True)
    x.set_normal_placement_rules(True)
    x.set_stats_defence(2)
    x.set_stats_health_initial(100)
    x.set_text_a_or_an("the");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)
    x.set_text_description("A door covered in claw marks")

    x.set_tile(tile=name + ".100", is_hp_100_percent=True)
    x.set_tile(tile=name + ".75", is_hp_75_percent=True)
    x.set_tile(tile=name + ".50", is_hp_50_percent=True)
    x.set_tile(tile=name + ".25", is_hp_25_percent=True)
    x.set_tile(tile=name + ".dead", is_dead=True)
    x.set_tile(tile=name + ".open", is_hp_100_percent=True, is_open=True)
    x.set_tile(tile=name + ".open", is_hp_75_percent=True, is_open=True)
    x.set_tile(tile=name + ".open", is_hp_50_percent=True, is_open=True)
    x.set_tile(tile=name + ".open", is_hp_25_percent=True, is_open=True)

    x.update()

def init():
    tp_init(name="door1", text_name="door")

init()
