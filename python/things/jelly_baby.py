import zx
import tp
import random

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    if not zx.sound_play_channel_at(zx.CHANNEL_MONST, "squelch", x, y):
        zx.sound_play_channel_at(zx.CHANNEL_MONST_DEATH, "squelch", x, y)

def on_death(me, x, y):
    zx.tp_spawn_at(me, "pink_splatter")
    zx.sound_play_channel_at(zx.CHANNEL_MONST, "slime{}".format(random.randint(1, 9)), x, y)

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_scent_distance(5)
    x.set_attack_eater(True)
    x.set_attack_lunge(True)
    x.set_avoids_fire(100)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_melee_dice("1")
    x.set_gfx_anim_attack("pink_splatter")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("1")
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_interesting(True)
    x.set_is_jelly(True)
    x.set_is_jelly_baby(True)
    x.set_is_jelly_baby_eater(True)
    x.set_is_jelly_eater(True)
    x.set_is_jumper(True)
    x.set_is_jumper_chance_d1000(100)
    x.set_is_jumper_distance(3)
    x.set_is_jumper_on_low_hp_chance_d1000(500)
    x.set_is_living(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_moveable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_long_text_description("Jelly jumpers are numerous, bouncy and carnivorous. They will eat almost anything, including their own. They have the annoying habit of jumping when threatened. This one is a baby jelly. It tends to avoid adults of its kind. So should you.")
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(10)
    x.set_stat_defence(5)
    x.set_stat_strength(5)
    x.set_monst_size(zx.MONST_SIZE_TINY)
    x.set_move_speed_ms(150)
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d4")
    x.set_on_death_do("jelly_baby.on_death()")
    x.set_on_hit_do("jelly_baby.on_hit()")
    x.set_rarity(zx.RARITY_COMMON)
    x.set_stamina(10)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=limegreen$A small pile of semi sentient jelly.")
    x.set_text_hits("splats");
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="jelly_baby", text_name="baby jelly")

init()

