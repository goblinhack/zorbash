import my
import tp

self = None


def on_equip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "You feel as if nothing in life can stop you now!")


def on_unequip(owner, me, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "Your feel vulnerable again!")


def on_tick(owner, me, x, y):
    # my.topcon("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.topcon("item    {} {:X}".format(my.thing_name_get(me), me))
    if owner:
        old_health = my.thing_health(owner)
        my.thing_health_incr(owner, 1)
        new_health = my.thing_health(owner)
        if old_health != new_health:
            my.thing_stamina_decr(owner, 1)
        return True

    return False


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.equip_carry_anim(self, "amulet_healing_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "1250")
    my.is_able_to_fall(self, True)
    my.is_amulet(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_tickable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.long_text_description(self, "Amulet of healing. Watch with joy as your health recovers automatically. Watch out though, for each health unit restored, you lose one stamina.")
    my.noise_additional_on_jump_end(self, 10)
    my.noise_on_dropping(self, 50)
    my.normal_placement_rules(self, True)
    my.on_equip_do(self, "me.on_equip()")
    my.on_tick_do(self, "me.on_tick()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.rarity(self, my.RARITY_VERY_RARE)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Amuler of healing.")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="\"", ascii_bg_col="", ascii_fg_col="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="amulet_healing",
        text_name="amulet of healing",
        short_text_name="amulet of healing",
    )


init()
