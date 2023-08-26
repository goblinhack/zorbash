import my
import tp


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.aggression_pct(self, 100)
    my.ai_wanderer(self, True)
    my.attack_humanoid(self, True)
    my.chance_d1000_teleport_attack(self, 1000)
    my.collision_check(self, True)
    my.collision_hit_priority(self, 20)
    my.distance_vision(self, 8)
    my.gfx_ascii_fade_with_dist(self, True)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_bounce_on_move(self, True)
    my.gfx_pixelart_health_bar_shown(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_highlighted(self, True)
    my.gfx_pixelart_wobbles_when_hit(self, True)
    my.health_initial_dice(self, "1")
    my.is_able_to_be_teleported(self, True)
    my.is_able_to_see_in_the_dark(self, True)
    my.is_able_to_teleport_attack(self, True)
    my.is_biome_chasms(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_ice(self, True)
    my.is_biome_lava(self, True)
    my.is_described_in_leftbar(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_ethereal(self, True)
    my.is_immune_to_acid(self, True)
    my.is_immune_to_cold(self, True)
    my.is_immune_to_fire(self, True)
    my.is_immune_to_poison(self, True)
    my.is_interesting(self, True)
    my.is_lifeless(self, True)
    my.is_loggable(self, True)
    my.is_magical(self, True)
    my.is_monst_class_B(self, True)
    my.is_monst(self, True)
    my.is_moveable(self, True)
    my.is_tickable(self, True)
    my.light_color(self, "purple")
    my.light_dist(self, 1)
    my.move_speed(self, 50)
    my.noise_decibels_hearing(self, 5)
    my.noise_on_moving(self, 1)
    my.normal_placement_rules(self, True)
    my.rarity(self, my.RARITY_UNCOMMON)  # how rare within this monster class
    my.stat_con(self, 10)
    my.stat_def(self, 10)
    my.stat_dex(self, 10)
    my.stat_luck(self, 10)
    my.stat_psi(self, 0)
    my.stat_str(self, 10)
    my.teleport_distance(self, 20)
    my.text_a_or_an(self, "a")
    my.text_description_long2(self, "Originally used to get rid of detritus from the dungeon floor, they also work well for getting rid of annoying dungeoneers.")
    my.text_description_long(self, "Portable holes are a one way ticket to other parts of the dungeon, which may or may not be a good thing.")
    my.text_description_short(self, "A portable hole.")
    my.text_hits(self, "burns")
    my.thing_size(self, my.THING_SIZE_NORMAL)
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_CONSUMER)  # so it appears over things when consuming
    # end sort marker

    delay = 200
    my.tile(self,
            ascii_fg_char="O", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".1", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="o", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".2", delay_ms=delay)
    my.tile(self,
            ascii_fg_char=".", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".3", delay_ms=delay)
    my.tile(self,
            ascii_fg_char="o", ascii_bg_col_name="", ascii_fg_col_name="purple",
            tile=name + ".4", delay_ms=delay)

    my.tp_update(self)


def init():
    tp_init(name="portable_hole", text_long_name="portable hole", text_short_name="portable hole")


init()
