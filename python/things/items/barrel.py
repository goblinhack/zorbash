import my
import tp


def explode(me, x, y):
    my.thing_dead(me, "exploded")
    my.thing_msg(me, "The oil filled barrel explodes. Health and safety have been alerted.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_at_thing(me, "fire")


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_death(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name):
    mytp = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(mytp, True)
    my.tp_set_collision_check(mytp, True)
    my.tp_set_collision_hit_priority(mytp, 1)
    my.tp_set_damage_crush_chance_d1000(mytp, 1000)
    my.tp_set_damage_crush_dice(mytp, "2d6")
    my.tp_set_damage_received_doubled_from_fire(mytp, True)
    my.tp_set_environ_avoids_fire(mytp, 100)
    my.tp_set_gfx_oversized_and_on_floor(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_always_hit(mytp, True)
    my.tp_set_is_attackable_by_monst(mytp, True)
    my.tp_set_is_attackable_by_player(mytp, True)
    my.tp_set_is_barrel(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_burnable(mytp, True)
    my.tp_set_is_cursor_can_hover_over(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_heavy(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_light_blocker_for_monst(mytp, True)  # to give cover to the player
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_shovable(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # So it can interact with fire
    my.tp_set_is_very_combustible(mytp, True)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_death_do(mytp, "me.on_death()")
    my.tp_set_on_fall_do(mytp, "me.on_fall()")
    my.tp_set_on_you_are_on_fire_do(mytp, "me.on_fire()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A barrel of oil. Why? Don't ask.")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_IN_FRONT)

    my.tp_set_tile(mytp, tile=name)

    my.tp_update(mytp, )


def init():
    tp_init(name="barrel", text_name="barrel")


init()
