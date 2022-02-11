import my
import tp

mytp = None


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_get_name(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_get_name(item), item))
    # my.con("target  {} {:X}".format(my.thing_get_name(target), target))
    did_something = False

    enchant = my.thing_get_enchant(item)

    health = my.thing_get_health(owner)
    new_health = int((my.thing_get_health_max(owner) / 100.0) * 80 + enchant * 10)
    if new_health > health:
        did_something = True
        my.thing_set_health(owner, new_health)

    stamina = my.thing_get_stamina(owner)
    new_stamina = int((my.thing_get_stamina_max(owner) / 100.0) * 80 + enchant * 10)
    if new_stamina > stamina:
        did_something = True
        my.thing_set_stamina(owner, new_stamina)

    if my.thing_get_poisoned_amount(owner) != 0:
        did_something = True
        my.thing_set_poisoned_amount(owner, 0)

    if did_something:
        my.level_spawn_using_items_radius_range(owner, item, target, "pot_health_effect")
        if my.thing_is_player(owner):
            my.thing_msg(owner, "%%fg=pink$You glow with renewed health.%%fg=reset$")
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "Hm. That potion didn't seem to do anything.")


def explode(me, x, y):
    my.thing_msg(me, "The potion of health explodes.")
    my.level_spawn_at_thing(me, "explosion_minor")
    my.level_spawn_fire_around_thing(me, "fire")
    my.thing_dead(me, "exploded")


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The potion bubbles.")
    enchant = my.thing_get_enchant(me)
    global mytp
    if enchant == 0:
        my.tp_set_long_text_description(mytp, "Restores you to 80 percent health")
    elif enchant == 0:
        my.tp_set_long_text_description(mytp, "Restores you to 90 percent health")
    else:
        my.tp_set_long_text_description(mytp, "Restores you to full health")


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    my.tp_set_collision_hit_priority(mytp, 5)
    my.tp_set_collision_hit_priority(mytp, 6)
    my.tp_set_enchant_max(mytp, 2)
    my.tp_set_environ_avoids_fire(mytp, 20)
    my.tp_set_gfx_animated(mytp, True)
    my.tp_set_gfx_short_shadow_caster(mytp, True)
    my.tp_set_gfx_show_outlined(mytp, True)
    my.tp_set_gold_value_dice(mytp, "50")
    my.tp_set_is_able_to_fall(mytp, True)
    my.tp_set_is_bag_item(mytp, True)
    my.tp_set_is_biome_dungeon(mytp, True)
    my.tp_set_is_collectable(mytp, True)
    my.tp_set_is_combustible(mytp, True)
    my.tp_set_is_crushable(mytp, True)
    my.tp_set_is_described_when_hovering_over(mytp, True)
    my.tp_set_is_droppable(mytp, True)
    my.tp_set_is_enchantable(mytp, True)
    my.tp_set_is_glass(mytp, True)
    my.tp_set_is_health_booster(mytp, True)
    my.tp_set_is_hittable(mytp, True)
    my.tp_set_is_item(mytp, True)
    my.tp_set_is_loggable(mytp, True)
    my.tp_set_is_moveable(mytp, True)
    my.tp_set_is_potion(mytp, True)
    my.tp_set_is_throwable(mytp, True)
    my.tp_set_is_tickable(mytp, True)  # So it can interact with fire
    my.tp_set_is_treasure_class_b(mytp, True)
    my.tp_set_is_treasure(mytp, True)
    my.tp_set_is_treasure_type(mytp, True)
    my.tp_set_is_usable(mytp, True)
    my.tp_set_item_height(mytp, 4)
    my.tp_set_item_width(mytp, 4)
    my.tp_set_long_text_description(mytp, "Restores your health and stamina to at least 80 percent. You'll feel like your old self again. Only even more awesome.")
    my.tp_set_noise_on_moving_or_being_carried(mytp, 10)
    my.tp_set_normal_placement_rules(mytp, True)
    my.tp_set_on_enchant_do(mytp, "me.on_enchant()")
    my.tp_set_on_fall_do(mytp, "me.on_fall()")
    my.tp_set_on_use_do(mytp, "me.on_use()")
    my.tp_set_on_you_are_hit_but_still_alive_do(mytp, "me.on_you_are_hit_but_still_alive()")
    my.tp_set_on_you_are_on_fire_do(mytp, "me.on_fire()")
    my.tp_set_text_a_or_an(mytp, "a")
    my.tp_set_text_description(mytp, "A potion of health restoration.")
    my.tp_set_text_enchant(mytp, "+10 percent health and stamina")
    my.tp_set_z_depth(mytp, my.MAP_DEPTH_OBJ)
    my.tp_set_z_prio(mytp, my.MAP_PRIO_BEHIND)

    my.tp_set_tile(mytp, tile=name + ".1", delay_ms=500)
    my.tp_set_tile(mytp, tile=name + ".2", delay_ms=500)
    my.tp_set_tile(mytp, tile=name + ".3", delay_ms=500)
    my.tp_set_tile(mytp, tile=name + ".4", delay_ms=500)
    my.tp_set_tile(mytp, tile=name + ".5", delay_ms=500)
    my.tp_set_tile(mytp, tile=name + ".6", delay_ms=500)

    my.tp_update(mytp, )


def init():
    tp_init(
        name="pot_health",
        text_name="potion of health awesomeness",
        short_text_name="potion of health",
    )


init()
