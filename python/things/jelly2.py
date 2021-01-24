import builtins
import zx
import tp

def on_death(me, x, y):
    zx.tp_spawn_under(me, "pink_splatter")
    zx.tp_spawn_next_to(me, "jelly1")
    zx.tp_spawn_next_to(me, "jelly1")
    zx.tp_spawn_next_to(me, "jelly1")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_delay_after_moving_ms(1000)
    x.set_ai_scent_distance(5)
    x.set_attack_eater(True)
    x.set_attack_lunge(True)
    x.set_attackable_by_monst(True)
    x.set_attackable_by_player(True)
    x.set_avoids_fire(100)
    x.set_collision_attack(True)
    x.set_collision_attack_radius(0.60)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_melee_dice("1d5")
    x.set_gfx_anim_attack("pink_splatter")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_moves_ahead_shown(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("10")
    x.set_is_able_to_fall(True)
    x.set_is_acid(True)
    x.set_is_active(True)
    x.set_is_combustible(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_interesting(True)
    x.set_is_jelly(True)
    x.set_is_jelly_baby_eater(True)
    x.set_is_jelly_eater(True)
    x.set_is_jelly_parent(True)
    x.set_is_jumper(True)
    x.set_is_jumper_chance_d1000(2)
    x.set_is_jumper_distance(10)
    x.set_is_jumper_on_low_hp_chance_d1000(500)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_attackable(True)
    x.set_is_movable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_long_text_description("Jelly jumpers are numerous, bouncy and carnivorous. They will eat almost anything, including their own. They have the annoying habit of jumping when attacked and multiplying when attacked. This is an adult. It will eat its own children!")
    x.set_modifier_attack(10)
    x.set_modifier_constitution(14)
    x.set_modifier_defence(8)
    x.set_modifier_strength(15)
    x.set_monst_size(zx.MONST_SIZE_LARGE)
    x.set_move_speed_ms(1000)
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d4")
    x.set_on_death_do("jelly2.on_death()")
    x.set_rarity(zx.RARITY_COMMON)
    x.set_stamina(100)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=limegreen$A gargantuan pile of sentient jelly")
    x.set_text_hits("splats");
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.75", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.50", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".6.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".7.25", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".8.25", is_hp_25_percent=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="jelly2", text_name="jelly jumper")

init()
