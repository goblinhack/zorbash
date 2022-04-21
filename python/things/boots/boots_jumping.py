import my
import tp

self = None


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The boots become a bit less squeaky and yet more jumpy.")
    my.thing_noise_incr(me, -10)
    my.thing_jump_distance_mod_incr(me, 1)


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.equip_carry_anim(self, "boots_jumping_carry")
    my.gfx_short_shadow_caster(self, True)
    my.gold_value_dice(self, "750")
    my.is_able_to_fall(self, True)
    my.is_auto_equipped(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_biome_swamp(self, True)
    my.is_boots(self, True)
    my.is_burnable(self, True)
    my.is_collectable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.item_height(self, 3)
    my.item_width(self, 3)
    my.jump_distance_mod(self, 1)
    my.long_text_description(self, "Boots of jumping. With these boots you can bound with impunity across chasms. Well, maybe.")
    my.noise_additional_on_jump_end(self, 50)
    my.noise_on_dropping(self, 50)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.rarity(self, my.RARITY_VERY_RARE)
    my.stamina_drain_on_using(self, 10)
    my.stat_dex_mod(self, 1)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Boots of jumping.")
    my.text_enchant(self, "+1 tile")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_char="X", ascii_bg="", ascii_fg="white",
            tile=name)

    my.tp_update(self)


def init():
    tp_init(
        name="boots_jumping",
        text_name="boots of jumping",
        short_text_name="boots of jumping",
    )


init()
