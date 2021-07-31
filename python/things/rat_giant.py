import zx
import tp

def on_bite(me, x, y):
    sound = "growl{}".format(zx.non_pcq_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    sound = "hiss{}".format(zx.non_pcq_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_miss(me, hitter, x, y):
    sound = "hiss{}".format(zx.non_pcq_randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_death(me, x, y):
    zx.sound_play("squeaky_toy")

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_enemy_memory(10)
    mytp.set_ai_scent_distance(10)
    mytp.set_attack_eater(True)
    mytp.set_attack_lunge(True)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_bite_dice("1d6+2")
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_damage_doubled_from_poison(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_attack("attack_claws")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_oversized_but_sitting_on_the_ground(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_hates_acid(True)
    mytp.set_hates_fire(100)
    mytp.set_hates_poison(True)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("2d6")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_bleeder(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_food_eater(True)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_jumper_chance_d1000(50)
    mytp.set_is_jumper_distance(2)
    mytp.set_is_jumper(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_meat(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_shovable(True)
    mytp.set_long_text_description("An enormous rat. Blood drips from its teeth. Will eat almost anything, especially you. Answers to the name of Mr Squeekles.")
    mytp.set_monst_size(zx.MONST_SIZE_LARGE)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d6")
    mytp.set_on_bite_do("rat_giant.on_bite()")
    mytp.set_on_death_do("rat_giant.on_death()")
    mytp.set_on_hit_do("rat_giant.on_hit()")
    mytp.set_on_miss_do("rat_giant.on_miss()")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(11)
    mytp.set_stat_defence(12)
    mytp.set_stat_strength(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=brown$A giant rat. Slightly cute. Likely rabid.")
    mytp.set_text_hits("gores")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=150
    mytp.set_tile("rat_giant.1", delay_ms=delay)
    mytp.set_tile("rat_giant.2", delay_ms=delay)
    mytp.set_tile("rat_giant.dead", is_dead=True, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="rat_giant", text_name="giant rat")

init()

