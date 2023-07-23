import my
import tp


def on_death(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_IMPACT, "pressure_plate")
    # my.spawn_gas_poison_around_thing(me, 3)
    for it in my.level_flood_fill_get_all_grid_things(me, x, y, 3):
        my.spawn_gas_poison_around_thing(it, 1)


def on_activated(me, victim, x, y):
    if my.thing_is_player(victim):
        my.thing_msg(victim, "You hear a pressure plate click beneath you...")
        my.thing_msg(victim, "%%fg=red$Gas surrounds you!%%fg=reset$")
    else:
        my.thing_msg(victim, "The pressure plate clicks...")
    my.thing_dead(me, "activated")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.gfx_ascii_shown(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_pressure_plate(self, True)
    my.is_trap(self, True)
    my.noise_on_hit_and_now_dead(self, 50)
    my.noise_on_hit_and_still_alive(self, 50)
    my.normal_placement_rules(self, True)
    my.on_activated_do(self, "me.on_activated()")
    my.on_death_do(self, "me.on_death()")
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "A strange looking floor tile.")
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="middle_dot", ascii_fg_col_name="brown", tile="trap.1")
    my.tile(self,
            ascii_fg_char="middle_dot", ascii_fg_col_name="brown", tile="trap.2")
    my.tile(self,
            ascii_fg_char="middle_dot", ascii_fg_col_name="brown", tile="trap.3")

    my.tp_update(self)


def init():
    tp_init(name="trap_pressure_plate_gas", text_long_name="inconspicious floor tile")


init()
