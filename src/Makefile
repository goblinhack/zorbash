COMPILER_FLAGS=-Werror -I/opt/local/include/SDL2 -D_THREAD_SAFE -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -Wsign-compare -fno-common -dynamic -DNDEBUG -g -Wall   -arch x86_64 -g  -DVERSION=\"0.0.4\" -DPYTHONVERSION=\"3.6\" -g -ggdb3 -O3 # AUTOGEN
    
CLANG_COMPILER_WARNINGS=-Wall -Wmissing-prototypes -std=c++1z -stdlib=libc++ # AUTOGEN
GCC_COMPILER_WARNINGS=-x c++ -Wall -std=c++2a -ffast-math  # AUTOGEN
COMPILER_WARNINGS=$(CLANG_COMPILER_WARNINGS) # AUTOGEN
COMPILER_WARNINGS=$(GCC_COMPILER_WARNINGS) # AUTOGEN
# CC=clang++ # AUTOGEN
CC=g++ # AUTOGEN
    
EXE= # AUTOGEN
DSYM=dsymutil ../zorbash # AUTOGEN
LDLIBS=-L/opt/local/lib -lSDL2 -lSDL2_mixer -lSDL2_ttf -L/Library/Frameworks/Python.framework/Versions/3.6/lib/python3.6/config-3.6m-darwin -lpython3.6m -ldl -framework CoreFoundation -funwind-tables -rdynamic -Wl,-framework,Opengl # AUTOGEN
CFLAGS=$(COMPILER_FLAGS) $(COMPILER_WARNINGS) # AUTOGEN

NAME=zorbash
OBJDIR=.o

GAME_OBJECTS=				    \
    $(OBJDIR)/ascii.o                       \
    $(OBJDIR)/ascii_box.o                   \
    $(OBJDIR)/charmap.o                     \
    $(OBJDIR)/color.o                       \
    $(OBJDIR)/color1.o                      \
    $(OBJDIR)/color2.o                      \
    $(OBJDIR)/color3.o                      \
    $(OBJDIR)/color4.o                      \
    $(OBJDIR)/command.o                     \
    $(OBJDIR)/console.o                     \
    $(OBJDIR)/dice.o                        \
    $(OBJDIR)/dict1.o                       \
    $(OBJDIR)/dict2.o                       \
    $(OBJDIR)/dir.o                         \
    $(OBJDIR)/dmap.o                        \
    $(OBJDIR)/dungeon.o                     \
    $(OBJDIR)/dungeon_grid.o                \
    $(OBJDIR)/file.o                        \
    $(OBJDIR)/file_log.o                    \
    $(OBJDIR)/file_read.o                   \
    $(OBJDIR)/font.o                        \
    $(OBJDIR)/game.o                        \
    $(OBJDIR)/game_config.o                 \
    $(OBJDIR)/game_config_gfx.o             \
    $(OBJDIR)/game_config_keyboard.o        \
    $(OBJDIR)/game_config_other.o           \
    $(OBJDIR)/game_config_sound.o           \
    $(OBJDIR)/game_credits.o                \
    $(OBJDIR)/game_dead.o                   \
    $(OBJDIR)/game_display.o                \
    $(OBJDIR)/game_dump.o                   \
    $(OBJDIR)/game_error.o                  \
    $(OBJDIR)/game_fini.o                   \
    $(OBJDIR)/game_init.o                   \
    $(OBJDIR)/game_load.o                   \
    $(OBJDIR)/game_log.o                    \
    $(OBJDIR)/game_main_menu.o              \
    $(OBJDIR)/game_menu_flames.o            \
    $(OBJDIR)/game_mouse.o                  \
    $(OBJDIR)/game_notice.o                 \
    $(OBJDIR)/game_paused.o                 \
    $(OBJDIR)/game_quit.o                   \
    $(OBJDIR)/game_save.o                   \
    $(OBJDIR)/game_tick.o                   \
    $(OBJDIR)/gauss.o                       \
    $(OBJDIR)/gfx.o                         \
    $(OBJDIR)/gfx0.o                        \
    $(OBJDIR)/gfx1.o                        \
    $(OBJDIR)/gfx10.o                       \
    $(OBJDIR)/gfx11.o                       \
    $(OBJDIR)/gfx12.o                       \
    $(OBJDIR)/gfx2.o                        \
    $(OBJDIR)/gfx3.o                        \
    $(OBJDIR)/gfx4.o                        \
    $(OBJDIR)/gfx5.o                        \
    $(OBJDIR)/gfx6.o                        \
    $(OBJDIR)/gfx7.o                        \
    $(OBJDIR)/gfx8.o                        \
    $(OBJDIR)/gfx9.o                        \
    $(OBJDIR)/gl.o                          \
    $(OBJDIR)/globals.o                     \
    $(OBJDIR)/hacklib.o                     \
    $(OBJDIR)/hexdump.o                     \
    $(OBJDIR)/level.o                       \
    $(OBJDIR)/level_create.o                \
    $(OBJDIR)/level_map_update.o            \
    $(OBJDIR)/level_cursor.o                \
    $(OBJDIR)/level_cursor_path.o           \
    $(OBJDIR)/level_display.o               \
    $(OBJDIR)/level_display_anim.o          \
    $(OBJDIR)/level_display_blood.o         \
    $(OBJDIR)/level_display_chasm.o         \
    $(OBJDIR)/level_display_deep_water.o    \
    $(OBJDIR)/level_display_fade.o          \
    $(OBJDIR)/level_display_lava.o          \
    $(OBJDIR)/level_display_minimap.o       \
    $(OBJDIR)/level_display_shake.o         \
    $(OBJDIR)/level_display_wall.o          \
    $(OBJDIR)/level_display_water.o         \
    $(OBJDIR)/level_fini.o                  \
    $(OBJDIR)/level_gc.o                    \
    $(OBJDIR)/level_heatmap.o               \
    $(OBJDIR)/level_init.o                  \
    $(OBJDIR)/level_log.o                   \
    $(OBJDIR)/level_map_things.o            \
    $(OBJDIR)/level_minimap.o               \
    $(OBJDIR)/level_scroll.o                \
    $(OBJDIR)/level_static.o                \
    $(OBJDIR)/level_tick.o                  \
    $(OBJDIR)/level_map_update.o            \
    $(OBJDIR)/light.o                       \
    $(OBJDIR)/light_log.o                   \
    $(OBJDIR)/log.o                         \
    $(OBJDIR)/log_util.o                    \
    $(OBJDIR)/main.o                        \
    $(OBJDIR)/map.o                         \
    $(OBJDIR)/minilzo.o                     \
    $(OBJDIR)/particle.o                    \
    $(OBJDIR)/pcg_basic.o                   \
    $(OBJDIR)/player.o                      \
    $(OBJDIR)/ptrcheck.o                    \
    $(OBJDIR)/py_level.o                    \
    $(OBJDIR)/py_log.o                      \
    $(OBJDIR)/py_room.o                     \
    $(OBJDIR)/py_sdl.o                      \
    $(OBJDIR)/py_tex.o                      \
    $(OBJDIR)/py_tile.o                     \
    $(OBJDIR)/py_tp.o                       \
    $(OBJDIR)/py_ttf.o                      \
    $(OBJDIR)/python.o                      \
    $(OBJDIR)/random_name.o                 \
    $(OBJDIR)/room.o                        \
    $(OBJDIR)/sdl.o                         \
    $(OBJDIR)/sdl_screenshot.o              \
    $(OBJDIR)/signal.o                      \
    $(OBJDIR)/slre.o                        \
    $(OBJDIR)/sprintf.o                     \
    $(OBJDIR)/stb_image.o                   \
    $(OBJDIR)/string.o                      \
    $(OBJDIR)/tex.o                         \
    $(OBJDIR)/thing_acid.o                  \
    $(OBJDIR)/thing_ai.o                    \
    $(OBJDIR)/thing_ai_goals.o              \
    $(OBJDIR)/thing_ai_wander.o             \
    $(OBJDIR)/thing_anim.o                  \
    $(OBJDIR)/thing_api.o                   \
    $(OBJDIR)/thing_astar.o                 \
    $(OBJDIR)/thing_attack.o                \
    $(OBJDIR)/thing_avoid.o                 \
    $(OBJDIR)/thing_bag.o                   \
    $(OBJDIR)/thing_bounce.o                \
    $(OBJDIR)/thing_carry.o                 \
    $(OBJDIR)/thing_chasm.o                 \
    $(OBJDIR)/thing_collision.o             \
    $(OBJDIR)/thing_cursor.o                \
    $(OBJDIR)/thing_cursor_path.o           \
    $(OBJDIR)/thing_danger.o                \
    $(OBJDIR)/thing_dead.o                  \
    $(OBJDIR)/thing_describe.o              \
    $(OBJDIR)/thing_dir.o                   \
    $(OBJDIR)/thing_display.o               \
    $(OBJDIR)/thing_distance.o              \
    $(OBJDIR)/thing_door.o                  \
    $(OBJDIR)/thing_drop.o                  \
    $(OBJDIR)/thing_eat.o                   \
    $(OBJDIR)/thing_enemy.o                 \
    $(OBJDIR)/thing_entrance.o              \
    $(OBJDIR)/thing_escape.o                \
    $(OBJDIR)/thing_exit.o                  \
    $(OBJDIR)/thing_fadeup.o                \
    $(OBJDIR)/thing_fall.o                  \
    $(OBJDIR)/thing_fini.o                  \
    $(OBJDIR)/thing_fire.o                  \
    $(OBJDIR)/thing_gc.o                    \
    $(OBJDIR)/thing_health.o                \
    $(OBJDIR)/thing_hide.o                  \
    $(OBJDIR)/thing_hit.o                   \
    $(OBJDIR)/thing_hooks.o                 \
    $(OBJDIR)/thing_hunger.o                \
    $(OBJDIR)/thing_id.o                    \
    $(OBJDIR)/thing_inherit.o               \
    $(OBJDIR)/thing_init.o                  \
    $(OBJDIR)/thing_inventory.o             \
    $(OBJDIR)/thing_item.o                  \
    $(OBJDIR)/thing_jump.o                  \
    $(OBJDIR)/thing_kill.o                  \
    $(OBJDIR)/thing_kill_if.o               \
    $(OBJDIR)/thing_lava.o                  \
    $(OBJDIR)/thing_level_change.o          \
    $(OBJDIR)/thing_level_enter.o           \
    $(OBJDIR)/thing_level_find.o            \
    $(OBJDIR)/thing_level_leave.o           \
    $(OBJDIR)/thing_level_pop.o             \
    $(OBJDIR)/thing_level_push.o            \
    $(OBJDIR)/thing_lifespan.o              \
    $(OBJDIR)/thing_light.o                 \
    $(OBJDIR)/thing_location.o              \
    $(OBJDIR)/thing_log.o                   \
    $(OBJDIR)/thing_lunge.o                 \
    $(OBJDIR)/thing_match.o                 \
    $(OBJDIR)/thing_move.o                  \
    $(OBJDIR)/thing_move_dir.o              \
    $(OBJDIR)/thing_msg.o                   \
    $(OBJDIR)/thing_nearby.o                \
    $(OBJDIR)/thing_obstacle.o              \
    $(OBJDIR)/thing_on_fire.o               \
    $(OBJDIR)/thing_owner.o                 \
    $(OBJDIR)/thing_path.o                  \
    $(OBJDIR)/thing_place.o                 \
    $(OBJDIR)/thing_rest.o                  \
    $(OBJDIR)/thing_resurrect.o             \
    $(OBJDIR)/thing_shove.o                 \
    $(OBJDIR)/thing_spawn.o                 \
    $(OBJDIR)/thing_stamina.o               \
    $(OBJDIR)/thing_steal.o                 \
    $(OBJDIR)/thing_string.o                \
    $(OBJDIR)/thing_template.o              \
    $(OBJDIR)/thing_template_api.o          \
    $(OBJDIR)/thing_terrain.o               \
    $(OBJDIR)/thing_text.o                  \
    $(OBJDIR)/thing_tick.o                  \
    $(OBJDIR)/thing_tile.o                  \
    $(OBJDIR)/thing_torch.o                 \
    $(OBJDIR)/thing_treasure.o              \
    $(OBJDIR)/thing_update.o                \
    $(OBJDIR)/thing_use.o                   \
    $(OBJDIR)/thing_visible.o               \
    $(OBJDIR)/thing_water.o                 \
    $(OBJDIR)/thing_weapon.o                \
    $(OBJDIR)/thing_wobble.o                \
    $(OBJDIR)/tile.o                        \
    $(OBJDIR)/time.o                        \
    $(OBJDIR)/token.o                       \
    $(OBJDIR)/traceback.o                   \
    $(OBJDIR)/ttf.o                         \
    $(OBJDIR)/util.o                        \
    $(OBJDIR)/wid.o                         \
    $(OBJDIR)/wid_bag.o                     \
    $(OBJDIR)/wid_botcon.o                  \
    $(OBJDIR)/wid_console.o                 \
    $(OBJDIR)/wid_inventory.o               \
    $(OBJDIR)/wid_leftbar.o                 \
    $(OBJDIR)/wid_log.o                     \
    $(OBJDIR)/wid_minicon.o                 \
    $(OBJDIR)/wid_popup.o                   \
    $(OBJDIR)/wid_rightbar.o                \
    $(OBJDIR)/wid_text_box.o                \
    $(OBJDIR)/wid_thing_collect.o           \
    $(OBJDIR)/wid_thing_info.o              \
    $(OBJDIR)/wid_tiles.o                   \
    $(OBJDIR)/world.o                       \
    $(OBJDIR)/world_fini.o                  \
    $(OBJDIR)/world_init.o                  \

#
# compile
#
$(OBJDIR)/%.o: %.cpp
	@echo $(CC) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<
	@$(CC) $(EXTRA_CFLAGS) $(CFLAGS) -c -o $@ $<

#
# link
#
TARGET_GAME=$(NAME)$(EXE)
$(TARGET_GAME): $(GAME_OBJECTS)
	$(CC) $(GAME_OBJECTS) $(LDLIBS) -o ../$(TARGET_GAME)

#
# To force clean and avoid "up to date" warning.
#
.PHONY: clean
.PHONY: clobber

clean:
	rm -rf ../$(TARGET_GAME) ../stdout.txt ../stderr.txt
	rm -rf $(GAME_OBJECTS) $(TARGET_GAME) stdout.txt stderr.txt

clobber: clean
	rm -rf $(OBJDIR)
	mkdir -p $(OBJDIR)

valgrind:
	valgrind --gen-suppressions=all --leak-check=full --suppressions=valgrind.suppress --error-limit=no ../$(NAME)

all: $(TARGET_GAME)
	$(DSYM)
# DO NOT DELETE

.o/ascii.o: my_ascii.h /usr/include/wchar.h /usr/include/_types.h
.o/ascii.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/ascii.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii.o: /usr/include/sys/_posix_availability.h
.o/ascii.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ascii.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/ascii.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/ascii.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/machine/types.h
.o/ascii.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_int64_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii.o: /usr/include/sys/_types/_rune_t.h
.o/ascii.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/ascii.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/ascii.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ascii.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ascii.o: /usr/include/secure/_common.h /usr/include/time.h
.o/ascii.o: /usr/include/sys/_types/_clock_t.h
.o/ascii.o: /usr/include/sys/_types/_time_t.h
.o/ascii.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ascii.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h my_tile.h
.o/ascii.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/ascii.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/ascii.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ascii.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/ascii.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ascii.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/ascii.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/ascii.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/ascii.o: slre.h my_point.h my_math.h /usr/include/math.h my_color.h
.o/ascii.o: my_font.h my_game.h my_world.h my_level.h my_time.h my_particle.h
.o/ascii.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/ascii.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/ascii.o: my_gl.h my_thing_template.h my_dice.h
.o/ascii_box.o: my_ascii.h /usr/include/wchar.h /usr/include/_types.h
.o/ascii_box.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/ascii_box.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii_box.o: /usr/include/sys/_posix_availability.h
.o/ascii_box.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ascii_box.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii_box.o: /usr/include/Availability.h
.o/ascii_box.o: /usr/include/AvailabilityInternal.h
.o/ascii_box.o: /usr/include/sys/_types/_null.h
.o/ascii_box.o: /usr/include/sys/_types/_size_t.h
.o/ascii_box.o: /usr/include/sys/_types/_mbstate_t.h
.o/ascii_box.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ascii_box.o: /usr/include/sys/_types/_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int64_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii_box.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii_box.o: /usr/include/sys/_types/_rune_t.h
.o/ascii_box.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/ascii_box.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/ascii_box.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ssize_t.h
.o/ascii_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ascii_box.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ascii_box.o: /usr/include/sys/_types/_time_t.h
.o/ascii_box.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii_box.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ascii_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii_box.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h
.o/ascii_box.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/ascii_box.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/ascii_box.o: /usr/include/_types/_uint8_t.h
.o/ascii_box.o: /usr/include/_types/_uint16_t.h
.o/ascii_box.o: /usr/include/_types/_uint32_t.h
.o/ascii_box.o: /usr/include/_types/_uint64_t.h
.o/ascii_box.o: /usr/include/_types/_intmax_t.h
.o/ascii_box.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/ascii_box.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/ascii_box.o: /usr/include/assert.h my_vector_bounds_check.h
.o/ascii_box.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/ascii_box.o: slre.h my_point.h my_math.h /usr/include/math.h my_color.h
.o/charmap.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/charmap.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/charmap.o: /usr/include/sys/_posix_availability.h
.o/charmap.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/charmap.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/charmap.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/charmap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/charmap.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/charmap.o: /usr/include/sys/_types/_int8_t.h
.o/charmap.o: /usr/include/sys/_types/_int16_t.h
.o/charmap.o: /usr/include/sys/_types/_int32_t.h
.o/charmap.o: /usr/include/sys/_types/_int64_t.h
.o/charmap.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/charmap.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/charmap.o: /usr/include/sys/_types/_intptr_t.h
.o/charmap.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/charmap.o: /usr/include/sys/_types/_u_int8_t.h
.o/charmap.o: /usr/include/sys/_types/_u_int16_t.h
.o/charmap.o: /usr/include/sys/_types/_u_int32_t.h
.o/charmap.o: /usr/include/sys/_types/_u_int64_t.h
.o/charmap.o: /usr/include/sys/_types/_uintptr_t.h
.o/charmap.o: /usr/include/_types/_intmax_t.h
.o/charmap.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/charmap.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/charmap.o: /usr/include/assert.h my_vector_bounds_check.h
.o/charmap.o: c_plus_plus_serializer.h my_charmap.h
.o/color.o: /usr/include/strings.h /usr/include/_types.h
.o/color.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/color.o: /usr/include/sys/_symbol_aliasing.h
.o/color.o: /usr/include/sys/_posix_availability.h
.o/color.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/color.o: /usr/include/sys/_types/_null.h
.o/color.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/color.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/color.o: /usr/include/sys/_types/_int16_t.h
.o/color.o: /usr/include/sys/_types/_int32_t.h
.o/color.o: /usr/include/sys/_types/_int64_t.h
.o/color.o: /usr/include/sys/_types/_u_int8_t.h
.o/color.o: /usr/include/sys/_types/_u_int16_t.h
.o/color.o: /usr/include/sys/_types/_u_int32_t.h
.o/color.o: /usr/include/sys/_types/_u_int64_t.h
.o/color.o: /usr/include/sys/_types/_intptr_t.h
.o/color.o: /usr/include/sys/_types/_uintptr_t.h
.o/color.o: /usr/include/sys/_types/_errno_t.h
.o/color.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/color.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/color.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/color.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/color.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/color.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/color.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/color.o: c_plus_plus_serializer.h my_gl.h my_color.h my_point.h my_math.h
.o/color.o: /usr/include/math.h my_size.h my_string.h /usr/include/wchar.h
.o/color.o: /usr/include/sys/_types/_mbstate_t.h
.o/color.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/color.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/color.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/color.o: /usr/include/sys/_types/_clock_t.h
.o/color.o: /usr/include/sys/_types/_time_t.h
.o/color.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/color1.o: /usr/include/strings.h /usr/include/_types.h
.o/color1.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/color1.o: /usr/include/sys/_symbol_aliasing.h
.o/color1.o: /usr/include/sys/_posix_availability.h
.o/color1.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color1.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color1.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color1.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/color1.o: /usr/include/sys/_types/_null.h
.o/color1.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/color1.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/color1.o: /usr/include/sys/_types/_int16_t.h
.o/color1.o: /usr/include/sys/_types/_int32_t.h
.o/color1.o: /usr/include/sys/_types/_int64_t.h
.o/color1.o: /usr/include/sys/_types/_u_int8_t.h
.o/color1.o: /usr/include/sys/_types/_u_int16_t.h
.o/color1.o: /usr/include/sys/_types/_u_int32_t.h
.o/color1.o: /usr/include/sys/_types/_u_int64_t.h
.o/color1.o: /usr/include/sys/_types/_intptr_t.h
.o/color1.o: /usr/include/sys/_types/_uintptr_t.h
.o/color1.o: /usr/include/sys/_types/_errno_t.h
.o/color1.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/color1.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/color1.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/color1.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color1.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/color1.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/color1.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color1.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/color1.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/color1.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_gl.h
.o/color1.o: my_color.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/color1.o: my_string.h /usr/include/wchar.h
.o/color1.o: /usr/include/sys/_types/_mbstate_t.h
.o/color1.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color1.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/color1.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/color1.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color1.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/color1.o: /usr/include/sys/_types/_clock_t.h
.o/color1.o: /usr/include/sys/_types/_time_t.h
.o/color1.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color1.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color1.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color1.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/color2.o: /usr/include/strings.h /usr/include/_types.h
.o/color2.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/color2.o: /usr/include/sys/_symbol_aliasing.h
.o/color2.o: /usr/include/sys/_posix_availability.h
.o/color2.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color2.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color2.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color2.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/color2.o: /usr/include/sys/_types/_null.h
.o/color2.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/color2.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/color2.o: /usr/include/sys/_types/_int16_t.h
.o/color2.o: /usr/include/sys/_types/_int32_t.h
.o/color2.o: /usr/include/sys/_types/_int64_t.h
.o/color2.o: /usr/include/sys/_types/_u_int8_t.h
.o/color2.o: /usr/include/sys/_types/_u_int16_t.h
.o/color2.o: /usr/include/sys/_types/_u_int32_t.h
.o/color2.o: /usr/include/sys/_types/_u_int64_t.h
.o/color2.o: /usr/include/sys/_types/_intptr_t.h
.o/color2.o: /usr/include/sys/_types/_uintptr_t.h
.o/color2.o: /usr/include/sys/_types/_errno_t.h
.o/color2.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/color2.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/color2.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/color2.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color2.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/color2.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/color2.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color2.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/color2.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/color2.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_gl.h
.o/color2.o: my_color.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/color2.o: my_string.h /usr/include/wchar.h
.o/color2.o: /usr/include/sys/_types/_mbstate_t.h
.o/color2.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color2.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/color2.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/color2.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color2.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/color2.o: /usr/include/sys/_types/_clock_t.h
.o/color2.o: /usr/include/sys/_types/_time_t.h
.o/color2.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color2.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color2.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color2.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/color3.o: /usr/include/strings.h /usr/include/_types.h
.o/color3.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/color3.o: /usr/include/sys/_symbol_aliasing.h
.o/color3.o: /usr/include/sys/_posix_availability.h
.o/color3.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color3.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color3.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color3.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/color3.o: /usr/include/sys/_types/_null.h
.o/color3.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/color3.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/color3.o: /usr/include/sys/_types/_int16_t.h
.o/color3.o: /usr/include/sys/_types/_int32_t.h
.o/color3.o: /usr/include/sys/_types/_int64_t.h
.o/color3.o: /usr/include/sys/_types/_u_int8_t.h
.o/color3.o: /usr/include/sys/_types/_u_int16_t.h
.o/color3.o: /usr/include/sys/_types/_u_int32_t.h
.o/color3.o: /usr/include/sys/_types/_u_int64_t.h
.o/color3.o: /usr/include/sys/_types/_intptr_t.h
.o/color3.o: /usr/include/sys/_types/_uintptr_t.h
.o/color3.o: /usr/include/sys/_types/_errno_t.h
.o/color3.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/color3.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/color3.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/color3.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color3.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/color3.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/color3.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color3.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/color3.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/color3.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_gl.h
.o/color3.o: my_color.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/color3.o: my_string.h /usr/include/wchar.h
.o/color3.o: /usr/include/sys/_types/_mbstate_t.h
.o/color3.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color3.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/color3.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/color3.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color3.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/color3.o: /usr/include/sys/_types/_clock_t.h
.o/color3.o: /usr/include/sys/_types/_time_t.h
.o/color3.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color3.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color3.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color3.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/color4.o: /usr/include/strings.h /usr/include/_types.h
.o/color4.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/color4.o: /usr/include/sys/_symbol_aliasing.h
.o/color4.o: /usr/include/sys/_posix_availability.h
.o/color4.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color4.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color4.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color4.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/color4.o: /usr/include/sys/_types/_null.h
.o/color4.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/color4.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/color4.o: /usr/include/sys/_types/_int16_t.h
.o/color4.o: /usr/include/sys/_types/_int32_t.h
.o/color4.o: /usr/include/sys/_types/_int64_t.h
.o/color4.o: /usr/include/sys/_types/_u_int8_t.h
.o/color4.o: /usr/include/sys/_types/_u_int16_t.h
.o/color4.o: /usr/include/sys/_types/_u_int32_t.h
.o/color4.o: /usr/include/sys/_types/_u_int64_t.h
.o/color4.o: /usr/include/sys/_types/_intptr_t.h
.o/color4.o: /usr/include/sys/_types/_uintptr_t.h
.o/color4.o: /usr/include/sys/_types/_errno_t.h
.o/color4.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/color4.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/color4.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/color4.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color4.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/color4.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/color4.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color4.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/color4.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/color4.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_gl.h
.o/color4.o: my_color.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/color4.o: my_string.h /usr/include/wchar.h
.o/color4.o: /usr/include/sys/_types/_mbstate_t.h
.o/color4.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color4.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/color4.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/color4.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color4.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/color4.o: /usr/include/sys/_types/_clock_t.h
.o/color4.o: /usr/include/sys/_types/_time_t.h
.o/color4.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color4.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color4.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color4.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/command.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/command.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/command.o: /usr/include/sys/_posix_availability.h
.o/command.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/command.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/command.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/command.o: /usr/include/sys/_pthread/_pthread_types.h
.o/command.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/command.o: /usr/include/sys/_types/_int8_t.h
.o/command.o: /usr/include/sys/_types/_int16_t.h
.o/command.o: /usr/include/sys/_types/_int32_t.h
.o/command.o: /usr/include/sys/_types/_int64_t.h
.o/command.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/command.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/command.o: /usr/include/sys/_types/_intptr_t.h
.o/command.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/command.o: /usr/include/sys/_types/_u_int8_t.h
.o/command.o: /usr/include/sys/_types/_u_int16_t.h
.o/command.o: /usr/include/sys/_types/_u_int32_t.h
.o/command.o: /usr/include/sys/_types/_u_int64_t.h
.o/command.o: /usr/include/sys/_types/_uintptr_t.h
.o/command.o: /usr/include/_types/_intmax_t.h
.o/command.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/command.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/command.o: /usr/include/assert.h my_vector_bounds_check.h
.o/command.o: c_plus_plus_serializer.h my_python.h my_point.h my_math.h
.o/command.o: /usr/include/math.h my_command.h my_token.h my_string.h
.o/command.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/command.o: /usr/include/sys/_types/_size_t.h
.o/command.o: /usr/include/sys/_types/_mbstate_t.h
.o/command.o: /usr/include/sys/_types/_ct_rune_t.h
.o/command.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/command.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/command.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/command.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/command.o: /usr/include/secure/_common.h /usr/include/time.h
.o/command.o: /usr/include/sys/_types/_clock_t.h
.o/command.o: /usr/include/sys/_types/_time_t.h
.o/command.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/command.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/command.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/command.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/command.o: my_command_history.h
.o/console.o: my_console.h my_thing_template.h my_dice.h my_tile.h my_sdl.h
.o/console.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/console.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/console.o: /usr/include/sys/_posix_availability.h
.o/console.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/console.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/console.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/console.o: /usr/include/sys/_pthread/_pthread_types.h
.o/console.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/console.o: /usr/include/sys/_types/_int8_t.h
.o/console.o: /usr/include/sys/_types/_int16_t.h
.o/console.o: /usr/include/sys/_types/_int32_t.h
.o/console.o: /usr/include/sys/_types/_int64_t.h
.o/console.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/console.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/console.o: /usr/include/sys/_types/_intptr_t.h
.o/console.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/console.o: /usr/include/sys/_types/_u_int8_t.h
.o/console.o: /usr/include/sys/_types/_u_int16_t.h
.o/console.o: /usr/include/sys/_types/_u_int32_t.h
.o/console.o: /usr/include/sys/_types/_u_int64_t.h
.o/console.o: /usr/include/sys/_types/_uintptr_t.h
.o/console.o: /usr/include/_types/_intmax_t.h
.o/console.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/console.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/console.o: /usr/include/assert.h my_vector_bounds_check.h
.o/console.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/console.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/console.o: /usr/include/sys/_types/_size_t.h
.o/console.o: /usr/include/sys/_types/_mbstate_t.h
.o/console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/console.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/console.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/console.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/console.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/console.o: /usr/include/secure/_common.h /usr/include/time.h
.o/console.o: /usr/include/sys/_types/_clock_t.h
.o/console.o: /usr/include/sys/_types/_time_t.h
.o/console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/console.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/console.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/console.o: my_math.h /usr/include/math.h my_color.h my_size.h
.o/dice.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/dice.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/dice.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/dice.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/dice.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/dice.o: /usr/include/i386/_types.h
.o/dice.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dice.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dice.o: /usr/include/sys/_types/_int8_t.h
.o/dice.o: /usr/include/sys/_types/_int16_t.h
.o/dice.o: /usr/include/sys/_types/_int32_t.h
.o/dice.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/dice.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dice.o: /usr/include/_types/_uint64_t.h
.o/dice.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/dice.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/dice.o: /usr/include/sys/_types/_u_int16_t.h
.o/dice.o: /usr/include/sys/_types/_u_int32_t.h
.o/dice.o: /usr/include/sys/_types/_u_int64_t.h
.o/dice.o: /usr/include/sys/_types/_uintptr_t.h
.o/dice.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dice.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/dice.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dice.o: c_plus_plus_serializer.h my_string.h /usr/include/wchar.h
.o/dice.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/dice.o: /usr/include/sys/_types/_mbstate_t.h
.o/dice.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dice.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/dice.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/dice.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/dice.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dice.o: /usr/include/secure/_common.h /usr/include/time.h
.o/dice.o: /usr/include/sys/_types/_clock_t.h
.o/dice.o: /usr/include/sys/_types/_time_t.h
.o/dice.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/dice.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/dice.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/dice.o: /usr/include/_ctype.h /usr/include/runetype.h my_dice.h
.o/dict1.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/dict1.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/dict1.o: /usr/include/sys/_posix_availability.h
.o/dict1.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dict1.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/dict1.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dict1.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dict1.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dict1.o: /usr/include/sys/_types/_int8_t.h
.o/dict1.o: /usr/include/sys/_types/_int16_t.h
.o/dict1.o: /usr/include/sys/_types/_int32_t.h
.o/dict1.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/dict1.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dict1.o: /usr/include/_types/_uint64_t.h
.o/dict1.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/dict1.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/dict1.o: /usr/include/sys/_types/_u_int16_t.h
.o/dict1.o: /usr/include/sys/_types/_u_int32_t.h
.o/dict1.o: /usr/include/sys/_types/_u_int64_t.h
.o/dict1.o: /usr/include/sys/_types/_uintptr_t.h
.o/dict1.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dict1.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/dict1.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dict1.o: c_plus_plus_serializer.h
.o/dict2.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/dict2.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/dict2.o: /usr/include/sys/_posix_availability.h
.o/dict2.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dict2.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/dict2.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dict2.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dict2.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dict2.o: /usr/include/sys/_types/_int8_t.h
.o/dict2.o: /usr/include/sys/_types/_int16_t.h
.o/dict2.o: /usr/include/sys/_types/_int32_t.h
.o/dict2.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/dict2.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dict2.o: /usr/include/_types/_uint64_t.h
.o/dict2.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/dict2.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/dict2.o: /usr/include/sys/_types/_u_int16_t.h
.o/dict2.o: /usr/include/sys/_types/_u_int32_t.h
.o/dict2.o: /usr/include/sys/_types/_u_int64_t.h
.o/dict2.o: /usr/include/sys/_types/_uintptr_t.h
.o/dict2.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dict2.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/dict2.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dict2.o: c_plus_plus_serializer.h
.o/dir.o: /usr/include/strings.h /usr/include/_types.h
.o/dir.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/dir.o: /usr/include/sys/_symbol_aliasing.h
.o/dir.o: /usr/include/sys/_posix_availability.h
.o/dir.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dir.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dir.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/dir.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_rsize_t.h
.o/dir.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/dir.o: /usr/include/sys/_types/_int8_t.h
.o/dir.o: /usr/include/sys/_types/_int16_t.h
.o/dir.o: /usr/include/sys/_types/_int32_t.h
.o/dir.o: /usr/include/sys/_types/_int64_t.h
.o/dir.o: /usr/include/sys/_types/_u_int8_t.h
.o/dir.o: /usr/include/sys/_types/_u_int16_t.h
.o/dir.o: /usr/include/sys/_types/_u_int32_t.h
.o/dir.o: /usr/include/sys/_types/_u_int64_t.h
.o/dir.o: /usr/include/sys/_types/_intptr_t.h
.o/dir.o: /usr/include/sys/_types/_uintptr_t.h
.o/dir.o: /usr/include/sys/_types/_errno_t.h
.o/dir.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/dir.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/dir.o: /usr/include/sys/param.h /usr/include/sys/types.h
.o/dir.o: /usr/include/sys/appleapiopts.h /usr/include/machine/endian.h
.o/dir.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/dir.o: /usr/include/libkern/_OSByteOrder.h
.o/dir.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/dir.o: /usr/include/sys/_types/_u_char.h
.o/dir.o: /usr/include/sys/_types/_u_short.h /usr/include/sys/_types/_u_int.h
.o/dir.o: /usr/include/sys/_types/_caddr_t.h /usr/include/sys/_types/_dev_t.h
.o/dir.o: /usr/include/sys/_types/_blkcnt_t.h
.o/dir.o: /usr/include/sys/_types/_blksize_t.h
.o/dir.o: /usr/include/sys/_types/_gid_t.h
.o/dir.o: /usr/include/sys/_types/_in_addr_t.h
.o/dir.o: /usr/include/sys/_types/_in_port_t.h
.o/dir.o: /usr/include/sys/_types/_ino_t.h /usr/include/sys/_types/_ino64_t.h
.o/dir.o: /usr/include/sys/_types/_key_t.h /usr/include/sys/_types/_mode_t.h
.o/dir.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
.o/dir.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_off_t.h
.o/dir.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_clock_t.h
.o/dir.o: /usr/include/sys/_types/_time_t.h
.o/dir.o: /usr/include/sys/_types/_useconds_t.h
.o/dir.o: /usr/include/sys/_types/_suseconds_t.h
.o/dir.o: /usr/include/sys/_types/_fd_def.h
.o/dir.o: /usr/include/sys/_types/_fd_setsize.h
.o/dir.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/dir.o: /usr/include/sys/_types/_fd_zero.h
.o/dir.o: /usr/include/sys/_types/_fd_isset.h
.o/dir.o: /usr/include/sys/_types/_fd_copy.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_cond_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_condattr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_mutex_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_mutexattr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_once_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_rwlock_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_rwlockattr_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_t.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_key_t.h
.o/dir.o: /usr/include/sys/_types/_fsblkcnt_t.h
.o/dir.o: /usr/include/sys/_types/_fsfilcnt_t.h /usr/include/sys/syslimits.h
.o/dir.o: /usr/include/machine/param.h /usr/include/i386/param.h
.o/dir.o: /usr/include/i386/_param.h /usr/include/limits.h
.o/dir.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/dir.o: /usr/include/i386/_limits.h /usr/include/sys/signal.h
.o/dir.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/dir.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/dir.o: /usr/include/mach/machine/_structs.h
.o/dir.o: /usr/include/mach/i386/_structs.h
.o/dir.o: /usr/include/sys/_types/_sigaltstack.h
.o/dir.o: /usr/include/sys/_types/_ucontext.h
.o/dir.o: /usr/include/sys/_types/_sigset_t.h /usr/include/unistd.h
.o/dir.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/dir.o: /usr/include/sys/_types/_seek_set.h /usr/include/_types/_uint64_t.h
.o/dir.o: /usr/include/_types/_uint32_t.h /usr/include/sys/select.h
.o/dir.o: /usr/include/sys/_types/_timespec.h
.o/dir.o: /usr/include/sys/_types/_timeval.h /usr/include/sys/_select.h
.o/dir.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/dir.o: /usr/include/sys/stat.h /usr/include/sys/_types/_s_ifmt.h
.o/dir.o: /usr/include/sys/_types/_filesec_t.h my_main.h my_sys.h
.o/dir.o: my_pcg_basic.h /usr/include/inttypes.h
.o/dir.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dir.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/dir.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dir.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/dir.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dir.o: c_plus_plus_serializer.h my_dir.h my_string.h /usr/include/wchar.h
.o/dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/dir.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/dir.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/dir.o: /usr/include/time.h /usr/include/_wctype.h /usr/include/__wctype.h
.o/dir.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/dir.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/dmap.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/dmap.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/dmap.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/dmap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/dmap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/dmap.o: /usr/include/i386/_types.h
.o/dmap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dmap.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dmap.o: /usr/include/sys/_types/_int8_t.h
.o/dmap.o: /usr/include/sys/_types/_int16_t.h
.o/dmap.o: /usr/include/sys/_types/_int32_t.h
.o/dmap.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/dmap.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dmap.o: /usr/include/_types/_uint64_t.h
.o/dmap.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/dmap.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/dmap.o: /usr/include/sys/_types/_u_int16_t.h
.o/dmap.o: /usr/include/sys/_types/_u_int32_t.h
.o/dmap.o: /usr/include/sys/_types/_u_int64_t.h
.o/dmap.o: /usr/include/sys/_types/_uintptr_t.h
.o/dmap.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dmap.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/dmap.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dmap.o: c_plus_plus_serializer.h my_dmap.h my_point.h my_math.h
.o/dmap.o: /usr/include/math.h my_sprintf.h
.o/dungeon.o: my_dungeon.h my_room.h my_main.h my_sys.h my_pcg_basic.h
.o/dungeon.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/dungeon.o: /usr/include/sys/_symbol_aliasing.h
.o/dungeon.o: /usr/include/sys/_posix_availability.h
.o/dungeon.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dungeon.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/dungeon.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dungeon.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dungeon.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dungeon.o: /usr/include/sys/_types/_int8_t.h
.o/dungeon.o: /usr/include/sys/_types/_int16_t.h
.o/dungeon.o: /usr/include/sys/_types/_int32_t.h
.o/dungeon.o: /usr/include/sys/_types/_int64_t.h
.o/dungeon.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/dungeon.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/dungeon.o: /usr/include/sys/_types/_intptr_t.h
.o/dungeon.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/dungeon.o: /usr/include/sys/_types/_u_int8_t.h
.o/dungeon.o: /usr/include/sys/_types/_u_int16_t.h
.o/dungeon.o: /usr/include/sys/_types/_u_int32_t.h
.o/dungeon.o: /usr/include/sys/_types/_u_int64_t.h
.o/dungeon.o: /usr/include/sys/_types/_uintptr_t.h
.o/dungeon.o: /usr/include/_types/_intmax_t.h
.o/dungeon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/dungeon.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/dungeon.o: /usr/include/assert.h my_vector_bounds_check.h
.o/dungeon.o: c_plus_plus_serializer.h my_point.h my_math.h
.o/dungeon.o: /usr/include/math.h my_depth.h my_charmap.h my_dmap.h
.o/dungeon.o: my_level_static.h my_dungeon_grid.h
.o/dungeon_grid.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/dungeon_grid.o: /usr/include/sys/cdefs.h
.o/dungeon_grid.o: /usr/include/sys/_symbol_aliasing.h
.o/dungeon_grid.o: /usr/include/sys/_posix_availability.h
.o/dungeon_grid.o: /usr/include/Availability.h
.o/dungeon_grid.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/dungeon_grid.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/dungeon_grid.o: /usr/include/i386/_types.h
.o/dungeon_grid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dungeon_grid.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/dungeon_grid.o: /usr/include/sys/_types/_int8_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_int16_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_int32_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_int64_t.h
.o/dungeon_grid.o: /usr/include/_types/_uint8_t.h
.o/dungeon_grid.o: /usr/include/_types/_uint16_t.h
.o/dungeon_grid.o: /usr/include/_types/_uint32_t.h
.o/dungeon_grid.o: /usr/include/_types/_uint64_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_intptr_t.h
.o/dungeon_grid.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/dungeon_grid.o: /usr/include/sys/_types/_u_int8_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_u_int16_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_u_int32_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_u_int64_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_uintptr_t.h
.o/dungeon_grid.o: /usr/include/_types/_intmax_t.h
.o/dungeon_grid.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/dungeon_grid.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/dungeon_grid.o: my_bounds_check.h /usr/include/assert.h
.o/dungeon_grid.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/dungeon_grid.o: my_dmap.h my_point.h my_math.h /usr/include/math.h
.o/dungeon_grid.o: my_dungeon_grid.h
.o/file.o: /usr/include/strings.h /usr/include/_types.h
.o/file.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/file.o: /usr/include/sys/_symbol_aliasing.h
.o/file.o: /usr/include/sys/_posix_availability.h
.o/file.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/file.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/file.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/file.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_rsize_t.h
.o/file.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/file.o: /usr/include/sys/_types/_int8_t.h
.o/file.o: /usr/include/sys/_types/_int16_t.h
.o/file.o: /usr/include/sys/_types/_int32_t.h
.o/file.o: /usr/include/sys/_types/_int64_t.h
.o/file.o: /usr/include/sys/_types/_u_int8_t.h
.o/file.o: /usr/include/sys/_types/_u_int16_t.h
.o/file.o: /usr/include/sys/_types/_u_int32_t.h
.o/file.o: /usr/include/sys/_types/_u_int64_t.h
.o/file.o: /usr/include/sys/_types/_intptr_t.h
.o/file.o: /usr/include/sys/_types/_uintptr_t.h
.o/file.o: /usr/include/sys/_types/_errno_t.h
.o/file.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/file.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/file.o: /usr/include/sys/stat.h /usr/include/sys/_types/_timespec.h
.o/file.o: /usr/include/sys/_types/_blkcnt_t.h
.o/file.o: /usr/include/sys/_types/_blksize_t.h
.o/file.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_ino_t.h
.o/file.o: /usr/include/sys/_types/_ino64_t.h
.o/file.o: /usr/include/sys/_types/_mode_t.h
.o/file.o: /usr/include/sys/_types/_nlink_t.h
.o/file.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/file.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_time_t.h
.o/file.o: /usr/include/sys/_types/_s_ifmt.h
.o/file.o: /usr/include/sys/_types/_filesec_t.h /usr/include/unistd.h
.o/file.o: /usr/include/sys/unistd.h
.o/file.o: /usr/include/sys/_types/_posix_vdisable.h
.o/file.o: /usr/include/sys/_types/_seek_set.h
.o/file.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_uint32_t.h
.o/file.o: /usr/include/sys/_types/_pid_t.h
.o/file.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/file.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/file.o: /usr/include/sys/_types/_timeval.h
.o/file.o: /usr/include/sys/_types/_suseconds_t.h
.o/file.o: /usr/include/sys/_types/_sigset_t.h
.o/file.o: /usr/include/sys/_types/_fd_setsize.h
.o/file.o: /usr/include/sys/_types/_fd_set.h
.o/file.o: /usr/include/sys/_types/_fd_clr.h
.o/file.o: /usr/include/sys/_types/_fd_isset.h
.o/file.o: /usr/include/sys/_types/_fd_zero.h
.o/file.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/file.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/file.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/file.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/file.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/file.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/file.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/file.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/file.o: c_plus_plus_serializer.h my_file.h
.o/file_log.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/file_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/file_log.o: /usr/include/sys/_posix_availability.h
.o/file_log.o: /usr/include/Availability.h
.o/file_log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/file_log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/file_log.o: /usr/include/i386/_types.h
.o/file_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/file_log.o: /usr/include/sys/_types/_int8_t.h
.o/file_log.o: /usr/include/sys/_types/_int16_t.h
.o/file_log.o: /usr/include/sys/_types/_int32_t.h
.o/file_log.o: /usr/include/sys/_types/_int64_t.h
.o/file_log.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/file_log.o: /usr/include/_types/_uint32_t.h
.o/file_log.o: /usr/include/_types/_uint64_t.h
.o/file_log.o: /usr/include/sys/_types/_intptr_t.h
.o/file_log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/file_log.o: /usr/include/sys/_types/_u_int8_t.h
.o/file_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/file_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/file_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/file_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/file_log.o: /usr/include/_types/_intmax_t.h
.o/file_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/file_log.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/file_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/file_log.o: c_plus_plus_serializer.h my_time.h my_sdl.h my_command.h
.o/file_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/file_log.o: /usr/include/sys/_types/_null.h
.o/file_log.o: /usr/include/sys/_types/_size_t.h
.o/file_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/file_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/file_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/file_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/file_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/file_log.o: /usr/include/sys/_types/_ssize_t.h
.o/file_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/file_log.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/file_log.o: /usr/include/sys/_types/_time_t.h
.o/file_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/file_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/file_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/file_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_log.h
.o/file_read.o: /usr/include/strings.h /usr/include/_types.h
.o/file_read.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/file_read.o: /usr/include/sys/_symbol_aliasing.h
.o/file_read.o: /usr/include/sys/_posix_availability.h
.o/file_read.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/file_read.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file_read.o: /usr/include/Availability.h
.o/file_read.o: /usr/include/AvailabilityInternal.h
.o/file_read.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/file_read.o: /usr/include/sys/_types/_null.h
.o/file_read.o: /usr/include/sys/_types/_rsize_t.h
.o/file_read.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/file_read.o: /usr/include/sys/_types/_int8_t.h
.o/file_read.o: /usr/include/sys/_types/_int16_t.h
.o/file_read.o: /usr/include/sys/_types/_int32_t.h
.o/file_read.o: /usr/include/sys/_types/_int64_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int8_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int16_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int32_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int64_t.h
.o/file_read.o: /usr/include/sys/_types/_intptr_t.h
.o/file_read.o: /usr/include/sys/_types/_uintptr_t.h
.o/file_read.o: /usr/include/sys/_types/_errno_t.h
.o/file_read.o: /usr/include/sys/_types/_ssize_t.h
.o/file_read.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
.o/file_read.o: /usr/include/secure/_strings.h my_main.h my_sys.h
.o/file_read.o: my_pcg_basic.h /usr/include/inttypes.h
.o/file_read.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/file_read.o: /usr/include/_types/_uint8_t.h
.o/file_read.o: /usr/include/_types/_uint16_t.h
.o/file_read.o: /usr/include/_types/_uint32_t.h
.o/file_read.o: /usr/include/_types/_uint64_t.h
.o/file_read.o: /usr/include/_types/_intmax_t.h
.o/file_read.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/file_read.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/file_read.o: /usr/include/assert.h my_vector_bounds_check.h
.o/file_read.o: c_plus_plus_serializer.h my_string.h /usr/include/wchar.h
.o/file_read.o: /usr/include/sys/_types/_mbstate_t.h
.o/file_read.o: /usr/include/sys/_types/_ct_rune_t.h
.o/file_read.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/file_read.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/file_read.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/file_read.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/file_read.o: /usr/include/sys/_types/_clock_t.h
.o/file_read.o: /usr/include/sys/_types/_time_t.h
.o/file_read.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/file_read.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/file_read.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/file_read.o: /usr/include/_ctype.h /usr/include/runetype.h my_file.h
.o/font.o: my_ttf.h my_font.h my_tile.h my_sdl.h my_main.h my_sys.h
.o/font.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/font.o: /usr/include/sys/_symbol_aliasing.h
.o/font.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/font.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/font.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/font.o: /usr/include/i386/_types.h
.o/font.o: /usr/include/sys/_pthread/_pthread_types.h
.o/font.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/font.o: /usr/include/sys/_types/_int8_t.h
.o/font.o: /usr/include/sys/_types/_int16_t.h
.o/font.o: /usr/include/sys/_types/_int32_t.h
.o/font.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/font.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/font.o: /usr/include/_types/_uint64_t.h
.o/font.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/font.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/font.o: /usr/include/sys/_types/_u_int16_t.h
.o/font.o: /usr/include/sys/_types/_u_int32_t.h
.o/font.o: /usr/include/sys/_types/_u_int64_t.h
.o/font.o: /usr/include/sys/_types/_uintptr_t.h
.o/font.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/font.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/font.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/font.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/font.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/font.o: /usr/include/sys/_types/_size_t.h
.o/font.o: /usr/include/sys/_types/_mbstate_t.h
.o/font.o: /usr/include/sys/_types/_ct_rune_t.h
.o/font.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/font.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/font.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/font.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/font.o: /usr/include/secure/_common.h /usr/include/time.h
.o/font.o: /usr/include/sys/_types/_clock_t.h
.o/font.o: /usr/include/sys/_types/_time_t.h
.o/font.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/font.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/font.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/font.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/font.o: my_math.h /usr/include/math.h my_color.h
.o/game.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/game.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/game.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game.o: /usr/include/i386/_types.h
.o/game.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game.o: /usr/include/sys/_types/_int8_t.h
.o/game.o: /usr/include/sys/_types/_int16_t.h
.o/game.o: /usr/include/sys/_types/_int32_t.h
.o/game.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/game.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/game.o: /usr/include/_types/_uint64_t.h
.o/game.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/game.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/game.o: /usr/include/sys/_types/_u_int16_t.h
.o/game.o: /usr/include/sys/_types/_u_int32_t.h
.o/game.o: /usr/include/sys/_types/_u_int64_t.h
.o/game.o: /usr/include/sys/_types/_uintptr_t.h
.o/game.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/game.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/game.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/game.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/game.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/game.o: /usr/include/sys/_types/_mbstate_t.h
.o/game.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/game.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game.o: /usr/include/sys/_types/_clock_t.h
.o/game.o: /usr/include/sys/_types/_time_t.h
.o/game.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_particle.h
.o/game.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/game.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/game_config.o: my_game.h my_world.h my_point.h my_math.h
.o/game_config.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_config.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config.o: /usr/include/sys/_posix_availability.h
.o/game_config.o: /usr/include/Availability.h
.o/game_config.o: /usr/include/AvailabilityInternal.h
.o/game_config.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_config.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_config.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_config.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/game_config.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_config.o: /usr/include/sys/_types/_int8_t.h
.o/game_config.o: /usr/include/sys/_types/_int16_t.h
.o/game_config.o: /usr/include/sys/_types/_int32_t.h
.o/game_config.o: /usr/include/sys/_types/_int64_t.h
.o/game_config.o: /usr/include/_types/_uint8_t.h
.o/game_config.o: /usr/include/_types/_uint16_t.h
.o/game_config.o: /usr/include/_types/_uint32_t.h
.o/game_config.o: /usr/include/_types/_uint64_t.h
.o/game_config.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_config.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config.o: /usr/include/_types/_intmax_t.h
.o/game_config.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_config.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_config.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_config.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_config.o: /usr/include/sys/_types/_null.h
.o/game_config.o: /usr/include/sys/_types/_size_t.h
.o/game_config.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_config.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_config.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_config.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_config.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_config.o: /usr/include/sys/_types/_time_t.h
.o/game_config.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_config.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_config.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_config.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_config.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_config.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_config.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/game_config.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/game_config.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/game_config.o: my_wid_rightbar.h my_wid_leftbar.h my_wid_inventory.h
.o/game_config.o: my_wid_thing_info.h my_wid_thing_collect.h
.o/game_config_gfx.o: my_game.h my_world.h my_point.h my_math.h
.o/game_config_gfx.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_config_gfx.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_gfx.o: /usr/include/sys/_posix_availability.h
.o/game_config_gfx.o: /usr/include/Availability.h
.o/game_config_gfx.o: /usr/include/AvailabilityInternal.h
.o/game_config_gfx.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_config_gfx.o: my_main.h my_sys.h my_pcg_basic.h
.o/game_config_gfx.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game_config_gfx.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_config_gfx.o: /usr/include/i386/_types.h
.o/game_config_gfx.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config_gfx.o: /usr/include/sys/_types/_wchar_t.h
.o/game_config_gfx.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_int16_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_int32_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_int64_t.h
.o/game_config_gfx.o: /usr/include/_types/_uint8_t.h
.o/game_config_gfx.o: /usr/include/_types/_uint16_t.h
.o/game_config_gfx.o: /usr/include/_types/_uint32_t.h
.o/game_config_gfx.o: /usr/include/_types/_uint64_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config_gfx.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_config_gfx.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config_gfx.o: /usr/include/_types/_intmax_t.h
.o/game_config_gfx.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_config_gfx.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_config_gfx.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_gfx.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_config_gfx.o: my_string.h /usr/include/wchar.h
.o/game_config_gfx.o: /usr/include/sys/_types/_null.h
.o/game_config_gfx.o: /usr/include/sys/_types/_size_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_config_gfx.o: /usr/include/_stdio.h
.o/game_config_gfx.o: /usr/include/sys/_types/_va_list.h
.o/game_config_gfx.o: /usr/include/sys/stdio.h
.o/game_config_gfx.o: /usr/include/sys/_types/_off_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_gfx.o: /usr/include/secure/_stdio.h
.o/game_config_gfx.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game_config_gfx.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_time_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_timespec.h
.o/game_config_gfx.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_gfx.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_gfx.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_gfx.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_config_gfx.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_config_gfx.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_config_gfx.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_config_gfx.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h
.o/game_config_gfx.o: my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/game_config_gfx.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/game_config_keyboard.o: my_game.h my_world.h my_point.h my_math.h
.o/game_config_keyboard.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_config_keyboard.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_keyboard.o: /usr/include/sys/_posix_availability.h
.o/game_config_keyboard.o: /usr/include/Availability.h
.o/game_config_keyboard.o: /usr/include/AvailabilityInternal.h
.o/game_config_keyboard.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/game_config_keyboard.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/game_config_keyboard.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game_config_keyboard.o: /usr/include/sys/_types.h
.o/game_config_keyboard.o: /usr/include/machine/_types.h
.o/game_config_keyboard.o: /usr/include/i386/_types.h
.o/game_config_keyboard.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_wchar_t.h
.o/game_config_keyboard.o: /usr/include/stdint.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int8_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int16_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int32_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_int64_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint8_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint16_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint32_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uint64_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config_keyboard.o: /usr/include/machine/types.h
.o/game_config_keyboard.o: /usr/include/i386/types.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config_keyboard.o: /usr/include/_types/_intmax_t.h
.o/game_config_keyboard.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_config_keyboard.o: my_globals.h my_callstack.h
.o/game_config_keyboard.o: my_array_bounds_check.h my_bounds_check.h
.o/game_config_keyboard.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_config_keyboard.o: my_command.h my_token.h my_string.h
.o/game_config_keyboard.o: /usr/include/wchar.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_null.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_size_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_rune_t.h
.o/game_config_keyboard.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_va_list.h
.o/game_config_keyboard.o: /usr/include/sys/stdio.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_off_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_keyboard.o: /usr/include/secure/_stdio.h
.o/game_config_keyboard.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_time_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_timespec.h
.o/game_config_keyboard.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_keyboard.o: /usr/include/_types/_wctype_t.h
.o/game_config_keyboard.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/game_config_keyboard.o: /usr/include/runetype.h slre.h my_particle.h
.o/game_config_keyboard.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_config_keyboard.o: my_depth.h my_charmap.h my_dmap.h
.o/game_config_keyboard.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_config_keyboard.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h
.o/game_config_keyboard.o: my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/game_config_keyboard.o: my_light.h my_thing_template.h my_dice.h
.o/game_config_keyboard.o: my_thing_ai.h my_game_notice.h
.o/game_config_other.o: my_game.h my_world.h my_point.h my_math.h
.o/game_config_other.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_config_other.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_other.o: /usr/include/sys/_posix_availability.h
.o/game_config_other.o: /usr/include/Availability.h
.o/game_config_other.o: /usr/include/AvailabilityInternal.h
.o/game_config_other.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/game_config_other.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/game_config_other.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game_config_other.o: /usr/include/sys/_types.h
.o/game_config_other.o: /usr/include/machine/_types.h
.o/game_config_other.o: /usr/include/i386/_types.h
.o/game_config_other.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config_other.o: /usr/include/sys/_types/_wchar_t.h
.o/game_config_other.o: /usr/include/stdint.h
.o/game_config_other.o: /usr/include/sys/_types/_int8_t.h
.o/game_config_other.o: /usr/include/sys/_types/_int16_t.h
.o/game_config_other.o: /usr/include/sys/_types/_int32_t.h
.o/game_config_other.o: /usr/include/sys/_types/_int64_t.h
.o/game_config_other.o: /usr/include/_types/_uint8_t.h
.o/game_config_other.o: /usr/include/_types/_uint16_t.h
.o/game_config_other.o: /usr/include/_types/_uint32_t.h
.o/game_config_other.o: /usr/include/_types/_uint64_t.h
.o/game_config_other.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config_other.o: /usr/include/machine/types.h
.o/game_config_other.o: /usr/include/i386/types.h
.o/game_config_other.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config_other.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config_other.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config_other.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config_other.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config_other.o: /usr/include/_types/_intmax_t.h
.o/game_config_other.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_config_other.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_config_other.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_other.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_config_other.o: my_string.h /usr/include/wchar.h
.o/game_config_other.o: /usr/include/sys/_types/_null.h
.o/game_config_other.o: /usr/include/sys/_types/_size_t.h
.o/game_config_other.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_other.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_other.o: /usr/include/sys/_types/_rune_t.h
.o/game_config_other.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_config_other.o: /usr/include/sys/_types/_va_list.h
.o/game_config_other.o: /usr/include/sys/stdio.h
.o/game_config_other.o: /usr/include/sys/_types/_off_t.h
.o/game_config_other.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_other.o: /usr/include/secure/_stdio.h
.o/game_config_other.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game_config_other.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_other.o: /usr/include/sys/_types/_time_t.h
.o/game_config_other.o: /usr/include/sys/_types/_timespec.h
.o/game_config_other.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_other.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_other.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_other.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_config_other.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_config_other.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_config_other.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_config_other.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h
.o/game_config_other.o: my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/game_config_other.o: my_light.h my_thing_template.h my_dice.h
.o/game_config_other.o: my_thing_ai.h
.o/game_config_sound.o: my_game.h my_world.h my_point.h my_math.h
.o/game_config_sound.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_config_sound.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_sound.o: /usr/include/sys/_posix_availability.h
.o/game_config_sound.o: /usr/include/Availability.h
.o/game_config_sound.o: /usr/include/AvailabilityInternal.h
.o/game_config_sound.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/game_config_sound.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/game_config_sound.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game_config_sound.o: /usr/include/sys/_types.h
.o/game_config_sound.o: /usr/include/machine/_types.h
.o/game_config_sound.o: /usr/include/i386/_types.h
.o/game_config_sound.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config_sound.o: /usr/include/sys/_types/_wchar_t.h
.o/game_config_sound.o: /usr/include/stdint.h
.o/game_config_sound.o: /usr/include/sys/_types/_int8_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_int16_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_int32_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_int64_t.h
.o/game_config_sound.o: /usr/include/_types/_uint8_t.h
.o/game_config_sound.o: /usr/include/_types/_uint16_t.h
.o/game_config_sound.o: /usr/include/_types/_uint32_t.h
.o/game_config_sound.o: /usr/include/_types/_uint64_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config_sound.o: /usr/include/machine/types.h
.o/game_config_sound.o: /usr/include/i386/types.h
.o/game_config_sound.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config_sound.o: /usr/include/_types/_intmax_t.h
.o/game_config_sound.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_config_sound.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_config_sound.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_sound.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_config_sound.o: my_string.h /usr/include/wchar.h
.o/game_config_sound.o: /usr/include/sys/_types/_null.h
.o/game_config_sound.o: /usr/include/sys/_types/_size_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_rune_t.h
.o/game_config_sound.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_config_sound.o: /usr/include/sys/_types/_va_list.h
.o/game_config_sound.o: /usr/include/sys/stdio.h
.o/game_config_sound.o: /usr/include/sys/_types/_off_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_sound.o: /usr/include/secure/_stdio.h
.o/game_config_sound.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game_config_sound.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_time_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_timespec.h
.o/game_config_sound.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_sound.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_sound.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_sound.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_config_sound.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_config_sound.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_config_sound.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_config_sound.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h
.o/game_config_sound.o: my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/game_config_sound.o: my_light.h my_thing_template.h my_dice.h
.o/game_config_sound.o: my_thing_ai.h
.o/game_credits.o: my_game.h my_world.h my_point.h my_math.h
.o/game_credits.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_credits.o: /usr/include/sys/_symbol_aliasing.h
.o/game_credits.o: /usr/include/sys/_posix_availability.h
.o/game_credits.o: /usr/include/Availability.h
.o/game_credits.o: /usr/include/AvailabilityInternal.h
.o/game_credits.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_credits.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_credits.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_credits.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/game_credits.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_credits.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_credits.o: /usr/include/sys/_types/_int8_t.h
.o/game_credits.o: /usr/include/sys/_types/_int16_t.h
.o/game_credits.o: /usr/include/sys/_types/_int32_t.h
.o/game_credits.o: /usr/include/sys/_types/_int64_t.h
.o/game_credits.o: /usr/include/_types/_uint8_t.h
.o/game_credits.o: /usr/include/_types/_uint16_t.h
.o/game_credits.o: /usr/include/_types/_uint32_t.h
.o/game_credits.o: /usr/include/_types/_uint64_t.h
.o/game_credits.o: /usr/include/sys/_types/_intptr_t.h
.o/game_credits.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_credits.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_credits.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_credits.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_credits.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_credits.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_credits.o: /usr/include/_types/_intmax_t.h
.o/game_credits.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_credits.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_credits.o: my_bounds_check.h /usr/include/assert.h
.o/game_credits.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_credits.o: my_string.h /usr/include/wchar.h
.o/game_credits.o: /usr/include/sys/_types/_null.h
.o/game_credits.o: /usr/include/sys/_types/_size_t.h
.o/game_credits.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_credits.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_credits.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_credits.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_credits.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_credits.o: /usr/include/sys/_types/_ssize_t.h
.o/game_credits.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_credits.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_credits.o: /usr/include/sys/_types/_time_t.h
.o/game_credits.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_credits.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_credits.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_credits.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_credits.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_credits.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_credits.o: my_level_static.h my_dungeon_grid.h my_wid_minicon.h
.o/game_credits.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/game_credits.o: my_wid_tiles.h my_thing.h my_light.h my_thing_template.h
.o/game_credits.o: my_dice.h my_thing_ai.h my_wid_botcon.h my_wid_popup.h
.o/game_credits.o: my_wid_text_box.h my_gl.h
.o/game_dead.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_dead.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_dead.o: /usr/include/sys/_posix_availability.h
.o/game_dead.o: /usr/include/Availability.h
.o/game_dead.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_dead.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_dead.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_dead.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_dead.o: /usr/include/i386/_types.h
.o/game_dead.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_dead.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_dead.o: /usr/include/sys/_types/_int8_t.h
.o/game_dead.o: /usr/include/sys/_types/_int16_t.h
.o/game_dead.o: /usr/include/sys/_types/_int32_t.h
.o/game_dead.o: /usr/include/sys/_types/_int64_t.h
.o/game_dead.o: /usr/include/_types/_uint8_t.h
.o/game_dead.o: /usr/include/_types/_uint16_t.h
.o/game_dead.o: /usr/include/_types/_uint32_t.h
.o/game_dead.o: /usr/include/_types/_uint64_t.h
.o/game_dead.o: /usr/include/sys/_types/_intptr_t.h
.o/game_dead.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_dead.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_dead.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_dead.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_dead.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_dead.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_dead.o: /usr/include/_types/_intmax_t.h
.o/game_dead.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_dead.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_dead.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_dead.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_dead.o: /usr/include/sys/_types/_null.h
.o/game_dead.o: /usr/include/sys/_types/_size_t.h
.o/game_dead.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_dead.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_dead.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_dead.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_dead.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_dead.o: /usr/include/sys/_types/_ssize_t.h
.o/game_dead.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_dead.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_dead.o: /usr/include/sys/_types/_time_t.h
.o/game_dead.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_dead.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_dead.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_dead.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_dead.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_dead.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_dead.o: my_dungeon_grid.h my_wid_minicon.h my_wid.h my_ascii.h
.o/game_dead.o: my_tex.h my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/game_dead.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/game_dead.o: my_wid_botcon.h my_wid_popup.h my_wid_text_box.h
.o/game_display.o: my_game.h my_world.h my_point.h my_math.h
.o/game_display.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_display.o: /usr/include/sys/_symbol_aliasing.h
.o/game_display.o: /usr/include/sys/_posix_availability.h
.o/game_display.o: /usr/include/Availability.h
.o/game_display.o: /usr/include/AvailabilityInternal.h
.o/game_display.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_display.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_display.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_display.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/game_display.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_display.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_display.o: /usr/include/sys/_types/_int8_t.h
.o/game_display.o: /usr/include/sys/_types/_int16_t.h
.o/game_display.o: /usr/include/sys/_types/_int32_t.h
.o/game_display.o: /usr/include/sys/_types/_int64_t.h
.o/game_display.o: /usr/include/_types/_uint8_t.h
.o/game_display.o: /usr/include/_types/_uint16_t.h
.o/game_display.o: /usr/include/_types/_uint32_t.h
.o/game_display.o: /usr/include/_types/_uint64_t.h
.o/game_display.o: /usr/include/sys/_types/_intptr_t.h
.o/game_display.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_display.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_display.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_display.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_display.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_display.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_display.o: /usr/include/_types/_intmax_t.h
.o/game_display.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_display.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_display.o: my_bounds_check.h /usr/include/assert.h
.o/game_display.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_display.o: my_string.h /usr/include/wchar.h
.o/game_display.o: /usr/include/sys/_types/_null.h
.o/game_display.o: /usr/include/sys/_types/_size_t.h
.o/game_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_display.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_display.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_display.o: /usr/include/sys/_types/_ssize_t.h
.o/game_display.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_display.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_display.o: /usr/include/sys/_types/_time_t.h
.o/game_display.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_display.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_display.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_display.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_display.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_display.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/game_display.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/game_display.o: my_thing_ai.h
.o/game_dump.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_dump.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_dump.o: /usr/include/sys/_posix_availability.h
.o/game_dump.o: /usr/include/Availability.h
.o/game_dump.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_dump.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_dump.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_dump.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_dump.o: /usr/include/i386/_types.h
.o/game_dump.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_dump.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_dump.o: /usr/include/sys/_types/_int8_t.h
.o/game_dump.o: /usr/include/sys/_types/_int16_t.h
.o/game_dump.o: /usr/include/sys/_types/_int32_t.h
.o/game_dump.o: /usr/include/sys/_types/_int64_t.h
.o/game_dump.o: /usr/include/_types/_uint8_t.h
.o/game_dump.o: /usr/include/_types/_uint16_t.h
.o/game_dump.o: /usr/include/_types/_uint32_t.h
.o/game_dump.o: /usr/include/_types/_uint64_t.h
.o/game_dump.o: /usr/include/sys/_types/_intptr_t.h
.o/game_dump.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_dump.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_dump.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_dump.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_dump.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_dump.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_dump.o: /usr/include/_types/_intmax_t.h
.o/game_dump.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_dump.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_dump.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_dump.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_dump.o: /usr/include/sys/_types/_null.h
.o/game_dump.o: /usr/include/sys/_types/_size_t.h
.o/game_dump.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_dump.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_dump.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_dump.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_dump.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_dump.o: /usr/include/sys/_types/_ssize_t.h
.o/game_dump.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_dump.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_dump.o: /usr/include/sys/_types/_time_t.h
.o/game_dump.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_dump.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_dump.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_dump.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_dump.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_dump.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_dump.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/game_dump.o: my_dice.h my_tile.h my_color.h my_thing_ai.h
.o/game_error.o: my_game.h my_world.h my_point.h my_math.h
.o/game_error.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_error.o: /usr/include/sys/_symbol_aliasing.h
.o/game_error.o: /usr/include/sys/_posix_availability.h
.o/game_error.o: /usr/include/Availability.h
.o/game_error.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_error.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_error.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_error.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_error.o: /usr/include/i386/_types.h
.o/game_error.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_error.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_error.o: /usr/include/sys/_types/_int8_t.h
.o/game_error.o: /usr/include/sys/_types/_int16_t.h
.o/game_error.o: /usr/include/sys/_types/_int32_t.h
.o/game_error.o: /usr/include/sys/_types/_int64_t.h
.o/game_error.o: /usr/include/_types/_uint8_t.h
.o/game_error.o: /usr/include/_types/_uint16_t.h
.o/game_error.o: /usr/include/_types/_uint32_t.h
.o/game_error.o: /usr/include/_types/_uint64_t.h
.o/game_error.o: /usr/include/sys/_types/_intptr_t.h
.o/game_error.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_error.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_error.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_error.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_error.o: /usr/include/_types/_intmax_t.h
.o/game_error.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_error.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_error.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_error.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_error.o: /usr/include/sys/_types/_null.h
.o/game_error.o: /usr/include/sys/_types/_size_t.h
.o/game_error.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_error.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_error.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_error.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_error.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_error.o: /usr/include/sys/_types/_ssize_t.h
.o/game_error.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_error.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_error.o: /usr/include/sys/_types/_time_t.h
.o/game_error.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_error.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_error.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_error.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_error.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_error.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_error.o: my_dungeon_grid.h my_wid_popup.h my_wid_text_box.h my_wid.h
.o/game_error.o: my_ascii.h my_tex.h my_tile.h my_color.h my_wid_tiles.h
.o/game_error.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/game_error.o: my_thing_ai.h my_traceback.h
.o/game_fini.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_fini.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_fini.o: /usr/include/sys/_posix_availability.h
.o/game_fini.o: /usr/include/Availability.h
.o/game_fini.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_fini.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_fini.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_fini.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_fini.o: /usr/include/i386/_types.h
.o/game_fini.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_fini.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_fini.o: /usr/include/sys/_types/_int8_t.h
.o/game_fini.o: /usr/include/sys/_types/_int16_t.h
.o/game_fini.o: /usr/include/sys/_types/_int32_t.h
.o/game_fini.o: /usr/include/sys/_types/_int64_t.h
.o/game_fini.o: /usr/include/_types/_uint8_t.h
.o/game_fini.o: /usr/include/_types/_uint16_t.h
.o/game_fini.o: /usr/include/_types/_uint32_t.h
.o/game_fini.o: /usr/include/_types/_uint64_t.h
.o/game_fini.o: /usr/include/sys/_types/_intptr_t.h
.o/game_fini.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_fini.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_fini.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_fini.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_fini.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_fini.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_fini.o: /usr/include/_types/_intmax_t.h
.o/game_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_fini.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_fini.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_fini.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_fini.o: /usr/include/sys/_types/_null.h
.o/game_fini.o: /usr/include/sys/_types/_size_t.h
.o/game_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_fini.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_fini.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/game_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_fini.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_fini.o: /usr/include/sys/_types/_time_t.h
.o/game_fini.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_fini.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_fini.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_fini.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_fini.o: my_dungeon_grid.h
.o/game_init.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_init.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_init.o: /usr/include/sys/_posix_availability.h
.o/game_init.o: /usr/include/Availability.h
.o/game_init.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_init.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_init.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_init.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_init.o: /usr/include/i386/_types.h
.o/game_init.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_init.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_init.o: /usr/include/sys/_types/_int8_t.h
.o/game_init.o: /usr/include/sys/_types/_int16_t.h
.o/game_init.o: /usr/include/sys/_types/_int32_t.h
.o/game_init.o: /usr/include/sys/_types/_int64_t.h
.o/game_init.o: /usr/include/_types/_uint8_t.h
.o/game_init.o: /usr/include/_types/_uint16_t.h
.o/game_init.o: /usr/include/_types/_uint32_t.h
.o/game_init.o: /usr/include/_types/_uint64_t.h
.o/game_init.o: /usr/include/sys/_types/_intptr_t.h
.o/game_init.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_init.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_init.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_init.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_init.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_init.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_init.o: /usr/include/_types/_intmax_t.h
.o/game_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_init.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_init.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_init.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_init.o: /usr/include/sys/_types/_null.h
.o/game_init.o: /usr/include/sys/_types/_size_t.h
.o/game_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_init.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_init.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_init.o: /usr/include/sys/_types/_ssize_t.h
.o/game_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_init.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_init.o: /usr/include/sys/_types/_time_t.h
.o/game_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_init.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_init.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_init.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_init.o: my_dungeon_grid.h my_random_name.h
.o/game_load.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_load.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_load.o: /usr/include/sys/_posix_availability.h
.o/game_load.o: /usr/include/Availability.h
.o/game_load.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_load.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_load.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_load.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_load.o: /usr/include/i386/_types.h
.o/game_load.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_load.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_load.o: /usr/include/sys/_types/_int8_t.h
.o/game_load.o: /usr/include/sys/_types/_int16_t.h
.o/game_load.o: /usr/include/sys/_types/_int32_t.h
.o/game_load.o: /usr/include/sys/_types/_int64_t.h
.o/game_load.o: /usr/include/_types/_uint8_t.h
.o/game_load.o: /usr/include/_types/_uint16_t.h
.o/game_load.o: /usr/include/_types/_uint32_t.h
.o/game_load.o: /usr/include/_types/_uint64_t.h
.o/game_load.o: /usr/include/sys/_types/_intptr_t.h
.o/game_load.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_load.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_load.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_load.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_load.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_load.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_load.o: /usr/include/_types/_intmax_t.h
.o/game_load.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_load.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_load.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_load.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_load.o: /usr/include/sys/_types/_null.h
.o/game_load.o: /usr/include/sys/_types/_size_t.h
.o/game_load.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_load.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_load.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_load.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_load.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_load.o: /usr/include/sys/_types/_ssize_t.h
.o/game_load.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_load.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_load.o: /usr/include/sys/_types/_time_t.h
.o/game_load.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_load.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_load.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_load.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_load.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_load.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_load.o: my_dungeon_grid.h minilzo.h /usr/include/limits.h
.o/game_load.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/game_load.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
.o/game_load.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/game_load.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/game_load.o: /usr/include/sys/_types/_rsize_t.h lzodefs.h lzoconf.h
.o/game_load.o: my_wid_minicon.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/game_load.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/game_load.o: my_thing_template.h my_dice.h my_thing_ai.h my_wid_botcon.h
.o/game_load.o: my_wid_console.h my_wid_popup.h my_wid_text_box.h
.o/game_load.o: my_game_error.h my_wid_rightbar.h my_alloc.h my_sprintf.h
.o/game_log.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_log.o: /usr/include/sys/_posix_availability.h
.o/game_log.o: /usr/include/Availability.h
.o/game_log.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_log.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_log.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_log.o: /usr/include/i386/_types.h
.o/game_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_log.o: /usr/include/sys/_types/_int8_t.h
.o/game_log.o: /usr/include/sys/_types/_int16_t.h
.o/game_log.o: /usr/include/sys/_types/_int32_t.h
.o/game_log.o: /usr/include/sys/_types/_int64_t.h
.o/game_log.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/game_log.o: /usr/include/_types/_uint32_t.h
.o/game_log.o: /usr/include/_types/_uint64_t.h
.o/game_log.o: /usr/include/sys/_types/_intptr_t.h
.o/game_log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_log.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_log.o: /usr/include/_types/_intmax_t.h
.o/game_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_log.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_log.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_log.o: /usr/include/sys/_types/_null.h
.o/game_log.o: /usr/include/sys/_types/_size_t.h
.o/game_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_log.o: /usr/include/sys/_types/_ssize_t.h
.o/game_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_log.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_log.o: /usr/include/sys/_types/_time_t.h
.o/game_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_log.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_log.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_log.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/game_log.o: my_dice.h my_tile.h my_color.h my_thing_ai.h
.o/game_main_menu.o: my_game.h my_world.h my_point.h my_math.h
.o/game_main_menu.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_main_menu.o: /usr/include/sys/_symbol_aliasing.h
.o/game_main_menu.o: /usr/include/sys/_posix_availability.h
.o/game_main_menu.o: /usr/include/Availability.h
.o/game_main_menu.o: /usr/include/AvailabilityInternal.h
.o/game_main_menu.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_main_menu.o: my_main.h my_sys.h my_pcg_basic.h
.o/game_main_menu.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game_main_menu.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_main_menu.o: /usr/include/i386/_types.h
.o/game_main_menu.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_main_menu.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_main_menu.o: /usr/include/sys/_types/_int8_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_int16_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_int32_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_int64_t.h
.o/game_main_menu.o: /usr/include/_types/_uint8_t.h
.o/game_main_menu.o: /usr/include/_types/_uint16_t.h
.o/game_main_menu.o: /usr/include/_types/_uint32_t.h
.o/game_main_menu.o: /usr/include/_types/_uint64_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_intptr_t.h
.o/game_main_menu.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_main_menu.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_main_menu.o: /usr/include/_types/_intmax_t.h
.o/game_main_menu.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_main_menu.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_main_menu.o: my_bounds_check.h /usr/include/assert.h
.o/game_main_menu.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_main_menu.o: my_string.h /usr/include/wchar.h
.o/game_main_menu.o: /usr/include/sys/_types/_null.h
.o/game_main_menu.o: /usr/include/sys/_types/_size_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_main_menu.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_main_menu.o: /usr/include/sys/stdio.h
.o/game_main_menu.o: /usr/include/sys/_types/_off_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_ssize_t.h
.o/game_main_menu.o: /usr/include/secure/_stdio.h
.o/game_main_menu.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game_main_menu.o: /usr/include/sys/_types/_clock_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_time_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_timespec.h
.o/game_main_menu.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_main_menu.o: /usr/include/sys/_types/_wint_t.h
.o/game_main_menu.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_main_menu.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_main_menu.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_main_menu.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_main_menu.o: my_level_static.h my_dungeon_grid.h my_wid_minicon.h
.o/game_main_menu.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/game_main_menu.o: my_wid_tiles.h my_thing.h my_light.h my_thing_template.h
.o/game_main_menu.o: my_dice.h my_thing_ai.h my_wid_botcon.h my_wid_popup.h
.o/game_main_menu.o: my_wid_text_box.h my_wid_rightbar.h my_wid_leftbar.h
.o/game_main_menu.o: my_wid_thing_info.h my_wid_inventory.h
.o/game_main_menu.o: my_wid_thing_collect.h my_gl.h
.o/game_menu_flames.o: my_game.h my_world.h my_point.h my_math.h
.o/game_menu_flames.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_menu_flames.o: /usr/include/sys/_symbol_aliasing.h
.o/game_menu_flames.o: /usr/include/sys/_posix_availability.h
.o/game_menu_flames.o: /usr/include/Availability.h
.o/game_menu_flames.o: /usr/include/AvailabilityInternal.h
.o/game_menu_flames.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_menu_flames.o: my_main.h my_sys.h my_pcg_basic.h
.o/game_menu_flames.o: /usr/include/inttypes.h /usr/include/_types.h
.o/game_menu_flames.o: /usr/include/sys/_types.h
.o/game_menu_flames.o: /usr/include/machine/_types.h
.o/game_menu_flames.o: /usr/include/i386/_types.h
.o/game_menu_flames.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_menu_flames.o: /usr/include/sys/_types/_wchar_t.h
.o/game_menu_flames.o: /usr/include/stdint.h
.o/game_menu_flames.o: /usr/include/sys/_types/_int8_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_int16_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_int32_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_int64_t.h
.o/game_menu_flames.o: /usr/include/_types/_uint8_t.h
.o/game_menu_flames.o: /usr/include/_types/_uint16_t.h
.o/game_menu_flames.o: /usr/include/_types/_uint32_t.h
.o/game_menu_flames.o: /usr/include/_types/_uint64_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_intptr_t.h
.o/game_menu_flames.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_menu_flames.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_menu_flames.o: /usr/include/_types/_intmax_t.h
.o/game_menu_flames.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_menu_flames.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/game_menu_flames.o: my_bounds_check.h /usr/include/assert.h
.o/game_menu_flames.o: my_vector_bounds_check.h my_command.h my_token.h
.o/game_menu_flames.o: my_string.h /usr/include/wchar.h
.o/game_menu_flames.o: /usr/include/sys/_types/_null.h
.o/game_menu_flames.o: /usr/include/sys/_types/_size_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_menu_flames.o: /usr/include/_stdio.h
.o/game_menu_flames.o: /usr/include/sys/_types/_va_list.h
.o/game_menu_flames.o: /usr/include/sys/stdio.h
.o/game_menu_flames.o: /usr/include/sys/_types/_off_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_ssize_t.h
.o/game_menu_flames.o: /usr/include/secure/_stdio.h
.o/game_menu_flames.o: /usr/include/secure/_common.h /usr/include/time.h
.o/game_menu_flames.o: /usr/include/sys/_types/_clock_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_time_t.h
.o/game_menu_flames.o: /usr/include/sys/_types/_timespec.h
.o/game_menu_flames.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_menu_flames.o: /usr/include/sys/_types/_wint_t.h
.o/game_menu_flames.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_menu_flames.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_menu_flames.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_menu_flames.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_menu_flames.o: my_level_static.h my_dungeon_grid.h my_wid_minicon.h
.o/game_menu_flames.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/game_menu_flames.o: my_wid_tiles.h my_thing.h my_light.h
.o/game_menu_flames.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/game_menu_flames.o: my_wid_botcon.h my_wid_popup.h my_wid_text_box.h
.o/game_menu_flames.o: my_wid_rightbar.h my_gl.h
.o/game_mouse.o: my_game.h my_world.h my_point.h my_math.h
.o/game_mouse.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_mouse.o: /usr/include/sys/_symbol_aliasing.h
.o/game_mouse.o: /usr/include/sys/_posix_availability.h
.o/game_mouse.o: /usr/include/Availability.h
.o/game_mouse.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_mouse.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_mouse.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_mouse.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_mouse.o: /usr/include/i386/_types.h
.o/game_mouse.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_mouse.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_mouse.o: /usr/include/sys/_types/_int8_t.h
.o/game_mouse.o: /usr/include/sys/_types/_int16_t.h
.o/game_mouse.o: /usr/include/sys/_types/_int32_t.h
.o/game_mouse.o: /usr/include/sys/_types/_int64_t.h
.o/game_mouse.o: /usr/include/_types/_uint8_t.h
.o/game_mouse.o: /usr/include/_types/_uint16_t.h
.o/game_mouse.o: /usr/include/_types/_uint32_t.h
.o/game_mouse.o: /usr/include/_types/_uint64_t.h
.o/game_mouse.o: /usr/include/sys/_types/_intptr_t.h
.o/game_mouse.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_mouse.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_mouse.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_mouse.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_mouse.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_mouse.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_mouse.o: /usr/include/_types/_intmax_t.h
.o/game_mouse.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_mouse.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_mouse.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_mouse.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_mouse.o: /usr/include/sys/_types/_null.h
.o/game_mouse.o: /usr/include/sys/_types/_size_t.h
.o/game_mouse.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_mouse.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_mouse.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_mouse.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_mouse.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_mouse.o: /usr/include/sys/_types/_ssize_t.h
.o/game_mouse.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_mouse.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_mouse.o: /usr/include/sys/_types/_time_t.h
.o/game_mouse.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_mouse.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_mouse.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_mouse.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_mouse.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_mouse.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_mouse.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/game_mouse.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_wid.h
.o/game_mouse.o: my_ascii.h my_tex.h my_wid_tiles.h
.o/game_notice.o: my_game.h my_world.h my_point.h my_math.h
.o/game_notice.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_notice.o: /usr/include/sys/_symbol_aliasing.h
.o/game_notice.o: /usr/include/sys/_posix_availability.h
.o/game_notice.o: /usr/include/Availability.h
.o/game_notice.o: /usr/include/AvailabilityInternal.h
.o/game_notice.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_notice.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_notice.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_notice.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/game_notice.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_notice.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_notice.o: /usr/include/sys/_types/_int8_t.h
.o/game_notice.o: /usr/include/sys/_types/_int16_t.h
.o/game_notice.o: /usr/include/sys/_types/_int32_t.h
.o/game_notice.o: /usr/include/sys/_types/_int64_t.h
.o/game_notice.o: /usr/include/_types/_uint8_t.h
.o/game_notice.o: /usr/include/_types/_uint16_t.h
.o/game_notice.o: /usr/include/_types/_uint32_t.h
.o/game_notice.o: /usr/include/_types/_uint64_t.h
.o/game_notice.o: /usr/include/sys/_types/_intptr_t.h
.o/game_notice.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_notice.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_notice.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_notice.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_notice.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_notice.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_notice.o: /usr/include/_types/_intmax_t.h
.o/game_notice.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_notice.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_notice.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_notice.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_notice.o: /usr/include/sys/_types/_null.h
.o/game_notice.o: /usr/include/sys/_types/_size_t.h
.o/game_notice.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_notice.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_notice.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_notice.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_notice.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_notice.o: /usr/include/sys/_types/_ssize_t.h
.o/game_notice.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_notice.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_notice.o: /usr/include/sys/_types/_time_t.h
.o/game_notice.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_notice.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_notice.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_notice.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_notice.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_notice.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_notice.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_notice.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/game_notice.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/game_notice.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/game_paused.o: my_game.h my_world.h my_point.h my_math.h
.o/game_paused.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/game_paused.o: /usr/include/sys/_symbol_aliasing.h
.o/game_paused.o: /usr/include/sys/_posix_availability.h
.o/game_paused.o: /usr/include/Availability.h
.o/game_paused.o: /usr/include/AvailabilityInternal.h
.o/game_paused.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/game_paused.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_paused.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_paused.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/game_paused.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_paused.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_paused.o: /usr/include/sys/_types/_int8_t.h
.o/game_paused.o: /usr/include/sys/_types/_int16_t.h
.o/game_paused.o: /usr/include/sys/_types/_int32_t.h
.o/game_paused.o: /usr/include/sys/_types/_int64_t.h
.o/game_paused.o: /usr/include/_types/_uint8_t.h
.o/game_paused.o: /usr/include/_types/_uint16_t.h
.o/game_paused.o: /usr/include/_types/_uint32_t.h
.o/game_paused.o: /usr/include/_types/_uint64_t.h
.o/game_paused.o: /usr/include/sys/_types/_intptr_t.h
.o/game_paused.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_paused.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_paused.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_paused.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_paused.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_paused.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_paused.o: /usr/include/_types/_intmax_t.h
.o/game_paused.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_paused.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_paused.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_paused.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_paused.o: /usr/include/sys/_types/_null.h
.o/game_paused.o: /usr/include/sys/_types/_size_t.h
.o/game_paused.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_paused.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_paused.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_paused.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_paused.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_paused.o: /usr/include/sys/_types/_ssize_t.h
.o/game_paused.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_paused.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_paused.o: /usr/include/sys/_types/_time_t.h
.o/game_paused.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_paused.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_paused.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_paused.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_paused.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/game_paused.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/game_paused.o: my_level_static.h my_dungeon_grid.h my_wid_popup.h
.o/game_paused.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/game_paused.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/game_paused.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/game_paused.o: my_wid_thing_info.h
.o/game_quit.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_quit.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_quit.o: /usr/include/sys/_posix_availability.h
.o/game_quit.o: /usr/include/Availability.h
.o/game_quit.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_quit.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_quit.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_quit.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_quit.o: /usr/include/i386/_types.h
.o/game_quit.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_quit.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_quit.o: /usr/include/sys/_types/_int8_t.h
.o/game_quit.o: /usr/include/sys/_types/_int16_t.h
.o/game_quit.o: /usr/include/sys/_types/_int32_t.h
.o/game_quit.o: /usr/include/sys/_types/_int64_t.h
.o/game_quit.o: /usr/include/_types/_uint8_t.h
.o/game_quit.o: /usr/include/_types/_uint16_t.h
.o/game_quit.o: /usr/include/_types/_uint32_t.h
.o/game_quit.o: /usr/include/_types/_uint64_t.h
.o/game_quit.o: /usr/include/sys/_types/_intptr_t.h
.o/game_quit.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_quit.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_quit.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_quit.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_quit.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_quit.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_quit.o: /usr/include/_types/_intmax_t.h
.o/game_quit.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_quit.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_quit.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_quit.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_quit.o: /usr/include/sys/_types/_null.h
.o/game_quit.o: /usr/include/sys/_types/_size_t.h
.o/game_quit.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_quit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_quit.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_quit.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_quit.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_quit.o: /usr/include/sys/_types/_ssize_t.h
.o/game_quit.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_quit.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_quit.o: /usr/include/sys/_types/_time_t.h
.o/game_quit.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_quit.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_quit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_quit.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_quit.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_quit.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_quit.o: my_dungeon_grid.h my_wid_minicon.h my_wid.h my_ascii.h
.o/game_quit.o: my_tex.h my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/game_quit.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/game_quit.o: my_wid_botcon.h my_wid_popup.h my_wid_text_box.h
.o/game_save.o: minilzo.h /usr/include/limits.h /usr/include/sys/cdefs.h
.o/game_save.o: /usr/include/sys/_symbol_aliasing.h
.o/game_save.o: /usr/include/sys/_posix_availability.h
.o/game_save.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/game_save.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
.o/game_save.o: /usr/include/stddef.h /usr/include/_types.h
.o/game_save.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_save.o: /usr/include/i386/_types.h
.o/game_save.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_save.o: /usr/include/sys/_types/_null.h
.o/game_save.o: /usr/include/sys/_types/_offsetof.h
.o/game_save.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/game_save.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_save.o: /usr/include/sys/_types/_int8_t.h
.o/game_save.o: /usr/include/sys/_types/_int16_t.h
.o/game_save.o: /usr/include/sys/_types/_int32_t.h
.o/game_save.o: /usr/include/sys/_types/_int64_t.h
.o/game_save.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_save.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_save.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_save.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_save.o: /usr/include/sys/_types/_intptr_t.h
.o/game_save.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_save.o: /usr/include/sys/_types/_rsize_t.h
.o/game_save.o: /usr/include/sys/_types/_size_t.h
.o/game_save.o: /usr/include/sys/_types/_wchar_t.h
.o/game_save.o: /usr/include/sys/_types/_wint_t.h lzodefs.h lzoconf.h
.o/game_save.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_save.o: /usr/include/Availability.h
.o/game_save.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_save.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_save.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/stdint.h
.o/game_save.o: /usr/include/_types/_uint8_t.h
.o/game_save.o: /usr/include/_types/_uint16_t.h
.o/game_save.o: /usr/include/_types/_uint32_t.h
.o/game_save.o: /usr/include/_types/_uint64_t.h
.o/game_save.o: /usr/include/_types/_intmax_t.h
.o/game_save.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_save.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_save.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_save.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_save.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_save.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_save.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_save.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_save.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_save.o: /usr/include/sys/_types/_ssize_t.h
.o/game_save.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_save.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_save.o: /usr/include/sys/_types/_time_t.h
.o/game_save.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_save.o: /usr/include/__wctype.h /usr/include/_types/_wctype_t.h
.o/game_save.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/game_save.o: /usr/include/runetype.h slre.h my_particle.h my_size.h
.o/game_save.o: my_thing_id.h my_dungeon.h my_room.h my_depth.h my_charmap.h
.o/game_save.o: my_dmap.h my_level_static.h my_dungeon_grid.h
.o/game_save.o: my_wid_minicon.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/game_save.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/game_save.o: my_thing_template.h my_dice.h my_thing_ai.h my_wid_console.h
.o/game_save.o: my_wid_popup.h my_wid_text_box.h my_alloc.h
.o/game_tick.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/game_tick.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_tick.o: /usr/include/sys/_posix_availability.h
.o/game_tick.o: /usr/include/Availability.h
.o/game_tick.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/game_tick.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/game_tick.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/game_tick.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_tick.o: /usr/include/i386/_types.h
.o/game_tick.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_tick.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_tick.o: /usr/include/sys/_types/_int8_t.h
.o/game_tick.o: /usr/include/sys/_types/_int16_t.h
.o/game_tick.o: /usr/include/sys/_types/_int32_t.h
.o/game_tick.o: /usr/include/sys/_types/_int64_t.h
.o/game_tick.o: /usr/include/_types/_uint8_t.h
.o/game_tick.o: /usr/include/_types/_uint16_t.h
.o/game_tick.o: /usr/include/_types/_uint32_t.h
.o/game_tick.o: /usr/include/_types/_uint64_t.h
.o/game_tick.o: /usr/include/sys/_types/_intptr_t.h
.o/game_tick.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_tick.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_tick.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_tick.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_tick.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_tick.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_tick.o: /usr/include/_types/_intmax_t.h
.o/game_tick.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/game_tick.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/game_tick.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/game_tick.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_tick.o: /usr/include/sys/_types/_null.h
.o/game_tick.o: /usr/include/sys/_types/_size_t.h
.o/game_tick.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_tick.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_tick.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/game_tick.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_tick.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game_tick.o: /usr/include/sys/_types/_ssize_t.h
.o/game_tick.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_tick.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/game_tick.o: /usr/include/sys/_types/_time_t.h
.o/game_tick.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_tick.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_tick.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_tick.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/game_tick.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/game_tick.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/game_tick.o: my_dungeon_grid.h
.o/gauss.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/gauss.o: /usr/include/sys/_symbol_aliasing.h
.o/gauss.o: /usr/include/sys/_posix_availability.h
.o/gauss.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/gauss.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/gauss.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/gauss.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/gauss.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gauss.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gauss.o: /usr/include/sys/_types/_int8_t.h
.o/gauss.o: /usr/include/sys/_types/_int16_t.h
.o/gauss.o: /usr/include/sys/_types/_int32_t.h
.o/gauss.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gauss.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gauss.o: /usr/include/_types/_uint64_t.h
.o/gauss.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gauss.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gauss.o: /usr/include/sys/_types/_u_int16_t.h
.o/gauss.o: /usr/include/sys/_types/_u_int32_t.h
.o/gauss.o: /usr/include/sys/_types/_u_int64_t.h
.o/gauss.o: /usr/include/sys/_types/_uintptr_t.h
.o/gauss.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gauss.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gauss.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gauss.o: c_plus_plus_serializer.h
.o/gfx.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx.o: /usr/include/i386/_types.h
.o/gfx.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx.o: /usr/include/sys/_types/_int8_t.h
.o/gfx.o: /usr/include/sys/_types/_int16_t.h
.o/gfx.o: /usr/include/sys/_types/_int32_t.h
.o/gfx.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/gfx.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/gfx.o: /usr/include/sys/_types/_u_int8_t.h
.o/gfx.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx.o: /usr/include/sys/_types/_size_t.h
.o/gfx.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx.o: /usr/include/sys/_types/_clock_t.h
.o/gfx.o: /usr/include/sys/_types/_time_t.h
.o/gfx.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx.o: my_math.h /usr/include/math.h my_color.h my_gfx.h
.o/gfx0.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx0.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx0.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx0.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx0.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx0.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx0.o: /usr/include/i386/_types.h
.o/gfx0.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx0.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx0.o: /usr/include/sys/_types/_int8_t.h
.o/gfx0.o: /usr/include/sys/_types/_int16_t.h
.o/gfx0.o: /usr/include/sys/_types/_int32_t.h
.o/gfx0.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx0.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx0.o: /usr/include/_types/_uint64_t.h
.o/gfx0.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx0.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx0.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx0.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx0.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx0.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx0.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx0.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx0.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx0.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx0.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx0.o: /usr/include/sys/_types/_size_t.h
.o/gfx0.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx0.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx0.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx0.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx0.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx0.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx0.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx0.o: /usr/include/sys/_types/_clock_t.h
.o/gfx0.o: /usr/include/sys/_types/_time_t.h
.o/gfx0.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx0.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx0.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx0.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx0.o: my_math.h /usr/include/math.h my_color.h
.o/gfx1.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx1.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx1.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx1.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx1.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx1.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx1.o: /usr/include/i386/_types.h
.o/gfx1.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx1.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx1.o: /usr/include/sys/_types/_int8_t.h
.o/gfx1.o: /usr/include/sys/_types/_int16_t.h
.o/gfx1.o: /usr/include/sys/_types/_int32_t.h
.o/gfx1.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx1.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx1.o: /usr/include/_types/_uint64_t.h
.o/gfx1.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx1.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx1.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx1.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx1.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx1.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx1.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx1.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx1.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx1.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx1.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx1.o: /usr/include/sys/_types/_size_t.h
.o/gfx1.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx1.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx1.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx1.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx1.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx1.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx1.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx1.o: /usr/include/sys/_types/_clock_t.h
.o/gfx1.o: /usr/include/sys/_types/_time_t.h
.o/gfx1.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx1.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx1.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx1.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx1.o: my_math.h /usr/include/math.h my_color.h
.o/gfx10.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx10.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx10.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx10.o: /usr/include/sys/_posix_availability.h
.o/gfx10.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/gfx10.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/gfx10.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/gfx10.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx10.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx10.o: /usr/include/sys/_types/_int8_t.h
.o/gfx10.o: /usr/include/sys/_types/_int16_t.h
.o/gfx10.o: /usr/include/sys/_types/_int32_t.h
.o/gfx10.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx10.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx10.o: /usr/include/_types/_uint64_t.h
.o/gfx10.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx10.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx10.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx10.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx10.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx10.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx10.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx10.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx10.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx10.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx10.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx10.o: /usr/include/sys/_types/_size_t.h
.o/gfx10.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx10.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx10.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx10.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx10.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx10.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx10.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx10.o: /usr/include/sys/_types/_clock_t.h
.o/gfx10.o: /usr/include/sys/_types/_time_t.h
.o/gfx10.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx10.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx10.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx10.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx10.o: my_math.h /usr/include/math.h my_color.h
.o/gfx11.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx11.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx11.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx11.o: /usr/include/sys/_posix_availability.h
.o/gfx11.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/gfx11.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/gfx11.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/gfx11.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx11.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx11.o: /usr/include/sys/_types/_int8_t.h
.o/gfx11.o: /usr/include/sys/_types/_int16_t.h
.o/gfx11.o: /usr/include/sys/_types/_int32_t.h
.o/gfx11.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx11.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx11.o: /usr/include/_types/_uint64_t.h
.o/gfx11.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx11.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx11.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx11.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx11.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx11.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx11.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx11.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx11.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx11.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx11.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx11.o: /usr/include/sys/_types/_size_t.h
.o/gfx11.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx11.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx11.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx11.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx11.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx11.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx11.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx11.o: /usr/include/sys/_types/_clock_t.h
.o/gfx11.o: /usr/include/sys/_types/_time_t.h
.o/gfx11.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx11.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx11.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx11.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx11.o: my_math.h /usr/include/math.h my_color.h
.o/gfx12.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx12.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx12.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx12.o: /usr/include/sys/_posix_availability.h
.o/gfx12.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/gfx12.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/gfx12.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/gfx12.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx12.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx12.o: /usr/include/sys/_types/_int8_t.h
.o/gfx12.o: /usr/include/sys/_types/_int16_t.h
.o/gfx12.o: /usr/include/sys/_types/_int32_t.h
.o/gfx12.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx12.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx12.o: /usr/include/_types/_uint64_t.h
.o/gfx12.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx12.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx12.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx12.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx12.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx12.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx12.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx12.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx12.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx12.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx12.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx12.o: /usr/include/sys/_types/_size_t.h
.o/gfx12.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx12.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx12.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx12.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx12.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx12.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx12.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx12.o: /usr/include/sys/_types/_clock_t.h
.o/gfx12.o: /usr/include/sys/_types/_time_t.h
.o/gfx12.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx12.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx12.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx12.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx12.o: my_math.h /usr/include/math.h my_color.h
.o/gfx2.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx2.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx2.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx2.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx2.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx2.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx2.o: /usr/include/i386/_types.h
.o/gfx2.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx2.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx2.o: /usr/include/sys/_types/_int8_t.h
.o/gfx2.o: /usr/include/sys/_types/_int16_t.h
.o/gfx2.o: /usr/include/sys/_types/_int32_t.h
.o/gfx2.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx2.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx2.o: /usr/include/_types/_uint64_t.h
.o/gfx2.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx2.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx2.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx2.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx2.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx2.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx2.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx2.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx2.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx2.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx2.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx2.o: /usr/include/sys/_types/_size_t.h
.o/gfx2.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx2.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx2.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx2.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx2.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx2.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx2.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx2.o: /usr/include/sys/_types/_clock_t.h
.o/gfx2.o: /usr/include/sys/_types/_time_t.h
.o/gfx2.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx2.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx2.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx2.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx2.o: my_math.h /usr/include/math.h my_color.h
.o/gfx3.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx3.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx3.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx3.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx3.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx3.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx3.o: /usr/include/i386/_types.h
.o/gfx3.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx3.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx3.o: /usr/include/sys/_types/_int8_t.h
.o/gfx3.o: /usr/include/sys/_types/_int16_t.h
.o/gfx3.o: /usr/include/sys/_types/_int32_t.h
.o/gfx3.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx3.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx3.o: /usr/include/_types/_uint64_t.h
.o/gfx3.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx3.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx3.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx3.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx3.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx3.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx3.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx3.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx3.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx3.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx3.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx3.o: /usr/include/sys/_types/_size_t.h
.o/gfx3.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx3.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx3.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx3.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx3.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx3.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx3.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx3.o: /usr/include/sys/_types/_clock_t.h
.o/gfx3.o: /usr/include/sys/_types/_time_t.h
.o/gfx3.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx3.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx3.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx3.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx3.o: my_math.h /usr/include/math.h my_color.h
.o/gfx4.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx4.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx4.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx4.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx4.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx4.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx4.o: /usr/include/i386/_types.h
.o/gfx4.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx4.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx4.o: /usr/include/sys/_types/_int8_t.h
.o/gfx4.o: /usr/include/sys/_types/_int16_t.h
.o/gfx4.o: /usr/include/sys/_types/_int32_t.h
.o/gfx4.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx4.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx4.o: /usr/include/_types/_uint64_t.h
.o/gfx4.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx4.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx4.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx4.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx4.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx4.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx4.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx4.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx4.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx4.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx4.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx4.o: /usr/include/sys/_types/_size_t.h
.o/gfx4.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx4.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx4.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx4.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx4.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx4.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx4.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx4.o: /usr/include/sys/_types/_clock_t.h
.o/gfx4.o: /usr/include/sys/_types/_time_t.h
.o/gfx4.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx4.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx4.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx4.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx4.o: my_math.h /usr/include/math.h my_color.h
.o/gfx5.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx5.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx5.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx5.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx5.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx5.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx5.o: /usr/include/i386/_types.h
.o/gfx5.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx5.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx5.o: /usr/include/sys/_types/_int8_t.h
.o/gfx5.o: /usr/include/sys/_types/_int16_t.h
.o/gfx5.o: /usr/include/sys/_types/_int32_t.h
.o/gfx5.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx5.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx5.o: /usr/include/_types/_uint64_t.h
.o/gfx5.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx5.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx5.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx5.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx5.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx5.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx5.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx5.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx5.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx5.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx5.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx5.o: /usr/include/sys/_types/_size_t.h
.o/gfx5.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx5.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx5.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx5.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx5.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx5.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx5.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx5.o: /usr/include/sys/_types/_clock_t.h
.o/gfx5.o: /usr/include/sys/_types/_time_t.h
.o/gfx5.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx5.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx5.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx5.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx5.o: my_math.h /usr/include/math.h my_color.h
.o/gfx6.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx6.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx6.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx6.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx6.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx6.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx6.o: /usr/include/i386/_types.h
.o/gfx6.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx6.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx6.o: /usr/include/sys/_types/_int8_t.h
.o/gfx6.o: /usr/include/sys/_types/_int16_t.h
.o/gfx6.o: /usr/include/sys/_types/_int32_t.h
.o/gfx6.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx6.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx6.o: /usr/include/_types/_uint64_t.h
.o/gfx6.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx6.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx6.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx6.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx6.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx6.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx6.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx6.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx6.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx6.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx6.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx6.o: /usr/include/sys/_types/_size_t.h
.o/gfx6.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx6.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx6.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx6.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx6.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx6.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx6.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx6.o: /usr/include/sys/_types/_clock_t.h
.o/gfx6.o: /usr/include/sys/_types/_time_t.h
.o/gfx6.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx6.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx6.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx6.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx6.o: my_math.h /usr/include/math.h my_color.h
.o/gfx7.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx7.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx7.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx7.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx7.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx7.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx7.o: /usr/include/i386/_types.h
.o/gfx7.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx7.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx7.o: /usr/include/sys/_types/_int8_t.h
.o/gfx7.o: /usr/include/sys/_types/_int16_t.h
.o/gfx7.o: /usr/include/sys/_types/_int32_t.h
.o/gfx7.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx7.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx7.o: /usr/include/_types/_uint64_t.h
.o/gfx7.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx7.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx7.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx7.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx7.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx7.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx7.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx7.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx7.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx7.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx7.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx7.o: /usr/include/sys/_types/_size_t.h
.o/gfx7.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx7.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx7.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx7.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx7.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx7.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx7.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx7.o: /usr/include/sys/_types/_clock_t.h
.o/gfx7.o: /usr/include/sys/_types/_time_t.h
.o/gfx7.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx7.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx7.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx7.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx7.o: my_math.h /usr/include/math.h my_color.h
.o/gfx8.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx8.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx8.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx8.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx8.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx8.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx8.o: /usr/include/i386/_types.h
.o/gfx8.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx8.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx8.o: /usr/include/sys/_types/_int8_t.h
.o/gfx8.o: /usr/include/sys/_types/_int16_t.h
.o/gfx8.o: /usr/include/sys/_types/_int32_t.h
.o/gfx8.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx8.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx8.o: /usr/include/_types/_uint64_t.h
.o/gfx8.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx8.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx8.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx8.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx8.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx8.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx8.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx8.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx8.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx8.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx8.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx8.o: /usr/include/sys/_types/_size_t.h
.o/gfx8.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx8.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx8.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx8.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx8.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx8.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx8.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx8.o: /usr/include/sys/_types/_clock_t.h
.o/gfx8.o: /usr/include/sys/_types/_time_t.h
.o/gfx8.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx8.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx8.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx8.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx8.o: my_math.h /usr/include/math.h my_color.h
.o/gfx9.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gfx9.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/gfx9.o: /usr/include/sys/_symbol_aliasing.h
.o/gfx9.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gfx9.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gfx9.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gfx9.o: /usr/include/i386/_types.h
.o/gfx9.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gfx9.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gfx9.o: /usr/include/sys/_types/_int8_t.h
.o/gfx9.o: /usr/include/sys/_types/_int16_t.h
.o/gfx9.o: /usr/include/sys/_types/_int32_t.h
.o/gfx9.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gfx9.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gfx9.o: /usr/include/_types/_uint64_t.h
.o/gfx9.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/gfx9.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gfx9.o: /usr/include/sys/_types/_u_int16_t.h
.o/gfx9.o: /usr/include/sys/_types/_u_int32_t.h
.o/gfx9.o: /usr/include/sys/_types/_u_int64_t.h
.o/gfx9.o: /usr/include/sys/_types/_uintptr_t.h
.o/gfx9.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/gfx9.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/gfx9.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx9.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/gfx9.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/gfx9.o: /usr/include/sys/_types/_size_t.h
.o/gfx9.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx9.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx9.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gfx9.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx9.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx9.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx9.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gfx9.o: /usr/include/sys/_types/_clock_t.h
.o/gfx9.o: /usr/include/sys/_types/_time_t.h
.o/gfx9.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx9.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx9.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx9.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_point.h
.o/gfx9.o: my_math.h /usr/include/math.h my_color.h
.o/gl.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/gl.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/gl.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gl.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/gl.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/gl.o: /usr/include/inttypes.h /usr/include/_types.h
.o/gl.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/gl.o: /usr/include/i386/_types.h
.o/gl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/gl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/gl.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
.o/gl.o: /usr/include/sys/_types/_int32_t.h
.o/gl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gl.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/gl.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/gl.o: /usr/include/sys/_types/_u_int8_t.h
.o/gl.o: /usr/include/sys/_types/_u_int16_t.h
.o/gl.o: /usr/include/sys/_types/_u_int32_t.h
.o/gl.o: /usr/include/sys/_types/_u_int64_t.h
.o/gl.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
.o/gl.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/gl.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/gl.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/gl.o: my_token.h my_string.h /usr/include/wchar.h
.o/gl.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/gl.o: /usr/include/sys/_types/_mbstate_t.h
.o/gl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gl.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/gl.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gl.o: /usr/include/secure/_common.h /usr/include/time.h
.o/gl.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
.o/gl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gl.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gl.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gl.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_particle.h
.o/gl.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/gl.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h my_gl.h
.o/gl.o: my_color.h my_thing_template.h my_dice.h my_tile.h
.o/globals.o: my_globals.h
.o/hacklib.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/hacklib.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/hacklib.o: /usr/include/sys/_posix_availability.h
.o/hacklib.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/hacklib.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/hacklib.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/hacklib.o: /usr/include/sys/_pthread/_pthread_types.h
.o/hacklib.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/hacklib.o: /usr/include/sys/_types/_int8_t.h
.o/hacklib.o: /usr/include/sys/_types/_int16_t.h
.o/hacklib.o: /usr/include/sys/_types/_int32_t.h
.o/hacklib.o: /usr/include/sys/_types/_int64_t.h
.o/hacklib.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/hacklib.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/hacklib.o: /usr/include/sys/_types/_intptr_t.h
.o/hacklib.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/hacklib.o: /usr/include/sys/_types/_u_int8_t.h
.o/hacklib.o: /usr/include/sys/_types/_u_int16_t.h
.o/hacklib.o: /usr/include/sys/_types/_u_int32_t.h
.o/hacklib.o: /usr/include/sys/_types/_u_int64_t.h
.o/hacklib.o: /usr/include/sys/_types/_uintptr_t.h
.o/hacklib.o: /usr/include/_types/_intmax_t.h
.o/hacklib.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/hacklib.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/hacklib.o: /usr/include/assert.h my_vector_bounds_check.h
.o/hacklib.o: c_plus_plus_serializer.h
.o/hexdump.o: /usr/include/strings.h /usr/include/_types.h
.o/hexdump.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/hexdump.o: /usr/include/sys/_symbol_aliasing.h
.o/hexdump.o: /usr/include/sys/_posix_availability.h
.o/hexdump.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/hexdump.o: /usr/include/sys/_pthread/_pthread_types.h
.o/hexdump.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/hexdump.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/hexdump.o: /usr/include/sys/_types/_null.h
.o/hexdump.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/hexdump.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/hexdump.o: /usr/include/sys/_types/_int16_t.h
.o/hexdump.o: /usr/include/sys/_types/_int32_t.h
.o/hexdump.o: /usr/include/sys/_types/_int64_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int8_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int16_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int32_t.h
.o/hexdump.o: /usr/include/sys/_types/_u_int64_t.h
.o/hexdump.o: /usr/include/sys/_types/_intptr_t.h
.o/hexdump.o: /usr/include/sys/_types/_uintptr_t.h
.o/hexdump.o: /usr/include/sys/_types/_errno_t.h
.o/hexdump.o: /usr/include/sys/_types/_ssize_t.h
.o/hexdump.o: /usr/include/secure/_string.h /usr/include/secure/_common.h
.o/hexdump.o: /usr/include/secure/_strings.h
.o/level.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/level.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level.o: /usr/include/sys/_symbol_aliasing.h
.o/level.o: /usr/include/sys/_posix_availability.h
.o/level.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/level.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/level.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level.o: /usr/include/sys/_types/_int8_t.h
.o/level.o: /usr/include/sys/_types/_int16_t.h
.o/level.o: /usr/include/sys/_types/_int32_t.h
.o/level.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/level.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/level.o: /usr/include/_types/_uint64_t.h
.o/level.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/level.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/level.o: /usr/include/sys/_types/_u_int16_t.h
.o/level.o: /usr/include/sys/_types/_u_int32_t.h
.o/level.o: /usr/include/sys/_types/_u_int64_t.h
.o/level.o: /usr/include/sys/_types/_uintptr_t.h
.o/level.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/level.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/level.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/level.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/level.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level.o: /usr/include/sys/_types/_size_t.h
.o/level.o: /usr/include/sys/_types/_mbstate_t.h
.o/level.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/level.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level.o: /usr/include/sys/_types/_clock_t.h
.o/level.o: /usr/include/sys/_types/_time_t.h
.o/level.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level.o: my_particle.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/level.o: my_thing_id.h my_dungeon.h my_room.h my_depth.h my_charmap.h
.o/level.o: my_dmap.h my_level_static.h my_dungeon_grid.h
.o/level_create.o: my_game.h my_world.h my_point.h my_math.h
.o/level_create.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/level_create.o: /usr/include/sys/_symbol_aliasing.h
.o/level_create.o: /usr/include/sys/_posix_availability.h
.o/level_create.o: /usr/include/Availability.h
.o/level_create.o: /usr/include/AvailabilityInternal.h
.o/level_create.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/level_create.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_create.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_create.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/level_create.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_create.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_create.o: /usr/include/sys/_types/_int8_t.h
.o/level_create.o: /usr/include/sys/_types/_int16_t.h
.o/level_create.o: /usr/include/sys/_types/_int32_t.h
.o/level_create.o: /usr/include/sys/_types/_int64_t.h
.o/level_create.o: /usr/include/_types/_uint8_t.h
.o/level_create.o: /usr/include/_types/_uint16_t.h
.o/level_create.o: /usr/include/_types/_uint32_t.h
.o/level_create.o: /usr/include/_types/_uint64_t.h
.o/level_create.o: /usr/include/sys/_types/_intptr_t.h
.o/level_create.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_create.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_create.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_create.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_create.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_create.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_create.o: /usr/include/_types/_intmax_t.h
.o/level_create.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_create.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_create.o: my_bounds_check.h /usr/include/assert.h
.o/level_create.o: my_vector_bounds_check.h my_command.h my_token.h
.o/level_create.o: my_string.h /usr/include/wchar.h
.o/level_create.o: /usr/include/sys/_types/_null.h
.o/level_create.o: /usr/include/sys/_types/_size_t.h
.o/level_create.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_create.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_create.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_create.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_create.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_create.o: /usr/include/sys/_types/_ssize_t.h
.o/level_create.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_create.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_create.o: /usr/include/sys/_types/_time_t.h
.o/level_create.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_create.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_create.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_create.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_create.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_create.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_create.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/level_create.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/level_create.o: my_thing_ai.h
.o/level_cursor.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_cursor.o: /usr/include/sys/cdefs.h
.o/level_cursor.o: /usr/include/sys/_symbol_aliasing.h
.o/level_cursor.o: /usr/include/sys/_posix_availability.h
.o/level_cursor.o: /usr/include/Availability.h
.o/level_cursor.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_cursor.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_cursor.o: /usr/include/i386/_types.h
.o/level_cursor.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_cursor.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_cursor.o: /usr/include/sys/_types/_int8_t.h
.o/level_cursor.o: /usr/include/sys/_types/_int16_t.h
.o/level_cursor.o: /usr/include/sys/_types/_int32_t.h
.o/level_cursor.o: /usr/include/sys/_types/_int64_t.h
.o/level_cursor.o: /usr/include/_types/_uint8_t.h
.o/level_cursor.o: /usr/include/_types/_uint16_t.h
.o/level_cursor.o: /usr/include/_types/_uint32_t.h
.o/level_cursor.o: /usr/include/_types/_uint64_t.h
.o/level_cursor.o: /usr/include/sys/_types/_intptr_t.h
.o/level_cursor.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_cursor.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_cursor.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_cursor.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_cursor.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_cursor.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_cursor.o: /usr/include/_types/_intmax_t.h
.o/level_cursor.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_cursor.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_cursor.o: my_bounds_check.h /usr/include/assert.h
.o/level_cursor.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_cursor.o: my_game.h my_world.h my_point.h my_math.h
.o/level_cursor.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_cursor.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_cursor.o: /usr/include/sys/_types/_null.h
.o/level_cursor.o: /usr/include/sys/_types/_size_t.h
.o/level_cursor.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_cursor.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_cursor.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_cursor.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_cursor.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_cursor.o: /usr/include/sys/_types/_ssize_t.h
.o/level_cursor.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_cursor.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_cursor.o: /usr/include/sys/_types/_time_t.h
.o/level_cursor.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_cursor.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_cursor.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_cursor.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_cursor.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_cursor.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_cursor.o: my_level_static.h my_dungeon_grid.h my_tile.h my_color.h
.o/level_cursor.o: my_tex.h my_gl.h my_thing.h my_light.h my_thing_template.h
.o/level_cursor.o: my_dice.h my_thing_ai.h my_wid_thing_info.h my_wid.h
.o/level_cursor.o: my_ascii.h my_wid_tiles.h my_wid_popup.h my_wid_text_box.h
.o/level_cursor.o: my_wid_inventory.h my_wid_bag.h
.o/level_cursor_path.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_cursor_path.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_cursor_path.o: /usr/include/sys/_symbol_aliasing.h
.o/level_cursor_path.o: /usr/include/sys/_posix_availability.h
.o/level_cursor_path.o: /usr/include/Availability.h
.o/level_cursor_path.o: /usr/include/AvailabilityInternal.h
.o/level_cursor_path.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_cursor_path.o: /usr/include/machine/_types.h
.o/level_cursor_path.o: /usr/include/i386/_types.h
.o/level_cursor_path.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_cursor_path.o: /usr/include/sys/_types/_wchar_t.h
.o/level_cursor_path.o: /usr/include/stdint.h
.o/level_cursor_path.o: /usr/include/sys/_types/_int8_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_int16_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_int32_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_int64_t.h
.o/level_cursor_path.o: /usr/include/_types/_uint8_t.h
.o/level_cursor_path.o: /usr/include/_types/_uint16_t.h
.o/level_cursor_path.o: /usr/include/_types/_uint32_t.h
.o/level_cursor_path.o: /usr/include/_types/_uint64_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_intptr_t.h
.o/level_cursor_path.o: /usr/include/machine/types.h
.o/level_cursor_path.o: /usr/include/i386/types.h
.o/level_cursor_path.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_cursor_path.o: /usr/include/_types/_intmax_t.h
.o/level_cursor_path.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_cursor_path.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_cursor_path.o: my_bounds_check.h /usr/include/assert.h
.o/level_cursor_path.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_cursor_path.o: my_game.h my_world.h my_point.h my_math.h
.o/level_cursor_path.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_cursor_path.o: my_command.h my_token.h my_string.h
.o/level_cursor_path.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level_cursor_path.o: /usr/include/sys/_types/_size_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_rune_t.h
.o/level_cursor_path.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_cursor_path.o: /usr/include/sys/_types/_va_list.h
.o/level_cursor_path.o: /usr/include/sys/stdio.h
.o/level_cursor_path.o: /usr/include/sys/_types/_off_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_ssize_t.h
.o/level_cursor_path.o: /usr/include/secure/_stdio.h
.o/level_cursor_path.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_cursor_path.o: /usr/include/sys/_types/_clock_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_time_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_timespec.h
.o/level_cursor_path.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_cursor_path.o: /usr/include/sys/_types/_wint_t.h
.o/level_cursor_path.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_cursor_path.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_cursor_path.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_cursor_path.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_cursor_path.o: my_level_static.h my_dungeon_grid.h my_tile.h
.o/level_cursor_path.o: my_color.h my_tex.h my_gl.h my_thing.h my_light.h
.o/level_cursor_path.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/level_display.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_display.o: /usr/include/sys/cdefs.h
.o/level_display.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display.o: /usr/include/sys/_posix_availability.h
.o/level_display.o: /usr/include/Availability.h
.o/level_display.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_display.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_display.o: /usr/include/i386/_types.h
.o/level_display.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_display.o: /usr/include/sys/_types/_int8_t.h
.o/level_display.o: /usr/include/sys/_types/_int16_t.h
.o/level_display.o: /usr/include/sys/_types/_int32_t.h
.o/level_display.o: /usr/include/sys/_types/_int64_t.h
.o/level_display.o: /usr/include/_types/_uint8_t.h
.o/level_display.o: /usr/include/_types/_uint16_t.h
.o/level_display.o: /usr/include/_types/_uint32_t.h
.o/level_display.o: /usr/include/_types/_uint64_t.h
.o/level_display.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_display.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display.o: /usr/include/_types/_intmax_t.h
.o/level_display.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display.o: my_bounds_check.h /usr/include/assert.h
.o/level_display.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_display.o: /usr/include/sys/_types/_null.h
.o/level_display.o: /usr/include/sys/_types/_size_t.h
.o/level_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_display.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_display.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_display.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display.o: /usr/include/secure/_stdio.h
.o/level_display.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display.o: /usr/include/sys/_types/_clock_t.h
.o/level_display.o: /usr/include/sys/_types/_time_t.h
.o/level_display.o: /usr/include/sys/_types/_timespec.h
.o/level_display.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display.o: /usr/include/sys/_types/_wint_t.h
.o/level_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_display.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_display.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_display.o: my_level_static.h my_dungeon_grid.h my_tile.h my_color.h
.o/level_display.o: my_tex.h my_gl.h my_thing.h my_light.h
.o/level_display.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/level_display_anim.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_anim.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_anim.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_anim.o: /usr/include/sys/_posix_availability.h
.o/level_display_anim.o: /usr/include/Availability.h
.o/level_display_anim.o: /usr/include/AvailabilityInternal.h
.o/level_display_anim.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_anim.o: /usr/include/machine/_types.h
.o/level_display_anim.o: /usr/include/i386/_types.h
.o/level_display_anim.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_anim.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_anim.o: /usr/include/stdint.h
.o/level_display_anim.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_anim.o: /usr/include/_types/_uint8_t.h
.o/level_display_anim.o: /usr/include/_types/_uint16_t.h
.o/level_display_anim.o: /usr/include/_types/_uint32_t.h
.o/level_display_anim.o: /usr/include/_types/_uint64_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_anim.o: /usr/include/machine/types.h
.o/level_display_anim.o: /usr/include/i386/types.h
.o/level_display_anim.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_anim.o: /usr/include/_types/_intmax_t.h
.o/level_display_anim.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_anim.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_anim.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_anim.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_anim.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_anim.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_anim.o: my_command.h my_token.h my_string.h
.o/level_display_anim.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level_display_anim.o: /usr/include/sys/_types/_size_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_anim.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_anim.o: /usr/include/sys/_types/_va_list.h
.o/level_display_anim.o: /usr/include/sys/stdio.h
.o/level_display_anim.o: /usr/include/sys/_types/_off_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_anim.o: /usr/include/secure/_stdio.h
.o/level_display_anim.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_anim.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_time_t.h
.o/level_display_anim.o: /usr/include/sys/_types/_timespec.h
.o/level_display_anim.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_anim.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_anim.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display_anim.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_display_anim.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_display_anim.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_display_anim.o: my_level_static.h my_dungeon_grid.h my_tile.h
.o/level_display_anim.o: my_color.h my_tex.h my_gl.h my_thing.h my_light.h
.o/level_display_anim.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/level_display_blood.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_blood.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_blood.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_blood.o: /usr/include/sys/_posix_availability.h
.o/level_display_blood.o: /usr/include/Availability.h
.o/level_display_blood.o: /usr/include/AvailabilityInternal.h
.o/level_display_blood.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_blood.o: /usr/include/machine/_types.h
.o/level_display_blood.o: /usr/include/i386/_types.h
.o/level_display_blood.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_blood.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_blood.o: /usr/include/stdint.h
.o/level_display_blood.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_blood.o: /usr/include/_types/_uint8_t.h
.o/level_display_blood.o: /usr/include/_types/_uint16_t.h
.o/level_display_blood.o: /usr/include/_types/_uint32_t.h
.o/level_display_blood.o: /usr/include/_types/_uint64_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_blood.o: /usr/include/machine/types.h
.o/level_display_blood.o: /usr/include/i386/types.h
.o/level_display_blood.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_blood.o: /usr/include/_types/_intmax_t.h
.o/level_display_blood.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_blood.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_blood.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_blood.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_blood.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_blood.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_blood.o: my_command.h my_token.h my_string.h
.o/level_display_blood.o: /usr/include/wchar.h
.o/level_display_blood.o: /usr/include/sys/_types/_null.h
.o/level_display_blood.o: /usr/include/sys/_types/_size_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_blood.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_blood.o: /usr/include/sys/_types/_va_list.h
.o/level_display_blood.o: /usr/include/sys/stdio.h
.o/level_display_blood.o: /usr/include/sys/_types/_off_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_blood.o: /usr/include/secure/_stdio.h
.o/level_display_blood.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_blood.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_time_t.h
.o/level_display_blood.o: /usr/include/sys/_types/_timespec.h
.o/level_display_blood.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_blood.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_blood.o: /usr/include/_types/_wctype_t.h
.o/level_display_blood.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_blood.o: /usr/include/runetype.h slre.h my_particle.h
.o/level_display_blood.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_display_blood.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_display_blood.o: my_dungeon_grid.h my_tile.h my_color.h my_tex.h
.o/level_display_blood.o: my_gl.h my_thing.h my_light.h my_thing_template.h
.o/level_display_blood.o: my_dice.h my_thing_ai.h
.o/level_display_chasm.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_chasm.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_chasm.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_chasm.o: /usr/include/sys/_posix_availability.h
.o/level_display_chasm.o: /usr/include/Availability.h
.o/level_display_chasm.o: /usr/include/AvailabilityInternal.h
.o/level_display_chasm.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_chasm.o: /usr/include/machine/_types.h
.o/level_display_chasm.o: /usr/include/i386/_types.h
.o/level_display_chasm.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_chasm.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_chasm.o: /usr/include/stdint.h
.o/level_display_chasm.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_chasm.o: /usr/include/_types/_uint8_t.h
.o/level_display_chasm.o: /usr/include/_types/_uint16_t.h
.o/level_display_chasm.o: /usr/include/_types/_uint32_t.h
.o/level_display_chasm.o: /usr/include/_types/_uint64_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_chasm.o: /usr/include/machine/types.h
.o/level_display_chasm.o: /usr/include/i386/types.h
.o/level_display_chasm.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_chasm.o: /usr/include/_types/_intmax_t.h
.o/level_display_chasm.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_chasm.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_chasm.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_chasm.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_chasm.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_chasm.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_chasm.o: my_command.h my_token.h my_string.h
.o/level_display_chasm.o: /usr/include/wchar.h
.o/level_display_chasm.o: /usr/include/sys/_types/_null.h
.o/level_display_chasm.o: /usr/include/sys/_types/_size_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_chasm.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_chasm.o: /usr/include/sys/_types/_va_list.h
.o/level_display_chasm.o: /usr/include/sys/stdio.h
.o/level_display_chasm.o: /usr/include/sys/_types/_off_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_chasm.o: /usr/include/secure/_stdio.h
.o/level_display_chasm.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_chasm.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_time_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_timespec.h
.o/level_display_chasm.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_chasm.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_chasm.o: /usr/include/_types/_wctype_t.h
.o/level_display_chasm.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_chasm.o: /usr/include/runetype.h slre.h my_particle.h
.o/level_display_chasm.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_display_chasm.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_display_chasm.o: my_dungeon_grid.h my_thing.h my_light.h
.o/level_display_chasm.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/level_display_chasm.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_display_deep_water.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_deep_water.o: /usr/include/inttypes.h
.o/level_display_deep_water.o: /usr/include/sys/cdefs.h
.o/level_display_deep_water.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_deep_water.o: /usr/include/sys/_posix_availability.h
.o/level_display_deep_water.o: /usr/include/Availability.h
.o/level_display_deep_water.o: /usr/include/AvailabilityInternal.h
.o/level_display_deep_water.o: /usr/include/_types.h
.o/level_display_deep_water.o: /usr/include/sys/_types.h
.o/level_display_deep_water.o: /usr/include/machine/_types.h
.o/level_display_deep_water.o: /usr/include/i386/_types.h
.o/level_display_deep_water.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_deep_water.o: /usr/include/stdint.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_deep_water.o: /usr/include/_types/_uint8_t.h
.o/level_display_deep_water.o: /usr/include/_types/_uint16_t.h
.o/level_display_deep_water.o: /usr/include/_types/_uint32_t.h
.o/level_display_deep_water.o: /usr/include/_types/_uint64_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_deep_water.o: /usr/include/machine/types.h
.o/level_display_deep_water.o: /usr/include/i386/types.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_deep_water.o: /usr/include/_types/_intmax_t.h
.o/level_display_deep_water.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_deep_water.o: my_globals.h my_callstack.h
.o/level_display_deep_water.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_deep_water.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_deep_water.o: c_plus_plus_serializer.h my_game.h my_world.h
.o/level_display_deep_water.o: my_point.h my_math.h /usr/include/math.h
.o/level_display_deep_water.o: my_level.h my_time.h my_sdl.h my_command.h
.o/level_display_deep_water.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_null.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_size_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_deep_water.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_va_list.h
.o/level_display_deep_water.o: /usr/include/sys/stdio.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_off_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_deep_water.o: /usr/include/secure/_stdio.h
.o/level_display_deep_water.o: /usr/include/secure/_common.h
.o/level_display_deep_water.o: /usr/include/time.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_time_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_timespec.h
.o/level_display_deep_water.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_deep_water.o: /usr/include/_types/_wctype_t.h
.o/level_display_deep_water.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_deep_water.o: /usr/include/runetype.h slre.h my_particle.h
.o/level_display_deep_water.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_display_deep_water.o: my_depth.h my_charmap.h my_dmap.h
.o/level_display_deep_water.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/level_display_deep_water.o: my_light.h my_thing_template.h my_dice.h
.o/level_display_deep_water.o: my_tile.h my_color.h my_thing_ai.h my_font.h
.o/level_display_deep_water.o: my_tex.h my_gl.h
.o/level_display_fade.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_fade.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_fade.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_fade.o: /usr/include/sys/_posix_availability.h
.o/level_display_fade.o: /usr/include/Availability.h
.o/level_display_fade.o: /usr/include/AvailabilityInternal.h
.o/level_display_fade.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_fade.o: /usr/include/machine/_types.h
.o/level_display_fade.o: /usr/include/i386/_types.h
.o/level_display_fade.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_fade.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_fade.o: /usr/include/stdint.h
.o/level_display_fade.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_fade.o: /usr/include/_types/_uint8_t.h
.o/level_display_fade.o: /usr/include/_types/_uint16_t.h
.o/level_display_fade.o: /usr/include/_types/_uint32_t.h
.o/level_display_fade.o: /usr/include/_types/_uint64_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_fade.o: /usr/include/machine/types.h
.o/level_display_fade.o: /usr/include/i386/types.h
.o/level_display_fade.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_fade.o: /usr/include/_types/_intmax_t.h
.o/level_display_fade.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_fade.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_fade.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_fade.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_fade.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_fade.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_fade.o: my_command.h my_token.h my_string.h
.o/level_display_fade.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level_display_fade.o: /usr/include/sys/_types/_size_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_fade.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_fade.o: /usr/include/sys/_types/_va_list.h
.o/level_display_fade.o: /usr/include/sys/stdio.h
.o/level_display_fade.o: /usr/include/sys/_types/_off_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_fade.o: /usr/include/secure/_stdio.h
.o/level_display_fade.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_fade.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_time_t.h
.o/level_display_fade.o: /usr/include/sys/_types/_timespec.h
.o/level_display_fade.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_fade.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_fade.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display_fade.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_display_fade.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_display_fade.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_display_fade.o: my_level_static.h my_dungeon_grid.h my_tile.h
.o/level_display_fade.o: my_color.h my_tex.h my_gl.h my_thing.h my_light.h
.o/level_display_fade.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/level_display_lava.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_lava.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_lava.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_lava.o: /usr/include/sys/_posix_availability.h
.o/level_display_lava.o: /usr/include/Availability.h
.o/level_display_lava.o: /usr/include/AvailabilityInternal.h
.o/level_display_lava.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_lava.o: /usr/include/machine/_types.h
.o/level_display_lava.o: /usr/include/i386/_types.h
.o/level_display_lava.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_lava.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_lava.o: /usr/include/stdint.h
.o/level_display_lava.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_lava.o: /usr/include/_types/_uint8_t.h
.o/level_display_lava.o: /usr/include/_types/_uint16_t.h
.o/level_display_lava.o: /usr/include/_types/_uint32_t.h
.o/level_display_lava.o: /usr/include/_types/_uint64_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_lava.o: /usr/include/machine/types.h
.o/level_display_lava.o: /usr/include/i386/types.h
.o/level_display_lava.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_lava.o: /usr/include/_types/_intmax_t.h
.o/level_display_lava.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_lava.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_lava.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_lava.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_lava.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_lava.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_lava.o: my_command.h my_token.h my_string.h
.o/level_display_lava.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level_display_lava.o: /usr/include/sys/_types/_size_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_lava.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_lava.o: /usr/include/sys/_types/_va_list.h
.o/level_display_lava.o: /usr/include/sys/stdio.h
.o/level_display_lava.o: /usr/include/sys/_types/_off_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_lava.o: /usr/include/secure/_stdio.h
.o/level_display_lava.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_lava.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_time_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_timespec.h
.o/level_display_lava.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_lava.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_lava.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display_lava.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_display_lava.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_display_lava.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_display_lava.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/level_display_lava.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/level_display_lava.o: my_color.h my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_display_minimap.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_minimap.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_minimap.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_minimap.o: /usr/include/sys/_posix_availability.h
.o/level_display_minimap.o: /usr/include/Availability.h
.o/level_display_minimap.o: /usr/include/AvailabilityInternal.h
.o/level_display_minimap.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_minimap.o: /usr/include/machine/_types.h
.o/level_display_minimap.o: /usr/include/i386/_types.h
.o/level_display_minimap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_minimap.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_minimap.o: /usr/include/stdint.h
.o/level_display_minimap.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_minimap.o: /usr/include/_types/_uint8_t.h
.o/level_display_minimap.o: /usr/include/_types/_uint16_t.h
.o/level_display_minimap.o: /usr/include/_types/_uint32_t.h
.o/level_display_minimap.o: /usr/include/_types/_uint64_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_minimap.o: /usr/include/machine/types.h
.o/level_display_minimap.o: /usr/include/i386/types.h
.o/level_display_minimap.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_minimap.o: /usr/include/_types/_intmax_t.h
.o/level_display_minimap.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_minimap.o: my_globals.h my_callstack.h
.o/level_display_minimap.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_minimap.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_minimap.o: c_plus_plus_serializer.h my_game.h my_world.h
.o/level_display_minimap.o: my_point.h my_math.h /usr/include/math.h
.o/level_display_minimap.o: my_level.h my_time.h my_sdl.h my_command.h
.o/level_display_minimap.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_display_minimap.o: /usr/include/sys/_types/_null.h
.o/level_display_minimap.o: /usr/include/sys/_types/_size_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_minimap.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_minimap.o: /usr/include/sys/_types/_va_list.h
.o/level_display_minimap.o: /usr/include/sys/stdio.h
.o/level_display_minimap.o: /usr/include/sys/_types/_off_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_minimap.o: /usr/include/secure/_stdio.h
.o/level_display_minimap.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_minimap.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_time_t.h
.o/level_display_minimap.o: /usr/include/sys/_types/_timespec.h
.o/level_display_minimap.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_minimap.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_minimap.o: /usr/include/_types/_wctype_t.h
.o/level_display_minimap.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_minimap.o: /usr/include/runetype.h slre.h my_particle.h
.o/level_display_minimap.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_display_minimap.o: my_depth.h my_charmap.h my_dmap.h
.o/level_display_minimap.o: my_level_static.h my_dungeon_grid.h my_tile.h
.o/level_display_minimap.o: my_color.h my_tex.h my_gl.h my_thing.h my_light.h
.o/level_display_minimap.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/level_display_shake.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_shake.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/level_display_shake.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_shake.o: /usr/include/sys/_posix_availability.h
.o/level_display_shake.o: /usr/include/Availability.h
.o/level_display_shake.o: /usr/include/AvailabilityInternal.h
.o/level_display_shake.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/level_display_shake.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/level_display_shake.o: /usr/include/inttypes.h /usr/include/_types.h
.o/level_display_shake.o: /usr/include/sys/_types.h
.o/level_display_shake.o: /usr/include/machine/_types.h
.o/level_display_shake.o: /usr/include/i386/_types.h
.o/level_display_shake.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_shake.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_shake.o: /usr/include/stdint.h
.o/level_display_shake.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_shake.o: /usr/include/_types/_uint8_t.h
.o/level_display_shake.o: /usr/include/_types/_uint16_t.h
.o/level_display_shake.o: /usr/include/_types/_uint32_t.h
.o/level_display_shake.o: /usr/include/_types/_uint64_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_shake.o: /usr/include/machine/types.h
.o/level_display_shake.o: /usr/include/i386/types.h
.o/level_display_shake.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_shake.o: /usr/include/_types/_intmax_t.h
.o/level_display_shake.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_shake.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_shake.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_shake.o: my_vector_bounds_check.h my_command.h my_token.h
.o/level_display_shake.o: my_string.h /usr/include/wchar.h
.o/level_display_shake.o: /usr/include/sys/_types/_null.h
.o/level_display_shake.o: /usr/include/sys/_types/_size_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_shake.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_shake.o: /usr/include/sys/_types/_va_list.h
.o/level_display_shake.o: /usr/include/sys/stdio.h
.o/level_display_shake.o: /usr/include/sys/_types/_off_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_shake.o: /usr/include/secure/_stdio.h
.o/level_display_shake.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_shake.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_time_t.h
.o/level_display_shake.o: /usr/include/sys/_types/_timespec.h
.o/level_display_shake.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_shake.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_shake.o: /usr/include/_types/_wctype_t.h
.o/level_display_shake.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_shake.o: /usr/include/runetype.h slre.h my_particle.h
.o/level_display_shake.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_display_shake.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_display_shake.o: my_dungeon_grid.h my_gl.h my_color.h my_thing.h
.o/level_display_shake.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/level_display_shake.o: my_thing_ai.h
.o/level_display_wall.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_wall.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_wall.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_wall.o: /usr/include/sys/_posix_availability.h
.o/level_display_wall.o: /usr/include/Availability.h
.o/level_display_wall.o: /usr/include/AvailabilityInternal.h
.o/level_display_wall.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_wall.o: /usr/include/machine/_types.h
.o/level_display_wall.o: /usr/include/i386/_types.h
.o/level_display_wall.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_wall.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_wall.o: /usr/include/stdint.h
.o/level_display_wall.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_wall.o: /usr/include/_types/_uint8_t.h
.o/level_display_wall.o: /usr/include/_types/_uint16_t.h
.o/level_display_wall.o: /usr/include/_types/_uint32_t.h
.o/level_display_wall.o: /usr/include/_types/_uint64_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_wall.o: /usr/include/machine/types.h
.o/level_display_wall.o: /usr/include/i386/types.h
.o/level_display_wall.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_wall.o: /usr/include/_types/_intmax_t.h
.o/level_display_wall.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_wall.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_wall.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_wall.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_wall.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_wall.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_wall.o: my_command.h my_token.h my_string.h
.o/level_display_wall.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level_display_wall.o: /usr/include/sys/_types/_size_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_wall.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_wall.o: /usr/include/sys/_types/_va_list.h
.o/level_display_wall.o: /usr/include/sys/stdio.h
.o/level_display_wall.o: /usr/include/sys/_types/_off_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_wall.o: /usr/include/secure/_stdio.h
.o/level_display_wall.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_wall.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_time_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_timespec.h
.o/level_display_wall.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_wall.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_wall.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display_wall.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_display_wall.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_display_wall.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_display_wall.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/level_display_wall.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/level_display_wall.o: my_color.h my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_display_water.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_display_water.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/level_display_water.o: /usr/include/sys/_symbol_aliasing.h
.o/level_display_water.o: /usr/include/sys/_posix_availability.h
.o/level_display_water.o: /usr/include/Availability.h
.o/level_display_water.o: /usr/include/AvailabilityInternal.h
.o/level_display_water.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_display_water.o: /usr/include/machine/_types.h
.o/level_display_water.o: /usr/include/i386/_types.h
.o/level_display_water.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_display_water.o: /usr/include/sys/_types/_wchar_t.h
.o/level_display_water.o: /usr/include/stdint.h
.o/level_display_water.o: /usr/include/sys/_types/_int8_t.h
.o/level_display_water.o: /usr/include/sys/_types/_int16_t.h
.o/level_display_water.o: /usr/include/sys/_types/_int32_t.h
.o/level_display_water.o: /usr/include/sys/_types/_int64_t.h
.o/level_display_water.o: /usr/include/_types/_uint8_t.h
.o/level_display_water.o: /usr/include/_types/_uint16_t.h
.o/level_display_water.o: /usr/include/_types/_uint32_t.h
.o/level_display_water.o: /usr/include/_types/_uint64_t.h
.o/level_display_water.o: /usr/include/sys/_types/_intptr_t.h
.o/level_display_water.o: /usr/include/machine/types.h
.o/level_display_water.o: /usr/include/i386/types.h
.o/level_display_water.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_display_water.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_display_water.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_display_water.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_display_water.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_display_water.o: /usr/include/_types/_intmax_t.h
.o/level_display_water.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_display_water.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_display_water.o: my_bounds_check.h /usr/include/assert.h
.o/level_display_water.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display_water.o: my_game.h my_world.h my_point.h my_math.h
.o/level_display_water.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_display_water.o: my_command.h my_token.h my_string.h
.o/level_display_water.o: /usr/include/wchar.h
.o/level_display_water.o: /usr/include/sys/_types/_null.h
.o/level_display_water.o: /usr/include/sys/_types/_size_t.h
.o/level_display_water.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_water.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_water.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_water.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display_water.o: /usr/include/sys/_types/_va_list.h
.o/level_display_water.o: /usr/include/sys/stdio.h
.o/level_display_water.o: /usr/include/sys/_types/_off_t.h
.o/level_display_water.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_water.o: /usr/include/secure/_stdio.h
.o/level_display_water.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_display_water.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_water.o: /usr/include/sys/_types/_time_t.h
.o/level_display_water.o: /usr/include/sys/_types/_timespec.h
.o/level_display_water.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_water.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_water.o: /usr/include/_types/_wctype_t.h
.o/level_display_water.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_water.o: /usr/include/runetype.h slre.h my_particle.h
.o/level_display_water.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_display_water.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_display_water.o: my_dungeon_grid.h my_thing.h my_light.h
.o/level_display_water.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/level_display_water.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_fini.o: my_game.h my_world.h my_point.h my_math.h
.o/level_fini.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/level_fini.o: /usr/include/sys/_symbol_aliasing.h
.o/level_fini.o: /usr/include/sys/_posix_availability.h
.o/level_fini.o: /usr/include/Availability.h
.o/level_fini.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/level_fini.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/level_fini.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/level_fini.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_fini.o: /usr/include/i386/_types.h
.o/level_fini.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_fini.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_fini.o: /usr/include/sys/_types/_int8_t.h
.o/level_fini.o: /usr/include/sys/_types/_int16_t.h
.o/level_fini.o: /usr/include/sys/_types/_int32_t.h
.o/level_fini.o: /usr/include/sys/_types/_int64_t.h
.o/level_fini.o: /usr/include/_types/_uint8_t.h
.o/level_fini.o: /usr/include/_types/_uint16_t.h
.o/level_fini.o: /usr/include/_types/_uint32_t.h
.o/level_fini.o: /usr/include/_types/_uint64_t.h
.o/level_fini.o: /usr/include/sys/_types/_intptr_t.h
.o/level_fini.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_fini.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_fini.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_fini.o: /usr/include/_types/_intmax_t.h
.o/level_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/level_fini.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/level_fini.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/level_fini.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_fini.o: /usr/include/sys/_types/_null.h
.o/level_fini.o: /usr/include/sys/_types/_size_t.h
.o/level_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_fini.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_fini.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/level_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_fini.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_fini.o: /usr/include/sys/_types/_time_t.h
.o/level_fini.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_fini.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_fini.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_fini.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_fini.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/level_fini.o: my_dice.h my_tile.h my_color.h my_thing_ai.h
.o/level_gc.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_gc.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_gc.o: /usr/include/sys/_posix_availability.h
.o/level_gc.o: /usr/include/Availability.h
.o/level_gc.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_gc.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_gc.o: /usr/include/i386/_types.h
.o/level_gc.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_gc.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_gc.o: /usr/include/sys/_types/_int8_t.h
.o/level_gc.o: /usr/include/sys/_types/_int16_t.h
.o/level_gc.o: /usr/include/sys/_types/_int32_t.h
.o/level_gc.o: /usr/include/sys/_types/_int64_t.h
.o/level_gc.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/level_gc.o: /usr/include/_types/_uint32_t.h
.o/level_gc.o: /usr/include/_types/_uint64_t.h
.o/level_gc.o: /usr/include/sys/_types/_intptr_t.h
.o/level_gc.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_gc.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_gc.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_gc.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_gc.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_gc.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_gc.o: /usr/include/_types/_intmax_t.h
.o/level_gc.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/level_gc.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/level_gc.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_gc.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/level_gc.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_gc.o: /usr/include/sys/_types/_null.h
.o/level_gc.o: /usr/include/sys/_types/_size_t.h
.o/level_gc.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_gc.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_gc.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_gc.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_gc.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_gc.o: /usr/include/sys/_types/_ssize_t.h
.o/level_gc.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_gc.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_gc.o: /usr/include/sys/_types/_time_t.h
.o/level_gc.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_gc.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_gc.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_gc.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_gc.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/level_gc.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/level_gc.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/level_gc.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/level_gc.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/level_heatmap.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/level_heatmap.o: my_pcg_basic.h /usr/include/inttypes.h
.o/level_heatmap.o: /usr/include/sys/cdefs.h
.o/level_heatmap.o: /usr/include/sys/_symbol_aliasing.h
.o/level_heatmap.o: /usr/include/sys/_posix_availability.h
.o/level_heatmap.o: /usr/include/Availability.h
.o/level_heatmap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_heatmap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_heatmap.o: /usr/include/i386/_types.h
.o/level_heatmap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_heatmap.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_heatmap.o: /usr/include/sys/_types/_int8_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_int16_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_int32_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_int64_t.h
.o/level_heatmap.o: /usr/include/_types/_uint8_t.h
.o/level_heatmap.o: /usr/include/_types/_uint16_t.h
.o/level_heatmap.o: /usr/include/_types/_uint32_t.h
.o/level_heatmap.o: /usr/include/_types/_uint64_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_intptr_t.h
.o/level_heatmap.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_heatmap.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_heatmap.o: /usr/include/_types/_intmax_t.h
.o/level_heatmap.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_heatmap.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_heatmap.o: my_bounds_check.h /usr/include/assert.h
.o/level_heatmap.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_heatmap.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_heatmap.o: /usr/include/sys/_types/_null.h
.o/level_heatmap.o: /usr/include/sys/_types/_size_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_heatmap.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_heatmap.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_ssize_t.h
.o/level_heatmap.o: /usr/include/secure/_stdio.h
.o/level_heatmap.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_heatmap.o: /usr/include/sys/_types/_clock_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_time_t.h
.o/level_heatmap.o: /usr/include/sys/_types/_timespec.h
.o/level_heatmap.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_heatmap.o: /usr/include/sys/_types/_wint_t.h
.o/level_heatmap.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_heatmap.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_heatmap.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/level_heatmap.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/level_heatmap.o: my_charmap.h my_dmap.h my_level_static.h
.o/level_heatmap.o: my_dungeon_grid.h
.o/level_init.o: my_game.h my_world.h my_point.h my_math.h
.o/level_init.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/level_init.o: /usr/include/sys/_symbol_aliasing.h
.o/level_init.o: /usr/include/sys/_posix_availability.h
.o/level_init.o: /usr/include/Availability.h
.o/level_init.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/level_init.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/level_init.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/level_init.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_init.o: /usr/include/i386/_types.h
.o/level_init.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_init.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_init.o: /usr/include/sys/_types/_int8_t.h
.o/level_init.o: /usr/include/sys/_types/_int16_t.h
.o/level_init.o: /usr/include/sys/_types/_int32_t.h
.o/level_init.o: /usr/include/sys/_types/_int64_t.h
.o/level_init.o: /usr/include/_types/_uint8_t.h
.o/level_init.o: /usr/include/_types/_uint16_t.h
.o/level_init.o: /usr/include/_types/_uint32_t.h
.o/level_init.o: /usr/include/_types/_uint64_t.h
.o/level_init.o: /usr/include/sys/_types/_intptr_t.h
.o/level_init.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_init.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_init.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_init.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_init.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_init.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_init.o: /usr/include/_types/_intmax_t.h
.o/level_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/level_init.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/level_init.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/level_init.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_init.o: /usr/include/sys/_types/_null.h
.o/level_init.o: /usr/include/sys/_types/_size_t.h
.o/level_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_init.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_init.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_init.o: /usr/include/sys/_types/_ssize_t.h
.o/level_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_init.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_init.o: /usr/include/sys/_types/_time_t.h
.o/level_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_init.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_init.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_init.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_init.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/level_init.o: my_dice.h my_tile.h my_color.h my_thing_ai.h
.o/level_log.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/level_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_log.o: /usr/include/sys/_posix_availability.h
.o/level_log.o: /usr/include/Availability.h
.o/level_log.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/level_log.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/level_log.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/level_log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_log.o: /usr/include/i386/_types.h
.o/level_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_log.o: /usr/include/sys/_types/_int8_t.h
.o/level_log.o: /usr/include/sys/_types/_int16_t.h
.o/level_log.o: /usr/include/sys/_types/_int32_t.h
.o/level_log.o: /usr/include/sys/_types/_int64_t.h
.o/level_log.o: /usr/include/_types/_uint8_t.h
.o/level_log.o: /usr/include/_types/_uint16_t.h
.o/level_log.o: /usr/include/_types/_uint32_t.h
.o/level_log.o: /usr/include/_types/_uint64_t.h
.o/level_log.o: /usr/include/sys/_types/_intptr_t.h
.o/level_log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_log.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_log.o: /usr/include/_types/_intmax_t.h
.o/level_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/level_log.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/level_log.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/level_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_log.o: /usr/include/sys/_types/_null.h
.o/level_log.o: /usr/include/sys/_types/_size_t.h
.o/level_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_log.o: /usr/include/sys/_types/_ssize_t.h
.o/level_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_log.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_log.o: /usr/include/sys/_types/_time_t.h
.o/level_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_log.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_log.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_log.o: my_dungeon_grid.h my_traceback.h my_console.h
.o/level_log.o: my_wid_console.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/level_log.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/level_log.o: my_thing_template.h my_dice.h my_thing_ai.h my_log.h
.o/level_map_things.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/level_map_things.o: my_pcg_basic.h /usr/include/inttypes.h
.o/level_map_things.o: /usr/include/sys/cdefs.h
.o/level_map_things.o: /usr/include/sys/_symbol_aliasing.h
.o/level_map_things.o: /usr/include/sys/_posix_availability.h
.o/level_map_things.o: /usr/include/Availability.h
.o/level_map_things.o: /usr/include/AvailabilityInternal.h
.o/level_map_things.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_map_things.o: /usr/include/machine/_types.h
.o/level_map_things.o: /usr/include/i386/_types.h
.o/level_map_things.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_map_things.o: /usr/include/sys/_types/_wchar_t.h
.o/level_map_things.o: /usr/include/stdint.h
.o/level_map_things.o: /usr/include/sys/_types/_int8_t.h
.o/level_map_things.o: /usr/include/sys/_types/_int16_t.h
.o/level_map_things.o: /usr/include/sys/_types/_int32_t.h
.o/level_map_things.o: /usr/include/sys/_types/_int64_t.h
.o/level_map_things.o: /usr/include/_types/_uint8_t.h
.o/level_map_things.o: /usr/include/_types/_uint16_t.h
.o/level_map_things.o: /usr/include/_types/_uint32_t.h
.o/level_map_things.o: /usr/include/_types/_uint64_t.h
.o/level_map_things.o: /usr/include/sys/_types/_intptr_t.h
.o/level_map_things.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_map_things.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_map_things.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_map_things.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_map_things.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_map_things.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_map_things.o: /usr/include/_types/_intmax_t.h
.o/level_map_things.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_map_things.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_map_things.o: my_bounds_check.h /usr/include/assert.h
.o/level_map_things.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_map_things.o: my_command.h my_token.h my_string.h
.o/level_map_things.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/level_map_things.o: /usr/include/sys/_types/_size_t.h
.o/level_map_things.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_map_things.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_map_things.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_map_things.o: /usr/include/_stdio.h
.o/level_map_things.o: /usr/include/sys/_types/_va_list.h
.o/level_map_things.o: /usr/include/sys/stdio.h
.o/level_map_things.o: /usr/include/sys/_types/_off_t.h
.o/level_map_things.o: /usr/include/sys/_types/_ssize_t.h
.o/level_map_things.o: /usr/include/secure/_stdio.h
.o/level_map_things.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_map_things.o: /usr/include/sys/_types/_clock_t.h
.o/level_map_things.o: /usr/include/sys/_types/_time_t.h
.o/level_map_things.o: /usr/include/sys/_types/_timespec.h
.o/level_map_things.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_map_things.o: /usr/include/sys/_types/_wint_t.h
.o/level_map_things.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_map_things.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_map_things.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/level_map_things.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_map_things.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_map_things.o: my_dungeon_grid.h my_thing.h my_light.h
.o/level_map_things.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/level_map_things.o: my_thing_ai.h
.o/level_map_update.o: my_game.h my_world.h my_point.h my_math.h
.o/level_map_update.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/level_map_update.o: /usr/include/sys/_symbol_aliasing.h
.o/level_map_update.o: /usr/include/sys/_posix_availability.h
.o/level_map_update.o: /usr/include/Availability.h
.o/level_map_update.o: /usr/include/AvailabilityInternal.h
.o/level_map_update.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/level_map_update.o: my_main.h my_sys.h my_pcg_basic.h
.o/level_map_update.o: /usr/include/inttypes.h /usr/include/_types.h
.o/level_map_update.o: /usr/include/sys/_types.h
.o/level_map_update.o: /usr/include/machine/_types.h
.o/level_map_update.o: /usr/include/i386/_types.h
.o/level_map_update.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_map_update.o: /usr/include/sys/_types/_wchar_t.h
.o/level_map_update.o: /usr/include/stdint.h
.o/level_map_update.o: /usr/include/sys/_types/_int8_t.h
.o/level_map_update.o: /usr/include/sys/_types/_int16_t.h
.o/level_map_update.o: /usr/include/sys/_types/_int32_t.h
.o/level_map_update.o: /usr/include/sys/_types/_int64_t.h
.o/level_map_update.o: /usr/include/_types/_uint8_t.h
.o/level_map_update.o: /usr/include/_types/_uint16_t.h
.o/level_map_update.o: /usr/include/_types/_uint32_t.h
.o/level_map_update.o: /usr/include/_types/_uint64_t.h
.o/level_map_update.o: /usr/include/sys/_types/_intptr_t.h
.o/level_map_update.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_map_update.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_map_update.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_map_update.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_map_update.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_map_update.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_map_update.o: /usr/include/_types/_intmax_t.h
.o/level_map_update.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_map_update.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_map_update.o: my_bounds_check.h /usr/include/assert.h
.o/level_map_update.o: my_vector_bounds_check.h my_command.h my_token.h
.o/level_map_update.o: my_string.h /usr/include/wchar.h
.o/level_map_update.o: /usr/include/sys/_types/_null.h
.o/level_map_update.o: /usr/include/sys/_types/_size_t.h
.o/level_map_update.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_map_update.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_map_update.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_map_update.o: /usr/include/_stdio.h
.o/level_map_update.o: /usr/include/sys/_types/_va_list.h
.o/level_map_update.o: /usr/include/sys/stdio.h
.o/level_map_update.o: /usr/include/sys/_types/_off_t.h
.o/level_map_update.o: /usr/include/sys/_types/_ssize_t.h
.o/level_map_update.o: /usr/include/secure/_stdio.h
.o/level_map_update.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_map_update.o: /usr/include/sys/_types/_clock_t.h
.o/level_map_update.o: /usr/include/sys/_types/_time_t.h
.o/level_map_update.o: /usr/include/sys/_types/_timespec.h
.o/level_map_update.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_map_update.o: /usr/include/sys/_types/_wint_t.h
.o/level_map_update.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_map_update.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_map_update.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_map_update.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_map_update.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/level_map_update.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/level_map_update.o: my_color.h my_thing_ai.h
.o/level_minimap.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_minimap.o: /usr/include/sys/cdefs.h
.o/level_minimap.o: /usr/include/sys/_symbol_aliasing.h
.o/level_minimap.o: /usr/include/sys/_posix_availability.h
.o/level_minimap.o: /usr/include/Availability.h
.o/level_minimap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_minimap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_minimap.o: /usr/include/i386/_types.h
.o/level_minimap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_minimap.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_minimap.o: /usr/include/sys/_types/_int8_t.h
.o/level_minimap.o: /usr/include/sys/_types/_int16_t.h
.o/level_minimap.o: /usr/include/sys/_types/_int32_t.h
.o/level_minimap.o: /usr/include/sys/_types/_int64_t.h
.o/level_minimap.o: /usr/include/_types/_uint8_t.h
.o/level_minimap.o: /usr/include/_types/_uint16_t.h
.o/level_minimap.o: /usr/include/_types/_uint32_t.h
.o/level_minimap.o: /usr/include/_types/_uint64_t.h
.o/level_minimap.o: /usr/include/sys/_types/_intptr_t.h
.o/level_minimap.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_minimap.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_minimap.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_minimap.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_minimap.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_minimap.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_minimap.o: /usr/include/_types/_intmax_t.h
.o/level_minimap.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_minimap.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_minimap.o: my_bounds_check.h /usr/include/assert.h
.o/level_minimap.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_minimap.o: my_game.h my_world.h my_point.h my_math.h
.o/level_minimap.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_minimap.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_minimap.o: /usr/include/sys/_types/_null.h
.o/level_minimap.o: /usr/include/sys/_types/_size_t.h
.o/level_minimap.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_minimap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_minimap.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_minimap.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_minimap.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_minimap.o: /usr/include/sys/_types/_ssize_t.h
.o/level_minimap.o: /usr/include/secure/_stdio.h
.o/level_minimap.o: /usr/include/secure/_common.h /usr/include/time.h
.o/level_minimap.o: /usr/include/sys/_types/_clock_t.h
.o/level_minimap.o: /usr/include/sys/_types/_time_t.h
.o/level_minimap.o: /usr/include/sys/_types/_timespec.h
.o/level_minimap.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_minimap.o: /usr/include/sys/_types/_wint_t.h
.o/level_minimap.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_minimap.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_minimap.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_minimap.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_minimap.o: my_level_static.h my_dungeon_grid.h my_tile.h my_color.h
.o/level_minimap.o: my_tex.h my_gl.h my_thing.h my_light.h
.o/level_minimap.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/level_scroll.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_scroll.o: /usr/include/sys/cdefs.h
.o/level_scroll.o: /usr/include/sys/_symbol_aliasing.h
.o/level_scroll.o: /usr/include/sys/_posix_availability.h
.o/level_scroll.o: /usr/include/Availability.h
.o/level_scroll.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_scroll.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_scroll.o: /usr/include/i386/_types.h
.o/level_scroll.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_scroll.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_scroll.o: /usr/include/sys/_types/_int8_t.h
.o/level_scroll.o: /usr/include/sys/_types/_int16_t.h
.o/level_scroll.o: /usr/include/sys/_types/_int32_t.h
.o/level_scroll.o: /usr/include/sys/_types/_int64_t.h
.o/level_scroll.o: /usr/include/_types/_uint8_t.h
.o/level_scroll.o: /usr/include/_types/_uint16_t.h
.o/level_scroll.o: /usr/include/_types/_uint32_t.h
.o/level_scroll.o: /usr/include/_types/_uint64_t.h
.o/level_scroll.o: /usr/include/sys/_types/_intptr_t.h
.o/level_scroll.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_scroll.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_scroll.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_scroll.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_scroll.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_scroll.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_scroll.o: /usr/include/_types/_intmax_t.h
.o/level_scroll.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_scroll.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_scroll.o: my_bounds_check.h /usr/include/assert.h
.o/level_scroll.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_scroll.o: my_game.h my_world.h my_point.h my_math.h
.o/level_scroll.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_scroll.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_scroll.o: /usr/include/sys/_types/_null.h
.o/level_scroll.o: /usr/include/sys/_types/_size_t.h
.o/level_scroll.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_scroll.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_scroll.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_scroll.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_scroll.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_scroll.o: /usr/include/sys/_types/_ssize_t.h
.o/level_scroll.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_scroll.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_scroll.o: /usr/include/sys/_types/_time_t.h
.o/level_scroll.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_scroll.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_scroll.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_scroll.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_scroll.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_scroll.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_scroll.o: my_level_static.h my_dungeon_grid.h my_tile.h my_color.h
.o/level_scroll.o: my_tex.h my_gl.h my_thing.h my_light.h my_thing_template.h
.o/level_scroll.o: my_dice.h my_thing_ai.h my_wid.h my_ascii.h my_wid_tiles.h
.o/level_scroll.o: my_wid_rightbar.h
.o/level_static.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/level_static.o: my_pcg_basic.h /usr/include/inttypes.h
.o/level_static.o: /usr/include/sys/cdefs.h
.o/level_static.o: /usr/include/sys/_symbol_aliasing.h
.o/level_static.o: /usr/include/sys/_posix_availability.h
.o/level_static.o: /usr/include/Availability.h
.o/level_static.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_static.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_static.o: /usr/include/i386/_types.h
.o/level_static.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_static.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_static.o: /usr/include/sys/_types/_int8_t.h
.o/level_static.o: /usr/include/sys/_types/_int16_t.h
.o/level_static.o: /usr/include/sys/_types/_int32_t.h
.o/level_static.o: /usr/include/sys/_types/_int64_t.h
.o/level_static.o: /usr/include/_types/_uint8_t.h
.o/level_static.o: /usr/include/_types/_uint16_t.h
.o/level_static.o: /usr/include/_types/_uint32_t.h
.o/level_static.o: /usr/include/_types/_uint64_t.h
.o/level_static.o: /usr/include/sys/_types/_intptr_t.h
.o/level_static.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_static.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_static.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_static.o: /usr/include/_types/_intmax_t.h
.o/level_static.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_static.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_static.o: my_bounds_check.h /usr/include/assert.h
.o/level_static.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_static.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_static.o: /usr/include/sys/_types/_null.h
.o/level_static.o: /usr/include/sys/_types/_size_t.h
.o/level_static.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_static.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_static.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_static.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_static.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_static.o: /usr/include/sys/_types/_ssize_t.h
.o/level_static.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_static.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_static.o: /usr/include/sys/_types/_time_t.h
.o/level_static.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_static.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_static.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_static.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_static.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/level_static.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/level_static.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/level_tick.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_tick.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_tick.o: /usr/include/sys/_posix_availability.h
.o/level_tick.o: /usr/include/Availability.h
.o/level_tick.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_tick.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_tick.o: /usr/include/i386/_types.h
.o/level_tick.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_tick.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_tick.o: /usr/include/sys/_types/_int8_t.h
.o/level_tick.o: /usr/include/sys/_types/_int16_t.h
.o/level_tick.o: /usr/include/sys/_types/_int32_t.h
.o/level_tick.o: /usr/include/sys/_types/_int64_t.h
.o/level_tick.o: /usr/include/_types/_uint8_t.h
.o/level_tick.o: /usr/include/_types/_uint16_t.h
.o/level_tick.o: /usr/include/_types/_uint32_t.h
.o/level_tick.o: /usr/include/_types/_uint64_t.h
.o/level_tick.o: /usr/include/sys/_types/_intptr_t.h
.o/level_tick.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_tick.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_tick.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_tick.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_tick.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_tick.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_tick.o: /usr/include/_types/_intmax_t.h
.o/level_tick.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/level_tick.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/level_tick.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_tick.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/level_tick.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/level_tick.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_tick.o: /usr/include/sys/_types/_null.h
.o/level_tick.o: /usr/include/sys/_types/_size_t.h
.o/level_tick.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_tick.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_tick.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_tick.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_tick.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_tick.o: /usr/include/sys/_types/_ssize_t.h
.o/level_tick.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_tick.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_tick.o: /usr/include/sys/_types/_time_t.h
.o/level_tick.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_tick.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_tick.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_tick.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_tick.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/level_tick.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/level_tick.o: my_dungeon_grid.h my_wid_console.h my_wid.h my_ascii.h
.o/level_tick.o: my_tex.h my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/level_tick.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/level_tick.o: my_python.h my_player.h
.o/level_update.o: my_game.h my_world.h my_point.h my_math.h
.o/level_update.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/level_update.o: /usr/include/sys/_symbol_aliasing.h
.o/level_update.o: /usr/include/sys/_posix_availability.h
.o/level_update.o: /usr/include/Availability.h
.o/level_update.o: /usr/include/AvailabilityInternal.h
.o/level_update.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/level_update.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_update.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_update.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/level_update.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_update.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_update.o: /usr/include/sys/_types/_int8_t.h
.o/level_update.o: /usr/include/sys/_types/_int16_t.h
.o/level_update.o: /usr/include/sys/_types/_int32_t.h
.o/level_update.o: /usr/include/sys/_types/_int64_t.h
.o/level_update.o: /usr/include/_types/_uint8_t.h
.o/level_update.o: /usr/include/_types/_uint16_t.h
.o/level_update.o: /usr/include/_types/_uint32_t.h
.o/level_update.o: /usr/include/_types/_uint64_t.h
.o/level_update.o: /usr/include/sys/_types/_intptr_t.h
.o/level_update.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_update.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_update.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_update.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_update.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_update.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_update.o: /usr/include/_types/_intmax_t.h
.o/level_update.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_update.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/level_update.o: my_bounds_check.h /usr/include/assert.h
.o/level_update.o: my_vector_bounds_check.h my_command.h my_token.h
.o/level_update.o: my_string.h /usr/include/wchar.h
.o/level_update.o: /usr/include/sys/_types/_null.h
.o/level_update.o: /usr/include/sys/_types/_size_t.h
.o/level_update.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_update.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_update.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/level_update.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level_update.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/level_update.o: /usr/include/sys/_types/_ssize_t.h
.o/level_update.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_update.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_update.o: /usr/include/sys/_types/_time_t.h
.o/level_update.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_update.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_update.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_update.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/level_update.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/level_update.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/level_update.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/level_update.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/level_update.o: my_thing_ai.h
.o/light.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/light.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/light.o: /usr/include/sys/_posix_availability.h
.o/light.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/light.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h my_main.h
.o/light.o: my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/light.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/light.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/light.o: /usr/include/sys/_pthread/_pthread_types.h
.o/light.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/light.o: /usr/include/sys/_types/_int8_t.h
.o/light.o: /usr/include/sys/_types/_int16_t.h
.o/light.o: /usr/include/sys/_types/_int32_t.h
.o/light.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/light.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/light.o: /usr/include/_types/_uint64_t.h
.o/light.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/light.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/light.o: /usr/include/sys/_types/_u_int16_t.h
.o/light.o: /usr/include/sys/_types/_u_int32_t.h
.o/light.o: /usr/include/sys/_types/_u_int64_t.h
.o/light.o: /usr/include/sys/_types/_uintptr_t.h
.o/light.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/light.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/light.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/light.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/light.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/light.o: /usr/include/sys/_types/_mbstate_t.h
.o/light.o: /usr/include/sys/_types/_ct_rune_t.h
.o/light.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/light.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/light.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/light.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/light.o: /usr/include/secure/_common.h /usr/include/time.h
.o/light.o: /usr/include/sys/_types/_clock_t.h
.o/light.o: /usr/include/sys/_types/_time_t.h
.o/light.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/light.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/light.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/light.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/light.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/light.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/light.o: my_dungeon_grid.h my_gl.h my_color.h my_tex.h my_thing.h
.o/light.o: my_light.h my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/light_log.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/light_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/light_log.o: /usr/include/sys/_posix_availability.h
.o/light_log.o: /usr/include/Availability.h
.o/light_log.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/light_log.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/light_log.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/light_log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/light_log.o: /usr/include/i386/_types.h
.o/light_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/light_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/light_log.o: /usr/include/sys/_types/_int8_t.h
.o/light_log.o: /usr/include/sys/_types/_int16_t.h
.o/light_log.o: /usr/include/sys/_types/_int32_t.h
.o/light_log.o: /usr/include/sys/_types/_int64_t.h
.o/light_log.o: /usr/include/_types/_uint8_t.h
.o/light_log.o: /usr/include/_types/_uint16_t.h
.o/light_log.o: /usr/include/_types/_uint32_t.h
.o/light_log.o: /usr/include/_types/_uint64_t.h
.o/light_log.o: /usr/include/sys/_types/_intptr_t.h
.o/light_log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/light_log.o: /usr/include/sys/_types/_u_int8_t.h
.o/light_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/light_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/light_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/light_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/light_log.o: /usr/include/_types/_intmax_t.h
.o/light_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/light_log.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/light_log.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/light_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/light_log.o: /usr/include/sys/_types/_null.h
.o/light_log.o: /usr/include/sys/_types/_size_t.h
.o/light_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/light_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/light_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/light_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/light_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/light_log.o: /usr/include/sys/_types/_ssize_t.h
.o/light_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/light_log.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/light_log.o: /usr/include/sys/_types/_time_t.h
.o/light_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/light_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/light_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/light_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/light_log.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/light_log.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/light_log.o: my_dungeon_grid.h my_traceback.h my_console.h
.o/light_log.o: my_wid_console.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/light_log.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/light_log.o: my_thing_template.h my_dice.h my_thing_ai.h my_log.h
.o/log.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/log.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/log.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/log.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/log.o: /usr/include/inttypes.h /usr/include/_types.h
.o/log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/log.o: /usr/include/i386/_types.h
.o/log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/log.o: /usr/include/sys/_types/_int8_t.h
.o/log.o: /usr/include/sys/_types/_int16_t.h
.o/log.o: /usr/include/sys/_types/_int32_t.h
.o/log.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/log.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/log.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/log.o: /usr/include/sys/_types/_u_int8_t.h
.o/log.o: /usr/include/sys/_types/_u_int16_t.h
.o/log.o: /usr/include/sys/_types/_u_int32_t.h
.o/log.o: /usr/include/sys/_types/_u_int64_t.h
.o/log.o: /usr/include/sys/_types/_uintptr_t.h
.o/log.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/log.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/log.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/log.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/log.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/log.o: /usr/include/sys/_types/_mbstate_t.h
.o/log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/log.o: /usr/include/secure/_common.h /usr/include/time.h
.o/log.o: /usr/include/sys/_types/_clock_t.h
.o/log.o: /usr/include/sys/_types/_time_t.h
.o/log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_particle.h
.o/log.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/log.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/log.o: my_traceback.h my_wid_console.h my_wid.h my_ascii.h my_tex.h
.o/log.o: my_tile.h my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/log.o: my_thing_template.h my_dice.h my_thing_ai.h my_wid_minicon.h
.o/log.o: my_wid_botcon.h my_python.h my_console.h my_log.h
.o/log_util.o: my_ascii.h /usr/include/wchar.h /usr/include/_types.h
.o/log_util.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/log_util.o: /usr/include/sys/_symbol_aliasing.h
.o/log_util.o: /usr/include/sys/_posix_availability.h
.o/log_util.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/log_util.o: /usr/include/sys/_pthread/_pthread_types.h
.o/log_util.o: /usr/include/Availability.h
.o/log_util.o: /usr/include/AvailabilityInternal.h
.o/log_util.o: /usr/include/sys/_types/_null.h
.o/log_util.o: /usr/include/sys/_types/_size_t.h
.o/log_util.o: /usr/include/sys/_types/_mbstate_t.h
.o/log_util.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/log_util.o: /usr/include/sys/_types/_int8_t.h
.o/log_util.o: /usr/include/sys/_types/_int16_t.h
.o/log_util.o: /usr/include/sys/_types/_int32_t.h
.o/log_util.o: /usr/include/sys/_types/_int64_t.h
.o/log_util.o: /usr/include/sys/_types/_u_int8_t.h
.o/log_util.o: /usr/include/sys/_types/_u_int16_t.h
.o/log_util.o: /usr/include/sys/_types/_u_int32_t.h
.o/log_util.o: /usr/include/sys/_types/_u_int64_t.h
.o/log_util.o: /usr/include/sys/_types/_intptr_t.h
.o/log_util.o: /usr/include/sys/_types/_uintptr_t.h
.o/log_util.o: /usr/include/sys/_types/_ct_rune_t.h
.o/log_util.o: /usr/include/sys/_types/_rune_t.h
.o/log_util.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/log_util.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/log_util.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/log_util.o: /usr/include/sys/_types/_ssize_t.h
.o/log_util.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/log_util.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/log_util.o: /usr/include/sys/_types/_time_t.h
.o/log_util.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/log_util.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/log_util.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/log_util.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h
.o/log_util.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/log_util.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/log_util.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/log_util.o: /usr/include/_types/_uint32_t.h
.o/log_util.o: /usr/include/_types/_uint64_t.h
.o/log_util.o: /usr/include/_types/_intmax_t.h
.o/log_util.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/log_util.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/log_util.o: /usr/include/assert.h my_vector_bounds_check.h
.o/log_util.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/log_util.o: slre.h my_point.h my_math.h /usr/include/math.h my_color.h
.o/main.o: /usr/include/strings.h /usr/include/_types.h
.o/main.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/main.o: /usr/include/sys/_symbol_aliasing.h
.o/main.o: /usr/include/sys/_posix_availability.h
.o/main.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/main.o: /usr/include/sys/_pthread/_pthread_types.h
.o/main.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/main.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/main.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_rsize_t.h
.o/main.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/main.o: /usr/include/sys/_types/_int8_t.h
.o/main.o: /usr/include/sys/_types/_int16_t.h
.o/main.o: /usr/include/sys/_types/_int32_t.h
.o/main.o: /usr/include/sys/_types/_int64_t.h
.o/main.o: /usr/include/sys/_types/_u_int8_t.h
.o/main.o: /usr/include/sys/_types/_u_int16_t.h
.o/main.o: /usr/include/sys/_types/_u_int32_t.h
.o/main.o: /usr/include/sys/_types/_u_int64_t.h
.o/main.o: /usr/include/sys/_types/_intptr_t.h
.o/main.o: /usr/include/sys/_types/_uintptr_t.h
.o/main.o: /usr/include/sys/_types/_errno_t.h
.o/main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/main.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/main.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/main.o: /usr/include/sys/_types/_time_t.h
.o/main.o: /usr/include/sys/_types/_timespec.h /usr/include/unistd.h
.o/main.o: /usr/include/sys/unistd.h
.o/main.o: /usr/include/sys/_types/_posix_vdisable.h
.o/main.o: /usr/include/sys/_types/_seek_set.h
.o/main.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_uint32_t.h
.o/main.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/main.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_pid_t.h
.o/main.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/main.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/main.o: /usr/include/sys/_types/_timeval.h
.o/main.o: /usr/include/sys/_types/_suseconds_t.h
.o/main.o: /usr/include/sys/_types/_sigset_t.h
.o/main.o: /usr/include/sys/_types/_fd_setsize.h
.o/main.o: /usr/include/sys/_types/_fd_set.h
.o/main.o: /usr/include/sys/_types/_fd_clr.h
.o/main.o: /usr/include/sys/_types/_fd_isset.h
.o/main.o: /usr/include/sys/_types/_fd_zero.h
.o/main.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/main.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/main.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/main.o: /usr/include/libgen.h /usr/include/signal.h
.o/main.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/main.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/main.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/main.o: /usr/include/mach/i386/_structs.h
.o/main.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/main.o: /usr/include/sys/_types/_sigaltstack.h
.o/main.o: /usr/include/sys/_types/_ucontext.h
.o/main.o: /usr/include/sys/_pthread/_pthread_t.h my_game.h my_world.h
.o/main.o: my_point.h my_math.h /usr/include/math.h c_plus_plus_serializer.h
.o/main.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/main.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/main.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_intmax_t.h
.o/main.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/main.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/main.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/main.o: my_token.h my_string.h /usr/include/wchar.h
.o/main.o: /usr/include/sys/_types/_mbstate_t.h
.o/main.o: /usr/include/sys/_types/_ct_rune_t.h
.o/main.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/main.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/main.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/main.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/main.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/main.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/main.o: slre.h my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/main.o: my_room.h my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/main.o: my_dungeon_grid.h my_thing_template.h my_dice.h my_tile.h
.o/main.o: my_color.h my_python.h my_gl.h my_wid_console.h my_wid.h
.o/main.o: my_ascii.h my_tex.h my_wid_tiles.h my_thing.h my_light.h
.o/main.o: my_thing_ai.h my_wid_minicon.h my_wid_botcon.h my_wid_test.h
.o/main.o: my_font.h my_dir.h my_file.h my_gfx.h my_random_name.h
.o/minilzo.o: minilzo.h /usr/include/limits.h /usr/include/sys/cdefs.h
.o/minilzo.o: /usr/include/sys/_symbol_aliasing.h
.o/minilzo.o: /usr/include/sys/_posix_availability.h
.o/minilzo.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/minilzo.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
.o/minilzo.o: /usr/include/stddef.h /usr/include/_types.h
.o/minilzo.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/minilzo.o: /usr/include/i386/_types.h
.o/minilzo.o: /usr/include/sys/_pthread/_pthread_types.h
.o/minilzo.o: /usr/include/sys/_types/_null.h
.o/minilzo.o: /usr/include/sys/_types/_offsetof.h
.o/minilzo.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/minilzo.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/minilzo.o: /usr/include/sys/_types/_int8_t.h
.o/minilzo.o: /usr/include/sys/_types/_int16_t.h
.o/minilzo.o: /usr/include/sys/_types/_int32_t.h
.o/minilzo.o: /usr/include/sys/_types/_int64_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int8_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int16_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int32_t.h
.o/minilzo.o: /usr/include/sys/_types/_u_int64_t.h
.o/minilzo.o: /usr/include/sys/_types/_intptr_t.h
.o/minilzo.o: /usr/include/sys/_types/_uintptr_t.h
.o/minilzo.o: /usr/include/sys/_types/_rsize_t.h
.o/minilzo.o: /usr/include/sys/_types/_size_t.h
.o/minilzo.o: /usr/include/sys/_types/_wchar_t.h
.o/minilzo.o: /usr/include/sys/_types/_wint_t.h lzodefs.h lzoconf.h
.o/minilzo.o: /usr/include/string.h /usr/include/Availability.h
.o/minilzo.o: /usr/include/AvailabilityInternal.h
.o/minilzo.o: /usr/include/sys/_types/_errno_t.h
.o/minilzo.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/minilzo.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/minilzo.o: /usr/include/secure/_string.h /usr/include/assert.h
.o/particle.o: my_particle.h my_main.h my_sys.h my_pcg_basic.h
.o/particle.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/particle.o: /usr/include/sys/_symbol_aliasing.h
.o/particle.o: /usr/include/sys/_posix_availability.h
.o/particle.o: /usr/include/Availability.h
.o/particle.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/particle.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/particle.o: /usr/include/i386/_types.h
.o/particle.o: /usr/include/sys/_pthread/_pthread_types.h
.o/particle.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/particle.o: /usr/include/sys/_types/_int8_t.h
.o/particle.o: /usr/include/sys/_types/_int16_t.h
.o/particle.o: /usr/include/sys/_types/_int32_t.h
.o/particle.o: /usr/include/sys/_types/_int64_t.h
.o/particle.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/particle.o: /usr/include/_types/_uint32_t.h
.o/particle.o: /usr/include/_types/_uint64_t.h
.o/particle.o: /usr/include/sys/_types/_intptr_t.h
.o/particle.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/particle.o: /usr/include/sys/_types/_u_int8_t.h
.o/particle.o: /usr/include/sys/_types/_u_int16_t.h
.o/particle.o: /usr/include/sys/_types/_u_int32_t.h
.o/particle.o: /usr/include/sys/_types/_u_int64_t.h
.o/particle.o: /usr/include/sys/_types/_uintptr_t.h
.o/particle.o: /usr/include/_types/_intmax_t.h
.o/particle.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/particle.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/particle.o: /usr/include/assert.h my_vector_bounds_check.h
.o/particle.o: c_plus_plus_serializer.h my_point.h my_math.h
.o/particle.o: /usr/include/math.h my_size.h my_thing_id.h my_level.h
.o/particle.o: my_time.h my_sdl.h my_command.h my_token.h my_string.h
.o/particle.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/particle.o: /usr/include/sys/_types/_size_t.h
.o/particle.o: /usr/include/sys/_types/_mbstate_t.h
.o/particle.o: /usr/include/sys/_types/_ct_rune_t.h
.o/particle.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/particle.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/particle.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/particle.o: /usr/include/sys/_types/_ssize_t.h
.o/particle.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/particle.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/particle.o: /usr/include/sys/_types/_time_t.h
.o/particle.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/particle.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/particle.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/particle.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/particle.o: my_dungeon.h my_room.h my_depth.h my_charmap.h my_dmap.h
.o/particle.o: my_level_static.h my_dungeon_grid.h my_tile.h my_color.h
.o/particle.o: my_gl.h my_thing.h my_light.h my_thing_template.h my_dice.h
.o/particle.o: my_thing_ai.h my_game.h my_world.h
.o/pcg_basic.o: my_pcg_basic.h /usr/include/inttypes.h
.o/pcg_basic.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/pcg_basic.o: /usr/include/sys/_posix_availability.h
.o/pcg_basic.o: /usr/include/Availability.h
.o/pcg_basic.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/pcg_basic.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/pcg_basic.o: /usr/include/i386/_types.h
.o/pcg_basic.o: /usr/include/sys/_pthread/_pthread_types.h
.o/pcg_basic.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/pcg_basic.o: /usr/include/sys/_types/_int8_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_int16_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_int32_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_int64_t.h
.o/pcg_basic.o: /usr/include/_types/_uint8_t.h
.o/pcg_basic.o: /usr/include/_types/_uint16_t.h
.o/pcg_basic.o: /usr/include/_types/_uint32_t.h
.o/pcg_basic.o: /usr/include/_types/_uint64_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_intptr_t.h
.o/pcg_basic.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int8_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int16_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int32_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_u_int64_t.h
.o/pcg_basic.o: /usr/include/sys/_types/_uintptr_t.h
.o/pcg_basic.o: /usr/include/_types/_intmax_t.h
.o/pcg_basic.o: /usr/include/_types/_uintmax_t.h
.o/player.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/player.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/player.o: /usr/include/sys/_posix_availability.h
.o/player.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/player.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/player.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/player.o: /usr/include/sys/_pthread/_pthread_types.h
.o/player.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/player.o: /usr/include/sys/_types/_int8_t.h
.o/player.o: /usr/include/sys/_types/_int16_t.h
.o/player.o: /usr/include/sys/_types/_int32_t.h
.o/player.o: /usr/include/sys/_types/_int64_t.h
.o/player.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/player.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/player.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/player.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/player.o: /usr/include/sys/_types/_u_int16_t.h
.o/player.o: /usr/include/sys/_types/_u_int32_t.h
.o/player.o: /usr/include/sys/_types/_u_int64_t.h
.o/player.o: /usr/include/sys/_types/_uintptr_t.h
.o/player.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/player.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/player.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/player.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_game.h
.o/player.o: my_world.h my_point.h my_math.h /usr/include/math.h my_level.h
.o/player.o: my_time.h my_sdl.h my_command.h my_token.h my_string.h
.o/player.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/player.o: /usr/include/sys/_types/_size_t.h
.o/player.o: /usr/include/sys/_types/_mbstate_t.h
.o/player.o: /usr/include/sys/_types/_ct_rune_t.h
.o/player.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/player.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/player.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/player.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/player.o: /usr/include/secure/_common.h /usr/include/time.h
.o/player.o: /usr/include/sys/_types/_clock_t.h
.o/player.o: /usr/include/sys/_types/_time_t.h
.o/player.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/player.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/player.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/player.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/player.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/player.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/player.o: my_dungeon_grid.h my_wid_console.h my_wid.h my_ascii.h my_tex.h
.o/player.o: my_tile.h my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/player.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/ptrcheck.o: /usr/include/locale.h /usr/include/_locale.h
.o/ptrcheck.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ptrcheck.o: /usr/include/sys/_posix_availability.h /usr/include/_types.h
.o/ptrcheck.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ptrcheck.o: /usr/include/i386/_types.h
.o/ptrcheck.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ptrcheck.o: /usr/include/sys/_types/_null.h /usr/include/stdint.h
.o/ptrcheck.o: /usr/include/sys/_types/_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int64_t.h
.o/ptrcheck.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ptrcheck.o: /usr/include/_types/_uint32_t.h
.o/ptrcheck.o: /usr/include/_types/_uint64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_intptr_t.h
.o/ptrcheck.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uintptr_t.h
.o/ptrcheck.o: /usr/include/_types/_intmax_t.h
.o/ptrcheck.o: /usr/include/_types/_uintmax_t.h /usr/include/stdio.h
.o/ptrcheck.o: /usr/include/_stdio.h /usr/include/Availability.h
.o/ptrcheck.o: /usr/include/AvailabilityInternal.h
.o/ptrcheck.o: /usr/include/sys/_types/_va_list.h
.o/ptrcheck.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/stdio.h
.o/ptrcheck.o: /usr/include/sys/_types/_off_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ssize_t.h
.o/ptrcheck.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ptrcheck.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ptrcheck.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/ptrcheck.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_time_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_timespec.h /usr/include/unistd.h
.o/ptrcheck.o: /usr/include/sys/unistd.h
.o/ptrcheck.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ptrcheck.o: /usr/include/sys/_types/_seek_set.h
.o/ptrcheck.o: /usr/include/sys/_types/_uid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_gid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_pid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_useconds_t.h
.o/ptrcheck.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_def.h
.o/ptrcheck.o: /usr/include/sys/_types/_timeval.h
.o/ptrcheck.o: /usr/include/sys/_types/_suseconds_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_sigset_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_setsize.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_set.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_clr.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_isset.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_zero.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ptrcheck.o: /usr/include/sys/_types/_dev_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_mode_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ptrcheck.o: my_traceback.h my_sprintf.h my_time.h my_sdl.h my_main.h
.o/ptrcheck.o: my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/ptrcheck.o: /usr/include/sys/_types/_wchar_t.h my_ptrcheck.h my_globals.h
.o/ptrcheck.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/ptrcheck.o: /usr/include/assert.h my_vector_bounds_check.h
.o/ptrcheck.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/ptrcheck.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/ptrcheck.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ptrcheck.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ptrcheck.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/py_level.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_level.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_level.o: /usr/include/sys/_posix_availability.h
.o/py_level.o: /usr/include/Availability.h
.o/py_level.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/py_level.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/py_level.o: /usr/include/i386/_types.h
.o/py_level.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_level.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_level.o: /usr/include/sys/_types/_int8_t.h
.o/py_level.o: /usr/include/sys/_types/_int16_t.h
.o/py_level.o: /usr/include/sys/_types/_int32_t.h
.o/py_level.o: /usr/include/sys/_types/_int64_t.h
.o/py_level.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_level.o: /usr/include/_types/_uint32_t.h
.o/py_level.o: /usr/include/_types/_uint64_t.h
.o/py_level.o: /usr/include/sys/_types/_intptr_t.h
.o/py_level.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/py_level.o: /usr/include/sys/_types/_u_int8_t.h
.o/py_level.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_level.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_level.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_level.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_level.o: /usr/include/_types/_intmax_t.h
.o/py_level.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/py_level.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/py_level.o: /usr/include/assert.h my_vector_bounds_check.h
.o/py_level.o: c_plus_plus_serializer.h my_depth.h my_python.h my_point.h
.o/py_level.o: my_math.h /usr/include/math.h my_level_static.h my_charmap.h
.o/py_log.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_log.o: /usr/include/sys/_posix_availability.h
.o/py_log.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_log.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_log.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_log.o: /usr/include/sys/_types/_int8_t.h
.o/py_log.o: /usr/include/sys/_types/_int16_t.h
.o/py_log.o: /usr/include/sys/_types/_int32_t.h
.o/py_log.o: /usr/include/sys/_types/_int64_t.h
.o/py_log.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_log.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_log.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/py_log.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_log.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_log.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/py_log.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/py_log.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_time.h
.o/py_log.o: my_sdl.h my_command.h my_token.h my_string.h
.o/py_log.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/py_log.o: /usr/include/sys/_types/_size_t.h
.o/py_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/py_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_log.o: /usr/include/secure/_common.h /usr/include/time.h
.o/py_log.o: /usr/include/sys/_types/_clock_t.h
.o/py_log.o: /usr/include/sys/_types/_time_t.h
.o/py_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_file.h
.o/py_log.o: my_log.h
.o/py_room.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_room.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_room.o: /usr/include/sys/_posix_availability.h
.o/py_room.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_room.o: c_plus_plus_serializer.h my_room.h my_main.h my_sys.h
.o/py_room.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/py_room.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/py_room.o: /usr/include/i386/_types.h
.o/py_room.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_room.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_room.o: /usr/include/sys/_types/_int8_t.h
.o/py_room.o: /usr/include/sys/_types/_int16_t.h
.o/py_room.o: /usr/include/sys/_types/_int32_t.h
.o/py_room.o: /usr/include/sys/_types/_int64_t.h
.o/py_room.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_room.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_room.o: /usr/include/sys/_types/_intptr_t.h
.o/py_room.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/py_room.o: /usr/include/sys/_types/_u_int8_t.h
.o/py_room.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_room.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_room.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_room.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_room.o: /usr/include/_types/_intmax_t.h
.o/py_room.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/py_room.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/py_room.o: /usr/include/assert.h my_vector_bounds_check.h my_depth.h
.o/py_room.o: my_charmap.h
.o/py_sdl.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_sdl.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_sdl.o: /usr/include/sys/_posix_availability.h
.o/py_sdl.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_sdl.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_sdl.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_sdl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_sdl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_sdl.o: /usr/include/sys/_types/_int8_t.h
.o/py_sdl.o: /usr/include/sys/_types/_int16_t.h
.o/py_sdl.o: /usr/include/sys/_types/_int32_t.h
.o/py_sdl.o: /usr/include/sys/_types/_int64_t.h
.o/py_sdl.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_sdl.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_sdl.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/py_sdl.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_sdl.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_sdl.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_sdl.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_sdl.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/py_sdl.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/py_sdl.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_python.h
.o/py_sdl.o: my_point.h my_math.h /usr/include/math.h my_py_sdl.h
.o/py_tex.o: /usr/include/strings.h /usr/include/_types.h
.o/py_tex.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/py_tex.o: /usr/include/sys/_symbol_aliasing.h
.o/py_tex.o: /usr/include/sys/_posix_availability.h
.o/py_tex.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_tex.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tex.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tex.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/py_tex.o: /usr/include/sys/_types/_null.h
.o/py_tex.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/py_tex.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/py_tex.o: /usr/include/sys/_types/_int16_t.h
.o/py_tex.o: /usr/include/sys/_types/_int32_t.h
.o/py_tex.o: /usr/include/sys/_types/_int64_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int8_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tex.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tex.o: /usr/include/sys/_types/_errno_t.h
.o/py_tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/py_tex.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/py_tex.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tex.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_tex.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_tex.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_tex.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tex.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/py_tex.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/py_tex.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_gl.h
.o/py_tex.o: my_color.h my_point.h my_math.h /usr/include/math.h my_size.h
.o/py_tex.o: my_python.h my_tex.h
.o/py_tile.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_tile.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tile.o: /usr/include/sys/_posix_availability.h
.o/py_tile.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tile.o: c_plus_plus_serializer.h my_tile.h my_sdl.h my_main.h my_sys.h
.o/py_tile.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/py_tile.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/py_tile.o: /usr/include/i386/_types.h
.o/py_tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tile.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_tile.o: /usr/include/sys/_types/_int8_t.h
.o/py_tile.o: /usr/include/sys/_types/_int16_t.h
.o/py_tile.o: /usr/include/sys/_types/_int32_t.h
.o/py_tile.o: /usr/include/sys/_types/_int64_t.h
.o/py_tile.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_tile.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_tile.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tile.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/py_tile.o: /usr/include/sys/_types/_u_int8_t.h
.o/py_tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tile.o: /usr/include/_types/_intmax_t.h
.o/py_tile.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/py_tile.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/py_tile.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/py_tile.o: my_token.h my_string.h /usr/include/wchar.h
.o/py_tile.o: /usr/include/sys/_types/_null.h
.o/py_tile.o: /usr/include/sys/_types/_size_t.h
.o/py_tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/py_tile.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tile.o: /usr/include/secure/_common.h /usr/include/time.h
.o/py_tile.o: /usr/include/sys/_types/_clock_t.h
.o/py_tile.o: /usr/include/sys/_types/_time_t.h
.o/py_tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tile.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_color.h
.o/py_tp.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_tp.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tp.o: /usr/include/sys/_posix_availability.h
.o/py_tp.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tp.o: c_plus_plus_serializer.h my_thing_template.h my_dice.h my_tile.h
.o/py_tp.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/py_tp.o: /usr/include/inttypes.h /usr/include/_types.h
.o/py_tp.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/py_tp.o: /usr/include/i386/_types.h
.o/py_tp.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tp.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_tp.o: /usr/include/sys/_types/_int8_t.h
.o/py_tp.o: /usr/include/sys/_types/_int16_t.h
.o/py_tp.o: /usr/include/sys/_types/_int32_t.h
.o/py_tp.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/py_tp.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/py_tp.o: /usr/include/_types/_uint64_t.h
.o/py_tp.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/py_tp.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_tp.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tp.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tp.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tp.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tp.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tp.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/py_tp.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/py_tp.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/py_tp.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/py_tp.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_tp.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tp.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/py_tp.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_tp.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_tp.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tp.o: /usr/include/secure/_common.h /usr/include/time.h
.o/py_tp.o: /usr/include/sys/_types/_clock_t.h
.o/py_tp.o: /usr/include/sys/_types/_time_t.h
.o/py_tp.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_tp.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tp.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tp.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_color.h
.o/py_tp.o: my_size.h my_game.h my_world.h my_level.h my_time.h my_particle.h
.o/py_tp.o: my_thing_id.h my_dungeon.h my_room.h my_depth.h my_charmap.h
.o/py_tp.o: my_dmap.h my_level_static.h my_dungeon_grid.h my_thing.h
.o/py_tp.o: my_light.h my_thing_ai.h
.o/py_ttf.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_ttf.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_ttf.o: /usr/include/sys/_posix_availability.h
.o/py_ttf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_ttf.o: c_plus_plus_serializer.h my_ascii.h /usr/include/wchar.h
.o/py_ttf.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_ttf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_ttf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_ttf.o: /usr/include/sys/_types/_null.h
.o/py_ttf.o: /usr/include/sys/_types/_size_t.h
.o/py_ttf.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_ttf.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/py_ttf.o: /usr/include/sys/_types/_int8_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int16_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int32_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int64_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int8_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_ttf.o: /usr/include/sys/_types/_intptr_t.h
.o/py_ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_ttf.o: /usr/include/sys/_types/_rune_t.h
.o/py_ttf.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/py_ttf.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_ttf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_ttf.o: /usr/include/secure/_common.h /usr/include/time.h
.o/py_ttf.o: /usr/include/sys/_types/_clock_t.h
.o/py_ttf.o: /usr/include/sys/_types/_time_t.h
.o/py_ttf.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_ttf.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_ttf.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_ttf.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h my_tile.h
.o/py_ttf.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/py_ttf.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/py_ttf.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_ttf.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_ttf.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/py_ttf.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/py_ttf.o: my_vector_bounds_check.h my_command.h my_token.h my_string.h
.o/py_ttf.o: slre.h my_color.h
.o/python.o: my_py_tp.h my_depth.h my_python.h my_point.h my_math.h
.o/python.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/python.o: /usr/include/sys/_symbol_aliasing.h
.o/python.o: /usr/include/sys/_posix_availability.h
.o/python.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/python.o: c_plus_plus_serializer.h my_py_sdl.h my_ascii.h
.o/python.o: /usr/include/wchar.h /usr/include/_types.h
.o/python.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/python.o: /usr/include/i386/_types.h
.o/python.o: /usr/include/sys/_pthread/_pthread_types.h
.o/python.o: /usr/include/sys/_types/_null.h
.o/python.o: /usr/include/sys/_types/_size_t.h
.o/python.o: /usr/include/sys/_types/_mbstate_t.h
.o/python.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/python.o: /usr/include/sys/_types/_int8_t.h
.o/python.o: /usr/include/sys/_types/_int16_t.h
.o/python.o: /usr/include/sys/_types/_int32_t.h
.o/python.o: /usr/include/sys/_types/_int64_t.h
.o/python.o: /usr/include/sys/_types/_u_int8_t.h
.o/python.o: /usr/include/sys/_types/_u_int16_t.h
.o/python.o: /usr/include/sys/_types/_u_int32_t.h
.o/python.o: /usr/include/sys/_types/_u_int64_t.h
.o/python.o: /usr/include/sys/_types/_intptr_t.h
.o/python.o: /usr/include/sys/_types/_uintptr_t.h
.o/python.o: /usr/include/sys/_types/_ct_rune_t.h
.o/python.o: /usr/include/sys/_types/_rune_t.h
.o/python.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/python.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/python.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/python.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/python.o: /usr/include/secure/_common.h /usr/include/time.h
.o/python.o: /usr/include/sys/_types/_clock_t.h
.o/python.o: /usr/include/sys/_types/_time_t.h
.o/python.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/python.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/python.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/python.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h my_tile.h
.o/python.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/python.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/python.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/python.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/python.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/python.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/python.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/python.o: my_vector_bounds_check.h my_command.h my_token.h my_string.h
.o/python.o: slre.h my_color.h my_thing_template.h my_dice.h my_size.h
.o/random_name.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/random_name.o: /usr/include/sys/cdefs.h
.o/random_name.o: /usr/include/sys/_symbol_aliasing.h
.o/random_name.o: /usr/include/sys/_posix_availability.h
.o/random_name.o: /usr/include/Availability.h
.o/random_name.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/random_name.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/random_name.o: /usr/include/i386/_types.h
.o/random_name.o: /usr/include/sys/_pthread/_pthread_types.h
.o/random_name.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/random_name.o: /usr/include/sys/_types/_int8_t.h
.o/random_name.o: /usr/include/sys/_types/_int16_t.h
.o/random_name.o: /usr/include/sys/_types/_int32_t.h
.o/random_name.o: /usr/include/sys/_types/_int64_t.h
.o/random_name.o: /usr/include/_types/_uint8_t.h
.o/random_name.o: /usr/include/_types/_uint16_t.h
.o/random_name.o: /usr/include/_types/_uint32_t.h
.o/random_name.o: /usr/include/_types/_uint64_t.h
.o/random_name.o: /usr/include/sys/_types/_intptr_t.h
.o/random_name.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/random_name.o: /usr/include/sys/_types/_u_int8_t.h
.o/random_name.o: /usr/include/sys/_types/_u_int16_t.h
.o/random_name.o: /usr/include/sys/_types/_u_int32_t.h
.o/random_name.o: /usr/include/sys/_types/_u_int64_t.h
.o/random_name.o: /usr/include/sys/_types/_uintptr_t.h
.o/random_name.o: /usr/include/_types/_intmax_t.h
.o/random_name.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/random_name.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/random_name.o: /usr/include/assert.h my_vector_bounds_check.h
.o/random_name.o: c_plus_plus_serializer.h my_random_name.h
.o/room.o: my_room.h my_main.h my_sys.h my_pcg_basic.h
.o/room.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/room.o: /usr/include/sys/_symbol_aliasing.h
.o/room.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/room.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/room.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/room.o: /usr/include/i386/_types.h
.o/room.o: /usr/include/sys/_pthread/_pthread_types.h
.o/room.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/room.o: /usr/include/sys/_types/_int8_t.h
.o/room.o: /usr/include/sys/_types/_int16_t.h
.o/room.o: /usr/include/sys/_types/_int32_t.h
.o/room.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/room.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/room.o: /usr/include/_types/_uint64_t.h
.o/room.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/room.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/room.o: /usr/include/sys/_types/_u_int16_t.h
.o/room.o: /usr/include/sys/_types/_u_int32_t.h
.o/room.o: /usr/include/sys/_types/_u_int64_t.h
.o/room.o: /usr/include/sys/_types/_uintptr_t.h
.o/room.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/room.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/room.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/room.o: c_plus_plus_serializer.h my_point.h my_math.h /usr/include/math.h
.o/room.o: my_depth.h my_charmap.h my_range.h
.o/sdl.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/sdl.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/sdl.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/sdl.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/sdl.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/sdl.o: /usr/include/inttypes.h /usr/include/_types.h
.o/sdl.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/sdl.o: /usr/include/i386/_types.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sdl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/sdl.o: /usr/include/sys/_types/_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/sdl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sdl.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/sdl.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/sdl.o: /usr/include/sys/_types/_u_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int64_t.h
.o/sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/sdl.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/sdl.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/sdl.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/sdl.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/sdl.o: /usr/include/sys/_types/_mbstate_t.h
.o/sdl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/sdl.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/sdl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/sdl.o: /usr/include/secure/_common.h /usr/include/time.h
.o/sdl.o: /usr/include/sys/_types/_clock_t.h
.o/sdl.o: /usr/include/sys/_types/_time_t.h
.o/sdl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/sdl.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/sdl.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/sdl.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_particle.h
.o/sdl.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/sdl.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h my_gl.h
.o/sdl.o: my_color.h my_ascii.h my_tex.h my_tile.h my_thing.h my_light.h
.o/sdl.o: my_thing_template.h my_dice.h my_thing_ai.h my_player.h
.o/sdl.o: my_wid_console.h my_wid.h my_wid_tiles.h stb_image_write.h
.o/sdl.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/sdl.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/sdl.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/sdl.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/sdl.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/sdl.o: /usr/include/mach/machine/_structs.h
.o/sdl.o: /usr/include/mach/i386/_structs.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sdl.o: /usr/include/sys/_types/_sigaltstack.h
.o/sdl.o: /usr/include/sys/_types/_ucontext.h
.o/sdl.o: /usr/include/sys/_types/_sigset_t.h
.o/sdl.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/sdl.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/sdl.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/sdl.o: /usr/include/libkern/_OSByteOrder.h
.o/sdl.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/sdl.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/sdl.o: my_wid_rightbar.h
.o/sdl_screenshot.o: my_game.h my_world.h my_point.h my_math.h
.o/sdl_screenshot.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/sdl_screenshot.o: /usr/include/sys/_symbol_aliasing.h
.o/sdl_screenshot.o: /usr/include/sys/_posix_availability.h
.o/sdl_screenshot.o: /usr/include/Availability.h
.o/sdl_screenshot.o: /usr/include/AvailabilityInternal.h
.o/sdl_screenshot.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/sdl_screenshot.o: my_main.h my_sys.h my_pcg_basic.h
.o/sdl_screenshot.o: /usr/include/inttypes.h /usr/include/_types.h
.o/sdl_screenshot.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/sdl_screenshot.o: /usr/include/i386/_types.h
.o/sdl_screenshot.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_int8_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_int16_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_int32_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_int64_t.h
.o/sdl_screenshot.o: /usr/include/_types/_uint8_t.h
.o/sdl_screenshot.o: /usr/include/_types/_uint16_t.h
.o/sdl_screenshot.o: /usr/include/_types/_uint32_t.h
.o/sdl_screenshot.o: /usr/include/_types/_uint64_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_intptr_t.h
.o/sdl_screenshot.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_u_int8_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_u_int16_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_u_int32_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_u_int64_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_uintptr_t.h
.o/sdl_screenshot.o: /usr/include/_types/_intmax_t.h
.o/sdl_screenshot.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/sdl_screenshot.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/sdl_screenshot.o: my_bounds_check.h /usr/include/assert.h
.o/sdl_screenshot.o: my_vector_bounds_check.h my_command.h my_token.h
.o/sdl_screenshot.o: my_string.h /usr/include/wchar.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_null.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_size_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_mbstate_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/sdl_screenshot.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/sdl_screenshot.o: /usr/include/sys/stdio.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_off_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_ssize_t.h
.o/sdl_screenshot.o: /usr/include/secure/_stdio.h
.o/sdl_screenshot.o: /usr/include/secure/_common.h /usr/include/time.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_clock_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_time_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_timespec.h
.o/sdl_screenshot.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_wint_t.h
.o/sdl_screenshot.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/sdl_screenshot.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/sdl_screenshot.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/sdl_screenshot.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/sdl_screenshot.o: my_level_static.h my_dungeon_grid.h my_gl.h my_color.h
.o/sdl_screenshot.o: my_ascii.h my_tex.h my_tile.h my_thing.h my_light.h
.o/sdl_screenshot.o: my_thing_template.h my_dice.h my_thing_ai.h my_player.h
.o/sdl_screenshot.o: my_wid_console.h my_wid.h my_wid_tiles.h
.o/sdl_screenshot.o: stb_image_write.h /usr/include/stdlib.h
.o/sdl_screenshot.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_id_t.h
.o/sdl_screenshot.o: /usr/include/sys/signal.h
.o/sdl_screenshot.o: /usr/include/sys/appleapiopts.h
.o/sdl_screenshot.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/sdl_screenshot.o: /usr/include/machine/_mcontext.h
.o/sdl_screenshot.o: /usr/include/i386/_mcontext.h
.o/sdl_screenshot.o: /usr/include/mach/machine/_structs.h
.o/sdl_screenshot.o: /usr/include/mach/i386/_structs.h
.o/sdl_screenshot.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_sigaltstack.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_ucontext.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_sigset_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_uid_t.h
.o/sdl_screenshot.o: /usr/include/sys/resource.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_timeval.h
.o/sdl_screenshot.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/sdl_screenshot.o: /usr/include/sys/_endian.h
.o/sdl_screenshot.o: /usr/include/libkern/_OSByteOrder.h
.o/sdl_screenshot.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/sdl_screenshot.o: /usr/include/alloca.h /usr/include/sys/_types/_dev_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_mode_t.h
.o/signal.o: /usr/include/strings.h /usr/include/_types.h
.o/signal.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/signal.o: /usr/include/sys/_symbol_aliasing.h
.o/signal.o: /usr/include/sys/_posix_availability.h
.o/signal.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/signal.o: /usr/include/sys/_pthread/_pthread_types.h
.o/signal.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/signal.o: /usr/include/sys/_types/_size_t.h /usr/include/string.h
.o/signal.o: /usr/include/sys/_types/_null.h
.o/signal.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/signal.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/signal.o: /usr/include/sys/_types/_int16_t.h
.o/signal.o: /usr/include/sys/_types/_int32_t.h
.o/signal.o: /usr/include/sys/_types/_int64_t.h
.o/signal.o: /usr/include/sys/_types/_u_int8_t.h
.o/signal.o: /usr/include/sys/_types/_u_int16_t.h
.o/signal.o: /usr/include/sys/_types/_u_int32_t.h
.o/signal.o: /usr/include/sys/_types/_u_int64_t.h
.o/signal.o: /usr/include/sys/_types/_intptr_t.h
.o/signal.o: /usr/include/sys/_types/_uintptr_t.h
.o/signal.o: /usr/include/sys/_types/_errno_t.h
.o/signal.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_string.h
.o/signal.o: /usr/include/secure/_common.h /usr/include/secure/_strings.h
.o/signal.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/signal.o: /usr/include/sys/_types/_time_t.h
.o/signal.o: /usr/include/sys/_types/_timespec.h /usr/include/unistd.h
.o/signal.o: /usr/include/sys/unistd.h
.o/signal.o: /usr/include/sys/_types/_posix_vdisable.h
.o/signal.o: /usr/include/sys/_types/_seek_set.h
.o/signal.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_uint32_t.h
.o/signal.o: /usr/include/sys/_types/_uid_t.h
.o/signal.o: /usr/include/sys/_types/_gid_t.h
.o/signal.o: /usr/include/sys/_types/_off_t.h
.o/signal.o: /usr/include/sys/_types/_pid_t.h
.o/signal.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/signal.o: /usr/include/sys/appleapiopts.h
.o/signal.o: /usr/include/sys/_types/_fd_def.h
.o/signal.o: /usr/include/sys/_types/_timeval.h
.o/signal.o: /usr/include/sys/_types/_suseconds_t.h
.o/signal.o: /usr/include/sys/_types/_sigset_t.h
.o/signal.o: /usr/include/sys/_types/_fd_setsize.h
.o/signal.o: /usr/include/sys/_types/_fd_set.h
.o/signal.o: /usr/include/sys/_types/_fd_clr.h
.o/signal.o: /usr/include/sys/_types/_fd_isset.h
.o/signal.o: /usr/include/sys/_types/_fd_zero.h
.o/signal.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/signal.o: /usr/include/sys/_types/_dev_t.h
.o/signal.o: /usr/include/sys/_types/_mode_t.h
.o/signal.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/signal.o: /usr/include/signal.h /usr/include/sys/signal.h
.o/signal.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/signal.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/signal.o: /usr/include/mach/machine/_structs.h
.o/signal.o: /usr/include/mach/i386/_structs.h
.o/signal.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/signal.o: /usr/include/sys/_types/_sigaltstack.h
.o/signal.o: /usr/include/sys/_types/_ucontext.h
.o/signal.o: /usr/include/sys/_pthread/_pthread_t.h my_game.h my_world.h
.o/signal.o: my_point.h my_math.h /usr/include/math.h
.o/signal.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h my_main.h
.o/signal.o: my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/signal.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/signal.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/signal.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/signal.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/signal.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/signal.o: my_vector_bounds_check.h my_command.h my_token.h my_string.h
.o/signal.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/signal.o: /usr/include/sys/_types/_ct_rune_t.h
.o/signal.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/signal.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/signal.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/signal.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/signal.o: /usr/include/sys/_types/_wint_t.h
.o/signal.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/signal.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/signal.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/signal.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/signal.o: my_dungeon_grid.h /usr/include/stdlib.h /usr/include/sys/wait.h
.o/signal.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/resource.h
.o/signal.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/signal.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/signal.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/slre.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/slre.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/slre.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/slre.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/slre.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/slre.o: /usr/include/i386/_types.h
.o/slre.o: /usr/include/sys/_pthread/_pthread_types.h
.o/slre.o: /usr/include/sys/_types/_va_list.h /usr/include/machine/types.h
.o/slre.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/slre.o: /usr/include/sys/_types/_int16_t.h
.o/slre.o: /usr/include/sys/_types/_int32_t.h
.o/slre.o: /usr/include/sys/_types/_int64_t.h
.o/slre.o: /usr/include/sys/_types/_u_int8_t.h
.o/slre.o: /usr/include/sys/_types/_u_int16_t.h
.o/slre.o: /usr/include/sys/_types/_u_int32_t.h
.o/slre.o: /usr/include/sys/_types/_u_int64_t.h
.o/slre.o: /usr/include/sys/_types/_intptr_t.h
.o/slre.o: /usr/include/sys/_types/_uintptr_t.h
.o/slre.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/slre.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/slre.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/slre.o: /usr/include/secure/_common.h /usr/include/assert.h
.o/slre.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/slre.o: /usr/include/sys/_types/_ct_rune_t.h
.o/slre.o: /usr/include/sys/_types/_rune_t.h
.o/slre.o: /usr/include/sys/_types/_wchar_t.h
.o/slre.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/slre.o: /usr/include/sys/_types/_rsize_t.h
.o/slre.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/slre.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/slre.o: slre.h
.o/sprintf.o: my_sprintf.h /usr/include/stdio.h /usr/include/_stdio.h
.o/sprintf.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/sprintf.o: /usr/include/sys/_posix_availability.h
.o/sprintf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/sprintf.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/sprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/sprintf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sprintf.o: /usr/include/sys/_types/_va_list.h /usr/include/machine/types.h
.o/sprintf.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/sprintf.o: /usr/include/sys/_types/_int16_t.h
.o/sprintf.o: /usr/include/sys/_types/_int32_t.h
.o/sprintf.o: /usr/include/sys/_types/_int64_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int8_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int16_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int32_t.h
.o/sprintf.o: /usr/include/sys/_types/_u_int64_t.h
.o/sprintf.o: /usr/include/sys/_types/_intptr_t.h
.o/sprintf.o: /usr/include/sys/_types/_uintptr_t.h
.o/sprintf.o: /usr/include/sys/_types/_size_t.h
.o/sprintf.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/sprintf.o: /usr/include/sys/_types/_off_t.h
.o/sprintf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/sprintf.o: /usr/include/secure/_common.h /usr/include/stdlib.h
.o/sprintf.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/sprintf.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/sprintf.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/sprintf.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/sprintf.o: /usr/include/i386/_mcontext.h
.o/sprintf.o: /usr/include/mach/machine/_structs.h
.o/sprintf.o: /usr/include/mach/i386/_structs.h
.o/sprintf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sprintf.o: /usr/include/sys/_types/_sigaltstack.h
.o/sprintf.o: /usr/include/sys/_types/_ucontext.h
.o/sprintf.o: /usr/include/sys/_types/_sigset_t.h
.o/sprintf.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/sprintf.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/sprintf.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sprintf.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/sprintf.o: /usr/include/_types/_uintmax_t.h
.o/sprintf.o: /usr/include/sys/_types/_timeval.h
.o/sprintf.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/sprintf.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/sprintf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/sprintf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sprintf.o: /usr/include/sys/_types/_rune_t.h
.o/sprintf.o: /usr/include/sys/_types/_wchar_t.h
.o/sprintf.o: /usr/include/sys/_types/_dev_t.h
.o/sprintf.o: /usr/include/sys/_types/_mode_t.h
.o/stb_image.o: stb_image.h /usr/include/stdio.h /usr/include/_stdio.h
.o/stb_image.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/stb_image.o: /usr/include/sys/_posix_availability.h
.o/stb_image.o: /usr/include/Availability.h
.o/stb_image.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/stb_image.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/stb_image.o: /usr/include/i386/_types.h
.o/stb_image.o: /usr/include/sys/_pthread/_pthread_types.h
.o/stb_image.o: /usr/include/sys/_types/_va_list.h
.o/stb_image.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/stb_image.o: /usr/include/sys/_types/_int8_t.h
.o/stb_image.o: /usr/include/sys/_types/_int16_t.h
.o/stb_image.o: /usr/include/sys/_types/_int32_t.h
.o/stb_image.o: /usr/include/sys/_types/_int64_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int8_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int16_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int32_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int64_t.h
.o/stb_image.o: /usr/include/sys/_types/_intptr_t.h
.o/stb_image.o: /usr/include/sys/_types/_uintptr_t.h
.o/stb_image.o: /usr/include/sys/_types/_size_t.h
.o/stb_image.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/stb_image.o: /usr/include/sys/_types/_off_t.h
.o/stb_image.o: /usr/include/sys/_types/_ssize_t.h
.o/stb_image.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/stb_image.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/stb_image.o: /usr/include/sys/_types/_pid_t.h
.o/stb_image.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/stb_image.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/stb_image.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/stb_image.o: /usr/include/i386/_mcontext.h
.o/stb_image.o: /usr/include/mach/machine/_structs.h
.o/stb_image.o: /usr/include/mach/i386/_structs.h
.o/stb_image.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/stb_image.o: /usr/include/sys/_types/_sigaltstack.h
.o/stb_image.o: /usr/include/sys/_types/_ucontext.h
.o/stb_image.o: /usr/include/sys/_types/_sigset_t.h
.o/stb_image.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/stb_image.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/stb_image.o: /usr/include/_types/_uint16_t.h
.o/stb_image.o: /usr/include/_types/_uint32_t.h
.o/stb_image.o: /usr/include/_types/_uint64_t.h
.o/stb_image.o: /usr/include/_types/_intmax_t.h
.o/stb_image.o: /usr/include/_types/_uintmax_t.h
.o/stb_image.o: /usr/include/sys/_types/_timeval.h
.o/stb_image.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/stb_image.o: /usr/include/sys/_endian.h
.o/stb_image.o: /usr/include/libkern/_OSByteOrder.h
.o/stb_image.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/stb_image.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/stb_image.o: /usr/include/sys/_types/_rune_t.h
.o/stb_image.o: /usr/include/sys/_types/_wchar_t.h
.o/stb_image.o: /usr/include/sys/_types/_dev_t.h
.o/stb_image.o: /usr/include/sys/_types/_mode_t.h /usr/include/stddef.h
.o/stb_image.o: /usr/include/sys/_types/_offsetof.h
.o/stb_image.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/stb_image.o: /usr/include/sys/_types/_rsize_t.h
.o/stb_image.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/stb_image.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/stb_image.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/stb_image.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/stb_image.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/stb_image.o: /usr/include/sys/syslimits.h /usr/include/math.h
.o/stb_image.o: /usr/include/assert.h stb_image_write.h
.o/string.o: /usr/include/libgen.h /usr/include/sys/cdefs.h
.o/string.o: /usr/include/sys/_symbol_aliasing.h
.o/string.o: /usr/include/sys/_posix_availability.h
.o/string.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/string.o: /usr/include/time.h /usr/include/_types.h
.o/string.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/string.o: /usr/include/i386/_types.h
.o/string.o: /usr/include/sys/_pthread/_pthread_types.h
.o/string.o: /usr/include/sys/_types/_clock_t.h /usr/include/machine/types.h
.o/string.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/string.o: /usr/include/sys/_types/_int16_t.h
.o/string.o: /usr/include/sys/_types/_int32_t.h
.o/string.o: /usr/include/sys/_types/_int64_t.h
.o/string.o: /usr/include/sys/_types/_u_int8_t.h
.o/string.o: /usr/include/sys/_types/_u_int16_t.h
.o/string.o: /usr/include/sys/_types/_u_int32_t.h
.o/string.o: /usr/include/sys/_types/_u_int64_t.h
.o/string.o: /usr/include/sys/_types/_intptr_t.h
.o/string.o: /usr/include/sys/_types/_uintptr_t.h
.o/string.o: /usr/include/sys/_types/_null.h
.o/string.o: /usr/include/sys/_types/_size_t.h
.o/string.o: /usr/include/sys/_types/_time_t.h
.o/string.o: /usr/include/sys/_types/_timespec.h my_main.h my_sys.h
.o/string.o: my_pcg_basic.h /usr/include/inttypes.h
.o/string.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/string.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/string.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/string.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/string.o: my_ptrcheck.h my_globals.h my_callstack.h
.o/string.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/string.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_sdl.h
.o/string.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/string.o: /usr/include/sys/_types/_mbstate_t.h
.o/string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/string.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/string.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/string.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/string.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/string.o: /usr/include/secure/_common.h /usr/include/_wctype.h
.o/string.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/string.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/string.o: my_thing_template.h my_dice.h my_tile.h my_point.h my_math.h
.o/string.o: /usr/include/math.h my_color.h my_size.h my_tex.h my_time.h
.o/tex.o: stb_image.h /usr/include/stdio.h /usr/include/_stdio.h
.o/tex.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/tex.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/tex.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/tex.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/tex.o: /usr/include/i386/_types.h
.o/tex.o: /usr/include/sys/_pthread/_pthread_types.h
.o/tex.o: /usr/include/sys/_types/_va_list.h /usr/include/machine/types.h
.o/tex.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/tex.o: /usr/include/sys/_types/_int16_t.h
.o/tex.o: /usr/include/sys/_types/_int32_t.h
.o/tex.o: /usr/include/sys/_types/_int64_t.h
.o/tex.o: /usr/include/sys/_types/_u_int8_t.h
.o/tex.o: /usr/include/sys/_types/_u_int16_t.h
.o/tex.o: /usr/include/sys/_types/_u_int32_t.h
.o/tex.o: /usr/include/sys/_types/_u_int64_t.h
.o/tex.o: /usr/include/sys/_types/_intptr_t.h
.o/tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/tex.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/tex.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tex.o: /usr/include/secure/_common.h /usr/include/stdlib.h
.o/tex.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/tex.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/tex.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/tex.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/tex.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/tex.o: /usr/include/mach/i386/_structs.h
.o/tex.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/tex.o: /usr/include/sys/_types/_sigaltstack.h
.o/tex.o: /usr/include/sys/_types/_ucontext.h
.o/tex.o: /usr/include/sys/_types/_sigset_t.h
.o/tex.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/tex.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/tex.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tex.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/tex.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
.o/tex.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/tex.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/tex.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/tex.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tex.o: /usr/include/sys/_types/_rune_t.h
.o/tex.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_dev_t.h
.o/tex.o: /usr/include/sys/_types/_mode_t.h /usr/include/stddef.h
.o/tex.o: /usr/include/sys/_types/_offsetof.h
.o/tex.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/tex.o: /usr/include/sys/_types/_rsize_t.h
.o/tex.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/tex.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/tex.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/tex.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/tex.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/tex.o: /usr/include/sys/syslimits.h /usr/include/math.h
.o/tex.o: /usr/include/assert.h my_main.h my_sys.h my_pcg_basic.h
.o/tex.o: /usr/include/inttypes.h my_ptrcheck.h my_globals.h my_callstack.h
.o/tex.o: my_array_bounds_check.h my_bounds_check.h my_vector_bounds_check.h
.o/tex.o: c_plus_plus_serializer.h my_gl.h my_color.h my_point.h my_math.h
.o/tex.o: my_size.h my_tex.h my_ramdisk.h my_pixel.h my_string.h
.o/tex.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/tex.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/tex.o: /usr/include/sys/_types/_time_t.h
.o/tex.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tex.o: /usr/include/__wctype.h /usr/include/_types/_wctype_t.h
.o/tex.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/thing_acid.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_acid.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_acid.o: /usr/include/sys/_posix_availability.h
.o/thing_acid.o: /usr/include/Availability.h
.o/thing_acid.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_acid.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_acid.o: /usr/include/i386/_types.h
.o/thing_acid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_acid.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_acid.o: /usr/include/sys/_types/_int8_t.h
.o/thing_acid.o: /usr/include/sys/_types/_int16_t.h
.o/thing_acid.o: /usr/include/sys/_types/_int32_t.h
.o/thing_acid.o: /usr/include/sys/_types/_int64_t.h
.o/thing_acid.o: /usr/include/_types/_uint8_t.h
.o/thing_acid.o: /usr/include/_types/_uint16_t.h
.o/thing_acid.o: /usr/include/_types/_uint32_t.h
.o/thing_acid.o: /usr/include/_types/_uint64_t.h
.o/thing_acid.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_acid.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_acid.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_acid.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_acid.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_acid.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_acid.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_acid.o: /usr/include/_types/_intmax_t.h
.o/thing_acid.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_acid.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_acid.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_acid.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_acid.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_acid.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_acid.o: /usr/include/sys/_types/_null.h
.o/thing_acid.o: /usr/include/sys/_types/_size_t.h
.o/thing_acid.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_acid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_acid.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_acid.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_acid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_acid.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_acid.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_acid.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_acid.o: /usr/include/sys/_types/_time_t.h
.o/thing_acid.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_acid.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_acid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_acid.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_acid.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_acid.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_acid.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_acid.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_ai.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_ai.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_ai.o: /usr/include/sys/_posix_availability.h
.o/thing_ai.o: /usr/include/Availability.h
.o/thing_ai.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_ai.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_ai.o: /usr/include/i386/_types.h
.o/thing_ai.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_ai.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_ai.o: /usr/include/sys/_types/_int8_t.h
.o/thing_ai.o: /usr/include/sys/_types/_int16_t.h
.o/thing_ai.o: /usr/include/sys/_types/_int32_t.h
.o/thing_ai.o: /usr/include/sys/_types/_int64_t.h
.o/thing_ai.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/thing_ai.o: /usr/include/_types/_uint32_t.h
.o/thing_ai.o: /usr/include/_types/_uint64_t.h
.o/thing_ai.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_ai.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_ai.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_ai.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_ai.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_ai.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_ai.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_ai.o: /usr/include/_types/_intmax_t.h
.o/thing_ai.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_ai.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_ai.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_ai.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_ai.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_ai.o: /usr/include/sys/_types/_null.h
.o/thing_ai.o: /usr/include/sys/_types/_size_t.h
.o/thing_ai.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_ai.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_ai.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_ai.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_ai.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_ai.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_ai.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_ai.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_ai.o: /usr/include/sys/_types/_time_t.h
.o/thing_ai.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_ai.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_ai.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_ai.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_ai.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_ai.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_ai.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_ai.o: my_thing.h my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_ai.o: my_color.h my_thing_ai.h
.o/thing_ai_goals.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_ai_goals.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_ai_goals.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_ai_goals.o: /usr/include/sys/_posix_availability.h
.o/thing_ai_goals.o: /usr/include/Availability.h
.o/thing_ai_goals.o: /usr/include/AvailabilityInternal.h
.o/thing_ai_goals.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_ai_goals.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_ai_goals.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_int8_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_int16_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_int32_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_int64_t.h
.o/thing_ai_goals.o: /usr/include/_types/_uint8_t.h
.o/thing_ai_goals.o: /usr/include/_types/_uint16_t.h
.o/thing_ai_goals.o: /usr/include/_types/_uint32_t.h
.o/thing_ai_goals.o: /usr/include/_types/_uint64_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_ai_goals.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_ai_goals.o: /usr/include/_types/_intmax_t.h
.o/thing_ai_goals.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_ai_goals.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_ai_goals.o: my_bounds_check.h /usr/include/assert.h
.o/thing_ai_goals.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_ai_goals.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_ai_goals.o: my_string.h /usr/include/wchar.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_null.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_size_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_ai_goals.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_ai_goals.o: /usr/include/sys/stdio.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_off_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_ai_goals.o: /usr/include/secure/_stdio.h
.o/thing_ai_goals.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_clock_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_time_t.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_timespec.h
.o/thing_ai_goals.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_ai_goals.o: /usr/include/sys/_types/_wint_t.h
.o/thing_ai_goals.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_ai_goals.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_ai_goals.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_ai_goals.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_ai_goals.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_ai_goals.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_ai_goals.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_ai_goals.o: my_thing_ai.h
.o/thing_ai_wander.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_ai_wander.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_ai_wander.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_ai_wander.o: /usr/include/sys/_posix_availability.h
.o/thing_ai_wander.o: /usr/include/Availability.h
.o/thing_ai_wander.o: /usr/include/AvailabilityInternal.h
.o/thing_ai_wander.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_ai_wander.o: /usr/include/machine/_types.h
.o/thing_ai_wander.o: /usr/include/i386/_types.h
.o/thing_ai_wander.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_ai_wander.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_int16_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_int32_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_int64_t.h
.o/thing_ai_wander.o: /usr/include/_types/_uint8_t.h
.o/thing_ai_wander.o: /usr/include/_types/_uint16_t.h
.o/thing_ai_wander.o: /usr/include/_types/_uint32_t.h
.o/thing_ai_wander.o: /usr/include/_types/_uint64_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_ai_wander.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_ai_wander.o: /usr/include/_types/_intmax_t.h
.o/thing_ai_wander.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_ai_wander.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_ai_wander.o: my_bounds_check.h /usr/include/assert.h
.o/thing_ai_wander.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_ai_wander.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_ai_wander.o: my_string.h /usr/include/wchar.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_null.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_size_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_ai_wander.o: /usr/include/_stdio.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_va_list.h
.o/thing_ai_wander.o: /usr/include/sys/stdio.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_off_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_ai_wander.o: /usr/include/secure/_stdio.h
.o/thing_ai_wander.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_clock_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_time_t.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_timespec.h
.o/thing_ai_wander.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_ai_wander.o: /usr/include/sys/_types/_wint_t.h
.o/thing_ai_wander.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_ai_wander.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_ai_wander.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_ai_wander.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_ai_wander.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_ai_wander.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_ai_wander.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_ai_wander.o: my_thing_ai.h my_game.h my_world.h
.o/thing_anim.o: my_thing.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_anim.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_anim.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_anim.o: /usr/include/sys/_posix_availability.h
.o/thing_anim.o: /usr/include/Availability.h
.o/thing_anim.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_anim.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_anim.o: /usr/include/i386/_types.h
.o/thing_anim.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_anim.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_anim.o: /usr/include/sys/_types/_int8_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int16_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int32_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int64_t.h
.o/thing_anim.o: /usr/include/_types/_uint8_t.h
.o/thing_anim.o: /usr/include/_types/_uint16_t.h
.o/thing_anim.o: /usr/include/_types/_uint32_t.h
.o/thing_anim.o: /usr/include/_types/_uint64_t.h
.o/thing_anim.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_anim.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_anim.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_anim.o: /usr/include/_types/_intmax_t.h
.o/thing_anim.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_anim.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_anim.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_anim.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/thing_anim.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_anim.o: /usr/include/sys/_types/_size_t.h
.o/thing_anim.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_anim.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_anim.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_anim.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_anim.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_anim.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_anim.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_anim.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_anim.o: /usr/include/sys/_types/_time_t.h
.o/thing_anim.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_anim.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_anim.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_anim.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_anim.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_anim.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_anim.o: my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_api.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_api.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_api.o: /usr/include/sys/_posix_availability.h
.o/thing_api.o: /usr/include/Availability.h
.o/thing_api.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_api.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_api.o: /usr/include/i386/_types.h
.o/thing_api.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_api.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_api.o: /usr/include/sys/_types/_int8_t.h
.o/thing_api.o: /usr/include/sys/_types/_int16_t.h
.o/thing_api.o: /usr/include/sys/_types/_int32_t.h
.o/thing_api.o: /usr/include/sys/_types/_int64_t.h
.o/thing_api.o: /usr/include/_types/_uint8_t.h
.o/thing_api.o: /usr/include/_types/_uint16_t.h
.o/thing_api.o: /usr/include/_types/_uint32_t.h
.o/thing_api.o: /usr/include/_types/_uint64_t.h
.o/thing_api.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_api.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_api.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_api.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_api.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_api.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_api.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_api.o: /usr/include/_types/_intmax_t.h
.o/thing_api.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_api.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_api.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_api.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_api.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_api.o: /usr/include/sys/_types/_null.h
.o/thing_api.o: /usr/include/sys/_types/_size_t.h
.o/thing_api.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_api.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_api.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_api.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_api.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_api.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_api.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_api.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_api.o: /usr/include/sys/_types/_time_t.h
.o/thing_api.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_api.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_api.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_api.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_api.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_api.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_api.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_api.o: my_color.h my_wid_rightbar.h my_wid.h my_ascii.h my_tex.h
.o/thing_api.o: my_tile.h my_wid_tiles.h my_thing.h my_light.h
.o/thing_api.o: my_thing_template.h my_dice.h my_thing_ai.h my_game.h
.o/thing_api.o: my_world.h
.o/thing_astar.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_astar.o: /usr/include/sys/cdefs.h
.o/thing_astar.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_astar.o: /usr/include/sys/_posix_availability.h
.o/thing_astar.o: /usr/include/Availability.h
.o/thing_astar.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_astar.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_astar.o: /usr/include/i386/_types.h
.o/thing_astar.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_astar.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_astar.o: /usr/include/sys/_types/_int8_t.h
.o/thing_astar.o: /usr/include/sys/_types/_int16_t.h
.o/thing_astar.o: /usr/include/sys/_types/_int32_t.h
.o/thing_astar.o: /usr/include/sys/_types/_int64_t.h
.o/thing_astar.o: /usr/include/_types/_uint8_t.h
.o/thing_astar.o: /usr/include/_types/_uint16_t.h
.o/thing_astar.o: /usr/include/_types/_uint32_t.h
.o/thing_astar.o: /usr/include/_types/_uint64_t.h
.o/thing_astar.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_astar.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_astar.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_astar.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_astar.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_astar.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_astar.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_astar.o: /usr/include/_types/_intmax_t.h
.o/thing_astar.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_astar.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_astar.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_astar.o: c_plus_plus_serializer.h my_dmap.h my_point.h my_math.h
.o/thing_astar.o: /usr/include/math.h my_sprintf.h my_thing.h my_time.h
.o/thing_astar.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_astar.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_astar.o: /usr/include/sys/_types/_size_t.h
.o/thing_astar.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_astar.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_astar.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_astar.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_astar.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_astar.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_astar.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_astar.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_astar.o: /usr/include/sys/_types/_time_t.h
.o/thing_astar.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_astar.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_astar.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_astar.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_astar.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_astar.o: my_color.h my_size.h my_thing_ai.h my_thing_id.h
.o/thing_attack.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_attack.o: /usr/include/sys/cdefs.h
.o/thing_attack.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_attack.o: /usr/include/sys/_posix_availability.h
.o/thing_attack.o: /usr/include/Availability.h
.o/thing_attack.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_attack.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_attack.o: /usr/include/i386/_types.h
.o/thing_attack.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_attack.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_attack.o: /usr/include/sys/_types/_int8_t.h
.o/thing_attack.o: /usr/include/sys/_types/_int16_t.h
.o/thing_attack.o: /usr/include/sys/_types/_int32_t.h
.o/thing_attack.o: /usr/include/sys/_types/_int64_t.h
.o/thing_attack.o: /usr/include/_types/_uint8_t.h
.o/thing_attack.o: /usr/include/_types/_uint16_t.h
.o/thing_attack.o: /usr/include/_types/_uint32_t.h
.o/thing_attack.o: /usr/include/_types/_uint64_t.h
.o/thing_attack.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_attack.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_attack.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_attack.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_attack.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_attack.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_attack.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_attack.o: /usr/include/_types/_intmax_t.h
.o/thing_attack.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_attack.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_attack.o: my_bounds_check.h /usr/include/assert.h
.o/thing_attack.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_attack.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_attack.o: my_string.h /usr/include/wchar.h
.o/thing_attack.o: /usr/include/sys/_types/_null.h
.o/thing_attack.o: /usr/include/sys/_types/_size_t.h
.o/thing_attack.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_attack.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_attack.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_attack.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_attack.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_attack.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_attack.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_attack.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_attack.o: /usr/include/sys/_types/_time_t.h
.o/thing_attack.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_attack.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_attack.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_attack.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_attack.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_attack.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_attack.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_attack.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_attack.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_avoid.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_avoid.o: /usr/include/sys/cdefs.h
.o/thing_avoid.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_avoid.o: /usr/include/sys/_posix_availability.h
.o/thing_avoid.o: /usr/include/Availability.h
.o/thing_avoid.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_avoid.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_avoid.o: /usr/include/i386/_types.h
.o/thing_avoid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_avoid.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_avoid.o: /usr/include/sys/_types/_int8_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_int16_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_int32_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_int64_t.h
.o/thing_avoid.o: /usr/include/_types/_uint8_t.h
.o/thing_avoid.o: /usr/include/_types/_uint16_t.h
.o/thing_avoid.o: /usr/include/_types/_uint32_t.h
.o/thing_avoid.o: /usr/include/_types/_uint64_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_avoid.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_avoid.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_avoid.o: /usr/include/_types/_intmax_t.h
.o/thing_avoid.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_avoid.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_avoid.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_avoid.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_avoid.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_avoid.o: /usr/include/sys/_types/_null.h
.o/thing_avoid.o: /usr/include/sys/_types/_size_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_avoid.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_avoid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_avoid.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_avoid.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_time_t.h
.o/thing_avoid.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_avoid.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_avoid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_avoid.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_avoid.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_avoid.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_avoid.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_avoid.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_avoid.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_bag.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_bag.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_bag.o: /usr/include/sys/_posix_availability.h
.o/thing_bag.o: /usr/include/Availability.h
.o/thing_bag.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_bag.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_bag.o: /usr/include/i386/_types.h
.o/thing_bag.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_bag.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_bag.o: /usr/include/sys/_types/_int8_t.h
.o/thing_bag.o: /usr/include/sys/_types/_int16_t.h
.o/thing_bag.o: /usr/include/sys/_types/_int32_t.h
.o/thing_bag.o: /usr/include/sys/_types/_int64_t.h
.o/thing_bag.o: /usr/include/_types/_uint8_t.h
.o/thing_bag.o: /usr/include/_types/_uint16_t.h
.o/thing_bag.o: /usr/include/_types/_uint32_t.h
.o/thing_bag.o: /usr/include/_types/_uint64_t.h
.o/thing_bag.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_bag.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_bag.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_bag.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_bag.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_bag.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_bag.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_bag.o: /usr/include/_types/_intmax_t.h
.o/thing_bag.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_bag.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_bag.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_bag.o: c_plus_plus_serializer.h my_sdl.h my_command.h my_token.h
.o/thing_bag.o: my_string.h /usr/include/wchar.h
.o/thing_bag.o: /usr/include/sys/_types/_null.h
.o/thing_bag.o: /usr/include/sys/_types/_size_t.h
.o/thing_bag.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_bag.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_bag.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_bag.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_bag.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_bag.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_bag.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_bag.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_bag.o: /usr/include/sys/_types/_time_t.h
.o/thing_bag.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_bag.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_bag.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_bag.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_bag.o: my_wid_bag.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/thing_bag.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_bag.o: my_wid_tiles.h my_thing.h my_time.h my_light.h
.o/thing_bag.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/thing_bag.o: my_dmap.h my_thing_id.h my_ttf.h my_font.h my_wid_popup.h
.o/thing_bag.o: my_wid_text_box.h my_game.h my_world.h my_level.h
.o/thing_bag.o: my_particle.h my_dungeon.h my_room.h my_depth.h my_charmap.h
.o/thing_bag.o: my_level_static.h my_dungeon_grid.h
.o/thing_bounce.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_bounce.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_bounce.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_bounce.o: /usr/include/sys/_posix_availability.h
.o/thing_bounce.o: /usr/include/Availability.h
.o/thing_bounce.o: /usr/include/AvailabilityInternal.h
.o/thing_bounce.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_bounce.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_bounce.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_bounce.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_bounce.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_bounce.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_bounce.o: /usr/include/sys/_types/_int8_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_int16_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_int32_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_int64_t.h
.o/thing_bounce.o: /usr/include/_types/_uint8_t.h
.o/thing_bounce.o: /usr/include/_types/_uint16_t.h
.o/thing_bounce.o: /usr/include/_types/_uint32_t.h
.o/thing_bounce.o: /usr/include/_types/_uint64_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_bounce.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_bounce.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_bounce.o: /usr/include/_types/_intmax_t.h
.o/thing_bounce.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_bounce.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_bounce.o: my_bounds_check.h /usr/include/assert.h
.o/thing_bounce.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_bounce.o: my_string.h /usr/include/wchar.h
.o/thing_bounce.o: /usr/include/sys/_types/_null.h
.o/thing_bounce.o: /usr/include/sys/_types/_size_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_bounce.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_bounce.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_bounce.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_bounce.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_time_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_bounce.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_bounce.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_bounce.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_bounce.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_bounce.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_bounce.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/thing_bounce.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_bounce.o: my_thing_ai.h my_sprintf.h my_gl.h
.o/thing_carry.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_carry.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_carry.o: /usr/include/sys/cdefs.h
.o/thing_carry.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_carry.o: /usr/include/sys/_posix_availability.h
.o/thing_carry.o: /usr/include/Availability.h
.o/thing_carry.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_carry.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_carry.o: /usr/include/i386/_types.h
.o/thing_carry.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_carry.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_carry.o: /usr/include/sys/_types/_int8_t.h
.o/thing_carry.o: /usr/include/sys/_types/_int16_t.h
.o/thing_carry.o: /usr/include/sys/_types/_int32_t.h
.o/thing_carry.o: /usr/include/sys/_types/_int64_t.h
.o/thing_carry.o: /usr/include/_types/_uint8_t.h
.o/thing_carry.o: /usr/include/_types/_uint16_t.h
.o/thing_carry.o: /usr/include/_types/_uint32_t.h
.o/thing_carry.o: /usr/include/_types/_uint64_t.h
.o/thing_carry.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_carry.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_carry.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_carry.o: /usr/include/_types/_intmax_t.h
.o/thing_carry.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_carry.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_carry.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_carry.o: c_plus_plus_serializer.h my_command.h my_token.h
.o/thing_carry.o: my_string.h /usr/include/wchar.h
.o/thing_carry.o: /usr/include/sys/_types/_null.h
.o/thing_carry.o: /usr/include/sys/_types/_size_t.h
.o/thing_carry.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_carry.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_carry.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_carry.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_carry.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_carry.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_carry.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_carry.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_carry.o: /usr/include/sys/_types/_time_t.h
.o/thing_carry.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_carry.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_carry.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_carry.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_carry.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_carry.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_carry.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_carry.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_carry.o: my_tile.h my_color.h my_thing_ai.h my_game.h my_world.h
.o/thing_carry.o: my_wid_inventory.h my_wid.h my_ascii.h my_tex.h
.o/thing_carry.o: my_wid_tiles.h
.o/thing_chasm.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_chasm.o: /usr/include/sys/cdefs.h
.o/thing_chasm.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_chasm.o: /usr/include/sys/_posix_availability.h
.o/thing_chasm.o: /usr/include/Availability.h
.o/thing_chasm.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_chasm.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_chasm.o: /usr/include/i386/_types.h
.o/thing_chasm.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_chasm.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_chasm.o: /usr/include/sys/_types/_int8_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_int16_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_int32_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_int64_t.h
.o/thing_chasm.o: /usr/include/_types/_uint8_t.h
.o/thing_chasm.o: /usr/include/_types/_uint16_t.h
.o/thing_chasm.o: /usr/include/_types/_uint32_t.h
.o/thing_chasm.o: /usr/include/_types/_uint64_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_chasm.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_chasm.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_chasm.o: /usr/include/_types/_intmax_t.h
.o/thing_chasm.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_chasm.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_chasm.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_chasm.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_chasm.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_chasm.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_chasm.o: /usr/include/sys/_types/_null.h
.o/thing_chasm.o: /usr/include/sys/_types/_size_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_chasm.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_chasm.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_chasm.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_chasm.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_time_t.h
.o/thing_chasm.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_chasm.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_chasm.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_chasm.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_chasm.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_chasm.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_chasm.o: my_level_static.h my_dungeon_grid.h my_color.h my_sprintf.h
.o/thing_chasm.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_chasm.o: my_tile.h my_thing_ai.h
.o/thing_collision.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_collision.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_collision.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_collision.o: /usr/include/sys/_posix_availability.h
.o/thing_collision.o: /usr/include/Availability.h
.o/thing_collision.o: /usr/include/AvailabilityInternal.h
.o/thing_collision.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_collision.o: /usr/include/machine/_types.h
.o/thing_collision.o: /usr/include/i386/_types.h
.o/thing_collision.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_collision.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_collision.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_collision.o: /usr/include/sys/_types/_int16_t.h
.o/thing_collision.o: /usr/include/sys/_types/_int32_t.h
.o/thing_collision.o: /usr/include/sys/_types/_int64_t.h
.o/thing_collision.o: /usr/include/_types/_uint8_t.h
.o/thing_collision.o: /usr/include/_types/_uint16_t.h
.o/thing_collision.o: /usr/include/_types/_uint32_t.h
.o/thing_collision.o: /usr/include/_types/_uint64_t.h
.o/thing_collision.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_collision.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_collision.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_collision.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_collision.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_collision.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_collision.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_collision.o: /usr/include/_types/_intmax_t.h
.o/thing_collision.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_collision.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_collision.o: my_bounds_check.h /usr/include/assert.h
.o/thing_collision.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_collision.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/thing_collision.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_collision.o: /usr/include/sys/_types/_size_t.h
.o/thing_collision.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_collision.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_collision.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_collision.o: /usr/include/_stdio.h
.o/thing_collision.o: /usr/include/sys/_types/_va_list.h
.o/thing_collision.o: /usr/include/sys/stdio.h
.o/thing_collision.o: /usr/include/sys/_types/_off_t.h
.o/thing_collision.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_collision.o: /usr/include/secure/_stdio.h
.o/thing_collision.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_collision.o: /usr/include/sys/_types/_clock_t.h
.o/thing_collision.o: /usr/include/sys/_types/_time_t.h
.o/thing_collision.o: /usr/include/sys/_types/_timespec.h
.o/thing_collision.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_collision.o: /usr/include/sys/_types/_wint_t.h
.o/thing_collision.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_collision.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_collision.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_collision.o: my_game.h my_world.h my_level.h my_time.h my_particle.h
.o/thing_collision.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_collision.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_collision.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_collision.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_cursor.o: my_ascii.h /usr/include/wchar.h /usr/include/_types.h
.o/thing_cursor.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/thing_cursor.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_cursor.o: /usr/include/sys/_posix_availability.h
.o/thing_cursor.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_cursor.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_cursor.o: /usr/include/Availability.h
.o/thing_cursor.o: /usr/include/AvailabilityInternal.h
.o/thing_cursor.o: /usr/include/sys/_types/_null.h
.o/thing_cursor.o: /usr/include/sys/_types/_size_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_cursor.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_cursor.o: /usr/include/sys/_types/_int8_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_int16_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_int32_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_int64_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_rune_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/thing_cursor.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_cursor.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_cursor.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_cursor.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_time_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_cursor.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_cursor.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_cursor.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h
.o/thing_cursor.o: my_tile.h my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/thing_cursor.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/thing_cursor.o: /usr/include/_types/_uint8_t.h
.o/thing_cursor.o: /usr/include/_types/_uint16_t.h
.o/thing_cursor.o: /usr/include/_types/_uint32_t.h
.o/thing_cursor.o: /usr/include/_types/_uint64_t.h
.o/thing_cursor.o: /usr/include/_types/_intmax_t.h
.o/thing_cursor.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_cursor.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_cursor.o: my_bounds_check.h /usr/include/assert.h
.o/thing_cursor.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_cursor.o: my_command.h my_token.h my_string.h slre.h my_point.h
.o/thing_cursor.o: my_math.h /usr/include/math.h my_color.h my_depth.h
.o/thing_cursor.o: my_dmap.h my_game.h my_world.h my_level.h my_time.h
.o/thing_cursor.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_cursor.o: my_room.h my_charmap.h my_level_static.h my_dungeon_grid.h
.o/thing_cursor.o: my_wid_inventory.h my_wid.h my_wid_tiles.h my_thing.h
.o/thing_cursor.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_cursor.o: my_wid_console.h my_wid_bag.h
.o/thing_cursor_path.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_cursor_path.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_cursor_path.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_cursor_path.o: /usr/include/sys/_posix_availability.h
.o/thing_cursor_path.o: /usr/include/Availability.h
.o/thing_cursor_path.o: /usr/include/AvailabilityInternal.h
.o/thing_cursor_path.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_cursor_path.o: /usr/include/machine/_types.h
.o/thing_cursor_path.o: /usr/include/i386/_types.h
.o/thing_cursor_path.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_cursor_path.o: /usr/include/stdint.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_int8_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_int16_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_int32_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_int64_t.h
.o/thing_cursor_path.o: /usr/include/_types/_uint8_t.h
.o/thing_cursor_path.o: /usr/include/_types/_uint16_t.h
.o/thing_cursor_path.o: /usr/include/_types/_uint32_t.h
.o/thing_cursor_path.o: /usr/include/_types/_uint64_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_cursor_path.o: /usr/include/machine/types.h
.o/thing_cursor_path.o: /usr/include/i386/types.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_cursor_path.o: /usr/include/_types/_intmax_t.h
.o/thing_cursor_path.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_cursor_path.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_cursor_path.o: my_bounds_check.h /usr/include/assert.h
.o/thing_cursor_path.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_cursor_path.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_cursor_path.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_cursor_path.o: my_command.h my_token.h my_string.h
.o/thing_cursor_path.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_size_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_rune_t.h
.o/thing_cursor_path.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_va_list.h
.o/thing_cursor_path.o: /usr/include/sys/stdio.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_off_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_cursor_path.o: /usr/include/secure/_stdio.h
.o/thing_cursor_path.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_clock_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_time_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_timespec.h
.o/thing_cursor_path.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_wint_t.h
.o/thing_cursor_path.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_cursor_path.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_cursor_path.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_cursor_path.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_cursor_path.o: my_level_static.h my_dungeon_grid.h my_wid_console.h
.o/thing_cursor_path.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/thing_cursor_path.o: my_wid_tiles.h my_thing.h my_light.h
.o/thing_cursor_path.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_danger.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_danger.o: /usr/include/sys/cdefs.h
.o/thing_danger.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_danger.o: /usr/include/sys/_posix_availability.h
.o/thing_danger.o: /usr/include/Availability.h
.o/thing_danger.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_danger.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_danger.o: /usr/include/i386/_types.h
.o/thing_danger.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_danger.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_danger.o: /usr/include/sys/_types/_int8_t.h
.o/thing_danger.o: /usr/include/sys/_types/_int16_t.h
.o/thing_danger.o: /usr/include/sys/_types/_int32_t.h
.o/thing_danger.o: /usr/include/sys/_types/_int64_t.h
.o/thing_danger.o: /usr/include/_types/_uint8_t.h
.o/thing_danger.o: /usr/include/_types/_uint16_t.h
.o/thing_danger.o: /usr/include/_types/_uint32_t.h
.o/thing_danger.o: /usr/include/_types/_uint64_t.h
.o/thing_danger.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_danger.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_danger.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_danger.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_danger.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_danger.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_danger.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_danger.o: /usr/include/_types/_intmax_t.h
.o/thing_danger.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_danger.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_danger.o: my_bounds_check.h /usr/include/assert.h
.o/thing_danger.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_danger.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_danger.o: my_string.h /usr/include/wchar.h
.o/thing_danger.o: /usr/include/sys/_types/_null.h
.o/thing_danger.o: /usr/include/sys/_types/_size_t.h
.o/thing_danger.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_danger.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_danger.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_danger.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_danger.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_danger.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_danger.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_danger.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_danger.o: /usr/include/sys/_types/_time_t.h
.o/thing_danger.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_danger.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_danger.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_danger.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_danger.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_danger.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_danger.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_danger.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_danger.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_dead.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_dead.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_dead.o: /usr/include/sys/_posix_availability.h
.o/thing_dead.o: /usr/include/Availability.h
.o/thing_dead.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_dead.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_dead.o: /usr/include/i386/_types.h
.o/thing_dead.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_dead.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_dead.o: /usr/include/sys/_types/_int8_t.h
.o/thing_dead.o: /usr/include/sys/_types/_int16_t.h
.o/thing_dead.o: /usr/include/sys/_types/_int32_t.h
.o/thing_dead.o: /usr/include/sys/_types/_int64_t.h
.o/thing_dead.o: /usr/include/_types/_uint8_t.h
.o/thing_dead.o: /usr/include/_types/_uint16_t.h
.o/thing_dead.o: /usr/include/_types/_uint32_t.h
.o/thing_dead.o: /usr/include/_types/_uint64_t.h
.o/thing_dead.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_dead.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_dead.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_dead.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_dead.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_dead.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_dead.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_dead.o: /usr/include/_types/_intmax_t.h
.o/thing_dead.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_dead.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_dead.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_dead.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_dead.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_dead.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_dead.o: /usr/include/sys/_types/_null.h
.o/thing_dead.o: /usr/include/sys/_types/_size_t.h
.o/thing_dead.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_dead.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_dead.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_dead.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_dead.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_dead.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_dead.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_dead.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_dead.o: /usr/include/sys/_types/_time_t.h
.o/thing_dead.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_dead.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_dead.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_dead.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_dead.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_dead.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_dead.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_dead.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_dead.o: my_thing_ai.h my_python.h my_log.h
.o/thing_describe.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_describe.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_describe.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_describe.o: /usr/include/sys/_posix_availability.h
.o/thing_describe.o: /usr/include/Availability.h
.o/thing_describe.o: /usr/include/AvailabilityInternal.h
.o/thing_describe.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_describe.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_describe.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_describe.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_describe.o: /usr/include/i386/_types.h
.o/thing_describe.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_describe.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_describe.o: /usr/include/sys/_types/_int8_t.h
.o/thing_describe.o: /usr/include/sys/_types/_int16_t.h
.o/thing_describe.o: /usr/include/sys/_types/_int32_t.h
.o/thing_describe.o: /usr/include/sys/_types/_int64_t.h
.o/thing_describe.o: /usr/include/_types/_uint8_t.h
.o/thing_describe.o: /usr/include/_types/_uint16_t.h
.o/thing_describe.o: /usr/include/_types/_uint32_t.h
.o/thing_describe.o: /usr/include/_types/_uint64_t.h
.o/thing_describe.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_describe.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_describe.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_describe.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_describe.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_describe.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_describe.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_describe.o: /usr/include/_types/_intmax_t.h
.o/thing_describe.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_describe.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_describe.o: my_bounds_check.h /usr/include/assert.h
.o/thing_describe.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_describe.o: my_string.h /usr/include/wchar.h
.o/thing_describe.o: /usr/include/sys/_types/_null.h
.o/thing_describe.o: /usr/include/sys/_types/_size_t.h
.o/thing_describe.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_describe.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_describe.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_describe.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_describe.o: /usr/include/sys/stdio.h
.o/thing_describe.o: /usr/include/sys/_types/_off_t.h
.o/thing_describe.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_describe.o: /usr/include/secure/_stdio.h
.o/thing_describe.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_describe.o: /usr/include/sys/_types/_clock_t.h
.o/thing_describe.o: /usr/include/sys/_types/_time_t.h
.o/thing_describe.o: /usr/include/sys/_types/_timespec.h
.o/thing_describe.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_describe.o: /usr/include/sys/_types/_wint_t.h
.o/thing_describe.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_describe.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_describe.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_describe.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_describe.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_describe.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_describe.o: my_color.h my_thing_ai.h
.o/thing_dir.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_dir.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_dir.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_dir.o: /usr/include/sys/_posix_availability.h
.o/thing_dir.o: /usr/include/Availability.h
.o/thing_dir.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_dir.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_dir.o: /usr/include/i386/_types.h
.o/thing_dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_dir.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_dir.o: /usr/include/sys/_types/_int8_t.h
.o/thing_dir.o: /usr/include/sys/_types/_int16_t.h
.o/thing_dir.o: /usr/include/sys/_types/_int32_t.h
.o/thing_dir.o: /usr/include/sys/_types/_int64_t.h
.o/thing_dir.o: /usr/include/_types/_uint8_t.h
.o/thing_dir.o: /usr/include/_types/_uint16_t.h
.o/thing_dir.o: /usr/include/_types/_uint32_t.h
.o/thing_dir.o: /usr/include/_types/_uint64_t.h
.o/thing_dir.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_dir.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_dir.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_dir.o: /usr/include/_types/_intmax_t.h
.o/thing_dir.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_dir.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_dir.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_dir.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/thing_dir.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_dir.o: /usr/include/sys/_types/_size_t.h
.o/thing_dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_dir.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_dir.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_dir.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_dir.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_dir.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_dir.o: /usr/include/sys/_types/_time_t.h
.o/thing_dir.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_dir.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_dir.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_dir.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_dir.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_dir.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_dir.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_dir.o: my_thing.h my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_dir.o: my_color.h my_thing_ai.h
.o/thing_display.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_display.o: /usr/include/sys/cdefs.h
.o/thing_display.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_display.o: /usr/include/sys/_posix_availability.h
.o/thing_display.o: /usr/include/Availability.h
.o/thing_display.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_display.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_display.o: /usr/include/i386/_types.h
.o/thing_display.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_display.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_display.o: /usr/include/sys/_types/_int8_t.h
.o/thing_display.o: /usr/include/sys/_types/_int16_t.h
.o/thing_display.o: /usr/include/sys/_types/_int32_t.h
.o/thing_display.o: /usr/include/sys/_types/_int64_t.h
.o/thing_display.o: /usr/include/_types/_uint8_t.h
.o/thing_display.o: /usr/include/_types/_uint16_t.h
.o/thing_display.o: /usr/include/_types/_uint32_t.h
.o/thing_display.o: /usr/include/_types/_uint64_t.h
.o/thing_display.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_display.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_display.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_display.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_display.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_display.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_display.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_display.o: /usr/include/_types/_intmax_t.h
.o/thing_display.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_display.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_display.o: my_bounds_check.h /usr/include/assert.h
.o/thing_display.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_display.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_display.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_display.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_display.o: /usr/include/sys/_types/_null.h
.o/thing_display.o: /usr/include/sys/_types/_size_t.h
.o/thing_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_display.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_display.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_display.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_display.o: /usr/include/secure/_stdio.h
.o/thing_display.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_display.o: /usr/include/sys/_types/_clock_t.h
.o/thing_display.o: /usr/include/sys/_types/_time_t.h
.o/thing_display.o: /usr/include/sys/_types/_timespec.h
.o/thing_display.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_display.o: /usr/include/sys/_types/_wint_t.h
.o/thing_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_display.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_display.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_display.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_display.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/thing_display.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_display.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/thing_distance.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_distance.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_distance.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_distance.o: /usr/include/sys/_posix_availability.h
.o/thing_distance.o: /usr/include/Availability.h
.o/thing_distance.o: /usr/include/AvailabilityInternal.h
.o/thing_distance.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_distance.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_distance.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_distance.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_distance.o: /usr/include/sys/_types/_int8_t.h
.o/thing_distance.o: /usr/include/sys/_types/_int16_t.h
.o/thing_distance.o: /usr/include/sys/_types/_int32_t.h
.o/thing_distance.o: /usr/include/sys/_types/_int64_t.h
.o/thing_distance.o: /usr/include/_types/_uint8_t.h
.o/thing_distance.o: /usr/include/_types/_uint16_t.h
.o/thing_distance.o: /usr/include/_types/_uint32_t.h
.o/thing_distance.o: /usr/include/_types/_uint64_t.h
.o/thing_distance.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_distance.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_distance.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_distance.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_distance.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_distance.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_distance.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_distance.o: /usr/include/_types/_intmax_t.h
.o/thing_distance.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_distance.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_distance.o: my_bounds_check.h /usr/include/assert.h
.o/thing_distance.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_distance.o: my_thing.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_distance.o: my_string.h /usr/include/wchar.h
.o/thing_distance.o: /usr/include/sys/_types/_null.h
.o/thing_distance.o: /usr/include/sys/_types/_size_t.h
.o/thing_distance.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_distance.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_distance.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_distance.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_distance.o: /usr/include/sys/stdio.h
.o/thing_distance.o: /usr/include/sys/_types/_off_t.h
.o/thing_distance.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_distance.o: /usr/include/secure/_stdio.h
.o/thing_distance.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_distance.o: /usr/include/sys/_types/_clock_t.h
.o/thing_distance.o: /usr/include/sys/_types/_time_t.h
.o/thing_distance.o: /usr/include/sys/_types/_timespec.h
.o/thing_distance.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_distance.o: /usr/include/sys/_types/_wint_t.h
.o/thing_distance.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_distance.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_distance.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_distance.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_distance.o: my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_distance.o: my_level.h my_particle.h my_dungeon.h my_room.h
.o/thing_distance.o: my_depth.h my_charmap.h my_level_static.h
.o/thing_distance.o: my_dungeon_grid.h
.o/thing_door.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_door.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_door.o: /usr/include/sys/_posix_availability.h
.o/thing_door.o: /usr/include/Availability.h
.o/thing_door.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_door.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_door.o: /usr/include/i386/_types.h
.o/thing_door.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_door.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_door.o: /usr/include/sys/_types/_int8_t.h
.o/thing_door.o: /usr/include/sys/_types/_int16_t.h
.o/thing_door.o: /usr/include/sys/_types/_int32_t.h
.o/thing_door.o: /usr/include/sys/_types/_int64_t.h
.o/thing_door.o: /usr/include/_types/_uint8_t.h
.o/thing_door.o: /usr/include/_types/_uint16_t.h
.o/thing_door.o: /usr/include/_types/_uint32_t.h
.o/thing_door.o: /usr/include/_types/_uint64_t.h
.o/thing_door.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_door.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_door.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_door.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_door.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_door.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_door.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_door.o: /usr/include/_types/_intmax_t.h
.o/thing_door.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_door.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_door.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_door.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_door.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_door.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_door.o: /usr/include/sys/_types/_null.h
.o/thing_door.o: /usr/include/sys/_types/_size_t.h
.o/thing_door.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_door.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_door.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_door.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_door.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_door.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_door.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_door.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_door.o: /usr/include/sys/_types/_time_t.h
.o/thing_door.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_door.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_door.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_door.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_door.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_door.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_door.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_door.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_door.o: my_thing_ai.h
.o/thing_drop.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_drop.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_drop.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_drop.o: /usr/include/sys/_posix_availability.h
.o/thing_drop.o: /usr/include/Availability.h
.o/thing_drop.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_drop.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_drop.o: /usr/include/i386/_types.h
.o/thing_drop.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_drop.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_drop.o: /usr/include/sys/_types/_int8_t.h
.o/thing_drop.o: /usr/include/sys/_types/_int16_t.h
.o/thing_drop.o: /usr/include/sys/_types/_int32_t.h
.o/thing_drop.o: /usr/include/sys/_types/_int64_t.h
.o/thing_drop.o: /usr/include/_types/_uint8_t.h
.o/thing_drop.o: /usr/include/_types/_uint16_t.h
.o/thing_drop.o: /usr/include/_types/_uint32_t.h
.o/thing_drop.o: /usr/include/_types/_uint64_t.h
.o/thing_drop.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_drop.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_drop.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_drop.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_drop.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_drop.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_drop.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_drop.o: /usr/include/_types/_intmax_t.h
.o/thing_drop.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_drop.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_drop.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_drop.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/thing_drop.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_drop.o: /usr/include/sys/_types/_size_t.h
.o/thing_drop.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_drop.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_drop.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_drop.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_drop.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_drop.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_drop.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_drop.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_drop.o: /usr/include/sys/_types/_time_t.h
.o/thing_drop.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_drop.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_drop.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_drop.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_drop.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_drop.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_drop.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_drop.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_drop.o: my_tile.h my_color.h my_thing_ai.h my_game.h my_world.h
.o/thing_drop.o: my_wid_thing_info.h my_wid.h my_ascii.h my_tex.h
.o/thing_drop.o: my_wid_tiles.h my_wid_popup.h my_wid_text_box.h
.o/thing_drop.o: my_wid_inventory.h
.o/thing_eat.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_eat.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_eat.o: /usr/include/sys/_posix_availability.h
.o/thing_eat.o: /usr/include/Availability.h
.o/thing_eat.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_eat.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_eat.o: /usr/include/i386/_types.h
.o/thing_eat.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_eat.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_eat.o: /usr/include/sys/_types/_int8_t.h
.o/thing_eat.o: /usr/include/sys/_types/_int16_t.h
.o/thing_eat.o: /usr/include/sys/_types/_int32_t.h
.o/thing_eat.o: /usr/include/sys/_types/_int64_t.h
.o/thing_eat.o: /usr/include/_types/_uint8_t.h
.o/thing_eat.o: /usr/include/_types/_uint16_t.h
.o/thing_eat.o: /usr/include/_types/_uint32_t.h
.o/thing_eat.o: /usr/include/_types/_uint64_t.h
.o/thing_eat.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_eat.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_eat.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_eat.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_eat.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_eat.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_eat.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_eat.o: /usr/include/_types/_intmax_t.h
.o/thing_eat.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_eat.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_eat.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_eat.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_eat.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_eat.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_eat.o: /usr/include/sys/_types/_null.h
.o/thing_eat.o: /usr/include/sys/_types/_size_t.h
.o/thing_eat.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_eat.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_eat.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_eat.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_eat.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_eat.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_eat.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_eat.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_eat.o: /usr/include/sys/_types/_time_t.h
.o/thing_eat.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_eat.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_eat.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_eat.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_eat.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_eat.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_eat.o: my_dungeon_grid.h my_tile.h my_color.h my_thing.h my_light.h
.o/thing_eat.o: my_thing_template.h my_dice.h my_thing_ai.h my_sprintf.h
.o/thing_enemy.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_enemy.o: /usr/include/sys/cdefs.h
.o/thing_enemy.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_enemy.o: /usr/include/sys/_posix_availability.h
.o/thing_enemy.o: /usr/include/Availability.h
.o/thing_enemy.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_enemy.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_enemy.o: /usr/include/i386/_types.h
.o/thing_enemy.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_enemy.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_enemy.o: /usr/include/sys/_types/_int8_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_int16_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_int32_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_int64_t.h
.o/thing_enemy.o: /usr/include/_types/_uint8_t.h
.o/thing_enemy.o: /usr/include/_types/_uint16_t.h
.o/thing_enemy.o: /usr/include/_types/_uint32_t.h
.o/thing_enemy.o: /usr/include/_types/_uint64_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_enemy.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_enemy.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_enemy.o: /usr/include/_types/_intmax_t.h
.o/thing_enemy.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_enemy.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_enemy.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_enemy.o: c_plus_plus_serializer.h my_tile.h my_sdl.h my_command.h
.o/thing_enemy.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_enemy.o: /usr/include/sys/_types/_null.h
.o/thing_enemy.o: /usr/include/sys/_types/_size_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_enemy.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_enemy.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_enemy.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_enemy.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_time_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_enemy.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_enemy.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_enemy.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_enemy.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_enemy.o: my_thing.h my_time.h my_light.h my_thing_template.h
.o/thing_enemy.o: my_dice.h my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_enemy.o: my_sprintf.h
.o/thing_entrance.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_entrance.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_entrance.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_entrance.o: /usr/include/sys/_posix_availability.h
.o/thing_entrance.o: /usr/include/Availability.h
.o/thing_entrance.o: /usr/include/AvailabilityInternal.h
.o/thing_entrance.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_entrance.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_entrance.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_entrance.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_entrance.o: /usr/include/sys/_types/_int8_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_int16_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_int32_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_int64_t.h
.o/thing_entrance.o: /usr/include/_types/_uint8_t.h
.o/thing_entrance.o: /usr/include/_types/_uint16_t.h
.o/thing_entrance.o: /usr/include/_types/_uint32_t.h
.o/thing_entrance.o: /usr/include/_types/_uint64_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_entrance.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_entrance.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_entrance.o: /usr/include/_types/_intmax_t.h
.o/thing_entrance.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_entrance.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_entrance.o: my_bounds_check.h /usr/include/assert.h
.o/thing_entrance.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_entrance.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_entrance.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_entrance.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_entrance.o: /usr/include/sys/_types/_null.h
.o/thing_entrance.o: /usr/include/sys/_types/_size_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_entrance.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_entrance.o: /usr/include/sys/stdio.h
.o/thing_entrance.o: /usr/include/sys/_types/_off_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_entrance.o: /usr/include/secure/_stdio.h
.o/thing_entrance.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_entrance.o: /usr/include/sys/_types/_clock_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_time_t.h
.o/thing_entrance.o: /usr/include/sys/_types/_timespec.h
.o/thing_entrance.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_entrance.o: /usr/include/sys/_types/_wint_t.h
.o/thing_entrance.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_entrance.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_entrance.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_entrance.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_entrance.o: my_level_static.h my_dungeon_grid.h my_color.h
.o/thing_entrance.o: my_sprintf.h my_thing.h my_light.h my_thing_template.h
.o/thing_entrance.o: my_dice.h my_tile.h my_thing_ai.h
.o/thing_escape.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_escape.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_escape.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_escape.o: /usr/include/sys/_posix_availability.h
.o/thing_escape.o: /usr/include/Availability.h
.o/thing_escape.o: /usr/include/AvailabilityInternal.h
.o/thing_escape.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_escape.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_escape.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_escape.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_escape.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_escape.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_escape.o: /usr/include/sys/_types/_int8_t.h
.o/thing_escape.o: /usr/include/sys/_types/_int16_t.h
.o/thing_escape.o: /usr/include/sys/_types/_int32_t.h
.o/thing_escape.o: /usr/include/sys/_types/_int64_t.h
.o/thing_escape.o: /usr/include/_types/_uint8_t.h
.o/thing_escape.o: /usr/include/_types/_uint16_t.h
.o/thing_escape.o: /usr/include/_types/_uint32_t.h
.o/thing_escape.o: /usr/include/_types/_uint64_t.h
.o/thing_escape.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_escape.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_escape.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_escape.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_escape.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_escape.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_escape.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_escape.o: /usr/include/_types/_intmax_t.h
.o/thing_escape.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_escape.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_escape.o: my_bounds_check.h /usr/include/assert.h
.o/thing_escape.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_escape.o: my_string.h /usr/include/wchar.h
.o/thing_escape.o: /usr/include/sys/_types/_null.h
.o/thing_escape.o: /usr/include/sys/_types/_size_t.h
.o/thing_escape.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_escape.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_escape.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_escape.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_escape.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_escape.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_escape.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_escape.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_escape.o: /usr/include/sys/_types/_time_t.h
.o/thing_escape.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_escape.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_escape.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_escape.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_escape.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_escape.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_escape.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/thing_escape.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_escape.o: my_thing_ai.h my_sprintf.h my_gl.h
.o/thing_exit.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_exit.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_exit.o: /usr/include/sys/_posix_availability.h
.o/thing_exit.o: /usr/include/Availability.h
.o/thing_exit.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_exit.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_exit.o: /usr/include/i386/_types.h
.o/thing_exit.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_exit.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_exit.o: /usr/include/sys/_types/_int8_t.h
.o/thing_exit.o: /usr/include/sys/_types/_int16_t.h
.o/thing_exit.o: /usr/include/sys/_types/_int32_t.h
.o/thing_exit.o: /usr/include/sys/_types/_int64_t.h
.o/thing_exit.o: /usr/include/_types/_uint8_t.h
.o/thing_exit.o: /usr/include/_types/_uint16_t.h
.o/thing_exit.o: /usr/include/_types/_uint32_t.h
.o/thing_exit.o: /usr/include/_types/_uint64_t.h
.o/thing_exit.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_exit.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_exit.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_exit.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_exit.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_exit.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_exit.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_exit.o: /usr/include/_types/_intmax_t.h
.o/thing_exit.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_exit.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_exit.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_exit.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_exit.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_exit.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_exit.o: /usr/include/sys/_types/_null.h
.o/thing_exit.o: /usr/include/sys/_types/_size_t.h
.o/thing_exit.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_exit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_exit.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_exit.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_exit.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_exit.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_exit.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_exit.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_exit.o: /usr/include/sys/_types/_time_t.h
.o/thing_exit.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_exit.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_exit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_exit.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_exit.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_exit.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_exit.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_exit.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_exit.o: my_thing_ai.h
.o/thing_fadeup.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_fadeup.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_fadeup.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_fadeup.o: /usr/include/sys/_posix_availability.h
.o/thing_fadeup.o: /usr/include/Availability.h
.o/thing_fadeup.o: /usr/include/AvailabilityInternal.h
.o/thing_fadeup.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_fadeup.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_fadeup.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_fadeup.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_fadeup.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_fadeup.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_fadeup.o: /usr/include/sys/_types/_int8_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_int16_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_int32_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_int64_t.h
.o/thing_fadeup.o: /usr/include/_types/_uint8_t.h
.o/thing_fadeup.o: /usr/include/_types/_uint16_t.h
.o/thing_fadeup.o: /usr/include/_types/_uint32_t.h
.o/thing_fadeup.o: /usr/include/_types/_uint64_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_fadeup.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_fadeup.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_fadeup.o: /usr/include/_types/_intmax_t.h
.o/thing_fadeup.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_fadeup.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_fadeup.o: my_bounds_check.h /usr/include/assert.h
.o/thing_fadeup.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_fadeup.o: my_string.h /usr/include/wchar.h
.o/thing_fadeup.o: /usr/include/sys/_types/_null.h
.o/thing_fadeup.o: /usr/include/sys/_types/_size_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_fadeup.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_fadeup.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_fadeup.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_fadeup.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_time_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_fadeup.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_fadeup.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_fadeup.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_fadeup.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_fadeup.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_fadeup.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/thing_fadeup.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_fadeup.o: my_thing_ai.h my_sprintf.h my_gl.h
.o/thing_fall.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_fall.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_fall.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_fall.o: /usr/include/sys/_posix_availability.h
.o/thing_fall.o: /usr/include/Availability.h
.o/thing_fall.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/thing_fall.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_fall.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/thing_fall.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_fall.o: /usr/include/i386/_types.h
.o/thing_fall.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_fall.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_fall.o: /usr/include/sys/_types/_int8_t.h
.o/thing_fall.o: /usr/include/sys/_types/_int16_t.h
.o/thing_fall.o: /usr/include/sys/_types/_int32_t.h
.o/thing_fall.o: /usr/include/sys/_types/_int64_t.h
.o/thing_fall.o: /usr/include/_types/_uint8_t.h
.o/thing_fall.o: /usr/include/_types/_uint16_t.h
.o/thing_fall.o: /usr/include/_types/_uint32_t.h
.o/thing_fall.o: /usr/include/_types/_uint64_t.h
.o/thing_fall.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_fall.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_fall.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_fall.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_fall.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_fall.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_fall.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_fall.o: /usr/include/_types/_intmax_t.h
.o/thing_fall.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_fall.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_fall.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/thing_fall.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_fall.o: /usr/include/sys/_types/_null.h
.o/thing_fall.o: /usr/include/sys/_types/_size_t.h
.o/thing_fall.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_fall.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_fall.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_fall.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_fall.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_fall.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_fall.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_fall.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_fall.o: /usr/include/sys/_types/_time_t.h
.o/thing_fall.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_fall.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_fall.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_fall.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_fall.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_fall.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_fall.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_fall.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_fall.o: my_gl.h
.o/thing_fini.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_fini.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_fini.o: /usr/include/sys/_posix_availability.h
.o/thing_fini.o: /usr/include/Availability.h
.o/thing_fini.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_fini.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_fini.o: /usr/include/i386/_types.h
.o/thing_fini.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_fini.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_fini.o: /usr/include/sys/_types/_int8_t.h
.o/thing_fini.o: /usr/include/sys/_types/_int16_t.h
.o/thing_fini.o: /usr/include/sys/_types/_int32_t.h
.o/thing_fini.o: /usr/include/sys/_types/_int64_t.h
.o/thing_fini.o: /usr/include/_types/_uint8_t.h
.o/thing_fini.o: /usr/include/_types/_uint16_t.h
.o/thing_fini.o: /usr/include/_types/_uint32_t.h
.o/thing_fini.o: /usr/include/_types/_uint64_t.h
.o/thing_fini.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_fini.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_fini.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_fini.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_fini.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_fini.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_fini.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_fini.o: /usr/include/_types/_intmax_t.h
.o/thing_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_fini.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_fini.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_fini.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_fini.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_fini.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_fini.o: /usr/include/sys/_types/_null.h
.o/thing_fini.o: /usr/include/sys/_types/_size_t.h
.o/thing_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_fini.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_fini.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_fini.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_fini.o: /usr/include/sys/_types/_time_t.h
.o/thing_fini.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_fini.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_fini.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_fini.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_fini.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_fini.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_fini.o: my_thing_ai.h
.o/thing_fire.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_fire.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_fire.o: /usr/include/sys/_posix_availability.h
.o/thing_fire.o: /usr/include/Availability.h
.o/thing_fire.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_fire.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_fire.o: /usr/include/i386/_types.h
.o/thing_fire.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_fire.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_fire.o: /usr/include/sys/_types/_int8_t.h
.o/thing_fire.o: /usr/include/sys/_types/_int16_t.h
.o/thing_fire.o: /usr/include/sys/_types/_int32_t.h
.o/thing_fire.o: /usr/include/sys/_types/_int64_t.h
.o/thing_fire.o: /usr/include/_types/_uint8_t.h
.o/thing_fire.o: /usr/include/_types/_uint16_t.h
.o/thing_fire.o: /usr/include/_types/_uint32_t.h
.o/thing_fire.o: /usr/include/_types/_uint64_t.h
.o/thing_fire.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_fire.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_fire.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_fire.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_fire.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_fire.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_fire.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_fire.o: /usr/include/_types/_intmax_t.h
.o/thing_fire.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_fire.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_fire.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_fire.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_fire.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_fire.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_fire.o: /usr/include/sys/_types/_null.h
.o/thing_fire.o: /usr/include/sys/_types/_size_t.h
.o/thing_fire.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_fire.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_fire.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_fire.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_fire.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_fire.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_fire.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_fire.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_fire.o: /usr/include/sys/_types/_time_t.h
.o/thing_fire.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_fire.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_fire.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_fire.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_fire.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_fire.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_fire.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_fire.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_gc.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_gc.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_gc.o: /usr/include/sys/_posix_availability.h
.o/thing_gc.o: /usr/include/Availability.h
.o/thing_gc.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_gc.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_gc.o: /usr/include/i386/_types.h
.o/thing_gc.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_gc.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_gc.o: /usr/include/sys/_types/_int8_t.h
.o/thing_gc.o: /usr/include/sys/_types/_int16_t.h
.o/thing_gc.o: /usr/include/sys/_types/_int32_t.h
.o/thing_gc.o: /usr/include/sys/_types/_int64_t.h
.o/thing_gc.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/thing_gc.o: /usr/include/_types/_uint32_t.h
.o/thing_gc.o: /usr/include/_types/_uint64_t.h
.o/thing_gc.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_gc.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_gc.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_gc.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_gc.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_gc.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_gc.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_gc.o: /usr/include/_types/_intmax_t.h
.o/thing_gc.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_gc.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_gc.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_gc.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_gc.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_gc.o: /usr/include/sys/_types/_null.h
.o/thing_gc.o: /usr/include/sys/_types/_size_t.h
.o/thing_gc.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_gc.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_gc.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_gc.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_gc.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_gc.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_gc.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_gc.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_gc.o: /usr/include/sys/_types/_time_t.h
.o/thing_gc.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_gc.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_gc.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_gc.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_gc.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_gc.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_gc.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_gc.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_gc.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_health.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_health.o: /usr/include/sys/cdefs.h
.o/thing_health.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_health.o: /usr/include/sys/_posix_availability.h
.o/thing_health.o: /usr/include/Availability.h
.o/thing_health.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_health.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_health.o: /usr/include/i386/_types.h
.o/thing_health.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_health.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_health.o: /usr/include/sys/_types/_int8_t.h
.o/thing_health.o: /usr/include/sys/_types/_int16_t.h
.o/thing_health.o: /usr/include/sys/_types/_int32_t.h
.o/thing_health.o: /usr/include/sys/_types/_int64_t.h
.o/thing_health.o: /usr/include/_types/_uint8_t.h
.o/thing_health.o: /usr/include/_types/_uint16_t.h
.o/thing_health.o: /usr/include/_types/_uint32_t.h
.o/thing_health.o: /usr/include/_types/_uint64_t.h
.o/thing_health.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_health.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_health.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_health.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_health.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_health.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_health.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_health.o: /usr/include/_types/_intmax_t.h
.o/thing_health.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_health.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_health.o: my_bounds_check.h /usr/include/assert.h
.o/thing_health.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_health.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/thing_health.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_health.o: /usr/include/sys/_types/_size_t.h
.o/thing_health.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_health.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_health.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_health.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_health.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_health.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_health.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_health.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_health.o: /usr/include/sys/_types/_time_t.h
.o/thing_health.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_health.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_health.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_health.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_health.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_health.o: my_thing.h my_time.h my_light.h my_thing_template.h
.o/thing_health.o: my_dice.h my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_hide.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_hide.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_hide.o: /usr/include/sys/_posix_availability.h
.o/thing_hide.o: /usr/include/Availability.h
.o/thing_hide.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_hide.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_hide.o: /usr/include/i386/_types.h
.o/thing_hide.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_hide.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_hide.o: /usr/include/sys/_types/_int8_t.h
.o/thing_hide.o: /usr/include/sys/_types/_int16_t.h
.o/thing_hide.o: /usr/include/sys/_types/_int32_t.h
.o/thing_hide.o: /usr/include/sys/_types/_int64_t.h
.o/thing_hide.o: /usr/include/_types/_uint8_t.h
.o/thing_hide.o: /usr/include/_types/_uint16_t.h
.o/thing_hide.o: /usr/include/_types/_uint32_t.h
.o/thing_hide.o: /usr/include/_types/_uint64_t.h
.o/thing_hide.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_hide.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_hide.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_hide.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_hide.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_hide.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_hide.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_hide.o: /usr/include/_types/_intmax_t.h
.o/thing_hide.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_hide.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_hide.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_hide.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_hide.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_hide.o: /usr/include/sys/_types/_null.h
.o/thing_hide.o: /usr/include/sys/_types/_size_t.h
.o/thing_hide.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_hide.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_hide.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_hide.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_hide.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_hide.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_hide.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_hide.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_hide.o: /usr/include/sys/_types/_time_t.h
.o/thing_hide.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_hide.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_hide.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_hide.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_hide.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_hide.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_hide.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_hide.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_hide.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_hit.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_hit.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_hit.o: /usr/include/sys/_posix_availability.h
.o/thing_hit.o: /usr/include/Availability.h
.o/thing_hit.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_hit.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_hit.o: /usr/include/i386/_types.h
.o/thing_hit.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_hit.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_hit.o: /usr/include/sys/_types/_int8_t.h
.o/thing_hit.o: /usr/include/sys/_types/_int16_t.h
.o/thing_hit.o: /usr/include/sys/_types/_int32_t.h
.o/thing_hit.o: /usr/include/sys/_types/_int64_t.h
.o/thing_hit.o: /usr/include/_types/_uint8_t.h
.o/thing_hit.o: /usr/include/_types/_uint16_t.h
.o/thing_hit.o: /usr/include/_types/_uint32_t.h
.o/thing_hit.o: /usr/include/_types/_uint64_t.h
.o/thing_hit.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_hit.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_hit.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_hit.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_hit.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_hit.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_hit.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_hit.o: /usr/include/_types/_intmax_t.h
.o/thing_hit.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_hit.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_hit.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_hit.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_hit.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_hit.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_hit.o: /usr/include/sys/_types/_null.h
.o/thing_hit.o: /usr/include/sys/_types/_size_t.h
.o/thing_hit.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_hit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_hit.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_hit.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_hit.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_hit.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_hit.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_hit.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_hit.o: /usr/include/sys/_types/_time_t.h
.o/thing_hit.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_hit.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_hit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_hit.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_hit.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_hit.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_hit.o: my_dungeon_grid.h my_tile.h my_color.h my_thing.h my_light.h
.o/thing_hit.o: my_thing_template.h my_dice.h my_thing_ai.h my_sprintf.h
.o/thing_hooks.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_hooks.o: /usr/include/sys/cdefs.h
.o/thing_hooks.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_hooks.o: /usr/include/sys/_posix_availability.h
.o/thing_hooks.o: /usr/include/Availability.h
.o/thing_hooks.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_hooks.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_hooks.o: /usr/include/i386/_types.h
.o/thing_hooks.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_hooks.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_hooks.o: /usr/include/sys/_types/_int8_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_int16_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_int32_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_int64_t.h
.o/thing_hooks.o: /usr/include/_types/_uint8_t.h
.o/thing_hooks.o: /usr/include/_types/_uint16_t.h
.o/thing_hooks.o: /usr/include/_types/_uint32_t.h
.o/thing_hooks.o: /usr/include/_types/_uint64_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_hooks.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_hooks.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_hooks.o: /usr/include/_types/_intmax_t.h
.o/thing_hooks.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_hooks.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_hooks.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_hooks.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_hooks.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_hooks.o: /usr/include/sys/_types/_null.h
.o/thing_hooks.o: /usr/include/sys/_types/_size_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_hooks.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_hooks.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_hooks.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_hooks.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_time_t.h
.o/thing_hooks.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_hooks.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_hooks.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_hooks.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_hooks.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_hooks.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_hooks.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_hooks.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_hooks.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_hunger.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_hunger.o: /usr/include/sys/cdefs.h
.o/thing_hunger.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_hunger.o: /usr/include/sys/_posix_availability.h
.o/thing_hunger.o: /usr/include/Availability.h
.o/thing_hunger.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_hunger.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_hunger.o: /usr/include/i386/_types.h
.o/thing_hunger.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_hunger.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_hunger.o: /usr/include/sys/_types/_int8_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_int16_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_int32_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_int64_t.h
.o/thing_hunger.o: /usr/include/_types/_uint8_t.h
.o/thing_hunger.o: /usr/include/_types/_uint16_t.h
.o/thing_hunger.o: /usr/include/_types/_uint32_t.h
.o/thing_hunger.o: /usr/include/_types/_uint64_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_hunger.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_hunger.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_hunger.o: /usr/include/_types/_intmax_t.h
.o/thing_hunger.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_hunger.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_hunger.o: my_bounds_check.h /usr/include/assert.h
.o/thing_hunger.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_hunger.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/thing_hunger.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_hunger.o: /usr/include/sys/_types/_size_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_hunger.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_hunger.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_hunger.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_hunger.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_time_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_hunger.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_hunger.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_hunger.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_hunger.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_hunger.o: my_thing.h my_time.h my_light.h my_thing_template.h
.o/thing_hunger.o: my_dice.h my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_id.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_id.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_id.o: /usr/include/sys/_posix_availability.h
.o/thing_id.o: /usr/include/Availability.h
.o/thing_id.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_id.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_id.o: /usr/include/i386/_types.h
.o/thing_id.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_id.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_id.o: /usr/include/sys/_types/_int8_t.h
.o/thing_id.o: /usr/include/sys/_types/_int16_t.h
.o/thing_id.o: /usr/include/sys/_types/_int32_t.h
.o/thing_id.o: /usr/include/sys/_types/_int64_t.h
.o/thing_id.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/thing_id.o: /usr/include/_types/_uint32_t.h
.o/thing_id.o: /usr/include/_types/_uint64_t.h
.o/thing_id.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_id.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_id.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_id.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_id.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_id.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_id.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_id.o: /usr/include/_types/_intmax_t.h
.o/thing_id.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_id.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_id.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_id.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_id.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_id.o: /usr/include/sys/_types/_null.h
.o/thing_id.o: /usr/include/sys/_types/_size_t.h
.o/thing_id.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_id.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_id.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_id.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_id.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_id.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_id.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_id.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_id.o: /usr/include/sys/_types/_time_t.h
.o/thing_id.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_id.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_id.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_id.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_id.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_id.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_id.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_id.o: my_world.h my_color.h my_thing.h my_light.h
.o/thing_id.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_inherit.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_inherit.o: /usr/include/sys/cdefs.h
.o/thing_inherit.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_inherit.o: /usr/include/sys/_posix_availability.h
.o/thing_inherit.o: /usr/include/Availability.h
.o/thing_inherit.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_inherit.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_inherit.o: /usr/include/i386/_types.h
.o/thing_inherit.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_inherit.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_inherit.o: /usr/include/sys/_types/_int8_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_int16_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_int32_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_int64_t.h
.o/thing_inherit.o: /usr/include/_types/_uint8_t.h
.o/thing_inherit.o: /usr/include/_types/_uint16_t.h
.o/thing_inherit.o: /usr/include/_types/_uint32_t.h
.o/thing_inherit.o: /usr/include/_types/_uint64_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_inherit.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_inherit.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_inherit.o: /usr/include/_types/_intmax_t.h
.o/thing_inherit.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_inherit.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_inherit.o: my_bounds_check.h /usr/include/assert.h
.o/thing_inherit.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_inherit.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_inherit.o: my_string.h /usr/include/wchar.h
.o/thing_inherit.o: /usr/include/sys/_types/_null.h
.o/thing_inherit.o: /usr/include/sys/_types/_size_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_inherit.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_inherit.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_inherit.o: /usr/include/secure/_stdio.h
.o/thing_inherit.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_inherit.o: /usr/include/sys/_types/_clock_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_time_t.h
.o/thing_inherit.o: /usr/include/sys/_types/_timespec.h
.o/thing_inherit.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_inherit.o: /usr/include/sys/_types/_wint_t.h
.o/thing_inherit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_inherit.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_inherit.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_inherit.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_inherit.o: my_charmap.h my_dmap.h my_level_static.h
.o/thing_inherit.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_inherit.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_inherit.o: my_thing_ai.h
.o/thing_init.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_init.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_init.o: /usr/include/sys/_posix_availability.h
.o/thing_init.o: /usr/include/Availability.h
.o/thing_init.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_init.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_init.o: /usr/include/i386/_types.h
.o/thing_init.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_init.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_init.o: /usr/include/sys/_types/_int8_t.h
.o/thing_init.o: /usr/include/sys/_types/_int16_t.h
.o/thing_init.o: /usr/include/sys/_types/_int32_t.h
.o/thing_init.o: /usr/include/sys/_types/_int64_t.h
.o/thing_init.o: /usr/include/_types/_uint8_t.h
.o/thing_init.o: /usr/include/_types/_uint16_t.h
.o/thing_init.o: /usr/include/_types/_uint32_t.h
.o/thing_init.o: /usr/include/_types/_uint64_t.h
.o/thing_init.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_init.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_init.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_init.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_init.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_init.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_init.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_init.o: /usr/include/_types/_intmax_t.h
.o/thing_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_init.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_init.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_init.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_init.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_init.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_init.o: /usr/include/sys/_types/_null.h
.o/thing_init.o: /usr/include/sys/_types/_size_t.h
.o/thing_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_init.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_init.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_init.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_init.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_init.o: /usr/include/sys/_types/_time_t.h
.o/thing_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_init.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_init.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_init.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_init.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_init.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_init.o: my_thing_ai.h my_python.h
.o/thing_inventory.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_inventory.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_inventory.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_inventory.o: /usr/include/sys/_posix_availability.h
.o/thing_inventory.o: /usr/include/Availability.h
.o/thing_inventory.o: /usr/include/AvailabilityInternal.h
.o/thing_inventory.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_inventory.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_inventory.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_inventory.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_inventory.o: /usr/include/i386/_types.h
.o/thing_inventory.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_inventory.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_inventory.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_int16_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_int32_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_int64_t.h
.o/thing_inventory.o: /usr/include/_types/_uint8_t.h
.o/thing_inventory.o: /usr/include/_types/_uint16_t.h
.o/thing_inventory.o: /usr/include/_types/_uint32_t.h
.o/thing_inventory.o: /usr/include/_types/_uint64_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_inventory.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_inventory.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_inventory.o: /usr/include/_types/_intmax_t.h
.o/thing_inventory.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_inventory.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_inventory.o: my_bounds_check.h /usr/include/assert.h
.o/thing_inventory.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_inventory.o: my_string.h /usr/include/wchar.h
.o/thing_inventory.o: /usr/include/sys/_types/_null.h
.o/thing_inventory.o: /usr/include/sys/_types/_size_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_inventory.o: /usr/include/_stdio.h
.o/thing_inventory.o: /usr/include/sys/_types/_va_list.h
.o/thing_inventory.o: /usr/include/sys/stdio.h
.o/thing_inventory.o: /usr/include/sys/_types/_off_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_inventory.o: /usr/include/secure/_stdio.h
.o/thing_inventory.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_inventory.o: /usr/include/sys/_types/_clock_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_time_t.h
.o/thing_inventory.o: /usr/include/sys/_types/_timespec.h
.o/thing_inventory.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_inventory.o: /usr/include/sys/_types/_wint_t.h
.o/thing_inventory.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_inventory.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_inventory.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_inventory.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_inventory.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_inventory.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_inventory.o: my_color.h my_thing_ai.h my_wid_inventory.h my_wid.h
.o/thing_inventory.o: my_ascii.h my_tex.h my_wid_tiles.h my_wid_thing_info.h
.o/thing_inventory.o: my_wid_popup.h my_wid_text_box.h
.o/thing_item.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_item.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_item.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_item.o: /usr/include/sys/_posix_availability.h
.o/thing_item.o: /usr/include/Availability.h
.o/thing_item.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/thing_item.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_item.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/thing_item.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_item.o: /usr/include/i386/_types.h
.o/thing_item.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_item.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_item.o: /usr/include/sys/_types/_int8_t.h
.o/thing_item.o: /usr/include/sys/_types/_int16_t.h
.o/thing_item.o: /usr/include/sys/_types/_int32_t.h
.o/thing_item.o: /usr/include/sys/_types/_int64_t.h
.o/thing_item.o: /usr/include/_types/_uint8_t.h
.o/thing_item.o: /usr/include/_types/_uint16_t.h
.o/thing_item.o: /usr/include/_types/_uint32_t.h
.o/thing_item.o: /usr/include/_types/_uint64_t.h
.o/thing_item.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_item.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_item.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_item.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_item.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_item.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_item.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_item.o: /usr/include/_types/_intmax_t.h
.o/thing_item.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_item.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_item.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/thing_item.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_item.o: /usr/include/sys/_types/_null.h
.o/thing_item.o: /usr/include/sys/_types/_size_t.h
.o/thing_item.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_item.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_item.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_item.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_item.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_item.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_item.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_item.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_item.o: /usr/include/sys/_types/_time_t.h
.o/thing_item.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_item.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_item.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_item.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_item.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_item.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_item.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_item.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_item.o: my_gl.h
.o/thing_jump.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_jump.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_jump.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_jump.o: /usr/include/sys/_posix_availability.h
.o/thing_jump.o: /usr/include/Availability.h
.o/thing_jump.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/thing_jump.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_jump.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/thing_jump.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_jump.o: /usr/include/i386/_types.h
.o/thing_jump.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_jump.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_jump.o: /usr/include/sys/_types/_int8_t.h
.o/thing_jump.o: /usr/include/sys/_types/_int16_t.h
.o/thing_jump.o: /usr/include/sys/_types/_int32_t.h
.o/thing_jump.o: /usr/include/sys/_types/_int64_t.h
.o/thing_jump.o: /usr/include/_types/_uint8_t.h
.o/thing_jump.o: /usr/include/_types/_uint16_t.h
.o/thing_jump.o: /usr/include/_types/_uint32_t.h
.o/thing_jump.o: /usr/include/_types/_uint64_t.h
.o/thing_jump.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_jump.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_jump.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_jump.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_jump.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_jump.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_jump.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_jump.o: /usr/include/_types/_intmax_t.h
.o/thing_jump.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_jump.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_jump.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/thing_jump.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_jump.o: /usr/include/sys/_types/_null.h
.o/thing_jump.o: /usr/include/sys/_types/_size_t.h
.o/thing_jump.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_jump.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_jump.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_jump.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_jump.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_jump.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_jump.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_jump.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_jump.o: /usr/include/sys/_types/_time_t.h
.o/thing_jump.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_jump.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_jump.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_jump.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_jump.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_jump.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_jump.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_jump.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_jump.o: my_gl.h
.o/thing_kill.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_kill.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_kill.o: /usr/include/sys/_posix_availability.h
.o/thing_kill.o: /usr/include/Availability.h
.o/thing_kill.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_kill.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_kill.o: /usr/include/i386/_types.h
.o/thing_kill.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_kill.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_kill.o: /usr/include/sys/_types/_int8_t.h
.o/thing_kill.o: /usr/include/sys/_types/_int16_t.h
.o/thing_kill.o: /usr/include/sys/_types/_int32_t.h
.o/thing_kill.o: /usr/include/sys/_types/_int64_t.h
.o/thing_kill.o: /usr/include/_types/_uint8_t.h
.o/thing_kill.o: /usr/include/_types/_uint16_t.h
.o/thing_kill.o: /usr/include/_types/_uint32_t.h
.o/thing_kill.o: /usr/include/_types/_uint64_t.h
.o/thing_kill.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_kill.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_kill.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_kill.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_kill.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_kill.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_kill.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_kill.o: /usr/include/_types/_intmax_t.h
.o/thing_kill.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_kill.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_kill.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_kill.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_kill.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_kill.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_kill.o: /usr/include/sys/_types/_null.h
.o/thing_kill.o: /usr/include/sys/_types/_size_t.h
.o/thing_kill.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_kill.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_kill.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_kill.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_kill.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_kill.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_kill.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_kill.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_kill.o: /usr/include/sys/_types/_time_t.h
.o/thing_kill.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_kill.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_kill.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_kill.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_kill.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_kill.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_kill.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_kill.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_kill.o: my_thing_ai.h my_python.h my_log.h
.o/thing_kill_if.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_kill_if.o: /usr/include/sys/cdefs.h
.o/thing_kill_if.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_kill_if.o: /usr/include/sys/_posix_availability.h
.o/thing_kill_if.o: /usr/include/Availability.h
.o/thing_kill_if.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_kill_if.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_kill_if.o: /usr/include/i386/_types.h
.o/thing_kill_if.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_kill_if.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_kill_if.o: /usr/include/sys/_types/_int8_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_int16_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_int32_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_int64_t.h
.o/thing_kill_if.o: /usr/include/_types/_uint8_t.h
.o/thing_kill_if.o: /usr/include/_types/_uint16_t.h
.o/thing_kill_if.o: /usr/include/_types/_uint32_t.h
.o/thing_kill_if.o: /usr/include/_types/_uint64_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_kill_if.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_kill_if.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_kill_if.o: /usr/include/_types/_intmax_t.h
.o/thing_kill_if.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_kill_if.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_kill_if.o: my_bounds_check.h /usr/include/assert.h
.o/thing_kill_if.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_kill_if.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_kill_if.o: my_string.h /usr/include/wchar.h
.o/thing_kill_if.o: /usr/include/sys/_types/_null.h
.o/thing_kill_if.o: /usr/include/sys/_types/_size_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_kill_if.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_kill_if.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_kill_if.o: /usr/include/secure/_stdio.h
.o/thing_kill_if.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_kill_if.o: /usr/include/sys/_types/_clock_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_time_t.h
.o/thing_kill_if.o: /usr/include/sys/_types/_timespec.h
.o/thing_kill_if.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_kill_if.o: /usr/include/sys/_types/_wint_t.h
.o/thing_kill_if.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_kill_if.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_kill_if.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_kill_if.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_kill_if.o: my_charmap.h my_dmap.h my_level_static.h
.o/thing_kill_if.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_kill_if.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_kill_if.o: my_thing_ai.h
.o/thing_lava.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_lava.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_lava.o: /usr/include/sys/_posix_availability.h
.o/thing_lava.o: /usr/include/Availability.h
.o/thing_lava.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_lava.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_lava.o: /usr/include/i386/_types.h
.o/thing_lava.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_lava.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_lava.o: /usr/include/sys/_types/_int8_t.h
.o/thing_lava.o: /usr/include/sys/_types/_int16_t.h
.o/thing_lava.o: /usr/include/sys/_types/_int32_t.h
.o/thing_lava.o: /usr/include/sys/_types/_int64_t.h
.o/thing_lava.o: /usr/include/_types/_uint8_t.h
.o/thing_lava.o: /usr/include/_types/_uint16_t.h
.o/thing_lava.o: /usr/include/_types/_uint32_t.h
.o/thing_lava.o: /usr/include/_types/_uint64_t.h
.o/thing_lava.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_lava.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_lava.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_lava.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_lava.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_lava.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_lava.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_lava.o: /usr/include/_types/_intmax_t.h
.o/thing_lava.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_lava.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_lava.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_lava.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_lava.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_lava.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_lava.o: /usr/include/sys/_types/_null.h
.o/thing_lava.o: /usr/include/sys/_types/_size_t.h
.o/thing_lava.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_lava.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_lava.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_lava.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_lava.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_lava.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_lava.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_lava.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_lava.o: /usr/include/sys/_types/_time_t.h
.o/thing_lava.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_lava.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_lava.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_lava.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_lava.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_lava.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_lava.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_lava.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_level_change.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_level_change.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_level_change.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level_change.o: /usr/include/sys/_posix_availability.h
.o/thing_level_change.o: /usr/include/Availability.h
.o/thing_level_change.o: /usr/include/AvailabilityInternal.h
.o/thing_level_change.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/thing_level_change.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/thing_level_change.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_level_change.o: /usr/include/sys/_types.h
.o/thing_level_change.o: /usr/include/machine/_types.h
.o/thing_level_change.o: /usr/include/i386/_types.h
.o/thing_level_change.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level_change.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_level_change.o: /usr/include/stdint.h
.o/thing_level_change.o: /usr/include/sys/_types/_int8_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level_change.o: /usr/include/_types/_uint8_t.h
.o/thing_level_change.o: /usr/include/_types/_uint16_t.h
.o/thing_level_change.o: /usr/include/_types/_uint32_t.h
.o/thing_level_change.o: /usr/include/_types/_uint64_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level_change.o: /usr/include/machine/types.h
.o/thing_level_change.o: /usr/include/i386/types.h
.o/thing_level_change.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level_change.o: /usr/include/_types/_intmax_t.h
.o/thing_level_change.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level_change.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_level_change.o: my_bounds_check.h /usr/include/assert.h
.o/thing_level_change.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_level_change.o: my_string.h /usr/include/wchar.h
.o/thing_level_change.o: /usr/include/sys/_types/_null.h
.o/thing_level_change.o: /usr/include/sys/_types/_size_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_rune_t.h
.o/thing_level_change.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_level_change.o: /usr/include/sys/_types/_va_list.h
.o/thing_level_change.o: /usr/include/sys/stdio.h
.o/thing_level_change.o: /usr/include/sys/_types/_off_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level_change.o: /usr/include/secure/_stdio.h
.o/thing_level_change.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_level_change.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_time_t.h
.o/thing_level_change.o: /usr/include/sys/_types/_timespec.h
.o/thing_level_change.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_level_change.o: /usr/include/sys/_types/_wint_t.h
.o/thing_level_change.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level_change.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_level_change.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_level_change.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_level_change.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_level_change.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_level_change.o: my_color.h my_thing_ai.h my_gl.h
.o/thing_level_enter.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_level_enter.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_level_enter.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level_enter.o: /usr/include/sys/_posix_availability.h
.o/thing_level_enter.o: /usr/include/Availability.h
.o/thing_level_enter.o: /usr/include/AvailabilityInternal.h
.o/thing_level_enter.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/thing_level_enter.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/thing_level_enter.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_level_enter.o: /usr/include/sys/_types.h
.o/thing_level_enter.o: /usr/include/machine/_types.h
.o/thing_level_enter.o: /usr/include/i386/_types.h
.o/thing_level_enter.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level_enter.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_level_enter.o: /usr/include/stdint.h
.o/thing_level_enter.o: /usr/include/sys/_types/_int8_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level_enter.o: /usr/include/_types/_uint8_t.h
.o/thing_level_enter.o: /usr/include/_types/_uint16_t.h
.o/thing_level_enter.o: /usr/include/_types/_uint32_t.h
.o/thing_level_enter.o: /usr/include/_types/_uint64_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level_enter.o: /usr/include/machine/types.h
.o/thing_level_enter.o: /usr/include/i386/types.h
.o/thing_level_enter.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level_enter.o: /usr/include/_types/_intmax_t.h
.o/thing_level_enter.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level_enter.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_level_enter.o: my_bounds_check.h /usr/include/assert.h
.o/thing_level_enter.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_level_enter.o: my_string.h /usr/include/wchar.h
.o/thing_level_enter.o: /usr/include/sys/_types/_null.h
.o/thing_level_enter.o: /usr/include/sys/_types/_size_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_rune_t.h
.o/thing_level_enter.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_level_enter.o: /usr/include/sys/_types/_va_list.h
.o/thing_level_enter.o: /usr/include/sys/stdio.h
.o/thing_level_enter.o: /usr/include/sys/_types/_off_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level_enter.o: /usr/include/secure/_stdio.h
.o/thing_level_enter.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_level_enter.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_time_t.h
.o/thing_level_enter.o: /usr/include/sys/_types/_timespec.h
.o/thing_level_enter.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_level_enter.o: /usr/include/sys/_types/_wint_t.h
.o/thing_level_enter.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level_enter.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_level_enter.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_level_enter.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_level_enter.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_level_enter.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_level_enter.o: my_color.h my_thing_ai.h my_gl.h
.o/thing_level_find.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_level_find.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_level_find.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level_find.o: /usr/include/sys/_posix_availability.h
.o/thing_level_find.o: /usr/include/Availability.h
.o/thing_level_find.o: /usr/include/AvailabilityInternal.h
.o/thing_level_find.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_level_find.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_level_find.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_level_find.o: /usr/include/sys/_types.h
.o/thing_level_find.o: /usr/include/machine/_types.h
.o/thing_level_find.o: /usr/include/i386/_types.h
.o/thing_level_find.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level_find.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_level_find.o: /usr/include/stdint.h
.o/thing_level_find.o: /usr/include/sys/_types/_int8_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level_find.o: /usr/include/_types/_uint8_t.h
.o/thing_level_find.o: /usr/include/_types/_uint16_t.h
.o/thing_level_find.o: /usr/include/_types/_uint32_t.h
.o/thing_level_find.o: /usr/include/_types/_uint64_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level_find.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_level_find.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level_find.o: /usr/include/_types/_intmax_t.h
.o/thing_level_find.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level_find.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_level_find.o: my_bounds_check.h /usr/include/assert.h
.o/thing_level_find.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_level_find.o: my_string.h /usr/include/wchar.h
.o/thing_level_find.o: /usr/include/sys/_types/_null.h
.o/thing_level_find.o: /usr/include/sys/_types/_size_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_level_find.o: /usr/include/_stdio.h
.o/thing_level_find.o: /usr/include/sys/_types/_va_list.h
.o/thing_level_find.o: /usr/include/sys/stdio.h
.o/thing_level_find.o: /usr/include/sys/_types/_off_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level_find.o: /usr/include/secure/_stdio.h
.o/thing_level_find.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_level_find.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_time_t.h
.o/thing_level_find.o: /usr/include/sys/_types/_timespec.h
.o/thing_level_find.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_level_find.o: /usr/include/sys/_types/_wint_t.h
.o/thing_level_find.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level_find.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_level_find.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_level_find.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_level_find.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_level_find.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_level_find.o: my_color.h my_thing_ai.h my_gl.h
.o/thing_level_leave.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_level_leave.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_level_leave.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level_leave.o: /usr/include/sys/_posix_availability.h
.o/thing_level_leave.o: /usr/include/Availability.h
.o/thing_level_leave.o: /usr/include/AvailabilityInternal.h
.o/thing_level_leave.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/thing_level_leave.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/thing_level_leave.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_level_leave.o: /usr/include/sys/_types.h
.o/thing_level_leave.o: /usr/include/machine/_types.h
.o/thing_level_leave.o: /usr/include/i386/_types.h
.o/thing_level_leave.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level_leave.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_level_leave.o: /usr/include/stdint.h
.o/thing_level_leave.o: /usr/include/sys/_types/_int8_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level_leave.o: /usr/include/_types/_uint8_t.h
.o/thing_level_leave.o: /usr/include/_types/_uint16_t.h
.o/thing_level_leave.o: /usr/include/_types/_uint32_t.h
.o/thing_level_leave.o: /usr/include/_types/_uint64_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level_leave.o: /usr/include/machine/types.h
.o/thing_level_leave.o: /usr/include/i386/types.h
.o/thing_level_leave.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level_leave.o: /usr/include/_types/_intmax_t.h
.o/thing_level_leave.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level_leave.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_level_leave.o: my_bounds_check.h /usr/include/assert.h
.o/thing_level_leave.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_level_leave.o: my_string.h /usr/include/wchar.h
.o/thing_level_leave.o: /usr/include/sys/_types/_null.h
.o/thing_level_leave.o: /usr/include/sys/_types/_size_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_rune_t.h
.o/thing_level_leave.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_level_leave.o: /usr/include/sys/_types/_va_list.h
.o/thing_level_leave.o: /usr/include/sys/stdio.h
.o/thing_level_leave.o: /usr/include/sys/_types/_off_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level_leave.o: /usr/include/secure/_stdio.h
.o/thing_level_leave.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_level_leave.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_time_t.h
.o/thing_level_leave.o: /usr/include/sys/_types/_timespec.h
.o/thing_level_leave.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_level_leave.o: /usr/include/sys/_types/_wint_t.h
.o/thing_level_leave.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level_leave.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_level_leave.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_level_leave.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_level_leave.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_level_leave.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_level_leave.o: my_color.h my_thing_ai.h my_gl.h
.o/thing_level_pop.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_level_pop.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_level_pop.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level_pop.o: /usr/include/sys/_posix_availability.h
.o/thing_level_pop.o: /usr/include/Availability.h
.o/thing_level_pop.o: /usr/include/AvailabilityInternal.h
.o/thing_level_pop.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_level_pop.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_level_pop.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_level_pop.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_level_pop.o: /usr/include/i386/_types.h
.o/thing_level_pop.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level_pop.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_level_pop.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level_pop.o: /usr/include/_types/_uint8_t.h
.o/thing_level_pop.o: /usr/include/_types/_uint16_t.h
.o/thing_level_pop.o: /usr/include/_types/_uint32_t.h
.o/thing_level_pop.o: /usr/include/_types/_uint64_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level_pop.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_level_pop.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level_pop.o: /usr/include/_types/_intmax_t.h
.o/thing_level_pop.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level_pop.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_level_pop.o: my_bounds_check.h /usr/include/assert.h
.o/thing_level_pop.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_level_pop.o: my_string.h /usr/include/wchar.h
.o/thing_level_pop.o: /usr/include/sys/_types/_null.h
.o/thing_level_pop.o: /usr/include/sys/_types/_size_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_level_pop.o: /usr/include/_stdio.h
.o/thing_level_pop.o: /usr/include/sys/_types/_va_list.h
.o/thing_level_pop.o: /usr/include/sys/stdio.h
.o/thing_level_pop.o: /usr/include/sys/_types/_off_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level_pop.o: /usr/include/secure/_stdio.h
.o/thing_level_pop.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_level_pop.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_time_t.h
.o/thing_level_pop.o: /usr/include/sys/_types/_timespec.h
.o/thing_level_pop.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_level_pop.o: /usr/include/sys/_types/_wint_t.h
.o/thing_level_pop.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level_pop.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_level_pop.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_level_pop.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_level_pop.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_level_pop.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_level_pop.o: my_color.h my_thing_ai.h my_gl.h
.o/thing_level_push.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_level_push.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_level_push.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level_push.o: /usr/include/sys/_posix_availability.h
.o/thing_level_push.o: /usr/include/Availability.h
.o/thing_level_push.o: /usr/include/AvailabilityInternal.h
.o/thing_level_push.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_level_push.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_level_push.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_level_push.o: /usr/include/sys/_types.h
.o/thing_level_push.o: /usr/include/machine/_types.h
.o/thing_level_push.o: /usr/include/i386/_types.h
.o/thing_level_push.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level_push.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_level_push.o: /usr/include/stdint.h
.o/thing_level_push.o: /usr/include/sys/_types/_int8_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level_push.o: /usr/include/_types/_uint8_t.h
.o/thing_level_push.o: /usr/include/_types/_uint16_t.h
.o/thing_level_push.o: /usr/include/_types/_uint32_t.h
.o/thing_level_push.o: /usr/include/_types/_uint64_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level_push.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_level_push.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level_push.o: /usr/include/_types/_intmax_t.h
.o/thing_level_push.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level_push.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_level_push.o: my_bounds_check.h /usr/include/assert.h
.o/thing_level_push.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_level_push.o: my_string.h /usr/include/wchar.h
.o/thing_level_push.o: /usr/include/sys/_types/_null.h
.o/thing_level_push.o: /usr/include/sys/_types/_size_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_level_push.o: /usr/include/_stdio.h
.o/thing_level_push.o: /usr/include/sys/_types/_va_list.h
.o/thing_level_push.o: /usr/include/sys/stdio.h
.o/thing_level_push.o: /usr/include/sys/_types/_off_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level_push.o: /usr/include/secure/_stdio.h
.o/thing_level_push.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_level_push.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_time_t.h
.o/thing_level_push.o: /usr/include/sys/_types/_timespec.h
.o/thing_level_push.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_level_push.o: /usr/include/sys/_types/_wint_t.h
.o/thing_level_push.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level_push.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_level_push.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_level_push.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_level_push.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_level_push.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_level_push.o: my_color.h my_thing_ai.h my_gl.h
.o/thing_lifespan.o: my_thing.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_lifespan.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_lifespan.o: /usr/include/sys/cdefs.h
.o/thing_lifespan.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_lifespan.o: /usr/include/sys/_posix_availability.h
.o/thing_lifespan.o: /usr/include/Availability.h
.o/thing_lifespan.o: /usr/include/AvailabilityInternal.h
.o/thing_lifespan.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_lifespan.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_lifespan.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_lifespan.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int8_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int16_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int32_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int64_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint8_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint16_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint32_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint64_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_lifespan.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_lifespan.o: /usr/include/_types/_intmax_t.h
.o/thing_lifespan.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_lifespan.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_lifespan.o: my_bounds_check.h /usr/include/assert.h
.o/thing_lifespan.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_lifespan.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_lifespan.o: /usr/include/sys/_types/_null.h
.o/thing_lifespan.o: /usr/include/sys/_types/_size_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_lifespan.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_lifespan.o: /usr/include/sys/stdio.h
.o/thing_lifespan.o: /usr/include/sys/_types/_off_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_lifespan.o: /usr/include/secure/_stdio.h
.o/thing_lifespan.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_lifespan.o: /usr/include/sys/_types/_clock_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_time_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_timespec.h
.o/thing_lifespan.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_lifespan.o: /usr/include/sys/_types/_wint_t.h
.o/thing_lifespan.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_lifespan.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_lifespan.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_lifespan.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_lifespan.o: my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_lifespan.o: my_sprintf.h
.o/thing_light.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_light.o: /usr/include/sys/cdefs.h
.o/thing_light.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_light.o: /usr/include/sys/_posix_availability.h
.o/thing_light.o: /usr/include/Availability.h
.o/thing_light.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_light.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_light.o: /usr/include/i386/_types.h
.o/thing_light.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_light.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_light.o: /usr/include/sys/_types/_int8_t.h
.o/thing_light.o: /usr/include/sys/_types/_int16_t.h
.o/thing_light.o: /usr/include/sys/_types/_int32_t.h
.o/thing_light.o: /usr/include/sys/_types/_int64_t.h
.o/thing_light.o: /usr/include/_types/_uint8_t.h
.o/thing_light.o: /usr/include/_types/_uint16_t.h
.o/thing_light.o: /usr/include/_types/_uint32_t.h
.o/thing_light.o: /usr/include/_types/_uint64_t.h
.o/thing_light.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_light.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_light.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_light.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_light.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_light.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_light.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_light.o: /usr/include/_types/_intmax_t.h
.o/thing_light.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_light.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_light.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_light.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_light.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_light.o: /usr/include/sys/_types/_null.h
.o/thing_light.o: /usr/include/sys/_types/_size_t.h
.o/thing_light.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_light.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_light.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_light.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_light.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_light.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_light.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_light.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_light.o: /usr/include/sys/_types/_time_t.h
.o/thing_light.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_light.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_light.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_light.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_light.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_light.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_light.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_light.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_light.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_light.o: my_game.h my_world.h my_gl.h
.o/thing_location.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_location.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_location.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_location.o: /usr/include/sys/_posix_availability.h
.o/thing_location.o: /usr/include/Availability.h
.o/thing_location.o: /usr/include/AvailabilityInternal.h
.o/thing_location.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_location.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_location.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_location.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_location.o: /usr/include/sys/_types/_int8_t.h
.o/thing_location.o: /usr/include/sys/_types/_int16_t.h
.o/thing_location.o: /usr/include/sys/_types/_int32_t.h
.o/thing_location.o: /usr/include/sys/_types/_int64_t.h
.o/thing_location.o: /usr/include/_types/_uint8_t.h
.o/thing_location.o: /usr/include/_types/_uint16_t.h
.o/thing_location.o: /usr/include/_types/_uint32_t.h
.o/thing_location.o: /usr/include/_types/_uint64_t.h
.o/thing_location.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_location.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_location.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_location.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_location.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_location.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_location.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_location.o: /usr/include/_types/_intmax_t.h
.o/thing_location.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_location.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_location.o: my_bounds_check.h /usr/include/assert.h
.o/thing_location.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_location.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_location.o: my_string.h /usr/include/wchar.h
.o/thing_location.o: /usr/include/sys/_types/_null.h
.o/thing_location.o: /usr/include/sys/_types/_size_t.h
.o/thing_location.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_location.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_location.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_location.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_location.o: /usr/include/sys/stdio.h
.o/thing_location.o: /usr/include/sys/_types/_off_t.h
.o/thing_location.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_location.o: /usr/include/secure/_stdio.h
.o/thing_location.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_location.o: /usr/include/sys/_types/_clock_t.h
.o/thing_location.o: /usr/include/sys/_types/_time_t.h
.o/thing_location.o: /usr/include/sys/_types/_timespec.h
.o/thing_location.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_location.o: /usr/include/sys/_types/_wint_t.h
.o/thing_location.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_location.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_location.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_location.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_location.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_location.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_location.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_location.o: my_thing_ai.h my_sprintf.h
.o/thing_log.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_log.o: /usr/include/sys/_posix_availability.h
.o/thing_log.o: /usr/include/Availability.h
.o/thing_log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_log.o: /usr/include/i386/_types.h
.o/thing_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_log.o: /usr/include/sys/_types/_int8_t.h
.o/thing_log.o: /usr/include/sys/_types/_int16_t.h
.o/thing_log.o: /usr/include/sys/_types/_int32_t.h
.o/thing_log.o: /usr/include/sys/_types/_int64_t.h
.o/thing_log.o: /usr/include/_types/_uint8_t.h
.o/thing_log.o: /usr/include/_types/_uint16_t.h
.o/thing_log.o: /usr/include/_types/_uint32_t.h
.o/thing_log.o: /usr/include/_types/_uint64_t.h
.o/thing_log.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_log.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_log.o: /usr/include/_types/_intmax_t.h
.o/thing_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_log.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_log.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_log.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_log.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_log.o: /usr/include/sys/_types/_null.h
.o/thing_log.o: /usr/include/sys/_types/_size_t.h
.o/thing_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_log.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_log.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_log.o: /usr/include/sys/_types/_time_t.h
.o/thing_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_log.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_log.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_log.o: my_dungeon_grid.h my_traceback.h my_console.h
.o/thing_log.o: my_wid_console.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/thing_log.o: my_color.h my_wid_tiles.h my_thing.h my_light.h
.o/thing_log.o: my_thing_template.h my_dice.h my_thing_ai.h my_wid_minicon.h
.o/thing_log.o: my_wid_botcon.h my_log.h
.o/thing_lunge.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_lunge.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_lunge.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_lunge.o: /usr/include/sys/_posix_availability.h
.o/thing_lunge.o: /usr/include/Availability.h
.o/thing_lunge.o: /usr/include/AvailabilityInternal.h
.o/thing_lunge.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_lunge.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_lunge.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_lunge.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_lunge.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_lunge.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_lunge.o: /usr/include/sys/_types/_int8_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_int16_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_int32_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_int64_t.h
.o/thing_lunge.o: /usr/include/_types/_uint8_t.h
.o/thing_lunge.o: /usr/include/_types/_uint16_t.h
.o/thing_lunge.o: /usr/include/_types/_uint32_t.h
.o/thing_lunge.o: /usr/include/_types/_uint64_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_lunge.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_lunge.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_lunge.o: /usr/include/_types/_intmax_t.h
.o/thing_lunge.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_lunge.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_lunge.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/thing_lunge.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_lunge.o: /usr/include/sys/_types/_null.h
.o/thing_lunge.o: /usr/include/sys/_types/_size_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_lunge.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_lunge.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_lunge.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_lunge.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_time_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_lunge.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_lunge.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_lunge.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_lunge.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_lunge.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_lunge.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/thing_lunge.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_lunge.o: my_thing_ai.h my_sprintf.h my_gl.h
.o/thing_match.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_match.o: /usr/include/sys/cdefs.h
.o/thing_match.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_match.o: /usr/include/sys/_posix_availability.h
.o/thing_match.o: /usr/include/Availability.h
.o/thing_match.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_match.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_match.o: /usr/include/i386/_types.h
.o/thing_match.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_match.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_match.o: /usr/include/sys/_types/_int8_t.h
.o/thing_match.o: /usr/include/sys/_types/_int16_t.h
.o/thing_match.o: /usr/include/sys/_types/_int32_t.h
.o/thing_match.o: /usr/include/sys/_types/_int64_t.h
.o/thing_match.o: /usr/include/_types/_uint8_t.h
.o/thing_match.o: /usr/include/_types/_uint16_t.h
.o/thing_match.o: /usr/include/_types/_uint32_t.h
.o/thing_match.o: /usr/include/_types/_uint64_t.h
.o/thing_match.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_match.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_match.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_match.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_match.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_match.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_match.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_match.o: /usr/include/_types/_intmax_t.h
.o/thing_match.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_match.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_match.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_match.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_match.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_match.o: /usr/include/sys/_types/_null.h
.o/thing_match.o: /usr/include/sys/_types/_size_t.h
.o/thing_match.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_match.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_match.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_match.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_match.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_match.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_match.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_match.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_match.o: /usr/include/sys/_types/_time_t.h
.o/thing_match.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_match.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_match.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_match.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_match.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_match.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_match.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_match.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_match.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_move.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_move.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_move.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_move.o: /usr/include/sys/_posix_availability.h
.o/thing_move.o: /usr/include/Availability.h
.o/thing_move.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/thing_move.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_move.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/thing_move.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_move.o: /usr/include/i386/_types.h
.o/thing_move.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_move.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_move.o: /usr/include/sys/_types/_int8_t.h
.o/thing_move.o: /usr/include/sys/_types/_int16_t.h
.o/thing_move.o: /usr/include/sys/_types/_int32_t.h
.o/thing_move.o: /usr/include/sys/_types/_int64_t.h
.o/thing_move.o: /usr/include/_types/_uint8_t.h
.o/thing_move.o: /usr/include/_types/_uint16_t.h
.o/thing_move.o: /usr/include/_types/_uint32_t.h
.o/thing_move.o: /usr/include/_types/_uint64_t.h
.o/thing_move.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_move.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_move.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_move.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_move.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_move.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_move.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_move.o: /usr/include/_types/_intmax_t.h
.o/thing_move.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_move.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_move.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/thing_move.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_move.o: /usr/include/sys/_types/_null.h
.o/thing_move.o: /usr/include/sys/_types/_size_t.h
.o/thing_move.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_move.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_move.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_move.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_move.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_move.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_move.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_move.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_move.o: /usr/include/sys/_types/_time_t.h
.o/thing_move.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_move.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_move.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_move.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_move.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_move.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_move.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_move.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_move.o: my_gl.h my_wid_thing_collect.h my_wid.h my_ascii.h my_tex.h
.o/thing_move.o: my_wid_tiles.h my_wid_popup.h my_wid_text_box.h
.o/thing_move_dir.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_move_dir.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_move_dir.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_move_dir.o: /usr/include/sys/_posix_availability.h
.o/thing_move_dir.o: /usr/include/Availability.h
.o/thing_move_dir.o: /usr/include/AvailabilityInternal.h
.o/thing_move_dir.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_move_dir.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_move_dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_move_dir.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_move_dir.o: /usr/include/sys/_types/_int8_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_int16_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_int32_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_int64_t.h
.o/thing_move_dir.o: /usr/include/_types/_uint8_t.h
.o/thing_move_dir.o: /usr/include/_types/_uint16_t.h
.o/thing_move_dir.o: /usr/include/_types/_uint32_t.h
.o/thing_move_dir.o: /usr/include/_types/_uint64_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_move_dir.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_move_dir.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_move_dir.o: /usr/include/_types/_intmax_t.h
.o/thing_move_dir.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_move_dir.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_move_dir.o: my_bounds_check.h /usr/include/assert.h
.o/thing_move_dir.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_move_dir.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_move_dir.o: my_string.h /usr/include/wchar.h
.o/thing_move_dir.o: /usr/include/sys/_types/_null.h
.o/thing_move_dir.o: /usr/include/sys/_types/_size_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_move_dir.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_move_dir.o: /usr/include/sys/stdio.h
.o/thing_move_dir.o: /usr/include/sys/_types/_off_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_move_dir.o: /usr/include/secure/_stdio.h
.o/thing_move_dir.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_move_dir.o: /usr/include/sys/_types/_clock_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_time_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_timespec.h
.o/thing_move_dir.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_move_dir.o: /usr/include/sys/_types/_wint_t.h
.o/thing_move_dir.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_move_dir.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_move_dir.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_move_dir.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_move_dir.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_move_dir.o: my_dungeon_grid.h my_color.h my_thing.h my_light.h
.o/thing_move_dir.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_msg.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_msg.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_msg.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_msg.o: /usr/include/sys/_posix_availability.h
.o/thing_msg.o: /usr/include/Availability.h
.o/thing_msg.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_msg.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_msg.o: /usr/include/i386/_types.h
.o/thing_msg.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_msg.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_msg.o: /usr/include/sys/_types/_int8_t.h
.o/thing_msg.o: /usr/include/sys/_types/_int16_t.h
.o/thing_msg.o: /usr/include/sys/_types/_int32_t.h
.o/thing_msg.o: /usr/include/sys/_types/_int64_t.h
.o/thing_msg.o: /usr/include/_types/_uint8_t.h
.o/thing_msg.o: /usr/include/_types/_uint16_t.h
.o/thing_msg.o: /usr/include/_types/_uint32_t.h
.o/thing_msg.o: /usr/include/_types/_uint64_t.h
.o/thing_msg.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_msg.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_msg.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_msg.o: /usr/include/_types/_intmax_t.h
.o/thing_msg.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_msg.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_msg.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_msg.o: c_plus_plus_serializer.h my_command.h my_token.h my_string.h
.o/thing_msg.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_msg.o: /usr/include/sys/_types/_size_t.h
.o/thing_msg.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_msg.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_msg.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_msg.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_msg.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_msg.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_msg.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_msg.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_msg.o: /usr/include/sys/_types/_time_t.h
.o/thing_msg.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_msg.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_msg.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_msg.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_msg.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_msg.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_msg.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_msg.o: my_thing.h my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_msg.o: my_color.h my_thing_ai.h my_sprintf.h
.o/thing_nearby.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_nearby.o: /usr/include/sys/cdefs.h
.o/thing_nearby.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_nearby.o: /usr/include/sys/_posix_availability.h
.o/thing_nearby.o: /usr/include/Availability.h
.o/thing_nearby.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_nearby.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_nearby.o: /usr/include/i386/_types.h
.o/thing_nearby.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_nearby.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_nearby.o: /usr/include/sys/_types/_int8_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_int16_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_int32_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_int64_t.h
.o/thing_nearby.o: /usr/include/_types/_uint8_t.h
.o/thing_nearby.o: /usr/include/_types/_uint16_t.h
.o/thing_nearby.o: /usr/include/_types/_uint32_t.h
.o/thing_nearby.o: /usr/include/_types/_uint64_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_nearby.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_nearby.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_nearby.o: /usr/include/_types/_intmax_t.h
.o/thing_nearby.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_nearby.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_nearby.o: my_bounds_check.h /usr/include/assert.h
.o/thing_nearby.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_nearby.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_nearby.o: my_string.h /usr/include/wchar.h
.o/thing_nearby.o: /usr/include/sys/_types/_null.h
.o/thing_nearby.o: /usr/include/sys/_types/_size_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_nearby.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_nearby.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_nearby.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_nearby.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_time_t.h
.o/thing_nearby.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_nearby.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_nearby.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_nearby.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_nearby.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_nearby.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_nearby.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_nearby.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_nearby.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_obstacle.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_obstacle.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_obstacle.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_obstacle.o: /usr/include/sys/_posix_availability.h
.o/thing_obstacle.o: /usr/include/Availability.h
.o/thing_obstacle.o: /usr/include/AvailabilityInternal.h
.o/thing_obstacle.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_obstacle.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_obstacle.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_obstacle.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_obstacle.o: /usr/include/sys/_types/_int8_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_int16_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_int32_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_int64_t.h
.o/thing_obstacle.o: /usr/include/_types/_uint8_t.h
.o/thing_obstacle.o: /usr/include/_types/_uint16_t.h
.o/thing_obstacle.o: /usr/include/_types/_uint32_t.h
.o/thing_obstacle.o: /usr/include/_types/_uint64_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_obstacle.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_obstacle.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_obstacle.o: /usr/include/_types/_intmax_t.h
.o/thing_obstacle.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_obstacle.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_obstacle.o: my_bounds_check.h /usr/include/assert.h
.o/thing_obstacle.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_obstacle.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_obstacle.o: my_string.h /usr/include/wchar.h
.o/thing_obstacle.o: /usr/include/sys/_types/_null.h
.o/thing_obstacle.o: /usr/include/sys/_types/_size_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_obstacle.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_obstacle.o: /usr/include/sys/stdio.h
.o/thing_obstacle.o: /usr/include/sys/_types/_off_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_obstacle.o: /usr/include/secure/_stdio.h
.o/thing_obstacle.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_obstacle.o: /usr/include/sys/_types/_clock_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_time_t.h
.o/thing_obstacle.o: /usr/include/sys/_types/_timespec.h
.o/thing_obstacle.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_obstacle.o: /usr/include/sys/_types/_wint_t.h
.o/thing_obstacle.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_obstacle.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_obstacle.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_obstacle.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_obstacle.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_obstacle.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_obstacle.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_obstacle.o: my_thing_ai.h
.o/thing_on_fire.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_on_fire.o: /usr/include/sys/cdefs.h
.o/thing_on_fire.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_on_fire.o: /usr/include/sys/_posix_availability.h
.o/thing_on_fire.o: /usr/include/Availability.h
.o/thing_on_fire.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_on_fire.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_on_fire.o: /usr/include/i386/_types.h
.o/thing_on_fire.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_on_fire.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_on_fire.o: /usr/include/sys/_types/_int8_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_int16_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_int32_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_int64_t.h
.o/thing_on_fire.o: /usr/include/_types/_uint8_t.h
.o/thing_on_fire.o: /usr/include/_types/_uint16_t.h
.o/thing_on_fire.o: /usr/include/_types/_uint32_t.h
.o/thing_on_fire.o: /usr/include/_types/_uint64_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_on_fire.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_on_fire.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_on_fire.o: /usr/include/_types/_intmax_t.h
.o/thing_on_fire.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_on_fire.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_on_fire.o: my_bounds_check.h /usr/include/assert.h
.o/thing_on_fire.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_on_fire.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_on_fire.o: my_string.h /usr/include/wchar.h
.o/thing_on_fire.o: /usr/include/sys/_types/_null.h
.o/thing_on_fire.o: /usr/include/sys/_types/_size_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_on_fire.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_on_fire.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_on_fire.o: /usr/include/secure/_stdio.h
.o/thing_on_fire.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_on_fire.o: /usr/include/sys/_types/_clock_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_time_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_timespec.h
.o/thing_on_fire.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_on_fire.o: /usr/include/sys/_types/_wint_t.h
.o/thing_on_fire.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_on_fire.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_on_fire.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_on_fire.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_on_fire.o: my_charmap.h my_dmap.h my_level_static.h
.o/thing_on_fire.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_on_fire.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_on_fire.o: my_thing_ai.h my_sprintf.h
.o/thing_owner.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_owner.o: /usr/include/sys/cdefs.h
.o/thing_owner.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_owner.o: /usr/include/sys/_posix_availability.h
.o/thing_owner.o: /usr/include/Availability.h
.o/thing_owner.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_owner.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_owner.o: /usr/include/i386/_types.h
.o/thing_owner.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_owner.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_owner.o: /usr/include/sys/_types/_int8_t.h
.o/thing_owner.o: /usr/include/sys/_types/_int16_t.h
.o/thing_owner.o: /usr/include/sys/_types/_int32_t.h
.o/thing_owner.o: /usr/include/sys/_types/_int64_t.h
.o/thing_owner.o: /usr/include/_types/_uint8_t.h
.o/thing_owner.o: /usr/include/_types/_uint16_t.h
.o/thing_owner.o: /usr/include/_types/_uint32_t.h
.o/thing_owner.o: /usr/include/_types/_uint64_t.h
.o/thing_owner.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_owner.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_owner.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_owner.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_owner.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_owner.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_owner.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_owner.o: /usr/include/_types/_intmax_t.h
.o/thing_owner.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_owner.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_owner.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_owner.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_owner.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_owner.o: /usr/include/sys/_types/_null.h
.o/thing_owner.o: /usr/include/sys/_types/_size_t.h
.o/thing_owner.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_owner.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_owner.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_owner.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_owner.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_owner.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_owner.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_owner.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_owner.o: /usr/include/sys/_types/_time_t.h
.o/thing_owner.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_owner.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_owner.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_owner.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_owner.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_owner.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_owner.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_owner.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_owner.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_path.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_path.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_path.o: /usr/include/sys/_posix_availability.h
.o/thing_path.o: /usr/include/Availability.h
.o/thing_path.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_path.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_path.o: /usr/include/i386/_types.h
.o/thing_path.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_path.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_path.o: /usr/include/sys/_types/_int8_t.h
.o/thing_path.o: /usr/include/sys/_types/_int16_t.h
.o/thing_path.o: /usr/include/sys/_types/_int32_t.h
.o/thing_path.o: /usr/include/sys/_types/_int64_t.h
.o/thing_path.o: /usr/include/_types/_uint8_t.h
.o/thing_path.o: /usr/include/_types/_uint16_t.h
.o/thing_path.o: /usr/include/_types/_uint32_t.h
.o/thing_path.o: /usr/include/_types/_uint64_t.h
.o/thing_path.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_path.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_path.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_path.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_path.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_path.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_path.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_path.o: /usr/include/_types/_intmax_t.h
.o/thing_path.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_path.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_path.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_path.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_path.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_path.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_path.o: /usr/include/sys/_types/_null.h
.o/thing_path.o: /usr/include/sys/_types/_size_t.h
.o/thing_path.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_path.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_path.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_path.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_path.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_path.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_path.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_path.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_path.o: /usr/include/sys/_types/_time_t.h
.o/thing_path.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_path.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_path.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_path.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_path.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_path.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_path.o: my_dungeon_grid.h my_wid_console.h my_wid.h my_ascii.h
.o/thing_path.o: my_tex.h my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/thing_path.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_place.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_place.o: /usr/include/sys/cdefs.h
.o/thing_place.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_place.o: /usr/include/sys/_posix_availability.h
.o/thing_place.o: /usr/include/Availability.h
.o/thing_place.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_place.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_place.o: /usr/include/i386/_types.h
.o/thing_place.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_place.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_place.o: /usr/include/sys/_types/_int8_t.h
.o/thing_place.o: /usr/include/sys/_types/_int16_t.h
.o/thing_place.o: /usr/include/sys/_types/_int32_t.h
.o/thing_place.o: /usr/include/sys/_types/_int64_t.h
.o/thing_place.o: /usr/include/_types/_uint8_t.h
.o/thing_place.o: /usr/include/_types/_uint16_t.h
.o/thing_place.o: /usr/include/_types/_uint32_t.h
.o/thing_place.o: /usr/include/_types/_uint64_t.h
.o/thing_place.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_place.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_place.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_place.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_place.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_place.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_place.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_place.o: /usr/include/_types/_intmax_t.h
.o/thing_place.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_place.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_place.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_place.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_place.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_place.o: /usr/include/sys/_types/_null.h
.o/thing_place.o: /usr/include/sys/_types/_size_t.h
.o/thing_place.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_place.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_place.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_place.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_place.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_place.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_place.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_place.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_place.o: /usr/include/sys/_types/_time_t.h
.o/thing_place.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_place.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_place.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_place.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_place.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_place.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_place.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_place.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_place.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_rest.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_rest.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_rest.o: /usr/include/sys/_posix_availability.h
.o/thing_rest.o: /usr/include/Availability.h
.o/thing_rest.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_rest.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_rest.o: /usr/include/i386/_types.h
.o/thing_rest.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_rest.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_rest.o: /usr/include/sys/_types/_int8_t.h
.o/thing_rest.o: /usr/include/sys/_types/_int16_t.h
.o/thing_rest.o: /usr/include/sys/_types/_int32_t.h
.o/thing_rest.o: /usr/include/sys/_types/_int64_t.h
.o/thing_rest.o: /usr/include/_types/_uint8_t.h
.o/thing_rest.o: /usr/include/_types/_uint16_t.h
.o/thing_rest.o: /usr/include/_types/_uint32_t.h
.o/thing_rest.o: /usr/include/_types/_uint64_t.h
.o/thing_rest.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_rest.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_rest.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_rest.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_rest.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_rest.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_rest.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_rest.o: /usr/include/_types/_intmax_t.h
.o/thing_rest.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_rest.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_rest.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_rest.o: c_plus_plus_serializer.h my_tile.h my_sdl.h my_command.h
.o/thing_rest.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_rest.o: /usr/include/sys/_types/_null.h
.o/thing_rest.o: /usr/include/sys/_types/_size_t.h
.o/thing_rest.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_rest.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_rest.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_rest.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_rest.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_rest.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_rest.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_rest.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_rest.o: /usr/include/sys/_types/_time_t.h
.o/thing_rest.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_rest.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_rest.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_rest.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_rest.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_rest.o: my_thing.h my_time.h my_light.h my_thing_template.h
.o/thing_rest.o: my_dice.h my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_resurrect.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_resurrect.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_resurrect.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_resurrect.o: /usr/include/sys/_posix_availability.h
.o/thing_resurrect.o: /usr/include/Availability.h
.o/thing_resurrect.o: /usr/include/AvailabilityInternal.h
.o/thing_resurrect.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_resurrect.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_resurrect.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_resurrect.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_resurrect.o: /usr/include/i386/_types.h
.o/thing_resurrect.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_resurrect.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_resurrect.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_int16_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_int32_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_int64_t.h
.o/thing_resurrect.o: /usr/include/_types/_uint8_t.h
.o/thing_resurrect.o: /usr/include/_types/_uint16_t.h
.o/thing_resurrect.o: /usr/include/_types/_uint32_t.h
.o/thing_resurrect.o: /usr/include/_types/_uint64_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_resurrect.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_resurrect.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_resurrect.o: /usr/include/_types/_intmax_t.h
.o/thing_resurrect.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_resurrect.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_resurrect.o: my_bounds_check.h /usr/include/assert.h
.o/thing_resurrect.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_resurrect.o: my_string.h /usr/include/wchar.h
.o/thing_resurrect.o: /usr/include/sys/_types/_null.h
.o/thing_resurrect.o: /usr/include/sys/_types/_size_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_resurrect.o: /usr/include/_stdio.h
.o/thing_resurrect.o: /usr/include/sys/_types/_va_list.h
.o/thing_resurrect.o: /usr/include/sys/stdio.h
.o/thing_resurrect.o: /usr/include/sys/_types/_off_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_resurrect.o: /usr/include/secure/_stdio.h
.o/thing_resurrect.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_resurrect.o: /usr/include/sys/_types/_clock_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_time_t.h
.o/thing_resurrect.o: /usr/include/sys/_types/_timespec.h
.o/thing_resurrect.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_resurrect.o: /usr/include/sys/_types/_wint_t.h
.o/thing_resurrect.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_resurrect.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_resurrect.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_resurrect.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_resurrect.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_resurrect.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_resurrect.o: my_color.h my_thing_ai.h my_sprintf.h
.o/thing_shove.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_shove.o: /usr/include/sys/cdefs.h
.o/thing_shove.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_shove.o: /usr/include/sys/_posix_availability.h
.o/thing_shove.o: /usr/include/Availability.h
.o/thing_shove.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_shove.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_shove.o: /usr/include/i386/_types.h
.o/thing_shove.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_shove.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_shove.o: /usr/include/sys/_types/_int8_t.h
.o/thing_shove.o: /usr/include/sys/_types/_int16_t.h
.o/thing_shove.o: /usr/include/sys/_types/_int32_t.h
.o/thing_shove.o: /usr/include/sys/_types/_int64_t.h
.o/thing_shove.o: /usr/include/_types/_uint8_t.h
.o/thing_shove.o: /usr/include/_types/_uint16_t.h
.o/thing_shove.o: /usr/include/_types/_uint32_t.h
.o/thing_shove.o: /usr/include/_types/_uint64_t.h
.o/thing_shove.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_shove.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_shove.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_shove.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_shove.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_shove.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_shove.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_shove.o: /usr/include/_types/_intmax_t.h
.o/thing_shove.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_shove.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_shove.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_shove.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_shove.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_shove.o: /usr/include/sys/_types/_null.h
.o/thing_shove.o: /usr/include/sys/_types/_size_t.h
.o/thing_shove.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_shove.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_shove.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_shove.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_shove.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_shove.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_shove.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_shove.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_shove.o: /usr/include/sys/_types/_time_t.h
.o/thing_shove.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_shove.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_shove.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_shove.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_shove.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_shove.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_shove.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_shove.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_shove.o: my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_spawn.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_spawn.o: /usr/include/sys/cdefs.h
.o/thing_spawn.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_spawn.o: /usr/include/sys/_posix_availability.h
.o/thing_spawn.o: /usr/include/Availability.h
.o/thing_spawn.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_spawn.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_spawn.o: /usr/include/i386/_types.h
.o/thing_spawn.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_spawn.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_spawn.o: /usr/include/sys/_types/_int8_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_int16_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_int32_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_int64_t.h
.o/thing_spawn.o: /usr/include/_types/_uint8_t.h
.o/thing_spawn.o: /usr/include/_types/_uint16_t.h
.o/thing_spawn.o: /usr/include/_types/_uint32_t.h
.o/thing_spawn.o: /usr/include/_types/_uint64_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_spawn.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_spawn.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_spawn.o: /usr/include/_types/_intmax_t.h
.o/thing_spawn.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_spawn.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_spawn.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_spawn.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_spawn.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_spawn.o: /usr/include/sys/_types/_null.h
.o/thing_spawn.o: /usr/include/sys/_types/_size_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_spawn.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_spawn.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_spawn.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_spawn.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_time_t.h
.o/thing_spawn.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_spawn.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_spawn.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_spawn.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_spawn.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_spawn.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_spawn.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_spawn.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_spawn.o: my_tile.h my_color.h my_thing_ai.h
.o/thing_stamina.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_stamina.o: /usr/include/sys/cdefs.h
.o/thing_stamina.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_stamina.o: /usr/include/sys/_posix_availability.h
.o/thing_stamina.o: /usr/include/Availability.h
.o/thing_stamina.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_stamina.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_stamina.o: /usr/include/i386/_types.h
.o/thing_stamina.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_stamina.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_stamina.o: /usr/include/sys/_types/_int8_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_int16_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_int32_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_int64_t.h
.o/thing_stamina.o: /usr/include/_types/_uint8_t.h
.o/thing_stamina.o: /usr/include/_types/_uint16_t.h
.o/thing_stamina.o: /usr/include/_types/_uint32_t.h
.o/thing_stamina.o: /usr/include/_types/_uint64_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_stamina.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_stamina.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_stamina.o: /usr/include/_types/_intmax_t.h
.o/thing_stamina.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_stamina.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_stamina.o: my_bounds_check.h /usr/include/assert.h
.o/thing_stamina.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_stamina.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/thing_stamina.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/thing_stamina.o: /usr/include/sys/_types/_size_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_stamina.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_stamina.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_stamina.o: /usr/include/secure/_stdio.h
.o/thing_stamina.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_stamina.o: /usr/include/sys/_types/_clock_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_time_t.h
.o/thing_stamina.o: /usr/include/sys/_types/_timespec.h
.o/thing_stamina.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_stamina.o: /usr/include/sys/_types/_wint_t.h
.o/thing_stamina.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_stamina.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_stamina.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_stamina.o: my_thing.h my_time.h my_light.h my_thing_template.h
.o/thing_stamina.o: my_dice.h my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_steal.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_steal.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_steal.o: /usr/include/sys/cdefs.h
.o/thing_steal.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_steal.o: /usr/include/sys/_posix_availability.h
.o/thing_steal.o: /usr/include/Availability.h
.o/thing_steal.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_steal.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_steal.o: /usr/include/i386/_types.h
.o/thing_steal.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_steal.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_steal.o: /usr/include/sys/_types/_int8_t.h
.o/thing_steal.o: /usr/include/sys/_types/_int16_t.h
.o/thing_steal.o: /usr/include/sys/_types/_int32_t.h
.o/thing_steal.o: /usr/include/sys/_types/_int64_t.h
.o/thing_steal.o: /usr/include/_types/_uint8_t.h
.o/thing_steal.o: /usr/include/_types/_uint16_t.h
.o/thing_steal.o: /usr/include/_types/_uint32_t.h
.o/thing_steal.o: /usr/include/_types/_uint64_t.h
.o/thing_steal.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_steal.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_steal.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_steal.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_steal.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_steal.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_steal.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_steal.o: /usr/include/_types/_intmax_t.h
.o/thing_steal.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_steal.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_steal.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_steal.o: c_plus_plus_serializer.h my_command.h my_token.h
.o/thing_steal.o: my_string.h /usr/include/wchar.h
.o/thing_steal.o: /usr/include/sys/_types/_null.h
.o/thing_steal.o: /usr/include/sys/_types/_size_t.h
.o/thing_steal.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_steal.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_steal.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_steal.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_steal.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_steal.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_steal.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_steal.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_steal.o: /usr/include/sys/_types/_time_t.h
.o/thing_steal.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_steal.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_steal.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_steal.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_steal.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_steal.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_steal.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_steal.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_steal.o: my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_steal.o: my_wid_rightbar.h my_wid.h my_ascii.h my_tex.h
.o/thing_steal.o: my_wid_tiles.h
.o/thing_string.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_string.o: /usr/include/sys/cdefs.h
.o/thing_string.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_string.o: /usr/include/sys/_posix_availability.h
.o/thing_string.o: /usr/include/Availability.h
.o/thing_string.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_string.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_string.o: /usr/include/i386/_types.h
.o/thing_string.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_string.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_string.o: /usr/include/sys/_types/_int8_t.h
.o/thing_string.o: /usr/include/sys/_types/_int16_t.h
.o/thing_string.o: /usr/include/sys/_types/_int32_t.h
.o/thing_string.o: /usr/include/sys/_types/_int64_t.h
.o/thing_string.o: /usr/include/_types/_uint8_t.h
.o/thing_string.o: /usr/include/_types/_uint16_t.h
.o/thing_string.o: /usr/include/_types/_uint32_t.h
.o/thing_string.o: /usr/include/_types/_uint64_t.h
.o/thing_string.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_string.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_string.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_string.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_string.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_string.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_string.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_string.o: /usr/include/_types/_intmax_t.h
.o/thing_string.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_string.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_string.o: my_bounds_check.h /usr/include/assert.h
.o/thing_string.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_string.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_string.o: my_string.h /usr/include/wchar.h
.o/thing_string.o: /usr/include/sys/_types/_null.h
.o/thing_string.o: /usr/include/sys/_types/_size_t.h
.o/thing_string.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_string.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_string.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_string.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_string.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_string.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_string.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_string.o: /usr/include/sys/_types/_time_t.h
.o/thing_string.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_string.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_string.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_string.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_string.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_string.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_string.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_string.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_template.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_template.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_template.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_template.o: /usr/include/sys/_posix_availability.h
.o/thing_template.o: /usr/include/Availability.h
.o/thing_template.o: /usr/include/AvailabilityInternal.h
.o/thing_template.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_template.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_template.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_template.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_template.o: /usr/include/sys/_types/_int8_t.h
.o/thing_template.o: /usr/include/sys/_types/_int16_t.h
.o/thing_template.o: /usr/include/sys/_types/_int32_t.h
.o/thing_template.o: /usr/include/sys/_types/_int64_t.h
.o/thing_template.o: /usr/include/_types/_uint8_t.h
.o/thing_template.o: /usr/include/_types/_uint16_t.h
.o/thing_template.o: /usr/include/_types/_uint32_t.h
.o/thing_template.o: /usr/include/_types/_uint64_t.h
.o/thing_template.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_template.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_template.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_template.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_template.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_template.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_template.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_template.o: /usr/include/_types/_intmax_t.h
.o/thing_template.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_template.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_template.o: my_bounds_check.h /usr/include/assert.h
.o/thing_template.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_template.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_template.o: my_string.h /usr/include/wchar.h
.o/thing_template.o: /usr/include/sys/_types/_null.h
.o/thing_template.o: /usr/include/sys/_types/_size_t.h
.o/thing_template.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_template.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_template.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_template.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_template.o: /usr/include/sys/stdio.h
.o/thing_template.o: /usr/include/sys/_types/_off_t.h
.o/thing_template.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_template.o: /usr/include/secure/_stdio.h
.o/thing_template.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_template.o: /usr/include/sys/_types/_clock_t.h
.o/thing_template.o: /usr/include/sys/_types/_time_t.h
.o/thing_template.o: /usr/include/sys/_types/_timespec.h
.o/thing_template.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_template.o: /usr/include/sys/_types/_wint_t.h
.o/thing_template.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_template.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_template.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_template.o: my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_template.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_template.o: my_dungeon_grid.h my_thing_template.h my_dice.h
.o/thing_template.o: my_tile.h my_color.h
.o/thing_template_api.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_template_api.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/thing_template_api.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_template_api.o: /usr/include/sys/_posix_availability.h
.o/thing_template_api.o: /usr/include/Availability.h
.o/thing_template_api.o: /usr/include/AvailabilityInternal.h
.o/thing_template_api.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_template_api.o: /usr/include/machine/_types.h
.o/thing_template_api.o: /usr/include/i386/_types.h
.o/thing_template_api.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_template_api.o: /usr/include/sys/_types/_wchar_t.h
.o/thing_template_api.o: /usr/include/stdint.h
.o/thing_template_api.o: /usr/include/sys/_types/_int8_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_int16_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_int32_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_int64_t.h
.o/thing_template_api.o: /usr/include/_types/_uint8_t.h
.o/thing_template_api.o: /usr/include/_types/_uint16_t.h
.o/thing_template_api.o: /usr/include/_types/_uint32_t.h
.o/thing_template_api.o: /usr/include/_types/_uint64_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_template_api.o: /usr/include/machine/types.h
.o/thing_template_api.o: /usr/include/i386/types.h
.o/thing_template_api.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_template_api.o: /usr/include/_types/_intmax_t.h
.o/thing_template_api.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_template_api.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_template_api.o: my_bounds_check.h /usr/include/assert.h
.o/thing_template_api.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_template_api.o: my_level.h my_time.h my_sdl.h my_command.h
.o/thing_template_api.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_template_api.o: /usr/include/sys/_types/_null.h
.o/thing_template_api.o: /usr/include/sys/_types/_size_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_rune_t.h
.o/thing_template_api.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_template_api.o: /usr/include/sys/_types/_va_list.h
.o/thing_template_api.o: /usr/include/sys/stdio.h
.o/thing_template_api.o: /usr/include/sys/_types/_off_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_template_api.o: /usr/include/secure/_stdio.h
.o/thing_template_api.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_template_api.o: /usr/include/sys/_types/_clock_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_time_t.h
.o/thing_template_api.o: /usr/include/sys/_types/_timespec.h
.o/thing_template_api.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_template_api.o: /usr/include/sys/_types/_wint_t.h
.o/thing_template_api.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_template_api.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_template_api.o: my_particle.h my_point.h my_math.h
.o/thing_template_api.o: /usr/include/math.h my_size.h my_thing_id.h
.o/thing_template_api.o: my_dungeon.h my_room.h my_depth.h my_charmap.h
.o/thing_template_api.o: my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_template_api.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_terrain.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_terrain.o: /usr/include/sys/cdefs.h
.o/thing_terrain.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_terrain.o: /usr/include/sys/_posix_availability.h
.o/thing_terrain.o: /usr/include/Availability.h
.o/thing_terrain.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_terrain.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_terrain.o: /usr/include/i386/_types.h
.o/thing_terrain.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_terrain.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_terrain.o: /usr/include/sys/_types/_int8_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_int16_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_int32_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_int64_t.h
.o/thing_terrain.o: /usr/include/_types/_uint8_t.h
.o/thing_terrain.o: /usr/include/_types/_uint16_t.h
.o/thing_terrain.o: /usr/include/_types/_uint32_t.h
.o/thing_terrain.o: /usr/include/_types/_uint64_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_terrain.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_terrain.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_terrain.o: /usr/include/_types/_intmax_t.h
.o/thing_terrain.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_terrain.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_terrain.o: my_bounds_check.h /usr/include/assert.h
.o/thing_terrain.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_terrain.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_terrain.o: my_string.h /usr/include/wchar.h
.o/thing_terrain.o: /usr/include/sys/_types/_null.h
.o/thing_terrain.o: /usr/include/sys/_types/_size_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_terrain.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_terrain.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_terrain.o: /usr/include/secure/_stdio.h
.o/thing_terrain.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_terrain.o: /usr/include/sys/_types/_clock_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_time_t.h
.o/thing_terrain.o: /usr/include/sys/_types/_timespec.h
.o/thing_terrain.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_terrain.o: /usr/include/sys/_types/_wint_t.h
.o/thing_terrain.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_terrain.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_terrain.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_terrain.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_terrain.o: my_charmap.h my_dmap.h my_level_static.h
.o/thing_terrain.o: my_dungeon_grid.h my_thing.h my_light.h
.o/thing_terrain.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_terrain.o: my_thing_ai.h
.o/thing_text.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_text.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_text.o: /usr/include/sys/_posix_availability.h
.o/thing_text.o: /usr/include/Availability.h
.o/thing_text.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_text.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_text.o: /usr/include/i386/_types.h
.o/thing_text.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_text.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_text.o: /usr/include/sys/_types/_int8_t.h
.o/thing_text.o: /usr/include/sys/_types/_int16_t.h
.o/thing_text.o: /usr/include/sys/_types/_int32_t.h
.o/thing_text.o: /usr/include/sys/_types/_int64_t.h
.o/thing_text.o: /usr/include/_types/_uint8_t.h
.o/thing_text.o: /usr/include/_types/_uint16_t.h
.o/thing_text.o: /usr/include/_types/_uint32_t.h
.o/thing_text.o: /usr/include/_types/_uint64_t.h
.o/thing_text.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_text.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_text.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_text.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_text.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_text.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_text.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_text.o: /usr/include/_types/_intmax_t.h
.o/thing_text.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_text.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_text.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_text.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_text.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_text.o: /usr/include/sys/_types/_null.h
.o/thing_text.o: /usr/include/sys/_types/_size_t.h
.o/thing_text.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_text.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_text.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_text.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_text.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_text.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_text.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_text.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_text.o: /usr/include/sys/_types/_time_t.h
.o/thing_text.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_text.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_text.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_text.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_text.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_text.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_text.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_text.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_text.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_tick.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_tick.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_tick.o: /usr/include/sys/_posix_availability.h
.o/thing_tick.o: /usr/include/Availability.h
.o/thing_tick.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_tick.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_tick.o: /usr/include/i386/_types.h
.o/thing_tick.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_tick.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_tick.o: /usr/include/sys/_types/_int8_t.h
.o/thing_tick.o: /usr/include/sys/_types/_int16_t.h
.o/thing_tick.o: /usr/include/sys/_types/_int32_t.h
.o/thing_tick.o: /usr/include/sys/_types/_int64_t.h
.o/thing_tick.o: /usr/include/_types/_uint8_t.h
.o/thing_tick.o: /usr/include/_types/_uint16_t.h
.o/thing_tick.o: /usr/include/_types/_uint32_t.h
.o/thing_tick.o: /usr/include/_types/_uint64_t.h
.o/thing_tick.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_tick.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_tick.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_tick.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_tick.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_tick.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_tick.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_tick.o: /usr/include/_types/_intmax_t.h
.o/thing_tick.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_tick.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_tick.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_tick.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h
.o/thing_tick.o: my_math.h /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/thing_tick.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_tick.o: /usr/include/sys/_types/_null.h
.o/thing_tick.o: /usr/include/sys/_types/_size_t.h
.o/thing_tick.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_tick.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_tick.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_tick.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_tick.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_tick.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_tick.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_tick.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_tick.o: /usr/include/sys/_types/_time_t.h
.o/thing_tick.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_tick.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_tick.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_tick.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_tick.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_tick.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_tick.o: my_dungeon_grid.h my_wid_console.h my_wid.h my_ascii.h
.o/thing_tick.o: my_tex.h my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/thing_tick.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_tick.o: my_python.h
.o/thing_tile.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_tile.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_tile.o: /usr/include/sys/_posix_availability.h
.o/thing_tile.o: /usr/include/Availability.h
.o/thing_tile.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_tile.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_tile.o: /usr/include/i386/_types.h
.o/thing_tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_tile.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_tile.o: /usr/include/sys/_types/_int8_t.h
.o/thing_tile.o: /usr/include/sys/_types/_int16_t.h
.o/thing_tile.o: /usr/include/sys/_types/_int32_t.h
.o/thing_tile.o: /usr/include/sys/_types/_int64_t.h
.o/thing_tile.o: /usr/include/_types/_uint8_t.h
.o/thing_tile.o: /usr/include/_types/_uint16_t.h
.o/thing_tile.o: /usr/include/_types/_uint32_t.h
.o/thing_tile.o: /usr/include/_types/_uint64_t.h
.o/thing_tile.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_tile.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_tile.o: /usr/include/_types/_intmax_t.h
.o/thing_tile.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_tile.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_tile.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_tile.o: c_plus_plus_serializer.h my_tile.h my_sdl.h my_command.h
.o/thing_tile.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_tile.o: /usr/include/sys/_types/_null.h
.o/thing_tile.o: /usr/include/sys/_types/_size_t.h
.o/thing_tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_tile.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_tile.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_tile.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_tile.o: /usr/include/sys/_types/_time_t.h
.o/thing_tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_tile.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_tile.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_tile.o: my_thing.h my_time.h my_light.h my_thing_template.h
.o/thing_tile.o: my_dice.h my_size.h my_thing_ai.h my_dmap.h my_thing_id.h
.o/thing_torch.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_torch.o: /usr/include/sys/cdefs.h
.o/thing_torch.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_torch.o: /usr/include/sys/_posix_availability.h
.o/thing_torch.o: /usr/include/Availability.h
.o/thing_torch.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_torch.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_torch.o: /usr/include/i386/_types.h
.o/thing_torch.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_torch.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_torch.o: /usr/include/sys/_types/_int8_t.h
.o/thing_torch.o: /usr/include/sys/_types/_int16_t.h
.o/thing_torch.o: /usr/include/sys/_types/_int32_t.h
.o/thing_torch.o: /usr/include/sys/_types/_int64_t.h
.o/thing_torch.o: /usr/include/_types/_uint8_t.h
.o/thing_torch.o: /usr/include/_types/_uint16_t.h
.o/thing_torch.o: /usr/include/_types/_uint32_t.h
.o/thing_torch.o: /usr/include/_types/_uint64_t.h
.o/thing_torch.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_torch.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_torch.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_torch.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_torch.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_torch.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_torch.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_torch.o: /usr/include/_types/_intmax_t.h
.o/thing_torch.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_torch.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_torch.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_torch.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_torch.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_torch.o: /usr/include/sys/_types/_null.h
.o/thing_torch.o: /usr/include/sys/_types/_size_t.h
.o/thing_torch.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_torch.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_torch.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_torch.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_torch.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_torch.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_torch.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_torch.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_torch.o: /usr/include/sys/_types/_time_t.h
.o/thing_torch.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_torch.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_torch.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_torch.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_torch.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_torch.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_torch.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_torch.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_torch.o: my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_treasure.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_treasure.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_treasure.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_treasure.o: /usr/include/sys/_posix_availability.h
.o/thing_treasure.o: /usr/include/Availability.h
.o/thing_treasure.o: /usr/include/AvailabilityInternal.h
.o/thing_treasure.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_treasure.o: my_main.h my_sys.h my_pcg_basic.h
.o/thing_treasure.o: /usr/include/inttypes.h /usr/include/_types.h
.o/thing_treasure.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_treasure.o: /usr/include/i386/_types.h
.o/thing_treasure.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_treasure.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_treasure.o: /usr/include/sys/_types/_int8_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_int16_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_int32_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_int64_t.h
.o/thing_treasure.o: /usr/include/_types/_uint8_t.h
.o/thing_treasure.o: /usr/include/_types/_uint16_t.h
.o/thing_treasure.o: /usr/include/_types/_uint32_t.h
.o/thing_treasure.o: /usr/include/_types/_uint64_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_treasure.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_treasure.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_treasure.o: /usr/include/_types/_intmax_t.h
.o/thing_treasure.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_treasure.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_treasure.o: my_bounds_check.h /usr/include/assert.h
.o/thing_treasure.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_treasure.o: my_string.h /usr/include/wchar.h
.o/thing_treasure.o: /usr/include/sys/_types/_null.h
.o/thing_treasure.o: /usr/include/sys/_types/_size_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_treasure.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_treasure.o: /usr/include/sys/stdio.h
.o/thing_treasure.o: /usr/include/sys/_types/_off_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_treasure.o: /usr/include/secure/_stdio.h
.o/thing_treasure.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_treasure.o: /usr/include/sys/_types/_clock_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_time_t.h
.o/thing_treasure.o: /usr/include/sys/_types/_timespec.h
.o/thing_treasure.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_treasure.o: /usr/include/sys/_types/_wint_t.h
.o/thing_treasure.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_treasure.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_treasure.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_treasure.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_treasure.o: my_level_static.h my_dungeon_grid.h my_thing.h
.o/thing_treasure.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_treasure.o: my_color.h my_thing_ai.h my_sprintf.h my_gl.h
.o/thing_update.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_update.o: /usr/include/sys/cdefs.h
.o/thing_update.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_update.o: /usr/include/sys/_posix_availability.h
.o/thing_update.o: /usr/include/Availability.h
.o/thing_update.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_update.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_update.o: /usr/include/i386/_types.h
.o/thing_update.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_update.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_update.o: /usr/include/sys/_types/_int8_t.h
.o/thing_update.o: /usr/include/sys/_types/_int16_t.h
.o/thing_update.o: /usr/include/sys/_types/_int32_t.h
.o/thing_update.o: /usr/include/sys/_types/_int64_t.h
.o/thing_update.o: /usr/include/_types/_uint8_t.h
.o/thing_update.o: /usr/include/_types/_uint16_t.h
.o/thing_update.o: /usr/include/_types/_uint32_t.h
.o/thing_update.o: /usr/include/_types/_uint64_t.h
.o/thing_update.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_update.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_update.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_update.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_update.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_update.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_update.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_update.o: /usr/include/_types/_intmax_t.h
.o/thing_update.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_update.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_update.o: my_bounds_check.h /usr/include/assert.h
.o/thing_update.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_update.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_update.o: my_string.h /usr/include/wchar.h
.o/thing_update.o: /usr/include/sys/_types/_null.h
.o/thing_update.o: /usr/include/sys/_types/_size_t.h
.o/thing_update.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_update.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_update.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_update.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_update.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_update.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_update.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_update.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_update.o: /usr/include/sys/_types/_time_t.h
.o/thing_update.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_update.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_update.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_update.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_update.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_update.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_update.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_update.o: my_color.h my_sprintf.h my_thing.h my_light.h
.o/thing_update.o: my_thing_template.h my_dice.h my_tile.h my_thing_ai.h
.o/thing_use.o: my_game.h my_world.h my_point.h my_math.h /usr/include/math.h
.o/thing_use.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_use.o: /usr/include/sys/_posix_availability.h
.o/thing_use.o: /usr/include/Availability.h
.o/thing_use.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/thing_use.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_use.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/thing_use.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_use.o: /usr/include/i386/_types.h
.o/thing_use.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_use.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_use.o: /usr/include/sys/_types/_int8_t.h
.o/thing_use.o: /usr/include/sys/_types/_int16_t.h
.o/thing_use.o: /usr/include/sys/_types/_int32_t.h
.o/thing_use.o: /usr/include/sys/_types/_int64_t.h
.o/thing_use.o: /usr/include/_types/_uint8_t.h
.o/thing_use.o: /usr/include/_types/_uint16_t.h
.o/thing_use.o: /usr/include/_types/_uint32_t.h
.o/thing_use.o: /usr/include/_types/_uint64_t.h
.o/thing_use.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_use.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_use.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_use.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_use.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_use.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_use.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_use.o: /usr/include/_types/_intmax_t.h
.o/thing_use.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_use.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_use.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/thing_use.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_use.o: /usr/include/sys/_types/_null.h
.o/thing_use.o: /usr/include/sys/_types/_size_t.h
.o/thing_use.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_use.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_use.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_use.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_use.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_use.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_use.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_use.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_use.o: /usr/include/sys/_types/_time_t.h
.o/thing_use.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_use.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_use.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_use.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_use.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/thing_use.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/thing_use.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/thing_use.o: my_dice.h my_tile.h my_color.h my_thing_ai.h my_python.h
.o/thing_visible.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_visible.o: /usr/include/sys/cdefs.h
.o/thing_visible.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_visible.o: /usr/include/sys/_posix_availability.h
.o/thing_visible.o: /usr/include/Availability.h
.o/thing_visible.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_visible.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_visible.o: /usr/include/i386/_types.h
.o/thing_visible.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_visible.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_visible.o: /usr/include/sys/_types/_int8_t.h
.o/thing_visible.o: /usr/include/sys/_types/_int16_t.h
.o/thing_visible.o: /usr/include/sys/_types/_int32_t.h
.o/thing_visible.o: /usr/include/sys/_types/_int64_t.h
.o/thing_visible.o: /usr/include/_types/_uint8_t.h
.o/thing_visible.o: /usr/include/_types/_uint16_t.h
.o/thing_visible.o: /usr/include/_types/_uint32_t.h
.o/thing_visible.o: /usr/include/_types/_uint64_t.h
.o/thing_visible.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_visible.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_visible.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_visible.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_visible.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_visible.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_visible.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_visible.o: /usr/include/_types/_intmax_t.h
.o/thing_visible.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_visible.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_visible.o: my_bounds_check.h /usr/include/assert.h
.o/thing_visible.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_visible.o: my_level.h my_time.h my_sdl.h my_command.h my_token.h
.o/thing_visible.o: my_string.h /usr/include/wchar.h
.o/thing_visible.o: /usr/include/sys/_types/_null.h
.o/thing_visible.o: /usr/include/sys/_types/_size_t.h
.o/thing_visible.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_visible.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_visible.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_visible.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_visible.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_visible.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_visible.o: /usr/include/secure/_stdio.h
.o/thing_visible.o: /usr/include/secure/_common.h /usr/include/time.h
.o/thing_visible.o: /usr/include/sys/_types/_clock_t.h
.o/thing_visible.o: /usr/include/sys/_types/_time_t.h
.o/thing_visible.o: /usr/include/sys/_types/_timespec.h
.o/thing_visible.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_visible.o: /usr/include/sys/_types/_wint_t.h
.o/thing_visible.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_visible.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_visible.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_visible.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_visible.o: my_charmap.h my_dmap.h my_level_static.h
.o/thing_visible.o: my_dungeon_grid.h my_color.h my_sprintf.h my_thing.h
.o/thing_visible.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_visible.o: my_thing_ai.h
.o/thing_water.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_water.o: /usr/include/sys/cdefs.h
.o/thing_water.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_water.o: /usr/include/sys/_posix_availability.h
.o/thing_water.o: /usr/include/Availability.h
.o/thing_water.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_water.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_water.o: /usr/include/i386/_types.h
.o/thing_water.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_water.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_water.o: /usr/include/sys/_types/_int8_t.h
.o/thing_water.o: /usr/include/sys/_types/_int16_t.h
.o/thing_water.o: /usr/include/sys/_types/_int32_t.h
.o/thing_water.o: /usr/include/sys/_types/_int64_t.h
.o/thing_water.o: /usr/include/_types/_uint8_t.h
.o/thing_water.o: /usr/include/_types/_uint16_t.h
.o/thing_water.o: /usr/include/_types/_uint32_t.h
.o/thing_water.o: /usr/include/_types/_uint64_t.h
.o/thing_water.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_water.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_water.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_water.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_water.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_water.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_water.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_water.o: /usr/include/_types/_intmax_t.h
.o/thing_water.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/thing_water.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/thing_water.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_water.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_water.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_water.o: /usr/include/sys/_types/_null.h
.o/thing_water.o: /usr/include/sys/_types/_size_t.h
.o/thing_water.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_water.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_water.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_water.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_water.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_water.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_water.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_water.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_water.o: /usr/include/sys/_types/_time_t.h
.o/thing_water.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_water.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_water.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_water.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_water.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_water.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_water.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_water.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_water.o: my_tile.h my_color.h my_thing_ai.h my_sprintf.h
.o/thing_weapon.o: my_level.h my_time.h my_sdl.h my_main.h my_sys.h
.o/thing_weapon.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_weapon.o: /usr/include/sys/cdefs.h
.o/thing_weapon.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_weapon.o: /usr/include/sys/_posix_availability.h
.o/thing_weapon.o: /usr/include/Availability.h
.o/thing_weapon.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_weapon.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_weapon.o: /usr/include/i386/_types.h
.o/thing_weapon.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_weapon.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_weapon.o: /usr/include/sys/_types/_int8_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_int16_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_int32_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_int64_t.h
.o/thing_weapon.o: /usr/include/_types/_uint8_t.h
.o/thing_weapon.o: /usr/include/_types/_uint16_t.h
.o/thing_weapon.o: /usr/include/_types/_uint32_t.h
.o/thing_weapon.o: /usr/include/_types/_uint64_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_weapon.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_weapon.o: /usr/include/_types/_intmax_t.h
.o/thing_weapon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_weapon.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_weapon.o: my_bounds_check.h /usr/include/assert.h
.o/thing_weapon.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_weapon.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_weapon.o: /usr/include/sys/_types/_null.h
.o/thing_weapon.o: /usr/include/sys/_types/_size_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_weapon.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_weapon.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_weapon.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_weapon.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_time_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_weapon.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_weapon.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_weapon.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_weapon.o: my_particle.h my_point.h my_math.h /usr/include/math.h
.o/thing_weapon.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/thing_weapon.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/thing_weapon.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_weapon.o: my_tile.h my_color.h my_thing_ai.h my_game.h my_world.h
.o/thing_wobble.o: my_game.h my_world.h my_point.h my_math.h
.o/thing_wobble.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/thing_wobble.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_wobble.o: /usr/include/sys/_posix_availability.h
.o/thing_wobble.o: /usr/include/Availability.h
.o/thing_wobble.o: /usr/include/AvailabilityInternal.h
.o/thing_wobble.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/thing_wobble.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_wobble.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_wobble.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_wobble.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_wobble.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_wobble.o: /usr/include/sys/_types/_int8_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_int16_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_int32_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_int64_t.h
.o/thing_wobble.o: /usr/include/_types/_uint8_t.h
.o/thing_wobble.o: /usr/include/_types/_uint16_t.h
.o/thing_wobble.o: /usr/include/_types/_uint32_t.h
.o/thing_wobble.o: /usr/include/_types/_uint64_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_wobble.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_wobble.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_wobble.o: /usr/include/_types/_intmax_t.h
.o/thing_wobble.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_wobble.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/thing_wobble.o: my_bounds_check.h /usr/include/assert.h
.o/thing_wobble.o: my_vector_bounds_check.h my_command.h my_token.h
.o/thing_wobble.o: my_string.h /usr/include/wchar.h
.o/thing_wobble.o: /usr/include/sys/_types/_null.h
.o/thing_wobble.o: /usr/include/sys/_types/_size_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/thing_wobble.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_wobble.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_wobble.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_wobble.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_time_t.h
.o/thing_wobble.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_wobble.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_wobble.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_wobble.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/thing_wobble.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/thing_wobble.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/thing_wobble.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/thing_wobble.o: my_thing_template.h my_dice.h my_tile.h my_color.h
.o/thing_wobble.o: my_thing_ai.h my_sprintf.h my_gl.h
.o/tile.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/tile.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/tile.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/tile.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/tile.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/tile.o: /usr/include/i386/_types.h
.o/tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/tile.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/tile.o: /usr/include/sys/_types/_int8_t.h
.o/tile.o: /usr/include/sys/_types/_int16_t.h
.o/tile.o: /usr/include/sys/_types/_int32_t.h
.o/tile.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/tile.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tile.o: /usr/include/_types/_uint64_t.h
.o/tile.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/tile.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/tile.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/tile.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/tile.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/tile.o: c_plus_plus_serializer.h my_depth.h my_gl.h my_color.h my_point.h
.o/tile.o: my_math.h /usr/include/math.h my_size.h my_tile.h my_sdl.h
.o/tile.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/tile.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tile.o: /usr/include/secure/_common.h /usr/include/time.h
.o/tile.o: /usr/include/sys/_types/_clock_t.h
.o/tile.o: /usr/include/sys/_types/_time_t.h
.o/tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/tile.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_tex.h
.o/tile.o: my_pixel.h my_thing_template.h my_dice.h my_dmap.h my_game.h
.o/tile.o: my_world.h my_level.h my_time.h my_particle.h my_thing_id.h
.o/tile.o: my_dungeon.h my_room.h my_charmap.h my_level_static.h
.o/tile.o: my_dungeon_grid.h
.o/time.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/time.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/time.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/time.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/time.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/time.o: /usr/include/i386/_types.h
.o/time.o: /usr/include/sys/_pthread/_pthread_types.h
.o/time.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/time.o: /usr/include/sys/_types/_int8_t.h
.o/time.o: /usr/include/sys/_types/_int16_t.h
.o/time.o: /usr/include/sys/_types/_int32_t.h
.o/time.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/time.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/time.o: /usr/include/_types/_uint64_t.h
.o/time.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/time.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/time.o: /usr/include/sys/_types/_u_int16_t.h
.o/time.o: /usr/include/sys/_types/_u_int32_t.h
.o/time.o: /usr/include/sys/_types/_u_int64_t.h
.o/time.o: /usr/include/sys/_types/_uintptr_t.h
.o/time.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/time.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/time.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/time.o: c_plus_plus_serializer.h my_string.h /usr/include/wchar.h
.o/time.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/time.o: /usr/include/sys/_types/_mbstate_t.h
.o/time.o: /usr/include/sys/_types/_ct_rune_t.h
.o/time.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/time.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/time.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/time.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/time.o: /usr/include/secure/_common.h /usr/include/time.h
.o/time.o: /usr/include/sys/_types/_clock_t.h
.o/time.o: /usr/include/sys/_types/_time_t.h
.o/time.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/time.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/time.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/time.o: /usr/include/_ctype.h /usr/include/runetype.h my_time.h my_sdl.h
.o/time.o: my_command.h my_token.h slre.h
.o/token.o: /usr/include/string.h /usr/include/_types.h
.o/token.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/token.o: /usr/include/sys/_symbol_aliasing.h
.o/token.o: /usr/include/sys/_posix_availability.h
.o/token.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/token.o: /usr/include/sys/_pthread/_pthread_types.h
.o/token.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/token.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/token.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
.o/token.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/token.o: /usr/include/sys/_types/_int16_t.h
.o/token.o: /usr/include/sys/_types/_int32_t.h
.o/token.o: /usr/include/sys/_types/_int64_t.h
.o/token.o: /usr/include/sys/_types/_u_int8_t.h
.o/token.o: /usr/include/sys/_types/_u_int16_t.h
.o/token.o: /usr/include/sys/_types/_u_int32_t.h
.o/token.o: /usr/include/sys/_types/_u_int64_t.h
.o/token.o: /usr/include/sys/_types/_intptr_t.h
.o/token.o: /usr/include/sys/_types/_uintptr_t.h
.o/token.o: /usr/include/sys/_types/_errno_t.h
.o/token.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/token.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/token.o: /usr/include/secure/_string.h my_main.h my_sys.h my_pcg_basic.h
.o/token.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/token.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/token.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/token.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/token.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/token.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/token.o: /usr/include/assert.h my_vector_bounds_check.h
.o/token.o: c_plus_plus_serializer.h slre.h my_token.h my_string.h
.o/token.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/token.o: /usr/include/sys/_types/_ct_rune_t.h
.o/token.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/token.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/token.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/token.o: /usr/include/secure/_stdio.h /usr/include/time.h
.o/token.o: /usr/include/sys/_types/_clock_t.h
.o/token.o: /usr/include/sys/_types/_time_t.h
.o/token.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/token.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/token.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/token.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/traceback.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/traceback.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/traceback.o: /usr/include/sys/_posix_availability.h
.o/traceback.o: /usr/include/Availability.h
.o/traceback.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/traceback.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/traceback.o: /usr/include/i386/_types.h
.o/traceback.o: /usr/include/sys/_pthread/_pthread_types.h
.o/traceback.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/traceback.o: /usr/include/sys/_types/_int8_t.h
.o/traceback.o: /usr/include/sys/_types/_int16_t.h
.o/traceback.o: /usr/include/sys/_types/_int32_t.h
.o/traceback.o: /usr/include/sys/_types/_int64_t.h
.o/traceback.o: /usr/include/_types/_uint8_t.h
.o/traceback.o: /usr/include/_types/_uint16_t.h
.o/traceback.o: /usr/include/_types/_uint32_t.h
.o/traceback.o: /usr/include/_types/_uint64_t.h
.o/traceback.o: /usr/include/sys/_types/_intptr_t.h
.o/traceback.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/traceback.o: /usr/include/sys/_types/_u_int8_t.h
.o/traceback.o: /usr/include/sys/_types/_u_int16_t.h
.o/traceback.o: /usr/include/sys/_types/_u_int32_t.h
.o/traceback.o: /usr/include/sys/_types/_u_int64_t.h
.o/traceback.o: /usr/include/sys/_types/_uintptr_t.h
.o/traceback.o: /usr/include/_types/_intmax_t.h
.o/traceback.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/traceback.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/traceback.o: /usr/include/assert.h my_vector_bounds_check.h
.o/traceback.o: c_plus_plus_serializer.h my_traceback.h my_sprintf.h
.o/traceback.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/traceback.o: /usr/include/sys/_types/_va_list.h
.o/traceback.o: /usr/include/sys/_types/_size_t.h
.o/traceback.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/traceback.o: /usr/include/sys/_types/_off_t.h
.o/traceback.o: /usr/include/sys/_types/_ssize_t.h
.o/traceback.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/traceback.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/traceback.o: /usr/include/sys/_types/_pid_t.h
.o/traceback.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/traceback.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/traceback.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/traceback.o: /usr/include/i386/_mcontext.h
.o/traceback.o: /usr/include/mach/machine/_structs.h
.o/traceback.o: /usr/include/mach/i386/_structs.h
.o/traceback.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/traceback.o: /usr/include/sys/_types/_sigaltstack.h
.o/traceback.o: /usr/include/sys/_types/_ucontext.h
.o/traceback.o: /usr/include/sys/_types/_sigset_t.h
.o/traceback.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/traceback.o: /usr/include/sys/_types/_timeval.h
.o/traceback.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/traceback.o: /usr/include/sys/_endian.h
.o/traceback.o: /usr/include/libkern/_OSByteOrder.h
.o/traceback.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/traceback.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/traceback.o: /usr/include/sys/_types/_rune_t.h
.o/traceback.o: /usr/include/sys/_types/_dev_t.h
.o/traceback.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
.o/traceback.o: /usr/include/sys/_types/_rsize_t.h
.o/traceback.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/traceback.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/traceback.o: /usr/include/execinfo.h /usr/include/cxxabi.h
.o/traceback.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/traceback.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/traceback.o: /usr/include/sys/_types/_wint_t.h
.o/traceback.o: /usr/include/__cxxabi_config.h
.o/ttf.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/ttf.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ttf.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/ttf.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ttf.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ttf.o: /usr/include/i386/_types.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ttf.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ttf.o: /usr/include/sys/_types/_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/ttf.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ttf.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/ttf.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ttf.o: /usr/include/sys/_types/_u_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int64_t.h
.o/ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ttf.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/ttf.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/ttf.o: c_plus_plus_serializer.h my_gl.h my_color.h my_point.h my_math.h
.o/ttf.o: /usr/include/math.h my_size.h my_wid.h my_ascii.h
.o/ttf.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/ttf.o: /usr/include/sys/_types/_size_t.h
.o/ttf.o: /usr/include/sys/_types/_mbstate_t.h
.o/ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/ttf.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/ttf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ttf.o: /usr/include/secure/_common.h /usr/include/time.h
.o/ttf.o: /usr/include/sys/_types/_clock_t.h
.o/ttf.o: /usr/include/sys/_types/_time_t.h
.o/ttf.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ttf.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ttf.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ttf.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h my_tile.h
.o/ttf.o: my_sdl.h my_command.h my_token.h my_string.h slre.h my_wid_tiles.h
.o/ttf.o: my_thing.h my_time.h my_light.h my_thing_template.h my_dice.h
.o/ttf.o: my_thing_ai.h my_dmap.h my_thing_id.h my_ttf.h my_font.h
.o/ttf.o: my_ramdisk.h my_bits.h my_pixel.h stb_image.h /usr/include/stdlib.h
.o/ttf.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/ttf.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/ttf.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/ttf.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ttf.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/ttf.o: /usr/include/mach/i386/_structs.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ttf.o: /usr/include/sys/_types/_sigaltstack.h
.o/ttf.o: /usr/include/sys/_types/_ucontext.h
.o/ttf.o: /usr/include/sys/_types/_sigset_t.h
.o/ttf.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/ttf.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/ttf.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/ttf.o: /usr/include/libkern/_OSByteOrder.h
.o/ttf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ttf.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/ttf.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/ttf.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/ttf.o: /usr/include/sys/_types/_rsize_t.h /usr/include/string.h
.o/ttf.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ttf.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/ttf.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/ttf.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/ttf.o: /usr/include/sys/syslimits.h stb_image_write.h
.o/util.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/util.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/util.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/util.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/util.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/util.o: /usr/include/i386/_types.h
.o/util.o: /usr/include/sys/_pthread/_pthread_types.h
.o/util.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/util.o: /usr/include/sys/_types/_int8_t.h
.o/util.o: /usr/include/sys/_types/_int16_t.h
.o/util.o: /usr/include/sys/_types/_int32_t.h
.o/util.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/util.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/util.o: /usr/include/_types/_uint64_t.h
.o/util.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/util.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/util.o: /usr/include/sys/_types/_u_int16_t.h
.o/util.o: /usr/include/sys/_types/_u_int32_t.h
.o/util.o: /usr/include/sys/_types/_u_int64_t.h
.o/util.o: /usr/include/sys/_types/_uintptr_t.h
.o/util.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/util.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/util.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/util.o: c_plus_plus_serializer.h /usr/include/stdlib.h
.o/util.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/util.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/util.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/util.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/util.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/util.o: /usr/include/mach/i386/_structs.h
.o/util.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/util.o: /usr/include/sys/_types/_sigaltstack.h
.o/util.o: /usr/include/sys/_types/_ucontext.h
.o/util.o: /usr/include/sys/_types/_sigset_t.h
.o/util.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
.o/util.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
.o/util.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/util.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/util.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/util.o: /usr/include/sys/_types/_ct_rune_t.h
.o/util.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_null.h
.o/util.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/util.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/util.o: /usr/include/sys/_types/_errno_t.h
.o/util.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/util.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/util.o: /usr/include/secure/_string.h
.o/wid.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/wid.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid.o: /usr/include/i386/_types.h
.o/wid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid.o: /usr/include/sys/_types/_int8_t.h
.o/wid.o: /usr/include/sys/_types/_int16_t.h
.o/wid.o: /usr/include/sys/_types/_int32_t.h
.o/wid.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/wid.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/wid.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/wid.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/wid.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/wid.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/wid.o: c_plus_plus_serializer.h my_game.h my_world.h my_point.h my_math.h
.o/wid.o: /usr/include/math.h my_level.h my_time.h my_sdl.h my_command.h
.o/wid.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/wid.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid.o: /usr/include/secure/_common.h /usr/include/time.h
.o/wid.o: /usr/include/sys/_types/_clock_t.h
.o/wid.o: /usr/include/sys/_types/_time_t.h
.o/wid.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_particle.h
.o/wid.o: my_size.h my_thing_id.h my_dungeon.h my_room.h my_depth.h
.o/wid.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h my_wid.h
.o/wid.o: my_ascii.h my_tex.h my_tile.h my_color.h my_wid_tiles.h my_thing.h
.o/wid.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/wid.o: my_wid_console.h my_wid_minicon.h my_sprintf.h my_gl.h
.o/wid.o: my_wid_inventory.h my_wid_thing_info.h my_wid_popup.h
.o/wid.o: my_wid_text_box.h my_wid_thing_collect.h
.o/wid_bag.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_bag.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_bag.o: /usr/include/sys/_posix_availability.h
.o/wid_bag.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/wid_bag.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/wid_bag.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_bag.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_bag.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_bag.o: /usr/include/sys/_types/_int8_t.h
.o/wid_bag.o: /usr/include/sys/_types/_int16_t.h
.o/wid_bag.o: /usr/include/sys/_types/_int32_t.h
.o/wid_bag.o: /usr/include/sys/_types/_int64_t.h
.o/wid_bag.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/wid_bag.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/wid_bag.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_bag.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_bag.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_bag.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_bag.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_bag.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_bag.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_bag.o: /usr/include/_types/_intmax_t.h
.o/wid_bag.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_bag.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_bag.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_bag.o: c_plus_plus_serializer.h my_sdl.h my_command.h my_token.h
.o/wid_bag.o: my_string.h /usr/include/wchar.h
.o/wid_bag.o: /usr/include/sys/_types/_null.h
.o/wid_bag.o: /usr/include/sys/_types/_size_t.h
.o/wid_bag.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_bag.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_bag.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_bag.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_bag.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_bag.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid_bag.o: /usr/include/secure/_common.h /usr/include/time.h
.o/wid_bag.o: /usr/include/sys/_types/_clock_t.h
.o/wid_bag.o: /usr/include/sys/_types/_time_t.h
.o/wid_bag.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_bag.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_bag.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_bag.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_bag.o: my_wid_bag.h my_wid.h my_ascii.h my_tex.h my_tile.h my_point.h
.o/wid_bag.o: my_math.h /usr/include/math.h my_color.h my_wid_tiles.h
.o/wid_bag.o: my_thing.h my_time.h my_light.h my_thing_template.h my_dice.h
.o/wid_bag.o: my_size.h my_thing_ai.h my_dmap.h my_thing_id.h my_ttf.h
.o/wid_bag.o: my_font.h my_wid_popup.h my_wid_text_box.h my_game.h my_world.h
.o/wid_bag.o: my_level.h my_particle.h my_dungeon.h my_room.h my_depth.h
.o/wid_bag.o: my_charmap.h my_level_static.h my_dungeon_grid.h
.o/wid_bag.o: my_wid_inventory.h
.o/wid_botcon.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_botcon.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_botcon.o: /usr/include/sys/_posix_availability.h
.o/wid_botcon.o: /usr/include/Availability.h
.o/wid_botcon.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_botcon.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_botcon.o: /usr/include/i386/_types.h
.o/wid_botcon.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_botcon.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_botcon.o: /usr/include/sys/_types/_int8_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_int16_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_int32_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_int64_t.h
.o/wid_botcon.o: /usr/include/_types/_uint8_t.h
.o/wid_botcon.o: /usr/include/_types/_uint16_t.h
.o/wid_botcon.o: /usr/include/_types/_uint32_t.h
.o/wid_botcon.o: /usr/include/_types/_uint64_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_botcon.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_botcon.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_botcon.o: /usr/include/_types/_intmax_t.h
.o/wid_botcon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_botcon.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_botcon.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_botcon.o: c_plus_plus_serializer.h my_sdl.h my_command.h my_token.h
.o/wid_botcon.o: my_string.h /usr/include/wchar.h
.o/wid_botcon.o: /usr/include/sys/_types/_null.h
.o/wid_botcon.o: /usr/include/sys/_types/_size_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_botcon.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_botcon.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_botcon.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_botcon.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_time_t.h
.o/wid_botcon.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_botcon.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_botcon.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_botcon.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_botcon.o: my_wid_botcon.h my_point.h my_math.h /usr/include/math.h
.o/wid_botcon.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_botcon.o: my_wid_tiles.h my_thing.h my_time.h my_light.h
.o/wid_botcon.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/wid_botcon.o: my_dmap.h my_thing_id.h my_ttf.h my_font.h my_game.h
.o/wid_botcon.o: my_world.h my_level.h my_particle.h my_dungeon.h my_room.h
.o/wid_botcon.o: my_depth.h my_charmap.h my_level_static.h my_dungeon_grid.h
.o/wid_console.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_console.o: /usr/include/sys/cdefs.h
.o/wid_console.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_console.o: /usr/include/sys/_posix_availability.h
.o/wid_console.o: /usr/include/Availability.h
.o/wid_console.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_console.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_console.o: /usr/include/i386/_types.h
.o/wid_console.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_console.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_console.o: /usr/include/sys/_types/_int8_t.h
.o/wid_console.o: /usr/include/sys/_types/_int16_t.h
.o/wid_console.o: /usr/include/sys/_types/_int32_t.h
.o/wid_console.o: /usr/include/sys/_types/_int64_t.h
.o/wid_console.o: /usr/include/_types/_uint8_t.h
.o/wid_console.o: /usr/include/_types/_uint16_t.h
.o/wid_console.o: /usr/include/_types/_uint32_t.h
.o/wid_console.o: /usr/include/_types/_uint64_t.h
.o/wid_console.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_console.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_console.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_console.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_console.o: /usr/include/_types/_intmax_t.h
.o/wid_console.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_console.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_console.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_console.o: c_plus_plus_serializer.h my_sdl.h my_command.h my_token.h
.o/wid_console.o: my_string.h /usr/include/wchar.h
.o/wid_console.o: /usr/include/sys/_types/_null.h
.o/wid_console.o: /usr/include/sys/_types/_size_t.h
.o/wid_console.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_console.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_console.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_console.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_console.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_console.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_console.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_console.o: /usr/include/sys/_types/_time_t.h
.o/wid_console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_console.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_console.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_console.o: my_wid_console.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/wid_console.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/wid_console.o: my_wid_tiles.h my_thing.h my_time.h my_light.h
.o/wid_console.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/wid_console.o: my_dmap.h my_thing_id.h my_ttf.h my_font.h
.o/wid_inventory.o: my_game.h my_world.h my_point.h my_math.h
.o/wid_inventory.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/wid_inventory.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_inventory.o: /usr/include/sys/_posix_availability.h
.o/wid_inventory.o: /usr/include/Availability.h
.o/wid_inventory.o: /usr/include/AvailabilityInternal.h
.o/wid_inventory.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/wid_inventory.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_inventory.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/wid_inventory.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_inventory.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_inventory.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_inventory.o: /usr/include/sys/_types/_int8_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_int16_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_int32_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_int64_t.h
.o/wid_inventory.o: /usr/include/_types/_uint8_t.h
.o/wid_inventory.o: /usr/include/_types/_uint16_t.h
.o/wid_inventory.o: /usr/include/_types/_uint32_t.h
.o/wid_inventory.o: /usr/include/_types/_uint64_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_inventory.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_inventory.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_inventory.o: /usr/include/_types/_intmax_t.h
.o/wid_inventory.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_inventory.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/wid_inventory.o: my_bounds_check.h /usr/include/assert.h
.o/wid_inventory.o: my_vector_bounds_check.h my_command.h my_token.h
.o/wid_inventory.o: my_string.h /usr/include/wchar.h
.o/wid_inventory.o: /usr/include/sys/_types/_null.h
.o/wid_inventory.o: /usr/include/sys/_types/_size_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_inventory.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_inventory.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_inventory.o: /usr/include/secure/_stdio.h
.o/wid_inventory.o: /usr/include/secure/_common.h /usr/include/time.h
.o/wid_inventory.o: /usr/include/sys/_types/_clock_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_time_t.h
.o/wid_inventory.o: /usr/include/sys/_types/_timespec.h
.o/wid_inventory.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/wid_inventory.o: /usr/include/sys/_types/_wint_t.h
.o/wid_inventory.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_inventory.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_inventory.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/wid_inventory.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/wid_inventory.o: my_level_static.h my_dungeon_grid.h my_wid_inventory.h
.o/wid_inventory.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_inventory.o: my_wid_tiles.h my_thing.h my_light.h my_thing_template.h
.o/wid_inventory.o: my_dice.h my_thing_ai.h my_wid_thing_info.h
.o/wid_inventory.o: my_wid_popup.h my_wid_text_box.h my_wid_thing_collect.h
.o/wid_inventory.o: my_wid_bag.h
.o/wid_leftbar.o: my_game.h my_world.h my_point.h my_math.h
.o/wid_leftbar.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/wid_leftbar.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_leftbar.o: /usr/include/sys/_posix_availability.h
.o/wid_leftbar.o: /usr/include/Availability.h
.o/wid_leftbar.o: /usr/include/AvailabilityInternal.h
.o/wid_leftbar.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/wid_leftbar.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_leftbar.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/wid_leftbar.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_leftbar.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_leftbar.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_leftbar.o: /usr/include/sys/_types/_int8_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_int16_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_int32_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_int64_t.h
.o/wid_leftbar.o: /usr/include/_types/_uint8_t.h
.o/wid_leftbar.o: /usr/include/_types/_uint16_t.h
.o/wid_leftbar.o: /usr/include/_types/_uint32_t.h
.o/wid_leftbar.o: /usr/include/_types/_uint64_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_leftbar.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_leftbar.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_leftbar.o: /usr/include/_types/_intmax_t.h
.o/wid_leftbar.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_leftbar.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_leftbar.o: /usr/include/assert.h my_vector_bounds_check.h my_command.h
.o/wid_leftbar.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_leftbar.o: /usr/include/sys/_types/_null.h
.o/wid_leftbar.o: /usr/include/sys/_types/_size_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_leftbar.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_leftbar.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_leftbar.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_leftbar.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_time_t.h
.o/wid_leftbar.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_leftbar.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_leftbar.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_leftbar.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_leftbar.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/wid_leftbar.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/wid_leftbar.o: my_level_static.h my_dungeon_grid.h my_wid_leftbar.h
.o/wid_leftbar.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_leftbar.o: my_wid_tiles.h my_thing.h my_light.h my_thing_template.h
.o/wid_leftbar.o: my_dice.h my_thing_ai.h my_sprintf.h
.o/wid_log.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_log.o: /usr/include/sys/_posix_availability.h
.o/wid_log.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/wid_log.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/wid_log.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_log.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_log.o: /usr/include/sys/_types/_int8_t.h
.o/wid_log.o: /usr/include/sys/_types/_int16_t.h
.o/wid_log.o: /usr/include/sys/_types/_int32_t.h
.o/wid_log.o: /usr/include/sys/_types/_int64_t.h
.o/wid_log.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/wid_log.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/wid_log.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_log.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_log.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_log.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_log.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_log.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_log.o: /usr/include/_types/_intmax_t.h
.o/wid_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_log.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_log.o: c_plus_plus_serializer.h my_time.h my_sdl.h my_command.h
.o/wid_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_log.o: /usr/include/sys/_types/_null.h
.o/wid_log.o: /usr/include/sys/_types/_size_t.h
.o/wid_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid_log.o: /usr/include/secure/_common.h /usr/include/time.h
.o/wid_log.o: /usr/include/sys/_types/_clock_t.h
.o/wid_log.o: /usr/include/sys/_types/_time_t.h
.o/wid_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_log.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_wid.h
.o/wid_log.o: my_ascii.h my_tex.h my_tile.h my_point.h my_math.h
.o/wid_log.o: /usr/include/math.h my_color.h my_wid_tiles.h my_thing.h
.o/wid_log.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/wid_log.o: my_thing_ai.h my_dmap.h my_thing_id.h my_log.h
.o/wid_minicon.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_minicon.o: /usr/include/sys/cdefs.h
.o/wid_minicon.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_minicon.o: /usr/include/sys/_posix_availability.h
.o/wid_minicon.o: /usr/include/Availability.h
.o/wid_minicon.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_minicon.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_minicon.o: /usr/include/i386/_types.h
.o/wid_minicon.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_minicon.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_minicon.o: /usr/include/sys/_types/_int8_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_int16_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_int32_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_int64_t.h
.o/wid_minicon.o: /usr/include/_types/_uint8_t.h
.o/wid_minicon.o: /usr/include/_types/_uint16_t.h
.o/wid_minicon.o: /usr/include/_types/_uint32_t.h
.o/wid_minicon.o: /usr/include/_types/_uint64_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_minicon.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_minicon.o: /usr/include/_types/_intmax_t.h
.o/wid_minicon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_minicon.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_minicon.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_minicon.o: c_plus_plus_serializer.h my_sdl.h my_command.h my_token.h
.o/wid_minicon.o: my_string.h /usr/include/wchar.h
.o/wid_minicon.o: /usr/include/sys/_types/_null.h
.o/wid_minicon.o: /usr/include/sys/_types/_size_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_minicon.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_minicon.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_minicon.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_minicon.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_time_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_minicon.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_minicon.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_minicon.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_minicon.o: my_wid_minicon.h my_point.h my_math.h /usr/include/math.h
.o/wid_minicon.o: my_size.h my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_minicon.o: my_wid_tiles.h my_thing.h my_time.h my_light.h
.o/wid_minicon.o: my_thing_template.h my_dice.h my_thing_ai.h my_dmap.h
.o/wid_minicon.o: my_thing_id.h my_wid_inventory.h my_wid_thing_info.h
.o/wid_minicon.o: my_wid_popup.h my_wid_text_box.h my_wid_thing_collect.h
.o/wid_minicon.o: my_ttf.h my_font.h my_wid_bag.h my_game.h my_world.h
.o/wid_minicon.o: my_level.h my_particle.h my_dungeon.h my_room.h my_depth.h
.o/wid_minicon.o: my_charmap.h my_level_static.h my_dungeon_grid.h
.o/wid_popup.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_popup.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_popup.o: /usr/include/sys/_posix_availability.h
.o/wid_popup.o: /usr/include/Availability.h
.o/wid_popup.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_popup.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_popup.o: /usr/include/i386/_types.h
.o/wid_popup.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_popup.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_popup.o: /usr/include/sys/_types/_int8_t.h
.o/wid_popup.o: /usr/include/sys/_types/_int16_t.h
.o/wid_popup.o: /usr/include/sys/_types/_int32_t.h
.o/wid_popup.o: /usr/include/sys/_types/_int64_t.h
.o/wid_popup.o: /usr/include/_types/_uint8_t.h
.o/wid_popup.o: /usr/include/_types/_uint16_t.h
.o/wid_popup.o: /usr/include/_types/_uint32_t.h
.o/wid_popup.o: /usr/include/_types/_uint64_t.h
.o/wid_popup.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_popup.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_popup.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_popup.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_popup.o: /usr/include/_types/_intmax_t.h
.o/wid_popup.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_popup.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_popup.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_popup.o: c_plus_plus_serializer.h my_sdl.h my_command.h my_token.h
.o/wid_popup.o: my_string.h /usr/include/wchar.h
.o/wid_popup.o: /usr/include/sys/_types/_null.h
.o/wid_popup.o: /usr/include/sys/_types/_size_t.h
.o/wid_popup.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_popup.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_popup.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_popup.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_popup.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_popup.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_popup.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_popup.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_popup.o: /usr/include/sys/_types/_time_t.h
.o/wid_popup.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_popup.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_popup.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_popup.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_popup.o: my_wid_popup.h my_wid_text_box.h my_wid.h my_ascii.h my_tex.h
.o/wid_popup.o: my_tile.h my_point.h my_math.h /usr/include/math.h my_color.h
.o/wid_popup.o: my_wid_tiles.h my_thing.h my_time.h my_light.h
.o/wid_popup.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/wid_popup.o: my_dmap.h my_thing_id.h my_ttf.h my_font.h
.o/wid_rightbar.o: my_game.h my_world.h my_point.h my_math.h
.o/wid_rightbar.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/wid_rightbar.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_rightbar.o: /usr/include/sys/_posix_availability.h
.o/wid_rightbar.o: /usr/include/Availability.h
.o/wid_rightbar.o: /usr/include/AvailabilityInternal.h
.o/wid_rightbar.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/wid_rightbar.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_rightbar.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/wid_rightbar.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_rightbar.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_rightbar.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_rightbar.o: /usr/include/sys/_types/_int8_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_int16_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_int32_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_int64_t.h
.o/wid_rightbar.o: /usr/include/_types/_uint8_t.h
.o/wid_rightbar.o: /usr/include/_types/_uint16_t.h
.o/wid_rightbar.o: /usr/include/_types/_uint32_t.h
.o/wid_rightbar.o: /usr/include/_types/_uint64_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_rightbar.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_rightbar.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_rightbar.o: /usr/include/_types/_intmax_t.h
.o/wid_rightbar.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_rightbar.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/wid_rightbar.o: my_bounds_check.h /usr/include/assert.h
.o/wid_rightbar.o: my_vector_bounds_check.h my_command.h my_token.h
.o/wid_rightbar.o: my_string.h /usr/include/wchar.h
.o/wid_rightbar.o: /usr/include/sys/_types/_null.h
.o/wid_rightbar.o: /usr/include/sys/_types/_size_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_rightbar.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_rightbar.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_rightbar.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_rightbar.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_time_t.h
.o/wid_rightbar.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_rightbar.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_rightbar.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_rightbar.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_rightbar.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/wid_rightbar.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/wid_rightbar.o: my_level_static.h my_dungeon_grid.h my_wid_rightbar.h
.o/wid_rightbar.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_rightbar.o: my_wid_tiles.h my_thing.h my_light.h my_thing_template.h
.o/wid_rightbar.o: my_dice.h my_thing_ai.h
.o/wid_text_box.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_text_box.o: /usr/include/sys/cdefs.h
.o/wid_text_box.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_text_box.o: /usr/include/sys/_posix_availability.h
.o/wid_text_box.o: /usr/include/Availability.h
.o/wid_text_box.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_text_box.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_text_box.o: /usr/include/i386/_types.h
.o/wid_text_box.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_text_box.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_text_box.o: /usr/include/sys/_types/_int8_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_int16_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_int32_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_int64_t.h
.o/wid_text_box.o: /usr/include/_types/_uint8_t.h
.o/wid_text_box.o: /usr/include/_types/_uint16_t.h
.o/wid_text_box.o: /usr/include/_types/_uint32_t.h
.o/wid_text_box.o: /usr/include/_types/_uint64_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_text_box.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_text_box.o: /usr/include/_types/_intmax_t.h
.o/wid_text_box.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_text_box.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/wid_text_box.o: my_bounds_check.h /usr/include/assert.h
.o/wid_text_box.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_sdl.h
.o/wid_text_box.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid_text_box.o: /usr/include/sys/_types/_null.h
.o/wid_text_box.o: /usr/include/sys/_types/_size_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_text_box.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_text_box.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_text_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_text_box.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_time_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_text_box.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_text_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_text_box.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_text_box.o: my_wid_text_box.h my_wid.h my_ascii.h my_tex.h my_tile.h
.o/wid_text_box.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/wid_text_box.o: my_wid_tiles.h my_thing.h my_time.h my_light.h
.o/wid_text_box.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/wid_text_box.o: my_dmap.h my_thing_id.h my_ttf.h my_font.h
.o/wid_thing_collect.o: my_game.h my_world.h my_point.h my_math.h
.o/wid_thing_collect.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/wid_thing_collect.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_thing_collect.o: /usr/include/sys/_posix_availability.h
.o/wid_thing_collect.o: /usr/include/Availability.h
.o/wid_thing_collect.o: /usr/include/AvailabilityInternal.h
.o/wid_thing_collect.o: c_plus_plus_serializer.h my_level.h my_time.h
.o/wid_thing_collect.o: my_sdl.h my_main.h my_sys.h my_pcg_basic.h
.o/wid_thing_collect.o: /usr/include/inttypes.h /usr/include/_types.h
.o/wid_thing_collect.o: /usr/include/sys/_types.h
.o/wid_thing_collect.o: /usr/include/machine/_types.h
.o/wid_thing_collect.o: /usr/include/i386/_types.h
.o/wid_thing_collect.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_wchar_t.h
.o/wid_thing_collect.o: /usr/include/stdint.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_int8_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_int16_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_int32_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_int64_t.h
.o/wid_thing_collect.o: /usr/include/_types/_uint8_t.h
.o/wid_thing_collect.o: /usr/include/_types/_uint16_t.h
.o/wid_thing_collect.o: /usr/include/_types/_uint32_t.h
.o/wid_thing_collect.o: /usr/include/_types/_uint64_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_thing_collect.o: /usr/include/machine/types.h
.o/wid_thing_collect.o: /usr/include/i386/types.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_thing_collect.o: /usr/include/_types/_intmax_t.h
.o/wid_thing_collect.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_thing_collect.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/wid_thing_collect.o: my_bounds_check.h /usr/include/assert.h
.o/wid_thing_collect.o: my_vector_bounds_check.h my_command.h my_token.h
.o/wid_thing_collect.o: my_string.h /usr/include/wchar.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_null.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_size_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_rune_t.h
.o/wid_thing_collect.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_va_list.h
.o/wid_thing_collect.o: /usr/include/sys/stdio.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_off_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_thing_collect.o: /usr/include/secure/_stdio.h
.o/wid_thing_collect.o: /usr/include/secure/_common.h /usr/include/time.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_clock_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_time_t.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_timespec.h
.o/wid_thing_collect.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/wid_thing_collect.o: /usr/include/sys/_types/_wint_t.h
.o/wid_thing_collect.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_thing_collect.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_thing_collect.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/wid_thing_collect.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/wid_thing_collect.o: my_level_static.h my_dungeon_grid.h my_wid_minicon.h
.o/wid_thing_collect.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_thing_collect.o: my_wid_tiles.h my_thing.h my_light.h
.o/wid_thing_collect.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/wid_thing_collect.o: my_wid_botcon.h my_wid_popup.h my_wid_text_box.h
.o/wid_thing_collect.o: my_wid_thing_collect.h my_wid_console.h my_wid_bag.h
.o/wid_thing_info.o: my_game.h my_world.h my_point.h my_math.h
.o/wid_thing_info.o: /usr/include/math.h /usr/include/sys/cdefs.h
.o/wid_thing_info.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_thing_info.o: /usr/include/sys/_posix_availability.h
.o/wid_thing_info.o: /usr/include/Availability.h
.o/wid_thing_info.o: /usr/include/AvailabilityInternal.h
.o/wid_thing_info.o: c_plus_plus_serializer.h my_level.h my_time.h my_sdl.h
.o/wid_thing_info.o: my_main.h my_sys.h my_pcg_basic.h
.o/wid_thing_info.o: /usr/include/inttypes.h /usr/include/_types.h
.o/wid_thing_info.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_thing_info.o: /usr/include/i386/_types.h
.o/wid_thing_info.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_thing_info.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_thing_info.o: /usr/include/sys/_types/_int8_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_int16_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_int32_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_int64_t.h
.o/wid_thing_info.o: /usr/include/_types/_uint8_t.h
.o/wid_thing_info.o: /usr/include/_types/_uint16_t.h
.o/wid_thing_info.o: /usr/include/_types/_uint32_t.h
.o/wid_thing_info.o: /usr/include/_types/_uint64_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_thing_info.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_thing_info.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_thing_info.o: /usr/include/_types/_intmax_t.h
.o/wid_thing_info.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_thing_info.o: my_globals.h my_callstack.h my_array_bounds_check.h
.o/wid_thing_info.o: my_bounds_check.h /usr/include/assert.h
.o/wid_thing_info.o: my_vector_bounds_check.h my_command.h my_token.h
.o/wid_thing_info.o: my_string.h /usr/include/wchar.h
.o/wid_thing_info.o: /usr/include/sys/_types/_null.h
.o/wid_thing_info.o: /usr/include/sys/_types/_size_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_thing_info.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_thing_info.o: /usr/include/sys/stdio.h
.o/wid_thing_info.o: /usr/include/sys/_types/_off_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_thing_info.o: /usr/include/secure/_stdio.h
.o/wid_thing_info.o: /usr/include/secure/_common.h /usr/include/time.h
.o/wid_thing_info.o: /usr/include/sys/_types/_clock_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_time_t.h
.o/wid_thing_info.o: /usr/include/sys/_types/_timespec.h
.o/wid_thing_info.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/wid_thing_info.o: /usr/include/sys/_types/_wint_t.h
.o/wid_thing_info.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_thing_info.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/wid_thing_info.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h
.o/wid_thing_info.o: my_room.h my_depth.h my_charmap.h my_dmap.h
.o/wid_thing_info.o: my_level_static.h my_dungeon_grid.h my_wid_minicon.h
.o/wid_thing_info.o: my_wid.h my_ascii.h my_tex.h my_tile.h my_color.h
.o/wid_thing_info.o: my_wid_tiles.h my_thing.h my_light.h my_thing_template.h
.o/wid_thing_info.o: my_dice.h my_thing_ai.h my_wid_botcon.h my_wid_popup.h
.o/wid_thing_info.o: my_wid_text_box.h my_wid_thing_info.h my_wid_console.h
.o/wid_thing_info.o: my_wid_bag.h my_traceback.h
.o/wid_tiles.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_tiles.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_tiles.o: /usr/include/sys/_posix_availability.h
.o/wid_tiles.o: /usr/include/Availability.h
.o/wid_tiles.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_tiles.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_tiles.o: /usr/include/i386/_types.h
.o/wid_tiles.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_tiles.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_tiles.o: /usr/include/sys/_types/_int8_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int16_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int32_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int64_t.h
.o/wid_tiles.o: /usr/include/_types/_uint8_t.h
.o/wid_tiles.o: /usr/include/_types/_uint16_t.h
.o/wid_tiles.o: /usr/include/_types/_uint32_t.h
.o/wid_tiles.o: /usr/include/_types/_uint64_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_tiles.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_tiles.o: /usr/include/_types/_intmax_t.h
.o/wid_tiles.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/wid_tiles.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/wid_tiles.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_tiles.o: c_plus_plus_serializer.h my_gl.h my_color.h my_point.h
.o/wid_tiles.o: my_math.h /usr/include/math.h my_size.h my_wid_tiles.h
.o/wid_tiles.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/wid_tiles.o: /usr/include/wchar.h /usr/include/sys/_types/_null.h
.o/wid_tiles.o: /usr/include/sys/_types/_size_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/wid_tiles.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_tiles.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_tiles.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_tiles.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_time_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_tiles.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_tiles.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_tiles.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_tex.h
.o/world.o: my_dungeon.h my_room.h my_main.h my_sys.h my_pcg_basic.h
.o/world.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/world.o: /usr/include/sys/_symbol_aliasing.h
.o/world.o: /usr/include/sys/_posix_availability.h
.o/world.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/world.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/world.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/world.o: /usr/include/sys/_pthread/_pthread_types.h
.o/world.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/world.o: /usr/include/sys/_types/_int8_t.h
.o/world.o: /usr/include/sys/_types/_int16_t.h
.o/world.o: /usr/include/sys/_types/_int32_t.h
.o/world.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/world.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/world.o: /usr/include/_types/_uint64_t.h
.o/world.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/world.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/world.o: /usr/include/sys/_types/_u_int16_t.h
.o/world.o: /usr/include/sys/_types/_u_int32_t.h
.o/world.o: /usr/include/sys/_types/_u_int64_t.h
.o/world.o: /usr/include/sys/_types/_uintptr_t.h
.o/world.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/world.o: my_ptrcheck.h my_globals.h my_callstack.h my_array_bounds_check.h
.o/world.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/world.o: c_plus_plus_serializer.h my_point.h my_math.h /usr/include/math.h
.o/world.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/world.o: my_dungeon_grid.h my_thing.h my_time.h my_sdl.h my_command.h
.o/world.o: my_token.h my_string.h /usr/include/wchar.h
.o/world.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/world.o: /usr/include/sys/_types/_mbstate_t.h
.o/world.o: /usr/include/sys/_types/_ct_rune_t.h
.o/world.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/world.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/world.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/world.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/world.o: /usr/include/secure/_common.h /usr/include/time.h
.o/world.o: /usr/include/sys/_types/_clock_t.h
.o/world.o: /usr/include/sys/_types/_time_t.h
.o/world.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/world.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/world.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/world.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h my_light.h
.o/world.o: my_thing_template.h my_dice.h my_tile.h my_color.h my_size.h
.o/world.o: my_thing_ai.h my_thing_id.h
.o/world_fini.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/world_fini.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/world_fini.o: /usr/include/sys/_posix_availability.h
.o/world_fini.o: /usr/include/Availability.h
.o/world_fini.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/world_fini.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/world_fini.o: /usr/include/i386/_types.h
.o/world_fini.o: /usr/include/sys/_pthread/_pthread_types.h
.o/world_fini.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/world_fini.o: /usr/include/sys/_types/_int8_t.h
.o/world_fini.o: /usr/include/sys/_types/_int16_t.h
.o/world_fini.o: /usr/include/sys/_types/_int32_t.h
.o/world_fini.o: /usr/include/sys/_types/_int64_t.h
.o/world_fini.o: /usr/include/_types/_uint8_t.h
.o/world_fini.o: /usr/include/_types/_uint16_t.h
.o/world_fini.o: /usr/include/_types/_uint32_t.h
.o/world_fini.o: /usr/include/_types/_uint64_t.h
.o/world_fini.o: /usr/include/sys/_types/_intptr_t.h
.o/world_fini.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/world_fini.o: /usr/include/sys/_types/_u_int8_t.h
.o/world_fini.o: /usr/include/sys/_types/_u_int16_t.h
.o/world_fini.o: /usr/include/sys/_types/_u_int32_t.h
.o/world_fini.o: /usr/include/sys/_types/_u_int64_t.h
.o/world_fini.o: /usr/include/sys/_types/_uintptr_t.h
.o/world_fini.o: /usr/include/_types/_intmax_t.h
.o/world_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/world_fini.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/world_fini.o: /usr/include/assert.h my_vector_bounds_check.h
.o/world_fini.o: c_plus_plus_serializer.h my_world.h my_point.h my_math.h
.o/world_fini.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/world_fini.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/world_fini.o: /usr/include/sys/_types/_null.h
.o/world_fini.o: /usr/include/sys/_types/_size_t.h
.o/world_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/world_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/world_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/world_fini.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/world_fini.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/world_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/world_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/world_fini.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/world_fini.o: /usr/include/sys/_types/_time_t.h
.o/world_fini.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/world_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/world_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/world_fini.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/world_fini.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/world_fini.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/world_fini.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/world_fini.o: my_dice.h my_tile.h my_color.h my_thing_ai.h
.o/world_init.o: my_main.h my_sys.h my_pcg_basic.h /usr/include/inttypes.h
.o/world_init.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/world_init.o: /usr/include/sys/_posix_availability.h
.o/world_init.o: /usr/include/Availability.h
.o/world_init.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/world_init.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/world_init.o: /usr/include/i386/_types.h
.o/world_init.o: /usr/include/sys/_pthread/_pthread_types.h
.o/world_init.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/world_init.o: /usr/include/sys/_types/_int8_t.h
.o/world_init.o: /usr/include/sys/_types/_int16_t.h
.o/world_init.o: /usr/include/sys/_types/_int32_t.h
.o/world_init.o: /usr/include/sys/_types/_int64_t.h
.o/world_init.o: /usr/include/_types/_uint8_t.h
.o/world_init.o: /usr/include/_types/_uint16_t.h
.o/world_init.o: /usr/include/_types/_uint32_t.h
.o/world_init.o: /usr/include/_types/_uint64_t.h
.o/world_init.o: /usr/include/sys/_types/_intptr_t.h
.o/world_init.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/world_init.o: /usr/include/sys/_types/_u_int8_t.h
.o/world_init.o: /usr/include/sys/_types/_u_int16_t.h
.o/world_init.o: /usr/include/sys/_types/_u_int32_t.h
.o/world_init.o: /usr/include/sys/_types/_u_int64_t.h
.o/world_init.o: /usr/include/sys/_types/_uintptr_t.h
.o/world_init.o: /usr/include/_types/_intmax_t.h
.o/world_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_globals.h
.o/world_init.o: my_callstack.h my_array_bounds_check.h my_bounds_check.h
.o/world_init.o: /usr/include/assert.h my_vector_bounds_check.h
.o/world_init.o: c_plus_plus_serializer.h my_world.h my_point.h my_math.h
.o/world_init.o: /usr/include/math.h my_level.h my_time.h my_sdl.h
.o/world_init.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/world_init.o: /usr/include/sys/_types/_null.h
.o/world_init.o: /usr/include/sys/_types/_size_t.h
.o/world_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/world_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/world_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/stdio.h
.o/world_init.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/world_init.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/world_init.o: /usr/include/sys/_types/_ssize_t.h
.o/world_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/world_init.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/world_init.o: /usr/include/sys/_types/_time_t.h
.o/world_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/world_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/world_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/world_init.o: /usr/include/_ctype.h /usr/include/runetype.h slre.h
.o/world_init.o: my_particle.h my_size.h my_thing_id.h my_dungeon.h my_room.h
.o/world_init.o: my_depth.h my_charmap.h my_dmap.h my_level_static.h
.o/world_init.o: my_dungeon_grid.h my_thing.h my_light.h my_thing_template.h
.o/world_init.o: my_dice.h my_tile.h my_color.h my_thing_ai.h
