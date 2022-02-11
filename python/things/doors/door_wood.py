import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"door_hit{my.non_pcg_randint(1, 2)}")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_break")


def on_open(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_open")


def tp_init(name):
    mytp = tp.Tp(name, "wood door")
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 9)
    my.tp_set_damage_crush_chance_d1000(mytp, 1000)
    my.tp_set_damage_crush_dice(mytp, "2d6")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_environ_avoids_fire(mytp, 100)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_health_bar_autohide(mytp, True)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_health_initial_dice(mytp, "5d10")
    my.tp_set_is_always_hit(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_corpse_on_death(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_door(mytp, True)
    my.tp_set_is_gas_blocker(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_interesting(mytp, True)
    my.tp_set_is_light_blocker(mytp, True)
    my.tp_set_is_obs_wall_or_door(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # So it can interact with fire
    my.tp_set_noise_blocker(mytp, True)
    my.tp_set_noise_on_open(mytp, 60)
    my.tp_set_noise_on_you_are_hit_and_now_dead(mytp, 70)
    my.tp_set_noise_on_you_are_hit_but_still_alive(mytp, 60)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_death_is_open(mytp, True)
    my.tp_set_on_open_do(mytp, "me.on_open()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_stat_def(mytp, 20)
    my.tp_set_text_a_or_an(mytp, "the")
    my.tp_set_text_description(mytp, "A door covered in claw marks.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_NORMAL)

    my.tp_set_tile(mytp, tile=name + ".100", is_hp_100_percent=True)
    my.tp_set_tile(mytp, tile=name + ".75", is_hp_75_percent=True)
    my.tp_set_tile(mytp, tile=name + ".50", is_hp_50_percent=True)
    my.tp_set_tile(mytp, tile=name + ".25", is_hp_25_percent=True)
    my.tp_set_tile(mytp, tile=name + ".dead", is_dead=True)
    my.tp_set_tile(mytp, tile=name + ".open", is_hp_100_percent=True, is_open=True)
    my.tp_set_tile(mytp, tile=name + ".open", is_hp_75_percent=True, is_open=True)
    my.tp_set_tile(mytp, tile=name + ".open", is_hp_50_percent=True, is_open=True)
    my.tp_set_tile(mytp, tile=name + ".open", is_hp_25_percent=True, is_open=True)

    my.tp_update(mytp, )


def init():
    tp_init(name="door_wood")


init()
