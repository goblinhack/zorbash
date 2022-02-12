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
            my.thing_msg(owner, f"%%fg=blue$The {my.thing_get_name(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    my.thing_msg(me, "The wand of descent explodes. The earth tremors.")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_dead(me, "exploded")


def on_final_use(owner, item, target, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(owner, "The wand crumbles into dust.")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.tp_set_blast_max_radius(self, 2)
    my.tp_set_charge_count(self, 3)
    my.tp_set_collision_hit_priority(self, 5)
    my.tp_set_collision_hit_priority(self, 6)
    my.tp_set_equip_carry_anim(self, "wand_descent_carry")
    my.tp_set_gfx_animated(self, True)
    my.tp_set_gfx_short_shadow_caster(self, True)
    my.tp_set_gfx_show_outlined(self, True)
    my.tp_set_gold_value_dice(self, "500")
    my.tp_set_is_able_to_fall(self, True)
    my.tp_set_is_bag_item(self, True)
    my.tp_set_is_biome_dungeon(self, True)
    my.tp_set_is_burnable(self, True)
    my.tp_set_is_collectable(self, True)
    my.tp_set_is_combustible(self, True)
    my.tp_set_is_crushable(self, True)
    my.tp_set_is_described_when_hovering_over(self, True)
    my.tp_set_is_droppable(self, True)
    my.tp_set_is_item_magical(self, True)
    my.tp_set_is_item(self, True)
    my.tp_set_is_loggable(self, True)
    my.tp_set_is_spawner(self, True)
    my.tp_set_is_victim_select(self, True)
    my.tp_set_is_tickable(self, True)  # So it can interact with fire
    my.tp_set_is_treasure_class_c(self, True)
    my.tp_set_is_treasure(self, True)
    my.tp_set_is_treasure_type(self, True)
    my.tp_set_is_usable(self, True)
    my.tp_set_is_very_combustible(self, True)
    my.tp_set_is_wand(self, True)
    my.tp_set_is_wooden(self, True)
    my.tp_set_item_height(self, 4)
    my.tp_set_item_width(self, 4)
    my.tp_set_laser_name(self, "laser_descent")
    my.tp_set_long_text_description(self, "This most dangerous wand can transport its target to the next level by the most efficacious means possible...")
    my.tp_set_noise_on_moving_or_being_carried(self, 5)
    my.tp_set_normal_placement_rules(self, True)
    my.tp_set_on_fall_do(self, "me.on_fall()")
    my.tp_set_on_final_use_do(self, "me.on_final_use()")
    my.tp_set_on_idle_tick_frequency_dice(self, "1d1000+200:me.on_idle()")
    my.tp_set_on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.tp_set_on_you_are_on_fire_do(self, "me.on_fire()")
    my.tp_set_range_max(self, 7)
    my.tp_set_text_a_or_an(self, "a")
    my.tp_set_text_description(self, "A wand of descent.")
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
    tp_init(
        name="wand_descent",
        text_name="wand of sudden descent",
        short_text_name="wand of descent",
    )


init()
