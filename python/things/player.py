import my
import tp


# hitter: arrow / monst
# real_hitter: who fired the arrow
def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, damage):
    # my.topcon("player hit damage {}".format(damage))
    if damage <= 5:
        my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "player_hit{}".format(my.non_pcg_randint(1, 4)))
    else:
        my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "player_hit5")

def on_you_bite_attack(me, x, y):
    my.sound_play("player_punch")

def on_born(me, x, y):
    pass

# Don't repeat footsteps and wait for the current channel to finish so sounds do not overlap
last_footstep = 0
def on_move(me, x, y):
    global last_footstep

    if my.level_is_water_at(me, x, y):
        footstep = my.non_pcg_randint(1, 6)
        while footstep == last_footstep:
            footstep = my.non_pcg_randint(1, 6)

        if my.thing_sound_play_channel(me, my.CHANNEL_FOOTSTEPS, "splash{}".format(footstep)):
            last_footstep = footstep
    else:
        footstep = my.non_pcg_randint(1, 8)
        while footstep == last_footstep:
            footstep = my.non_pcg_randint(1, 8)

        if my.thing_sound_play_channel(me, my.CHANNEL_FOOTSTEPS, "footsteps{}".format(footstep)):
            last_footstep = footstep

def tp_init(name, text_name, short_text_name, title):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_ai_avoid_distance(4)
    mytp.set_ai_is_able_to_attack_generators(True)
    mytp.set_ai_is_able_to_break_down_doors(True)
    mytp.set_ai_is_able_to_break_out_of_webs(True)
    mytp.set_ai_is_able_to_collect_keys(True)
    mytp.set_ai_is_able_to_detect_secret_doors_when_close(True)
    mytp.set_ai_is_able_to_enchant_weapons(True)
    mytp.set_ai_is_able_to_jump_distance(2)
    mytp.set_ai_is_able_to_jump(True)
    mytp.set_ai_is_able_to_learn_skills(True)
    mytp.set_ai_is_able_to_open_doors(True)
    mytp.set_ai_is_able_to_shove(True)
    mytp.set_ai_is_exit_finder(True)
    mytp.set_ai_is_item_collector(True)
    mytp.set_ai_is_level_explorer(True)
    mytp.set_ai_resent_count(20)
    mytp.set_ai_scent_distance(10) # Used in enemy calculations
    mytp.set_ai_shove_chance_d1000(50)
    mytp.set_ai_unprovoked_attack_chance_d1000(100)
    mytp.set_ai_vision_distance(10)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_undead(True)
    mytp.set_capacity_height(20)
    mytp.set_capacity_width(20)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(20)
    mytp.set_damage_melee_dice("1d6+1")
    mytp.set_environ_dislikes_acid(True)
    mytp.set_environ_dislikes_fire(100)
    mytp.set_environ_dislikes_poison(True)
    mytp.set_environ_hates_poison(True)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_punch")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_hunger_pct(5)
    mytp.set_health_initial_dice("100")
    mytp.set_health_starving_pct(5)
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_bleeder(True)
    mytp.set_is_burnable(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_humanoid(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat(True)
    mytp.set_is_moveable(True)
    mytp.set_is_player(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_is_weapon_equiper(True)
    mytp.set_light_strength(8)
    mytp.set_long_text_description("Our most noble adventurer of no particular race or gender or creed. Devoid of fear and stout of heart. Likes kittens.")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_on_born_do("player.on_born()")
    mytp.set_on_move_do("player.on_move()")
    mytp.set_on_you_are_hit_do("player.on_you_are_hit()")
    mytp.set_on_you_bite_attack_do("player.on_you_bite_attack()")
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
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    delay = 900
    mytp.set_tile(tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_left=True, is_moving=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_left=True, is_moving=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_up=True, is_moving=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_up=True, is_moving=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_down=True, is_moving=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_down=True, is_moving=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_right=True, is_moving=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_right=True, is_moving=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_left=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_left=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_left=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_left=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_left=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_left=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_up=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_up=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_up=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_up=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_up=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_up=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_down=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_down=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_down=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_down=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_down=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_down=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_right=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_right=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_right=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_right=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_right=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_right=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=delay, frame=1)
    mytp.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=delay, frame=2)
    mytp.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=delay, frame=3)
    mytp.set_tile(tile=name + ".4", is_dir_none=True, delay_ms=delay, frame=4)
    mytp.set_tile(tile=name + ".5", is_dir_none=True, delay_ms=delay, frame=5)
    mytp.set_tile(tile=name + ".6", is_dir_none=True, delay_ms=delay, frame=6)

    mytp.set_tile(tile=name + ".dead", is_dead=True)

    mytp.update()

def init():
    tp_init(name="player1", text_name="noble warrior", title="Ser Hackalot", short_text_name="you")
    tp_init(name="player2", text_name="noble warrior", title="Ser Deadalot", short_text_name="you")

init()
