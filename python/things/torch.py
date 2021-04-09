import zx
import tp


def tp_init(name, text_name, tiles=[]):
    x = tp.Tp(name, text_name)
    x.set_bag_item_height(2)
    x.set_bag_item_width(2)
    x.set_charge_count(4)
    x.set_collision_circle(True)
    x.set_collision_hit_priority(0)
    x.set_collision_radius(0.40)
    x.set_gfx_animated(True)
    x.set_gfx_glows(True)
    x.set_gfx_show_outlined(True)
    x.set_gfx_small_shadow_caster(True)
    x.set_is_able_to_fall(True)
    x.set_is_active(True) # for pushing and falling
    x.set_is_burnable(True)
    x.set_is_collectable(True)
    x.set_is_combustible(True)
    x.set_is_described_when_hovering_over(True)
    x.set_is_droppable(True)
    x.set_is_flammable(True)
    x.set_is_interesting(True)
    x.set_is_item(True)
    x.set_is_loggable_for_important_stuff(True)
    x.set_is_loggable_for_unimportant_stuff(True)
    x.set_is_shown_on_leftbar(True)
    x.set_is_torch(True)
    x.set_is_treasure(True)
    x.set_is_treasure_class_a(True)
    x.set_is_usable(True)
    x.set_lifespan_dice("100+1d20")
    x.set_light_color("orange")
    x.set_light_strength(2)
    x.set_long_text_description("A bundle of torches to light the way. Be warned, they do burn out slowly. Don't find yourself lost in the dark...")
    x.set_normal_placement_rules(True)
    x.set_text_a_or_an("a");
    x.set_text_description("A small beacon of light in this blighted place.")
    x.set_z_depth(zx.MAP_DEPTH_OBJ)
    x.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=100
    for t in tiles:
        x.set_tile(tile=t, delay_ms=delay)

    x.update()

def init():
    tp_init(name="torch", text_name="torch",
            tiles=[
                "torch.1",
                "torch.2",
                "torch.3",
                "torch.4",
                "torch.5",
                ])
init()
