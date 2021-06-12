import zx
import tp

def on_idle_dice(me, x, y):
    zx.level_spawn_next_to(me, "ghost_minion")

def on_death(me, x, y):
    zx.level_spawn_at_thing(me, "generator_explosion")

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_attack_shove_chance_d1000(200)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_damage_doubled_from_water(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_glows(True)
    mytp.set_gfx_oversized_but_sitting_on_the_ground(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_hates_acid(True)
    mytp.set_hates_fire(100)
    mytp.set_hates_water(100)
    mytp.set_health_initial_dice("6d6")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True)
    mytp.set_is_always_hit(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_burnable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_ethereal_minion_generator(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_minion_generator(True)
    mytp.set_is_movement_blocking_soft(True)
    mytp.set_is_resurrectable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_shown_on_leftbar(True)
    mytp.set_light_color("cyan")
    mytp.set_light_strength(2)
    mytp.set_long_text_description("A bone portal which spews the angry spirits of those long passed.")
    mytp.set_minion_limit(5)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("ghost_minion_generator.on_death()")
    mytp.set_on_idle_dice("1d10+10:ghost_minion_generator.on_idle_dice()")
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(0)
    mytp.set_stat_defence(0)
    mytp.set_stat_strength(0)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A cursed pile of bones, spawning spirits.")
    mytp.set_tick_rate_tenths(2)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="ghost_minion_generator", text_name="pile of bones")

init()

