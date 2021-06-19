import builtins
import zx
import tp

def on_idle(me, x, y):
    zx.level_spawn_at_thing(me, "acid1")

def on_death(me, x, y):
    zx.level_spawn_at_thing(me, "green_splatter")

def tp_init(name, text_name, short_text_name):
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_ai_scent_distance(5)
    mytp.set_attack_lunge(True)
    mytp.set_collision_attack_radius(0.60)
    mytp.set_collision_attack(True)
    mytp.set_collision_check(True)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(10)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_damage_melee_dice("1d5")
    mytp.set_gfx_animated_can_hflip(True)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_anim_attack("green_splatter")
    mytp.set_gfx_bounce_on_move(True)
    mytp.set_gfx_health_bar_shown(True)
    mytp.set_gfx_oversized_but_sitting_on_the_ground(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_hates_fire(100)
    mytp.set_health_hunger_pct(95)
    mytp.set_health_initial_dice("6d6")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_acid_lover(True)
    mytp.set_is_acid(True)
    mytp.set_is_active(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_combustible(True)
    mytp.set_is_critical_to_level(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_hunger_insatiable(True)
    mytp.set_is_item_eater(True)
    mytp.set_is_jelly_baby_eater(True)
    mytp.set_is_jelly_eater(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_meat_eater(True)
    mytp.set_is_monst(True)
    mytp.set_is_moveable(True)
    mytp.set_is_potion_eater(True)
    mytp.set_is_steal_item_chance_d1000(200)
    mytp.set_is_treasure_eater(True)
    mytp.set_light_color("green")
    mytp.set_light_strength(2)
    mytp.set_long_text_description("Dungeon cleaners have evolved to scrub their domain of all messy organic matter. That means you. Cleaners leave a trail of corrosive slime in their wake. Avoid this. Cleaners also have a habit of eating your hard fought items.")
    mytp.set_monst_size(zx.MONST_SIZE_LARGE)
    mytp.set_move_speed_ms(150)
    mytp.set_normal_placement_rules(True)
    mytp.set_nutrition_dice("1d4")
    mytp.set_on_death_do("cleaner.on_death()")
    mytp.set_on_death_drop_all_items(True)
    mytp.set_on_idle_dice("1d0:cleaner.on_idle()")
    mytp.set_rarity(zx.RARITY_COMMON)
    mytp.set_stamina(100)
    mytp.set_stat_attack(10) # 10, means no bonus
    mytp.set_stat_constitution(20)
    mytp.set_stat_defence(14)
    mytp.set_stat_strength(14)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A dungeon auto cleaner jelly thingy.")
    mytp.set_text_hits("burns")
    mytp.set_tick_rate_tenths(3)
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay = 200
    mytp.set_tile(tile=name + ".1.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.100", is_hp_100_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.75", is_hp_75_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".2.50", is_hp_50_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)
    mytp.set_tile(tile=name + ".1.25", is_hp_25_percent=True, delay_ms=delay)

    mytp.update()

def init():
    tp_init(name="cleaner", text_name="dungeon cleaner", short_text_name="cleaner")

init()
