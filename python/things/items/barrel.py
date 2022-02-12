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
    my.ai_obstacle(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 1)
    my.damage_crush_chance_d1000(self, 1000)
    my.damage_crush_dice(self, "2d6")
    my.damage_received_doubled_from_fire(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.is_able_to_fall(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_barrel(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_cursor_can_hover_over(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_light_blocker_for_monst(self, True)  # to give cover to the player
    my.is_loggable(self, True)
    my.is_shovable(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_very_combustible(self, True)
    my.normal_placement_rules(self, True)
    my.on_death_do(self, "me.on_death()")
    my.on_fall_do(self, "me.on_fall()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.text_a_or_an(self, "a")
    my.text_description(self, "A barrel of oil. Why? Don't ask.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(name="barrel", text_name="barrel")


init()
