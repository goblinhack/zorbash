import my
import tp

def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, damage):
    if not my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch"):
        my.thing_sound_play_channel(me, my.CHANNEL_MONST_DEATH, "squelch")

def on_death(me, x, y):
    my.level_spawn_at_thing(me, "pink_splatter")
    if my.pcg_randint(1, 100) < 20:
        my.level_spawn_next_to(me, "jelly_baby")
    if my.pcg_randint(1, 100) < 20:
        my.level_spawn_next_to(me, "jelly_baby")
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "slime{}".format(my.non_pcg_randint(1, 9)))

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_aggression_level(20)
    mytp.set_ai_avoid_distance(2)
    mytp.set_ai_is_able_to_jump_distance(3)
    mytp.set_ai_is_able_to_jump_on_low_hp_chance_d1000(500)
    mytp.set_ai_is_able_to_jump(True)
    mytp.set_ai_random_jump_chance_d1000(100)
    mytp.set_ai_resent_count(3)
    mytp.set_ai_scent_distance(5)
    mytp.set_ai_unprovoked_attack_chance_d1000(1000)
    mytp.set_ai_vision_distance(3)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_blood(True)
    mytp.set_attack_eater(True)
    mytp.set_attack_lunge(True)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_damage_melee_dice("1")
    mytp.set_environ_damage_doubled_from_fire(True)
    mytp.set_environ_dislikes_fire(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("pink_splatter")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("1")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_see_in_the_dark(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_blood_eater(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hittable(True)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_jelly_baby_eater(True)
    mytp.set_is_jelly_baby(True)
    mytp.set_is_jelly_eater(True)
    mytp.set_is_jelly(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_soft_body(True)
    mytp.set_is_tickable(True)
    mytp.set_long_text_description("Jelly jumpers are numerous, bouncy and carnivorous. They will eat almost anything, including their own. They have the annoying habit of jumping when threatened. This one is a baby jelly. It tends to avoid adults of its kind. So should you.")
    mytp.set_monst_size(my.MONST_SIZE_TINY)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d4")
    mytp.set_on_death_do("jelly_baby.on_death()")
    mytp.set_on_you_are_hit_do("jelly_baby.on_you_are_hit()")
    mytp.set_rarity(my.RARITY_COMMON)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(10)
    mytp.set_stat_defence(5)
    mytp.set_stat_strength(5)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=limegreen$A small pile of semi sentient jelly.")
    mytp.set_text_hits("splats")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.100", is_hp_25_percent=True, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="jelly_baby", text_name="baby jelly")

init()

