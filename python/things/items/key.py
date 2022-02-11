import my
import tp


def key_init(name, text_name):
    self = tp.Tp(name, text_name)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_bounce_always(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_gold_value_dice(self, "10")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_auto_collect_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_collect_as_keys(self, True)
    my.tp_set_is_interesting(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_key(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_metal(self, True)
    my.tp_set_is_moveable(self, True)
    my.tp_set_light_color(self, "yellow")
    my.tp_set_light_power(self, 2)
    my.tp_set_noise_on_moving_or_being_carried(self, 5)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_text_a_or_an(self, "an")
    my.tp_set_text_description(self, "A key that leadeth places undreamt, or next door.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name + ".1", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".7", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".8", delay_ms=100)

    my.tp_update(self)


def init():
    key_init(name="key", text_name="key")


init()
