import zx
import tp


def tp_init(name, text_name):
    x = tp.Tp(name, text_name)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(1)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_gold_value_dice("1d100")
    x.set_is_able_to_fall(True)
    x.set_is_collectable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_attackable(True)
    x.set_is_item_collected_as_gold(True)
    x.set_is_attackable(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_treasure(True)
    x.set_is_attackable(True)
    x.set_is_treasure_class_b(True)
    x.set_is_attackable(True)
    x.set_long_text_description("Topaz is prized for its ability to help you make friends. Just what you need. There are some entrails left on this piece. Just wipe them off.")
    x.set_normal_placement_rules(True)
    x.set_rarity(zx.RARITY_COMMON)
    x.set_text_a_or_an("a");
    x.set_text_description("%%fg=cyan$Clean cut topaz")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_BEHIND)

    x.set_tile(tile=name + ".1", is_dir_none=True, delay_ms=2000)
    x.set_tile(tile=name + ".2", is_dir_none=True, delay_ms=100)
    x.set_tile(tile=name + ".3", is_dir_none=True, delay_ms=100)

    x.update()

def init():
    tp_init(name="gem2", text_name="topaz")

init()
