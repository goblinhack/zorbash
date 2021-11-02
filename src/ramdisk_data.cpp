#include "my_ramdisk.hpp"

void ramdisk_init (void)
{
    {
        extern unsigned char *data_weapons_tga_start_
           asm("data_weapons_tga_start_");
        extern unsigned char *data_weapons_tga_end_
           asm("data_weapons_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_weapons_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_weapons_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/weapons.tga"] = r;
    }

    {
        extern unsigned char *data_tiles1_monsts_and_items_tga_start_
           asm("data_tiles1_monsts_and_items_tga_start_");
        extern unsigned char *data_tiles1_monsts_and_items_tga_end_
           asm("data_tiles1_monsts_and_items_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles1_monsts_and_items_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles1_monsts_and_items_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles1_monsts_and_items.tga"] = r;
    }

    {
        extern unsigned char *data_ui_inventory_tga_start_
           asm("data_ui_inventory_tga_start_");
        extern unsigned char *data_ui_inventory_tga_end_
           asm("data_ui_inventory_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_inventory_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_inventory_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_inventory.tga"] = r;
    }

    {
        extern unsigned char *data_laser_descent_tga_start_
           asm("data_laser_descent_tga_start_");
        extern unsigned char *data_laser_descent_tga_end_
           asm("data_laser_descent_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_laser_descent_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_laser_descent_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/laser_descent.tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_water_tga_start_
           asm("data_tiles3_water_tga_start_");
        extern unsigned char *data_tiles3_water_tga_end_
           asm("data_tiles3_water_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles3_water_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles3_water_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_water.tga"] = r;
    }

    {
        extern unsigned char *data_ui_horiz2_tga_start_
           asm("data_ui_horiz2_tga_start_");
        extern unsigned char *data_ui_horiz2_tga_end_
           asm("data_ui_horiz2_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_horiz2_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_horiz2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_horiz2.tga"] = r;
    }

    {
        extern unsigned char *data_ui_horiz1_tga_start_
           asm("data_ui_horiz1_tga_start_");
        extern unsigned char *data_ui_horiz1_tga_end_
           asm("data_ui_horiz1_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_horiz1_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_horiz1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_horiz1.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box6_tga_start_
           asm("data_ui_box6_tga_start_");
        extern unsigned char *data_ui_box6_tga_end_
           asm("data_ui_box6_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box6_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box6_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box6.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box5_tga_start_
           asm("data_ui_box5_tga_start_");
        extern unsigned char *data_ui_box5_tga_end_
           asm("data_ui_box5_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box5_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box5_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box5.tga"] = r;
    }

    {
        extern unsigned char *data_ui_health_bar_tga_start_
           asm("data_ui_health_bar_tga_start_");
        extern unsigned char *data_ui_health_bar_tga_end_
           asm("data_ui_health_bar_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_health_bar_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_health_bar_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_health_bar.tga"] = r;
    }

    {
        extern unsigned char *data_glow_tga_start_
           asm("data_glow_tga_start_");
        extern unsigned char *data_glow_tga_end_
           asm("data_glow_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_glow_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_glow_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/glow.tga"] = r;
    }

    {
        extern unsigned char *data_ui_tabs_tga_start_
           asm("data_ui_tabs_tga_start_");
        extern unsigned char *data_ui_tabs_tga_end_
           asm("data_ui_tabs_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_tabs_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_tabs_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_tabs.tga"] = r;
    }

    {
        extern unsigned char *data_ui_credits_bg_tga_start_
           asm("data_ui_credits_bg_tga_start_");
        extern unsigned char *data_ui_credits_bg_tga_end_
           asm("data_ui_credits_bg_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_credits_bg_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_credits_bg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_credits_bg.tga"] = r;
    }

    {
        extern unsigned char *data_laser_green_tga_start_
           asm("data_laser_green_tga_start_");
        extern unsigned char *data_laser_green_tga_end_
           asm("data_laser_green_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_laser_green_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_laser_green_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/laser_green.tga"] = r;
    }

    {
        extern unsigned char *data_tiles1_floors_tga_start_
           asm("data_tiles1_floors_tga_start_");
        extern unsigned char *data_tiles1_floors_tga_end_
           asm("data_tiles1_floors_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles1_floors_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles1_floors_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles1_floors.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box0_tga_start_
           asm("data_ui_box0_tga_start_");
        extern unsigned char *data_ui_box0_tga_end_
           asm("data_ui_box0_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box0_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box0_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box0.tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_surface_effects_tga_start_
           asm("data_tiles3_surface_effects_tga_start_");
        extern unsigned char *data_tiles3_surface_effects_tga_end_
           asm("data_tiles3_surface_effects_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles3_surface_effects_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles3_surface_effects_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_surface_effects.tga"] = r;
    }

    {
        extern unsigned char *data_title_fg1_tga_start_
           asm("data_title_fg1_tga_start_");
        extern unsigned char *data_title_fg1_tga_end_
           asm("data_title_fg1_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_fg1_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_fg1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg1.tga"] = r;
    }

    {
        extern unsigned char *data_laser_energy_tga_start_
           asm("data_laser_energy_tga_start_");
        extern unsigned char *data_laser_energy_tga_end_
           asm("data_laser_energy_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_laser_energy_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_laser_energy_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/laser_energy.tga"] = r;
    }

    {
        extern unsigned char *data_ui_tile_bg_tga_start_
           asm("data_ui_tile_bg_tga_start_");
        extern unsigned char *data_ui_tile_bg_tga_end_
           asm("data_ui_tile_bg_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_tile_bg_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_tile_bg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_tile_bg.tga"] = r;
    }

    {
        extern unsigned char *data_ui_bag_tga_start_
           asm("data_ui_bag_tga_start_");
        extern unsigned char *data_ui_bag_tga_end_
           asm("data_ui_bag_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_bag_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_bag_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_bag.tga"] = r;
    }

    {
        extern unsigned char *data_tiles1_walls_tga_start_
           asm("data_tiles1_walls_tga_start_");
        extern unsigned char *data_tiles1_walls_tga_end_
           asm("data_tiles1_walls_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles1_walls_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles1_walls_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles1_walls.tga"] = r;
    }

    {
        extern unsigned char *data_ui_vert2_tga_start_
           asm("data_ui_vert2_tga_start_");
        extern unsigned char *data_ui_vert2_tga_end_
           asm("data_ui_vert2_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_vert2_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_vert2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_vert2.tga"] = r;
    }

    {
        extern unsigned char *data_title_fg3_tga_start_
           asm("data_title_fg3_tga_start_");
        extern unsigned char *data_title_fg3_tga_end_
           asm("data_title_fg3_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_fg3_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_fg3_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg3.tga"] = r;
    }

    {
        extern unsigned char *data_tiles2_tga_start_
           asm("data_tiles2_tga_start_");
        extern unsigned char *data_tiles2_tga_end_
           asm("data_tiles2_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles2_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles2.tga"] = r;
    }

    {
        extern unsigned char *data_solid_tga_start_
           asm("data_solid_tga_start_");
        extern unsigned char *data_solid_tga_end_
           asm("data_solid_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_solid_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_solid_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/solid.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box4_tga_start_
           asm("data_ui_box4_tga_start_");
        extern unsigned char *data_ui_box4_tga_end_
           asm("data_ui_box4_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box4_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box4_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box4.tga"] = r;
    }

    {
        extern unsigned char *data_chasm2_tga_start_
           asm("data_chasm2_tga_start_");
        extern unsigned char *data_chasm2_tga_end_
           asm("data_chasm2_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_chasm2_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_chasm2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/chasm2.tga"] = r;
    }

    {
        extern unsigned char *data_ui_bag_highlighted_tga_start_
           asm("data_ui_bag_highlighted_tga_start_");
        extern unsigned char *data_ui_bag_highlighted_tga_end_
           asm("data_ui_bag_highlighted_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_bag_highlighted_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_bag_highlighted_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_bag_highlighted.tga"] = r;
    }

    {
        extern unsigned char *data_ui_vert1_tga_start_
           asm("data_ui_vert1_tga_start_");
        extern unsigned char *data_ui_vert1_tga_end_
           asm("data_ui_vert1_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_vert1_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_vert1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_vert1.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box1_tga_start_
           asm("data_ui_box1_tga_start_");
        extern unsigned char *data_ui_box1_tga_end_
           asm("data_ui_box1_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box1_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box1.tga"] = r;
    }

    {
        extern unsigned char *data_ui_credits_fg_tga_start_
           asm("data_ui_credits_fg_tga_start_");
        extern unsigned char *data_ui_credits_fg_tga_end_
           asm("data_ui_credits_fg_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_credits_fg_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_credits_fg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_credits_fg.tga"] = r;
    }

    {
        extern unsigned char *data_light_tga_start_
           asm("data_light_tga_start_");
        extern unsigned char *data_light_tga_end_
           asm("data_light_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_light_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_light_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/light.tga"] = r;
    }

    {
        extern unsigned char *data_title_fg4_tga_start_
           asm("data_title_fg4_tga_start_");
        extern unsigned char *data_title_fg4_tga_end_
           asm("data_title_fg4_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_fg4_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_fg4_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg4.tga"] = r;
    }

    {
        extern unsigned char *data_title_bg_tga_start_
           asm("data_title_bg_tga_start_");
        extern unsigned char *data_title_bg_tga_end_
           asm("data_title_bg_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_bg_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_bg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_bg.tga"] = r;
    }

    {
        extern unsigned char *data_ui_dead_tga_start_
           asm("data_ui_dead_tga_start_");
        extern unsigned char *data_ui_dead_tga_end_
           asm("data_ui_dead_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_dead_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_dead_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_dead.tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_sewer_water_tga_start_
           asm("data_tiles3_sewer_water_tga_start_");
        extern unsigned char *data_tiles3_sewer_water_tga_end_
           asm("data_tiles3_sewer_water_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles3_sewer_water_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles3_sewer_water_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_sewer_water.tga"] = r;
    }

    {
        extern unsigned char *data_laser_lightning_tga_start_
           asm("data_laser_lightning_tga_start_");
        extern unsigned char *data_laser_lightning_tga_end_
           asm("data_laser_lightning_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_laser_lightning_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_laser_lightning_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/laser_lightning.tga"] = r;
    }

    {
        extern unsigned char *data_title_fg2_tga_start_
           asm("data_title_fg2_tga_start_");
        extern unsigned char *data_title_fg2_tga_end_
           asm("data_title_fg2_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_fg2_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_fg2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg2.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box2_tga_start_
           asm("data_ui_box2_tga_start_");
        extern unsigned char *data_ui_box2_tga_end_
           asm("data_ui_box2_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box2_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box2.tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_lava_tga_start_
           asm("data_tiles3_lava_tga_start_");
        extern unsigned char *data_tiles3_lava_tga_end_
           asm("data_tiles3_lava_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles3_lava_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles3_lava_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_lava.tga"] = r;
    }

    {
        extern unsigned char *data_ui_status_bar_tga_start_
           asm("data_ui_status_bar_tga_start_");
        extern unsigned char *data_ui_status_bar_tga_end_
           asm("data_ui_status_bar_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_status_bar_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_status_bar_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_status_bar.tga"] = r;
    }

    {
        extern unsigned char *data_chasm_tga_start_
           asm("data_chasm_tga_start_");
        extern unsigned char *data_chasm_tga_end_
           asm("data_chasm_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_chasm_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_chasm_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/chasm.tga"] = r;
    }

    {
        extern unsigned char *data_title_small_tga_start_
           asm("data_title_small_tga_start_");
        extern unsigned char *data_title_small_tga_end_
           asm("data_title_small_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_small_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_small_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_small.tga"] = r;
    }

    {
        extern unsigned char *data_attack_tga_start_
           asm("data_attack_tga_start_");
        extern unsigned char *data_attack_tga_end_
           asm("data_attack_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_attack_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_attack_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/attack.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box7_tga_start_
           asm("data_ui_box7_tga_start_");
        extern unsigned char *data_ui_box7_tga_end_
           asm("data_ui_box7_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box7_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box7_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box7.tga"] = r;
    }

    {
        extern unsigned char *data_ui_circle_tga_start_
           asm("data_ui_circle_tga_start_");
        extern unsigned char *data_ui_circle_tga_end_
           asm("data_ui_circle_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_circle_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_circle_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_circle.tga"] = r;
    }

    {
        extern unsigned char *data_title_splash_tga_start_
           asm("data_title_splash_tga_start_");
        extern unsigned char *data_title_splash_tga_end_
           asm("data_title_splash_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_title_splash_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_title_splash_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_splash.tga"] = r;
    }

    {
        extern unsigned char *data_projectile_fire_tga_start_
           asm("data_projectile_fire_tga_start_");
        extern unsigned char *data_projectile_fire_tga_end_
           asm("data_projectile_fire_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_projectile_fire_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_projectile_fire_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/projectile_fire.tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_deep_water_tga_start_
           asm("data_tiles3_deep_water_tga_start_");
        extern unsigned char *data_tiles3_deep_water_tga_end_
           asm("data_tiles3_deep_water_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles3_deep_water_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles3_deep_water_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_deep_water.tga"] = r;
    }

    {
        extern unsigned char *data_explosion_tga_start_
           asm("data_explosion_tga_start_");
        extern unsigned char *data_explosion_tga_end_
           asm("data_explosion_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_explosion_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_explosion_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/explosion.tga"] = r;
    }

    {
        extern unsigned char *data_ui_box3_tga_start_
           asm("data_ui_box3_tga_start_");
        extern unsigned char *data_ui_box3_tga_end_
           asm("data_ui_box3_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ui_box3_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ui_box3_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box3.tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_tga_start_
           asm("data_tiles3_tga_start_");
        extern unsigned char *data_tiles3_tga_end_
           asm("data_tiles3_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_tiles3_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_tiles3_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3.tga"] = r;
    }

    {
        extern unsigned char *data_background_tga_start_
           asm("data_background_tga_start_");
        extern unsigned char *data_background_tga_end_
           asm("data_background_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_background_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_background_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/background.tga"] = r;
    }

    {
        extern unsigned char *data_blood_tga_start_
           asm("data_blood_tga_start_");
        extern unsigned char *data_blood_tga_end_
           asm("data_blood_tga_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_blood_tga_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_blood_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/blood.tga"] = r;
    }

    {
        extern unsigned char *data___shoot_a_wav_start_
           asm("data___shoot_a_wav_start_");
        extern unsigned char *data___shoot_a_wav_end_
           asm("data___shoot_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___shoot_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___shoot_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._shoot_a.wav"] = r;
    }

    {
        extern unsigned char *data___swing_wav_start_
           asm("data___swing_wav_start_");
        extern unsigned char *data___swing_wav_end_
           asm("data___swing_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___swing_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___swing_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._swing.wav"] = r;
    }

    {
        extern unsigned char *data___disarm_single_wav_start_
           asm("data___disarm_single_wav_start_");
        extern unsigned char *data___disarm_single_wav_end_
           asm("data___disarm_single_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___disarm_single_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___disarm_single_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._disarm_single.wav"] = r;
    }

    {
        extern unsigned char *data_spell_b_wav_start_
           asm("data_spell_b_wav_start_");
        extern unsigned char *data_spell_b_wav_end_
           asm("data_spell_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_spell_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_spell_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/spell_b.wav"] = r;
    }

    {
        extern unsigned char *data___lightning_b_wav_start_
           asm("data___lightning_b_wav_start_");
        extern unsigned char *data___lightning_b_wav_end_
           asm("data___lightning_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___lightning_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___lightning_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._lightning_b.wav"] = r;
    }

    {
        extern unsigned char *data___laser_b_wav_start_
           asm("data___laser_b_wav_start_");
        extern unsigned char *data___laser_b_wav_end_
           asm("data___laser_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___laser_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___laser_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._laser_b.wav"] = r;
    }

    {
        extern unsigned char *data___heal_b_wav_start_
           asm("data___heal_b_wav_start_");
        extern unsigned char *data___heal_b_wav_end_
           asm("data___heal_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___heal_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___heal_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._heal_b.wav"] = r;
    }

    {
        extern unsigned char *data_spell_a_wav_start_
           asm("data_spell_a_wav_start_");
        extern unsigned char *data_spell_a_wav_end_
           asm("data_spell_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_spell_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_spell_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/spell_a.wav"] = r;
    }

    {
        extern unsigned char *data_shoot_b_wav_start_
           asm("data_shoot_b_wav_start_");
        extern unsigned char *data_shoot_b_wav_end_
           asm("data_shoot_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_shoot_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_shoot_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/shoot_b.wav"] = r;
    }

    {
        extern unsigned char *data_bazooka_wav_start_
           asm("data_bazooka_wav_start_");
        extern unsigned char *data_bazooka_wav_end_
           asm("data_bazooka_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bazooka_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bazooka_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/bazooka.wav"] = r;
    }

    {
        extern unsigned char *data___spell_a_wav_start_
           asm("data___spell_a_wav_start_");
        extern unsigned char *data___spell_a_wav_end_
           asm("data___spell_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___spell_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___spell_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._spell_a.wav"] = r;
    }

    {
        extern unsigned char *data_laser_b_wav_start_
           asm("data_laser_b_wav_start_");
        extern unsigned char *data_laser_b_wav_end_
           asm("data_laser_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_laser_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_laser_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/laser_b.wav"] = r;
    }

    {
        extern unsigned char *data___shotgun_wav_start_
           asm("data___shotgun_wav_start_");
        extern unsigned char *data___shotgun_wav_end_
           asm("data___shotgun_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___shotgun_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___shotgun_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._shotgun.wav"] = r;
    }

    {
        extern unsigned char *data___summon_wav_start_
           asm("data___summon_wav_start_");
        extern unsigned char *data___summon_wav_end_
           asm("data___summon_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___summon_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___summon_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._summon.wav"] = r;
    }

    {
        extern unsigned char *data___disarm_multi_a_wav_start_
           asm("data___disarm_multi_a_wav_start_");
        extern unsigned char *data___disarm_multi_a_wav_end_
           asm("data___disarm_multi_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___disarm_multi_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___disarm_multi_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._disarm_multi_a.wav"] = r;
    }

    {
        extern unsigned char *data___jump_a_wav_start_
           asm("data___jump_a_wav_start_");
        extern unsigned char *data___jump_a_wav_end_
           asm("data___jump_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___jump_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___jump_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._jump_a.wav"] = r;
    }

    {
        extern unsigned char *data_attack_b_wav_start_
           asm("data_attack_b_wav_start_");
        extern unsigned char *data_attack_b_wav_end_
           asm("data_attack_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_attack_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_attack_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/attack_b.wav"] = r;
    }

    {
        extern unsigned char *data_disarm_success_wav_start_
           asm("data_disarm_success_wav_start_");
        extern unsigned char *data_disarm_success_wav_end_
           asm("data_disarm_success_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_disarm_success_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_disarm_success_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/disarm_success.wav"] = r;
    }

    {
        extern unsigned char *data_lightning_b_wav_start_
           asm("data_lightning_b_wav_start_");
        extern unsigned char *data_lightning_b_wav_end_
           asm("data_lightning_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_lightning_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_lightning_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/lightning_b.wav"] = r;
    }

    {
        extern unsigned char *data_fire_b_wav_start_
           asm("data_fire_b_wav_start_");
        extern unsigned char *data_fire_b_wav_end_
           asm("data_fire_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_fire_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_fire_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/fire_b.wav"] = r;
    }

    {
        extern unsigned char *data_special_b_wav_start_
           asm("data_special_b_wav_start_");
        extern unsigned char *data_special_b_wav_end_
           asm("data_special_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_special_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_special_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/special_b.wav"] = r;
    }

    {
        extern unsigned char *data___telepathy_wav_start_
           asm("data___telepathy_wav_start_");
        extern unsigned char *data___telepathy_wav_end_
           asm("data___telepathy_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___telepathy_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___telepathy_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._telepathy.wav"] = r;
    }

    {
        extern unsigned char *data_heal_a_wav_start_
           asm("data_heal_a_wav_start_");
        extern unsigned char *data_heal_a_wav_end_
           asm("data_heal_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_heal_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_heal_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/heal_a.wav"] = r;
    }

    {
        extern unsigned char *data_woosh_b_wav_start_
           asm("data_woosh_b_wav_start_");
        extern unsigned char *data_woosh_b_wav_end_
           asm("data_woosh_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_woosh_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_woosh_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/woosh_b.wav"] = r;
    }

    {
        extern unsigned char *data_heal_b_wav_start_
           asm("data_heal_b_wav_start_");
        extern unsigned char *data_heal_b_wav_end_
           asm("data_heal_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_heal_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_heal_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/heal_b.wav"] = r;
    }

    {
        extern unsigned char *data___teleport_wav_start_
           asm("data___teleport_wav_start_");
        extern unsigned char *data___teleport_wav_end_
           asm("data___teleport_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___teleport_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___teleport_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._teleport.wav"] = r;
    }

    {
        extern unsigned char *data_fire_c_wav_start_
           asm("data_fire_c_wav_start_");
        extern unsigned char *data_fire_c_wav_end_
           asm("data_fire_c_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_fire_c_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_fire_c_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/fire_c.wav"] = r;
    }

    {
        extern unsigned char *data___fire_a_wav_start_
           asm("data___fire_a_wav_start_");
        extern unsigned char *data___fire_a_wav_end_
           asm("data___fire_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___fire_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___fire_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._fire_a.wav"] = r;
    }

    {
        extern unsigned char *data___disarm_success_wav_start_
           asm("data___disarm_success_wav_start_");
        extern unsigned char *data___disarm_success_wav_end_
           asm("data___disarm_success_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___disarm_success_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___disarm_success_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._disarm_success.wav"] = r;
    }

    {
        extern unsigned char *data_woosh_a_wav_start_
           asm("data_woosh_a_wav_start_");
        extern unsigned char *data_woosh_a_wav_end_
           asm("data_woosh_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_woosh_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_woosh_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/woosh_a.wav"] = r;
    }

    {
        extern unsigned char *data___woosh_a_wav_start_
           asm("data___woosh_a_wav_start_");
        extern unsigned char *data___woosh_a_wav_end_
           asm("data___woosh_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___woosh_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___woosh_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._woosh_a.wav"] = r;
    }

    {
        extern unsigned char *data_shoot_a_wav_start_
           asm("data_shoot_a_wav_start_");
        extern unsigned char *data_shoot_a_wav_end_
           asm("data_shoot_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_shoot_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_shoot_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/shoot_a.wav"] = r;
    }

    {
        extern unsigned char *data_lightning_a_wav_start_
           asm("data_lightning_a_wav_start_");
        extern unsigned char *data_lightning_a_wav_end_
           asm("data_lightning_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_lightning_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_lightning_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/lightning_a.wav"] = r;
    }

    {
        extern unsigned char *data_attack_a_wav_start_
           asm("data_attack_a_wav_start_");
        extern unsigned char *data_attack_a_wav_end_
           asm("data_attack_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_attack_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_attack_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/attack_a.wav"] = r;
    }

    {
        extern unsigned char *data___spell_b_wav_start_
           asm("data___spell_b_wav_start_");
        extern unsigned char *data___spell_b_wav_end_
           asm("data___spell_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___spell_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___spell_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._spell_b.wav"] = r;
    }

    {
        extern unsigned char *data_jump_b_wav_start_
           asm("data_jump_b_wav_start_");
        extern unsigned char *data_jump_b_wav_end_
           asm("data_jump_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_jump_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_jump_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/jump_b.wav"] = r;
    }

    {
        extern unsigned char *data_disarm_multi_a_wav_start_
           asm("data_disarm_multi_a_wav_start_");
        extern unsigned char *data_disarm_multi_a_wav_end_
           asm("data_disarm_multi_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_disarm_multi_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_disarm_multi_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/disarm_multi_a.wav"] = r;
    }

    {
        extern unsigned char *data_sorcery_wav_start_
           asm("data_sorcery_wav_start_");
        extern unsigned char *data_sorcery_wav_end_
           asm("data_sorcery_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_sorcery_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_sorcery_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/sorcery.wav"] = r;
    }

    {
        extern unsigned char *data_disarm_multi_b_wav_start_
           asm("data_disarm_multi_b_wav_start_");
        extern unsigned char *data_disarm_multi_b_wav_end_
           asm("data_disarm_multi_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_disarm_multi_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_disarm_multi_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/disarm_multi_b.wav"] = r;
    }

    {
        extern unsigned char *data___attack_a_wav_start_
           asm("data___attack_a_wav_start_");
        extern unsigned char *data___attack_a_wav_end_
           asm("data___attack_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___attack_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___attack_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._attack_a.wav"] = r;
    }

    {
        extern unsigned char *data___fire_b_wav_start_
           asm("data___fire_b_wav_start_");
        extern unsigned char *data___fire_b_wav_end_
           asm("data___fire_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___fire_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___fire_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._fire_b.wav"] = r;
    }

    {
        extern unsigned char *data___jump_b_wav_start_
           asm("data___jump_b_wav_start_");
        extern unsigned char *data___jump_b_wav_end_
           asm("data___jump_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___jump_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___jump_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._jump_b.wav"] = r;
    }

    {
        extern unsigned char *data_fire_a_wav_start_
           asm("data_fire_a_wav_start_");
        extern unsigned char *data_fire_a_wav_end_
           asm("data_fire_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_fire_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_fire_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/fire_a.wav"] = r;
    }

    {
        extern unsigned char *data___laser_a_wav_start_
           asm("data___laser_a_wav_start_");
        extern unsigned char *data___laser_a_wav_end_
           asm("data___laser_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___laser_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___laser_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._laser_a.wav"] = r;
    }

    {
        extern unsigned char *data___woosh_b_wav_start_
           asm("data___woosh_b_wav_start_");
        extern unsigned char *data___woosh_b_wav_end_
           asm("data___woosh_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___woosh_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___woosh_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._woosh_b.wav"] = r;
    }

    {
        extern unsigned char *data___special_b_wav_start_
           asm("data___special_b_wav_start_");
        extern unsigned char *data___special_b_wav_end_
           asm("data___special_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___special_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___special_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._special_b.wav"] = r;
    }

    {
        extern unsigned char *data_disarm_single_wav_start_
           asm("data_disarm_single_wav_start_");
        extern unsigned char *data_disarm_single_wav_end_
           asm("data_disarm_single_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_disarm_single_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_disarm_single_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/disarm_single.wav"] = r;
    }

    {
        extern unsigned char *data_shotgun_wav_start_
           asm("data_shotgun_wav_start_");
        extern unsigned char *data_shotgun_wav_end_
           asm("data_shotgun_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_shotgun_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_shotgun_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/shotgun.wav"] = r;
    }

    {
        extern unsigned char *data___lightning_a_wav_start_
           asm("data___lightning_a_wav_start_");
        extern unsigned char *data___lightning_a_wav_end_
           asm("data___lightning_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___lightning_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___lightning_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._lightning_a.wav"] = r;
    }

    {
        extern unsigned char *data___fire_c_wav_start_
           asm("data___fire_c_wav_start_");
        extern unsigned char *data___fire_c_wav_end_
           asm("data___fire_c_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___fire_c_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___fire_c_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._fire_c.wav"] = r;
    }

    {
        extern unsigned char *data___special_a_wav_start_
           asm("data___special_a_wav_start_");
        extern unsigned char *data___special_a_wav_end_
           asm("data___special_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___special_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___special_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._special_a.wav"] = r;
    }

    {
        extern unsigned char *data_teleport_wav_start_
           asm("data_teleport_wav_start_");
        extern unsigned char *data_teleport_wav_end_
           asm("data_teleport_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_teleport_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_teleport_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/teleport.wav"] = r;
    }

    {
        extern unsigned char *data___reload_wav_start_
           asm("data___reload_wav_start_");
        extern unsigned char *data___reload_wav_end_
           asm("data___reload_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___reload_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___reload_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._reload.wav"] = r;
    }

    {
        extern unsigned char *data___disarm_multi_b_wav_start_
           asm("data___disarm_multi_b_wav_start_");
        extern unsigned char *data___disarm_multi_b_wav_end_
           asm("data___disarm_multi_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___disarm_multi_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___disarm_multi_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._disarm_multi_b.wav"] = r;
    }

    {
        extern unsigned char *data_swing_wav_start_
           asm("data_swing_wav_start_");
        extern unsigned char *data_swing_wav_end_
           asm("data_swing_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_swing_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_swing_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/swing.wav"] = r;
    }

    {
        extern unsigned char *data_blaster_wav_start_
           asm("data_blaster_wav_start_");
        extern unsigned char *data_blaster_wav_end_
           asm("data_blaster_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_blaster_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_blaster_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/blaster.wav"] = r;
    }

    {
        extern unsigned char *data_special_a_wav_start_
           asm("data_special_a_wav_start_");
        extern unsigned char *data_special_a_wav_end_
           asm("data_special_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_special_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_special_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/special_a.wav"] = r;
    }

    {
        extern unsigned char *data___attack_b_wav_start_
           asm("data___attack_b_wav_start_");
        extern unsigned char *data___attack_b_wav_end_
           asm("data___attack_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___attack_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___attack_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._attack_b.wav"] = r;
    }

    {
        extern unsigned char *data___sorcery_wav_start_
           asm("data___sorcery_wav_start_");
        extern unsigned char *data___sorcery_wav_end_
           asm("data___sorcery_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___sorcery_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___sorcery_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._sorcery.wav"] = r;
    }

    {
        extern unsigned char *data___shoot_b_wav_start_
           asm("data___shoot_b_wav_start_");
        extern unsigned char *data___shoot_b_wav_end_
           asm("data___shoot_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___shoot_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___shoot_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._shoot_b.wav"] = r;
    }

    {
        extern unsigned char *data_summon_wav_start_
           asm("data_summon_wav_start_");
        extern unsigned char *data_summon_wav_end_
           asm("data_summon_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_summon_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_summon_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/summon.wav"] = r;
    }

    {
        extern unsigned char *data___heal_a_wav_start_
           asm("data___heal_a_wav_start_");
        extern unsigned char *data___heal_a_wav_end_
           asm("data___heal_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___heal_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___heal_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._heal_a.wav"] = r;
    }

    {
        extern unsigned char *data___blaster_wav_start_
           asm("data___blaster_wav_start_");
        extern unsigned char *data___blaster_wav_end_
           asm("data___blaster_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___blaster_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___blaster_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._blaster.wav"] = r;
    }

    {
        extern unsigned char *data_reload_wav_start_
           asm("data_reload_wav_start_");
        extern unsigned char *data_reload_wav_end_
           asm("data_reload_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_reload_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_reload_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/reload.wav"] = r;
    }

    {
        extern unsigned char *data_telepathy_wav_start_
           asm("data_telepathy_wav_start_");
        extern unsigned char *data_telepathy_wav_end_
           asm("data_telepathy_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_telepathy_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_telepathy_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/telepathy.wav"] = r;
    }

    {
        extern unsigned char *data_jump_a_wav_start_
           asm("data_jump_a_wav_start_");
        extern unsigned char *data_jump_a_wav_end_
           asm("data_jump_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_jump_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_jump_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/jump_a.wav"] = r;
    }

    {
        extern unsigned char *data_laser_a_wav_start_
           asm("data_laser_a_wav_start_");
        extern unsigned char *data_laser_a_wav_end_
           asm("data_laser_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_laser_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_laser_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/laser_a.wav"] = r;
    }

    {
        extern unsigned char *data___bazooka_wav_start_
           asm("data___bazooka_wav_start_");
        extern unsigned char *data___bazooka_wav_end_
           asm("data___bazooka_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___bazooka_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___bazooka_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/abilities/._bazooka.wav"] = r;
    }

    {
        extern unsigned char *data_slime4_wav_start_
           asm("data_slime4_wav_start_");
        extern unsigned char *data_slime4_wav_end_
           asm("data_slime4_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime4_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime4_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime4.wav"] = r;
    }

    {
        extern unsigned char *data_snake_wav_start_
           asm("data_snake_wav_start_");
        extern unsigned char *data_snake_wav_end_
           asm("data_snake_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_snake_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_snake_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/snake.wav"] = r;
    }

    {
        extern unsigned char *data___mouse_wav_start_
           asm("data___mouse_wav_start_");
        extern unsigned char *data___mouse_wav_end_
           asm("data___mouse_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___mouse_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___mouse_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._mouse.wav"] = r;
    }

    {
        extern unsigned char *data_beetle_wav_start_
           asm("data_beetle_wav_start_");
        extern unsigned char *data_beetle_wav_end_
           asm("data_beetle_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_beetle_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_beetle_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/beetle.wav"] = r;
    }

    {
        extern unsigned char *data_mouse_wav_start_
           asm("data_mouse_wav_start_");
        extern unsigned char *data_mouse_wav_end_
           asm("data_mouse_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_mouse_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_mouse_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/mouse.wav"] = r;
    }

    {
        extern unsigned char *data___beetle_wav_start_
           asm("data___beetle_wav_start_");
        extern unsigned char *data___beetle_wav_end_
           asm("data___beetle_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___beetle_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___beetle_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._beetle.wav"] = r;
    }

    {
        extern unsigned char *data_bird_wav_start_
           asm("data_bird_wav_start_");
        extern unsigned char *data_bird_wav_end_
           asm("data_bird_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bird_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bird_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/bird.wav"] = r;
    }

    {
        extern unsigned char *data_bones1_wav_start_
           asm("data_bones1_wav_start_");
        extern unsigned char *data_bones1_wav_end_
           asm("data_bones1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bones1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bones1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/bones1.wav"] = r;
    }

    {
        extern unsigned char *data_growl9_wav_start_
           asm("data_growl9_wav_start_");
        extern unsigned char *data_growl9_wav_end_
           asm("data_growl9_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl9_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl9_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl9.wav"] = r;
    }

    {
        extern unsigned char *data_growl6_wav_start_
           asm("data_growl6_wav_start_");
        extern unsigned char *data_growl6_wav_end_
           asm("data_growl6_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl6_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl6_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl6.wav"] = r;
    }

    {
        extern unsigned char *data_growl3_wav_start_
           asm("data_growl3_wav_start_");
        extern unsigned char *data_growl3_wav_end_
           asm("data_growl3_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl3_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl3_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl3.wav"] = r;
    }

    {
        extern unsigned char *data_growl5_wav_start_
           asm("data_growl5_wav_start_");
        extern unsigned char *data_growl5_wav_end_
           asm("data_growl5_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl5_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl5_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl5.wav"] = r;
    }

    {
        extern unsigned char *data_slime2_wav_start_
           asm("data_slime2_wav_start_");
        extern unsigned char *data_slime2_wav_end_
           asm("data_slime2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime2.wav"] = r;
    }

    {
        extern unsigned char *data_slime9_wav_start_
           asm("data_slime9_wav_start_");
        extern unsigned char *data_slime9_wav_end_
           asm("data_slime9_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime9_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime9_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime9.wav"] = r;
    }

    {
        extern unsigned char *data_hiss7_wav_start_
           asm("data_hiss7_wav_start_");
        extern unsigned char *data_hiss7_wav_end_
           asm("data_hiss7_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss7_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss7_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss7.wav"] = r;
    }

    {
        extern unsigned char *data___mystical_wav_start_
           asm("data___mystical_wav_start_");
        extern unsigned char *data___mystical_wav_end_
           asm("data___mystical_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___mystical_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___mystical_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._mystical.wav"] = r;
    }

    {
        extern unsigned char *data_slime7_wav_start_
           asm("data_slime7_wav_start_");
        extern unsigned char *data_slime7_wav_end_
           asm("data_slime7_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime7_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime7_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime7.wav"] = r;
    }

    {
        extern unsigned char *data___bird_wav_start_
           asm("data___bird_wav_start_");
        extern unsigned char *data___bird_wav_end_
           asm("data___bird_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___bird_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___bird_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._bird.wav"] = r;
    }

    {
        extern unsigned char *data_swarm_wav_start_
           asm("data_swarm_wav_start_");
        extern unsigned char *data_swarm_wav_end_
           asm("data_swarm_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_swarm_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_swarm_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/swarm.wav"] = r;
    }

    {
        extern unsigned char *data_hiss6_wav_start_
           asm("data_hiss6_wav_start_");
        extern unsigned char *data_hiss6_wav_end_
           asm("data_hiss6_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss6_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss6_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss6.wav"] = r;
    }

    {
        extern unsigned char *data___snake_wav_start_
           asm("data___snake_wav_start_");
        extern unsigned char *data___snake_wav_end_
           asm("data___snake_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___snake_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___snake_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._snake.wav"] = r;
    }

    {
        extern unsigned char *data___claw_wav_start_
           asm("data___claw_wav_start_");
        extern unsigned char *data___claw_wav_end_
           asm("data___claw_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___claw_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___claw_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._claw.wav"] = r;
    }

    {
        extern unsigned char *data_76962__michel88__deaths_wav_start_
           asm("data_76962__michel88__deaths_wav_start_");
        extern unsigned char *data_76962__michel88__deaths_wav_end_
           asm("data_76962__michel88__deaths_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_76962__michel88__deaths_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_76962__michel88__deaths_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/76962__michel88__deaths.wav"] = r;
    }

    {
        extern unsigned char *data_hiss8_wav_start_
           asm("data_hiss8_wav_start_");
        extern unsigned char *data_hiss8_wav_end_
           asm("data_hiss8_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss8_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss8_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss8.wav"] = r;
    }

    {
        extern unsigned char *data_hiss4_wav_start_
           asm("data_hiss4_wav_start_");
        extern unsigned char *data_hiss4_wav_end_
           asm("data_hiss4_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss4_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss4_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss4.wav"] = r;
    }

    {
        extern unsigned char *data_slime5_wav_start_
           asm("data_slime5_wav_start_");
        extern unsigned char *data_slime5_wav_end_
           asm("data_slime5_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime5_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime5_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime5.wav"] = r;
    }

    {
        extern unsigned char *data_growl4_wav_start_
           asm("data_growl4_wav_start_");
        extern unsigned char *data_growl4_wav_end_
           asm("data_growl4_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl4_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl4_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl4.wav"] = r;
    }

    {
        extern unsigned char *data___76962__michel88__deaths_wav_start_
           asm("data___76962__michel88__deaths_wav_start_");
        extern unsigned char *data___76962__michel88__deaths_wav_end_
           asm("data___76962__michel88__deaths_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___76962__michel88__deaths_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___76962__michel88__deaths_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._76962__michel88__deaths.wav"] = r;
    }

    {
        extern unsigned char *data_hiss1_wav_start_
           asm("data_hiss1_wav_start_");
        extern unsigned char *data_hiss1_wav_end_
           asm("data_hiss1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss1.wav"] = r;
    }

    {
        extern unsigned char *data_hiss5_wav_start_
           asm("data_hiss5_wav_start_");
        extern unsigned char *data_hiss5_wav_end_
           asm("data_hiss5_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss5_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss5_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss5.wav"] = r;
    }

    {
        extern unsigned char *data_growl10_wav_start_
           asm("data_growl10_wav_start_");
        extern unsigned char *data_growl10_wav_end_
           asm("data_growl10_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl10_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl10_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl10.wav"] = r;
    }

    {
        extern unsigned char *data_slime3_wav_start_
           asm("data_slime3_wav_start_");
        extern unsigned char *data_slime3_wav_end_
           asm("data_slime3_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime3_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime3_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime3.wav"] = r;
    }

    {
        extern unsigned char *data_23733__tim_kahn__squeakyrat_wav_start_
           asm("data_23733__tim_kahn__squeakyrat_wav_start_");
        extern unsigned char *data_23733__tim_kahn__squeakyrat_wav_end_
           asm("data_23733__tim_kahn__squeakyrat_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_23733__tim_kahn__squeakyrat_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_23733__tim_kahn__squeakyrat_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/23733__tim-kahn__squeakyrat.wav"] = r;
    }

    {
        extern unsigned char *data_skeleton_wav_start_
           asm("data_skeleton_wav_start_");
        extern unsigned char *data_skeleton_wav_end_
           asm("data_skeleton_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_skeleton_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_skeleton_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/skeleton.wav"] = r;
    }

    {
        extern unsigned char *data___swarm_wav_start_
           asm("data___swarm_wav_start_");
        extern unsigned char *data___swarm_wav_end_
           asm("data___swarm_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___swarm_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___swarm_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._swarm.wav"] = r;
    }

    {
        extern unsigned char *data_slime1_wav_start_
           asm("data_slime1_wav_start_");
        extern unsigned char *data_slime1_wav_end_
           asm("data_slime1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime1.wav"] = r;
    }

    {
        extern unsigned char *data_growl2_wav_start_
           asm("data_growl2_wav_start_");
        extern unsigned char *data_growl2_wav_end_
           asm("data_growl2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl2.wav"] = r;
    }

    {
        extern unsigned char *data___frog_wav_start_
           asm("data___frog_wav_start_");
        extern unsigned char *data___frog_wav_end_
           asm("data___frog_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___frog_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___frog_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._frog.wav"] = r;
    }

    {
        extern unsigned char *data___jelly_wav_start_
           asm("data___jelly_wav_start_");
        extern unsigned char *data___jelly_wav_end_
           asm("data___jelly_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___jelly_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___jelly_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._jelly.wav"] = r;
    }

    {
        extern unsigned char *data_slime8_wav_start_
           asm("data_slime8_wav_start_");
        extern unsigned char *data_slime8_wav_end_
           asm("data_slime8_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime8_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime8_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime8.wav"] = r;
    }

    {
        extern unsigned char *data_hiss9_wav_start_
           asm("data_hiss9_wav_start_");
        extern unsigned char *data_hiss9_wav_end_
           asm("data_hiss9_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss9_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss9_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss9.wav"] = r;
    }

    {
        extern unsigned char *data_hiss10_wav_start_
           asm("data_hiss10_wav_start_");
        extern unsigned char *data_hiss10_wav_end_
           asm("data_hiss10_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss10_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss10_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss10.wav"] = r;
    }

    {
        extern unsigned char *data_frog_wav_start_
           asm("data_frog_wav_start_");
        extern unsigned char *data_frog_wav_end_
           asm("data_frog_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_frog_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_frog_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/frog.wav"] = r;
    }

    {
        extern unsigned char *data_bones2_wav_start_
           asm("data_bones2_wav_start_");
        extern unsigned char *data_bones2_wav_end_
           asm("data_bones2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bones2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bones2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/bones2.wav"] = r;
    }

    {
        extern unsigned char *data___wings_wav_start_
           asm("data___wings_wav_start_");
        extern unsigned char *data___wings_wav_end_
           asm("data___wings_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___wings_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___wings_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._wings.wav"] = r;
    }

    {
        extern unsigned char *data___skeleton_wav_start_
           asm("data___skeleton_wav_start_");
        extern unsigned char *data___skeleton_wav_end_
           asm("data___skeleton_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___skeleton_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___skeleton_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/._skeleton.wav"] = r;
    }

    {
        extern unsigned char *data_growl8_wav_start_
           asm("data_growl8_wav_start_");
        extern unsigned char *data_growl8_wav_end_
           asm("data_growl8_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl8_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl8_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl8.wav"] = r;
    }

    {
        extern unsigned char *data_wings_wav_start_
           asm("data_wings_wav_start_");
        extern unsigned char *data_wings_wav_end_
           asm("data_wings_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_wings_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_wings_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/wings.wav"] = r;
    }

    {
        extern unsigned char *data_growl7_wav_start_
           asm("data_growl7_wav_start_");
        extern unsigned char *data_growl7_wav_end_
           asm("data_growl7_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl7_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl7_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl7.wav"] = r;
    }

    {
        extern unsigned char *data_mystical_wav_start_
           asm("data_mystical_wav_start_");
        extern unsigned char *data_mystical_wav_end_
           asm("data_mystical_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_mystical_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_mystical_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/mystical.wav"] = r;
    }

    {
        extern unsigned char *data_hiss2_wav_start_
           asm("data_hiss2_wav_start_");
        extern unsigned char *data_hiss2_wav_end_
           asm("data_hiss2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss2.wav"] = r;
    }

    {
        extern unsigned char *data_148975__adam_n__squelch_1_wav_start_
           asm("data_148975__adam_n__squelch_1_wav_start_");
        extern unsigned char *data_148975__adam_n__squelch_1_wav_end_
           asm("data_148975__adam_n__squelch_1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_148975__adam_n__squelch_1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_148975__adam_n__squelch_1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/148975__adam_n__squelch_1.wav"] = r;
    }

    {
        extern unsigned char *data_slime6_wav_start_
           asm("data_slime6_wav_start_");
        extern unsigned char *data_slime6_wav_end_
           asm("data_slime6_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_slime6_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_slime6_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/slime6.wav"] = r;
    }

    {
        extern unsigned char *data_claw_wav_start_
           asm("data_claw_wav_start_");
        extern unsigned char *data_claw_wav_end_
           asm("data_claw_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_claw_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_claw_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/claw.wav"] = r;
    }

    {
        extern unsigned char *data_jelly_wav_start_
           asm("data_jelly_wav_start_");
        extern unsigned char *data_jelly_wav_end_
           asm("data_jelly_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_jelly_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_jelly_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/jelly.wav"] = r;
    }

    {
        extern unsigned char *data_growl1_wav_start_
           asm("data_growl1_wav_start_");
        extern unsigned char *data_growl1_wav_end_
           asm("data_growl1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_growl1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_growl1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/growl1.wav"] = r;
    }

    {
        extern unsigned char *data_hiss3_wav_start_
           asm("data_hiss3_wav_start_");
        extern unsigned char *data_hiss3_wav_end_
           asm("data_hiss3_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hiss3_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hiss3_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/creatures/hiss3.wav"] = r;
    }

    {
        extern unsigned char *data___pit_trap_fall_wav_start_
           asm("data___pit_trap_fall_wav_start_");
        extern unsigned char *data___pit_trap_fall_wav_end_
           asm("data___pit_trap_fall_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___pit_trap_fall_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___pit_trap_fall_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._pit_trap_fall.wav"] = r;
    }

    {
        extern unsigned char *data___spike_trap_b_wav_start_
           asm("data___spike_trap_b_wav_start_");
        extern unsigned char *data___spike_trap_b_wav_end_
           asm("data___spike_trap_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___spike_trap_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___spike_trap_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._spike_trap_b.wav"] = r;
    }

    {
        extern unsigned char *data_magic_dust_a_wav_start_
           asm("data_magic_dust_a_wav_start_");
        extern unsigned char *data_magic_dust_a_wav_end_
           asm("data_magic_dust_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_magic_dust_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_magic_dust_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/magic_dust_a.wav"] = r;
    }

    {
        extern unsigned char *data___magic_crumble_wav_start_
           asm("data___magic_crumble_wav_start_");
        extern unsigned char *data___magic_crumble_wav_end_
           asm("data___magic_crumble_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___magic_crumble_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___magic_crumble_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._magic_crumble.wav"] = r;
    }

    {
        extern unsigned char *data_434462__dersuperanton__getting_hit_hugh_wav_start_
           asm("data_434462__dersuperanton__getting_hit_hugh_wav_start_");
        extern unsigned char *data_434462__dersuperanton__getting_hit_hugh_wav_end_
           asm("data_434462__dersuperanton__getting_hit_hugh_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_434462__dersuperanton__getting_hit_hugh_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_434462__dersuperanton__getting_hit_hugh_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/434462__dersuperanton__getting-hit-hugh.wav"] = r;
    }

    {
        extern unsigned char *data___hit_wav_start_
           asm("data___hit_wav_start_");
        extern unsigned char *data___hit_wav_end_
           asm("data___hit_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___hit_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___hit_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._hit.wav"] = r;
    }

    {
        extern unsigned char *data_437650__dersuperanton__getting_hit_damage_scream_wav_start_
           asm("data_437650__dersuperanton__getting_hit_damage_scream_wav_start_");
        extern unsigned char *data_437650__dersuperanton__getting_hit_damage_scream_wav_end_
           asm("data_437650__dersuperanton__getting_hit_damage_scream_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_437650__dersuperanton__getting_hit_damage_scream_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_437650__dersuperanton__getting_hit_damage_scream_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/437650__dersuperanton__getting-hit-damage-scream.wav"] = r;
    }

    {
        extern unsigned char *data_sear_wav_start_
           asm("data_sear_wav_start_");
        extern unsigned char *data_sear_wav_end_
           asm("data_sear_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_sear_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_sear_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/sear.wav"] = r;
    }

    {
        extern unsigned char *data___437650__dersuperanton__getting_hit_damage_scream_wav_start_
           asm("data___437650__dersuperanton__getting_hit_damage_scream_wav_start_");
        extern unsigned char *data___437650__dersuperanton__getting_hit_damage_scream_wav_end_
           asm("data___437650__dersuperanton__getting_hit_damage_scream_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___437650__dersuperanton__getting_hit_damage_scream_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___437650__dersuperanton__getting_hit_damage_scream_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._437650__dersuperanton__getting-hit-damage-scream.wav"] = r;
    }

    {
        extern unsigned char *data_spike_trap_a_wav_start_
           asm("data_spike_trap_a_wav_start_");
        extern unsigned char *data_spike_trap_a_wav_end_
           asm("data_spike_trap_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_spike_trap_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_spike_trap_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/spike_trap_a.wav"] = r;
    }

    {
        extern unsigned char *data___boom_b_wav_start_
           asm("data___boom_b_wav_start_");
        extern unsigned char *data___boom_b_wav_end_
           asm("data___boom_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___boom_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___boom_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._boom_b.wav"] = r;
    }

    {
        extern unsigned char *data_257709__vmgraw__grunt_2_wav_start_
           asm("data_257709__vmgraw__grunt_2_wav_start_");
        extern unsigned char *data_257709__vmgraw__grunt_2_wav_end_
           asm("data_257709__vmgraw__grunt_2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_257709__vmgraw__grunt_2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_257709__vmgraw__grunt_2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/257709__vmgraw__grunt-2.wav"] = r;
    }

    {
        extern unsigned char *data_splash3_wav_start_
           asm("data_splash3_wav_start_");
        extern unsigned char *data_splash3_wav_end_
           asm("data_splash3_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_splash3_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_splash3_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/splash3.wav"] = r;
    }

    {
        extern unsigned char *data___boom_a_wav_start_
           asm("data___boom_a_wav_start_");
        extern unsigned char *data___boom_a_wav_end_
           asm("data___boom_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___boom_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___boom_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._boom_a.wav"] = r;
    }

    {
        extern unsigned char *data_437653__dersuperanton__moan_male_beat_punch_wav_start_
           asm("data_437653__dersuperanton__moan_male_beat_punch_wav_start_");
        extern unsigned char *data_437653__dersuperanton__moan_male_beat_punch_wav_end_
           asm("data_437653__dersuperanton__moan_male_beat_punch_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_437653__dersuperanton__moan_male_beat_punch_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_437653__dersuperanton__moan_male_beat_punch_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/437653__dersuperanton__moan-male-beat-punch.wav"] = r;
    }

    {
        extern unsigned char *data___434462__dersuperanton__getting_hit_hugh_wav_start_
           asm("data___434462__dersuperanton__getting_hit_hugh_wav_start_");
        extern unsigned char *data___434462__dersuperanton__getting_hit_hugh_wav_end_
           asm("data___434462__dersuperanton__getting_hit_hugh_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___434462__dersuperanton__getting_hit_hugh_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___434462__dersuperanton__getting_hit_hugh_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._434462__dersuperanton__getting-hit-hugh.wav"] = r;
    }

    {
        extern unsigned char *data___443293__deathscyp__wood_break_wav_start_
           asm("data___443293__deathscyp__wood_break_wav_start_");
        extern unsigned char *data___443293__deathscyp__wood_break_wav_end_
           asm("data___443293__deathscyp__wood_break_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___443293__deathscyp__wood_break_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___443293__deathscyp__wood_break_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._443293__deathscyp__wood-break.wav"] = r;
    }

    {
        extern unsigned char *data_magic_dust_b_wav_start_
           asm("data_magic_dust_b_wav_start_");
        extern unsigned char *data_magic_dust_b_wav_end_
           asm("data_magic_dust_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_magic_dust_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_magic_dust_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/magic_dust_b.wav"] = r;
    }

    {
        extern unsigned char *data_magic_crumble_wav_start_
           asm("data_magic_crumble_wav_start_");
        extern unsigned char *data_magic_crumble_wav_end_
           asm("data_magic_crumble_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_magic_crumble_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_magic_crumble_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/magic_crumble.wav"] = r;
    }

    {
        extern unsigned char *data_pit_trap_damage_wav_start_
           asm("data_pit_trap_damage_wav_start_");
        extern unsigned char *data_pit_trap_damage_wav_end_
           asm("data_pit_trap_damage_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_pit_trap_damage_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_pit_trap_damage_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/pit_trap_damage.wav"] = r;
    }

    {
        extern unsigned char *data___impact_b_wav_start_
           asm("data___impact_b_wav_start_");
        extern unsigned char *data___impact_b_wav_end_
           asm("data___impact_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___impact_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___impact_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._impact_b.wav"] = r;
    }

    {
        extern unsigned char *data___magic_dust_a_wav_start_
           asm("data___magic_dust_a_wav_start_");
        extern unsigned char *data___magic_dust_a_wav_end_
           asm("data___magic_dust_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___magic_dust_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___magic_dust_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._magic_dust_a.wav"] = r;
    }

    {
        extern unsigned char *data___explosion_a_wav_start_
           asm("data___explosion_a_wav_start_");
        extern unsigned char *data___explosion_a_wav_end_
           asm("data___explosion_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___explosion_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___explosion_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._explosion_a.wav"] = r;
    }

    {
        extern unsigned char *data_door_hit1_wav_start_
           asm("data_door_hit1_wav_start_");
        extern unsigned char *data_door_hit1_wav_end_
           asm("data_door_hit1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_door_hit1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_door_hit1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/door_hit1.wav"] = r;
    }

    {
        extern unsigned char *data_splash6_wav_start_
           asm("data_splash6_wav_start_");
        extern unsigned char *data_splash6_wav_end_
           asm("data_splash6_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_splash6_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_splash6_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/splash6.wav"] = r;
    }

    {
        extern unsigned char *data_explosion_a_wav_start_
           asm("data_explosion_a_wav_start_");
        extern unsigned char *data_explosion_a_wav_end_
           asm("data_explosion_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_explosion_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_explosion_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/explosion_a.wav"] = r;
    }

    {
        extern unsigned char *data_impact_a_wav_start_
           asm("data_impact_a_wav_start_");
        extern unsigned char *data_impact_a_wav_end_
           asm("data_impact_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_impact_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_impact_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/impact_a.wav"] = r;
    }

    {
        extern unsigned char *data_explosion_e_wav_start_
           asm("data_explosion_e_wav_start_");
        extern unsigned char *data_explosion_e_wav_end_
           asm("data_explosion_e_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_explosion_e_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_explosion_e_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/explosion_e.wav"] = r;
    }

    {
        extern unsigned char *data_splash2_wav_start_
           asm("data_splash2_wav_start_");
        extern unsigned char *data_splash2_wav_end_
           asm("data_splash2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_splash2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_splash2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/splash2.wav"] = r;
    }

    {
        extern unsigned char *data_443293__deathscyp__wood_break_wav_start_
           asm("data_443293__deathscyp__wood_break_wav_start_");
        extern unsigned char *data_443293__deathscyp__wood_break_wav_end_
           asm("data_443293__deathscyp__wood_break_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_443293__deathscyp__wood_break_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_443293__deathscyp__wood_break_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/443293__deathscyp__wood-break.wav"] = r;
    }

    {
        extern unsigned char *data_area_effect_a_wav_start_
           asm("data_area_effect_a_wav_start_");
        extern unsigned char *data_area_effect_a_wav_end_
           asm("data_area_effect_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_area_effect_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_area_effect_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/area_effect_a.wav"] = r;
    }

    {
        extern unsigned char *data___magic_dust_b_wav_start_
           asm("data___magic_dust_b_wav_start_");
        extern unsigned char *data___magic_dust_b_wav_end_
           asm("data___magic_dust_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___magic_dust_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___magic_dust_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._magic_dust_b.wav"] = r;
    }

    {
        extern unsigned char *data___impact_a_wav_start_
           asm("data___impact_a_wav_start_");
        extern unsigned char *data___impact_a_wav_end_
           asm("data___impact_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___impact_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___impact_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._impact_a.wav"] = r;
    }

    {
        extern unsigned char *data_splash1_wav_start_
           asm("data_splash1_wav_start_");
        extern unsigned char *data_splash1_wav_end_
           asm("data_splash1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_splash1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_splash1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/splash1.wav"] = r;
    }

    {
        extern unsigned char *data_268227__xxchr0nosxx__swing_wav_start_
           asm("data_268227__xxchr0nosxx__swing_wav_start_");
        extern unsigned char *data_268227__xxchr0nosxx__swing_wav_end_
           asm("data_268227__xxchr0nosxx__swing_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_268227__xxchr0nosxx__swing_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_268227__xxchr0nosxx__swing_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/268227__xxchr0nosxx__swing.wav"] = r;
    }

    {
        extern unsigned char *data_59992__qubodup__swosh_sword_swing_wav_start_
           asm("data_59992__qubodup__swosh_sword_swing_wav_start_");
        extern unsigned char *data_59992__qubodup__swosh_sword_swing_wav_end_
           asm("data_59992__qubodup__swosh_sword_swing_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_59992__qubodup__swosh_sword_swing_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_59992__qubodup__swosh_sword_swing_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/59992__qubodup__swosh-sword-swing.wav"] = r;
    }

    {
        extern unsigned char *data___explosion_c_wav_start_
           asm("data___explosion_c_wav_start_");
        extern unsigned char *data___explosion_c_wav_end_
           asm("data___explosion_c_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___explosion_c_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___explosion_c_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._explosion_c.wav"] = r;
    }

    {
        extern unsigned char *data_82388__robinhood76__01308_man_hit_9_wav_start_
           asm("data_82388__robinhood76__01308_man_hit_9_wav_start_");
        extern unsigned char *data_82388__robinhood76__01308_man_hit_9_wav_end_
           asm("data_82388__robinhood76__01308_man_hit_9_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_82388__robinhood76__01308_man_hit_9_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_82388__robinhood76__01308_man_hit_9_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/82388__robinhood76__01308_man_hit_9.wav"] = r;
    }

    {
        extern unsigned char *data_impact_b_wav_start_
           asm("data_impact_b_wav_start_");
        extern unsigned char *data_impact_b_wav_end_
           asm("data_impact_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_impact_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_impact_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/impact_b.wav"] = r;
    }

    {
        extern unsigned char *data_splash4_wav_start_
           asm("data_splash4_wav_start_");
        extern unsigned char *data_splash4_wav_end_
           asm("data_splash4_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_splash4_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_splash4_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/splash4.wav"] = r;
    }

    {
        extern unsigned char *data_explosion_b_wav_start_
           asm("data_explosion_b_wav_start_");
        extern unsigned char *data_explosion_b_wav_end_
           asm("data_explosion_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_explosion_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_explosion_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/explosion_b.wav"] = r;
    }

    {
        extern unsigned char *data_hit_wav_start_
           asm("data_hit_wav_start_");
        extern unsigned char *data_hit_wav_end_
           asm("data_hit_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_hit_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_hit_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/hit.wav"] = r;
    }

    {
        extern unsigned char *data___explosion_b_wav_start_
           asm("data___explosion_b_wav_start_");
        extern unsigned char *data___explosion_b_wav_end_
           asm("data___explosion_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___explosion_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___explosion_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._explosion_b.wav"] = r;
    }

    {
        extern unsigned char *data___spike_trap_a_wav_start_
           asm("data___spike_trap_a_wav_start_");
        extern unsigned char *data___spike_trap_a_wav_end_
           asm("data___spike_trap_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___spike_trap_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___spike_trap_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._spike_trap_a.wav"] = r;
    }

    {
        extern unsigned char *data_door_hit2_wav_start_
           asm("data_door_hit2_wav_start_");
        extern unsigned char *data_door_hit2_wav_end_
           asm("data_door_hit2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_door_hit2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_door_hit2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/door_hit2.wav"] = r;
    }

    {
        extern unsigned char *data___sear_wav_start_
           asm("data___sear_wav_start_");
        extern unsigned char *data___sear_wav_end_
           asm("data___sear_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___sear_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___sear_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._sear.wav"] = r;
    }

    {
        extern unsigned char *data_spike_trap_b_wav_start_
           asm("data_spike_trap_b_wav_start_");
        extern unsigned char *data_spike_trap_b_wav_end_
           asm("data_spike_trap_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_spike_trap_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_spike_trap_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/spike_trap_b.wav"] = r;
    }

    {
        extern unsigned char *data_boom_b_wav_start_
           asm("data_boom_b_wav_start_");
        extern unsigned char *data_boom_b_wav_end_
           asm("data_boom_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_boom_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_boom_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/boom_b.wav"] = r;
    }

    {
        extern unsigned char *data_splash5_wav_start_
           asm("data_splash5_wav_start_");
        extern unsigned char *data_splash5_wav_end_
           asm("data_splash5_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_splash5_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_splash5_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/splash5.wav"] = r;
    }

    {
        extern unsigned char *data___area_effect_b_wav_start_
           asm("data___area_effect_b_wav_start_");
        extern unsigned char *data___area_effect_b_wav_end_
           asm("data___area_effect_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___area_effect_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___area_effect_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._area_effect_b.wav"] = r;
    }

    {
        extern unsigned char *data_404109__deathscyp__damage_1_wav_start_
           asm("data_404109__deathscyp__damage_1_wav_start_");
        extern unsigned char *data_404109__deathscyp__damage_1_wav_end_
           asm("data_404109__deathscyp__damage_1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_404109__deathscyp__damage_1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_404109__deathscyp__damage_1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/404109__deathscyp__damage-1.wav"] = r;
    }

    {
        extern unsigned char *data_554153__danielvj__door_open_wav_start_
           asm("data_554153__danielvj__door_open_wav_start_");
        extern unsigned char *data_554153__danielvj__door_open_wav_end_
           asm("data_554153__danielvj__door_open_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_554153__danielvj__door_open_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_554153__danielvj__door_open_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/554153__danielvj__door-open.wav"] = r;
    }

    {
        extern unsigned char *data___area_effect_a_wav_start_
           asm("data___area_effect_a_wav_start_");
        extern unsigned char *data___area_effect_a_wav_end_
           asm("data___area_effect_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___area_effect_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___area_effect_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._area_effect_a.wav"] = r;
    }

    {
        extern unsigned char *data_area_effect_b_wav_start_
           asm("data_area_effect_b_wav_start_");
        extern unsigned char *data_area_effect_b_wav_end_
           asm("data_area_effect_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_area_effect_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_area_effect_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/area_effect_b.wav"] = r;
    }

    {
        extern unsigned char *data___404109__deathscyp__damage_1_wav_start_
           asm("data___404109__deathscyp__damage_1_wav_start_");
        extern unsigned char *data___404109__deathscyp__damage_1_wav_end_
           asm("data___404109__deathscyp__damage_1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___404109__deathscyp__damage_1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___404109__deathscyp__damage_1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._404109__deathscyp__damage-1.wav"] = r;
    }

    {
        extern unsigned char *data_explosion_d_wav_start_
           asm("data_explosion_d_wav_start_");
        extern unsigned char *data_explosion_d_wav_end_
           asm("data_explosion_d_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_explosion_d_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_explosion_d_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/explosion_d.wav"] = r;
    }

    {
        extern unsigned char *data_explosion_c_wav_start_
           asm("data_explosion_c_wav_start_");
        extern unsigned char *data_explosion_c_wav_end_
           asm("data_explosion_c_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_explosion_c_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_explosion_c_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/explosion_c.wav"] = r;
    }

    {
        extern unsigned char *data_pit_trap_fall_wav_start_
           asm("data_pit_trap_fall_wav_start_");
        extern unsigned char *data_pit_trap_fall_wav_end_
           asm("data_pit_trap_fall_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_pit_trap_fall_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_pit_trap_fall_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/pit_trap_fall.wav"] = r;
    }

    {
        extern unsigned char *data_507466__danjocross__clean_fast_swoosh_wav_start_
           asm("data_507466__danjocross__clean_fast_swoosh_wav_start_");
        extern unsigned char *data_507466__danjocross__clean_fast_swoosh_wav_end_
           asm("data_507466__danjocross__clean_fast_swoosh_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_507466__danjocross__clean_fast_swoosh_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_507466__danjocross__clean_fast_swoosh_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/507466__danjocross__clean-fast-swoosh.wav"] = r;
    }

    {
        extern unsigned char *data___pit_trap_damage_wav_start_
           asm("data___pit_trap_damage_wav_start_");
        extern unsigned char *data___pit_trap_damage_wav_end_
           asm("data___pit_trap_damage_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___pit_trap_damage_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___pit_trap_damage_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/._pit_trap_damage.wav"] = r;
    }

    {
        extern unsigned char *data_boom_a_wav_start_
           asm("data_boom_a_wav_start_");
        extern unsigned char *data_boom_a_wav_end_
           asm("data_boom_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_boom_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_boom_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/impacts/boom_a.wav"] = r;
    }

    {
        extern unsigned char *data___paper_wav_start_
           asm("data___paper_wav_start_");
        extern unsigned char *data___paper_wav_end_
           asm("data___paper_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___paper_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___paper_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._paper.wav"] = r;
    }

    {
        extern unsigned char *data___new_turn_wav_start_
           asm("data___new_turn_wav_start_");
        extern unsigned char *data___new_turn_wav_end_
           asm("data___new_turn_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___new_turn_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___new_turn_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._new_turn.wav"] = r;
    }

    {
        extern unsigned char *data_bonus_wav_start_
           asm("data_bonus_wav_start_");
        extern unsigned char *data_bonus_wav_end_
           asm("data_bonus_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bonus_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bonus_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/bonus.wav"] = r;
    }

    {
        extern unsigned char *data_end_turn_wav_start_
           asm("data_end_turn_wav_start_");
        extern unsigned char *data_end_turn_wav_end_
           asm("data_end_turn_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_end_turn_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_end_turn_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/end_turn.wav"] = r;
    }

    {
        extern unsigned char *data___ding_wav_start_
           asm("data___ding_wav_start_");
        extern unsigned char *data___ding_wav_end_
           asm("data___ding_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___ding_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___ding_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._ding.wav"] = r;
    }

    {
        extern unsigned char *data_1up_a_wav_start_
           asm("data_1up_a_wav_start_");
        extern unsigned char *data_1up_a_wav_end_
           asm("data_1up_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_1up_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_1up_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/1up_a.wav"] = r;
    }

    {
        extern unsigned char *data_lose_a_wav_start_
           asm("data_lose_a_wav_start_");
        extern unsigned char *data_lose_a_wav_end_
           asm("data_lose_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_lose_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_lose_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/lose_a.wav"] = r;
    }

    {
        extern unsigned char *data_click_long_wav_start_
           asm("data_click_long_wav_start_");
        extern unsigned char *data_click_long_wav_end_
           asm("data_click_long_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_click_long_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_click_long_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/click_long.wav"] = r;
    }

    {
        extern unsigned char *data_lose_b_wav_start_
           asm("data_lose_b_wav_start_");
        extern unsigned char *data_lose_b_wav_end_
           asm("data_lose_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_lose_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_lose_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/lose_b.wav"] = r;
    }

    {
        extern unsigned char *data___1up_a_wav_start_
           asm("data___1up_a_wav_start_");
        extern unsigned char *data___1up_a_wav_end_
           asm("data___1up_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___1up_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___1up_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._1up_a.wav"] = r;
    }

    {
        extern unsigned char *data_error_wav_start_
           asm("data_error_wav_start_");
        extern unsigned char *data_error_wav_end_
           asm("data_error_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_error_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_error_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/error.wav"] = r;
    }

    {
        extern unsigned char *data_dong_wav_start_
           asm("data_dong_wav_start_");
        extern unsigned char *data_dong_wav_end_
           asm("data_dong_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_dong_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_dong_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/dong.wav"] = r;
    }

    {
        extern unsigned char *data___coin_wav_start_
           asm("data___coin_wav_start_");
        extern unsigned char *data___coin_wav_end_
           asm("data___coin_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___coin_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___coin_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._coin.wav"] = r;
    }

    {
        extern unsigned char *data_level_up_wav_start_
           asm("data_level_up_wav_start_");
        extern unsigned char *data_level_up_wav_end_
           asm("data_level_up_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_level_up_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_level_up_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/level_up.wav"] = r;
    }

    {
        extern unsigned char *data___score_wav_start_
           asm("data___score_wav_start_");
        extern unsigned char *data___score_wav_end_
           asm("data___score_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___score_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___score_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._score.wav"] = r;
    }

    {
        extern unsigned char *data___error_wav_start_
           asm("data___error_wav_start_");
        extern unsigned char *data___error_wav_end_
           asm("data___error_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___error_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___error_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._error.wav"] = r;
    }

    {
        extern unsigned char *data_score_wav_start_
           asm("data_score_wav_start_");
        extern unsigned char *data_score_wav_end_
           asm("data_score_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_score_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_score_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/score.wav"] = r;
    }

    {
        extern unsigned char *data___lose_a_wav_start_
           asm("data___lose_a_wav_start_");
        extern unsigned char *data___lose_a_wav_end_
           asm("data___lose_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___lose_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___lose_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._lose_a.wav"] = r;
    }

    {
        extern unsigned char *data_select_b_wav_start_
           asm("data_select_b_wav_start_");
        extern unsigned char *data_select_b_wav_end_
           asm("data_select_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_select_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_select_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/select_b.wav"] = r;
    }

    {
        extern unsigned char *data___lose_b_wav_start_
           asm("data___lose_b_wav_start_");
        extern unsigned char *data___lose_b_wav_end_
           asm("data___lose_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___lose_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___lose_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._lose_b.wav"] = r;
    }

    {
        extern unsigned char *data_1up_b_wav_start_
           asm("data_1up_b_wav_start_");
        extern unsigned char *data_1up_b_wav_end_
           asm("data_1up_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_1up_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_1up_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/1up_b.wav"] = r;
    }

    {
        extern unsigned char *data_181002__ueffects__s_key_wav_start_
           asm("data_181002__ueffects__s_key_wav_start_");
        extern unsigned char *data_181002__ueffects__s_key_wav_end_
           asm("data_181002__ueffects__s_key_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_181002__ueffects__s_key_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_181002__ueffects__s_key_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/181002__ueffects__s-key.wav"] = r;
    }

    {
        extern unsigned char *data___gold_wav_start_
           asm("data___gold_wav_start_");
        extern unsigned char *data___gold_wav_end_
           asm("data___gold_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___gold_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___gold_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._gold.wav"] = r;
    }

    {
        extern unsigned char *data___select_a_wav_start_
           asm("data___select_a_wav_start_");
        extern unsigned char *data___select_a_wav_end_
           asm("data___select_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___select_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___select_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._select_a.wav"] = r;
    }

    {
        extern unsigned char *data___click_wav_start_
           asm("data___click_wav_start_");
        extern unsigned char *data___click_wav_end_
           asm("data___click_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___click_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___click_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._click.wav"] = r;
    }

    {
        extern unsigned char *data_ding_wav_start_
           asm("data_ding_wav_start_");
        extern unsigned char *data_ding_wav_end_
           asm("data_ding_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ding_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ding_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/ding.wav"] = r;
    }

    {
        extern unsigned char *data___select_b_wav_start_
           asm("data___select_b_wav_start_");
        extern unsigned char *data___select_b_wav_end_
           asm("data___select_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___select_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___select_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._select_b.wav"] = r;
    }

    {
        extern unsigned char *data___level_up_wav_start_
           asm("data___level_up_wav_start_");
        extern unsigned char *data___level_up_wav_end_
           asm("data___level_up_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___level_up_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___level_up_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._level_up.wav"] = r;
    }

    {
        extern unsigned char *data_new_turn_wav_start_
           asm("data_new_turn_wav_start_");
        extern unsigned char *data_new_turn_wav_end_
           asm("data_new_turn_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_new_turn_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_new_turn_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/new_turn.wav"] = r;
    }

    {
        extern unsigned char *data_select_a_wav_start_
           asm("data_select_a_wav_start_");
        extern unsigned char *data_select_a_wav_end_
           asm("data_select_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_select_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_select_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/select_a.wav"] = r;
    }

    {
        extern unsigned char *data___click_long_wav_start_
           asm("data___click_long_wav_start_");
        extern unsigned char *data___click_long_wav_end_
           asm("data___click_long_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___click_long_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___click_long_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._click_long.wav"] = r;
    }

    {
        extern unsigned char *data___1up_b_wav_start_
           asm("data___1up_b_wav_start_");
        extern unsigned char *data___1up_b_wav_end_
           asm("data___1up_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___1up_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___1up_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._1up_b.wav"] = r;
    }

    {
        extern unsigned char *data_coin_wav_start_
           asm("data_coin_wav_start_");
        extern unsigned char *data_coin_wav_end_
           asm("data_coin_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_coin_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_coin_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/coin.wav"] = r;
    }

    {
        extern unsigned char *data___dong_wav_start_
           asm("data___dong_wav_start_");
        extern unsigned char *data___dong_wav_end_
           asm("data___dong_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___dong_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___dong_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._dong.wav"] = r;
    }

    {
        extern unsigned char *data_gold_wav_start_
           asm("data_gold_wav_start_");
        extern unsigned char *data_gold_wav_end_
           asm("data_gold_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_gold_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_gold_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/gold.wav"] = r;
    }

    {
        extern unsigned char *data_click2_wav_start_
           asm("data_click2_wav_start_");
        extern unsigned char *data_click2_wav_end_
           asm("data_click2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_click2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_click2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/click2.wav"] = r;
    }

    {
        extern unsigned char *data___bonus_wav_start_
           asm("data___bonus_wav_start_");
        extern unsigned char *data___bonus_wav_end_
           asm("data___bonus_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___bonus_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___bonus_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._bonus.wav"] = r;
    }

    {
        extern unsigned char *data_blip_wav_start_
           asm("data_blip_wav_start_");
        extern unsigned char *data_blip_wav_end_
           asm("data_blip_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_blip_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_blip_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/blip.wav"] = r;
    }

    {
        extern unsigned char *data___end_turn_wav_start_
           asm("data___end_turn_wav_start_");
        extern unsigned char *data___end_turn_wav_end_
           asm("data___end_turn_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___end_turn_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___end_turn_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._end_turn.wav"] = r;
    }

    {
        extern unsigned char *data___blip_wav_start_
           asm("data___blip_wav_start_");
        extern unsigned char *data___blip_wav_end_
           asm("data___blip_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___blip_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___blip_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/._blip.wav"] = r;
    }

    {
        extern unsigned char *data_click_wav_start_
           asm("data_click_wav_start_");
        extern unsigned char *data_click_wav_end_
           asm("data_click_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_click_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_click_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/click.wav"] = r;
    }

    {
        extern unsigned char *data_paper_wav_start_
           asm("data_paper_wav_start_");
        extern unsigned char *data_paper_wav_end_
           asm("data_paper_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_paper_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_paper_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/interface/paper.wav"] = r;
    }

    {
        extern unsigned char *data_rebound_wav_start_
           asm("data_rebound_wav_start_");
        extern unsigned char *data_rebound_wav_end_
           asm("data_rebound_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_rebound_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_rebound_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/rebound.wav"] = r;
    }

    {
        extern unsigned char *data___open_wav_start_
           asm("data___open_wav_start_");
        extern unsigned char *data___open_wav_end_
           asm("data___open_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___open_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___open_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._open.wav"] = r;
    }

    {
        extern unsigned char *data___rebound_wav_start_
           asm("data___rebound_wav_start_");
        extern unsigned char *data___rebound_wav_end_
           asm("data___rebound_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___rebound_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___rebound_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._rebound.wav"] = r;
    }

    {
        extern unsigned char *data_open_wav_start_
           asm("data_open_wav_start_");
        extern unsigned char *data_open_wav_end_
           asm("data_open_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_open_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_open_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/open.wav"] = r;
    }

    {
        extern unsigned char *data___zong_wav_start_
           asm("data___zong_wav_start_");
        extern unsigned char *data___zong_wav_end_
           asm("data___zong_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___zong_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___zong_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._zong.wav"] = r;
    }

    {
        extern unsigned char *data___wiggle_a_wav_start_
           asm("data___wiggle_a_wav_start_");
        extern unsigned char *data___wiggle_a_wav_end_
           asm("data___wiggle_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___wiggle_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___wiggle_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._wiggle_a.wav"] = r;
    }

    {
        extern unsigned char *data___wave_wav_start_
           asm("data___wave_wav_start_");
        extern unsigned char *data___wave_wav_end_
           asm("data___wave_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___wave_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___wave_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._wave.wav"] = r;
    }

    {
        extern unsigned char *data_collect_b_wav_start_
           asm("data_collect_b_wav_start_");
        extern unsigned char *data_collect_b_wav_end_
           asm("data_collect_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_collect_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_collect_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/collect_b.wav"] = r;
    }

    {
        extern unsigned char *data_bay_door_open_wav_start_
           asm("data_bay_door_open_wav_start_");
        extern unsigned char *data_bay_door_open_wav_end_
           asm("data_bay_door_open_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bay_door_open_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bay_door_open_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/bay_door_open.wav"] = r;
    }

    {
        extern unsigned char *data_fall_wav_start_
           asm("data_fall_wav_start_");
        extern unsigned char *data_fall_wav_end_
           asm("data_fall_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_fall_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_fall_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/fall.wav"] = r;
    }

    {
        extern unsigned char *data___whistle_wav_start_
           asm("data___whistle_wav_start_");
        extern unsigned char *data___whistle_wav_end_
           asm("data___whistle_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___whistle_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___whistle_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._whistle.wav"] = r;
    }

    {
        extern unsigned char *data___close_shut_wav_start_
           asm("data___close_shut_wav_start_");
        extern unsigned char *data___close_shut_wav_end_
           asm("data___close_shut_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___close_shut_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___close_shut_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._close_shut.wav"] = r;
    }

    {
        extern unsigned char *data_swerve_wav_start_
           asm("data_swerve_wav_start_");
        extern unsigned char *data_swerve_wav_end_
           asm("data_swerve_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_swerve_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_swerve_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/swerve.wav"] = r;
    }

    {
        extern unsigned char *data_shriek_wav_start_
           asm("data_shriek_wav_start_");
        extern unsigned char *data_shriek_wav_end_
           asm("data_shriek_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_shriek_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_shriek_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/shriek.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps3_wav_start_
           asm("data_footsteps3_wav_start_");
        extern unsigned char *data_footsteps3_wav_end_
           asm("data_footsteps3_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps3_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps3_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps3.wav"] = r;
    }

    {
        extern unsigned char *data___scramble_wav_start_
           asm("data___scramble_wav_start_");
        extern unsigned char *data___scramble_wav_end_
           asm("data___scramble_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___scramble_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___scramble_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._scramble.wav"] = r;
    }

    {
        extern unsigned char *data___collect_b_wav_start_
           asm("data___collect_b_wav_start_");
        extern unsigned char *data___collect_b_wav_end_
           asm("data___collect_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___collect_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___collect_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._collect_b.wav"] = r;
    }

    {
        extern unsigned char *data___wiggle_b_wav_start_
           asm("data___wiggle_b_wav_start_");
        extern unsigned char *data___wiggle_b_wav_end_
           asm("data___wiggle_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___wiggle_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___wiggle_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._wiggle_b.wav"] = r;
    }

    {
        extern unsigned char *data___ping_wav_start_
           asm("data___ping_wav_start_");
        extern unsigned char *data___ping_wav_end_
           asm("data___ping_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___ping_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___ping_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._ping.wav"] = r;
    }

    {
        extern unsigned char *data___resurrect_wav_start_
           asm("data___resurrect_wav_start_");
        extern unsigned char *data___resurrect_wav_end_
           asm("data___resurrect_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___resurrect_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___resurrect_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._resurrect.wav"] = r;
    }

    {
        extern unsigned char *data___step_wav_start_
           asm("data___step_wav_start_");
        extern unsigned char *data___step_wav_end_
           asm("data___step_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___step_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___step_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._step.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps5_wav_start_
           asm("data_footsteps5_wav_start_");
        extern unsigned char *data_footsteps5_wav_end_
           asm("data_footsteps5_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps5_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps5_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps5.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps2_wav_start_
           asm("data_footsteps2_wav_start_");
        extern unsigned char *data_footsteps2_wav_end_
           asm("data_footsteps2_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps2_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps2_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps2.wav"] = r;
    }

    {
        extern unsigned char *data_bay_door_close_wav_start_
           asm("data_bay_door_close_wav_start_");
        extern unsigned char *data_bay_door_close_wav_end_
           asm("data_bay_door_close_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_bay_door_close_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_bay_door_close_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/bay_door_close.wav"] = r;
    }

    {
        extern unsigned char *data___shut_wav_start_
           asm("data___shut_wav_start_");
        extern unsigned char *data___shut_wav_end_
           asm("data___shut_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___shut_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___shut_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._shut.wav"] = r;
    }

    {
        extern unsigned char *data___shriek_wav_start_
           asm("data___shriek_wav_start_");
        extern unsigned char *data___shriek_wav_end_
           asm("data___shriek_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___shriek_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___shriek_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._shriek.wav"] = r;
    }

    {
        extern unsigned char *data_twing_wav_start_
           asm("data_twing_wav_start_");
        extern unsigned char *data_twing_wav_end_
           asm("data_twing_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_twing_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_twing_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/twing.wav"] = r;
    }

    {
        extern unsigned char *data_drip_wav_start_
           asm("data_drip_wav_start_");
        extern unsigned char *data_drip_wav_end_
           asm("data_drip_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_drip_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_drip_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/drip.wav"] = r;
    }

    {
        extern unsigned char *data_scatter_wav_start_
           asm("data_scatter_wav_start_");
        extern unsigned char *data_scatter_wav_end_
           asm("data_scatter_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_scatter_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_scatter_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/scatter.wav"] = r;
    }

    {
        extern unsigned char *data___blurb_wav_start_
           asm("data___blurb_wav_start_");
        extern unsigned char *data___blurb_wav_end_
           asm("data___blurb_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___blurb_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___blurb_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._blurb.wav"] = r;
    }

    {
        extern unsigned char *data_step_wav_start_
           asm("data_step_wav_start_");
        extern unsigned char *data_step_wav_end_
           asm("data_step_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_step_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_step_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/step.wav"] = r;
    }

    {
        extern unsigned char *data___bay_door_open_wav_start_
           asm("data___bay_door_open_wav_start_");
        extern unsigned char *data___bay_door_open_wav_end_
           asm("data___bay_door_open_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___bay_door_open_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___bay_door_open_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._bay_door_open.wav"] = r;
    }

    {
        extern unsigned char *data_ping_wav_start_
           asm("data_ping_wav_start_");
        extern unsigned char *data_ping_wav_end_
           asm("data_ping_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_ping_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_ping_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/ping.wav"] = r;
    }

    {
        extern unsigned char *data___swerve_wav_start_
           asm("data___swerve_wav_start_");
        extern unsigned char *data___swerve_wav_end_
           asm("data___swerve_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___swerve_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___swerve_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._swerve.wav"] = r;
    }

    {
        extern unsigned char *data___twing_wav_start_
           asm("data___twing_wav_start_");
        extern unsigned char *data___twing_wav_end_
           asm("data___twing_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___twing_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___twing_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._twing.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps1_wav_start_
           asm("data_footsteps1_wav_start_");
        extern unsigned char *data_footsteps1_wav_end_
           asm("data_footsteps1_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps1_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps1_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps1.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps4_wav_start_
           asm("data_footsteps4_wav_start_");
        extern unsigned char *data_footsteps4_wav_end_
           asm("data_footsteps4_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps4_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps4_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps4.wav"] = r;
    }

    {
        extern unsigned char *data_wave_wav_start_
           asm("data_wave_wav_start_");
        extern unsigned char *data_wave_wav_end_
           asm("data_wave_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_wave_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_wave_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/wave.wav"] = r;
    }

    {
        extern unsigned char *data_shut_wav_start_
           asm("data_shut_wav_start_");
        extern unsigned char *data_shut_wav_end_
           asm("data_shut_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_shut_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_shut_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/shut.wav"] = r;
    }

    {
        extern unsigned char *data_close_wav_start_
           asm("data_close_wav_start_");
        extern unsigned char *data_close_wav_end_
           asm("data_close_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_close_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_close_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/close.wav"] = r;
    }

    {
        extern unsigned char *data___fall_wav_start_
           asm("data___fall_wav_start_");
        extern unsigned char *data___fall_wav_end_
           asm("data___fall_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___fall_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___fall_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._fall.wav"] = r;
    }

    {
        extern unsigned char *data_clack_wav_start_
           asm("data_clack_wav_start_");
        extern unsigned char *data_clack_wav_end_
           asm("data_clack_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_clack_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_clack_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/clack.wav"] = r;
    }

    {
        extern unsigned char *data___chime_wav_start_
           asm("data___chime_wav_start_");
        extern unsigned char *data___chime_wav_end_
           asm("data___chime_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___chime_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___chime_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._chime.wav"] = r;
    }

    {
        extern unsigned char *data_wiggle_b_wav_start_
           asm("data_wiggle_b_wav_start_");
        extern unsigned char *data_wiggle_b_wav_end_
           asm("data_wiggle_b_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_wiggle_b_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_wiggle_b_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/wiggle_b.wav"] = r;
    }

    {
        extern unsigned char *data___bay_door_close_wav_start_
           asm("data___bay_door_close_wav_start_");
        extern unsigned char *data___bay_door_close_wav_end_
           asm("data___bay_door_close_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___bay_door_close_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___bay_door_close_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._bay_door_close.wav"] = r;
    }

    {
        extern unsigned char *data_zong_wav_start_
           asm("data_zong_wav_start_");
        extern unsigned char *data_zong_wav_end_
           asm("data_zong_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_zong_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_zong_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/zong.wav"] = r;
    }

    {
        extern unsigned char *data_chime_wav_start_
           asm("data_chime_wav_start_");
        extern unsigned char *data_chime_wav_end_
           asm("data_chime_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_chime_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_chime_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/chime.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps6_wav_start_
           asm("data_footsteps6_wav_start_");
        extern unsigned char *data_footsteps6_wav_end_
           asm("data_footsteps6_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps6_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps6_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps6.wav"] = r;
    }

    {
        extern unsigned char *data_resurrect_wav_start_
           asm("data_resurrect_wav_start_");
        extern unsigned char *data_resurrect_wav_end_
           asm("data_resurrect_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_resurrect_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_resurrect_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/resurrect.wav"] = r;
    }

    {
        extern unsigned char *data___drip_wav_start_
           asm("data___drip_wav_start_");
        extern unsigned char *data___drip_wav_end_
           asm("data___drip_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___drip_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___drip_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._drip.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps8_wav_start_
           asm("data_footsteps8_wav_start_");
        extern unsigned char *data_footsteps8_wav_end_
           asm("data_footsteps8_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps8_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps8_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps8.wav"] = r;
    }

    {
        extern unsigned char *data_transistor_wav_start_
           asm("data_transistor_wav_start_");
        extern unsigned char *data_transistor_wav_end_
           asm("data_transistor_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_transistor_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_transistor_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/transistor.wav"] = r;
    }

    {
        extern unsigned char *data_blurb_wav_start_
           asm("data_blurb_wav_start_");
        extern unsigned char *data_blurb_wav_end_
           asm("data_blurb_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_blurb_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_blurb_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/blurb.wav"] = r;
    }

    {
        extern unsigned char *data_unlock_wav_start_
           asm("data_unlock_wav_start_");
        extern unsigned char *data_unlock_wav_end_
           asm("data_unlock_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_unlock_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_unlock_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/unlock.wav"] = r;
    }

    {
        extern unsigned char *data___rubberband_wav_start_
           asm("data___rubberband_wav_start_");
        extern unsigned char *data___rubberband_wav_end_
           asm("data___rubberband_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___rubberband_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___rubberband_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._rubberband.wav"] = r;
    }

    {
        extern unsigned char *data___scatter_wav_start_
           asm("data___scatter_wav_start_");
        extern unsigned char *data___scatter_wav_end_
           asm("data___scatter_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___scatter_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___scatter_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._scatter.wav"] = r;
    }

    {
        extern unsigned char *data_drop_wav_start_
           asm("data_drop_wav_start_");
        extern unsigned char *data_drop_wav_end_
           asm("data_drop_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_drop_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_drop_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/drop.wav"] = r;
    }

    {
        extern unsigned char *data_whistle_wav_start_
           asm("data_whistle_wav_start_");
        extern unsigned char *data_whistle_wav_end_
           asm("data_whistle_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_whistle_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_whistle_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/whistle.wav"] = r;
    }

    {
        extern unsigned char *data_wiggle_a_wav_start_
           asm("data_wiggle_a_wav_start_");
        extern unsigned char *data_wiggle_a_wav_end_
           asm("data_wiggle_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_wiggle_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_wiggle_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/wiggle_a.wav"] = r;
    }

    {
        extern unsigned char *data_mushroom_wav_start_
           asm("data_mushroom_wav_start_");
        extern unsigned char *data_mushroom_wav_end_
           asm("data_mushroom_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_mushroom_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_mushroom_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/mushroom.wav"] = r;
    }

    {
        extern unsigned char *data___transistor_wav_start_
           asm("data___transistor_wav_start_");
        extern unsigned char *data___transistor_wav_end_
           asm("data___transistor_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___transistor_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___transistor_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._transistor.wav"] = r;
    }

    {
        extern unsigned char *data___clack_wav_start_
           asm("data___clack_wav_start_");
        extern unsigned char *data___clack_wav_end_
           asm("data___clack_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___clack_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___clack_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._clack.wav"] = r;
    }

    {
        extern unsigned char *data___mushroom_wav_start_
           asm("data___mushroom_wav_start_");
        extern unsigned char *data___mushroom_wav_end_
           asm("data___mushroom_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___mushroom_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___mushroom_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._mushroom.wav"] = r;
    }

    {
        extern unsigned char *data_rubberband_wav_start_
           asm("data_rubberband_wav_start_");
        extern unsigned char *data_rubberband_wav_end_
           asm("data_rubberband_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_rubberband_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_rubberband_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/rubberband.wav"] = r;
    }

    {
        extern unsigned char *data_close_shut_wav_start_
           asm("data_close_shut_wav_start_");
        extern unsigned char *data_close_shut_wav_end_
           asm("data_close_shut_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_close_shut_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_close_shut_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/close_shut.wav"] = r;
    }

    {
        extern unsigned char *data___unlock_wav_start_
           asm("data___unlock_wav_start_");
        extern unsigned char *data___unlock_wav_end_
           asm("data___unlock_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___unlock_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___unlock_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._unlock.wav"] = r;
    }

    {
        extern unsigned char *data_collect_a_wav_start_
           asm("data_collect_a_wav_start_");
        extern unsigned char *data_collect_a_wav_end_
           asm("data_collect_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_collect_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_collect_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/collect_a.wav"] = r;
    }

    {
        extern unsigned char *data___close_wav_start_
           asm("data___close_wav_start_");
        extern unsigned char *data___close_wav_end_
           asm("data___close_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___close_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___close_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._close.wav"] = r;
    }

    {
        extern unsigned char *data_footsteps7_wav_start_
           asm("data_footsteps7_wav_start_");
        extern unsigned char *data_footsteps7_wav_end_
           asm("data_footsteps7_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_footsteps7_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_footsteps7_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/footsteps7.wav"] = r;
    }

    {
        extern unsigned char *data___collect_a_wav_start_
           asm("data___collect_a_wav_start_");
        extern unsigned char *data___collect_a_wav_end_
           asm("data___collect_a_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___collect_a_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___collect_a_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/._collect_a.wav"] = r;
    }

    {
        extern unsigned char *data_scramble_wav_start_
           asm("data_scramble_wav_start_");
        extern unsigned char *data_scramble_wav_end_
           asm("data_scramble_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_scramble_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_scramble_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/misc/scramble.wav"] = r;
    }

    {
        extern unsigned char *data___curse_wav_start_
           asm("data___curse_wav_start_");
        extern unsigned char *data___curse_wav_end_
           asm("data___curse_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___curse_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___curse_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._curse.wav"] = r;
    }

    {
        extern unsigned char *data_charm_wav_start_
           asm("data_charm_wav_start_");
        extern unsigned char *data_charm_wav_end_
           asm("data_charm_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_charm_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_charm_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/charm.wav"] = r;
    }

    {
        extern unsigned char *data_curse_wav_start_
           asm("data_curse_wav_start_");
        extern unsigned char *data_curse_wav_end_
           asm("data_curse_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_curse_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_curse_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/curse.wav"] = r;
    }

    {
        extern unsigned char *data___confuse_wav_start_
           asm("data___confuse_wav_start_");
        extern unsigned char *data___confuse_wav_end_
           asm("data___confuse_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___confuse_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___confuse_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._confuse.wav"] = r;
    }

    {
        extern unsigned char *data___burn_wav_start_
           asm("data___burn_wav_start_");
        extern unsigned char *data___burn_wav_end_
           asm("data___burn_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___burn_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___burn_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._burn.wav"] = r;
    }

    {
        extern unsigned char *data_mutation_wav_start_
           asm("data_mutation_wav_start_");
        extern unsigned char *data_mutation_wav_end_
           asm("data_mutation_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_mutation_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_mutation_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/mutation.wav"] = r;
    }

    {
        extern unsigned char *data_disease_wav_start_
           asm("data_disease_wav_start_");
        extern unsigned char *data_disease_wav_end_
           asm("data_disease_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_disease_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_disease_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/disease.wav"] = r;
    }

    {
        extern unsigned char *data_freeze_wav_start_
           asm("data_freeze_wav_start_");
        extern unsigned char *data_freeze_wav_end_
           asm("data_freeze_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_freeze_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_freeze_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/freeze.wav"] = r;
    }

    {
        extern unsigned char *data_poison_wav_start_
           asm("data_poison_wav_start_");
        extern unsigned char *data_poison_wav_end_
           asm("data_poison_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_poison_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_poison_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/poison.wav"] = r;
    }

    {
        extern unsigned char *data___charm_wav_start_
           asm("data___charm_wav_start_");
        extern unsigned char *data___charm_wav_end_
           asm("data___charm_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___charm_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___charm_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._charm.wav"] = r;
    }

    {
        extern unsigned char *data_confuse_wav_start_
           asm("data_confuse_wav_start_");
        extern unsigned char *data_confuse_wav_end_
           asm("data_confuse_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_confuse_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_confuse_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/confuse.wav"] = r;
    }

    {
        extern unsigned char *data_burn_wav_start_
           asm("data_burn_wav_start_");
        extern unsigned char *data_burn_wav_end_
           asm("data_burn_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data_burn_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data_burn_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/burn.wav"] = r;
    }

    {
        extern unsigned char *data___poison_wav_start_
           asm("data___poison_wav_start_");
        extern unsigned char *data___poison_wav_end_
           asm("data___poison_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___poison_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___poison_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._poison.wav"] = r;
    }

    {
        extern unsigned char *data___disease_wav_start_
           asm("data___disease_wav_start_");
        extern unsigned char *data___disease_wav_end_
           asm("data___disease_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___disease_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___disease_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._disease.wav"] = r;
    }

    {
        extern unsigned char *data___mutation_wav_start_
           asm("data___mutation_wav_start_");
        extern unsigned char *data___mutation_wav_end_
           asm("data___mutation_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___mutation_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___mutation_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._mutation.wav"] = r;
    }

    {
        extern unsigned char *data___freeze_wav_start_
           asm("data___freeze_wav_start_");
        extern unsigned char *data___freeze_wav_end_
           asm("data___freeze_wav_end_");
        static const unsigned char *const start =
           (const unsigned char *const) (char*)&data___freeze_wav_start_;
        static const unsigned char *const end   =
           (const unsigned char *const) (char*)&data___freeze_wav_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/sounds/status/._freeze.wav"] = r;
    }

}
