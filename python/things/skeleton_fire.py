import zx
import tp

def on_fire_at(me, target, x, y): # Return True on doing an action
    if random.randint(1, 10) < 5:
        zx.thing_fire_at(me, "projectile_fire", target)
        return True
    return False

def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_ai_scent_distance(10)
    x.set_attack_eater(True)
    x.set_attack_lunge(True)
    x.set_attack_meat(True)
    x.set_attack_shove(True)
    x.set_attack_shove_chance_d1000(200)
    x.set_avoids_acid(True)
    x.set_avoids_water(100)
    x.set_collision_attack(True)
    x.set_collision_check(True)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(10)
    x.set_collision_radius(0.40)
    x.set_damage_bite_dice("1d4")
    x.set_damage_doubled_from_water(True)
    x.set_damage_melee_dice("1d6")
    x.set_gfx_anim_attack("attack_claws")
    x.set_gfx_animated(True)
    x.set_gfx_animated_can_hflip(True)
    x.set_gfx_bounce_on_move(True)
    x.set_gfx_glows(True)
    x.set_gfx_health_bar_shown(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_health_hunger_pct(95)
    x.set_health_initial_dice("2")
    x.set_is_able_to_change_levels(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True)
    x.set_is_attackable_by_monst(True)
    x.set_is_attackable_by_player(True)
    x.set_is_carrier_of_treasure_class_a(True)
    x.set_is_combustible(True)
    x.set_is_corpse_on_death(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_fearless(True)
    x.set_is_hunger_insatiable(True)
    x.set_is_intelligent(True)
    x.set_is_interesting(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_monst(True)
    x.set_is_moveable(True)
    x.set_is_resurrectable(True)
    x.set_is_shovable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_undead(True)
    x.set_is_weapon_wielder(True)
    x.set_light_color("yellow")
    x.set_light_strength(2)
    x.set_long_text_description("A collection of tortured burning bones, driven to wander the dungeon forever. Or at least until you release them. Such creatures abhor the cleansing powers of water.")
    x.set_monst_size(zx.MONST_SIZE_NORMAL)
    x.set_move_speed_ms(150)
    x.set_normal_placement_rules(True)
    x.set_on_fire_at_do("skelton_fire.on_fire_at()")
    x.set_rarity(zx.RARITY_COMMON)
    x.set_resurrect_dice("1d10+30")
    x.set_stat_attack(10) # 10, means no bonus
    x.set_stat_constitution(9)
    x.set_stat_defence(9)
    x.set_stat_strength(9)
    x.set_text_a_or_an("a");
    x.set_text_description("The burning bones of one surprised to be moving again and literally on fire.")
    x.set_text_hits("claws");
    x.set_tick_rate_tenths(3)
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    x.set_tile("skeleton_fire.1", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_left=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_left=True, is_moving=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_up=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_up=True, is_moving=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_down=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_down=True, is_moving=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_right=True, is_moving=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_right=True, is_moving=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_left=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_left=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_left=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_left=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_up=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_up=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_up=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_up=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_down=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_down=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_down=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_down=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_right=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_right=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_right=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_right=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1", is_dir_none=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2", is_dir_none=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3", is_dir_none=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4", is_dir_none=True, delay_ms=delay)

    x.set_tile("skeleton_fire.1.dead", is_dead=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2.dead", is_dead=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3.dead", is_dead=True, delay_ms=delay)
    x.set_tile("skeleton_fire.4.dead", is_dead=True, delay_ms=delay, is_end_of_anim=True)

    x.set_tile("skeleton_fire.4.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile("skeleton_fire.3.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile("skeleton_fire.2.dead", is_resurrecting=True, delay_ms=delay)
    x.set_tile("skeleton_fire.1.dead", is_resurrecting=True, is_end_of_anim=True, is_alive_on_end_of_anim=True)

    x.update()

def init():
    tp_init(name="skeleton_fire", text_name="firey skeleton")

init()
