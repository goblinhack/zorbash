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
    self = tp.Tp(name, text_name)
    my.tp_set_ai_obstacle(self, True)
    my.tp_set_collision_check(self, True)
    my.tp_set_collision_hit_priority(self, 1)
    my.tp_set_damage_crush_chance_d1000(self, 1000)
    my.tp_set_damage_crush_dice(self, "2d6")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_environ_avoids_fire(self, 100)
    my.tp_set_gfx_oversized_and_on_floor(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_always_hit(self, True)
    my.tp_set_is_attackable_by_monst(self, True)
    my.tp_set_is_attackable_by_player(self, True)
    my.tp_set_is_barrel(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_cursor_can_hover_over(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_heavy(self, True)
    my.tp_set_is_hittable(self, True)
    my.tp_set_is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_shovable(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with fire
    my.tp_set_is_very_combustible(self, True)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_death_do(self, "me.on_death()")
    my.tp_set_on_fall_do(self, "me.on_fall()")
    my.tp_set_on_you_are_on_fire_do(self, "me.on_fire()")
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A barrel of oil. Why? Don't ask.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tp_set_tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(name="barrel", text_name="barrel")


init()
