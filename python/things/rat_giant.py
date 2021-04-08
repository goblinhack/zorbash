import zx
import tp
import random

def on_claw_attack(me, x, y):
    sound = "growl{}".format(random.randint(1, 10))
    if not zx.sound_play_channel(zx.CHANNEL_MONST, sound):
        zx.sound_play_channel(zx.CHANNEL_MONST2, sound)

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    zx.sound_play("squeaky_toy")

def on_miss(me, hitter, x, y):
    sound = "hiss{}".format(random.randint(1, 10))
    if not zx.sound_play_channel(zx.CHANNEL_MONST, sound):
        zx.sound_play_channel(zx.CHANNEL_MONST2, sound)

def on_death(me, x, y):
    sound = "growl{}".format(random.randint(1, 10))
    if not zx.sound_play_channel(zx.CHANNEL_MONST, sound):
        zx.sound_play_channel(zx.CHANNEL_MONST2, sound)

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_scent_distance(10)
    x.set_attack_eater(True)
    x.set_attack_lunge(True)
    x.set_avoids_acid(True)
    x.set_avoids_fire(100)
    x.set_avoids_poison(True)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_doubled_from_poison(True)
    x.set_damage_melee_dice("1d4+2")
    x.set_gfx_anim_attack("attack_claws")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_oversized_but_sitting_on_the_ground(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("2d6")
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_burnable(True)
    x.set_is_combustible(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_food_eater(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_interesting(True)
    x.set_is_jumper(True)
    x.set_is_jumper_chance_d1000(50)
    x.set_is_jumper_distance(2)
    x.set_is_living(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat(True)
    x.set_is_meat_eater(True)
    x.set_is_monst(True)
    x.set_is_moveable(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_long_text_description("An enormous rat. Blood drips from its teeth. Will eat almost anything, especially you. Answers to the name of Mr Squeekles.")
    x.set_modifier_attack(7)
    x.set_modifier_constitution(11)
    x.set_modifier_defence(12)
    x.set_modifier_strength(7)
    x.set_monst_size(zx.MONST_SIZE_LARGE)
    x.set_move_speed_ms(50)
    x.set_normal_placement_rules(True)
    x.set_nutrition_dice("1d6")
    x.set_on_claw_attack_do("rat_giant.on_claw_attack()")
    x.set_on_death_do("rat_giant.on_death()")
    x.set_on_hit_do("rat_giant.on_hit()")
    x.set_on_miss_do("rat_giant.on_hit()")
    x.set_on_death_is_corpse(True)
    x.set_rarity(zx.RARITY_COMMON)
    x.set_stamina(100)
    x.set_text_a_or_an("the");
    x.set_text_description("%%fg=brown$A giant rat. Slightly cute. Likely rabid.")
    x.set_text_hits("gores");
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=150
    x.set_tile("rat_giant.1", delay_ms=delay)
    x.set_tile("rat_giant.2", delay_ms=delay)
    x.set_tile("rat_giant.dead", is_dead=True, delay_ms=delay)

    x.update()

def init():
    tp_init(name="rat_giant", text_name="giant rat")

init()

