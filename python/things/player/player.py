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


def on_you_nat_att(me, x, y):
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


def on_receiving_dmg_melee(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_poison(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_future1(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_bite(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_claw(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_cold(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_fire(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_crush(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_lightning(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_energy(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_acid(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_digest(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_nat_att(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_necrosis(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_draining(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_stat_str(me, hitter, x, y, damage):
    return damage


def on_receiving_dmg_stat_con(me, hitter, x, y, damage):
    return damage


def on_attacking_dmg_melee(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_poison(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_future1(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_bite(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_claw(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_cold(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_fire(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_crush(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_lightning(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_energy(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_acid(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_digest(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_nat_att(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_necrosis(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_draining(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_stat_str(me, victim, x, y, damage):
    return damage


def on_attacking_dmg_stat_con(me, victim, x, y, damage):
    return damage


def tp_init(name, text_long_name, text_short_name, title):
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.aggression_pct(self, 25)
    my.ai_detect_secret_doors(self, True)
    my.ai_resent_count(self, 20)
    my.ai_shove_chance_d1000(self, 50)
    my.ai_wanderer(self, True)
    my.attack_lunge(self, True)
    my.attack_undead(self, True)
    my.capacity_height(self, 20)
    my.capacity_width(self, 20)
    my.collateral_damage_pct(self, 90)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.collision_hit_priority(self, 6)
    my.damage_nat_att_dice(self, "1d3")
    my.damage_nat_att_type(self, "punch")
    my.distance_avoid(self, 3)
    my.distance_throw(self, 5)
    my.distance_vision(self, 10)
    my.environ_avoids_acid(self, 100)
    my.environ_avoids_fire(self, 10)
    my.environ_avoids_poison(self, 100)
    my.gfx_anim_use(self, "attack_punch")
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated_can_hflip(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_flickers(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.health_initial_dice(self, "100")
    my.hunger_clock_tick_freq(self, 1)
    my.hunger_is_starving_at_pct(self, 10)
    my.hunger_is_hungry_at_pct(self, 50)
    my.is_able_to_attack_mobs(self, True)
    my.is_able_to_break_down_doors(self, True)
    my.is_able_to_break_out_of_ice(self, True)
    my.is_able_to_break_out_of_webs(self, True)
    my.is_able_to_burn(self, True)
    my.is_able_to_change_levels(self, True)
    my.is_able_to_collect_keys(self, True)
    my.is_able_to_enchant_items(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_jump(self, True)
    my.is_able_to_learn_skills(self, True)
    my.is_able_to_move_diagonally(self, True)
    my.is_able_to_open_doors(self, True)
    my.is_able_to_shove(self, True)
    my.is_able_to_use_amulet(self, True)
    my.is_able_to_use_armor(self, True)
    my.is_able_to_use_boots(self, True)
    my.is_able_to_use_cloak(self, True)
    my.is_able_to_use_gauntlet(self, True)
    my.is_able_to_use_helmet(self, True)
    my.is_able_to_use_rings(self, True)
    my.is_able_to_use_shield(self, True)
    my.is_able_to_use_wands_or_staffs(self, True)
    my.is_able_to_use_weapons(self, True)
    my.is_air_breathher(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_biome_dungeon(self, True)
    my.is_bleeder(self, True)
    my.is_corpse_on_death(self, True)
    my.is_corpse_with_bones(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_exit_finder(self, True)
    my.is_explorer(self, True)
    my.is_humanoid(self, True)
    my.is_intelligent(self, True)
    my.is_interesting(self, True)
    my.is_item_collector(self, True)
    my.is_living(self, True)
    my.is_loggable(self, True)
    my.is_meat(self, True)
    my.is_eater_of_food(self, True)
    my.is_moveable(self, True)
    my.is_player(self, True)
    my.is_red_blooded(self, True)
    my.is_shovable(self, True)
    my.is_temperature_change_sensitive(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.jump_distance(self, 2)
    my.light_dist(self, 10)
    my.move_speed(self, 100)
    my.noise_additional_on_jump_end(self, 20)
    my.noise_decibels_hearing(self, 30)
    my.noise_on_moving(self, 50)
    my.on_attacking_dmg_acid_do(self, "player.on_attacking_dmg_acid()")
    my.on_attacking_dmg_bite_do(self, "player.on_attacking_dmg_bite()")
    my.on_attacking_dmg_claw_do(self, "player.on_attacking_dmg_claw()")
    my.on_attacking_dmg_cold_do(self, "player.on_attacking_dmg_cold()")
    my.on_attacking_dmg_crush_do(self, "player.on_attacking_dmg_crush()")
    my.on_attacking_dmg_digest_do(self, "player.on_attacking_dmg_digest()")
    my.on_attacking_dmg_draining_do(self, "player.on_attacking_dmg_draining()")
    my.on_attacking_dmg_energy_do(self, "player.on_attacking_dmg_energy()")
    my.on_attacking_dmg_fire_do(self, "player.on_attacking_dmg_fire()")
    my.on_attacking_dmg_future1_do(self, "player.on_attacking_dmg_future1()")
    my.on_attacking_dmg_lightning_do(self, "player.on_attacking_dmg_lightning()")
    my.on_attacking_dmg_melee_do(self, "player.on_attacking_dmg_melee()")
    my.on_attacking_dmg_nat_att_do(self, "player.on_attacking_dmg_nat_att()")
    my.on_attacking_dmg_necrosis_do(self, "player.on_attacking_dmg_necrosis()")
    my.on_attacking_dmg_poison_do(self, "player.on_attacking_dmg_poison()")
    my.on_attacking_dmg_stat_con_do(self, "player.on_attacking_dmg_stat_con()")
    my.on_attacking_dmg_stat_str_do(self, "player.on_attacking_dmg_stat_str()")
    my.on_born_do(self, "player.on_born()")
    my.on_death_do(self, "player.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_move_do(self, "player.on_move()")
    my.on_receiving_dmg_acid_do(self, "player.on_receiving_dmg_acid()")
    my.on_receiving_dmg_bite_do(self, "player.on_receiving_dmg_bite()")
    my.on_receiving_dmg_claw_do(self, "player.on_receiving_dmg_claw()")
    my.on_receiving_dmg_cold_do(self, "player.on_receiving_dmg_cold()")
    my.on_receiving_dmg_crush_do(self, "player.on_receiving_dmg_crush()")
    my.on_receiving_dmg_digest_do(self, "player.on_receiving_dmg_digest()")
    my.on_receiving_dmg_draining_do(self, "player.on_receiving_dmg_draining()")
    my.on_receiving_dmg_energy_do(self, "player.on_receiving_dmg_energy()")
    my.on_receiving_dmg_fire_do(self, "player.on_receiving_dmg_fire()")
    my.on_receiving_dmg_future1_do(self, "player.on_receiving_dmg_future1()")
    my.on_receiving_dmg_lightning_do(self, "player.on_receiving_dmg_lightning()")
    my.on_receiving_dmg_melee_do(self, "player.on_receiving_dmg_melee()")
    my.on_receiving_dmg_nat_att_do(self, "player.on_receiving_dmg_nat_att()")
    my.on_receiving_dmg_necrosis_do(self, "player.on_receiving_dmg_necrosis()")
    my.on_receiving_dmg_poison_do(self, "player.on_receiving_dmg_poison()")
    my.on_receiving_dmg_stat_con_do(self, "player.on_receiving_dmg_stat_con()")
    my.on_receiving_dmg_stat_str_do(self, "player.on_receiving_dmg_stat_str()")
    my.on_you_are_hit_but_still_alive_do(self, "player.on_you_are_hit_but_still_alive()")
    my.on_you_nat_att_do(self, "player.on_you_nat_att()")
    my.stamina(self, 100)
    my.stat_att_penalty_when_idle_max(self, 0)
    my.stat_att_penalty_when_idle(self, 0)
    my.stat_att_penalty_when_in_deep_water(self, 5)
    my.stat_att_penalty_when_in_shallow_water(self, 2)
    my.stat_att_penalty_when_stuck_max(self, 2)
    my.stat_att_penalty_when_stuck(self, 1)
    my.stat_con(self, 10)
    my.stat_def_penalty_when_idle_max(self, 5)
    my.stat_def_penalty_when_idle(self, 5)
    my.stat_def_penalty_when_in_deep_water(self, 5)
    my.stat_def_penalty_when_in_shallow_water(self, 2)
    my.stat_def_penalty_when_stuck_max(self, 15)
    my.stat_def_penalty_when_stuck(self, 10)
    my.stat_def(self, 10)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.text_a_or_an(self, "the")
    my.text_hits(self, "hits")
    my.text_long_description2(self, "A most noble adventurer of no particular race, gender or creed. Devoid of fear and stout of heart.")
    my.text_long_description3(self, "Likes kittens.")
    my.text_long_description(self, "You.")
    my.text_short_description(self, "Our most noble adventurer. Press 'h' for help.")
    my.text_title(self, title)
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_HIGH)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_PLAYER)
    # end sort marker

    delay = 900
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_left=True, is_moving=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_left=True, is_moving=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_left=True, is_moving=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_left=True, is_moving=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_left=True, is_moving=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_left=True, is_moving=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_up=True, is_moving=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_up=True, is_moving=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_up=True, is_moving=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_up=True, is_moving=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_up=True, is_moving=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_up=True, is_moving=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_down=True, is_moving=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_down=True, is_moving=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_down=True, is_moving=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_down=True, is_moving=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_down=True, is_moving=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_down=True, is_moving=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_right=True, is_moving=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_right=True, is_moving=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_right=True, is_moving=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_right=True, is_moving=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_right=True, is_moving=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_right=True, is_moving=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_left=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_left=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_left=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_left=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_left=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_left=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_up=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_up=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_up=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_up=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_up=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_up=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_down=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_down=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_down=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_down=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_down=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_down=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_right=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_right=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_right=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_right=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_right=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_right=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".1", is_dir_none=True, delay_ms=delay, frame=1)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".2", is_dir_none=True, delay_ms=delay, frame=2)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".3", is_dir_none=True, delay_ms=delay, frame=3)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".4", is_dir_none=True, delay_ms=delay, frame=4)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".5", is_dir_none=True, delay_ms=delay, frame=5)
    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="pink", ascii_bg_col_name="",
            tile=name + ".6", is_dir_none=True, delay_ms=delay, frame=6)

    my.tile(self, ascii_fg_char="@", ascii_fg_col_name="grey", ascii_bg_col_name="",
            tile=name + ".dead", is_dead=True)

    my.tp_update(self)


def init():
    tp_init(
        name="player1",
        text_long_name="noble warrior",
        title="Ser Hackalot",
        text_short_name="you",
    )
    tp_init(
        name="player2",
        text_long_name="noble warrior",
        title="Ser Deadalot",
        text_short_name="you",
    )


init()
