import builtins
import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_under(me, "acid1")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)

    x.set_ai_delay_after_moving_ms(1000)
    x.set_ai_scent_distance(5)
    x.set_collision_attack(True)
    x.set_collision_attack_radius(0.60)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_acid(True)
    x.set_is_acid_dweller(True)
    x.set_is_active(True)
    x.set_is_attack_eater(True)
    x.set_is_attack_lunge(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_combustible(True)
    x.set_is_corpse_on_death(True)
    x.set_is_double_damage_from_fire(True)
    x.set_is_fire_hater(100)
    x.set_is_gfx_health_bar_shown(True)
    x.set_is_gfx_moves_ahead_shown(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_interesting(True)
    x.set_is_item_eater(True)
    x.set_is_light_strength(20)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_potion_eater(True)
    x.set_is_shown_on_monstbar(True)
    x.set_is_slime_baby_eater(True)
    x.set_is_slime_eater(True)
    x.set_is_treasure_eater(True)
    x.set_light_color("green")
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d4")
    x.set_on_idle_dice_do("1d0:cube1.spawn()")
    x.set_stats_attack_dice("1d5")
    x.set_stats_defence(0)
    x.set_stats_health_hunger_pct(95)
    x.set_stats_health_initial(25)
    x.set_stats_move_speed_ms(1000)
    x.set_stats_strength(1)
    x.set_text_a_or_an("a");
    x.set_text_description("An dungeon auto cleaner jelly thingy")
    x.set_text_hits("burns");
    x.set_tick_rate_tenths(3)
    x.set_weapon_use_anim("splat1")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)

    delay=10
    x.set_tile("splat1.1", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.2", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.3", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.4", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.5", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.6", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.7", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.8", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.9", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.10", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.11", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.12", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.13", is_dead=True, delay_ms=delay)
    x.set_tile("splat1.14", is_dead=True, delay_ms=delay, is_end_of_anim = True)

    x.update()

def init():
    tp_init(name="cube1", text_name="acid cube")

init()
