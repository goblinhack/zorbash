import zx
import tp
import random


# hitter: arrow / monst
# real_hitter: who fired the arrow
def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    # zx.topcon("player hit damage {}".format(damage))
    if damage <= 5:
        zx.thing_sound_play_channel(me, zx.CHANNEL_IMPACT, "player_hit{}".format(random.randint(1, 4)))
    else:
        zx.thing_sound_play_channel(me, zx.CHANNEL_IMPACT, "player_hit5")

def on_bite(me, x, y):
    zx.sound_play("player_punch")

def on_born(me, x, y):
    pass

# Don't repeat footsteps and wait for the current channel to finish so sounds do not overlap
last_footstep = 0
def on_move(me, x, y):
    global last_footstep

    if zx.level_is_water_at(me, x, y):
        footstep = random.randint(1, 6)
        while footstep == last_footstep:
            footstep = random.randint(1, 6)

        if zx.thing_sound_play_channel(me, zx.CHANNEL_FOOTSTEPS, "splash{}".format(footstep)):
            last_footstep = footstep
    else:
        footstep = random.randint(1, 8)
        while footstep == last_footstep:
            footstep = random.randint(1, 8)

        if zx.thing_sound_play_channel(me, zx.CHANNEL_FOOTSTEPS, "footsteps{}".format(footstep)):
            last_footstep = footstep

def tp_init(name, text_name, short_text_name, title):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_ai_scent_distance(10) # Used in enemy calculations
    mytp.set_attack_shove(True)
    mytp.set_capacity_height(20)
    mytp.set_capacity_width(20)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(20)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_melee_dice("1d6+1")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_attack("attack_punch")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_hates_acid(True)
    mytp.set_hates_fire(100)
    mytp.set_hates_poison(True) # mytp.set_loves_poison(True) for some odd creature
    mytp.set_health_hunger_pct(5)
    mytp.set_health_initial_dice("100")
    mytp.set_health_starving_pct(5)
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_bleeder(True)
    mytp.set_is_burnable(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_humanoid(True)
    mytp.set_is_jumper_distance(2)
    mytp.set_is_jumper(True)
    mytp.set_is_key_collector(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_meat(True)
    mytp.set_is_moveable(True)
    mytp.set_is_player(True)
    mytp.set_is_shovable(True)
    mytp.set_is_treasure_collector(True)
    mytp.set_is_weapon_wielder(True)
    mytp.set_light_strength(8)
    mytp.set_long_text_description("Our most noble adventurer or no particular race or gender. Devoid of fear and stout of heart. Likes kittens.")
    mytp.set_monst_size(zx.MONST_SIZE_NORMAL)
    mytp.set_on_bite_do("player.on_bite()")
    mytp.set_on_born_do("player.on_born()")
    mytp.set_on_hit_do("player.on_hit()")
    mytp.set_on_move_do("player.on_move()")
    mytp.set_stamina(100)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(10)
    mytp.set_stat_defence(10)
    mytp.set_stat_strength(10)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Our most noble adventurer. Press 'h' for help.")
    mytp.set_text_hits("hits")
    mytp.set_text_title(title)
    mytp.set_throw_distance(5)
    mytp.set_tick_rate_tenths(1)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 900
    mytp.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_left=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_left=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_up=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_up=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_down=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_down=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_right=True, is_moving=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_right=True, is_moving=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_left=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_left=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_up=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_up=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_down=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_down=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_right=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_right=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay)

    mytp.set_tile(tile=name + ".dead", is_dead=True)

    mytp.update()

def init():
    tp_init(name="player1", text_name="noble warrior", title="Ser Hackalot", short_text_name="you")
    tp_init(name="player2", text_name="noble warrior", title="Ser Deadalot", short_text_name="you")

init()
