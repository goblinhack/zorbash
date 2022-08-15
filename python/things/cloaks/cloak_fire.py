import my
import tp

self = None


def on_equip(owner, me, x, y):
    my.thing_buff_add(owner, "buff_fire_proof")


def on_unequip(owner, me, x, y):
    my.thing_buff_remove(owner, "buff_fire_proof")


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The fire cloak burns brighter.")


def on_waiting(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if not owner:
        return False

    enchant = my.thing_enchant_get(me)
    if enchant == 0:
        enchant = 1

    if my.level_is_lava_at(owner, x, y):
        my.thing_stamina_incr(owner, 10 * enchant)
        my.thing_health_incr(owner, 10 * enchant)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You wait inside the lava and feel invigoratied.")
        return True

    if my.level_is_fire_at(owner, x, y) or my.level_is_lava_at(owner, x, y):
        my.thing_stamina_incr(owner, 5 * enchant)
        my.thing_health_incr(owner, 5 * enchant)
        if my.thing_is_player(owner):
            my.thing_msg(owner, "You wait inside the fire and feel invigorated.")
        return True

    return False


def on_move(me, x, y):
    return on_waiting(me, x, y)


def tp_init(name, text_long_name, text_short_name):
    global self
    self = tp.Tp(name, text_long_name, text_short_name)
    # start sort marker
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.gfx_ascii_shown(self, True)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 10)
    my.equip_carry_anim(self, "cloak_fire_carry")
    my.gfx_pixelart_shadow_short(self, True)
    my.gold_value_dice(self, "666")
    my.is_able_to_fall(self, True)
    my.is_cloak(self, True)
    my.on_move_do(self, "me.on_move()")
    my.on_waiting_do(self, "me.on_waiting()")
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_unequip_do(self, "me.on_unequip()")
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
    my.text_long_description(self, "A brilliant fiery red cloak.")
    my.noise_on_dropping(self, -20)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.rarity(self, my.RARITY_COMMON)
    my.stat_def_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_short_description(self, "Cloak of fire protection.")
    my.text_enchant(self, "+1 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_ITEM)
    # end sort marker

    my.tile(self,
            ascii_fg_char="[", ascii_bg_col_name="", ascii_fg_col_name="orange",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="cloak_fire",
        text_long_name="fire cloak",
        text_short_name="cloak, fire",
    )


init()
