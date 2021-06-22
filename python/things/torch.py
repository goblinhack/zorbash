import zx
import tp


def on_lifespan(owner, me, x, y):
    if zx.if_matches(owner, "is_player"):
        zx.topcon("One of your torches fizzles out.")

def tp_init(name, text_name, tiles=[]):
    mytp = tp.Tp(name, text_name)
    mytp.set_item_height(4)
    mytp.set_item_width(4)
    mytp.set_charge_count(4)
    mytp.set_collision_circle(True)
    mytp.set_collision_hit_priority(1)
    mytp.set_collision_radius(0.40)
    mytp.set_gfx_animated(True)
    mytp.set_gfx_flickers(True)
    mytp.set_gfx_glows(True)
    mytp.set_gfx_short_shadow_caster(True)
    mytp.set_gfx_show_outlined(True)
    mytp.set_is_able_to_fall(True)
    mytp.set_is_active(True) # for pushing and falling
    mytp.set_is_collectable(True)
    mytp.set_is_described_when_hovering_over(True)
    mytp.set_is_droppable(True)
    mytp.set_is_bag_item(True)
    mytp.set_is_item(True)
    mytp.set_is_loggable_for_important_stuff(True)
    mytp.set_is_loggable_for_unimportant_stuff(True)
    mytp.set_is_torch(True)
    mytp.set_is_treasure_class_a(True)
    mytp.set_is_treasure(True)
    mytp.set_lifespan_dice("1d300+10")
    mytp.set_light_color("orange")
    mytp.set_light_strength(2)
    mytp.set_long_text_description("A bundle of torches to light the way. Be warned, they do burn out slowly. Don't find yourself lost in the dark...")
    mytp.set_normal_placement_rules(True)
    mytp.set_on_lifespan_do("torch.on_lifespan()")
    mytp.set_text_a_or_an("a")
    mytp.set_text_description("A small beacon of light in this blighted place.")
    mytp.set_z_depth(zx.MAP_DEPTH_OBJ)
    mytp.set_z_prio(zx.MAP_PRIO_NORMAL)

    delay=100
    for t in tiles:
        mytp.set_tile(tile=t, delay_ms=delay)

    mytp.update()

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
