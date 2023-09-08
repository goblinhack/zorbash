import my
import tp


def on_born(me, x, y):
    for it in my.level_get_all(me, x, y):
        if my.thing_is_portal(it):
            my.spawn_at_my_position(it, "explosion_major")


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.collision_check(self, True)
    my.collision_hit_priority(self, 100)
    my.dmg_chance_d1000_cold(self, 0, 1000)
    my.dmg_cold_dice(self, "1")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_shown_in_bg(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.health_initial_dice(self, "1d200")
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_gas_blocker(self, True)
    my.is_gas_explosion_blocker(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_stamina_drain(self, True)
    my.is_interesting(self, True)  # so it can be shoved
    my.is_loggable(self, True)
    my.is_obs_ai(self, True)
    my.is_obs_jump_end(self, True)
    my.is_obs_jumping(self, True)
    my.is_obs_shooting(self, True)
    my.is_obs_shoving(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_obs_spawn(self, True)
    my.is_obs_spell_casting(self, True)
    my.is_obs_throwing(self, True)
    my.is_obs_wall_or_door(self, True)
    my.is_only_one_per_tile(self, True)  # so wands of ice do not pile these up
    my.is_shootable(self, True)
    my.is_spell_of_holding_barrier(self, True)
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
    my.text_description_short(self, "An impenetrable shimmering field of energy.")
    my.text_hits(self, "chills")
    my.thing_size(self, my.THING_SIZE_GIANT)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_EFFECT)
    # end sort marker

    delay = 50

    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=255,
            delay_ms=delay, tile="spell_of_holding_barrier.1")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=200,
            delay_ms=delay, tile="spell_of_holding_barrier.2")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=200,
            delay_ms=delay, tile="spell_of_holding_barrier.3")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=150,
            delay_ms=delay, tile="spell_of_holding_barrier.4")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=150,
            delay_ms=delay, tile="spell_of_holding_barrier.1")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=100,
            delay_ms=delay, tile="spell_of_holding_barrier.2")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=100,
            delay_ms=delay, tile="spell_of_holding_barrier.3")
    my.tile(self, ascii_bg_char="block", ascii_bg_col_name="cyan", ascii_bg_alpha=50,
            delay_ms=delay, tile="spell_of_holding_barrier.4")

    my.tp_update(self)


def init():
    tp_init(name="spell_of_holding_barrier", text_long_name="spell hold barrier")


init()
