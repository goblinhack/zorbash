import my
import tp


def on_you_nat_attack(me, x, y):
    my.thing_sound_play_channel(me, my.CHANNEL_MONST, "squelch")


def on_idle(me, x, y):
    if not my.level_is_acid_at(me, x, y):
        my.level_spawn_at_thing(me, "acid1")


def on_death(me, x, y):
    my.level_spawn_at_thing(me, "green_splatter")


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_dead(me, "exploded")
    my.thing_msg(me, "The dungeon cleaner erupts in flaming goo!")
    my.level_spawn_at_thing(me, "explosion_major")
    my.level_spawn_fire_around_thing(me, "fire")
    my.level_spawn_at_thing(me, "fire")


def on_fire(me, x, y):
    explode(me, x, y)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.aggression_level_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_eater(self, True)
    my.attack_engulf_chance_d1000(self, 1000)
    my.attack_lunge(self, True)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 10)
    my.collision_hit_priority(self, 6)
    my.damage_digest_dice(self, "1d40")
    my.damage_nat_attack_type(self, "burn")
    my.damage_natural_dice(self, "1d20")
    my.damage_received_doubled_from_cold(self, True)
    my.damage_received_doubled_from_fire(self, True)
    my.distance_vision(self, 3)
    my.environ_avoids_fire(self, 100)
    my.gfx_animated_can_hflip(self, True)
    my.gfx_animated(self, True)
    my.gfx_anim_use(self, "green_splatter")
    my.gfx_bounce_on_move(self, True)
    my.gfx_health_bar_shown(self, True)
    my.gfx_oversized_and_on_floor(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.health_initial_dice(self, "8d10+40")
    my.hunger_clock_tick_freq(self, 50)
    my.hunger_health_pct(self, 95)
    my.hunger_is_insatiable(self, True)
    my.is_able_to_fall(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_attackable_by_monst(self, True)
    my.is_attackable_by_player(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_bleeder(self, True)
    my.is_carrier_of_treasure_class_a(self, True)
    my.is_carrier_of_treasure_class_b(self, True)
    my.is_carrier_of_treasure_class_c(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_engulfer(self, True)
    my.is_green_blooded(self, True)
    my.is_heavy(self, True)
    my.is_hittable(self, True)
    my.is_immune_to_acid(self, True)
    my.is_item_collector(self, True)
    my.is_item_eater(self, True)
    my.is_jelly_baby_eater(self, True)
    my.is_jelly_eater(self, True)
    my.is_loggable(self, True)
    my.is_meat_eater(self, True)
    my.is_monst_class_b(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_potion_eater(self, True)
    my.is_red_blood_eater(self, True)
    my.is_soft(self, True)
    my.is_steal_item_chance_d1000(self, 200)
    my.is_sticky(self, True)
    my.is_temperature_sensitive(self, True)
    my.is_tickable(self, True)
    my.is_treasure_eater(self, True)
    my.light_color(self, "green")
    my.light_dist(self, 2)
    my.long_text_description(self, "Dungeon cleaners have evolved to scrub their domain of all messy organic matter. That means you. Cleaners leave a trail of corrosive slime in their wake. Avoid this. Cleaners also have a habit of eating your hard fought items.")
    my.monst_size(self, my.MONST_SIZE_LARGE)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 50)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d4")
    my.on_death_do(self, "me.on_death()")
    my.on_death_drop_all_items(self, True)
    my.on_idle_tick_freq_dice(self, "1d5:me.on_idle()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.on_you_nat_attack_do(self, "me.on_you_nat_attack()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_con(self, 20)
    my.stat_def(self, 6)
    my.stat_dex(self, 3)
    my.stat_luck(self, 10)
    my.stat_str(self, 14)
    my.text_a_or_an(self, "a")
    my.text_description(self, "A dungeon auto cleaner jelly thingy.")
    my.text_hits(self, "burns")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_IN_FRONT)  # so it appears over things when consuming

    delay = 200
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_char="m", ascii_bg="", ascii_fg="white",
            tile=name + ".4", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="cleaner", text_name="dungeon cleaner", short_text_name="cleaner")


init()
