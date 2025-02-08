import my
import tp


def on_death(me, x, y):
    my.spawn_gas_healing_around_thing(me, 1)


def tp_init(name, tiles=[]):
    self = tp.Tp(name, "divine fungus", "divine fungus")
    # begin sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 3)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow_long(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_shadow_solid(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.health_initial_dice(self, "1")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_flooded(self, True)
    my.is_biome_swamp(self, True)
    my.is_combustible(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, False)
    my.is_described_when_hovering_over(self, True)
    my.is_fungus_healing(self, True)
    my.is_fungus(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover
    my.is_one_per_tile(self, True)
    my.is_organic(self, True)
    my.is_shootable(self, True)
    my.light_color(self, "pink")
    my.light_dist(self, 1)
    my.on_death_do(self, "me.on_death()")
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature_sensitive(self, True)
    my.temperature_sensitive_to_sudden_changes(self, True)
    my.text_a_or_an(self, "the")
    my.text_description_long(self, "This beautiful glowing fungus is well known for its healing properties and will release a gas of helpful spores upon its death.")
    my.text_description_short(self, "A divine fungus.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    for t in tiles:
        my.tile(self,
                ascii_fg_char="\"", ascii_bg_col_name="", ascii_fg_col_name="pink",
                tile=t)

    my.tp_update(self)


def init():
    tp_init(name="fungus_healing", tiles=["fungus_healing"])


init()
