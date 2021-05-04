import zx
import tp

def on_use(owner, item, target, x, y):
    #zx.con("owner   {} {:08X}".format(zx.thing_get_name(owner), owner))
    #zx.con("item    {} {:08X}".format(zx.thing_get_name(item), item))
    #zx.con("target  {} {:08X}".format(zx.thing_get_name(target), target))
    health = zx.thing_get_health(owner)
    new_health = int((zx.thing_get_health_max(owner) / 100.0) * 80)
    if new_health > health:
        zx.level_spawn_using_items_radius_range(owner, item, target, "potion_health_effect")
        zx.thing_set_health(owner, new_health)
        if zx.if_matches(owner, "is_player"):
            zx.topcon("%%fg=pink$You glow with renewed health.%%fg=reset$")
    else:
        if zx.if_matches(owner, "is_player"):
            zx.topcon("Hm. That potion didn't seem to do anything.")

def tp_init(name, text_name, short_text_name):
    x = tp.Tp(name, text_name, short_text_name)
    x.set_hates_fire(100)
    x.set_bag_item_height(2)
    x.set_bag_item_width(2)
    x.set_blast_max_radius(0)
    x.set_blast_min_radius(0)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(5)
    x.set_collision_radius(0.40)
    x.set_damage_doubled_from_fire(True)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_attackable_by_player(True)
    x.set_is_collectable(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_droppable(True)
    x.set_is_active(True) # So it can interact with fire
    x.set_is_item(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_moveable(True)
    x.set_is_potion(True)
    x.set_is_combustible(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_throwable(True)
    x.set_is_thrown_automatically_when_chosen(False)
    x.set_is_treasure(True)
    x.set_is_treasure_class_b(True)
    x.set_is_usable(True)
    x.set_is_used_when_thrown(False)
    x.set_long_text_description("Restores you to 80 percent health")
    x.set_normal_placement_rules(True)
    x.set_on_use_do("potion_health.on_use()")
    x.set_text_a_or_an("a")
    x.set_text_description("%%fg=pink$A potion of health restoration.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", delay_ms=500)
    x.set_tile(tile=name + ".2", delay_ms=500)
    x.set_tile(tile=name + ".3", delay_ms=500)
    x.set_tile(tile=name + ".4", delay_ms=500)
    x.set_tile(tile=name + ".5", delay_ms=500)
    x.set_tile(tile=name + ".6", delay_ms=500)

    x.update()

def init():
    tp_init(name="potion_health", text_name="potion of health", short_text_name="pot.health")

init()
