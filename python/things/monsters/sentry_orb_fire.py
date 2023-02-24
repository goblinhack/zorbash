import my
import tp


def on_death(me, x, y):
    explode(me, x, y)


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_msg(me, "The sentry orb explodes!")
    my.spawn_at_my_position(me, "explosion_major")


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    if my.pcg_randint(1, 100) < 80:
        my.thing_shoot_at(me, "staff_fire_projectile", target)
        return True
    return False


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_humanoid(self, True)
    my.attacks_per_round(self, 0)  # fires only
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_vision(self, 8)
    my.dmg_received_doubled_from_cold(self, True)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1")
    my.is_able_to_be_surprised(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at_close_range(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_fire(self, True)
    my.is_interesting(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_msg_allowed_hears_something(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_senses_danger(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "orange")
    my.light_dist(self, 1)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 5)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.rarity(self, my.RARITY_RARE)  # how rare within this monster class
    my.stat_con(self, 10)
    my.stat_def(self, 10)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.temperature_max(self, 1000)
    my.temperature_min(self, 0)
    my.temperature(self, 200)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Note that sentry orbs are fragile and prone to explosive outbursts...")
    my.text_description_long(self, "Sentry orbs patrol the dungeon, raining down punishment on whomever should not be there. Essentially you... This one fires beams of fire.")
    my.text_description_short(self, "A sentry orb.")
    my.text_hits(self, "burns")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CONSUMER)  # so it appears over things when consuming
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="O", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="o", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="O", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name + ".3", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="sentry_orb_fire", text_long_name="sentry orb", text_short_name="sentry orb")


init()
