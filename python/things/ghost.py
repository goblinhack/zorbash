import zx
import tp

def on_death(me, x, y):
    zx.level_spawn_at_thing(me, "ghost_explosion")

def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    mytp.set_ai_scent_distance(10)
    mytp.set_attack_humanoid(True)
    mytp.set_attack_living(False) # No, else it attacks spiders
    mytp.set_attack_lunge(True)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_bite_dice("1")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_attack("attack_claws")
    mytp.set_gfx_glows(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_health_initial_dice("1")
    mytp.set_is_able_to_change_levels(True)
    mytp.set_is_able_to_fall(False)
    mytp.set_is_able_to_walk_through_walls(True)
    mytp.set_is_active(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_ethereal(True)
    mytp.set_is_fearless(True)
    mytp.set_is_floating(True)
    mytp.set_is_intelligent(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_undead(True)
    mytp.set_light_color("green")
    mytp.set_light_strength(1)
    mytp.set_long_text_description("A spirit of one less fortunate than you. Beware, ghosts can traverse chasms that you cannot.")
    mytp.set_loves_poison(True)
    mytp.set_monst_size(zx.MONST_SIZE_NORMAL)
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("ghost.on_death()")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(20)
    mytp.set_stat_defence(12)
    mytp.set_stat_strength(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("The angry spirit of one long passed.")
    mytp.set_text_hits("slashes")
    mytp.set_tick_rate_tenths(3)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    delay = 200
    mytp.set_tile("ghost.1", delay_ms=delay)
    mytp.set_tile("ghost.2", delay_ms=delay)
    mytp.set_tile("ghost.3", delay_ms=delay)
    mytp.set_tile("ghost.4", delay_ms=delay)
    mytp.set_tile("ghost.5", delay_ms=delay)
    mytp.set_tile("ghost.6", delay_ms=delay)
    mytp.set_tile("ghost.7", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.8", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.9", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.10", delay_ms=delay, is_invisible=True)
    mytp.set_tile("ghost.11", delay_ms=delay, is_invisible=True)

    mytp.update()

def init():
    tp_init(name="ghost", text_name="ghost")

init()

