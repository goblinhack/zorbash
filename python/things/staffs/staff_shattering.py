import my
import tp


def on_targeted(me, x, y):
    radius = my.thing_effect_radius_get(me)
    # my.con("targeted {} {:X} at {} {} radius {}".format(my.thing_name_get(me), me, x, y, radius))

    for dx in range(-radius, radius + 1):
        for dy in range(-radius, radius + 1):
            x1 = x + dx
            y1 = y + dy
            distance = (((x1 - x)**2 + (y1 - y)**2)**0.5)
            if distance > radius + 0.5:
                continue

            my.place_at(me, "explosion_shattering", x1, y1)
            for it in my.level_get_all(me, x1, y1):
                if my.thing_possible_to_attack(me, it):
                    my.thing_hit(0, me, it)


def on_targeted_radially(me, x, y):
    radius = my.thing_effect_radius_get(me)
    radius += 1
    # my.con("targeted radially {} {:X}".format(my.thing_name_get(me), me))
    my.spawn_things_around_me(me, "explosion_shattering", radius)


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_charge_count(me) < my.thing_initial_charge_count(me):
        my.thing_charge_count_incr(me, 1)
        owner = my.thing_top_owner_id_get(me)
        if owner and my.thing_is_player(owner):
            my.thing_msg(owner, f"%%fg=blue$The {my.thing_name_get(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    if my.thing_charge_count(me) == 0:
        return

    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if owner and my.thing_is_player(owner):
            my.thing_msg(me, "Your staff of shattering explodes.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s staff of shattering explodes.")
    else:
        my.thing_msg(me, "The staff of shattering explodes.")

    my.spawn_at_my_position(me, "explosion_major")
    my.thing_msg(me, "The earth shakes.")
    on_targeted(me, x, y)
    my.thing_dead(me, "exploded")


def on_final_use(owner, item, target, x, y):
    if owner and my.thing_is_player(owner):
        my.thing_msg(owner, "The staff crumbles into dust.")


def on_thrown(owner, me, x, y):
    if my.thing_charge_count(me) == 0:
        return
    if my.level_is_chasm_at(me, x, y):
        return
    if my.level_is_water_at(me, x, y):
        return
    explode(me, x, y)


def on_hit_and_now_dead(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_set_on_fire(self, 5000)
    my.charge_count(self, 3)
    my.collision_hit_priority(self, 6)
    my.effect_has_blast_radius(self, True)
    my.equip_carry_anim(self, "staff_shattering_carry")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_targeted_laser(self, "staff_tunneling_laser")
    my.gfx_targeted_radial(self, "staff_shattering_radial")
    my.gold_value_dice(self, "750")
    my.health_initial_dice(self, "20+1d10")
    my.is_able_to_be_reflected(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_staff(self, True)
    my.is_target_radial(self, True)
    my.is_target_select(self, True)
    my.is_throwable(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_treasure_class_C(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 5)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_final_use_do(self, "me.on_final_use()")
    my.on_hit_and_now_dead_do(self, "me.on_hit_and_now_dead()")
    my.on_idle_tick_freq_dice(self, "1d200+200:me.on_idle()")
    my.on_targeted_do(self, "me.on_targeted()")
    my.on_targeted_radially_do(self, "me.on_targeted_radially()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.range_max(self, 7)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 radius")
    my.text_description_long(self, "This staff will destroy various wall like obstacles and in their place will create a shard of crystal. The crystal is generally easier to then destroy and has additional reflective properties for beam like weapons.")
    my.text_description_short(self, "A staff of shattering.")
    my.tick_prio(self, my.MAP_TICK_PRIO_LOW)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".1", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="yellow",
            tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="staff_shattering", text_long_name="staff of shattering", text_short_name="staff, shattering")


init()
