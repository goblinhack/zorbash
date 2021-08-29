import zx
import tp

mytp = None

def on_use(owner, item, target, x, y):
    #zx.con("owner   {} {:08X}".format(zx.thing_get_name(owner), owner))
    #zx.con("item    {} {:08X}".format(zx.thing_get_name(item), item))
    #zx.con("target  {} {:08X}".format(zx.thing_get_name(target), target))
    did_something = False

    enchant = zx.thing_get_enchant(item)

    health = zx.thing_get_health(owner)
    new_health = int((zx.thing_get_health_max(owner) / 100.0) * 80 + enchant * 10)
    if new_health > health:
        did_something = True
        zx.thing_set_health(owner, new_health)

    stamina = zx.thing_get_stamina(owner)
    new_stamina = int((zx.thing_get_stamina_max(owner) / 100.0) * 80 + enchant * 10)
    if new_stamina > stamina:
        did_something = True
        zx.thing_set_stamina(owner, new_stamina)

    if did_something:
        zx.level_spawn_using_items_radius_range(owner, item, target, "potion_health_effect")
        if zx.if_matches(owner, "is_player"):
            zx.topcon("%%fg=pink$You glow with renewed health.%%fg=reset$")
    else:
        if zx.if_matches(owner, "is_player"):
            zx.topcon("Hm. That potion didn't seem to do anything.")

def explode(me, x, y):
    zx.thing_msg(me, "The potion of health explodes.")
    zx.level_spawn_at_thing(me, "explosion_minor")
    zx.level_spawn_fire_around_thing(me, "fire")
    zx.thing_killed(me, "exploded")

def on_hit(me, hitter, real_hitter, x, y, crit, bite, damage):
    explode(me, x, y)

def on_fire(me, x, y):
    explode(me, x, y)

def on_fall(me, x, y):
    explode(me, x, y)

def on_enchant(me, x, y):
    zx.topcon("The potion bubbles.")
    enchant = zx.thing_get_enchant(me)
    global mytp
    if enchant == 0:
        mytp.set_long_text_description("Restores you to 90 percent health")
    else:
        mytp.set_long_text_description("Restores you to full health")

def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_blast_max_radius(0)
    mytp.set_blast_min_radius(0)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(5)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_enchant_max(2)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gold_value_dice("50")
    mytp.set_hates_fire(100)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_tickable(True) # So it can interact with fire
    mytp.set_is_bag_item(True)
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_hittable(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_moveable(True)
    mytp.set_is_potion(True)
    mytp.set_is_throwable(True)
    mytp.set_is_thrown_automatically_when_chosen(False)
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure_type(True)
    mytp.set_is_health_booster(True)
    mytp.set_is_usable(True)
    mytp.set_is_used_when_thrown(False)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_long_text_description("Restores you to 80 percent health")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("potion_health.on_enchant()")
    mytp.set_on_fall_do("potion_health.on_fall()")
    mytp.set_on_fire_do("potion_health.on_fire()")
    mytp.set_on_hit_do("potion_health.on_hit()")
    mytp.set_on_use_do("potion_health.on_use()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=pink$A potion of health restoration.")
    mytp.set_text_enchant("+10 percent health and stamina")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", delay_ms=500)
    mytp.set_tile(tile=name + ".2", delay_ms=500)
    mytp.set_tile(tile=name + ".3", delay_ms=500)
    mytp.set_tile(tile=name + ".4", delay_ms=500)
    mytp.set_tile(tile=name + ".5", delay_ms=500)
    mytp.set_tile(tile=name + ".6", delay_ms=500)

    mytp.update()

def init():
    tp_init(name="potion_health", text_name="potion of health", short_text_name="pot.health")

init()
