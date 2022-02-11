import my
import tp


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "ghost_explosion")


def tp_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_aggression_level_pct(self, 100)
    my.tp_set_ai_wanderer(self, True)
    my.tp_set_attack_humanoid(self, True)
    my.tp_set_attack_lunge(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 10)
    my.tp_set_damage_cold_dice(self, "1")
    my.tp_set_distance_vision(self, 7)
    my.tp_set_gfx_animated_can_hflip(self, True)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_anim_use(self, "attack_claws")
    my.tp_set_gfx_glows(self, True)
    my.tp_set_gfx_health_bar_shown(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_health_initial_dice(self, "1")
    my.tp_set_is_able_to_see_in_the_dark(self, True)
    my.tp_set_is_able_to_walk_through_walls(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_biome_swamp(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_ethereal(self, True)
    my.tp_set_is_fearless(self, True)
    my.tp_set_is_floating(self, True)
    my.tp_set_is_green_blooded(self, True)  # not really
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_immune_to_acid(self, True)
    my.tp_set_is_immune_to_cold(self, True)
    my.tp_set_is_immune_to_fire(self, True)
    my.tp_set_is_immune_to_necrosis(self, True)
    my.tp_set_is_immune_to_poison(self, True)
    my.tp_set_is_immune_to_water(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_monst_class_a(self, True)
    my.tp_set_is_monst(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_is_tickable(self, True)
    my.tp_set_is_undead(self, True)
    my.tp_set_light_color(self, "green")
    my.tp_set_light_power(self, 1)
    my.tp_set_long_text_description(self, "A spirit of one less fortunate than you. Beware, ghosts can traverse chasms that you cannot.")
    my.tp_set_monst_size(self, my.MONST_SIZE_NORMAL)
    my.tp_set_noise_decibels_hearing(self, 0)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_rarity(self, my.RARITY_COMMON)
    my.tp_set_stat_con(self, 10)
    my.tp_set_stat_def(self, 11)
    my.tp_set_stat_dex(self, 13)
    my.tp_set_stat_luck(self, 10)
    my.tp_set_stat_str(self, 7)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "The angry spirit of one long passed.")
    my.tp_set_text_hits(self, "slashes")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    delay = 200
    my.tp_set_tile(self, "ghost.1", delay_ms=delay)
    my.tp_set_tile(self, "ghost.2", delay_ms=delay)
    my.tp_set_tile(self, "ghost.3", delay_ms=delay)
    my.tp_set_tile(self, "ghost.4", delay_ms=delay)
    my.tp_set_tile(self, "ghost.5", delay_ms=delay)
    my.tp_set_tile(self, "ghost.6", delay_ms=delay)
    my.tp_set_tile(self, "ghost.7", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(self, "ghost.8", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(self, "ghost.9", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(self, "ghost.10", delay_ms=delay, is_invisible=True)
    my.tp_set_tile(self, "ghost.11", delay_ms=delay, is_invisible=True)

    my.tp_update(self)


def init():
    tp_init(name="ghost", text_name="ghost")


init()
