import my
import tp
import random


# hitter: arrow / monst
# real_hitter: who fired the arrow
def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    if damage <= 5:
        my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"player_hit{my.non_pcg_randint(1, 4)}")
    else:
        my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "player_hit5")


def on_you_natural_attack(me, x, y):
    my.sound_play("player_punch")


def on_born(me, x, y):
    pass


def on_death(me, x, y):
    messages = [
        "A grave is a place where the dead are laid to await the coming of the medical student - Ambrose Bierce.",
        "All tragedies are finished by a death, all comedies by a marriage - Lord Byron.",
        "Always go to other people's funerals, otherwise they won't come to yours - Yogi Berra.",
        "At my age flowers scare me - George Burns.",
        "I get my daily paper, look at the obituaries page and if I'm not there I carry on as usual - Mark Twain.",
        "Death is a delightful hiding place for weary men - Herodotus.",
        "Death is a very narrow theme, but it reaches a wide audience - Socrates.",
        "Death is just nature's way of telling you to slow down - Dick Sharples.",
        "Death was nature's way of telling you to slow down - Terry Pratchett.",
        "Don't send me flowers when I'm dead. If you like me, send them while I'm alive - Brian Clough.",
        "Dying is a very dull, dreary affair, and my advice to you is to have nothing to do with it - Somerset Maugham.",
        "Dying is easy; it's living that scares me to death - Annie Lennox.",
        "Either he's dead or my watch has stopped - Groucho Marx.",
        "Fear of death increases in exact proportion to increase in wealth - Ernest Hemingway.",
        "For three days after death, hair and nails continue to grow but phone calls taper off - Johnny Carson.",
        "He is one of those people who would be enormously improved by death - HH Munro.",
        "He was a great patriot, a humanitarian, a loyal friend, provided of course, he really is dead - Voltaire.",
        "I am prepared to meet my maker. Whether my maker is prepared to meet me is another matter - Winston Churchill.",
        "I can't afford to die; I'd lose too much money - George Burns.",
        "I do not fear death. I had been dead for billions of years before I was born and had not suffered the slightest inconvenience - Mark Twain.",
        "I don't mind dying, the trouble is you feel so stiff the next day - George Axlerod.",
        "I don't want to achieve immortality through my work, I want to achieve it through not dying - Woody Allen.",
        "If you die in an elevator, be sure to push the UP button - Sam Levenson.",
        "I have never killed a man, but I have read many obituaries with great pleasure - Clarence Darrow.",
        "I intend to live forever or die trying - Groucho Marx.",
        "I like sleeping; it's like death without the commitment - Unknown.",
        "I'm always relieved when someone is delivering a eulogy and I realize that I'm listening to it - George Carlin.",
        "Immortality... a fate worse than death - Edgar A Shoaff.",
        "I'm not afraid to die, I just don't want to be there when it happens - Woody Allen.",
        "I'm very pleased to be here. At my age I'm very pleased to be anywhere - George Burns.",
        "In this world, nothing can be certain, except death and taxes - Benjamin Franklin.",
        "It's funny how most people love the dead, once you're dead your made for life - Jimi Hendrix.",
        "I've looked that old scoundrel death in the eyes many times but this time I think he has me on the ropes - Douglas MacArthur.",
        "Life is hard. Then you die. Then they throw dirt in your face. Then the worms eat you. Be grateful if it happens in that order - David Gerrold.",
        "Millions long for immortality who don't know what to do with themselves on a rainy Sunday afternoon - Susan Ertz.",
        "My luck is so bad that if I bought a cemetery, people would stop dying - Ed Furgol.",
        "On the plus side, death is one of the few things that can be done as easily lying down - Woody Allen.",
        "Self-decapitation is an extremely difficult, not to say dangerous, thing to attempt - WS Gilbert.",
        "Some men are alive simply because it is against the law to kill them - EW Howe.",
        "The reports of my death have been greatly exaggerated - Mark Twain.",
        "The trouble with quotes about death is that all of them are made by people who are still alive - Joshua Burns.",
        "When I came back to Dublin I was court-martialed in my absence and sentenced to death in my absence, so I said they could shoot me in my absence - Brendan Behan.",
        "When I die, I hope to go to heaven, whatever the hell that is - Ayn Rand.",
        "When I die, I'm leaving my body to science fiction - Steven Wright.",
        "When I die, I want my body to be donated for research, but more specifically, to a scientist who is working on bringing dead bodies back to life - Nikhil Saluja.",
        "You know you're old when the candles cost more than the cake - Bob Hope.",
        #
        # Non quotes
        #
        "And I thought you were tough...",
        "Are you paid to play this?",
        "Are you paid to play this? You shouldn't be.",
        "Awful. Just awful.",
        "Believe in yourself more. Someone has to.",
        "Congratulations, you are dead!",
        "Congratulations, you died!",
        "Dead, what? When?",
        "Don't give up. But please give up on this game.",
        "Don't play games as a career.",
        "Epic fail.",
        "Goodbye cruel world.",
        "Good try I suppose.",
        "Hmm you seem to be dead.",
        "I had such high hopes for you.",
        "I hate to inquire, but are you dead?",
        "I have a goat plays better than you.",
        "In this dungeon the only certainty is death...",
        "Is that the best you could do?",
        "Is this your first game. Ever?",
        "Just give me a minute to recover my breath...",
        "Just stop playing. You'll never win.",
        "Let your pet pigeon play next time instead.",
        "Life was hard. Take it easy now...",
        "LOL.",
        "My pet kakapo plays better than that.",
        "My pet pigeon ccould do better.",
        "Not sure how that happened. It was going so well...",
        "Sinner, you are expired.",
        "Stick to knitting.",
        "Stick to sudoko.",
        "That could have gone a lot worse...",
        "The Gods are disappointed in you...",
        "This isn't pong you know?",
        "Time to rest in the fjords with your parrot!",
        "Try 3D Monster maze instead.",
        "Try firing next time.",
        "Try tetris instead?",
        "Was a noble pursuit.",
        "Welcome to the afterlife!",
        "Well, that could have been worse.",
        "Worst game ever.",
        "You are as lifeless as a Norweigian blue.",
        "You are at rest, sort of.",
        "You are in a better place.",
        "You are off to the happy hunting ground.",
        "You are profoundly and very dead.",
        "You are pushing up ze daisies now.",
        "You are six feet under.",
        "You bade farewell to life.",
        "You bit the dust.",
        "You bought the farm.",
        "You came to a sticky and pointless end.",
        "You checked out.",
        "You croaked it.",
        "You crossed the great divide.",
        "You died horribly.",
        "You disssapoint me.",
        "You fell off the perch.",
        "You find yourself sadly departed.",
        "You fought bravely...",
        "You gave up the ghost.",
        "You had your final summons.",
        "You have gone to a better place.",
        "You hear the sound of monsters laughing...",
        "You joined the choir invisible.",
        "You kicked the bucket.",
        "You left the mortal coil.",
        "You number was up.",
        "You paid the piper.",
        "You passed on.",
        "You popped your clogs.",
        "You reached your final destination.",
        "Your god told you to slow down.",
        "You seem to be suddenly expired.",
        "You slipped away.",
        "You snuffed it.",
        "You tried. Well done. I really mean it. Maybe.",
        "You wave farewell to the monsters.",
        "You went to meet your maker. It was not impressed.",
        "You went to the spirit in the sky.",
        "You went to the restaurant at the end of the universe.",
    ]
    my.topcon(f"{random.choice(messages)}")


