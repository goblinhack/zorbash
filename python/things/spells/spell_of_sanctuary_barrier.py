import my
import tp


def on_born(me, x, y):
    for it in my.level_get_all(me, x, y):
        if my.thing_is_portal(it):
            my.spawn_at_my_position(it, "explosion_major")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 100)
    my.dmg_chance_d1000_magic_drain(self, 0, 1000)
    my.dmg_chance_d1000_negation(self, 0, 1000)
    my.dmg_magic_drain_dice(self, "1")
    my.dmg_negation_dice(self, "1")
    my.dmg_num_of_attacks(self, 2)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_centered(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.health_initial_dice(self, "100+1d100")
    my.is_attackable_by_monst(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gas_blocker(self, True)
    my.is_gas_explosion_blocker(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_stamina_drain(self, True)
    my.is_interesting(self, True)  # so it can be shoved
    my.is_loggable(self, True)
    my.is_not_shown_as_a_pet(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_obs_spawn(self, True)
    my.is_one_per_tile(self, True)  # so wands of ice do not pile these up
    my.is_spell_of_sanctuary_barrier(self, True)
    my.is_tickable(self, True)
    my.lifespan_dice(self, "20+1d20")
    my.light_color(self, "white")
    my.light_dist(self, 3)
    my.noise_blocker(self, True)
    my.normal_placement_rules(self, True)
    my.on_born_do(self, "me.on_born()")
    my.temperature_never_changes(self, True)
    my.temperature(self, -10)
    my.text_a_or_an(self, "a")
    my.text_description_short(self, "A scrawled mark on the floor that repels all of evil intent. Hopefully that does not include you!")
    my.text_hits(self, "burns")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.z_depth(self, my.MAP_DEPTH_FLOOR2)
    my.z_prio(self, my.MAP_Z_PRIO_ALWAYS_BEHIND)
    # end sort marker

    delay = 250

    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=200,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.1")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=255,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.2")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=200,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.3")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=150,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.4")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=150,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.1")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=100,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.2")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=150,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.3")
    my.tile(self, ascii_fg_char="*", ascii_bg_char="block", ascii_bg_col_name="red", ascii_bg_alpha=150,
            delay_ms=delay, tile="spell_of_sanctuary_barrier.4")

    my.tp_update(self)


def init():
    tp_init(name="spell_of_sanctuary_barrier", text_long_name="magic barrier", text_short_name="magic barrier")


init()
