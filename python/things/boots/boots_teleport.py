import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The boots become a bit less squeaky.")
    my.thing_noise_incr(me, -10)


def on_use(owner, item, target, x, y):
    # my.topcon("owner  {} {}".format(my.thing_name_get(owner), my.thing_health_get(owner)))
    # my.topcon("item   {} {}".format(my.thing_name_get(item), my.thing_health_get(item)))
    # my.topcon("target {} {}".format(my.thing_name_get(target), my.thing_health_get(target)))
    return


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.equip_carry_anim(self, "boots_teleport_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "750")
    my.is_able_to_fall(self, True)
    my.is_boots(self, True)
    my.is_auto_equipped(self, True)
    my.is_item_targetted(self, True)
    my.is_usable(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_collectable(self, True)
    my.is_target_select(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.noise_additional_on_teleporting(self, 50)
    my.noise_additional_on_jump_end(self, 50)
    my.noise_on_dropping(self, 50)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_burnable(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.stat_dex_mod(self, -1)
    my.distance_teleport(self, 20)
    my.long_text_description(self, "Boots of teleport. With these boots you can travel with impunity across the level. Beware the cold of the void, however.")
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_use_do(self, "me.on_use()")
    my.rarity(self, my.RARITY_VERY_RARE)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Boots of teleport.")
    my.text_enchant(self, "-10 decibels")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self, tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="boots_teleport",
        text_name="boots of teleport",
        short_text_name="boots of teleport",
    )


init()
