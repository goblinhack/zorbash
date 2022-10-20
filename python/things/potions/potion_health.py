import my
import tp


def on_get_text_long_description(owner, me, x, y):
    enchant = my.thing_enchant_get(me)
    if enchant == 0:
        return ["Restores you to 80 percent health"]
    elif enchant == 1:
        return ["Restores you to 90 percent health"]
    else:
        return ["Restores you to full health"]


def on_thrown(me, x, y):
    if my.level_is_chasm_at(me, x, y):
        return
    if my.level_is_water_at(me, x, y):
        return
    my.spawn_at_my_position(me, "water")


def on_use(owner, item, target, x, y):
    # my.con("owner   {} {:X}".format(my.thing_name_get(owner), owner))
    # my.con("item    {} {:X}".format(my.thing_name_get(item), item))
    # my.con("target  {} {:X}".format(my.thing_name_get(target), target))
    did_something = False

    enchant = my.thing_enchant_get(item)

    health = my.thing_health(owner)
    new_health = int((my.thing_health_max(owner) / 100.0) * 80 + enchant * 10)
    if new_health > health:
        did_something = True
        my.thing_health_set(owner, new_health)

    stamina = my.thing_stamina(owner)
    new_stamina = int((my.thing_stamina_max(owner) / 100.0) * 80 + enchant * 10)
    if new_stamina > stamina:
        did_something = True
        my.thing_stamina_set(owner, new_stamina)

    if my.thing_poisoned_amount_get(owner) != 0:
        did_something = True
        my.thing_poisoned_amount_set(owner, 0)

    if did_something:
        my.spawn_using_items_radius_range(owner, item, target, "potion_health_effect")
        if my.thing_is_player(owner):
            my.thing_msg(owner, "%%fg=pink$You glow with renewed health.%%fg=reset$")
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "Hm. That potion didn't seem to do anything.")


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    owner = my.thing_top_owner_id_get(me)
    if owner:
        if my.thing_is_player(owner):
            my.thing_msg(me, "Your wand of ice explodes.")
        else:
            my.thing_msg(me, f"The {my.thing_name_get(owner)}'s wand of ice explodes.")
    else:
        my.thing_msg(me, "The wand of ice explodes.")

    my.spawn_at_my_position(me, "explosion_fire")
    my.spawn_fire_around_thing(me, "fire")
    my.thing_dead(me, "exploded")


def on_you_are_hit_but_still_alive(me, hitter, real_hitter, x, y, crit, damage):
    explode(me, x, y)


def on_fire(me, x, y):
    explode(me, x, y)


def on_fall(me, x, y):
    explode(me, x, y)


def on_enchant(me, x, y):
    owner = my.thing_top_owner_id_get(me)
    if my.thing_is_player(owner):
        my.thing_msg(me, "The potion bubbles.")


def tp_init(name, text_long_name, text_short_name):
    self = tp.Tp(name, text_long_name, text_short_name)
    # begin sort marker
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 5)
    my.environ_avoids_fire(self, 20)
    my.gfx_ascii_shown(self, True)
    my.gfx_pixelart_animated(self, True)
    my.gfx_pixelart_reflection(self, True)
    my.gfx_pixelart_shadow(self, True)
    my.gfx_pixelart_shadow_short(self, True)
    my.gfx_pixelart_show_outlined(self, True)
    my.gold_value_dice(self, "50")
    my.is_able_to_fall(self, True)
    my.is_bag_item(self, True)
    my.is_biome_dungeon(self, True)
    my.is_collectable(self, True)
    my.is_combustible(self, True)
    my.is_crushable(self, True)
    my.is_described_when_hovering_over(self, True)
    my.is_droppable(self, True)
    my.is_enchantable(self, True)
    my.is_glass(self, True)
    my.is_health_booster(self, True)
    my.is_hittable(self, True)
    my.is_interesting(self, True)
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_potion(self, True)
    my.is_throwable(self, True)
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.noise_on_dropping(self, 10)
    my.normal_placement_rules(self, True)
    my.nutrition_dice(self, "1d20")
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_fall_do(self, "me.on_fall()")
    my.on_get_text_long_description_do(self, "me.on_get_text_long_description()")
    my.on_thrown_do(self, "me.on_thrown()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.text_a_or_an(self, "a")
    my.text_enchant(self, "+10 percent health and stamina")
    my.text_long_description(self, "Restores your health and stamina to at least 80 percent. You'll feel like your old self again. Only even more awesome.")
    my.text_short_description(self, "A potion of health restoration.")
    my.tick_prio(self, my.MAP_TICK_PRIO_NORMAL)
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_Z_PRIO_BEHIND)
    # end sort marker

    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".1", delay_ms=500)
    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".2", delay_ms=500)
    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".3", delay_ms=500)
    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".4", delay_ms=500)
    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".5", delay_ms=500)
    my.tile(self,
            ascii_fg_char="!", ascii_bg_col_name="", ascii_fg_col_name="pink",
            tile=name + ".6", delay_ms=500)

    my.tp_update(self)


def init():
    tp_init(name="potion_health", text_long_name="potion of health awesomeness", text_short_name="pot. health")


init()
