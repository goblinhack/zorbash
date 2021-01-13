import zx
import tp

def spawn(me, x, y):
    zx.tp_spawn_under(me, "pink_splatter")


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_delay_after_moving_ms(1000)
    x.set_ai_scent_distance(10)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_gfx_anim_attack("claws1")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_moves_ahead_shown(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_acid_avoider(True)
    x.set_is_active(True)
    x.set_is_attack_eater(True)
    x.set_is_attack_lunge(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_combustible(True)
    x.set_is_double_damage_from_fire(True)
    x.set_is_double_damage_from_poison(True)
    x.set_is_fire_avoider(100)
    x.set_is_food_eater(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_interesting(True)
    x.set_is_jumper(True)
    x.set_is_jumper_chance_d1000(50)
    x.set_is_jumper_distance(2)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_movable(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_poison_avoider(True)
    x.set_long_text_description("An enormous rat. Blood drips from its teeth. Will eat almost anything, especially you. Answers to the name of Mr Squeekles.")
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d6")
    x.set_on_death_is_corpse(True)
    x.set_rarity(zx.RARITY_COMMON)
    x.set_damage_melee_dice("1d4+2")
    x.set_stats_defence(2)
    x.set_stats_health_hunger_pct(95)
    x.set_stats_health_initial_dice("2d6")
    x.set_stats_move_speed_ms(50)
    x.set_stats_stamina(100)
    x.set_stats_strength(20)
    x.set_text_a_or_an("the");
    x.set_text_description("%%fg=brown$A giant rat. Slightly cute. Likely rabid.")
    x.set_text_hits("gores");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=150
    x.set_tile("giant_rat.1", delay_ms=delay)
    x.set_tile("giant_rat.2", delay_ms=delay)
    x.set_tile("giant_rat.dead", is_dead=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="giant_rat", text_name="giant rat")

init()

