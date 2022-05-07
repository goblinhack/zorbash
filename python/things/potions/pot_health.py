import my
import tp

self = None


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
        my.level_spawn_using_items_radius_range(owner, item, target, "pot_health_effect")
        if my.thing_is_player(owner):
            my.thing_msg(owner, "%%fg=pink$You glow with renewed health.%%fg=reset$")
    else:
        if my.thing_is_player(owner):
            my.thing_msg(owner, "Hm. That potion didn't seem to do anything.")


def explode(me, x, y):
    if my.thing_is_dead(me):
        return

    my.thing_msg(me, "The potion of health explodes.")
    my.level_spawn_at_thing(me, "explosion_fire")
    my.level_spawn_fire_around_thing(me, "fire")
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
    enchant = my.thing_enchant_get(me)
    global self
    if enchant == 0:
        my.long_text_description(self, "Restores you to 80 percent health")
    elif enchant == 0:
        my.long_text_description(self, "Restores you to 90 percent health")
    else:
        my.long_text_description(self, "Restores you to full health")


def tp_init(name, text_name, short_text_name):
    global self
    self = tp.Tp(name, text_name, short_text_name)
    my.collision_hit_priority(self, 5)
    my.collision_hit_priority(self, 6)
    my.enchant_max(self, 5)
    my.environ_avoids_fire(self, 20)
    my.gfx_animated(self, True)
    my.gfx_short_shadow_caster(self, True)
    my.gfx_show_outlined(self, True)
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
    my.is_item(self, True)
    my.is_loggable(self, True)
    my.is_moveable(self, True)
    my.is_potion(self, True)
    my.is_throwable(self, True)
    my.is_tickable(self, True)  # So it can interact with fire
    my.is_treasure_class_b(self, True)
    my.is_treasure(self, True)
    my.is_treasure_type(self, True)
    my.is_usable(self, True)
    my.item_height(self, 4)
    my.item_width(self, 4)
    my.long_text_description(self, "Restores your health and stamina to at least 80 percent. You'll feel like your old self again. Only even more awesome.")
    my.noise_on_dropping(self, 10)
    my.normal_placement_rules(self, True)
    my.on_enchant_do(self, "me.on_enchant()")
    my.on_fall_do(self, "me.on_fall()")
    my.on_use_do(self, "me.on_use()")
    my.on_you_are_hit_but_still_alive_do(self, "me.on_you_are_hit_but_still_alive()")
    my.on_you_are_on_fire_do(self, "me.on_fire()")
    my.text_a_or_an(self, "a")
    my.text_description(self, "A potion of health restoration.")
    my.text_enchant(self, "+10 percent health and stamina")
    my.z_depth(self, my.MAP_DEPTH_OBJ)
    my.z_prio(self, my.MAP_PRIO_BEHIND)

    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".1", delay_ms=500)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".2", delay_ms=500)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".3", delay_ms=500)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".4", delay_ms=500)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".5", delay_ms=500)
    my.tile(self,
            ascii_fg_char="X", ascii_bg_col_name="", ascii_fg_col_name="white",
            tile=name + ".6", delay_ms=500)

    my.tp_update(self)


def init():
    tp_init(
        name="pot_health",
        text_name="potion of health awesomeness",
        short_text_name="potion of health",
    )


init()
