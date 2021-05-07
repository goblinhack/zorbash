import zx
import tp
import random

def on_bite(me, x, y):
    sound = "growl{}".format(random.randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    sound = "hiss{}".format(random.randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_miss(me, hitter, x, y):
    sound = "hiss{}".format(random.randint(1, 10))
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, sound):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, sound)

def on_death(me, x, y):
    if not zx.thing_sound_play_channel(me, zx.CHANNEL_MONST, "monst_death1"):
        zx.thing_sound_play_channel(me, zx.CHANNEL_MONST_DEATH, "monst_death1")

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_scent_distance(20)
    x.set_attack_eater(True)
    x.set_attack_lunge(True)
    x.set_attack_meat(True)
    x.set_attack_shove(True)
    x.set_attack_shove_chance_d1000(200)
    x.set_hates_acid(True)
    x.set_hates_fire(100)
    x.set_hates_water(100)
    x.set_loves_poison(True)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_damage_doubled_from_water(True)
    x.set_damage_melee_dice("1d6")
    x.set_gfx_anim_attack("attack_claws")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("2d20")
    x.set_is_able_to_change_levels(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_burnable(True)
    x.set_is_corpse_on_death(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_fearless(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_intelligent(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_monst(True)
    x.set_is_moveable(True)
    x.set_is_resurrectable(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_undead(True)
    x.set_attack_humanoid(True)
    x.set_attack_living(True)
    x.set_long_text_description("Possibly the corpse of one who ventured into this dungeon before. All life is gone now, and what remains is a corpse wrapped in rags. Death is no release for this poor creature.")
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(15)
    x.set_stat_defence(11)
    x.set_stat_strength(16)
    x.set_monst_size(zx.MONST_SIZE_NORMAL)
    x.set_move_speed_ms(150)
    x.set_normal_placement_rules(True)
    x.set_on_bite_do("mummy.on_bite()")
    x.set_on_death_do("mummy.on_death()")
    x.set_on_hit_do("mummy.on_hit()")
    x.set_on_miss_do("mummy.on_miss()")
    x.set_rarity(zx.RARITY_COMMON)
    x.set_resurrect_dice("1d10+30")
    x.set_text_a_or_an("a")
    x.set_text_description("A staggering corpse, covered in tissue paper.")
    x.set_text_hits("claws")
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)

    x.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    x.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    x.set_tile(tile=name + ".5.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile(tile=name + ".1.dead", is_resurrecting=True, is_end_of_anim=True, is_alive_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="mummy", text_name="mummy")

init()