# Don't repeat footsteps and wait for the current channel to finish so sounds do not overlap
last_footstep = 0


def on_move(me, x, y):
    global last_footstep

    if my.level_is_water_at(me, x, y):
        footstep = my.non_pcg_randint(1, 6)
        while footstep == last_footstep:
            footstep = my.non_pcg_randint(1, 6)

        if my.thing_sound_play_channel(me, my.CHANNEL_FOOTSTEPS, f"splash{footstep}"):
            last_footstep = footstep
    else:
        footstep = my.non_pcg_randint(1, 8)
        while footstep == last_footstep:
            footstep = my.non_pcg_randint(1, 8)

        if my.thing_sound_play_channel(me, my.CHANNEL_FOOTSTEPS, f"footsteps{footstep}"):
            last_footstep = footstep


def on_damage_melee(me, hitter, x, y, damage):
    return damage


def on_damage_poison(me, hitter, x, y, damage):
    return damage


def on_damage_future1(me, hitter, x, y, damage):
    return damage


def on_damage_future2(me, hitter, x, y, damage):
    return damage


def on_damage_future3(me, hitter, x, y, damage):
    return damage


def on_damage_cold(me, hitter, x, y, damage):
    return damage


def on_damage_fire(me, hitter, x, y, damage):
    return damage


