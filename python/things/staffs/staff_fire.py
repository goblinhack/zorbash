import my
import tp


def on_targeted(me, x, y):
    radius = my.thing_effect_radius_get(me)
    # my.con("targeted {} {:X} radius {}".format(my.thing_name_get(me), me, radius))

    for dx in range(-radius, radius + 1):
        for dy in range(-radius, radius + 1):
            x1 = x + dx
            y1 = y + dy
            distance = (((x1 - x)**2 + (y1 - y)**2)**0.5)
            if distance > radius + 0.5:
                continue

            if not my.level_is_fire_at(me, x1, y1):
                my.place_at(me, "fire", x1, y1)

            for it in my.level_get_all(me, x1, y1):
                if my.thing_possible_to_attack(me, it):
                    my.thing_hit_dmg_fire(0, me, it)

    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_b")


def on_targeted_radially(me, x, y):
    radius = my.thing_effect_radius_get(me)
    radius += 1

    # my.con("targeted radially {} {:X}".format(my.thing_name_get(me), me))
    for dx in range(-radius, radius + 1):
        for dy in range(-radius, radius + 1):
            if dx == 0 and dy == 0:
                continue
            x1 = x + dx
            y1 = y + dy
            distance = (((x1 - x)**2 + (y1 - y)**2)**0.5)
            if distance > radius + 0.5:
                continue

            if not my.level_is_fire_at(me, x1, y1):
                my.place_at(me, "fire", x1, y1)

            for it in my.level_get_all(me, x1, y1):
                if my.thing_possible_to_attack(me, it):
                    my.thing_hit_dmg_fire(0, me, it)

    my.thing_sound_play_channel(me, my.CHANNEL_EXPLOSION, "explosion_b")


def on_idle(me, x, y):
    #
    # Random recharge
    #
    if my.thing_charge_count(me) < my.thing_initial_charge_count(me):
        my.thing_charge_count_incr(me, 1)
        owner = my.thing_top_owner_id_get(me)
        if owner and my.thing_is_player(owner):
            my.thing_msg(me, f"%%fg=orange$The {my.thing_name_get(me)} pulses.%%fg=reset$")


def explode(me, x, y):
    if my.thing_charge_count(me) == 0:
        return

    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(me, "Your staff of fire explodes.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s staff of fire explodes.")
    else:
        my.thing_msg(me, "The staff of fire explodes.")

    my.spawn_at_my_position(me, "explosion_major")
    on_targeted(me, x, y)
    my.thing_dead(me, "exploded")


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


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.chance_d10000_enchanted(self, 20)
    my.chance_d10000_set_on_fire(self, 0)
    my.charge_count(self, 5)
    my.collision_hit_priority(self, 6)
    my.dmg_chance_d1000_fire(self, 1, 1000)
    my.dmg_fire_dice(self, "1d10+10")
    my.dmg_num_of_attacks(self, 1)
    my.dmg_rcv_doubled_from_cold(self, True)
    my.effect_has_blast_radius(self, True)
    my.environ_dislikes_water(self, 100)
    my.equip_carry_anim(self, "staff_fire_carry")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_targeted_projectile(self, "staff_projectile_fire")
    my.gold_value_dice(self, "500")
    my.health_initial_dice(self, "20+1d10")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    # my.is_able_to_spawn_things(self, False) else we end up owning fire
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
    my.is_immune_to_fire(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_staff(self, True)
    my.is_target_radial(self, True)
    my.is_target_select(self, True)
    my.is_throwable(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_treasure_class_B(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_value_offensive(self, 2)
    my.is_wooden(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 5)
    my.normal_placement_rules(self, True)
    my.on_fall_do(self, "me.on_fall()")
    my.on_hit_and_now_dead_do(self, "me.on_hit_and_now_dead()")
    my.on_idle_tick_freq_dice(self, "1d200+200:me.on_idle()")
    my.on_targeted_do(self, "me.on_targeted()")
    my.on_targeted_radially_do(self, "me.on_targeted_radially()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.range_max(self, 7)
    my.temperature(self, 30)
    my.text_a_or_an(self, "a")
    my.text_description_enchant(self, "+1 radius")
    my.text_description_long2(self, "When enchanted, creates a blast radius effect. Ideal for taking out multiple enemies.")
    my.text_description_long3(self, "Please use responsibly.")
    my.text_description_long(self, "Discharges a single fireball at an ungrateful recipient...")
    my.text_description_short(self, "A staff of fireballs.")
    my.tick_prio(self, my.MAP_TICK_PRIO_LOW)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="orange2",
            tile=name + ".1", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="orange2",
            tile=name + ".2", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="orange2",
            tile=name + ".3", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="orange2",
            tile=name + ".4", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="orange2",
            tile=name + ".5", delay_ms=100)
    my.tile(self,
            ascii_fg_char="/", ascii_bg_col_name="", ascii_fg_col_name="orange2",
            tile=name + ".6", delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(name="staff_fire", text_long_name="staff of fireballs", text_short_name="staff, fire")


init()
