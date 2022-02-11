import my
import tp


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_get_charge_count(me) < my.thing_get_initial_charge_count(me):
        my.thing_incr_charge_count(me, 1)
        owner = my.thing_get_top_owner_id(me)
        if my.thing_is_player(owner):
            my.thing_msg(me, f"%%fg=orange$The {my.thing_get_name(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    my.thing_msg(me, "The wand of cold explodes, oddly in a fireball.")
    my.level_spawn_at_thing(me, "explosion_major")
    my.thing_dead(me, "exploded")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_charge_count(self, 5)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_damage_cold_chance_d1000(self, 1000)
    my.tp_set_damage_cold_dice(self, "1d8+6")
    my.tp_set_damage_received_doubled_from_fire(self, True)
    my.tp_set_environ_avoids_water(self, 100)
    my.tp_set_equip_carry_anim(self, "wand_cold_carry")
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_gold_value_dice(self, "300")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_item_magical(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_target_auto_select(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with cold
    my.tp_set_is_treasure_class_b(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_is_wand(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_long_text_description(self, "Discharges a powerful blast of cold upon an unwitting recipient...")
    my.tp_set_noise_on_moving_or_being_carried(self, 5)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_fall_do(self, "me.on_fall()")
    my.tp_set_on_idle_tick_frequency_dice(self, "1d200+200:me.on_idle()")
    my.tp_set_on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_on_you_are_on_fire_do(self, "me.on_fire()")
    my.tp_set_projectile_name(self, "projectile_cold")
    my.tp_set_range_max(self, 7)
    my.tp_set_temperature(self, -10)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A wand of cold.")
    my.tp_set_z_depth(self, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(self, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(self, tile=name + ".1", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".2", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".3", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".4", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".5", delay_ms=100)
    my.tp_set_tile(self, tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="wand_cold", text_name="wand of cold", short_text_name="wand of cold")


init()