def on_damage_crush(me, hitter, x, y, damage):
    return damage


def on_damage_lightning(me, hitter, x, y, damage):
    return damage


def on_damage_energy(me, hitter, x, y, damage):
    return damage


def on_damage_acid(me, hitter, x, y, damage):
    return damage


def on_damage_digest(me, hitter, x, y, damage):
    return damage


def on_damage_natural_attack(me, hitter, x, y, damage):
    return damage


def on_damage_necrosis(me, hitter, x, y, damage):
    return damage


def on_damage_stat_str(me, hitter, x, y, damage):
    return damage


def on_damage_stat_con(me, hitter, x, y, damage):
    return damage


def tp_init(name, text_name, short_text_name, title):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_aggression_level_pct(75)
    mytp.set_ai_detect_secret_doors(True)
    mytp.set_ai_resent_count(20)
    mytp.set_ai_shove_chance_d1000(50)
    mytp.set_ai_wanderer(True)
    mytp.set_attack_undead(True)
    mytp.set_capacity_height(20)
    mytp.set_capacity_width(20)
    mytp.set_collateral_damage_pct(90)
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(20)
    mytp.set_collision_hit_priority(6)
    mytp.set_damage_natural_attack_type("punch")
    mytp.set_damage_natural_dice("1d6+1")
    mytp.set_distance_avoid(3)
    mytp.set_distance_jump(2)
    mytp.set_distance_throw(5)
    mytp.set_distance_vision(10)
    mytp.set_environ_avoids_acid(100)
    mytp.set_environ_avoids_fire(10)
    mytp.set_environ_avoids_poison(100)
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_use("attack_punch")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_health_initial_dice("100")
    mytp.set_health_starving_pct(5)
    mytp.set_hunger_clock_tick_frequency(50)
    mytp.set_hunger_health_pct(5)
    mytp.set_is_able_to_attack_mobs(True)
    mytp.set_is_able_to_break_down_doors(True)
    mytp.set_is_able_to_break_out_of_webs(True)
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_collect_keys(True)
    mytp.set_is_able_to_enchant_items(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_able_to_jump(True)
    mytp.set_is_able_to_learn_skills(True)
    mytp.set_is_able_to_move_diagonally(True)
    mytp.set_is_able_to_open_doors(True)
    mytp.set_is_able_to_shove(True)
    mytp.set_is_able_to_use_amulet(True)
    mytp.set_is_able_to_use_armor(True)
    mytp.set_is_able_to_use_boots(True)
    mytp.set_is_able_to_use_cloak(True)
    mytp.set_is_able_to_use_gauntlet(True)
    mytp.set_is_able_to_use_helmet(True)
    mytp.set_is_able_to_use_rings(True)
    mytp.set_is_able_to_use_shield(True)
    mytp.set_is_able_to_use_wands(True)
    mytp.set_is_able_to_use_weapons(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_biome_dungeon(True)
    mytp.set_is_bleeder(True)
    mytp.set_is_bony(True)
    mytp.set_is_breather(True)
    mytp.set_is_burnable(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_exit_finder(True)
    mytp.set_is_explorer(True)
    mytp.set_is_humanoid(True)
    mytp.set_is_intelligent(True)
    mytp.set_is_item_collector(True)
    mytp.set_is_living(True)
    mytp.set_is_loggable(True)
    mytp.set_is_meat(True)
    mytp.set_is_moveable(True)
    mytp.set_is_player(True)
    mytp.set_is_red_blooded(True)
    mytp.set_is_shovable(True)
    mytp.set_is_tickable(True)
    mytp.set_light_power(10)
    mytp.set_long_text_description("Our most noble adventurer of no particular race or gender or creed. Devoid of fear and stout of heart. Likes kittens.")
    mytp.set_monst_size(my.MONST_SIZE_NORMAL)
    mytp.set_noise_decibels_hearing(30)
    mytp.set_noise_on_jumping(20)
    mytp.set_noise_on_moving_or_being_carried(20)
    mytp.set_on_born_do("player.on_born()")
    mytp.set_on_damage_acid_do("player.on_damage_acid()")
    mytp.set_on_damage_cold_do("player.on_damage_cold()")
    mytp.set_on_damage_crush_do("player.on_damage_crush()")
    mytp.set_on_damage_digest_do("player.on_damage_digest()")
    mytp.set_on_damage_energy_do("player.on_damage_energy()")
    mytp.set_on_damage_fire_do("player.on_damage_fire()")
    mytp.set_on_damage_future1_do("player.on_damage_future1()")
    mytp.set_on_damage_future2_do("player.on_damage_future2()")
    mytp.set_on_damage_future3_do("player.on_damage_future3()")
    mytp.set_on_damage_lightning_do("player.on_damage_lightning()")
    mytp.set_on_damage_melee_do("player.on_damage_melee()")
    mytp.set_on_damage_natural_attack_do("player.on_damage_natural_attack()")
    mytp.set_on_damage_necrosis_do("player.on_damage_necrosis()")
    mytp.set_on_damage_poison_do("player.on_damage_poison()")
    mytp.set_on_damage_stat_con_do("player.on_damage_stat_con()")
    mytp.set_on_damage_stat_str_do("player.on_damage_stat_str()")
    mytp.set_on_death_do("player.on_death()")
    mytp.set_on_move_do("player.on_move()")
    mytp.set_on_you_are_hit_but_still_alive_do("player.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_natural_attack_do("player.on_you_natural_attack()")
    mytp.set_stamina(100)
    mytp.set_stat_att_penalty_when_idle(0)
    mytp.set_stat_att_penalty_when_idle_max(0)
    mytp.set_stat_att_penalty_when_in_deep_water(5)
    mytp.set_stat_att_penalty_when_in_shallow_water(2)
    mytp.set_stat_att_penalty_when_stuck(5)
    mytp.set_stat_att_penalty_when_stuck_max(5)
    mytp.set_stat_con(10)
    mytp.set_stat_def(10)
    mytp.set_stat_def_penalty_when_idle(5)
    mytp.set_stat_def_penalty_when_idle_max(5)
    mytp.set_stat_def_penalty_when_in_deep_water(5)
    mytp.set_stat_def_penalty_when_in_shallow_water(2)
    mytp.set_stat_def_penalty_when_stuck(10)
    mytp.set_stat_def_penalty_when_stuck_max(15)
    mytp.set_stat_dex(10)
    mytp.set_stat_str(10)
    mytp.set_temperature_change_sensitive(True)
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("Our most noble adventurer. Press 'h' for help.")
    mytp.set_text_hits("hits")
    mytp.set_text_title(title)
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
    tp_init(
        name="player1",
        text_name="noble warrior",
        title="Ser Hackalot",
        short_text_name="you",
    )
    tp_init(
        name="player2",
        text_name="noble warrior",
        title="Ser Deadalot",
        short_text_name="you",
    )


init()
