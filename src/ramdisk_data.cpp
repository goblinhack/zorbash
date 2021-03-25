#include "my_ramdisk.h"

void ramdisk_init (void)
{
    {
        extern unsigned char *data_title_small_tga_start_ asm("data_title_small_tga_start_");
        extern unsigned char *data_title_small_tga_end_ asm("data_title_small_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_small_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_small_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_small_tga"] = r;
    }

    {
        extern unsigned char *data_weapons_tga_start_ asm("data_weapons_tga_start_");
        extern unsigned char *data_weapons_tga_end_ asm("data_weapons_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_weapons_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_weapons_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/weapons_tga"] = r;
    }

    {
        extern unsigned char *data_ui_tile_bg_tga_start_ asm("data_ui_tile_bg_tga_start_");
        extern unsigned char *data_ui_tile_bg_tga_end_ asm("data_ui_tile_bg_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_tile_bg_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_tile_bg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_tile_bg_tga"] = r;
    }

    {
        extern unsigned char *data_solid_tga_start_ asm("data_solid_tga_start_");
        extern unsigned char *data_solid_tga_end_ asm("data_solid_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_solid_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_solid_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/solid_tga"] = r;
    }

    {
        extern unsigned char *data_title_fg4_tga_start_ asm("data_title_fg4_tga_start_");
        extern unsigned char *data_title_fg4_tga_end_ asm("data_title_fg4_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_fg4_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_fg4_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg4_tga"] = r;
    }

    {
        extern unsigned char *data_ui_horiz2_tga_start_ asm("data_ui_horiz2_tga_start_");
        extern unsigned char *data_ui_horiz2_tga_end_ asm("data_ui_horiz2_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_horiz2_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_horiz2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_horiz2_tga"] = r;
    }

    {
        extern unsigned char *data_title_fg1_tga_start_ asm("data_title_fg1_tga_start_");
        extern unsigned char *data_title_fg1_tga_end_ asm("data_title_fg1_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_fg1_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_fg1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg1_tga"] = r;
    }

    {
        extern unsigned char *data_chasm2_tga_start_ asm("data_chasm2_tga_start_");
        extern unsigned char *data_chasm2_tga_end_ asm("data_chasm2_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_chasm2_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_chasm2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/chasm2_tga"] = r;
    }

    {
        extern unsigned char *data_title_fg3_tga_start_ asm("data_title_fg3_tga_start_");
        extern unsigned char *data_title_fg3_tga_end_ asm("data_title_fg3_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_fg3_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_fg3_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg3_tga"] = r;
    }

    {
        extern unsigned char *data_ui_horiz1_tga_start_ asm("data_ui_horiz1_tga_start_");
        extern unsigned char *data_ui_horiz1_tga_end_ asm("data_ui_horiz1_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_horiz1_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_horiz1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_horiz1_tga"] = r;
    }

    {
        extern unsigned char *data_title_fg2_tga_start_ asm("data_title_fg2_tga_start_");
        extern unsigned char *data_title_fg2_tga_end_ asm("data_title_fg2_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_fg2_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_fg2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_fg2_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_lava_tga_start_ asm("data_tiles3_lava_tga_start_");
        extern unsigned char *data_tiles3_lava_tga_end_ asm("data_tiles3_lava_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_lava_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_lava_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_lava_tga"] = r;
    }

    {
        extern unsigned char *data_ui_dead_tga_start_ asm("data_ui_dead_tga_start_");
        extern unsigned char *data_ui_dead_tga_end_ asm("data_ui_dead_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_dead_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_dead_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_dead_tga"] = r;
    }

    {
        extern unsigned char *data_title_splash_tga_start_ asm("data_title_splash_tga_start_");
        extern unsigned char *data_title_splash_tga_end_ asm("data_title_splash_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_splash_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_splash_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_splash_tga"] = r;
    }

    {
        extern unsigned char *data_ui_health_bar_tga_start_ asm("data_ui_health_bar_tga_start_");
        extern unsigned char *data_ui_health_bar_tga_end_ asm("data_ui_health_bar_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_health_bar_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_health_bar_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_health_bar_tga"] = r;
    }

    {
        extern unsigned char *data_ui_credits_fg_tga_start_ asm("data_ui_credits_fg_tga_start_");
        extern unsigned char *data_ui_credits_fg_tga_end_ asm("data_ui_credits_fg_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_credits_fg_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_credits_fg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_credits_fg_tga"] = r;
    }

    {
        extern unsigned char *data_blood_tga_start_ asm("data_blood_tga_start_");
        extern unsigned char *data_blood_tga_end_ asm("data_blood_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_blood_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_blood_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/blood_tga"] = r;
    }

    {
        extern unsigned char *data_glow_tga_start_ asm("data_glow_tga_start_");
        extern unsigned char *data_glow_tga_end_ asm("data_glow_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_glow_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_glow_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/glow_tga"] = r;
    }

    {
        extern unsigned char *data_background_tga_start_ asm("data_background_tga_start_");
        extern unsigned char *data_background_tga_end_ asm("data_background_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_background_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_background_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/background_tga"] = r;
    }

    {
        extern unsigned char *data_ui_bag_tga_start_ asm("data_ui_bag_tga_start_");
        extern unsigned char *data_ui_bag_tga_end_ asm("data_ui_bag_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_bag_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_bag_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_bag_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_chasm_tga_start_ asm("data_tiles3_chasm_tga_start_");
        extern unsigned char *data_tiles3_chasm_tga_end_ asm("data_tiles3_chasm_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_chasm_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_chasm_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_chasm_tga"] = r;
    }

    {
        extern unsigned char *data_light_tga_start_ asm("data_light_tga_start_");
        extern unsigned char *data_light_tga_end_ asm("data_light_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_light_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_light_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/light_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_water_tga_start_ asm("data_tiles3_water_tga_start_");
        extern unsigned char *data_tiles3_water_tga_end_ asm("data_tiles3_water_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_water_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_water_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_water_tga"] = r;
    }

    {
        extern unsigned char *data_ui_vert2_tga_start_ asm("data_ui_vert2_tga_start_");
        extern unsigned char *data_ui_vert2_tga_end_ asm("data_ui_vert2_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_vert2_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_vert2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_vert2_tga"] = r;
    }

    {
        extern unsigned char *data_chasm_tga_start_ asm("data_chasm_tga_start_");
        extern unsigned char *data_chasm_tga_end_ asm("data_chasm_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_chasm_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_chasm_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/chasm_tga"] = r;
    }

    {
        extern unsigned char *data_attack_tga_start_ asm("data_attack_tga_start_");
        extern unsigned char *data_attack_tga_end_ asm("data_attack_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_attack_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_attack_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/attack_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_sewer_water_tga_start_ asm("data_tiles3_sewer_water_tga_start_");
        extern unsigned char *data_tiles3_sewer_water_tga_end_ asm("data_tiles3_sewer_water_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_sewer_water_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_sewer_water_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_sewer_water_tga"] = r;
    }

    {
        extern unsigned char *data_ui_circle_tga_start_ asm("data_ui_circle_tga_start_");
        extern unsigned char *data_ui_circle_tga_end_ asm("data_ui_circle_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_circle_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_circle_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_circle_tga"] = r;
    }

    {
        extern unsigned char *data_ui_vert1_tga_start_ asm("data_ui_vert1_tga_start_");
        extern unsigned char *data_ui_vert1_tga_end_ asm("data_ui_vert1_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_vert1_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_vert1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_vert1_tga"] = r;
    }

    {
        extern unsigned char *data_title_bg_tga_start_ asm("data_title_bg_tga_start_");
        extern unsigned char *data_title_bg_tga_end_ asm("data_title_bg_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_title_bg_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_title_bg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/title_bg_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box0_tga_start_ asm("data_ui_box0_tga_start_");
        extern unsigned char *data_ui_box0_tga_end_ asm("data_ui_box0_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box0_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box0_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box0_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box1_tga_start_ asm("data_ui_box1_tga_start_");
        extern unsigned char *data_ui_box1_tga_end_ asm("data_ui_box1_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box1_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box1_tga"] = r;
    }

    {
        extern unsigned char *data_tiles1_tga_start_ asm("data_tiles1_tga_start_");
        extern unsigned char *data_tiles1_tga_end_ asm("data_tiles1_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles1_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles1_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles1_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_surface_effects_tga_start_ asm("data_tiles3_surface_effects_tga_start_");
        extern unsigned char *data_tiles3_surface_effects_tga_end_ asm("data_tiles3_surface_effects_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_surface_effects_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_surface_effects_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_surface_effects_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_tga_start_ asm("data_tiles3_tga_start_");
        extern unsigned char *data_tiles3_tga_end_ asm("data_tiles3_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box3_tga_start_ asm("data_ui_box3_tga_start_");
        extern unsigned char *data_ui_box3_tga_end_ asm("data_ui_box3_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box3_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box3_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box3_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box2_tga_start_ asm("data_ui_box2_tga_start_");
        extern unsigned char *data_ui_box2_tga_end_ asm("data_ui_box2_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box2_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box2_tga"] = r;
    }

    {
        extern unsigned char *data_tiles2_tga_start_ asm("data_tiles2_tga_start_");
        extern unsigned char *data_tiles2_tga_end_ asm("data_tiles2_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles2_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles2_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles2_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box6_tga_start_ asm("data_ui_box6_tga_start_");
        extern unsigned char *data_ui_box6_tga_end_ asm("data_ui_box6_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box6_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box6_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box6_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box7_tga_start_ asm("data_ui_box7_tga_start_");
        extern unsigned char *data_ui_box7_tga_end_ asm("data_ui_box7_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box7_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box7_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box7_tga"] = r;
    }

    {
        extern unsigned char *data_tiles3_deep_water_tga_start_ asm("data_tiles3_deep_water_tga_start_");
        extern unsigned char *data_tiles3_deep_water_tga_end_ asm("data_tiles3_deep_water_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_tiles3_deep_water_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_tiles3_deep_water_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/tiles3_deep_water_tga"] = r;
    }

    {
        extern unsigned char *data_ui_status_bar_tga_start_ asm("data_ui_status_bar_tga_start_");
        extern unsigned char *data_ui_status_bar_tga_end_ asm("data_ui_status_bar_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_status_bar_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_status_bar_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_status_bar_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box5_tga_start_ asm("data_ui_box5_tga_start_");
        extern unsigned char *data_ui_box5_tga_end_ asm("data_ui_box5_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box5_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box5_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box5_tga"] = r;
    }

    {
        extern unsigned char *data_ui_credits_bg_tga_start_ asm("data_ui_credits_bg_tga_start_");
        extern unsigned char *data_ui_credits_bg_tga_end_ asm("data_ui_credits_bg_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_credits_bg_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_credits_bg_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_credits_bg_tga"] = r;
    }

    {
        extern unsigned char *data_ui_box4_tga_start_ asm("data_ui_box4_tga_start_");
        extern unsigned char *data_ui_box4_tga_end_ asm("data_ui_box4_tga_end_");
        static const unsigned char *const start = (const unsigned char *const) (char*)&data_ui_box4_tga_start_;
        static const unsigned char *const end   = (const unsigned char *const) (char*)&data_ui_box4_tga_end_;
        ramdisk_t r;
        r.data = start;
        r.len = end - start;
        ramdisk_data["data/gfx/ui_box4_tga"] = r;
    }

}
