import zx
import random

all_tps = {}
all_treasure_tps = []


class Tp:
    """thing template"""

    def __init__(self,
                 name,
                 d1000_appearing_roll=0):

        self.name = name
        self.d1000_appearing_roll = d1000_appearing_roll

        #
        # Load it into the game engine
        #
        zx.tp_load(self)
        self.set_raw_name(name)
        all_tps[name] = self
        self.long_name = None
        self.short_name = None
        self.raw_name = None
        self.speed = None
        self.blit_top_off = None
        self.blit_bot_off = None
        self.blit_left_off = None
        self.blit_right_off = None
        self.is_animated = False
        self.is_animated_no_dir = False
        self.is_animation = False
        self.is_monst = False
        self.str_zzz1 = ""
        self.str_zzz2 = ""
        self.str_zzz3 = ""
        self.str_zzz4 = ""
        self.str_zzz5 = ""
        self.str_zzz6 = ""
        self.str_zzz7 = ""
        self.str_zzz8 = ""
        self.str_zzz9 = ""
        self.str_zzz10 = ""
        self.str_zzz11 = ""
        self.str_zzz12 = ""
        self.str_zzz13 = ""
        self.str_zzz14 = ""
        self.str_zzz15 = ""
        self.str_zzz16 = ""
        self.str_zzz17 = ""
        self.str_zzz18 = ""
        self.weapon_carry_anim = ""
        self.weapon_use_anim = ""
        self.is_rrr1 = False
        self.is_rrr2 = False
        self.is_rrr3 = False
        self.is_rrr4 = False
        self.is_rrr5 = False
        self.is_rrr6 = False
        self.is_rrr7 = False
        self.is_rrr8 = False
        self.is_rrr9 = False
        self.is_rrr10 = False
        self.is_rrr11 = False
        self.is_rrr12 = False
        self.is_rrr13 = False
        self.is_rrr14 = False
        self.is_rrr15 = False
        self.is_rrr16 = False
        self.is_rrr17 = False
        self.is_rrr18 = False
        self.is_blit_off_center = False
        self.is_boring = False
        self.is_exit = False
        self.is_entrance = False
        self.move_delay_hundredths = False
        self.weapon_use_delay_hundredths = False
        self.for_collision_use_box = False
        self.for_collision_use_circle = False
        self.weapon_damage = False
        self.is_projectile = False
        self.is_explosion = False
        self.is_combustable = False
        self.is_spikes = False
        self.collision_priority = False
        self.weapon_use_distance = 0
        self.is_weapon_carry_anim = False
        self.is_weapon_use_effect = False
        self.is_weapon = False
        self.is_outlined = False
        self.is_shadow_caster = False
        self.is_ladder = False
        self.is_animated_walk_flip = False
        self.z_depth = False
        self.is_movable = False
        self.is_animated_walk_flip = False
        self.is_movement_blocking = False

        zx.tp_update(self)

    def set_tile(self, tile=None, **kw):
        zx.tp_set_tile(self, tile, **kw)

    def set_left_tile(self, left_tile=None, **kw):
        zx.tp_set_left_tile(self, left_tile, **kw)

    def set_right_tile(self, right_tile=None, **kw):
        zx.tp_set_right_tile(self, right_tile, **kw)

    def set_bot_tile(self, bot_tile=None, **kw):
        zx.tp_set_bot_tile(self, bot_tile, **kw)

    def set_top_tile(self, top_tile=None, **kw):
        zx.tp_set_top_tile(self, top_tile, **kw)

    def set_tl_tile(self, tl_tile=None, **kw):
        zx.tp_set_tl_tile(self, tl_tile, **kw)

    def set_tr_tile(self, tr_tile=None, **kw):
        zx.tp_set_tr_tile(self, tr_tile, **kw)

    def set_br_tile(self, br_tile=None, **kw):
        zx.tp_set_br_tile(self, br_tile, **kw)

    def set_bl_tile(self, bl_tile=None, **kw):
        zx.tp_set_bl_tile(self, bl_tile, **kw)

    def set_long_name(self, value):
        self.long_name = value

    def set_raw_name(self, value):
        self.raw_name = value
        zx.tp_set_raw_name(self, value)

    def set_short_name(self, value):
        self.short_name = value
        zx.tp_set_short_name(self, value)

    def set_blit_top_off(self, value):
        self.blit_top_off = value
        zx.tp_set_blit_top_off(self, value)

    def set_blit_bot_off(self, value):
        self.blit_bot_off = value
        zx.tp_set_blit_bot_off(self, value)

    def set_blit_left_off(self, value):
        self.blit_left_off = value
        zx.tp_set_blit_left_off(self, value)

    def set_blit_right_off(self, value):
        self.blit_right_off = value
        zx.tp_set_blit_right_off(self, value)

    def set_is_animated(self, value):
        self.is_animated = value
        zx.tp_set_is_animated(self, value)

    def set_is_animated_no_dir(self, value):
        self.is_animated_no_dir = value
        zx.tp_set_is_animated_no_dir(self, value)

    def set_is_animation(self, value):
        self.is_animation = value
        zx.tp_set_is_animation(self, value)

    def set_is_monst(self, value):
        self.is_monst = value
        zx.tp_set_is_monst(self, value)

    def set_is_player(self, value):
        self.is_player = value
        zx.tp_set_is_player(self, value)

    def set_str_zzz1(self, value):
        self.str_zzz1 = value
        zx.tp_set_str_zzz1(self, value)

    def set_str_zzz2(self, value):
        self.str_zzz2 = value
        zx.tp_set_str_zzz2(self, value)

    def set_str_zzz3(self, value):
        self.str_zzz3 = value
        zx.tp_set_str_zzz3(self, value)

    def set_str_zzz4(self, value):
        self.str_zzz4 = value
        zx.tp_set_str_zzz4(self, value)

    def set_str_zzz5(self, value):
        self.str_zzz5 = value
        zx.tp_set_str_zzz5(self, value)

    def set_str_zzz6(self, value):
        self.str_zzz6 = value
        zx.tp_set_str_zzz6(self, value)

    def set_str_zzz7(self, value):
        self.str_zzz7 = value
        zx.tp_set_str_zzz7(self, value)

    def set_str_zzz8(self, value):
        self.str_zzz8 = value
        zx.tp_set_str_zzz8(self, value)

    def set_str_zzz9(self, value):
        self.str_zzz9 = value
        zx.tp_set_str_zzz9(self, value)

    def set_str_zzz10(self, value):
        self.str_zzz10 = value
        zx.tp_set_str_zzz10(self, value)

    def set_str_zzz11(self, value):
        self.str_zzz11 = value
        zx.tp_set_str_zzz11(self, value)

    def set_str_zzz12(self, value):
        self.str_zzz12 = value
        zx.tp_set_str_zzz12(self, value)

    def set_str_zzz13(self, value):
        self.str_zzz13 = value
        zx.tp_set_str_zzz13(self, value)

    def set_str_zzz14(self, value):
        self.str_zzz14 = value
        zx.tp_set_str_zzz14(self, value)

    def set_str_zzz15(self, value):
        self.str_zzz15 = value
        zx.tp_set_str_zzz15(self, value)

    def set_str_zzz16(self, value):
        self.str_zzz16 = value
        zx.tp_set_str_zzz16(self, value)

    def set_str_zzz17(self, value):
        self.str_zzz17 = value
        zx.tp_set_str_zzz17(self, value)

    def set_str_zzz18(self, value):
        self.str_zzz18 = value
        zx.tp_set_str_zzz18(self, value)

    def set_weapon_carry_anim(self, value):
        self.weapon_carry_anim = value
        zx.tp_set_weapon_carry_anim(self, value)

    def set_weapon_use_anim(self, value):
        self.weapon_use_anim = value
        zx.tp_set_weapon_use_anim(self, value)

    def set_is_rrr1(self, value):
        self.is_rrr1 = value
        zx.tp_set_is_rrr1(self, value)

    def set_is_rrr2(self, value):
        self.is_rrr2 = value
        zx.tp_set_is_rrr2(self, value)

    def set_is_rrr3(self, value):
        self.is_rrr3 = value
        zx.tp_set_is_rrr3(self, value)

    def set_is_rrr4(self, value):
        self.is_rrr4 = value
        zx.tp_set_is_rrr4(self, value)

    def set_is_rrr5(self, value):
        self.is_rrr5 = value
        zx.tp_set_is_rrr5(self, value)

    def set_is_rrr6(self, value):
        self.is_rrr6 = value
        zx.tp_set_is_rrr6(self, value)

    def set_is_rrr7(self, value):
        self.is_rrr7 = value
        zx.tp_set_is_rrr7(self, value)

    def set_is_rrr8(self, value):
        self.is_rrr8 = value
        zx.tp_set_is_rrr8(self, value)

    def set_is_rrr9(self, value):
        self.is_rrr9 = value
        zx.tp_set_is_rrr9(self, value)

    def set_is_rrr10(self, value):
        self.is_rrr10 = value
        zx.tp_set_is_rrr10(self, value)

    def set_is_rrr11(self, value):
        self.is_rrr11 = value
        zx.tp_set_is_rrr11(self, value)

    def set_is_rrr12(self, value):
        self.is_rrr12 = value
        zx.tp_set_is_rrr12(self, value)

    def set_is_rrr13(self, value):
        self.is_rrr13 = value
        zx.tp_set_is_rrr13(self, value)

    def set_is_rrr14(self, value):
        self.is_rrr14 = value
        zx.tp_set_is_rrr14(self, value)

    def set_is_rrr15(self, value):
        self.is_rrr15 = value
        zx.tp_set_is_rrr15(self, value)

    def set_is_rrr16(self, value):
        self.is_rrr16 = value
        zx.tp_set_is_rrr16(self, value)

    def set_is_rrr17(self, value):
        self.is_rrr17 = value
        zx.tp_set_is_rrr17(self, value)

    def set_is_rrr18(self, value):
        self.is_rrr18 = value
        zx.tp_set_is_rrr18(self, value)

    def set_is_blit_off_center(self, value):
        self.is_blit_off_center = value
        zx.tp_set_is_blit_off_center(self, value)

    def set_is_boring(self, value):
        self.is_boring = value
        zx.tp_set_is_boring(self, value)

    def set_is_exit(self, value):
        self.is_exit = value
        zx.tp_set_is_exit(self, value)

    def set_is_entrance(self, value):
        self.is_entrance = value
        zx.tp_set_is_entrance(self, value)

    def set_move_delay_hundredths(self, value):
        self.move_delay_hundredths = value
        zx.tp_set_move_delay_hundredths(self, value)

    def set_weapon_use_delay_hundredths(self, value):
        self.weapon_use_delay_hundredths = value
        zx.tp_set_weapon_use_delay_hundredths(self, value)

    def set_for_collision_use_box(self, value):
        self.for_collision_use_box = value
        zx.tp_set_for_collision_use_box(self, value)

    def set_for_collision_use_circle(self, value):
        self.for_collision_use_circle = value
        zx.tp_set_for_collision_use_circle(self, value)

    def set_weapon_damage(self, value):
        self.weapon_damage = value
        zx.tp_set_weapon_damage(self, value)

    def set_is_projectile(self, value):
        self.is_projectile = value
        zx.tp_set_is_projectile(self, value)

    def set_is_explosion(self, value):
        self.is_explosion = value
        zx.tp_set_is_explosion(self, value)

    def set_is_combustable(self, value):
        self.is_combustable = value
        zx.tp_set_is_combustable(self, value)

    def set_is_spikes(self, value):
        self.is_spikes = value
        zx.tp_set_is_spikes(self, value)

    def set_collision_priority(self, value):
        self.collision_priority = value
        zx.tp_set_collision_priority(self, value)

    def set_weapon_use_distance(self, value):
        self.weapon_use_distance = value
        zx.tp_set_weapon_use_distance(self, value)

    def set_is_weapon_carry_anim(self, value):
        self.is_weapon_carry_anim = value
        zx.tp_set_is_weapon_carry_anim(self, value)

    def set_is_weapon_use_effect(self, value):
        self.is_weapon_use_effect = value
        zx.tp_set_is_weapon_use_effect(self, value)

    def set_is_weapon(self, value):
        self.is_weapon = value
        zx.tp_set_is_weapon(self, value)

    def set_is_outlined(self, value):
        self.is_outlined = value
        zx.tp_set_is_outlined(self, value)

    def set_is_shadow_caster(self, value):
        self.is_shadow_caster = value
        zx.tp_set_is_shadow_caster(self, value)

    def set_is_ladder(self, value):
        self.is_ladder = value
        zx.tp_set_is_ladder(self, value)

    def set_is_animated_walk_flip(self, value):
        self.is_animated_walk_flip = value
        zx.tp_set_is_animated_walk_flip(self, value)

    def set_z_depth(self, value):
        self.z_depth = value
        zx.tp_set_z_depth(self, value)

    def set_is_movable(self, value):
        self.is_movable = value
        zx.tp_set_is_movable(self, value)

    def set_is_animated_walk_flip(self, value):
        self.is_animated_walk_flip = value
        zx.tp_set_is_animated_walk_flip(self, value)

    def set_is_movement_blocking(self, value):
        self.is_movement_blocking = value
        zx.tp_set_is_movement_blocking(self, value)

    def set_is_treasure(self, value):
        self.is_treasure = value
        zx.tp_set_is_treasure(self, value)

    def set_is_wall(self, value):
        self.is_wall = value
        zx.tp_set_is_wall(self, value)

    def set_is_floor(self, value):
        self.is_floor = value
        zx.tp_set_is_floor(self, value)

def get_random_treasure(toughness=0):
    while True:
        tp = all_tps[random.choice(all_treasure_tps)]

        roll = random.randint(1, 1000) + toughness * 10
        if roll >= tp.d1000_appearing_roll:
            return tp

