import my
import tp


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, f"door_hit{my.non_pcg_randint(1, 2)}")


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_break")


def on_open(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "door_open")


def tp_init(name):
    self = tp.Tp(name, "wooden door")
    # start sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 9)
    my.damage_crush_chance_d1000(self, 0, 1000)
    my.damage_crush_dice(self, "2d6")
    my.damage_received_doubled_from_fire(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_ascii_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_health_bar_autohide(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "5d10")
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_corpse_on_death(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_door(self, True)
    my.is_gas_blocker(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_jump_blocker(self, True)
    my.is_light_blocker(self, True)
    my.is_obs_wall_or_door(self, True)
    my.noise_blocker(self, True)
    my.noise_on_open(self, 60)
    my.noise_on_you_are_hit_and_now_dead(self, 70)
    my.noise_on_you_are_hit_but_still_alive(self, 60)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_death_is_open(self, True)
    my.on_open_do(self, "me.on_open()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.stat_def(self, 20)
    my.text_a_or_an(self, "the")
    my.text_short_description(self, "A door covered in claw marks.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="+", ascii_bg_col_name="brown", ascii_fg_col_name="black",
            tile=name + ".100", is_hp_100_percent=True)
    my.tile(self,
            ascii_fg_char="+", ascii_bg_col_name="brown2", ascii_fg_col_name="black",
            tile=name + ".75", is_hp_75_percent=True)
    my.tile(self,
            ascii_fg_char="+", ascii_bg_col_name="orange", ascii_fg_col_name="black",
            tile=name + ".50", is_hp_50_percent=True)
    my.tile(self,
            ascii_fg_char="+", ascii_bg_col_name="red", ascii_fg_col_name="black",
            tile=name + ".25", is_hp_25_percent=True)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="gray10", ascii_fg_col_name="black",
            tile=name + ".dead", is_dead=True)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="brown", ascii_fg_col_name="black",
            tile=name + ".open", is_hp_100_percent=True, is_open=True)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="brown", ascii_fg_col_name="black",
            tile=name + ".open", is_hp_75_percent=True, is_open=True)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="brown", ascii_fg_col_name="black",
            tile=name + ".open", is_hp_50_percent=True, is_open=True)
    my.tile(self,
            ascii_fg_char="-", ascii_bg_col_name="brown", ascii_fg_col_name="black",
            tile=name + ".open", is_hp_25_percent=True, is_open=True)

    my.tp_update(self)


def init():
    tp_init(name="door_wood")


init()
