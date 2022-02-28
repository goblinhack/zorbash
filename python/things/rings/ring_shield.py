import my
import tp


def on_owner_add(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "A protective semi transparent shield surrounds you.")


# Called on removing a ring. Not called on death of the owner.
def on_owner_remove(me, owner, x, y):
    if my.thing_is_player(owner):
        my.thing_msg(me, "The shield around you fades.")


def on_owner_damage(me, owner, hitter, real_hitter, x, y, damage):
    if my.thing_is_player(owner):
        return int(damage / 2)
    return damage


def on_owner_damage_melee(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_poison(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_future1(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_future2(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_future3(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_cold(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_fire(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_crush(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_lightning(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_energy(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_acid(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_digest(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_natural_attack(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_necrosis(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_stat_str(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def on_owner_damage_stat_con(me, owner, hitter, real_hitter, x, y, damage):
    return on_owner_damage(me, owner, hitter, real_hitter, x, y, damage)


def tp_init(name, text_name, short_text_name):
    self = tp.Tp(name, text_name, short_text_name)
    my.blast_max_radius(self, 2)
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
    my.gold_value_dice(self, "500")
    my.health_initial_dice(self, "1d20")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_item_magical(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_ring(self, True)
    my.is_spawner(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_treasure_class_c(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.is_very_combustible(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "This magical ring is designed to create a protective shield, mainly from missle weapons. Damage will be reduced by 50 percent whilst this ring is worn.")
    my.normal_placement_rules(self, True)
    my.on_owner_add_do(self, "me.on_owner_add()")
    my.on_owner_damage_acid_do(self, "me.on_owner_damage_acid()")
    my.on_owner_damage_cold_do(self, "me.on_owner_damage_cold()")
    my.on_owner_damage_crush_do(self, "me.on_owner_damage_crush()")
    my.on_owner_damage_digest_do(self, "me.on_owner_damage_digest()")
    my.on_owner_damage_energy_do(self, "me.on_owner_damage_energy()")
    my.on_owner_damage_fire_do(self, "me.on_owner_damage_fire()")
    my.on_owner_damage_future1_do(self, "me.on_owner_damage_future1()")
    my.on_owner_damage_future2_do(self, "me.on_owner_damage_future2()")
    my.on_owner_damage_future3_do(self, "me.on_owner_damage_future3()")
    my.is_auto_equipped(self, True)
    my.on_owner_damage_lightning_do(self, "me.on_owner_damage_lightning()")
    my.on_owner_damage_melee_do(self, "me.on_owner_damage_melee()")
    my.on_owner_damage_natural_attack_do(self, "me.on_owner_damage_natural_attack()")
    my.on_owner_damage_necrosis_do(self, "me.on_owner_damage_necrosis()")
    my.on_owner_damage_poison_do(self, "me.on_owner_damage_poison()")
    my.on_owner_damage_stat_con_do(self, "me.on_owner_damage_stat_con()")
    my.on_owner_damage_stat_str_do(self, "me.on_owner_damage_stat_str()")
    my.on_owner_remove_do(self, "me.on_owner_remove()")
    my.on_unequip_do(self, "me.on_unequip()")
    my.stat_con_mod(self, 3)
    my.text_a_or_an(self, "a")
    my.text_description(self, "Shield ring.")
    my.text_enchant(self, "+1 DEF")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)
    my.equip_carry_anim(self, "ring_shield_carry")

    my.tile(self, tile=name, delay_ms=100)

    my.tp_update(self)


def init():
    tp_init(
        name="ring_shield",
        text_name="shield ring",
        short_text_name="shield ring",
    )


init()
