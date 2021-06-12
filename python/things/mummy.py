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
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_scent_distance(20)
    mytp.set_attack_eater(True)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_living(False)
    mytp.set_attack_living(True)
    mytp.set_attack_lunge(True)
    mytp.set_attack_meat(True)
    mytp.set_attack_shove_chance_d1000(200)
    mytp.set_attack_shove(True)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_damage_doubled_from_water(True)
    mytp.set_damage_melee_dice("1d6")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_attack("attack_claws")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_hates_acid(True)
    mytp.set_hates_fire(100)
    mytp.set_hates_water(100)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("2d20")
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_burnable(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_fearless(True)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_intelligent(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_resurrectable(True)
    mytp.set_is_shovable(True)
    mytp.set_is_shown_on_leftbar(True)
    mytp.set_is_undead(True)
    mytp.set_long_text_description("Possibly the corpse of one who ventured into this dungeon before. All life is gone now, and what remains is a corpse wrapped in rags. Death is no release for this poor creature.")
    mytp.set_loves_poison(True)
    mytp.set_monst_size(zx.MONST_SIZE_NORMAL)
    mytp.set_move_speed_ms(150)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_bite_do("mummy.on_bite()")
    mytp.set_on_death_do("mummy.on_death()")
    mytp.set_on_hit_do("mummy.on_hit()")
    mytp.set_on_miss_do("mummy.on_miss()")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_resurrect_dice("1d10+30")
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(15)
    mytp.set_stat_defence(11)
    mytp.set_stat_strength(16)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A staggering corpse, covered in tissue paper.")
    mytp.set_text_hits("claws")
    mytp.set_tick_rate_tenths(3)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.100", is_hp_25_percent=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_dead=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5.dead", is_dead=True, is_end_of_anim=True)

    mytp.set_tile(tile=name + ".5.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.dead", is_resurrecting=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.dead", is_resurrecting=True, is_end_of_anim=True, is_alive_on_end_of_anim=True)

    mytp.update()

def init():
    tp_init(name="mummy", text_name="mummy")

init()

