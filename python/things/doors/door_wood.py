import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"door_hit{my.non_pcg_randint(1, 2)}")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_break")


def on_open(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_open")


def tp_init(name):
    self = tp.Tp(name, "wood door")
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 9)
    my.tp_set_damage_crush_chance_d1000(self, 1000)
    my.tp_set_damage_crush_dice(self, "2d6")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_environ_avoids_fire(self, 100)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_health_bar_autohide(self, True)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_health_initial_dice(self, "5d10")
    my.tp_set_is_always_hit(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_corpse_on_death(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_door(self, True)
    my.tp_set_is_gas_blocker(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_light_blocker(self, True)
    my.tp_set_is_obs_wall_or_door(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with fire
    my.tp_set_noise_blocker(self, True)
    my.tp_set_noise_on_open(self, 60)
    my.tp_set_noise_on_you_are_hit_and_now_dead(self, 70)
    my.tp_set_noise_on_you_are_hit_but_still_alive(self, 60)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_death_is_open(self, True)
    my.tp_set_on_open_do(self, "me.on_open()")
    my.tp_set_on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_stat_def(self, 20)
    my.tp_set_text_a_or_an(self, "the")
    my.tp_set_text_description(self, "A door covered in claw marks.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_NORMAL)

    my.tp_set_tile(self, tile=name + ".100", is_hp_100_percent=True)
    my.tp_set_tile(self, tile=name + ".75", is_hp_75_percent=True)
    my.tp_set_tile(self, tile=name + ".50", is_hp_50_percent=True)
    my.tp_set_tile(self, tile=name + ".25", is_hp_25_percent=True)
    my.tp_set_tile(self, tile=name + ".dead", is_dead=True)
    my.tp_set_tile(self, tile=name + ".open", is_hp_100_percent=True, is_open=True)
    my.tp_set_tile(self, tile=name + ".open", is_hp_75_percent=True, is_open=True)
    my.tp_set_tile(self, tile=name + ".open", is_hp_50_percent=True, is_open=True)
    my.tp_set_tile(self, tile=name + ".open", is_hp_25_percent=True, is_open=True)

    my.tp_update(self)


def init():
    tp_init(name="door_wood")


init()
