import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The stone cloak glistens.")
    my.thing_stat_def_mod_incr(me, 2)


def on_waiting(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if not owner:
        return False

    if my.level_is_wall_at(owner, x, y):
        stamina = my.thing_stamina(owner)
        new_stamina = int((stamina / 100.0) * 90)
        my.thing_stamina_set(owner, new_stamina)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You wait inside the wall and feel drained.")
        return True

    if my.level_is_rock_at(owner, x, y):
        stamina = my.thing_stamina(owner)
        new_stamina = int((stamina / 100.0) * 80)
        my.thing_stamina_set(owner, new_stamina)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You wait inside solid rock and feel very drained.")
        return True

    return False


def on_move(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if not owner:
        return False

    if my.level_is_wall_at(owner, x, y):
        stamina = my.thing_stamina(owner)
        new_stamina = int((stamina / 100.0) * 80)
        my.thing_stamina_set(owner, new_stamina)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You pass into the wall, but feel drained.")
        return True

    if my.level_is_rock_at(owner, x, y):
        stamina = my.thing_stamina(owner)
        new_stamina = int((stamina / 100.0) * 50)
        my.thing_stamina_set(owner, new_stamina)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You pass into solid rock, but feel very drained.")
        return True

    return False


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.damaged_chance_d10000(self, 100)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 10)
    my.equip_carry_anim(self, "cloak_stone_carry")
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "500")
    my.is_able_to_fall(self, True)
    my.is_cloak(self, True)
    my.on_move_do(self, "me.on_move()")
    my.on_waiting_do(self, "me.on_waiting()")
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_able_to_walk_through_walls(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.text_long_description(self, "A strange, almost black, cloak that looks to be covered in shimmering stone dust... It glistens in your torch light as you examine it. It seems magical... but what does it do?")
    my.noise_on_dropping(self, -20)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "Stone cloak.")
    my.text_enchant(self, "+1 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="gray50",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="cloak_stone",
        text_long_name="stone cloak",
        text_short_name="cloak, stone",
    )


init()
