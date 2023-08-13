import my
import tp


def on_want_to_shoot_at(me, target, target_x, target_y):  # Return True on doing an action
    my.thing_shoot_at(me, "projectile_dart", target)
    for it in my.level_get_all(me, target_x, target_y):
        if my.thing_is_interesting(it):
            if it == me:
                continue
            dart = my.thing_new(me, "dart")
            my.thing_hit_dmg_missile(me, dart, it, thrown=True)
            my.thing_dead(dart, "used")

    return True


def tp_init(name, text_long_name):
    self = tp.Tp(name, text_long_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.attack_humanoid(self, True)
    my.chance_d1000_appearing(self, 100)
    my.chance_d1000_shooting(self, 300)
    my.collision_hit_priority(self, 20)
    my.distance_vision(self, 8)
    my.dmg_chance_d1000_crush(self, 0, 1000)
    my.dmg_crush_dice(self, "4d6")
    my.dmg_num_of_attacks(self, 0)  # fires only
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown_as_gray_in_shadow(self, True)
    my.gfx_ascii_shown_in_bg(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_oversized_and_on_floor(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d20")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_shoot_at(self, True)
    my.is_able_to_shoot_at_close_range(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_corpse_on_death(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_cursor_path_blocker(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_necrosis(self, True)
    my.is_immune_to_poison(self, True)
    my.is_immune_to_stamina_drain(self, True)
    my.is_interesting(self, True)  # so it can be shoved
    my.is_lifeless(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.is_loggable(self, True)
    my.is_obs_ai(self, True)
    my.is_obs_shoving(self, True)
    my.is_obs_spawn_monst(self, True)
    my.is_only_one_per_tile(self, True)
    my.is_sentry(self, True)
    my.is_shovable(self, True)
    my.is_stone(self, True)
    my.is_tickable(self, True)
    my.is_trap(self, True)
    my.is_very_combustible(self, True)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_want_to_shoot_at_do(self, "me.on_want_to_shoot_at()")
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "A menacing tower of stone with a roaming target-like eye atop it. It's either the entrance to a certain brand of shop, or something nasty. Which can it be...?")
    my.text_description_short(self, "A dart tower")
    my.thing_size(self, my.THING_SIZE_LARGE)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_MOB)
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="O", ascii_bg_col_name="blue", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="o", ascii_bg_col_name="blue", ascii_fg_col_name="red",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="O", ascii_bg_col_name="gray", ascii_fg_col_name="red",
            tile=name + ".dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    my.tp_update(self)


def init():
    tp_init(name="trap_dart", text_long_name="dart trap")


init()
