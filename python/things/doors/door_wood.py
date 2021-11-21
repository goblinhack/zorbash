import my
import tp


def on_you_are_hit(me, hitter, real_hitter, x, y, crit, bite, poison, damage):
    my.sound_play("door_hit{}".format(my.non_pcg_randint(1, 2)))

def on_death(me, x, y):
    my.sound_play("door_break")

def on_open(me, x, y):
    my.sound_play("door_open")

def tp_init(name):
    mytp = tp.Tp(name, "wooden door")
    mytp.set_collision_check(True)
    mytp.set_collision_hit_priority(9)
    mytp.set_damage_value_doubled_from_fire(True)
    mytp.set_environ_dislikes_fire(100)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_health_bar_autohide(True)
    mytp.set_gfx_oversized_and_on_floor(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_health_initial_dice("10d10")
    mytp.set_is_always_hit(True)
    mytp.set_is_attackable_by_monst(True)
    mytp.set_is_attackable_by_player(True)
    mytp.set_is_burnable(True)
    mytp.set_is_corpse_on_death(True)
    mytp.set_is_cursor_can_hover_over(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_door(True)
    mytp.set_is_hittable(True)
    mytp.set_is_interesting(True)
    mytp.set_is_light_blocker(True)
    mytp.set_is_obs_wall_or_door(True)
    mytp.set_is_tickable(True) # So it can interact with fire
    mytp.set_normal_placement_rules(True)
    mytp.set_on_death_do("door_wood.on_death()")
    mytp.set_on_death_is_open(True)
    mytp.set_on_open_do("door_wood.on_open()")
    mytp.set_on_you_are_hit_do("door_wood.on_you_are_hit()")
    mytp.set_stat_armor_class(20)
    mytp.set_stat_attack_bonus(10) # 10, means no bonus
    mytp.set_text_a_or_an("the")
    mytp.set_text_description("A door covered in claw marks.")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_NORMAL)

    mytp.set_tile(tile=name + ".100", is_hp_100_percent=True)
    mytp.set_tile(tile=name + ".75", is_hp_75_percent=True)
    mytp.set_tile(tile=name + ".50", is_hp_50_percent=True)
    mytp.set_tile(tile=name + ".25", is_hp_25_percent=True)
    mytp.set_tile(tile=name + ".dead", is_dead=True)
    mytp.set_tile(tile=name + ".open", is_hp_100_percent=True, is_open=True)
    mytp.set_tile(tile=name + ".open", is_hp_75_percent=True, is_open=True)
    mytp.set_tile(tile=name + ".open", is_hp_50_percent=True, is_open=True)
    mytp.set_tile(tile=name + ".open", is_hp_25_percent=True, is_open=True)

    mytp.update()

def init():
    tp_init(name="door1")

init()
