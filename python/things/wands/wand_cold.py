import my
import tp


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_get_charge_count(me) < my.thing_get_initial_charge_count(me):
        my.thing_charge_count_incr(me, 1)
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
    my.charge_count(self, 5)
    my.collision_hit_priority(self, 6)
    my.damage_cold_chance_d1000(self, 1000)
    my.damage_cold_dice(self, "1d8+6")
    my.damage_received_doubled_from_fire(self, True)
    my.environ_avoids_water(self, 100)
    my.equip_carry_anim(self, "wand_cold_carry")
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.gold_value_dice(self, "300")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_item_magical(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_victim_select(self, True)
    my.is_tickable(self, True)  # So it can interact with cold
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_wand(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "Discharges a powerful blast of cold upon an unwitting recipient...")
    my.noise_on_moving_or_being_carried(self, 5)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_idle_tick_frequency_dice(self, "1d200+200:me.on_idle()")
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.projectile_name(self, "projectile_cold")
    my.range_max(self, 7)
    my.temperature(self, -10)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A wand of cold.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name + ".1", delay_ms=100)
    my.tile(self, tile=name + ".2", delay_ms=100)
    my.tile(self, tile=name + ".3", delay_ms=100)
    my.tile(self, tile=name + ".4", delay_ms=100)
    my.tile(self, tile=name + ".5", delay_ms=100)
    my.tile(self, tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="wand_cold", text_name="wand of cold", short_text_name="wand of cold")


init()
