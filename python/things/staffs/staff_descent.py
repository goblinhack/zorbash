import my
import tp


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_charge_count_get(me) < my.thing_initial_charge_count_get(me):
        my.thing_charge_count_incr(me, 1)
        owner = my.thing_top_owner_id_get(me)
        if my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=blue$The {my.thing_name_get(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_msg(me, "The staff of descent explodes. The earth shakes.")
    my.level_spawn_using_items_radius_range(me, me, me, "explosion_destroy_floor")
    my.thing_dead(me, "exploded")


def on_final_use(owner, item, target, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(owner, "The wand crumbles into dust.")


def on_you_are_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.blast_max_radius(self, 2)
    my.charge_count(self, 3)
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.equip_carry_anim(self, "staff_descent_carry")
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "500")
    my.health_initial_dice(self, "20+1d10")
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
    my.is_spawner(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_target_select(self, True)
    my.is_target_radial(self, True)
    my.is_staff(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.target_name_laser(self, "effect_descent")
    my.target_name_radial(self, "effect_descent_radial")
    my.long_text_description(self, "This most dangerous wand can transport its target to the next level by the most efficacious means possible...")
    my.noise_on_dropping(self, 5)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_final_use_do(self, "me.on_final_use()")
    my.on_idle_tick_freq_dice(self, "1d1000+200:me.on_idle()")
    my.on_you_are_hit_and_now_dead_do(self, "me.on_you_are_hit_and_now_dead()")
    my.range_max(self, 7)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A staff of descent.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(
        name="staff_descent",
        text_name="staff of sudden descent",
        short_text_name="staff of descent",
    )


init()
