import zx
import tp
import random


# hitter: arrow / monst
# real_hitter: who fired the arrow
def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    # zx.topcon("player hit damage {}".format(damage))
    if damage <= 5:
        zx.sound_play_channel_at(zx.CHANNEL_IMPACT, "player_hit{}".format(random.randint(1, 4)), x, y)
    else:
        zx.sound_play_channel_at(zx.CHANNEL_IMPACT, "player_hit5", x, y)

def on_bite(me, x, y):
    zx.sound_play("player_punch")

def on_born(me, x, y):
    pass

# Don't repeat footsteps and wait for the current channel to finish so sounds do not overlap
last_footstep = 0
def on_move(me, x, y):
    global last_footstep
    footstep = random.randint(1, 8)
    while footstep == last_footstep:
        footstep = random.randint(1, 8)

    if zx.sound_play_channel_at(zx.CHANNEL_FOOTSTEPS, "footsteps{}".format(footstep), x, y):
        last_footstep = footstep

def tp_init(name, text_name, short_text_name, title):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_attack_shove(True)
    x.set_avoids_acid(True)
    x.set_avoids_fire(100)
    x.set_avoids_poison(True) # x.set_is_immune_to_poison(True) for some odd creature
    x.set_bag_height(12)
    x.set_bag_width(12)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(20)
    x.set_collision_radius(0.40)
    x.set_damage_melee_dice("1d6+1")
    x.set_gfx_anim_attack("attack_punch")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(5)
    x.set_health_initial_dice("20d10")
    x.set_health_starving_pct(5)
    x.set_is_able_to_change_levels(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_bleeder(True)
    x.set_is_combustible(True)
    x.set_is_corpse_on_death(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_humanoid(True)
    x.set_is_interesting(True)
    x.set_is_jumper(True)
    x.set_is_jumper_distance(2)
    x.set_is_living(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_meat(True)
    x.set_is_moveable(True)
    x.set_is_player(True)
    x.set_is_shovable(True)
    x.set_is_weapon_wielder(True)
    x.set_light_strength(8)
    x.set_long_text_description("Our most noble adventurer or no particular race or gender. Devoid of fear and stout of heart. Likes kittens.")
    x.set_monst_size(zx.MONST_SIZE_NORMAL)
    x.set_move_speed_ms(200)
    x.set_on_bite_do("player.on_bite()")
    x.set_on_born_do("player.on_born()")
    x.set_on_hit_do("player.on_hit()")
    x.set_on_move_do("player.on_move()")
    x.set_stamina(100)
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(10)
    x.set_stat_defence(10)
    x.set_stat_strength(10)
    x.set_text_a_or_an("the")
    x.set_text_description("Our most noble adventurer. Press 'h' for help.")
    x.set_text_hits("hits")
    x.set_text_title(title)
    x.set_throw_distance(5)
    x.set_tick_rate_tenths(1)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 900
    x.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_left=True, is_moving=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_up=True, is_moving=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_down=True, is_moving=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_right=True, is_moving=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_left=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_left=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_left=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_left=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_left=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_left=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_up=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_up=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_up=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_up=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_up=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_up=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_down=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_down=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_down=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_down=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_down=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_down=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_right=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_right=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_right=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_right=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_right=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_right=True, delay_ms=delay)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    x.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)

    x.set_tile(tile=name + ".dead", is_dead=True)

    x.update()

def init():
    tp_init(name="player1", text_name="noble warrior", title="Ser Hackalot", short_text_name="you")
    tp_init(name="player2", text_name="noble warrior", title="Ser Deadalot", short_text_name="you")

init()
