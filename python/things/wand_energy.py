import zx
import tp

mytp = None

def on_idle(me, x, y):
    if zx.thing_get_charge_count(me) < zx.thing_get_initial_charge_count(me):
        zx.thing_incr_charge_count(me, 1)
        owner = zx.thing_get_top_owner_id(me)
        if zx.thing_is_player(owner):
            zx.topcon("%%fg=gold$The {} pulses.%%fg=reset$".format(
                zx.thing_get_name(me)))

def on_use(owner, item, target, x, y):
    #zx.topcon("owner  {} {}".format(zx.thing_get_name(owner), zx.thing_get_health(owner)))
    #zx.topcon("item   {} {}".format(zx.thing_get_name(item), zx.thing_get_health(item)))
    #zx.topcon("target {} {}".format(zx.thing_get_name(target), zx.thing_get_health(target)))
    damage = zx.thing_get_damage_melee(item)
    enchant = zx.thing_get_enchant(item)
    zx.thing_set_current_damage(owner, damage + enchant)

def explode(me, x, y):
    zx.thing_msg(me, "The wand of energy explodes in a blaze of power.")
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
    zx.topcon("The wand glows.")
    zx.thing_incr_charge_count(me, 5)

def tp_init(name, text_name, short_text_name):
    global mytp
    mytp = tp.Tp(name, text_name, short_text_name)
    mytp.set_bag_item_height(2)
    mytp.set_bag_item_width(2)
    mytp.set_charge_count(5)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(5)
    mytp.set_collision_radius(0.40)
    mytp.set_damage_doubled_from_fire(True)
    mytp.set_damage_melee_dice("1d6+6")
    mytp.set_enchant_max(2)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True) # So it can interact with fire
    mytp.set_is_collectable(True)
    mytp.set_is_combustible(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_enchantable(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_shown_on_leftbar(True)
    mytp.set_is_spawner(True)
    mytp.set_is_target_select_automatically_when_chosen(True)
    mytp.set_is_treasure_class_b(True)
    mytp.set_is_treasure(True)
    mytp.set_is_usable(True)
    mytp.set_is_very_combustible(True)
    mytp.set_is_wand(True)
    mytp.set_laser_name("laser_energy")
    mytp.set_long_text_description("Discharges a powerful beam of energy upon an unwitting recipient...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_enchant_do("wand_energy.on_enchant()")
    mytp.set_on_fall_do("wand_energy.on_fall()")
    mytp.set_on_fire_do("wand_energy.on_fire()")
    mytp.set_on_hit_do("wand_energy.on_hit()")
    mytp.set_on_idle_dice("1d200+200:wand_energy.on_idle()")
    mytp.set_on_use_do("wand_energy.on_use()")
    mytp.set_range_max(7)
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("%%fg=yellow$A wand of energy.")
    mytp.set_text_enchant("+5 charges, +1 damage")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_BEHIND)

    mytp.set_tile(tile=name + ".1", delay_ms=100)
    mytp.set_tile(tile=name + ".2", delay_ms=100)
    mytp.set_tile(tile=name + ".3", delay_ms=100)
    mytp.set_tile(tile=name + ".4", delay_ms=100)
    mytp.set_tile(tile=name + ".5", delay_ms=100)
    mytp.set_tile(tile=name + ".6", delay_ms=100)

    mytp.update()

def init():
    tp_init(name="wand_energy", text_name="wand of energy", short_text_name="wand.energy")

init()
