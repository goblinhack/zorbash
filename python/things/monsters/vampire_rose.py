import my
import tp


def on_you_nat_att(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def try_to_grow(me, x, y, dx, dy):
    if my.level_is_monst_at(me, x + dx, y + dy) or \
       my.level_is_player_at(me, x + dx, y + dy) or \
       my.level_is_lava_at(me, x + dx, y + dy) or \
       my.level_is_chasm_at(me, x + dx, y + dy) or \
       my.level_is_brazier_at(me, x + dx, y + dy) or \
       my.level_is_fire_at(me, x + dx, y + dy) or \
       my.level_is_carnivorous_plant_at(me, x + dx, y + dy) or \
       my.level_is_wall_at(me, x + dx, y + dy) or \
       my.level_is_water_at(me, x + dx, y + dy):
        return
    if my.level_is_floor_at(me, x + dx, y + dy):
        if my.pcg_randint(1, 100) < 10:
            my.spawn_at(me, "vampire_rose_stem1", x + dx, y + dy)
            return
        if my.pcg_randint(1, 100) < 10:
            my.spawn_at(me, "vampire_rose_stem2", x + dx, y + dy)
            return


def on_idle(me, x, y):
    try_to_grow(me, x, y, -1, 0)
    try_to_grow(me, x, y,  1, 0)
    try_to_grow(me, x, y, 0, -1)
    try_to_grow(me, x, y, 0,  1)


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.attack_eater(self, True)
    my.attack_humanoid(self, True)
    my.attack_meat(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.consume_per_bite_amount(self, 1)
    my.distance_vision(self, 1)
    my.dmg_chance_d1000_digest(self, 0, 1000)
    my.dmg_chance_d1000_nat_att(self, 0, 1000)
    my.dmg_digest_dice(self, "1d5")
    my.dmg_nat_att_dice(self, "1d6")
    my.dmg_nat_att_type(self, "bleed")
    my.dmg_received_doubled_from_fire(self, True)
    my.environ_avoids_acid(self, True)
    my.environ_avoids_fire(self, 100)
    my.gfx_anim_use(self, "red_splatter")
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_submergible(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1d3")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_freeze(self, True)
    my.is_able_to_lunge(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_always_hit(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_swamp(self, True)
    my.is_burnable(self, True)
    my.is_carnivorous_plant(self, True)
    my.is_combustible(self, True)
    my.is_corpse_on_death(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_eater_of_meat(self, True)
    my.is_eater_of_red_blood(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_loggable(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_msg_allowed_is_dead(self, True)
    my.is_msg_allowed_is_seen(self, True)
    my.is_msg_allowed_is_wounded(self, True)
    my.is_plant(self, True)
    my.is_red_blooded(self, True)
    my.is_soft(self, True)
    my.is_tickable(self, True)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_idle_tick_freq_dice(self, "1d20:me.on_idle()")
    my.on_you_nat_att_do(self, "me.on_you_nat_att()")
    my.rarity(self, my.RARITY_COMMON)  # how rare within this monster class
    my.stat_con(self, 20)
    my.stat_def(self, 0)
    my.stat_dex(self, 0)
    my.stat_luck(self, 10)
    my.stat_str(self, 10)
    my.temperature_max(self, 50)
    my.temperature_min(self, 0)
    my.temperature(self, 20)
    my.temperature_sensitive(self, True)
    my.text_a_or_an(self, "a")
    my.text_description_long(self, "Vampire roses grow rapidly and primarily feed on blood and rotting corpses. Be a good gardener and don't allow them to spread.")
    my.text_description_short(self, "A beatiful vampire rose.")
    my.text_hits(self, "bites")
    my.thing_size(self, my.THING_SIZE_SMALL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    delay = 5000
    my.tile(self,
            ascii_fg_char="v", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".1", delay_ms=delay)
    delay = 200
    my.tile(self,
            ascii_fg_char="V", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="v", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="V", ascii_bg_col_name="", ascii_fg_col_name="red",
            tile=name + ".4", delay_ms=delay)

    my.tile(self,
            ascii_fg_char="v", ascii_bg_col_name="", ascii_fg_col_name="brown",
            tile=name + ".dead", is_dead=True)

    my.tp_update(self)


def init():
    tp_init(name="vampire_rose", text_long_name="vampire rose", text_short_name="vampire rose")


init()
