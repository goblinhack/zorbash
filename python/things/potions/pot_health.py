import my
import tp

mytp = None


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:08X}".format(my.thing_get_name(owner), owner))
    # my.con("item    {} {:08X}".format(my.thing_get_name(item), item))
    # my.con("target  {} {:08X}".format(my.thing_get_name(target), target))
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
            my.topcon("%%fg=pink$You glow with renewed health.%%fg=reset$")
    else:
        if my.thing_is_player(owner):
            my.topcon("Hm. That potion didn't seem to do anything.")


def explode(me, x, y):
    my.thing_msg(me, "The potion of health explodes.")
    my.level_spawn_at_thing(me, "explosion_minor")
    my.level_spawn_fire_around_thing(me, "fire")
    my.thing_kill(me, "exploded")


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_enchant(me, x, y):
    owner = my.thing_get_top_owner_id(me)
    if my.thing_is_player(owner):
        my.topcon("The potion bubbles.")
    enchant = my.thing_get_enchant(me)
    global mytp
    if enchant == 0:
        mytp.set_long_text_description("Restores you to 80 percent health")
    elif enchant == 0:
        mytp.set_long_text_description("Restores you to 90 percent health")
    else:
        mytp.set_long_text_description("Restores you to full health")


def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_collision_hit_priority(5)
    mytp.set_damage_received_doubled_from_fire(True)
    mytp.set_enchant_max(2)
    mytp.set_environ_avoids_fire(100)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("50")
    mytp.set_is_able_to_fall(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_crushable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_glass(True)
    mytp.set_is_health_booster(True)
    mytp.set_is_hittable(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable(True)
    mytp.set_is_moveable(True)
    mytp.set_is_potion(True)
    mytp.set_is_throwable(True)
    mytp.set_is_tickable(True)  # So it can interact with fire
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_usable(True)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Restores your health and stamina to at least 80 percent. You'll feel like your old self again. Only even more awesome.")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("me.on_enchant()")
    mytp.set_on_fall_do("me.on_fall()")
    mytp.set_on_use_do("me.on_use()")
    mytp.set_on_you_are_hit_but_still_alive_do("me.on_you_are_hit_but_still_alive()")
    mytp.set_on_you_are_on_fire_do("me.on_fire()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A potion of health restoration.")
    mytp.set_text_enchant("+10 percent health and stamina")
    mytp.set_z_depth(my.MAP_DEPTH_OBJ)
    mytp.set_z_prio(my.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", delay_ms=500)
    mytp.set_tile(tile=name + ".2", delay_ms=500)
    mytp.set_tile(tile=name + ".3", delay_ms=500)
    mytp.set_tile(tile=name + ".4", delay_ms=500)
    mytp.set_tile(tile=name + ".5", delay_ms=500)
    mytp.set_tile(tile=name + ".6", delay_ms=500)

    mytp.update()


def init():
    tp_init(
        name="pot_health",
        text_name="potion of health awesomeness",
        short_text_name="potion of health",
    )


init()
