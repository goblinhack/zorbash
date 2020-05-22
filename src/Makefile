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

GAME_OBJECTS=				\
    $(OBJDIR)/ascii.o 			\
    $(OBJDIR)/ascii_box.o 		\
    $(OBJDIR)/charmap.o 		\
    $(OBJDIR)/color.o			\
    $(OBJDIR)/command.o 		\
    $(OBJDIR)/console.o 		\
    $(OBJDIR)/dice.o			\
    $(OBJDIR)/dir.o 			\
    $(OBJDIR)/dmap.o 			\
    $(OBJDIR)/dungeon.o 		\
    $(OBJDIR)/dungeon_grid.o 		\
    $(OBJDIR)/file.o 			\
    $(OBJDIR)/file_read.o 		\
    $(OBJDIR)/font.o 			\
    $(OBJDIR)/game.o 			\
    $(OBJDIR)/game_config_gfx.o		\
    $(OBJDIR)/game_config_keyboard.o	\
    $(OBJDIR)/game_config_other.o	\
    $(OBJDIR)/game_config_sound.o	\
    $(OBJDIR)/game_config_top.o 	\
    $(OBJDIR)/game_dead.o 		\
    $(OBJDIR)/game_display.o 		\
    $(OBJDIR)/game_dump.o 		\
    $(OBJDIR)/game_error.o 		\
    $(OBJDIR)/game_fini.o 		\
    $(OBJDIR)/game_init.o 		\
    $(OBJDIR)/game_load.o 		\
    $(OBJDIR)/game_log.o 		\
    $(OBJDIR)/game_main_menu.o 		\
    $(OBJDIR)/game_mouse.o		\
    $(OBJDIR)/game_notice.o 		\
    $(OBJDIR)/game_paused.o 		\
    $(OBJDIR)/game_quit.o 		\
    $(OBJDIR)/game_save.o 		\
    $(OBJDIR)/game_status.o 		\
    $(OBJDIR)/game_tick.o 		\
    $(OBJDIR)/gauss.o 			\
    $(OBJDIR)/gfx.o			\
    $(OBJDIR)/gl.o 			\
    $(OBJDIR)/globals.o 		\
    $(OBJDIR)/hacklib.o 		\
    $(OBJDIR)/hexdump.o 		\
    $(OBJDIR)/level.o 			\
    $(OBJDIR)/level_display.o 		\
    $(OBJDIR)/level_display_lava.o 	\
    $(OBJDIR)/level_display_wall.o 	\
    $(OBJDIR)/level_display_chasm.o 	\
    $(OBJDIR)/level_display_water.o 	\
    $(OBJDIR)/level_display_deep_water.o \
    $(OBJDIR)/level_scroll.o 		\
    $(OBJDIR)/level_cursor.o 		\
    $(OBJDIR)/level_cursor_path.o 	\
    $(OBJDIR)/level_fini.o 		\
    $(OBJDIR)/level_init.o 		\
    $(OBJDIR)/level_log.o 		\
    $(OBJDIR)/level_map.o 		\
    $(OBJDIR)/level_static.o 		\
    $(OBJDIR)/level_thing.o 		\
    $(OBJDIR)/light.o 			\
    $(OBJDIR)/light_log.o 		\
    $(OBJDIR)/log.o 			\
    $(OBJDIR)/log_util.o 		\
    $(OBJDIR)/main.o 			\
    $(OBJDIR)/map.o 			\
    $(OBJDIR)/minilzo.o 		\
    $(OBJDIR)/pcg_basic.o 		\
    $(OBJDIR)/player.o 			\
    $(OBJDIR)/ptrcheck.o 		\
    $(OBJDIR)/py_level.o 		\
    $(OBJDIR)/py_room.o 		\
    $(OBJDIR)/py_sdl.o 			\
    $(OBJDIR)/py_tex.o 			\
    $(OBJDIR)/py_tile.o 		\
    $(OBJDIR)/py_tp.o 			\
    $(OBJDIR)/py_ttf.o 			\
    $(OBJDIR)/python.o 			\
    $(OBJDIR)/room.o 			\
    $(OBJDIR)/sdl.o 			\
    $(OBJDIR)/sdl_screenshot.o 		\
    $(OBJDIR)/slre.o 			\
    $(OBJDIR)/sprintf.o 		\
    $(OBJDIR)/stb_image.o 		\
    $(OBJDIR)/string.o 			\
    $(OBJDIR)/tex.o 			\
    $(OBJDIR)/thing.o 			\
    $(OBJDIR)/thing_ai.o 		\
    $(OBJDIR)/thing_anim.o 		\
    $(OBJDIR)/thing_api.o 		\
    $(OBJDIR)/thing_astar.o 		\
    $(OBJDIR)/thing_attach.o 		\
    $(OBJDIR)/thing_bounce.o 		\
    $(OBJDIR)/thing_carry.o 		\
    $(OBJDIR)/thing_collision.o 	\
    $(OBJDIR)/thing_cursor.o 		\
    $(OBJDIR)/thing_cursor_path.o 	\
    $(OBJDIR)/thing_dead.o 		\
    $(OBJDIR)/thing_display.o 		\
    $(OBJDIR)/thing_enemy.o 		\
    $(OBJDIR)/thing_fadeup.o 		\
    $(OBJDIR)/thing_health.o 		\
    $(OBJDIR)/thing_hit.o 		\
    $(OBJDIR)/thing_hunger.o 		\
    $(OBJDIR)/thing_id.o 		\
    $(OBJDIR)/thing_items.o 		\
    $(OBJDIR)/thing_lava.o 		\
    $(OBJDIR)/thing_level.o 		\
    $(OBJDIR)/thing_lifespan.o 		\
    $(OBJDIR)/thing_log.o 		\
    $(OBJDIR)/thing_lunge.o 		\
    $(OBJDIR)/thing_minimap.o 		\
    $(OBJDIR)/thing_move.o 		\
    $(OBJDIR)/thing_move_dir.o 		\
    $(OBJDIR)/thing_msg.o 		\
    $(OBJDIR)/thing_name.o 		\
    $(OBJDIR)/thing_on_fire.o 		\
    $(OBJDIR)/thing_path.o 		\
    $(OBJDIR)/thing_shove.o 		\
    $(OBJDIR)/thing_string.o 		\
    $(OBJDIR)/thing_template.o 		\
    $(OBJDIR)/thing_tick.o 		\
    $(OBJDIR)/thing_tile.o 		\
    $(OBJDIR)/thing_weapon.o 		\
    $(OBJDIR)/tile.o 			\
    $(OBJDIR)/time.o 			\
    $(OBJDIR)/token.o 			\
    $(OBJDIR)/traceback.o 		\
    $(OBJDIR)/ttf.o 			\
    $(OBJDIR)/util.o 			\
    $(OBJDIR)/wid.o 			\
    $(OBJDIR)/wid_console.o 		\
    $(OBJDIR)/wid_log.o 		\
    $(OBJDIR)/wid_minicon.o 		\
    $(OBJDIR)/wid_popup.o 		\
    $(OBJDIR)/wid_test.o 		\
    $(OBJDIR)/wid_text_box.o 		\
    $(OBJDIR)/wid_tiles.o 		\
    $(OBJDIR)/world.o 			\
    $(OBJDIR)/world_fini.o 		\
    $(OBJDIR)/world_init.o 		\

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
.o/ascii.o: /usr/include/_ctype.h /usr/include/runetype.h my_point.h
.o/ascii.o: my_math.h /usr/include/math.h c_plus_plus_serializer.h my_color.h
.o/ascii.o: my_tex.h my_tile.h my_main.h my_pcg_basic.h
.o/ascii.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/ascii.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ascii.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/ascii.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ascii.o: my_ptrcheck.h my_callstack.h my_array_bounds_check.h
.o/ascii.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/ascii.o: my_globals.h my_sdl.h my_command.h my_token.h my_string.h
.o/ascii.o: my_slre.h my_font.h my_game.h my_world.h my_level.h my_time.h
.o/ascii.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ascii.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii.o: /usr/include/sys/_types/_seek_set.h
.o/ascii.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/ascii.o: /usr/include/sys/_types/_pid_t.h
.o/ascii.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/ascii.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/ascii.o: /usr/include/sys/_types/_timeval.h
.o/ascii.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii.o: /usr/include/sys/_types/_fd_set.h
.o/ascii.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ascii.o: /usr/include/sys/_types/_dev_t.h
.o/ascii.o: /usr/include/sys/_types/_mode_t.h
.o/ascii.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ascii.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ascii.o: my_depth.h my_dmap.h my_gl.h my_thing_template.h my_dice.h
.o/ascii.o: my_size.h
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
.o/ascii_box.o: /usr/include/_ctype.h /usr/include/runetype.h my_point.h
.o/ascii_box.o: my_math.h /usr/include/math.h c_plus_plus_serializer.h
.o/ascii_box.o: my_color.h my_tex.h my_tile.h my_main.h my_pcg_basic.h
.o/ascii_box.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/ascii_box.o: /usr/include/_types/_uint8_t.h
.o/ascii_box.o: /usr/include/_types/_uint16_t.h
.o/ascii_box.o: /usr/include/_types/_uint32_t.h
.o/ascii_box.o: /usr/include/_types/_uint64_t.h
.o/ascii_box.o: /usr/include/_types/_intmax_t.h
.o/ascii_box.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/ascii_box.o: my_array_bounds_check.h my_bounds_check.h
.o/ascii_box.o: /usr/include/assert.h my_vector_bounds_check.h my_globals.h
.o/ascii_box.o: my_sdl.h my_command.h my_token.h my_string.h my_slre.h
.o/charmap.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/charmap.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/charmap.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/charmap.o: /usr/include/sys/_types/_va_list.h
.o/charmap.o: /usr/include/sys/_types/_size_t.h
.o/charmap.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/charmap.o: /usr/include/sys/_types/_off_t.h
.o/charmap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/charmap.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/charmap.o: my_bounds_check.h /usr/include/assert.h
.o/charmap.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/charmap.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/charmap.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/charmap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/charmap.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/charmap.o: /usr/include/sys/_types/_clock_t.h
.o/charmap.o: /usr/include/sys/_types/_time_t.h
.o/charmap.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/charmap.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/charmap.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/charmap.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/charmap.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/charmap.o: my_charmap.h
.o/color.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/color.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/color.o: /usr/include/sys/_posix_availability.h
.o/color.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/color.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/color.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/color.o: /usr/include/sys/_types/_int8_t.h
.o/color.o: /usr/include/sys/_types/_int16_t.h
.o/color.o: /usr/include/sys/_types/_int32_t.h
.o/color.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/color.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/color.o: /usr/include/_types/_uint64_t.h
.o/color.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/color.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/color.o: /usr/include/sys/_types/_u_int16_t.h
.o/color.o: /usr/include/sys/_types/_u_int32_t.h
.o/color.o: /usr/include/sys/_types/_u_int64_t.h
.o/color.o: /usr/include/sys/_types/_uintptr_t.h
.o/color.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/color.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/color.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/color.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/color.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/color.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/color.o: c_plus_plus_serializer.h my_globals.h my_gl.h my_color.h
.o/color.o: my_point.h my_math.h /usr/include/math.h my_string.h
.o/color.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/color.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/color.o: /usr/include/sys/_types/_clock_t.h
.o/color.o: /usr/include/sys/_types/_time_t.h
.o/color.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/color.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/color.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/command.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/command.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/command.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/command.o: /usr/include/sys/_types/_va_list.h
.o/command.o: /usr/include/sys/_types/_size_t.h
.o/command.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/command.o: /usr/include/sys/_types/_off_t.h
.o/command.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/command.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/command.o: my_bounds_check.h /usr/include/assert.h
.o/command.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/command.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/command.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/command.o: /usr/include/sys/_types/_mbstate_t.h
.o/command.o: /usr/include/sys/_types/_ct_rune_t.h
.o/command.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/command.o: /usr/include/sys/_types/_clock_t.h
.o/command.o: /usr/include/sys/_types/_time_t.h
.o/command.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/command.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/command.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/command.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/command.o: my_command_history.h
.o/console.o: my_console.h my_thing_template.h my_dice.h my_tile.h my_main.h
.o/console.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/console.o: /usr/include/sys/_symbol_aliasing.h
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
.o/console.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/console.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/console.o: /usr/include/sys/_types/_va_list.h
.o/console.o: /usr/include/sys/_types/_size_t.h
.o/console.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/console.o: /usr/include/sys/_types/_off_t.h
.o/console.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/console.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/console.o: my_bounds_check.h /usr/include/assert.h
.o/console.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/console.o: my_sdl.h my_command.h my_token.h my_string.h
.o/console.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/console.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/console.o: /usr/include/sys/_types/_clock_t.h
.o/console.o: /usr/include/sys/_types/_time_t.h
.o/console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/console.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/console.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/console.o: my_point.h my_math.h /usr/include/math.h my_color.h my_size.h
.o/dice.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/dice.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/dice.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/dice.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/dice.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/dice.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dice.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/dice.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dice.o: c_plus_plus_serializer.h my_globals.h my_string.h
.o/dice.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/dice.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dice.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/dice.o: /usr/include/sys/_types/_clock_t.h
.o/dice.o: /usr/include/sys/_types/_time_t.h
.o/dice.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/dice.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/dice.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/dice.o: /usr/include/_ctype.h /usr/include/runetype.h my_dice.h
.o/dir.o: /usr/include/sys/param.h /usr/include/sys/_types.h
.o/dir.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/dir.o: /usr/include/sys/_posix_availability.h
.o/dir.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dir.o: /usr/include/sys/_types/_null.h /usr/include/sys/types.h
.o/dir.o: /usr/include/sys/appleapiopts.h /usr/include/machine/types.h
.o/dir.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/dir.o: /usr/include/sys/_types/_int16_t.h
.o/dir.o: /usr/include/sys/_types/_int32_t.h
.o/dir.o: /usr/include/sys/_types/_int64_t.h
.o/dir.o: /usr/include/sys/_types/_u_int8_t.h
.o/dir.o: /usr/include/sys/_types/_u_int16_t.h
.o/dir.o: /usr/include/sys/_types/_u_int32_t.h
.o/dir.o: /usr/include/sys/_types/_u_int64_t.h
.o/dir.o: /usr/include/sys/_types/_intptr_t.h
.o/dir.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/machine/endian.h
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
.o/dir.o: /usr/include/sys/_types/_size_t.h
.o/dir.o: /usr/include/sys/_types/_ssize_t.h
.o/dir.o: /usr/include/sys/_types/_time_t.h
.o/dir.o: /usr/include/sys/_types/_useconds_t.h
.o/dir.o: /usr/include/sys/_types/_suseconds_t.h
.o/dir.o: /usr/include/sys/_types/_rsize_t.h
.o/dir.o: /usr/include/sys/_types/_errno_t.h
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
.o/dir.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dir.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/dir.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/dir.o: /usr/include/mach/machine/_structs.h
.o/dir.o: /usr/include/mach/i386/_structs.h
.o/dir.o: /usr/include/sys/_types/_sigaltstack.h
.o/dir.o: /usr/include/sys/_types/_ucontext.h
.o/dir.o: /usr/include/sys/_types/_sigset_t.h /usr/include/unistd.h
.o/dir.o: /usr/include/_types.h /usr/include/sys/unistd.h
.o/dir.o: /usr/include/sys/_types/_posix_vdisable.h
.o/dir.o: /usr/include/sys/_types/_seek_set.h /usr/include/_types/_uint64_t.h
.o/dir.o: /usr/include/_types/_uint32_t.h /usr/include/sys/select.h
.o/dir.o: /usr/include/sys/_types/_timespec.h
.o/dir.o: /usr/include/sys/_types/_timeval.h /usr/include/sys/_select.h
.o/dir.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/dir.o: /usr/include/sys/stat.h /usr/include/sys/_types/_s_ifmt.h
.o/dir.o: /usr/include/sys/_types/_filesec_t.h my_main.h my_pcg_basic.h
.o/dir.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/dir.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/dir.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_intmax_t.h
.o/dir.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/dir.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/dir.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/dir.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/dir.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/dir.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/dir.o: my_dir.h my_string.h /usr/include/wchar.h
.o/dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/dir.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/dir.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/dir.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/dmap.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/dmap.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/dmap.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/dmap.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/dmap.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/dmap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dmap.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/dmap.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/dmap.o: c_plus_plus_serializer.h my_globals.h my_dmap.h my_point.h
.o/dmap.o: my_math.h /usr/include/math.h my_sprintf.h /usr/include/string.h
.o/dmap.o: /usr/include/sys/_types/_rsize_t.h
.o/dmap.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/dmap.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/dungeon.o: my_dungeon.h my_room.h my_main.h my_pcg_basic.h
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
.o/dungeon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/dungeon.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/dungeon.o: /usr/include/sys/_types/_va_list.h
.o/dungeon.o: /usr/include/sys/_types/_size_t.h
.o/dungeon.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/dungeon.o: /usr/include/sys/_types/_off_t.h
.o/dungeon.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dungeon.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/dungeon.o: my_bounds_check.h /usr/include/assert.h
.o/dungeon.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/dungeon.o: my_point.h my_math.h /usr/include/math.h my_depth.h
.o/dungeon.o: my_charmap.h my_dmap.h my_level_static.h my_dungeon_grid.h
.o/dungeon_grid.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/dungeon_grid.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/dungeon_grid.o: /usr/include/sys/_types/_va_list.h
.o/dungeon_grid.o: /usr/include/sys/_types/_size_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/dungeon_grid.o: /usr/include/sys/_types/_off_t.h
.o/dungeon_grid.o: /usr/include/sys/_types/_ssize_t.h
.o/dungeon_grid.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/dungeon_grid.o: my_array_bounds_check.h my_bounds_check.h
.o/dungeon_grid.o: /usr/include/assert.h my_vector_bounds_check.h
.o/dungeon_grid.o: c_plus_plus_serializer.h my_globals.h my_dmap.h my_point.h
.o/dungeon_grid.o: my_math.h /usr/include/math.h my_dungeon_grid.h
.o/file.o: /usr/include/sys/stat.h /usr/include/sys/_types.h
.o/file.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/file.o: /usr/include/sys/_posix_availability.h
.o/file.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/file.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/file.o: /usr/include/sys/_types/_timespec.h /usr/include/machine/types.h
.o/file.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/file.o: /usr/include/sys/_types/_int16_t.h
.o/file.o: /usr/include/sys/_types/_int32_t.h
.o/file.o: /usr/include/sys/_types/_int64_t.h
.o/file.o: /usr/include/sys/_types/_u_int8_t.h
.o/file.o: /usr/include/sys/_types/_u_int16_t.h
.o/file.o: /usr/include/sys/_types/_u_int32_t.h
.o/file.o: /usr/include/sys/_types/_u_int64_t.h
.o/file.o: /usr/include/sys/_types/_intptr_t.h
.o/file.o: /usr/include/sys/_types/_uintptr_t.h
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
.o/file.o: /usr/include/_types.h /usr/include/sys/unistd.h
.o/file.o: /usr/include/sys/_types/_posix_vdisable.h
.o/file.o: /usr/include/sys/_types/_seek_set.h
.o/file.o: /usr/include/sys/_types/_size_t.h /usr/include/_types/_uint64_t.h
.o/file.o: /usr/include/_types/_uint32_t.h /usr/include/sys/_types/_ssize_t.h
.o/file.o: /usr/include/sys/_types/_pid_t.h
.o/file.o: /usr/include/sys/_types/_useconds_t.h
.o/file.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
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
.o/file.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/file.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/file.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/file.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/file.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/file.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/file.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/file.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/file.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/file.o: c_plus_plus_serializer.h my_globals.h
.o/file_read.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/file_read.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/file_read.o: /usr/include/sys/_posix_availability.h
.o/file_read.o: /usr/include/Availability.h
.o/file_read.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/file_read.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/file_read.o: /usr/include/i386/_types.h
.o/file_read.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file_read.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/file_read.o: /usr/include/sys/_types/_int8_t.h
.o/file_read.o: /usr/include/sys/_types/_int16_t.h
.o/file_read.o: /usr/include/sys/_types/_int32_t.h
.o/file_read.o: /usr/include/sys/_types/_int64_t.h
.o/file_read.o: /usr/include/_types/_uint8_t.h
.o/file_read.o: /usr/include/_types/_uint16_t.h
.o/file_read.o: /usr/include/_types/_uint32_t.h
.o/file_read.o: /usr/include/_types/_uint64_t.h
.o/file_read.o: /usr/include/sys/_types/_intptr_t.h
.o/file_read.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/file_read.o: /usr/include/sys/_types/_u_int8_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int16_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int32_t.h
.o/file_read.o: /usr/include/sys/_types/_u_int64_t.h
.o/file_read.o: /usr/include/sys/_types/_uintptr_t.h
.o/file_read.o: /usr/include/_types/_intmax_t.h
.o/file_read.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/file_read.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/file_read.o: /usr/include/sys/_types/_va_list.h
.o/file_read.o: /usr/include/sys/_types/_size_t.h
.o/file_read.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/file_read.o: /usr/include/sys/_types/_off_t.h
.o/file_read.o: /usr/include/sys/_types/_ssize_t.h
.o/file_read.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/file_read.o: my_array_bounds_check.h my_bounds_check.h
.o/file_read.o: /usr/include/assert.h my_vector_bounds_check.h
.o/file_read.o: c_plus_plus_serializer.h my_globals.h my_string.h
.o/file_read.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/file_read.o: /usr/include/sys/_types/_ct_rune_t.h
.o/file_read.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/file_read.o: /usr/include/sys/_types/_clock_t.h
.o/file_read.o: /usr/include/sys/_types/_time_t.h
.o/file_read.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/file_read.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/file_read.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/file_read.o: /usr/include/_ctype.h /usr/include/runetype.h my_file.h
.o/font.o: my_ttf.h my_font.h my_tile.h my_main.h my_pcg_basic.h
.o/font.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
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
.o/font.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/font.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/font.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/font.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/font.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/font.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/font.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/font.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/font.o: my_token.h my_string.h /usr/include/wchar.h
.o/font.o: /usr/include/sys/_types/_mbstate_t.h
.o/font.o: /usr/include/sys/_types/_ct_rune_t.h
.o/font.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/font.o: /usr/include/sys/_types/_clock_t.h
.o/font.o: /usr/include/sys/_types/_time_t.h
.o/font.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/font.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/font.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/font.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/font.o: my_math.h /usr/include/math.h my_color.h
.o/game.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/game.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/game.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/game.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/game.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game.o: my_token.h my_string.h /usr/include/wchar.h
.o/game.o: /usr/include/sys/_types/_mbstate_t.h
.o/game.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game.o: /usr/include/sys/_types/_clock_t.h
.o/game.o: /usr/include/sys/_types/_time_t.h
.o/game.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/game.o: my_math.h /usr/include/math.h my_world.h my_level.h my_time.h
.o/game.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/game.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game.o: /usr/include/sys/_types/_seek_set.h
.o/game.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/game.o: /usr/include/sys/_types/_pid_t.h
.o/game.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/game.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/game.o: /usr/include/sys/_types/_timeval.h
.o/game.o: /usr/include/sys/_types/_suseconds_t.h
.o/game.o: /usr/include/sys/_types/_sigset_t.h
.o/game.o: /usr/include/sys/_types/_fd_setsize.h
.o/game.o: /usr/include/sys/_types/_fd_set.h
.o/game.o: /usr/include/sys/_types/_fd_clr.h
.o/game.o: /usr/include/sys/_types/_fd_isset.h
.o/game.o: /usr/include/sys/_types/_fd_zero.h
.o/game.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/game.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game.o: my_depth.h my_dmap.h
.o/game_config_gfx.o: my_game.h my_main.h my_pcg_basic.h
.o/game_config_gfx.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_config_gfx.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_gfx.o: /usr/include/sys/_posix_availability.h
.o/game_config_gfx.o: /usr/include/Availability.h
.o/game_config_gfx.o: /usr/include/AvailabilityInternal.h
.o/game_config_gfx.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_config_gfx.o: /usr/include/machine/_types.h
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
.o/game_config_gfx.o: my_callstack.h /usr/include/stdio.h
.o/game_config_gfx.o: /usr/include/_stdio.h
.o/game_config_gfx.o: /usr/include/sys/_types/_va_list.h
.o/game_config_gfx.o: /usr/include/sys/_types/_size_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_null.h
.o/game_config_gfx.o: /usr/include/sys/stdio.h
.o/game_config_gfx.o: /usr/include/sys/_types/_off_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_gfx.o: /usr/include/secure/_stdio.h
.o/game_config_gfx.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game_config_gfx.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_gfx.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/game_config_gfx.o: my_globals.h my_sdl.h my_command.h my_token.h
.o/game_config_gfx.o: my_string.h /usr/include/wchar.h
.o/game_config_gfx.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_config_gfx.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_time_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_timespec.h
.o/game_config_gfx.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_gfx.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_gfx.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_gfx.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_config_gfx.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_config_gfx.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_config_gfx.o: /usr/include/sys/unistd.h
.o/game_config_gfx.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_config_gfx.o: /usr/include/sys/_types/_seek_set.h
.o/game_config_gfx.o: /usr/include/sys/_types/_uid_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_gid_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_pid_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_useconds_t.h
.o/game_config_gfx.o: /usr/include/sys/select.h
.o/game_config_gfx.o: /usr/include/sys/appleapiopts.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_def.h
.o/game_config_gfx.o: /usr/include/sys/_types/_timeval.h
.o/game_config_gfx.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_sigset_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_set.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_clr.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_isset.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_zero.h
.o/game_config_gfx.o: /usr/include/sys/_types/_fd_copy.h
.o/game_config_gfx.o: /usr/include/sys/_select.h
.o/game_config_gfx.o: /usr/include/sys/_types/_dev_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_mode_t.h
.o/game_config_gfx.o: /usr/include/sys/_types/_uuid_t.h
.o/game_config_gfx.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_config_gfx.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/game_config_gfx.o: my_dmap.h my_wid_popup.h my_wid_text_box.h my_wid.h
.o/game_config_gfx.o: my_size.h my_ascii.h my_color.h my_tex.h my_tile.h
.o/game_config_gfx.o: my_wid_tiles.h
.o/game_config_keyboard.o: my_game.h my_main.h my_pcg_basic.h
.o/game_config_keyboard.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_config_keyboard.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_keyboard.o: /usr/include/sys/_posix_availability.h
.o/game_config_keyboard.o: /usr/include/Availability.h
.o/game_config_keyboard.o: /usr/include/AvailabilityInternal.h
.o/game_config_keyboard.o: /usr/include/_types.h /usr/include/sys/_types.h
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
.o/game_config_keyboard.o: my_callstack.h /usr/include/stdio.h
.o/game_config_keyboard.o: /usr/include/_stdio.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_va_list.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_size_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_null.h
.o/game_config_keyboard.o: /usr/include/sys/stdio.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_off_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_keyboard.o: /usr/include/secure/_stdio.h
.o/game_config_keyboard.o: /usr/include/secure/_common.h
.o/game_config_keyboard.o: my_array_bounds_check.h my_bounds_check.h
.o/game_config_keyboard.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_config_keyboard.o: c_plus_plus_serializer.h my_globals.h my_sdl.h
.o/game_config_keyboard.o: my_command.h my_token.h my_string.h
.o/game_config_keyboard.o: /usr/include/wchar.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_rune_t.h
.o/game_config_keyboard.o: /usr/include/time.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_time_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_timespec.h
.o/game_config_keyboard.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_keyboard.o: /usr/include/_types/_wctype_t.h
.o/game_config_keyboard.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/game_config_keyboard.o: /usr/include/runetype.h my_slre.h my_point.h
.o/game_config_keyboard.o: my_math.h /usr/include/math.h my_world.h
.o/game_config_keyboard.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_config_keyboard.o: /usr/include/sys/unistd.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_seek_set.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_uid_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_gid_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_pid_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_useconds_t.h
.o/game_config_keyboard.o: /usr/include/sys/select.h
.o/game_config_keyboard.o: /usr/include/sys/appleapiopts.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_def.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_timeval.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_sigset_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_set.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_clr.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_isset.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_zero.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_fd_copy.h
.o/game_config_keyboard.o: /usr/include/sys/_select.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_dev_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_mode_t.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_uuid_t.h
.o/game_config_keyboard.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_config_keyboard.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/game_config_keyboard.o: my_dmap.h my_wid_popup.h my_wid_text_box.h
.o/game_config_keyboard.o: my_wid.h my_size.h my_ascii.h my_color.h my_tex.h
.o/game_config_keyboard.o: my_tile.h my_wid_tiles.h my_game_notice.h
.o/game_config_other.o: my_game.h my_main.h my_pcg_basic.h
.o/game_config_other.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_config_other.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_other.o: /usr/include/sys/_posix_availability.h
.o/game_config_other.o: /usr/include/Availability.h
.o/game_config_other.o: /usr/include/AvailabilityInternal.h
.o/game_config_other.o: /usr/include/_types.h /usr/include/sys/_types.h
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
.o/game_config_other.o: my_callstack.h /usr/include/stdio.h
.o/game_config_other.o: /usr/include/_stdio.h
.o/game_config_other.o: /usr/include/sys/_types/_va_list.h
.o/game_config_other.o: /usr/include/sys/_types/_size_t.h
.o/game_config_other.o: /usr/include/sys/_types/_null.h
.o/game_config_other.o: /usr/include/sys/stdio.h
.o/game_config_other.o: /usr/include/sys/_types/_off_t.h
.o/game_config_other.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_other.o: /usr/include/secure/_stdio.h
.o/game_config_other.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game_config_other.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_other.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/game_config_other.o: my_globals.h my_sdl.h my_command.h my_token.h
.o/game_config_other.o: my_string.h /usr/include/wchar.h
.o/game_config_other.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_other.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_other.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_config_other.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_other.o: /usr/include/sys/_types/_time_t.h
.o/game_config_other.o: /usr/include/sys/_types/_timespec.h
.o/game_config_other.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_other.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_other.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_other.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/game_config_other.o: my_slre.h my_point.h my_math.h /usr/include/math.h
.o/game_config_other.o: my_world.h my_level.h my_time.h /usr/include/unistd.h
.o/game_config_other.o: /usr/include/sys/unistd.h
.o/game_config_other.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_config_other.o: /usr/include/sys/_types/_seek_set.h
.o/game_config_other.o: /usr/include/sys/_types/_uid_t.h
.o/game_config_other.o: /usr/include/sys/_types/_gid_t.h
.o/game_config_other.o: /usr/include/sys/_types/_pid_t.h
.o/game_config_other.o: /usr/include/sys/_types/_useconds_t.h
.o/game_config_other.o: /usr/include/sys/select.h
.o/game_config_other.o: /usr/include/sys/appleapiopts.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_def.h
.o/game_config_other.o: /usr/include/sys/_types/_timeval.h
.o/game_config_other.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_config_other.o: /usr/include/sys/_types/_sigset_t.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_set.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_clr.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_isset.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_zero.h
.o/game_config_other.o: /usr/include/sys/_types/_fd_copy.h
.o/game_config_other.o: /usr/include/sys/_select.h
.o/game_config_other.o: /usr/include/sys/_types/_dev_t.h
.o/game_config_other.o: /usr/include/sys/_types/_mode_t.h
.o/game_config_other.o: /usr/include/sys/_types/_uuid_t.h
.o/game_config_other.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_config_other.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/game_config_other.o: my_dmap.h my_wid_popup.h my_wid_text_box.h my_wid.h
.o/game_config_other.o: my_size.h my_ascii.h my_color.h my_tex.h my_tile.h
.o/game_config_other.o: my_wid_tiles.h
.o/game_config_sound.o: my_game.h my_main.h my_pcg_basic.h
.o/game_config_sound.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_config_sound.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_sound.o: /usr/include/sys/_posix_availability.h
.o/game_config_sound.o: /usr/include/Availability.h
.o/game_config_sound.o: /usr/include/AvailabilityInternal.h
.o/game_config_sound.o: /usr/include/_types.h /usr/include/sys/_types.h
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
.o/game_config_sound.o: my_callstack.h /usr/include/stdio.h
.o/game_config_sound.o: /usr/include/_stdio.h
.o/game_config_sound.o: /usr/include/sys/_types/_va_list.h
.o/game_config_sound.o: /usr/include/sys/_types/_size_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_null.h
.o/game_config_sound.o: /usr/include/sys/stdio.h
.o/game_config_sound.o: /usr/include/sys/_types/_off_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_sound.o: /usr/include/secure/_stdio.h
.o/game_config_sound.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game_config_sound.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_sound.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/game_config_sound.o: my_globals.h my_sdl.h my_command.h my_token.h
.o/game_config_sound.o: my_string.h /usr/include/wchar.h
.o/game_config_sound.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_config_sound.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_time_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_timespec.h
.o/game_config_sound.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_sound.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_sound.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_sound.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/game_config_sound.o: my_slre.h my_point.h my_math.h /usr/include/math.h
.o/game_config_sound.o: my_world.h my_level.h my_time.h /usr/include/unistd.h
.o/game_config_sound.o: /usr/include/sys/unistd.h
.o/game_config_sound.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_config_sound.o: /usr/include/sys/_types/_seek_set.h
.o/game_config_sound.o: /usr/include/sys/_types/_uid_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_gid_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_pid_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_useconds_t.h
.o/game_config_sound.o: /usr/include/sys/select.h
.o/game_config_sound.o: /usr/include/sys/appleapiopts.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_def.h
.o/game_config_sound.o: /usr/include/sys/_types/_timeval.h
.o/game_config_sound.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_sigset_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_set.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_clr.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_isset.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_zero.h
.o/game_config_sound.o: /usr/include/sys/_types/_fd_copy.h
.o/game_config_sound.o: /usr/include/sys/_select.h
.o/game_config_sound.o: /usr/include/sys/_types/_dev_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_mode_t.h
.o/game_config_sound.o: /usr/include/sys/_types/_uuid_t.h
.o/game_config_sound.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_config_sound.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/game_config_sound.o: my_dmap.h my_wid_popup.h my_wid_text_box.h my_wid.h
.o/game_config_sound.o: my_size.h my_ascii.h my_color.h my_tex.h my_tile.h
.o/game_config_sound.o: my_wid_tiles.h
.o/game_config_top.o: my_game.h my_main.h my_pcg_basic.h
.o/game_config_top.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_config_top.o: /usr/include/sys/_symbol_aliasing.h
.o/game_config_top.o: /usr/include/sys/_posix_availability.h
.o/game_config_top.o: /usr/include/Availability.h
.o/game_config_top.o: /usr/include/AvailabilityInternal.h
.o/game_config_top.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_config_top.o: /usr/include/machine/_types.h
.o/game_config_top.o: /usr/include/i386/_types.h
.o/game_config_top.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_config_top.o: /usr/include/sys/_types/_wchar_t.h
.o/game_config_top.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/game_config_top.o: /usr/include/sys/_types/_int16_t.h
.o/game_config_top.o: /usr/include/sys/_types/_int32_t.h
.o/game_config_top.o: /usr/include/sys/_types/_int64_t.h
.o/game_config_top.o: /usr/include/_types/_uint8_t.h
.o/game_config_top.o: /usr/include/_types/_uint16_t.h
.o/game_config_top.o: /usr/include/_types/_uint32_t.h
.o/game_config_top.o: /usr/include/_types/_uint64_t.h
.o/game_config_top.o: /usr/include/sys/_types/_intptr_t.h
.o/game_config_top.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_config_top.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_config_top.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_config_top.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_config_top.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_config_top.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_config_top.o: /usr/include/_types/_intmax_t.h
.o/game_config_top.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_config_top.o: my_callstack.h /usr/include/stdio.h
.o/game_config_top.o: /usr/include/_stdio.h
.o/game_config_top.o: /usr/include/sys/_types/_va_list.h
.o/game_config_top.o: /usr/include/sys/_types/_size_t.h
.o/game_config_top.o: /usr/include/sys/_types/_null.h
.o/game_config_top.o: /usr/include/sys/stdio.h
.o/game_config_top.o: /usr/include/sys/_types/_off_t.h
.o/game_config_top.o: /usr/include/sys/_types/_ssize_t.h
.o/game_config_top.o: /usr/include/secure/_stdio.h
.o/game_config_top.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game_config_top.o: my_bounds_check.h /usr/include/assert.h
.o/game_config_top.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/game_config_top.o: my_globals.h my_sdl.h my_command.h my_token.h
.o/game_config_top.o: my_string.h /usr/include/wchar.h
.o/game_config_top.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_config_top.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_config_top.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_config_top.o: /usr/include/sys/_types/_clock_t.h
.o/game_config_top.o: /usr/include/sys/_types/_time_t.h
.o/game_config_top.o: /usr/include/sys/_types/_timespec.h
.o/game_config_top.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_config_top.o: /usr/include/sys/_types/_wint_t.h
.o/game_config_top.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_config_top.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_config_top.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_config_top.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_config_top.o: /usr/include/sys/unistd.h
.o/game_config_top.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_config_top.o: /usr/include/sys/_types/_seek_set.h
.o/game_config_top.o: /usr/include/sys/_types/_uid_t.h
.o/game_config_top.o: /usr/include/sys/_types/_gid_t.h
.o/game_config_top.o: /usr/include/sys/_types/_pid_t.h
.o/game_config_top.o: /usr/include/sys/_types/_useconds_t.h
.o/game_config_top.o: /usr/include/sys/select.h
.o/game_config_top.o: /usr/include/sys/appleapiopts.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_def.h
.o/game_config_top.o: /usr/include/sys/_types/_timeval.h
.o/game_config_top.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_config_top.o: /usr/include/sys/_types/_sigset_t.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_set.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_clr.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_isset.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_zero.h
.o/game_config_top.o: /usr/include/sys/_types/_fd_copy.h
.o/game_config_top.o: /usr/include/sys/_select.h
.o/game_config_top.o: /usr/include/sys/_types/_dev_t.h
.o/game_config_top.o: /usr/include/sys/_types/_mode_t.h
.o/game_config_top.o: /usr/include/sys/_types/_uuid_t.h
.o/game_config_top.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_config_top.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/game_config_top.o: my_dmap.h my_wid_popup.h my_wid_text_box.h my_wid.h
.o/game_config_top.o: my_size.h my_ascii.h my_color.h my_tex.h my_tile.h
.o/game_config_top.o: my_wid_tiles.h my_game_status.h
.o/game_dead.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_dead.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_dead.o: /usr/include/sys/_posix_availability.h
.o/game_dead.o: /usr/include/Availability.h
.o/game_dead.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_dead.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_dead.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_dead.o: /usr/include/sys/_types/_va_list.h
.o/game_dead.o: /usr/include/sys/_types/_size_t.h
.o/game_dead.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_dead.o: /usr/include/sys/_types/_off_t.h
.o/game_dead.o: /usr/include/sys/_types/_ssize_t.h
.o/game_dead.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_dead.o: my_array_bounds_check.h my_bounds_check.h
.o/game_dead.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_dead.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_dead.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_dead.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_dead.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_dead.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_dead.o: /usr/include/sys/_types/_clock_t.h
.o/game_dead.o: /usr/include/sys/_types/_time_t.h
.o/game_dead.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_dead.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_dead.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_dead.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_dead.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_dead.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_dead.o: /usr/include/sys/unistd.h
.o/game_dead.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_dead.o: /usr/include/sys/_types/_seek_set.h
.o/game_dead.o: /usr/include/sys/_types/_uid_t.h
.o/game_dead.o: /usr/include/sys/_types/_gid_t.h
.o/game_dead.o: /usr/include/sys/_types/_pid_t.h
.o/game_dead.o: /usr/include/sys/_types/_useconds_t.h
.o/game_dead.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_dead.o: /usr/include/sys/_types/_fd_def.h
.o/game_dead.o: /usr/include/sys/_types/_timeval.h
.o/game_dead.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_dead.o: /usr/include/sys/_types/_sigset_t.h
.o/game_dead.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_dead.o: /usr/include/sys/_types/_fd_set.h
.o/game_dead.o: /usr/include/sys/_types/_fd_clr.h
.o/game_dead.o: /usr/include/sys/_types/_fd_isset.h
.o/game_dead.o: /usr/include/sys/_types/_fd_zero.h
.o/game_dead.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_dead.o: /usr/include/sys/_types/_dev_t.h
.o/game_dead.o: /usr/include/sys/_types/_mode_t.h
.o/game_dead.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_dead.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_dead.o: my_depth.h my_dmap.h my_wid_minicon.h my_size.h my_wid.h
.o/game_dead.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/game_dead.o: my_wid_popup.h my_wid_text_box.h
.o/game_display.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_display.o: /usr/include/sys/cdefs.h
.o/game_display.o: /usr/include/sys/_symbol_aliasing.h
.o/game_display.o: /usr/include/sys/_posix_availability.h
.o/game_display.o: /usr/include/Availability.h
.o/game_display.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_display.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_display.o: /usr/include/i386/_types.h
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
.o/game_display.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game_display.o: /usr/include/sys/_types/_va_list.h
.o/game_display.o: /usr/include/sys/_types/_size_t.h
.o/game_display.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_display.o: /usr/include/sys/_types/_off_t.h
.o/game_display.o: /usr/include/sys/_types/_ssize_t.h
.o/game_display.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_display.o: my_array_bounds_check.h my_bounds_check.h
.o/game_display.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_display.o: c_plus_plus_serializer.h my_globals.h my_sdl.h
.o/game_display.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/game_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_display.o: /usr/include/sys/_types/_clock_t.h
.o/game_display.o: /usr/include/sys/_types/_time_t.h
.o/game_display.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_display.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_display.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_display.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_display.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_display.o: /usr/include/sys/unistd.h
.o/game_display.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_display.o: /usr/include/sys/_types/_seek_set.h
.o/game_display.o: /usr/include/sys/_types/_uid_t.h
.o/game_display.o: /usr/include/sys/_types/_gid_t.h
.o/game_display.o: /usr/include/sys/_types/_pid_t.h
.o/game_display.o: /usr/include/sys/_types/_useconds_t.h
.o/game_display.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_display.o: /usr/include/sys/_types/_fd_def.h
.o/game_display.o: /usr/include/sys/_types/_timeval.h
.o/game_display.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_display.o: /usr/include/sys/_types/_sigset_t.h
.o/game_display.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_display.o: /usr/include/sys/_types/_fd_set.h
.o/game_display.o: /usr/include/sys/_types/_fd_clr.h
.o/game_display.o: /usr/include/sys/_types/_fd_isset.h
.o/game_display.o: /usr/include/sys/_types/_fd_zero.h
.o/game_display.o: /usr/include/sys/_types/_fd_copy.h
.o/game_display.o: /usr/include/sys/_select.h
.o/game_display.o: /usr/include/sys/_types/_dev_t.h
.o/game_display.o: /usr/include/sys/_types/_mode_t.h
.o/game_display.o: /usr/include/sys/_types/_uuid_t.h
.o/game_display.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_display.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/game_display.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/game_display.o: my_tile.h my_color.h my_size.h my_thing_ai.h
.o/game_dump.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_dump.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_dump.o: /usr/include/sys/_posix_availability.h
.o/game_dump.o: /usr/include/Availability.h
.o/game_dump.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_dump.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_dump.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_dump.o: /usr/include/sys/_types/_va_list.h
.o/game_dump.o: /usr/include/sys/_types/_size_t.h
.o/game_dump.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_dump.o: /usr/include/sys/_types/_off_t.h
.o/game_dump.o: /usr/include/sys/_types/_ssize_t.h
.o/game_dump.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_dump.o: my_array_bounds_check.h my_bounds_check.h
.o/game_dump.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_dump.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_dump.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_dump.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_dump.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_dump.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_dump.o: /usr/include/sys/_types/_clock_t.h
.o/game_dump.o: /usr/include/sys/_types/_time_t.h
.o/game_dump.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_dump.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_dump.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_dump.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_dump.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_dump.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_dump.o: /usr/include/sys/unistd.h
.o/game_dump.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_dump.o: /usr/include/sys/_types/_seek_set.h
.o/game_dump.o: /usr/include/sys/_types/_uid_t.h
.o/game_dump.o: /usr/include/sys/_types/_gid_t.h
.o/game_dump.o: /usr/include/sys/_types/_pid_t.h
.o/game_dump.o: /usr/include/sys/_types/_useconds_t.h
.o/game_dump.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_dump.o: /usr/include/sys/_types/_fd_def.h
.o/game_dump.o: /usr/include/sys/_types/_timeval.h
.o/game_dump.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_dump.o: /usr/include/sys/_types/_sigset_t.h
.o/game_dump.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_dump.o: /usr/include/sys/_types/_fd_set.h
.o/game_dump.o: /usr/include/sys/_types/_fd_clr.h
.o/game_dump.o: /usr/include/sys/_types/_fd_isset.h
.o/game_dump.o: /usr/include/sys/_types/_fd_zero.h
.o/game_dump.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_dump.o: /usr/include/sys/_types/_dev_t.h
.o/game_dump.o: /usr/include/sys/_types/_mode_t.h
.o/game_dump.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_dump.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_dump.o: my_depth.h my_dmap.h my_thing.h my_light.h
.o/game_dump.o: my_thing_template.h my_dice.h my_tile.h my_color.h my_size.h
.o/game_dump.o: my_thing_ai.h
.o/game_error.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_error.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_error.o: /usr/include/sys/_posix_availability.h
.o/game_error.o: /usr/include/Availability.h
.o/game_error.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_error.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_error.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game_error.o: /usr/include/sys/_types/_va_list.h
.o/game_error.o: /usr/include/sys/_types/_size_t.h
.o/game_error.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_error.o: /usr/include/sys/_types/_off_t.h
.o/game_error.o: /usr/include/sys/_types/_ssize_t.h
.o/game_error.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_error.o: my_array_bounds_check.h my_bounds_check.h
.o/game_error.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_error.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_error.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_error.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_error.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_error.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_error.o: /usr/include/sys/_types/_clock_t.h
.o/game_error.o: /usr/include/sys/_types/_time_t.h
.o/game_error.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_error.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_error.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_error.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_error.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_error.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_error.o: /usr/include/sys/unistd.h
.o/game_error.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_error.o: /usr/include/sys/_types/_seek_set.h
.o/game_error.o: /usr/include/sys/_types/_uid_t.h
.o/game_error.o: /usr/include/sys/_types/_gid_t.h
.o/game_error.o: /usr/include/sys/_types/_pid_t.h
.o/game_error.o: /usr/include/sys/_types/_useconds_t.h
.o/game_error.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_error.o: /usr/include/sys/_types/_fd_def.h
.o/game_error.o: /usr/include/sys/_types/_timeval.h
.o/game_error.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_error.o: /usr/include/sys/_types/_sigset_t.h
.o/game_error.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_error.o: /usr/include/sys/_types/_fd_set.h
.o/game_error.o: /usr/include/sys/_types/_fd_clr.h
.o/game_error.o: /usr/include/sys/_types/_fd_isset.h
.o/game_error.o: /usr/include/sys/_types/_fd_zero.h
.o/game_error.o: /usr/include/sys/_types/_fd_copy.h
.o/game_error.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/game_error.o: /usr/include/sys/_types/_mode_t.h
.o/game_error.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_error.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_error.o: my_depth.h my_dmap.h my_wid_popup.h my_wid_text_box.h
.o/game_error.o: my_wid.h my_size.h my_ascii.h my_color.h my_tex.h my_tile.h
.o/game_error.o: my_wid_tiles.h my_traceback.h
.o/game_fini.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_fini.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_fini.o: /usr/include/sys/_posix_availability.h
.o/game_fini.o: /usr/include/Availability.h
.o/game_fini.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_fini.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_fini.o: /usr/include/sys/_types/_va_list.h
.o/game_fini.o: /usr/include/sys/_types/_size_t.h
.o/game_fini.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_fini.o: /usr/include/sys/_types/_off_t.h
.o/game_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/game_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_fini.o: my_array_bounds_check.h my_bounds_check.h
.o/game_fini.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_fini.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_fini.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_fini.o: /usr/include/sys/_types/_clock_t.h
.o/game_fini.o: /usr/include/sys/_types/_time_t.h
.o/game_fini.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_fini.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_fini.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_fini.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_fini.o: /usr/include/sys/unistd.h
.o/game_fini.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_fini.o: /usr/include/sys/_types/_seek_set.h
.o/game_fini.o: /usr/include/sys/_types/_uid_t.h
.o/game_fini.o: /usr/include/sys/_types/_gid_t.h
.o/game_fini.o: /usr/include/sys/_types/_pid_t.h
.o/game_fini.o: /usr/include/sys/_types/_useconds_t.h
.o/game_fini.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_fini.o: /usr/include/sys/_types/_fd_def.h
.o/game_fini.o: /usr/include/sys/_types/_timeval.h
.o/game_fini.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_fini.o: /usr/include/sys/_types/_sigset_t.h
.o/game_fini.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_fini.o: /usr/include/sys/_types/_fd_set.h
.o/game_fini.o: /usr/include/sys/_types/_fd_clr.h
.o/game_fini.o: /usr/include/sys/_types/_fd_isset.h
.o/game_fini.o: /usr/include/sys/_types/_fd_zero.h
.o/game_fini.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_fini.o: /usr/include/sys/_types/_dev_t.h
.o/game_fini.o: /usr/include/sys/_types/_mode_t.h
.o/game_fini.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_fini.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_fini.o: my_depth.h my_dmap.h
.o/game_init.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_init.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_init.o: /usr/include/sys/_posix_availability.h
.o/game_init.o: /usr/include/Availability.h
.o/game_init.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_init.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_init.o: /usr/include/sys/_types/_va_list.h
.o/game_init.o: /usr/include/sys/_types/_size_t.h
.o/game_init.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_init.o: /usr/include/sys/_types/_off_t.h
.o/game_init.o: /usr/include/sys/_types/_ssize_t.h
.o/game_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_init.o: my_array_bounds_check.h my_bounds_check.h
.o/game_init.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_init.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_init.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_init.o: /usr/include/sys/_types/_clock_t.h
.o/game_init.o: /usr/include/sys/_types/_time_t.h
.o/game_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_init.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_init.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_init.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_init.o: /usr/include/sys/unistd.h
.o/game_init.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_init.o: /usr/include/sys/_types/_seek_set.h
.o/game_init.o: /usr/include/sys/_types/_uid_t.h
.o/game_init.o: /usr/include/sys/_types/_gid_t.h
.o/game_init.o: /usr/include/sys/_types/_pid_t.h
.o/game_init.o: /usr/include/sys/_types/_useconds_t.h
.o/game_init.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_init.o: /usr/include/sys/_types/_fd_def.h
.o/game_init.o: /usr/include/sys/_types/_timeval.h
.o/game_init.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_init.o: /usr/include/sys/_types/_sigset_t.h
.o/game_init.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_init.o: /usr/include/sys/_types/_fd_set.h
.o/game_init.o: /usr/include/sys/_types/_fd_clr.h
.o/game_init.o: /usr/include/sys/_types/_fd_isset.h
.o/game_init.o: /usr/include/sys/_types/_fd_zero.h
.o/game_init.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_init.o: /usr/include/sys/_types/_dev_t.h
.o/game_init.o: /usr/include/sys/_types/_mode_t.h
.o/game_init.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_init.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_init.o: my_depth.h my_dmap.h
.o/game_load.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_load.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_load.o: /usr/include/sys/_posix_availability.h
.o/game_load.o: /usr/include/Availability.h
.o/game_load.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_load.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_load.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_load.o: /usr/include/sys/_types/_va_list.h
.o/game_load.o: /usr/include/sys/_types/_size_t.h
.o/game_load.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_load.o: /usr/include/sys/_types/_off_t.h
.o/game_load.o: /usr/include/sys/_types/_ssize_t.h
.o/game_load.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_load.o: my_array_bounds_check.h my_bounds_check.h
.o/game_load.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_load.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_load.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_load.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_load.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_load.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_load.o: /usr/include/sys/_types/_clock_t.h
.o/game_load.o: /usr/include/sys/_types/_time_t.h
.o/game_load.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_load.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_load.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_load.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_load.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_load.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_load.o: /usr/include/sys/unistd.h
.o/game_load.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_load.o: /usr/include/sys/_types/_seek_set.h
.o/game_load.o: /usr/include/sys/_types/_uid_t.h
.o/game_load.o: /usr/include/sys/_types/_gid_t.h
.o/game_load.o: /usr/include/sys/_types/_pid_t.h
.o/game_load.o: /usr/include/sys/_types/_useconds_t.h
.o/game_load.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_load.o: /usr/include/sys/_types/_fd_def.h
.o/game_load.o: /usr/include/sys/_types/_timeval.h
.o/game_load.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_load.o: /usr/include/sys/_types/_sigset_t.h
.o/game_load.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_load.o: /usr/include/sys/_types/_fd_set.h
.o/game_load.o: /usr/include/sys/_types/_fd_clr.h
.o/game_load.o: /usr/include/sys/_types/_fd_isset.h
.o/game_load.o: /usr/include/sys/_types/_fd_zero.h
.o/game_load.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_load.o: /usr/include/sys/_types/_dev_t.h
.o/game_load.o: /usr/include/sys/_types/_mode_t.h
.o/game_load.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_load.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_load.o: my_depth.h my_dmap.h minilzo.h /usr/include/limits.h
.o/game_load.o: /usr/include/machine/limits.h /usr/include/i386/limits.h
.o/game_load.o: /usr/include/i386/_limits.h /usr/include/sys/syslimits.h
.o/game_load.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/game_load.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/game_load.o: /usr/include/sys/_types/_rsize_t.h lzodefs.h lzoconf.h
.o/game_load.o: my_wid_minicon.h my_size.h my_wid.h my_ascii.h my_color.h
.o/game_load.o: my_tex.h my_tile.h my_wid_tiles.h my_wid_console.h
.o/game_load.o: my_wid_popup.h my_wid_text_box.h my_game_error.h
.o/game_load.o: my_game_status.h my_thing.h my_light.h my_thing_template.h
.o/game_load.o: my_dice.h my_thing_ai.h my_alloc.h
.o/game_log.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_log.o: /usr/include/sys/_posix_availability.h
.o/game_log.o: /usr/include/Availability.h
.o/game_log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_log.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_log.o: /usr/include/sys/_types/_va_list.h
.o/game_log.o: /usr/include/sys/_types/_size_t.h
.o/game_log.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_log.o: /usr/include/sys/_types/_off_t.h
.o/game_log.o: /usr/include/sys/_types/_ssize_t.h
.o/game_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_log.o: my_array_bounds_check.h my_bounds_check.h
.o/game_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_log.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_log.o: /usr/include/sys/_types/_clock_t.h
.o/game_log.o: /usr/include/sys/_types/_time_t.h
.o/game_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_log.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_log.o: my_point.h my_math.h /usr/include/math.h my_world.h my_level.h
.o/game_log.o: my_time.h /usr/include/unistd.h /usr/include/sys/unistd.h
.o/game_log.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_log.o: /usr/include/sys/_types/_seek_set.h
.o/game_log.o: /usr/include/sys/_types/_uid_t.h
.o/game_log.o: /usr/include/sys/_types/_gid_t.h
.o/game_log.o: /usr/include/sys/_types/_pid_t.h
.o/game_log.o: /usr/include/sys/_types/_useconds_t.h
.o/game_log.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_log.o: /usr/include/sys/_types/_fd_def.h
.o/game_log.o: /usr/include/sys/_types/_timeval.h
.o/game_log.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_log.o: /usr/include/sys/_types/_sigset_t.h
.o/game_log.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_log.o: /usr/include/sys/_types/_fd_set.h
.o/game_log.o: /usr/include/sys/_types/_fd_clr.h
.o/game_log.o: /usr/include/sys/_types/_fd_isset.h
.o/game_log.o: /usr/include/sys/_types/_fd_zero.h
.o/game_log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_log.o: /usr/include/sys/_types/_dev_t.h
.o/game_log.o: /usr/include/sys/_types/_mode_t.h
.o/game_log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_log.o: my_depth.h my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/game_log.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/game_main_menu.o: my_game.h my_main.h my_pcg_basic.h
.o/game_main_menu.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/game_main_menu.o: /usr/include/sys/_symbol_aliasing.h
.o/game_main_menu.o: /usr/include/sys/_posix_availability.h
.o/game_main_menu.o: /usr/include/Availability.h
.o/game_main_menu.o: /usr/include/AvailabilityInternal.h
.o/game_main_menu.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/game_main_menu.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
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
.o/game_main_menu.o: my_callstack.h /usr/include/stdio.h
.o/game_main_menu.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/game_main_menu.o: /usr/include/sys/_types/_size_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_main_menu.o: /usr/include/sys/_types/_off_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_ssize_t.h
.o/game_main_menu.o: /usr/include/secure/_stdio.h
.o/game_main_menu.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/game_main_menu.o: my_bounds_check.h /usr/include/assert.h
.o/game_main_menu.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/game_main_menu.o: my_globals.h my_sdl.h my_command.h my_token.h
.o/game_main_menu.o: my_string.h /usr/include/wchar.h
.o/game_main_menu.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_main_menu.o: /usr/include/sys/_types/_clock_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_time_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_timespec.h
.o/game_main_menu.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/game_main_menu.o: /usr/include/sys/_types/_wint_t.h
.o/game_main_menu.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_main_menu.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_main_menu.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_main_menu.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_main_menu.o: /usr/include/sys/unistd.h
.o/game_main_menu.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_main_menu.o: /usr/include/sys/_types/_seek_set.h
.o/game_main_menu.o: /usr/include/sys/_types/_uid_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_gid_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_pid_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_useconds_t.h
.o/game_main_menu.o: /usr/include/sys/select.h
.o/game_main_menu.o: /usr/include/sys/appleapiopts.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_def.h
.o/game_main_menu.o: /usr/include/sys/_types/_timeval.h
.o/game_main_menu.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_sigset_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_set.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_clr.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_isset.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_zero.h
.o/game_main_menu.o: /usr/include/sys/_types/_fd_copy.h
.o/game_main_menu.o: /usr/include/sys/_select.h
.o/game_main_menu.o: /usr/include/sys/_types/_dev_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_mode_t.h
.o/game_main_menu.o: /usr/include/sys/_types/_uuid_t.h
.o/game_main_menu.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_main_menu.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/game_main_menu.o: my_dmap.h my_wid_minicon.h my_size.h my_wid.h my_ascii.h
.o/game_main_menu.o: my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/game_main_menu.o: my_wid_popup.h my_wid_text_box.h my_game_status.h
.o/game_main_menu.o: my_gl.h
.o/game_mouse.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_mouse.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_mouse.o: /usr/include/sys/_posix_availability.h
.o/game_mouse.o: /usr/include/Availability.h
.o/game_mouse.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_mouse.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_mouse.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game_mouse.o: /usr/include/sys/_types/_va_list.h
.o/game_mouse.o: /usr/include/sys/_types/_size_t.h
.o/game_mouse.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_mouse.o: /usr/include/sys/_types/_off_t.h
.o/game_mouse.o: /usr/include/sys/_types/_ssize_t.h
.o/game_mouse.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_mouse.o: my_array_bounds_check.h my_bounds_check.h
.o/game_mouse.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_mouse.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_mouse.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_mouse.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_mouse.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_mouse.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_mouse.o: /usr/include/sys/_types/_clock_t.h
.o/game_mouse.o: /usr/include/sys/_types/_time_t.h
.o/game_mouse.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_mouse.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_mouse.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_mouse.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_mouse.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_mouse.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_mouse.o: /usr/include/sys/unistd.h
.o/game_mouse.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_mouse.o: /usr/include/sys/_types/_seek_set.h
.o/game_mouse.o: /usr/include/sys/_types/_uid_t.h
.o/game_mouse.o: /usr/include/sys/_types/_gid_t.h
.o/game_mouse.o: /usr/include/sys/_types/_pid_t.h
.o/game_mouse.o: /usr/include/sys/_types/_useconds_t.h
.o/game_mouse.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_def.h
.o/game_mouse.o: /usr/include/sys/_types/_timeval.h
.o/game_mouse.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_mouse.o: /usr/include/sys/_types/_sigset_t.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_set.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_clr.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_isset.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_zero.h
.o/game_mouse.o: /usr/include/sys/_types/_fd_copy.h
.o/game_mouse.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/game_mouse.o: /usr/include/sys/_types/_mode_t.h
.o/game_mouse.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_mouse.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_mouse.o: my_depth.h my_dmap.h my_thing.h my_light.h
.o/game_mouse.o: my_thing_template.h my_dice.h my_tile.h my_color.h my_size.h
.o/game_mouse.o: my_thing_ai.h
.o/game_notice.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_notice.o: /usr/include/sys/cdefs.h
.o/game_notice.o: /usr/include/sys/_symbol_aliasing.h
.o/game_notice.o: /usr/include/sys/_posix_availability.h
.o/game_notice.o: /usr/include/Availability.h
.o/game_notice.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_notice.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_notice.o: /usr/include/i386/_types.h
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
.o/game_notice.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_notice.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game_notice.o: /usr/include/sys/_types/_va_list.h
.o/game_notice.o: /usr/include/sys/_types/_size_t.h
.o/game_notice.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_notice.o: /usr/include/sys/_types/_off_t.h
.o/game_notice.o: /usr/include/sys/_types/_ssize_t.h
.o/game_notice.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_notice.o: my_array_bounds_check.h my_bounds_check.h
.o/game_notice.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_notice.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_notice.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_notice.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_notice.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_notice.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_notice.o: /usr/include/sys/_types/_clock_t.h
.o/game_notice.o: /usr/include/sys/_types/_time_t.h
.o/game_notice.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_notice.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_notice.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_notice.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_notice.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_notice.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_notice.o: /usr/include/sys/unistd.h
.o/game_notice.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_notice.o: /usr/include/sys/_types/_seek_set.h
.o/game_notice.o: /usr/include/sys/_types/_uid_t.h
.o/game_notice.o: /usr/include/sys/_types/_gid_t.h
.o/game_notice.o: /usr/include/sys/_types/_pid_t.h
.o/game_notice.o: /usr/include/sys/_types/_useconds_t.h
.o/game_notice.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_notice.o: /usr/include/sys/_types/_fd_def.h
.o/game_notice.o: /usr/include/sys/_types/_timeval.h
.o/game_notice.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_notice.o: /usr/include/sys/_types/_sigset_t.h
.o/game_notice.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_notice.o: /usr/include/sys/_types/_fd_set.h
.o/game_notice.o: /usr/include/sys/_types/_fd_clr.h
.o/game_notice.o: /usr/include/sys/_types/_fd_isset.h
.o/game_notice.o: /usr/include/sys/_types/_fd_zero.h
.o/game_notice.o: /usr/include/sys/_types/_fd_copy.h
.o/game_notice.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/game_notice.o: /usr/include/sys/_types/_mode_t.h
.o/game_notice.o: /usr/include/sys/_types/_uuid_t.h
.o/game_notice.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_notice.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/game_notice.o: my_wid_popup.h my_wid_text_box.h my_wid.h my_size.h
.o/game_notice.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/game_paused.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_paused.o: /usr/include/sys/cdefs.h
.o/game_paused.o: /usr/include/sys/_symbol_aliasing.h
.o/game_paused.o: /usr/include/sys/_posix_availability.h
.o/game_paused.o: /usr/include/Availability.h
.o/game_paused.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_paused.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_paused.o: /usr/include/i386/_types.h
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
.o/game_paused.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_paused.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game_paused.o: /usr/include/sys/_types/_va_list.h
.o/game_paused.o: /usr/include/sys/_types/_size_t.h
.o/game_paused.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_paused.o: /usr/include/sys/_types/_off_t.h
.o/game_paused.o: /usr/include/sys/_types/_ssize_t.h
.o/game_paused.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_paused.o: my_array_bounds_check.h my_bounds_check.h
.o/game_paused.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_paused.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_paused.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_paused.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_paused.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_paused.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_paused.o: /usr/include/sys/_types/_clock_t.h
.o/game_paused.o: /usr/include/sys/_types/_time_t.h
.o/game_paused.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_paused.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_paused.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_paused.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_paused.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_paused.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_paused.o: /usr/include/sys/unistd.h
.o/game_paused.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_paused.o: /usr/include/sys/_types/_seek_set.h
.o/game_paused.o: /usr/include/sys/_types/_uid_t.h
.o/game_paused.o: /usr/include/sys/_types/_gid_t.h
.o/game_paused.o: /usr/include/sys/_types/_pid_t.h
.o/game_paused.o: /usr/include/sys/_types/_useconds_t.h
.o/game_paused.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_paused.o: /usr/include/sys/_types/_fd_def.h
.o/game_paused.o: /usr/include/sys/_types/_timeval.h
.o/game_paused.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_paused.o: /usr/include/sys/_types/_sigset_t.h
.o/game_paused.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_paused.o: /usr/include/sys/_types/_fd_set.h
.o/game_paused.o: /usr/include/sys/_types/_fd_clr.h
.o/game_paused.o: /usr/include/sys/_types/_fd_isset.h
.o/game_paused.o: /usr/include/sys/_types/_fd_zero.h
.o/game_paused.o: /usr/include/sys/_types/_fd_copy.h
.o/game_paused.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/game_paused.o: /usr/include/sys/_types/_mode_t.h
.o/game_paused.o: /usr/include/sys/_types/_uuid_t.h
.o/game_paused.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_paused.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/game_paused.o: my_wid_popup.h my_wid_text_box.h my_wid.h my_size.h
.o/game_paused.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/game_quit.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_quit.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_quit.o: /usr/include/sys/_posix_availability.h
.o/game_quit.o: /usr/include/Availability.h
.o/game_quit.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_quit.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_quit.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_quit.o: /usr/include/sys/_types/_va_list.h
.o/game_quit.o: /usr/include/sys/_types/_size_t.h
.o/game_quit.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_quit.o: /usr/include/sys/_types/_off_t.h
.o/game_quit.o: /usr/include/sys/_types/_ssize_t.h
.o/game_quit.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_quit.o: my_array_bounds_check.h my_bounds_check.h
.o/game_quit.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_quit.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_quit.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_quit.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_quit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_quit.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_quit.o: /usr/include/sys/_types/_clock_t.h
.o/game_quit.o: /usr/include/sys/_types/_time_t.h
.o/game_quit.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_quit.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_quit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_quit.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_quit.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_quit.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_quit.o: /usr/include/sys/unistd.h
.o/game_quit.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_quit.o: /usr/include/sys/_types/_seek_set.h
.o/game_quit.o: /usr/include/sys/_types/_uid_t.h
.o/game_quit.o: /usr/include/sys/_types/_gid_t.h
.o/game_quit.o: /usr/include/sys/_types/_pid_t.h
.o/game_quit.o: /usr/include/sys/_types/_useconds_t.h
.o/game_quit.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_quit.o: /usr/include/sys/_types/_fd_def.h
.o/game_quit.o: /usr/include/sys/_types/_timeval.h
.o/game_quit.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_quit.o: /usr/include/sys/_types/_sigset_t.h
.o/game_quit.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_quit.o: /usr/include/sys/_types/_fd_set.h
.o/game_quit.o: /usr/include/sys/_types/_fd_clr.h
.o/game_quit.o: /usr/include/sys/_types/_fd_isset.h
.o/game_quit.o: /usr/include/sys/_types/_fd_zero.h
.o/game_quit.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_quit.o: /usr/include/sys/_types/_dev_t.h
.o/game_quit.o: /usr/include/sys/_types/_mode_t.h
.o/game_quit.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_quit.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_quit.o: my_depth.h my_dmap.h my_wid_minicon.h my_size.h my_wid.h
.o/game_quit.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/game_quit.o: my_wid_popup.h my_wid_text_box.h
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
.o/game_save.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_save.o: /usr/include/Availability.h
.o/game_save.o: /usr/include/AvailabilityInternal.h /usr/include/stdint.h
.o/game_save.o: /usr/include/_types/_uint8_t.h
.o/game_save.o: /usr/include/_types/_uint16_t.h
.o/game_save.o: /usr/include/_types/_uint32_t.h
.o/game_save.o: /usr/include/_types/_uint64_t.h
.o/game_save.o: /usr/include/_types/_intmax_t.h
.o/game_save.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_save.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_save.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/game_save.o: /usr/include/sys/_types/_off_t.h
.o/game_save.o: /usr/include/sys/_types/_ssize_t.h
.o/game_save.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_save.o: my_array_bounds_check.h my_bounds_check.h
.o/game_save.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_save.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_save.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_save.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_save.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_save.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_save.o: /usr/include/sys/_types/_clock_t.h
.o/game_save.o: /usr/include/sys/_types/_time_t.h
.o/game_save.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_save.o: /usr/include/__wctype.h /usr/include/_types/_wctype_t.h
.o/game_save.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/game_save.o: /usr/include/runetype.h my_slre.h my_point.h my_math.h
.o/game_save.o: /usr/include/math.h my_world.h my_level.h my_time.h
.o/game_save.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/game_save.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_save.o: /usr/include/sys/_types/_seek_set.h
.o/game_save.o: /usr/include/sys/_types/_uid_t.h
.o/game_save.o: /usr/include/sys/_types/_gid_t.h
.o/game_save.o: /usr/include/sys/_types/_pid_t.h
.o/game_save.o: /usr/include/sys/_types/_useconds_t.h
.o/game_save.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_save.o: /usr/include/sys/_types/_fd_def.h
.o/game_save.o: /usr/include/sys/_types/_timeval.h
.o/game_save.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_save.o: /usr/include/sys/_types/_sigset_t.h
.o/game_save.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_save.o: /usr/include/sys/_types/_fd_set.h
.o/game_save.o: /usr/include/sys/_types/_fd_clr.h
.o/game_save.o: /usr/include/sys/_types/_fd_isset.h
.o/game_save.o: /usr/include/sys/_types/_fd_zero.h
.o/game_save.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_save.o: /usr/include/sys/_types/_dev_t.h
.o/game_save.o: /usr/include/sys/_types/_mode_t.h
.o/game_save.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_save.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_save.o: my_depth.h my_dmap.h my_wid_minicon.h my_size.h my_wid.h
.o/game_save.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/game_save.o: my_wid_console.h my_wid_popup.h my_wid_text_box.h my_thing.h
.o/game_save.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/game_save.o: my_alloc.h
.o/game_status.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_status.o: /usr/include/sys/cdefs.h
.o/game_status.o: /usr/include/sys/_symbol_aliasing.h
.o/game_status.o: /usr/include/sys/_posix_availability.h
.o/game_status.o: /usr/include/Availability.h
.o/game_status.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game_status.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game_status.o: /usr/include/i386/_types.h
.o/game_status.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game_status.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/game_status.o: /usr/include/sys/_types/_int8_t.h
.o/game_status.o: /usr/include/sys/_types/_int16_t.h
.o/game_status.o: /usr/include/sys/_types/_int32_t.h
.o/game_status.o: /usr/include/sys/_types/_int64_t.h
.o/game_status.o: /usr/include/_types/_uint8_t.h
.o/game_status.o: /usr/include/_types/_uint16_t.h
.o/game_status.o: /usr/include/_types/_uint32_t.h
.o/game_status.o: /usr/include/_types/_uint64_t.h
.o/game_status.o: /usr/include/sys/_types/_intptr_t.h
.o/game_status.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/game_status.o: /usr/include/sys/_types/_u_int8_t.h
.o/game_status.o: /usr/include/sys/_types/_u_int16_t.h
.o/game_status.o: /usr/include/sys/_types/_u_int32_t.h
.o/game_status.o: /usr/include/sys/_types/_u_int64_t.h
.o/game_status.o: /usr/include/sys/_types/_uintptr_t.h
.o/game_status.o: /usr/include/_types/_intmax_t.h
.o/game_status.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/game_status.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/game_status.o: /usr/include/sys/_types/_va_list.h
.o/game_status.o: /usr/include/sys/_types/_size_t.h
.o/game_status.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_status.o: /usr/include/sys/_types/_off_t.h
.o/game_status.o: /usr/include/sys/_types/_ssize_t.h
.o/game_status.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_status.o: my_array_bounds_check.h my_bounds_check.h
.o/game_status.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_status.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_status.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_status.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_status.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_status.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_status.o: /usr/include/sys/_types/_clock_t.h
.o/game_status.o: /usr/include/sys/_types/_time_t.h
.o/game_status.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_status.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_status.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_status.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_status.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_status.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_status.o: /usr/include/sys/unistd.h
.o/game_status.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_status.o: /usr/include/sys/_types/_seek_set.h
.o/game_status.o: /usr/include/sys/_types/_uid_t.h
.o/game_status.o: /usr/include/sys/_types/_gid_t.h
.o/game_status.o: /usr/include/sys/_types/_pid_t.h
.o/game_status.o: /usr/include/sys/_types/_useconds_t.h
.o/game_status.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_status.o: /usr/include/sys/_types/_fd_def.h
.o/game_status.o: /usr/include/sys/_types/_timeval.h
.o/game_status.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_status.o: /usr/include/sys/_types/_sigset_t.h
.o/game_status.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_status.o: /usr/include/sys/_types/_fd_set.h
.o/game_status.o: /usr/include/sys/_types/_fd_clr.h
.o/game_status.o: /usr/include/sys/_types/_fd_isset.h
.o/game_status.o: /usr/include/sys/_types/_fd_zero.h
.o/game_status.o: /usr/include/sys/_types/_fd_copy.h
.o/game_status.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/game_status.o: /usr/include/sys/_types/_mode_t.h
.o/game_status.o: /usr/include/sys/_types/_uuid_t.h
.o/game_status.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/game_status.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/game_status.o: my_game_status.h my_wid.h my_size.h my_ascii.h my_color.h
.o/game_status.o: my_tex.h my_tile.h my_wid_tiles.h my_thing.h my_light.h
.o/game_status.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/game_tick.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/game_tick.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/game_tick.o: /usr/include/sys/_posix_availability.h
.o/game_tick.o: /usr/include/Availability.h
.o/game_tick.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/game_tick.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/game_tick.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/game_tick.o: /usr/include/sys/_types/_va_list.h
.o/game_tick.o: /usr/include/sys/_types/_size_t.h
.o/game_tick.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/game_tick.o: /usr/include/sys/_types/_off_t.h
.o/game_tick.o: /usr/include/sys/_types/_ssize_t.h
.o/game_tick.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/game_tick.o: my_array_bounds_check.h my_bounds_check.h
.o/game_tick.o: /usr/include/assert.h my_vector_bounds_check.h
.o/game_tick.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/game_tick.o: my_token.h my_string.h /usr/include/wchar.h
.o/game_tick.o: /usr/include/sys/_types/_mbstate_t.h
.o/game_tick.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game_tick.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game_tick.o: /usr/include/sys/_types/_clock_t.h
.o/game_tick.o: /usr/include/sys/_types/_time_t.h
.o/game_tick.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game_tick.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/game_tick.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game_tick.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/game_tick.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/game_tick.o: my_level.h my_time.h /usr/include/unistd.h
.o/game_tick.o: /usr/include/sys/unistd.h
.o/game_tick.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game_tick.o: /usr/include/sys/_types/_seek_set.h
.o/game_tick.o: /usr/include/sys/_types/_uid_t.h
.o/game_tick.o: /usr/include/sys/_types/_gid_t.h
.o/game_tick.o: /usr/include/sys/_types/_pid_t.h
.o/game_tick.o: /usr/include/sys/_types/_useconds_t.h
.o/game_tick.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/game_tick.o: /usr/include/sys/_types/_fd_def.h
.o/game_tick.o: /usr/include/sys/_types/_timeval.h
.o/game_tick.o: /usr/include/sys/_types/_suseconds_t.h
.o/game_tick.o: /usr/include/sys/_types/_sigset_t.h
.o/game_tick.o: /usr/include/sys/_types/_fd_setsize.h
.o/game_tick.o: /usr/include/sys/_types/_fd_set.h
.o/game_tick.o: /usr/include/sys/_types/_fd_clr.h
.o/game_tick.o: /usr/include/sys/_types/_fd_isset.h
.o/game_tick.o: /usr/include/sys/_types/_fd_zero.h
.o/game_tick.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game_tick.o: /usr/include/sys/_types/_dev_t.h
.o/game_tick.o: /usr/include/sys/_types/_mode_t.h
.o/game_tick.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game_tick.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game_tick.o: my_depth.h my_dmap.h my_dungeon.h my_room.h my_charmap.h
.o/game_tick.o: my_level_static.h my_dungeon_grid.h
.o/gauss.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/gauss.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/gauss.o: /usr/include/sys/_posix_availability.h
.o/gauss.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
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
.o/gauss.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/gauss.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gauss.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/gauss.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gauss.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gauss.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/gauss.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gauss.o: c_plus_plus_serializer.h my_globals.h
.o/gfx.o: my_tile.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/gfx.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
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
.o/gfx.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/gfx.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/gfx.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/gfx.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gfx.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gfx.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/gfx.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/gfx.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/gfx.o: my_token.h my_string.h /usr/include/wchar.h
.o/gfx.o: /usr/include/sys/_types/_mbstate_t.h
.o/gfx.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gfx.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/gfx.o: /usr/include/sys/_types/_clock_t.h
.o/gfx.o: /usr/include/sys/_types/_time_t.h
.o/gfx.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gfx.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gfx.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gfx.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/gfx.o: my_math.h /usr/include/math.h my_color.h
.o/gl.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/gl.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/gl.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/gl.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/gl.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/gl.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/gl.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
.o/gl.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/gl.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
.o/gl.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/gl.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/gl.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/gl.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/gl.o: /usr/include/sys/_types/_mbstate_t.h
.o/gl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gl.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/gl.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
.o/gl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gl.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/gl.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/gl.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/gl.o: my_math.h /usr/include/math.h my_world.h my_level.h my_time.h
.o/gl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/gl.o: /usr/include/sys/_types/_posix_vdisable.h
.o/gl.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_uid_t.h
.o/gl.o: /usr/include/sys/_types/_gid_t.h /usr/include/sys/_types/_pid_t.h
.o/gl.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/gl.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/gl.o: /usr/include/sys/_types/_timeval.h
.o/gl.o: /usr/include/sys/_types/_suseconds_t.h
.o/gl.o: /usr/include/sys/_types/_sigset_t.h
.o/gl.o: /usr/include/sys/_types/_fd_setsize.h
.o/gl.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/gl.o: /usr/include/sys/_types/_fd_isset.h
.o/gl.o: /usr/include/sys/_types/_fd_zero.h
.o/gl.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/gl.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/gl.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/gl.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/gl.o: my_depth.h my_dmap.h my_gl.h my_color.h my_thing_template.h
.o/gl.o: my_dice.h my_tile.h my_size.h
.o/globals.o: my_globals.h /usr/include/stdio.h /usr/include/_stdio.h
.o/globals.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/globals.o: /usr/include/sys/_posix_availability.h
.o/globals.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/globals.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/globals.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/globals.o: /usr/include/sys/_pthread/_pthread_types.h
.o/globals.o: /usr/include/sys/_types/_va_list.h /usr/include/machine/types.h
.o/globals.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/globals.o: /usr/include/sys/_types/_int16_t.h
.o/globals.o: /usr/include/sys/_types/_int32_t.h
.o/globals.o: /usr/include/sys/_types/_int64_t.h
.o/globals.o: /usr/include/sys/_types/_u_int8_t.h
.o/globals.o: /usr/include/sys/_types/_u_int16_t.h
.o/globals.o: /usr/include/sys/_types/_u_int32_t.h
.o/globals.o: /usr/include/sys/_types/_u_int64_t.h
.o/globals.o: /usr/include/sys/_types/_intptr_t.h
.o/globals.o: /usr/include/sys/_types/_uintptr_t.h
.o/globals.o: /usr/include/sys/_types/_size_t.h
.o/globals.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/globals.o: /usr/include/sys/_types/_off_t.h
.o/globals.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/globals.o: /usr/include/secure/_common.h
.o/hacklib.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/hacklib.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/hacklib.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/hacklib.o: /usr/include/sys/_types/_va_list.h
.o/hacklib.o: /usr/include/sys/_types/_size_t.h
.o/hacklib.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/hacklib.o: /usr/include/sys/_types/_off_t.h
.o/hacklib.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/hacklib.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/hacklib.o: my_bounds_check.h /usr/include/assert.h
.o/hacklib.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/level.o: my_level.h my_point.h my_math.h /usr/include/math.h
.o/level.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level.o: /usr/include/sys/_posix_availability.h
.o/level.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/level.o: c_plus_plus_serializer.h my_time.h /usr/include/assert.h
.o/level.o: /usr/include/unistd.h /usr/include/_types.h
.o/level.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level.o: /usr/include/i386/_types.h
.o/level.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level.o: /usr/include/sys/unistd.h
.o/level.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level.o: /usr/include/sys/_types/_seek_set.h
.o/level.o: /usr/include/sys/_types/_size_t.h /usr/include/_types/_uint64_t.h
.o/level.o: /usr/include/_types/_uint32_t.h
.o/level.o: /usr/include/sys/_types/_ssize_t.h /usr/include/machine/types.h
.o/level.o: /usr/include/i386/types.h /usr/include/sys/_types/_int8_t.h
.o/level.o: /usr/include/sys/_types/_int16_t.h
.o/level.o: /usr/include/sys/_types/_int32_t.h
.o/level.o: /usr/include/sys/_types/_int64_t.h
.o/level.o: /usr/include/sys/_types/_u_int8_t.h
.o/level.o: /usr/include/sys/_types/_u_int16_t.h
.o/level.o: /usr/include/sys/_types/_u_int32_t.h
.o/level.o: /usr/include/sys/_types/_u_int64_t.h
.o/level.o: /usr/include/sys/_types/_intptr_t.h
.o/level.o: /usr/include/sys/_types/_uintptr_t.h
.o/level.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/level.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_pid_t.h
.o/level.o: /usr/include/sys/_types/_useconds_t.h
.o/level.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/level.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/level.o: /usr/include/sys/_types/_timespec.h
.o/level.o: /usr/include/sys/_types/_timeval.h
.o/level.o: /usr/include/sys/_types/_time_t.h
.o/level.o: /usr/include/sys/_types/_suseconds_t.h
.o/level.o: /usr/include/sys/_types/_sigset_t.h
.o/level.o: /usr/include/sys/_types/_fd_setsize.h
.o/level.o: /usr/include/sys/_types/_fd_set.h
.o/level.o: /usr/include/sys/_types/_fd_clr.h
.o/level.o: /usr/include/sys/_types/_fd_isset.h
.o/level.o: /usr/include/sys/_types/_fd_zero.h
.o/level.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/level.o: /usr/include/sys/_types/_dev_t.h
.o/level.o: /usr/include/sys/_types/_mode_t.h
.o/level.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/level.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/level.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/level.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/level.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/level.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/level.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/level.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/level.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/level.o: my_bounds_check.h my_vector_bounds_check.h my_globals.h
.o/level.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level.o: /usr/include/sys/_types/_mbstate_t.h
.o/level.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/level.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level.o: my_depth.h
.o/level_cursor.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/level_cursor.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_cursor.o: /usr/include/sys/_types/_va_list.h
.o/level_cursor.o: /usr/include/sys/_types/_size_t.h
.o/level_cursor.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/level_cursor.o: /usr/include/sys/_types/_off_t.h
.o/level_cursor.o: /usr/include/sys/_types/_ssize_t.h
.o/level_cursor.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_cursor.o: my_array_bounds_check.h my_bounds_check.h
.o/level_cursor.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_cursor.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/level_cursor.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_cursor.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_cursor.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_cursor.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_cursor.o: /usr/include/sys/_types/_clock_t.h
.o/level_cursor.o: /usr/include/sys/_types/_time_t.h
.o/level_cursor.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_cursor.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_cursor.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_cursor.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_cursor.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/level_cursor.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_cursor.o: /usr/include/sys/unistd.h
.o/level_cursor.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_cursor.o: /usr/include/sys/_types/_seek_set.h
.o/level_cursor.o: /usr/include/sys/_types/_uid_t.h
.o/level_cursor.o: /usr/include/sys/_types/_gid_t.h
.o/level_cursor.o: /usr/include/sys/_types/_pid_t.h
.o/level_cursor.o: /usr/include/sys/_types/_useconds_t.h
.o/level_cursor.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_def.h
.o/level_cursor.o: /usr/include/sys/_types/_timeval.h
.o/level_cursor.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_cursor.o: /usr/include/sys/_types/_sigset_t.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_set.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_clr.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_isset.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_zero.h
.o/level_cursor.o: /usr/include/sys/_types/_fd_copy.h
.o/level_cursor.o: /usr/include/sys/_select.h
.o/level_cursor.o: /usr/include/sys/_types/_dev_t.h
.o/level_cursor.o: /usr/include/sys/_types/_mode_t.h
.o/level_cursor.o: /usr/include/sys/_types/_uuid_t.h
.o/level_cursor.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_cursor.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/level_cursor.o: my_tile.h my_color.h my_tex.h my_gl.h my_thing.h
.o/level_cursor.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/level_cursor.o: my_thing_ai.h
.o/level_cursor_path.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_cursor_path.o: /usr/include/sys/cdefs.h
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
.o/level_cursor_path.o: my_callstack.h /usr/include/stdio.h
.o/level_cursor_path.o: /usr/include/_stdio.h
.o/level_cursor_path.o: /usr/include/sys/_types/_va_list.h
.o/level_cursor_path.o: /usr/include/sys/_types/_size_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_null.h
.o/level_cursor_path.o: /usr/include/sys/stdio.h
.o/level_cursor_path.o: /usr/include/sys/_types/_off_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_ssize_t.h
.o/level_cursor_path.o: /usr/include/secure/_stdio.h
.o/level_cursor_path.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/level_cursor_path.o: my_bounds_check.h /usr/include/assert.h
.o/level_cursor_path.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_cursor_path.o: my_globals.h my_game.h my_sdl.h my_command.h
.o/level_cursor_path.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_cursor_path.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_cursor_path.o: /usr/include/sys/_types/_clock_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_time_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_timespec.h
.o/level_cursor_path.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_cursor_path.o: /usr/include/sys/_types/_wint_t.h
.o/level_cursor_path.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_cursor_path.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/level_cursor_path.o: my_slre.h my_point.h my_math.h /usr/include/math.h
.o/level_cursor_path.o: my_world.h my_level.h my_time.h /usr/include/unistd.h
.o/level_cursor_path.o: /usr/include/sys/unistd.h
.o/level_cursor_path.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_cursor_path.o: /usr/include/sys/_types/_seek_set.h
.o/level_cursor_path.o: /usr/include/sys/_types/_uid_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_gid_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_pid_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_useconds_t.h
.o/level_cursor_path.o: /usr/include/sys/select.h
.o/level_cursor_path.o: /usr/include/sys/appleapiopts.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_def.h
.o/level_cursor_path.o: /usr/include/sys/_types/_timeval.h
.o/level_cursor_path.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_sigset_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_set.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_clr.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_isset.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_zero.h
.o/level_cursor_path.o: /usr/include/sys/_types/_fd_copy.h
.o/level_cursor_path.o: /usr/include/sys/_select.h
.o/level_cursor_path.o: /usr/include/sys/_types/_dev_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_mode_t.h
.o/level_cursor_path.o: /usr/include/sys/_types/_uuid_t.h
.o/level_cursor_path.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_cursor_path.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/level_cursor_path.o: my_dmap.h my_tile.h my_color.h my_tex.h my_gl.h
.o/level_cursor_path.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/level_cursor_path.o: my_size.h my_thing_ai.h
.o/level_display.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/level_display.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_display.o: /usr/include/sys/_types/_va_list.h
.o/level_display.o: /usr/include/sys/_types/_size_t.h
.o/level_display.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/level_display.o: /usr/include/sys/_types/_off_t.h
.o/level_display.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display.o: /usr/include/secure/_stdio.h
.o/level_display.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/level_display.o: my_bounds_check.h /usr/include/assert.h
.o/level_display.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/level_display.o: my_globals.h my_game.h my_sdl.h my_command.h my_token.h
.o/level_display.o: my_string.h /usr/include/wchar.h
.o/level_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_display.o: /usr/include/sys/_types/_clock_t.h
.o/level_display.o: /usr/include/sys/_types/_time_t.h
.o/level_display.o: /usr/include/sys/_types/_timespec.h
.o/level_display.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display.o: /usr/include/sys/_types/_wint_t.h
.o/level_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_display.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/level_display.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_display.o: /usr/include/sys/unistd.h
.o/level_display.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_display.o: /usr/include/sys/_types/_seek_set.h
.o/level_display.o: /usr/include/sys/_types/_uid_t.h
.o/level_display.o: /usr/include/sys/_types/_gid_t.h
.o/level_display.o: /usr/include/sys/_types/_pid_t.h
.o/level_display.o: /usr/include/sys/_types/_useconds_t.h
.o/level_display.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/level_display.o: /usr/include/sys/_types/_fd_def.h
.o/level_display.o: /usr/include/sys/_types/_timeval.h
.o/level_display.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_display.o: /usr/include/sys/_types/_sigset_t.h
.o/level_display.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_display.o: /usr/include/sys/_types/_fd_set.h
.o/level_display.o: /usr/include/sys/_types/_fd_clr.h
.o/level_display.o: /usr/include/sys/_types/_fd_isset.h
.o/level_display.o: /usr/include/sys/_types/_fd_zero.h
.o/level_display.o: /usr/include/sys/_types/_fd_copy.h
.o/level_display.o: /usr/include/sys/_select.h
.o/level_display.o: /usr/include/sys/_types/_dev_t.h
.o/level_display.o: /usr/include/sys/_types/_mode_t.h
.o/level_display.o: /usr/include/sys/_types/_uuid_t.h
.o/level_display.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_display.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/level_display.o: my_tile.h my_color.h my_tex.h my_gl.h my_thing.h
.o/level_display.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/level_display.o: my_thing_ai.h
.o/level_display_chasm.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_display_chasm.o: /usr/include/sys/cdefs.h
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
.o/level_display_chasm.o: my_callstack.h /usr/include/stdio.h
.o/level_display_chasm.o: /usr/include/_stdio.h
.o/level_display_chasm.o: /usr/include/sys/_types/_va_list.h
.o/level_display_chasm.o: /usr/include/sys/_types/_size_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_null.h
.o/level_display_chasm.o: /usr/include/sys/stdio.h
.o/level_display_chasm.o: /usr/include/sys/_types/_off_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_chasm.o: /usr/include/secure/_stdio.h
.o/level_display_chasm.o: /usr/include/secure/_common.h
.o/level_display_chasm.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_chasm.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_chasm.o: c_plus_plus_serializer.h my_globals.h my_game.h
.o/level_display_chasm.o: my_sdl.h my_command.h my_token.h my_string.h
.o/level_display_chasm.o: /usr/include/wchar.h
.o/level_display_chasm.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_chasm.o: /usr/include/time.h
.o/level_display_chasm.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_time_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_timespec.h
.o/level_display_chasm.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_chasm.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_chasm.o: /usr/include/_types/_wctype_t.h
.o/level_display_chasm.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_chasm.o: /usr/include/runetype.h my_slre.h my_point.h
.o/level_display_chasm.o: my_math.h /usr/include/math.h my_world.h my_level.h
.o/level_display_chasm.o: my_time.h /usr/include/unistd.h
.o/level_display_chasm.o: /usr/include/sys/unistd.h
.o/level_display_chasm.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_display_chasm.o: /usr/include/sys/_types/_seek_set.h
.o/level_display_chasm.o: /usr/include/sys/_types/_uid_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_gid_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_pid_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_useconds_t.h
.o/level_display_chasm.o: /usr/include/sys/select.h
.o/level_display_chasm.o: /usr/include/sys/appleapiopts.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_def.h
.o/level_display_chasm.o: /usr/include/sys/_types/_timeval.h
.o/level_display_chasm.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_sigset_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_set.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_clr.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_isset.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_zero.h
.o/level_display_chasm.o: /usr/include/sys/_types/_fd_copy.h
.o/level_display_chasm.o: /usr/include/sys/_select.h
.o/level_display_chasm.o: /usr/include/sys/_types/_dev_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_mode_t.h
.o/level_display_chasm.o: /usr/include/sys/_types/_uuid_t.h
.o/level_display_chasm.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_display_chasm.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/level_display_chasm.o: my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/level_display_chasm.o: my_dice.h my_tile.h my_color.h my_size.h
.o/level_display_chasm.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_display_deep_water.o: my_main.h my_pcg_basic.h
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
.o/level_display_deep_water.o: my_callstack.h /usr/include/stdio.h
.o/level_display_deep_water.o: /usr/include/_stdio.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_va_list.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_size_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_null.h
.o/level_display_deep_water.o: /usr/include/sys/stdio.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_off_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_deep_water.o: /usr/include/secure/_stdio.h
.o/level_display_deep_water.o: /usr/include/secure/_common.h
.o/level_display_deep_water.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_deep_water.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_deep_water.o: c_plus_plus_serializer.h my_globals.h
.o/level_display_deep_water.o: my_game.h my_sdl.h my_command.h my_token.h
.o/level_display_deep_water.o: my_string.h /usr/include/wchar.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_deep_water.o: /usr/include/time.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_time_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_timespec.h
.o/level_display_deep_water.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_deep_water.o: /usr/include/_types/_wctype_t.h
.o/level_display_deep_water.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_deep_water.o: /usr/include/runetype.h my_slre.h my_point.h
.o/level_display_deep_water.o: my_math.h /usr/include/math.h my_world.h
.o/level_display_deep_water.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_display_deep_water.o: /usr/include/sys/unistd.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_seek_set.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_uid_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_gid_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_pid_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_useconds_t.h
.o/level_display_deep_water.o: /usr/include/sys/select.h
.o/level_display_deep_water.o: /usr/include/sys/appleapiopts.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_def.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_timeval.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_sigset_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_set.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_clr.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_isset.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_zero.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_fd_copy.h
.o/level_display_deep_water.o: /usr/include/sys/_select.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_dev_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_mode_t.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_uuid_t.h
.o/level_display_deep_water.o: /usr/include/gethostuuid.h
.o/level_display_deep_water.o: /usr/include/sys/time.h
.o/level_display_deep_water.o: /usr/include/sys/_types/_timeval64.h
.o/level_display_deep_water.o: my_depth.h my_dmap.h my_thing.h my_light.h
.o/level_display_deep_water.o: my_thing_template.h my_dice.h my_tile.h
.o/level_display_deep_water.o: my_color.h my_size.h my_thing_ai.h my_font.h
.o/level_display_deep_water.o: my_tex.h my_gl.h
.o/level_display_lava.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_display_lava.o: /usr/include/sys/cdefs.h
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
.o/level_display_lava.o: my_callstack.h /usr/include/stdio.h
.o/level_display_lava.o: /usr/include/_stdio.h
.o/level_display_lava.o: /usr/include/sys/_types/_va_list.h
.o/level_display_lava.o: /usr/include/sys/_types/_size_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_null.h
.o/level_display_lava.o: /usr/include/sys/stdio.h
.o/level_display_lava.o: /usr/include/sys/_types/_off_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_lava.o: /usr/include/secure/_stdio.h
.o/level_display_lava.o: /usr/include/secure/_common.h
.o/level_display_lava.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_lava.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_lava.o: c_plus_plus_serializer.h my_globals.h my_game.h
.o/level_display_lava.o: my_sdl.h my_command.h my_token.h my_string.h
.o/level_display_lava.o: /usr/include/wchar.h
.o/level_display_lava.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_lava.o: /usr/include/time.h
.o/level_display_lava.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_time_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_timespec.h
.o/level_display_lava.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_lava.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_lava.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display_lava.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/level_display_lava.o: my_slre.h my_point.h my_math.h /usr/include/math.h
.o/level_display_lava.o: my_world.h my_level.h my_time.h
.o/level_display_lava.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/level_display_lava.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_display_lava.o: /usr/include/sys/_types/_seek_set.h
.o/level_display_lava.o: /usr/include/sys/_types/_uid_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_gid_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_pid_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_useconds_t.h
.o/level_display_lava.o: /usr/include/sys/select.h
.o/level_display_lava.o: /usr/include/sys/appleapiopts.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_def.h
.o/level_display_lava.o: /usr/include/sys/_types/_timeval.h
.o/level_display_lava.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_sigset_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_set.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_clr.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_isset.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_zero.h
.o/level_display_lava.o: /usr/include/sys/_types/_fd_copy.h
.o/level_display_lava.o: /usr/include/sys/_select.h
.o/level_display_lava.o: /usr/include/sys/_types/_dev_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_mode_t.h
.o/level_display_lava.o: /usr/include/sys/_types/_uuid_t.h
.o/level_display_lava.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_display_lava.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/level_display_lava.o: my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/level_display_lava.o: my_dice.h my_tile.h my_color.h my_size.h
.o/level_display_lava.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_display_wall.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_display_wall.o: /usr/include/sys/cdefs.h
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
.o/level_display_wall.o: my_callstack.h /usr/include/stdio.h
.o/level_display_wall.o: /usr/include/_stdio.h
.o/level_display_wall.o: /usr/include/sys/_types/_va_list.h
.o/level_display_wall.o: /usr/include/sys/_types/_size_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_null.h
.o/level_display_wall.o: /usr/include/sys/stdio.h
.o/level_display_wall.o: /usr/include/sys/_types/_off_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_wall.o: /usr/include/secure/_stdio.h
.o/level_display_wall.o: /usr/include/secure/_common.h
.o/level_display_wall.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_wall.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_wall.o: c_plus_plus_serializer.h my_globals.h my_game.h
.o/level_display_wall.o: my_sdl.h my_command.h my_token.h my_string.h
.o/level_display_wall.o: /usr/include/wchar.h
.o/level_display_wall.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_wall.o: /usr/include/time.h
.o/level_display_wall.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_time_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_timespec.h
.o/level_display_wall.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_wall.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_wall.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_display_wall.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/level_display_wall.o: my_slre.h my_point.h my_math.h /usr/include/math.h
.o/level_display_wall.o: my_world.h my_level.h my_time.h
.o/level_display_wall.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/level_display_wall.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_display_wall.o: /usr/include/sys/_types/_seek_set.h
.o/level_display_wall.o: /usr/include/sys/_types/_uid_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_gid_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_pid_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_useconds_t.h
.o/level_display_wall.o: /usr/include/sys/select.h
.o/level_display_wall.o: /usr/include/sys/appleapiopts.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_def.h
.o/level_display_wall.o: /usr/include/sys/_types/_timeval.h
.o/level_display_wall.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_sigset_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_set.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_clr.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_isset.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_zero.h
.o/level_display_wall.o: /usr/include/sys/_types/_fd_copy.h
.o/level_display_wall.o: /usr/include/sys/_select.h
.o/level_display_wall.o: /usr/include/sys/_types/_dev_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_mode_t.h
.o/level_display_wall.o: /usr/include/sys/_types/_uuid_t.h
.o/level_display_wall.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_display_wall.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/level_display_wall.o: my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/level_display_wall.o: my_dice.h my_tile.h my_color.h my_size.h
.o/level_display_wall.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_display_water.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_display_water.o: /usr/include/sys/cdefs.h
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
.o/level_display_water.o: my_callstack.h /usr/include/stdio.h
.o/level_display_water.o: /usr/include/_stdio.h
.o/level_display_water.o: /usr/include/sys/_types/_va_list.h
.o/level_display_water.o: /usr/include/sys/_types/_size_t.h
.o/level_display_water.o: /usr/include/sys/_types/_null.h
.o/level_display_water.o: /usr/include/sys/stdio.h
.o/level_display_water.o: /usr/include/sys/_types/_off_t.h
.o/level_display_water.o: /usr/include/sys/_types/_ssize_t.h
.o/level_display_water.o: /usr/include/secure/_stdio.h
.o/level_display_water.o: /usr/include/secure/_common.h
.o/level_display_water.o: my_array_bounds_check.h my_bounds_check.h
.o/level_display_water.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_display_water.o: c_plus_plus_serializer.h my_globals.h my_game.h
.o/level_display_water.o: my_sdl.h my_command.h my_token.h my_string.h
.o/level_display_water.o: /usr/include/wchar.h
.o/level_display_water.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_display_water.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_display_water.o: /usr/include/sys/_types/_rune_t.h
.o/level_display_water.o: /usr/include/time.h
.o/level_display_water.o: /usr/include/sys/_types/_clock_t.h
.o/level_display_water.o: /usr/include/sys/_types/_time_t.h
.o/level_display_water.o: /usr/include/sys/_types/_timespec.h
.o/level_display_water.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/level_display_water.o: /usr/include/sys/_types/_wint_t.h
.o/level_display_water.o: /usr/include/_types/_wctype_t.h
.o/level_display_water.o: /usr/include/ctype.h /usr/include/_ctype.h
.o/level_display_water.o: /usr/include/runetype.h my_slre.h my_point.h
.o/level_display_water.o: my_math.h /usr/include/math.h my_world.h my_level.h
.o/level_display_water.o: my_time.h /usr/include/unistd.h
.o/level_display_water.o: /usr/include/sys/unistd.h
.o/level_display_water.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_display_water.o: /usr/include/sys/_types/_seek_set.h
.o/level_display_water.o: /usr/include/sys/_types/_uid_t.h
.o/level_display_water.o: /usr/include/sys/_types/_gid_t.h
.o/level_display_water.o: /usr/include/sys/_types/_pid_t.h
.o/level_display_water.o: /usr/include/sys/_types/_useconds_t.h
.o/level_display_water.o: /usr/include/sys/select.h
.o/level_display_water.o: /usr/include/sys/appleapiopts.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_def.h
.o/level_display_water.o: /usr/include/sys/_types/_timeval.h
.o/level_display_water.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_display_water.o: /usr/include/sys/_types/_sigset_t.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_set.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_clr.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_isset.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_zero.h
.o/level_display_water.o: /usr/include/sys/_types/_fd_copy.h
.o/level_display_water.o: /usr/include/sys/_select.h
.o/level_display_water.o: /usr/include/sys/_types/_dev_t.h
.o/level_display_water.o: /usr/include/sys/_types/_mode_t.h
.o/level_display_water.o: /usr/include/sys/_types/_uuid_t.h
.o/level_display_water.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_display_water.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/level_display_water.o: my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/level_display_water.o: my_dice.h my_tile.h my_color.h my_size.h
.o/level_display_water.o: my_thing_ai.h my_font.h my_tex.h my_gl.h
.o/level_fini.o: my_level.h my_point.h my_math.h /usr/include/math.h
.o/level_fini.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_fini.o: /usr/include/sys/_posix_availability.h
.o/level_fini.o: /usr/include/Availability.h
.o/level_fini.o: /usr/include/AvailabilityInternal.h c_plus_plus_serializer.h
.o/level_fini.o: my_time.h /usr/include/assert.h /usr/include/unistd.h
.o/level_fini.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/level_fini.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/level_fini.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_fini.o: /usr/include/sys/unistd.h
.o/level_fini.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_fini.o: /usr/include/sys/_types/_seek_set.h
.o/level_fini.o: /usr/include/sys/_types/_size_t.h
.o/level_fini.o: /usr/include/_types/_uint64_t.h
.o/level_fini.o: /usr/include/_types/_uint32_t.h
.o/level_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/level_fini.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_fini.o: /usr/include/sys/_types/_int8_t.h
.o/level_fini.o: /usr/include/sys/_types/_int16_t.h
.o/level_fini.o: /usr/include/sys/_types/_int32_t.h
.o/level_fini.o: /usr/include/sys/_types/_int64_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_fini.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_fini.o: /usr/include/sys/_types/_intptr_t.h
.o/level_fini.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_fini.o: /usr/include/sys/_types/_uid_t.h
.o/level_fini.o: /usr/include/sys/_types/_gid_t.h
.o/level_fini.o: /usr/include/sys/_types/_off_t.h
.o/level_fini.o: /usr/include/sys/_types/_pid_t.h
.o/level_fini.o: /usr/include/sys/_types/_useconds_t.h
.o/level_fini.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/level_fini.o: /usr/include/sys/appleapiopts.h
.o/level_fini.o: /usr/include/sys/_types/_fd_def.h
.o/level_fini.o: /usr/include/sys/_types/_timespec.h
.o/level_fini.o: /usr/include/sys/_types/_timeval.h
.o/level_fini.o: /usr/include/sys/_types/_time_t.h
.o/level_fini.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_fini.o: /usr/include/sys/_types/_sigset_t.h
.o/level_fini.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_fini.o: /usr/include/sys/_types/_fd_set.h
.o/level_fini.o: /usr/include/sys/_types/_fd_clr.h
.o/level_fini.o: /usr/include/sys/_types/_fd_isset.h
.o/level_fini.o: /usr/include/sys/_types/_fd_zero.h
.o/level_fini.o: /usr/include/sys/_types/_fd_copy.h
.o/level_fini.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/level_fini.o: /usr/include/sys/_types/_mode_t.h
.o/level_fini.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/level_fini.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/level_fini.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/level_fini.o: my_sdl.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_fini.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_fini.o: /usr/include/_types/_uint8_t.h
.o/level_fini.o: /usr/include/_types/_uint16_t.h
.o/level_fini.o: /usr/include/_types/_intmax_t.h
.o/level_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_fini.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_fini.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/level_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_fini.o: my_array_bounds_check.h my_bounds_check.h
.o/level_fini.o: my_vector_bounds_check.h my_globals.h my_command.h
.o/level_fini.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_fini.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/level_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_fini.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_fini.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/level_fini.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/level_fini.o: my_dmap.h
.o/level_init.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_init.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_init.o: /usr/include/sys/_posix_availability.h
.o/level_init.o: /usr/include/Availability.h
.o/level_init.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/level_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_init.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_init.o: /usr/include/sys/_types/_va_list.h
.o/level_init.o: /usr/include/sys/_types/_size_t.h
.o/level_init.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/level_init.o: /usr/include/sys/_types/_off_t.h
.o/level_init.o: /usr/include/sys/_types/_ssize_t.h
.o/level_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_init.o: my_array_bounds_check.h my_bounds_check.h
.o/level_init.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_init.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/level_init.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_init.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_init.o: /usr/include/sys/_types/_clock_t.h
.o/level_init.o: /usr/include/sys/_types/_time_t.h
.o/level_init.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_init.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_init.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/level_init.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_init.o: /usr/include/sys/unistd.h
.o/level_init.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_init.o: /usr/include/sys/_types/_seek_set.h
.o/level_init.o: /usr/include/sys/_types/_uid_t.h
.o/level_init.o: /usr/include/sys/_types/_gid_t.h
.o/level_init.o: /usr/include/sys/_types/_pid_t.h
.o/level_init.o: /usr/include/sys/_types/_useconds_t.h
.o/level_init.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/level_init.o: /usr/include/sys/_types/_fd_def.h
.o/level_init.o: /usr/include/sys/_types/_timeval.h
.o/level_init.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_init.o: /usr/include/sys/_types/_sigset_t.h
.o/level_init.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_init.o: /usr/include/sys/_types/_fd_set.h
.o/level_init.o: /usr/include/sys/_types/_fd_clr.h
.o/level_init.o: /usr/include/sys/_types/_fd_isset.h
.o/level_init.o: /usr/include/sys/_types/_fd_zero.h
.o/level_init.o: /usr/include/sys/_types/_fd_copy.h
.o/level_init.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/level_init.o: /usr/include/sys/_types/_mode_t.h
.o/level_init.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/level_init.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/level_init.o: my_depth.h my_dmap.h my_dungeon.h my_room.h my_charmap.h
.o/level_init.o: my_level_static.h my_dungeon_grid.h my_thing.h my_light.h
.o/level_init.o: my_thing_template.h my_dice.h my_tile.h my_color.h my_size.h
.o/level_init.o: my_thing_ai.h
.o/level_log.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_log.o: /usr/include/sys/_posix_availability.h
.o/level_log.o: /usr/include/Availability.h
.o/level_log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/level_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/level_log.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_log.o: /usr/include/sys/_types/_va_list.h
.o/level_log.o: /usr/include/sys/_types/_size_t.h
.o/level_log.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/level_log.o: /usr/include/sys/_types/_off_t.h
.o/level_log.o: /usr/include/sys/_types/_ssize_t.h
.o/level_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_log.o: my_array_bounds_check.h my_bounds_check.h
.o/level_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_log.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/level_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_log.o: /usr/include/sys/_types/_clock_t.h
.o/level_log.o: /usr/include/sys/_types/_time_t.h
.o/level_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_log.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_log.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/level_log.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_log.o: /usr/include/sys/unistd.h
.o/level_log.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_log.o: /usr/include/sys/_types/_seek_set.h
.o/level_log.o: /usr/include/sys/_types/_uid_t.h
.o/level_log.o: /usr/include/sys/_types/_gid_t.h
.o/level_log.o: /usr/include/sys/_types/_pid_t.h
.o/level_log.o: /usr/include/sys/_types/_useconds_t.h
.o/level_log.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/level_log.o: /usr/include/sys/_types/_fd_def.h
.o/level_log.o: /usr/include/sys/_types/_timeval.h
.o/level_log.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_log.o: /usr/include/sys/_types/_sigset_t.h
.o/level_log.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_log.o: /usr/include/sys/_types/_fd_set.h
.o/level_log.o: /usr/include/sys/_types/_fd_clr.h
.o/level_log.o: /usr/include/sys/_types/_fd_isset.h
.o/level_log.o: /usr/include/sys/_types/_fd_zero.h
.o/level_log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/level_log.o: /usr/include/sys/_types/_dev_t.h
.o/level_log.o: /usr/include/sys/_types/_mode_t.h
.o/level_log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/level_log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/level_log.o: my_depth.h my_dmap.h my_traceback.h my_console.h
.o/level_log.o: my_wid_console.h my_wid.h my_size.h my_ascii.h my_color.h
.o/level_log.o: my_tex.h my_tile.h my_wid_tiles.h my_log.h
.o/level_map.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/level_map.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/level_map.o: /usr/include/sys/_posix_availability.h
.o/level_map.o: /usr/include/Availability.h
.o/level_map.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/level_map.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_map.o: /usr/include/i386/_types.h
.o/level_map.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_map.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_map.o: /usr/include/sys/_types/_int8_t.h
.o/level_map.o: /usr/include/sys/_types/_int16_t.h
.o/level_map.o: /usr/include/sys/_types/_int32_t.h
.o/level_map.o: /usr/include/sys/_types/_int64_t.h
.o/level_map.o: /usr/include/_types/_uint8_t.h
.o/level_map.o: /usr/include/_types/_uint16_t.h
.o/level_map.o: /usr/include/_types/_uint32_t.h
.o/level_map.o: /usr/include/_types/_uint64_t.h
.o/level_map.o: /usr/include/sys/_types/_intptr_t.h
.o/level_map.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_map.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_map.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_map.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_map.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_map.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_map.o: /usr/include/_types/_intmax_t.h
.o/level_map.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/level_map.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/level_map.o: /usr/include/sys/_types/_va_list.h
.o/level_map.o: /usr/include/sys/_types/_size_t.h
.o/level_map.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/level_map.o: /usr/include/sys/_types/_off_t.h
.o/level_map.o: /usr/include/sys/_types/_ssize_t.h
.o/level_map.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_map.o: my_array_bounds_check.h my_bounds_check.h
.o/level_map.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_map.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/level_map.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_map.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_map.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_map.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_map.o: /usr/include/sys/_types/_clock_t.h
.o/level_map.o: /usr/include/sys/_types/_time_t.h
.o/level_map.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_map.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_map.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_map.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_map.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/level_map.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_map.o: /usr/include/sys/unistd.h
.o/level_map.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_map.o: /usr/include/sys/_types/_seek_set.h
.o/level_map.o: /usr/include/sys/_types/_uid_t.h
.o/level_map.o: /usr/include/sys/_types/_gid_t.h
.o/level_map.o: /usr/include/sys/_types/_pid_t.h
.o/level_map.o: /usr/include/sys/_types/_useconds_t.h
.o/level_map.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/level_map.o: /usr/include/sys/_types/_fd_def.h
.o/level_map.o: /usr/include/sys/_types/_timeval.h
.o/level_map.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_map.o: /usr/include/sys/_types/_sigset_t.h
.o/level_map.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_map.o: /usr/include/sys/_types/_fd_set.h
.o/level_map.o: /usr/include/sys/_types/_fd_clr.h
.o/level_map.o: /usr/include/sys/_types/_fd_isset.h
.o/level_map.o: /usr/include/sys/_types/_fd_zero.h
.o/level_map.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/level_map.o: /usr/include/sys/_types/_dev_t.h
.o/level_map.o: /usr/include/sys/_types/_mode_t.h
.o/level_map.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/level_map.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/level_map.o: my_depth.h my_dmap.h my_thing.h my_light.h
.o/level_map.o: my_thing_template.h my_dice.h my_tile.h my_color.h my_size.h
.o/level_map.o: my_thing_ai.h
.o/level_scroll.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/level_scroll.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_scroll.o: /usr/include/sys/_types/_va_list.h
.o/level_scroll.o: /usr/include/sys/_types/_size_t.h
.o/level_scroll.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/level_scroll.o: /usr/include/sys/_types/_off_t.h
.o/level_scroll.o: /usr/include/sys/_types/_ssize_t.h
.o/level_scroll.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_scroll.o: my_array_bounds_check.h my_bounds_check.h
.o/level_scroll.o: /usr/include/assert.h my_vector_bounds_check.h
.o/level_scroll.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/level_scroll.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_scroll.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_scroll.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_scroll.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/level_scroll.o: /usr/include/sys/_types/_clock_t.h
.o/level_scroll.o: /usr/include/sys/_types/_time_t.h
.o/level_scroll.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/level_scroll.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_scroll.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_scroll.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_scroll.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/level_scroll.o: my_level.h my_time.h /usr/include/unistd.h
.o/level_scroll.o: /usr/include/sys/unistd.h
.o/level_scroll.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_scroll.o: /usr/include/sys/_types/_seek_set.h
.o/level_scroll.o: /usr/include/sys/_types/_uid_t.h
.o/level_scroll.o: /usr/include/sys/_types/_gid_t.h
.o/level_scroll.o: /usr/include/sys/_types/_pid_t.h
.o/level_scroll.o: /usr/include/sys/_types/_useconds_t.h
.o/level_scroll.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_def.h
.o/level_scroll.o: /usr/include/sys/_types/_timeval.h
.o/level_scroll.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_scroll.o: /usr/include/sys/_types/_sigset_t.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_set.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_clr.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_isset.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_zero.h
.o/level_scroll.o: /usr/include/sys/_types/_fd_copy.h
.o/level_scroll.o: /usr/include/sys/_select.h
.o/level_scroll.o: /usr/include/sys/_types/_dev_t.h
.o/level_scroll.o: /usr/include/sys/_types/_mode_t.h
.o/level_scroll.o: /usr/include/sys/_types/_uuid_t.h
.o/level_scroll.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_scroll.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/level_scroll.o: my_tile.h my_color.h my_tex.h my_gl.h my_thing.h
.o/level_scroll.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/level_scroll.o: my_thing_ai.h my_wid.h my_ascii.h my_wid_tiles.h
.o/level_static.o: my_level.h my_point.h my_math.h /usr/include/math.h
.o/level_static.o: /usr/include/sys/cdefs.h
.o/level_static.o: /usr/include/sys/_symbol_aliasing.h
.o/level_static.o: /usr/include/sys/_posix_availability.h
.o/level_static.o: /usr/include/Availability.h
.o/level_static.o: /usr/include/AvailabilityInternal.h
.o/level_static.o: c_plus_plus_serializer.h my_time.h /usr/include/assert.h
.o/level_static.o: /usr/include/unistd.h /usr/include/_types.h
.o/level_static.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_static.o: /usr/include/i386/_types.h
.o/level_static.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_static.o: /usr/include/sys/unistd.h
.o/level_static.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_static.o: /usr/include/sys/_types/_seek_set.h
.o/level_static.o: /usr/include/sys/_types/_size_t.h
.o/level_static.o: /usr/include/_types/_uint64_t.h
.o/level_static.o: /usr/include/_types/_uint32_t.h
.o/level_static.o: /usr/include/sys/_types/_ssize_t.h
.o/level_static.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_static.o: /usr/include/sys/_types/_int8_t.h
.o/level_static.o: /usr/include/sys/_types/_int16_t.h
.o/level_static.o: /usr/include/sys/_types/_int32_t.h
.o/level_static.o: /usr/include/sys/_types/_int64_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_static.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_static.o: /usr/include/sys/_types/_intptr_t.h
.o/level_static.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_static.o: /usr/include/sys/_types/_uid_t.h
.o/level_static.o: /usr/include/sys/_types/_gid_t.h
.o/level_static.o: /usr/include/sys/_types/_off_t.h
.o/level_static.o: /usr/include/sys/_types/_pid_t.h
.o/level_static.o: /usr/include/sys/_types/_useconds_t.h
.o/level_static.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/level_static.o: /usr/include/sys/appleapiopts.h
.o/level_static.o: /usr/include/sys/_types/_fd_def.h
.o/level_static.o: /usr/include/sys/_types/_timespec.h
.o/level_static.o: /usr/include/sys/_types/_timeval.h
.o/level_static.o: /usr/include/sys/_types/_time_t.h
.o/level_static.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_static.o: /usr/include/sys/_types/_sigset_t.h
.o/level_static.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_static.o: /usr/include/sys/_types/_fd_set.h
.o/level_static.o: /usr/include/sys/_types/_fd_clr.h
.o/level_static.o: /usr/include/sys/_types/_fd_isset.h
.o/level_static.o: /usr/include/sys/_types/_fd_zero.h
.o/level_static.o: /usr/include/sys/_types/_fd_copy.h
.o/level_static.o: /usr/include/sys/_select.h
.o/level_static.o: /usr/include/sys/_types/_dev_t.h
.o/level_static.o: /usr/include/sys/_types/_mode_t.h
.o/level_static.o: /usr/include/sys/_types/_uuid_t.h
.o/level_static.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_static.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/level_static.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_main.h
.o/level_static.o: my_pcg_basic.h /usr/include/inttypes.h
.o/level_static.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_static.o: /usr/include/_types/_uint8_t.h
.o/level_static.o: /usr/include/_types/_uint16_t.h
.o/level_static.o: /usr/include/_types/_intmax_t.h
.o/level_static.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_static.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_static.o: /usr/include/sys/_types/_va_list.h
.o/level_static.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/level_static.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/level_static.o: my_bounds_check.h my_vector_bounds_check.h my_globals.h
.o/level_static.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/level_static.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_static.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_static.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/level_static.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_static.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_static.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_static.o: my_depth.h my_level_static.h my_charmap.h
.o/level_thing.o: my_level.h my_point.h my_math.h /usr/include/math.h
.o/level_thing.o: /usr/include/sys/cdefs.h
.o/level_thing.o: /usr/include/sys/_symbol_aliasing.h
.o/level_thing.o: /usr/include/sys/_posix_availability.h
.o/level_thing.o: /usr/include/Availability.h
.o/level_thing.o: /usr/include/AvailabilityInternal.h
.o/level_thing.o: c_plus_plus_serializer.h my_time.h /usr/include/assert.h
.o/level_thing.o: /usr/include/unistd.h /usr/include/_types.h
.o/level_thing.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/level_thing.o: /usr/include/i386/_types.h
.o/level_thing.o: /usr/include/sys/_pthread/_pthread_types.h
.o/level_thing.o: /usr/include/sys/unistd.h
.o/level_thing.o: /usr/include/sys/_types/_posix_vdisable.h
.o/level_thing.o: /usr/include/sys/_types/_seek_set.h
.o/level_thing.o: /usr/include/sys/_types/_size_t.h
.o/level_thing.o: /usr/include/_types/_uint64_t.h
.o/level_thing.o: /usr/include/_types/_uint32_t.h
.o/level_thing.o: /usr/include/sys/_types/_ssize_t.h
.o/level_thing.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/level_thing.o: /usr/include/sys/_types/_int8_t.h
.o/level_thing.o: /usr/include/sys/_types/_int16_t.h
.o/level_thing.o: /usr/include/sys/_types/_int32_t.h
.o/level_thing.o: /usr/include/sys/_types/_int64_t.h
.o/level_thing.o: /usr/include/sys/_types/_u_int8_t.h
.o/level_thing.o: /usr/include/sys/_types/_u_int16_t.h
.o/level_thing.o: /usr/include/sys/_types/_u_int32_t.h
.o/level_thing.o: /usr/include/sys/_types/_u_int64_t.h
.o/level_thing.o: /usr/include/sys/_types/_intptr_t.h
.o/level_thing.o: /usr/include/sys/_types/_uintptr_t.h
.o/level_thing.o: /usr/include/sys/_types/_uid_t.h
.o/level_thing.o: /usr/include/sys/_types/_gid_t.h
.o/level_thing.o: /usr/include/sys/_types/_off_t.h
.o/level_thing.o: /usr/include/sys/_types/_pid_t.h
.o/level_thing.o: /usr/include/sys/_types/_useconds_t.h
.o/level_thing.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/level_thing.o: /usr/include/sys/appleapiopts.h
.o/level_thing.o: /usr/include/sys/_types/_fd_def.h
.o/level_thing.o: /usr/include/sys/_types/_timespec.h
.o/level_thing.o: /usr/include/sys/_types/_timeval.h
.o/level_thing.o: /usr/include/sys/_types/_time_t.h
.o/level_thing.o: /usr/include/sys/_types/_suseconds_t.h
.o/level_thing.o: /usr/include/sys/_types/_sigset_t.h
.o/level_thing.o: /usr/include/sys/_types/_fd_setsize.h
.o/level_thing.o: /usr/include/sys/_types/_fd_set.h
.o/level_thing.o: /usr/include/sys/_types/_fd_clr.h
.o/level_thing.o: /usr/include/sys/_types/_fd_isset.h
.o/level_thing.o: /usr/include/sys/_types/_fd_zero.h
.o/level_thing.o: /usr/include/sys/_types/_fd_copy.h
.o/level_thing.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/level_thing.o: /usr/include/sys/_types/_mode_t.h
.o/level_thing.o: /usr/include/sys/_types/_uuid_t.h
.o/level_thing.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/level_thing.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/level_thing.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_main.h
.o/level_thing.o: my_pcg_basic.h /usr/include/inttypes.h
.o/level_thing.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/level_thing.o: /usr/include/_types/_uint8_t.h
.o/level_thing.o: /usr/include/_types/_uint16_t.h
.o/level_thing.o: /usr/include/_types/_intmax_t.h
.o/level_thing.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/level_thing.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/level_thing.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/level_thing.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/level_thing.o: my_array_bounds_check.h my_bounds_check.h
.o/level_thing.o: my_vector_bounds_check.h my_globals.h my_command.h
.o/level_thing.o: my_token.h my_string.h /usr/include/wchar.h
.o/level_thing.o: /usr/include/sys/_types/_mbstate_t.h
.o/level_thing.o: /usr/include/sys/_types/_ct_rune_t.h
.o/level_thing.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/level_thing.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/level_thing.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/level_thing.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/level_thing.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/level_thing.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/level_thing.o: my_dmap.h
.o/light.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/light.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/light.o: /usr/include/sys/_posix_availability.h
.o/light.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
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
.o/light.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/light.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/light.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/light.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/light.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/light.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/light.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/light.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/light.o: my_token.h my_string.h /usr/include/wchar.h
.o/light.o: /usr/include/sys/_types/_mbstate_t.h
.o/light.o: /usr/include/sys/_types/_ct_rune_t.h
.o/light.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/light.o: /usr/include/sys/_types/_clock_t.h
.o/light.o: /usr/include/sys/_types/_time_t.h
.o/light.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/light.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/light.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/light.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/light.o: my_point.h my_math.h /usr/include/math.h my_world.h my_level.h
.o/light.o: my_time.h /usr/include/unistd.h /usr/include/sys/unistd.h
.o/light.o: /usr/include/sys/_types/_posix_vdisable.h
.o/light.o: /usr/include/sys/_types/_seek_set.h
.o/light.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/light.o: /usr/include/sys/_types/_pid_t.h
.o/light.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/light.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/light.o: /usr/include/sys/_types/_timeval.h
.o/light.o: /usr/include/sys/_types/_suseconds_t.h
.o/light.o: /usr/include/sys/_types/_sigset_t.h
.o/light.o: /usr/include/sys/_types/_fd_setsize.h
.o/light.o: /usr/include/sys/_types/_fd_set.h
.o/light.o: /usr/include/sys/_types/_fd_clr.h
.o/light.o: /usr/include/sys/_types/_fd_isset.h
.o/light.o: /usr/include/sys/_types/_fd_zero.h
.o/light.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/light.o: /usr/include/sys/_types/_dev_t.h
.o/light.o: /usr/include/sys/_types/_mode_t.h
.o/light.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/light.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/light.o: my_depth.h my_dmap.h my_gl.h my_color.h my_tex.h my_thing.h
.o/light.o: my_light.h my_thing_template.h my_dice.h my_tile.h my_size.h
.o/light.o: my_thing_ai.h
.o/light_log.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/light_log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/light_log.o: /usr/include/sys/_posix_availability.h
.o/light_log.o: /usr/include/Availability.h
.o/light_log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/light_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/light_log.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/light_log.o: /usr/include/sys/_types/_va_list.h
.o/light_log.o: /usr/include/sys/_types/_size_t.h
.o/light_log.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/light_log.o: /usr/include/sys/_types/_off_t.h
.o/light_log.o: /usr/include/sys/_types/_ssize_t.h
.o/light_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/light_log.o: my_array_bounds_check.h my_bounds_check.h
.o/light_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/light_log.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/light_log.o: my_token.h my_string.h /usr/include/wchar.h
.o/light_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/light_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/light_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/light_log.o: /usr/include/sys/_types/_clock_t.h
.o/light_log.o: /usr/include/sys/_types/_time_t.h
.o/light_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/light_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/light_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/light_log.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/light_log.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/light_log.o: my_level.h my_time.h /usr/include/unistd.h
.o/light_log.o: /usr/include/sys/unistd.h
.o/light_log.o: /usr/include/sys/_types/_posix_vdisable.h
.o/light_log.o: /usr/include/sys/_types/_seek_set.h
.o/light_log.o: /usr/include/sys/_types/_uid_t.h
.o/light_log.o: /usr/include/sys/_types/_gid_t.h
.o/light_log.o: /usr/include/sys/_types/_pid_t.h
.o/light_log.o: /usr/include/sys/_types/_useconds_t.h
.o/light_log.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/light_log.o: /usr/include/sys/_types/_fd_def.h
.o/light_log.o: /usr/include/sys/_types/_timeval.h
.o/light_log.o: /usr/include/sys/_types/_suseconds_t.h
.o/light_log.o: /usr/include/sys/_types/_sigset_t.h
.o/light_log.o: /usr/include/sys/_types/_fd_setsize.h
.o/light_log.o: /usr/include/sys/_types/_fd_set.h
.o/light_log.o: /usr/include/sys/_types/_fd_clr.h
.o/light_log.o: /usr/include/sys/_types/_fd_isset.h
.o/light_log.o: /usr/include/sys/_types/_fd_zero.h
.o/light_log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/light_log.o: /usr/include/sys/_types/_dev_t.h
.o/light_log.o: /usr/include/sys/_types/_mode_t.h
.o/light_log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/light_log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/light_log.o: my_depth.h my_dmap.h my_traceback.h my_console.h
.o/light_log.o: my_wid_console.h my_wid.h my_size.h my_ascii.h my_color.h
.o/light_log.o: my_tex.h my_tile.h my_wid_tiles.h my_log.h my_light.h
.o/light_log.o: my_thing_template.h my_dice.h
.o/log.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/log.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/log.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/log.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/log.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/log.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/log.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/log.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/log.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/log.o: my_token.h my_string.h /usr/include/wchar.h
.o/log.o: /usr/include/sys/_types/_mbstate_t.h
.o/log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/log.o: /usr/include/sys/_types/_clock_t.h
.o/log.o: /usr/include/sys/_types/_time_t.h
.o/log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/log.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/log.o: my_math.h /usr/include/math.h my_world.h my_level.h my_time.h
.o/log.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/log.o: /usr/include/sys/_types/_posix_vdisable.h
.o/log.o: /usr/include/sys/_types/_seek_set.h
.o/log.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/log.o: /usr/include/sys/_types/_pid_t.h
.o/log.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/log.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/log.o: /usr/include/sys/_types/_timeval.h
.o/log.o: /usr/include/sys/_types/_suseconds_t.h
.o/log.o: /usr/include/sys/_types/_sigset_t.h
.o/log.o: /usr/include/sys/_types/_fd_setsize.h
.o/log.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/log.o: /usr/include/sys/_types/_fd_isset.h
.o/log.o: /usr/include/sys/_types/_fd_zero.h
.o/log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/log.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/log.o: my_depth.h my_dmap.h my_traceback.h my_wid_console.h my_wid.h
.o/log.o: my_size.h my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/log.o: my_wid_minicon.h my_python.h my_console.h my_log.h
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
.o/log_util.o: /usr/include/_ctype.h /usr/include/runetype.h my_point.h
.o/log_util.o: my_math.h /usr/include/math.h c_plus_plus_serializer.h
.o/log_util.o: my_color.h my_tex.h my_tile.h my_main.h my_pcg_basic.h
.o/log_util.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/log_util.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/log_util.o: /usr/include/_types/_uint32_t.h
.o/log_util.o: /usr/include/_types/_uint64_t.h
.o/log_util.o: /usr/include/_types/_intmax_t.h
.o/log_util.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/log_util.o: my_array_bounds_check.h my_bounds_check.h
.o/log_util.o: /usr/include/assert.h my_vector_bounds_check.h my_globals.h
.o/log_util.o: my_sdl.h my_command.h my_token.h my_string.h my_slre.h
.o/main.o: /usr/include/libgen.h /usr/include/sys/cdefs.h
.o/main.o: /usr/include/sys/_symbol_aliasing.h
.o/main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/main.o: /usr/include/AvailabilityInternal.h my_game.h my_main.h
.o/main.o: my_pcg_basic.h /usr/include/inttypes.h /usr/include/_types.h
.o/main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/main.o: /usr/include/i386/_types.h
.o/main.o: /usr/include/sys/_pthread/_pthread_types.h
.o/main.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/main.o: /usr/include/sys/_types/_int8_t.h
.o/main.o: /usr/include/sys/_types/_int16_t.h
.o/main.o: /usr/include/sys/_types/_int32_t.h
.o/main.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/main.o: /usr/include/_types/_uint64_t.h
.o/main.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/main.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/main.o: /usr/include/sys/_types/_u_int16_t.h
.o/main.o: /usr/include/sys/_types/_u_int32_t.h
.o/main.o: /usr/include/sys/_types/_u_int64_t.h
.o/main.o: /usr/include/sys/_types/_uintptr_t.h
.o/main.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/main.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/main.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/main.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/main.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/main.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/main.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/main.o: my_token.h my_string.h /usr/include/wchar.h
.o/main.o: /usr/include/sys/_types/_mbstate_t.h
.o/main.o: /usr/include/sys/_types/_ct_rune_t.h
.o/main.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/main.o: /usr/include/sys/_types/_clock_t.h
.o/main.o: /usr/include/sys/_types/_time_t.h
.o/main.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/main.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/main.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/main.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/main.o: my_math.h /usr/include/math.h my_world.h my_level.h my_time.h
.o/main.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/main.o: /usr/include/sys/_types/_posix_vdisable.h
.o/main.o: /usr/include/sys/_types/_seek_set.h
.o/main.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/main.o: /usr/include/sys/_types/_pid_t.h
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
.o/main.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/main.o: my_depth.h my_dmap.h my_thing_template.h my_dice.h my_tile.h
.o/main.o: my_color.h my_size.h my_python.h my_gl.h my_wid_console.h my_wid.h
.o/main.o: my_ascii.h my_tex.h my_wid_tiles.h my_wid_minicon.h my_wid_test.h
.o/main.o: my_font.h my_dir.h my_file.h my_room.h my_charmap.h
.o/main.o: my_level_static.h my_gfx.h
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
.o/player.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/player.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/player.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/player.o: /usr/include/sys/_types/_size_t.h
.o/player.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/player.o: /usr/include/sys/_types/_off_t.h
.o/player.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/player.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/player.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/player.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/player.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/player.o: /usr/include/sys/_types/_mbstate_t.h
.o/player.o: /usr/include/sys/_types/_ct_rune_t.h
.o/player.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/player.o: /usr/include/sys/_types/_clock_t.h
.o/player.o: /usr/include/sys/_types/_time_t.h
.o/player.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/player.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/player.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/player.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/player.o: my_point.h my_math.h /usr/include/math.h my_world.h my_level.h
.o/player.o: my_time.h /usr/include/unistd.h /usr/include/sys/unistd.h
.o/player.o: /usr/include/sys/_types/_posix_vdisable.h
.o/player.o: /usr/include/sys/_types/_seek_set.h
.o/player.o: /usr/include/sys/_types/_uid_t.h
.o/player.o: /usr/include/sys/_types/_gid_t.h
.o/player.o: /usr/include/sys/_types/_pid_t.h
.o/player.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/player.o: /usr/include/sys/appleapiopts.h
.o/player.o: /usr/include/sys/_types/_fd_def.h
.o/player.o: /usr/include/sys/_types/_timeval.h
.o/player.o: /usr/include/sys/_types/_suseconds_t.h
.o/player.o: /usr/include/sys/_types/_sigset_t.h
.o/player.o: /usr/include/sys/_types/_fd_setsize.h
.o/player.o: /usr/include/sys/_types/_fd_set.h
.o/player.o: /usr/include/sys/_types/_fd_clr.h
.o/player.o: /usr/include/sys/_types/_fd_isset.h
.o/player.o: /usr/include/sys/_types/_fd_zero.h
.o/player.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/player.o: /usr/include/sys/_types/_dev_t.h
.o/player.o: /usr/include/sys/_types/_mode_t.h
.o/player.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/player.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/player.o: my_depth.h my_dmap.h my_wid_console.h my_wid.h my_size.h
.o/player.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/player.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/player.o: my_thing_ai.h
.o/ptrcheck.o: my_traceback.h my_sprintf.h /usr/include/string.h
.o/ptrcheck.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/ptrcheck.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ptrcheck.o: /usr/include/sys/_posix_availability.h
.o/ptrcheck.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ptrcheck.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ptrcheck.o: /usr/include/Availability.h
.o/ptrcheck.o: /usr/include/AvailabilityInternal.h
.o/ptrcheck.o: /usr/include/sys/_types/_size_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_null.h
.o/ptrcheck.o: /usr/include/sys/_types/_rsize_t.h
.o/ptrcheck.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ptrcheck.o: /usr/include/sys/_types/_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_intptr_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uintptr_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_errno_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/ptrcheck.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/ptrcheck.o: /usr/include/secure/_string.h my_time.h /usr/include/assert.h
.o/ptrcheck.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ptrcheck.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ptrcheck.o: /usr/include/sys/_types/_seek_set.h
.o/ptrcheck.o: /usr/include/_types/_uint64_t.h
.o/ptrcheck.o: /usr/include/_types/_uint32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_gid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_off_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_pid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_useconds_t.h
.o/ptrcheck.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_def.h
.o/ptrcheck.o: /usr/include/sys/_types/_timespec.h
.o/ptrcheck.o: /usr/include/sys/_types/_timeval.h
.o/ptrcheck.o: /usr/include/sys/_types/_time_t.h
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
.o/ptrcheck.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ptrcheck.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ptrcheck.o: my_sdl.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ptrcheck.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ptrcheck.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ptrcheck.o: /usr/include/_types/_intmax_t.h
.o/ptrcheck.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/ptrcheck.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/ptrcheck.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/ptrcheck.o: /usr/include/secure/_stdio.h my_array_bounds_check.h
.o/ptrcheck.o: my_bounds_check.h my_vector_bounds_check.h
.o/ptrcheck.o: c_plus_plus_serializer.h my_globals.h my_command.h my_token.h
.o/ptrcheck.o: my_string.h /usr/include/wchar.h
.o/ptrcheck.o: /usr/include/sys/_types/_mbstate_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/ptrcheck.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ptrcheck.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ptrcheck.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/py_level.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/py_level.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/py_level.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/py_level.o: /usr/include/sys/_types/_va_list.h
.o/py_level.o: /usr/include/sys/_types/_size_t.h
.o/py_level.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_level.o: /usr/include/sys/_types/_off_t.h
.o/py_level.o: /usr/include/sys/_types/_ssize_t.h
.o/py_level.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/py_level.o: my_array_bounds_check.h my_bounds_check.h
.o/py_level.o: /usr/include/assert.h my_vector_bounds_check.h
.o/py_level.o: c_plus_plus_serializer.h my_globals.h my_depth.h my_python.h
.o/py_level.o: my_point.h my_math.h /usr/include/math.h my_level_static.h
.o/py_level.o: my_charmap.h
.o/py_room.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_room.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_room.o: /usr/include/sys/_posix_availability.h
.o/py_room.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_room.o: c_plus_plus_serializer.h my_room.h my_main.h my_pcg_basic.h
.o/py_room.o: /usr/include/inttypes.h /usr/include/_types.h
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
.o/py_room.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/py_room.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/py_room.o: /usr/include/sys/_types/_va_list.h
.o/py_room.o: /usr/include/sys/_types/_size_t.h
.o/py_room.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_room.o: /usr/include/sys/_types/_off_t.h
.o/py_room.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_room.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/py_room.o: my_bounds_check.h /usr/include/assert.h
.o/py_room.o: my_vector_bounds_check.h my_globals.h my_depth.h my_charmap.h
.o/py_sdl.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/py_sdl.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/py_sdl.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_sdl.o: /usr/include/sys/_types/_size_t.h
.o/py_sdl.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_sdl.o: /usr/include/sys/_types/_off_t.h
.o/py_sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_sdl.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/py_sdl.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/py_sdl.o: c_plus_plus_serializer.h my_globals.h my_python.h my_point.h
.o/py_sdl.o: my_math.h /usr/include/math.h my_py_sdl.h
.o/py_tex.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tex.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tex.o: /usr/include/sys/_posix_availability.h
.o/py_tex.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tex.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_tex.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_tex.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tex.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_tex.o: /usr/include/sys/_types/_int8_t.h
.o/py_tex.o: /usr/include/sys/_types/_int16_t.h
.o/py_tex.o: /usr/include/sys/_types/_int32_t.h
.o/py_tex.o: /usr/include/sys/_types/_int64_t.h
.o/py_tex.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_tex.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_tex.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/py_tex.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tex.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tex.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/py_tex.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_tex.o: /usr/include/sys/_types/_size_t.h
.o/py_tex.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_tex.o: /usr/include/sys/_types/_off_t.h
.o/py_tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tex.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/py_tex.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/py_tex.o: c_plus_plus_serializer.h my_globals.h my_gl.h my_color.h
.o/py_tex.o: my_point.h my_math.h /usr/include/math.h my_python.h my_tex.h
.o/py_tile.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_tile.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tile.o: /usr/include/sys/_posix_availability.h
.o/py_tile.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tile.o: c_plus_plus_serializer.h my_tile.h my_main.h my_pcg_basic.h
.o/py_tile.o: /usr/include/inttypes.h /usr/include/_types.h
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
.o/py_tile.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/py_tile.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/py_tile.o: /usr/include/sys/_types/_va_list.h
.o/py_tile.o: /usr/include/sys/_types/_size_t.h
.o/py_tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_tile.o: /usr/include/sys/_types/_off_t.h
.o/py_tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tile.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/py_tile.o: my_bounds_check.h /usr/include/assert.h
.o/py_tile.o: my_vector_bounds_check.h my_globals.h my_sdl.h my_command.h
.o/py_tile.o: my_token.h my_string.h /usr/include/wchar.h
.o/py_tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/py_tile.o: /usr/include/sys/_types/_clock_t.h
.o/py_tile.o: /usr/include/sys/_types/_time_t.h
.o/py_tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tile.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/py_tile.o: my_color.h
.o/py_tp.o: my_python.h my_point.h my_math.h /usr/include/math.h
.o/py_tp.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tp.o: /usr/include/sys/_posix_availability.h
.o/py_tp.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tp.o: c_plus_plus_serializer.h my_thing_template.h my_dice.h my_tile.h
.o/py_tp.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tp.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_tp.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
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
.o/py_tp.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/py_tp.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/py_tp.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/py_tp.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_tp.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tp.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/py_tp.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/py_tp.o: my_globals.h my_sdl.h my_command.h my_token.h my_string.h
.o/py_tp.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_tp.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tp.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/py_tp.o: /usr/include/sys/_types/_clock_t.h
.o/py_tp.o: /usr/include/sys/_types/_time_t.h
.o/py_tp.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_tp.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tp.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tp.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/py_tp.o: my_color.h my_size.h
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
.o/py_ttf.o: /usr/include/_ctype.h /usr/include/runetype.h my_color.h
.o/py_ttf.o: my_tex.h my_tile.h my_main.h my_pcg_basic.h
.o/py_ttf.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/py_ttf.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_ttf.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_ttf.o: my_ptrcheck.h my_callstack.h my_array_bounds_check.h
.o/py_ttf.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/py_ttf.o: my_globals.h my_sdl.h my_command.h my_token.h my_string.h
.o/py_ttf.o: my_slre.h
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
.o/python.o: /usr/include/_ctype.h /usr/include/runetype.h my_color.h
.o/python.o: my_tex.h my_tile.h my_main.h my_pcg_basic.h
.o/python.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/python.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/python.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/python.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/python.o: my_ptrcheck.h my_callstack.h my_array_bounds_check.h
.o/python.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/python.o: my_globals.h my_sdl.h my_command.h my_token.h my_string.h
.o/python.o: my_slre.h
.o/room.o: my_room.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/room.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
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
.o/room.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/room.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/room.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/room.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/room.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/room.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/room.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/room.o: c_plus_plus_serializer.h my_globals.h my_point.h my_math.h
.o/room.o: /usr/include/math.h my_depth.h my_charmap.h my_range.h
.o/sdl.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/sdl.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/sdl.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/sdl.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/sdl.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/sdl.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/sdl.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/sdl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/sdl.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/sdl.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/sdl.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/sdl.o: my_token.h my_string.h /usr/include/wchar.h
.o/sdl.o: /usr/include/sys/_types/_mbstate_t.h
.o/sdl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/sdl.o: /usr/include/sys/_types/_clock_t.h
.o/sdl.o: /usr/include/sys/_types/_time_t.h
.o/sdl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/sdl.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/sdl.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/sdl.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/sdl.o: my_math.h /usr/include/math.h my_world.h my_level.h my_time.h
.o/sdl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/sdl.o: /usr/include/sys/_types/_posix_vdisable.h
.o/sdl.o: /usr/include/sys/_types/_seek_set.h
.o/sdl.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/sdl.o: /usr/include/sys/_types/_pid_t.h
.o/sdl.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/sdl.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/sdl.o: /usr/include/sys/_types/_timeval.h
.o/sdl.o: /usr/include/sys/_types/_suseconds_t.h
.o/sdl.o: /usr/include/sys/_types/_sigset_t.h
.o/sdl.o: /usr/include/sys/_types/_fd_setsize.h
.o/sdl.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/sdl.o: /usr/include/sys/_types/_fd_isset.h
.o/sdl.o: /usr/include/sys/_types/_fd_zero.h
.o/sdl.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/sdl.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/sdl.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/sdl.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/sdl.o: my_depth.h my_dmap.h my_gl.h my_color.h my_ascii.h my_tex.h
.o/sdl.o: my_tile.h my_thing.h my_light.h my_thing_template.h my_dice.h
.o/sdl.o: my_size.h my_thing_ai.h my_player.h my_wid_console.h my_wid.h
.o/sdl.o: my_wid_tiles.h stb_image_write.h /usr/include/stdlib.h
.o/sdl.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/sdl.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/sdl.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/sdl.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/sdl.o: /usr/include/mach/i386/_structs.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sdl.o: /usr/include/sys/_types/_sigaltstack.h
.o/sdl.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
.o/sdl.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/sdl.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/sdl.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/sdl_screenshot.o: my_game.h my_main.h my_pcg_basic.h
.o/sdl_screenshot.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/sdl_screenshot.o: /usr/include/sys/_symbol_aliasing.h
.o/sdl_screenshot.o: /usr/include/sys/_posix_availability.h
.o/sdl_screenshot.o: /usr/include/Availability.h
.o/sdl_screenshot.o: /usr/include/AvailabilityInternal.h
.o/sdl_screenshot.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/sdl_screenshot.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
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
.o/sdl_screenshot.o: my_callstack.h /usr/include/stdio.h
.o/sdl_screenshot.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_size_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_off_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_ssize_t.h
.o/sdl_screenshot.o: /usr/include/secure/_stdio.h
.o/sdl_screenshot.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/sdl_screenshot.o: my_bounds_check.h /usr/include/assert.h
.o/sdl_screenshot.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/sdl_screenshot.o: my_globals.h my_sdl.h my_command.h my_token.h
.o/sdl_screenshot.o: my_string.h /usr/include/wchar.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_mbstate_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_clock_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_time_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_timespec.h
.o/sdl_screenshot.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_wint_t.h
.o/sdl_screenshot.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/sdl_screenshot.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/sdl_screenshot.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/sdl_screenshot.o: my_level.h my_time.h /usr/include/unistd.h
.o/sdl_screenshot.o: /usr/include/sys/unistd.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_posix_vdisable.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_seek_set.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_uid_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_gid_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_pid_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_useconds_t.h
.o/sdl_screenshot.o: /usr/include/sys/select.h
.o/sdl_screenshot.o: /usr/include/sys/appleapiopts.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_def.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_timeval.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_suseconds_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_sigset_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_setsize.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_set.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_clr.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_isset.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_zero.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_fd_copy.h
.o/sdl_screenshot.o: /usr/include/sys/_select.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_dev_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_mode_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_uuid_t.h
.o/sdl_screenshot.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/sdl_screenshot.o: my_dmap.h my_gl.h my_color.h my_ascii.h my_tex.h
.o/sdl_screenshot.o: my_tile.h my_thing.h my_light.h my_thing_template.h
.o/sdl_screenshot.o: my_dice.h my_size.h my_thing_ai.h my_player.h
.o/sdl_screenshot.o: my_wid_console.h my_wid.h my_wid_tiles.h
.o/sdl_screenshot.o: stb_image_write.h /usr/include/stdlib.h
.o/sdl_screenshot.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/sdl_screenshot.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/sdl_screenshot.o: /usr/include/i386/signal.h
.o/sdl_screenshot.o: /usr/include/machine/_mcontext.h
.o/sdl_screenshot.o: /usr/include/i386/_mcontext.h
.o/sdl_screenshot.o: /usr/include/mach/machine/_structs.h
.o/sdl_screenshot.o: /usr/include/mach/i386/_structs.h
.o/sdl_screenshot.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_sigaltstack.h
.o/sdl_screenshot.o: /usr/include/sys/_types/_ucontext.h
.o/sdl_screenshot.o: /usr/include/sys/resource.h
.o/sdl_screenshot.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/sdl_screenshot.o: /usr/include/sys/_endian.h
.o/sdl_screenshot.o: /usr/include/libkern/_OSByteOrder.h
.o/sdl_screenshot.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/sdl_screenshot.o: /usr/include/alloca.h
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
.o/slre.o: my_slre.h
.o/sprintf.o: my_sprintf.h /usr/include/string.h /usr/include/_types.h
.o/sprintf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/sprintf.o: /usr/include/sys/_symbol_aliasing.h
.o/sprintf.o: /usr/include/sys/_posix_availability.h
.o/sprintf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/sprintf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sprintf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/sprintf.o: /usr/include/sys/_types/_size_t.h
.o/sprintf.o: /usr/include/sys/_types/_null.h
.o/sprintf.o: /usr/include/sys/_types/_rsize_t.h /usr/include/machine/types.h
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
.o/sprintf.o: /usr/include/sys/_types/_errno_t.h
.o/sprintf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/strings.h
.o/sprintf.o: /usr/include/secure/_strings.h /usr/include/secure/_common.h
.o/sprintf.o: /usr/include/secure/_string.h /usr/include/stdio.h
.o/sprintf.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/sprintf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sprintf.o: /usr/include/secure/_stdio.h /usr/include/stdlib.h
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
.o/string.o: /usr/include/sys/_types/_timespec.h my_main.h my_pcg_basic.h
.o/string.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/string.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/string.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/string.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/string.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/string.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/string.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/string.o: /usr/include/sys/_types/_off_t.h
.o/string.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/string.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/string.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/string.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/string.o: my_token.h my_string.h /usr/include/wchar.h
.o/string.o: /usr/include/sys/_types/_mbstate_t.h
.o/string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/string.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/string.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/string.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/string.o: my_thing_template.h my_dice.h my_tile.h my_point.h my_math.h
.o/string.o: /usr/include/math.h my_color.h my_size.h my_tex.h my_time.h
.o/string.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/string.o: /usr/include/sys/_types/_posix_vdisable.h
.o/string.o: /usr/include/sys/_types/_seek_set.h
.o/string.o: /usr/include/sys/_types/_uid_t.h
.o/string.o: /usr/include/sys/_types/_gid_t.h
.o/string.o: /usr/include/sys/_types/_pid_t.h
.o/string.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/string.o: /usr/include/sys/appleapiopts.h
.o/string.o: /usr/include/sys/_types/_fd_def.h
.o/string.o: /usr/include/sys/_types/_timeval.h
.o/string.o: /usr/include/sys/_types/_suseconds_t.h
.o/string.o: /usr/include/sys/_types/_sigset_t.h
.o/string.o: /usr/include/sys/_types/_fd_setsize.h
.o/string.o: /usr/include/sys/_types/_fd_set.h
.o/string.o: /usr/include/sys/_types/_fd_clr.h
.o/string.o: /usr/include/sys/_types/_fd_isset.h
.o/string.o: /usr/include/sys/_types/_fd_zero.h
.o/string.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/string.o: /usr/include/sys/_types/_dev_t.h
.o/string.o: /usr/include/sys/_types/_mode_t.h
.o/string.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/string.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
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
.o/tex.o: /usr/include/assert.h my_main.h my_pcg_basic.h
.o/tex.o: /usr/include/inttypes.h my_ptrcheck.h my_callstack.h
.o/tex.o: my_array_bounds_check.h my_bounds_check.h my_vector_bounds_check.h
.o/tex.o: c_plus_plus_serializer.h my_globals.h my_gl.h my_color.h my_point.h
.o/tex.o: my_math.h my_tex.h my_ramdisk.h my_pixel.h my_string.h
.o/tex.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/tex.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/tex.o: /usr/include/sys/_types/_time_t.h
.o/tex.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tex.o: /usr/include/__wctype.h /usr/include/_types/_wctype_t.h
.o/tex.o: /usr/include/ctype.h /usr/include/_ctype.h /usr/include/runetype.h
.o/thing.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing.o: /usr/include/sys/_posix_availability.h
.o/thing.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/thing.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing.o: /usr/include/sys/_types/_int8_t.h
.o/thing.o: /usr/include/sys/_types/_int16_t.h
.o/thing.o: /usr/include/sys/_types/_int32_t.h
.o/thing.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/thing.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/thing.o: /usr/include/_types/_uint64_t.h
.o/thing.o: /usr/include/sys/_types/_intptr_t.h /usr/include/machine/types.h
.o/thing.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/thing.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/thing.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/thing.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/thing.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/thing.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/thing.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing.o: my_math.h /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing.o: /usr/include/sys/unistd.h
.o/thing.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing.o: /usr/include/sys/_types/_seek_set.h
.o/thing.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/thing.o: /usr/include/sys/_types/_pid_t.h
.o/thing.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/thing.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/thing.o: /usr/include/sys/_types/_timespec.h
.o/thing.o: /usr/include/sys/_types/_timeval.h
.o/thing.o: /usr/include/sys/_types/_time_t.h
.o/thing.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing.o: /usr/include/sys/_types/_sigset_t.h
.o/thing.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing.o: /usr/include/sys/_types/_fd_set.h
.o/thing.o: /usr/include/sys/_types/_fd_clr.h
.o/thing.o: /usr/include/sys/_types/_fd_isset.h
.o/thing.o: /usr/include/sys/_types/_fd_zero.h
.o/thing.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing.o: /usr/include/sys/_types/_dev_t.h
.o/thing.o: /usr/include/sys/_types/_mode_t.h
.o/thing.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/thing.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing.o: my_depth.h my_color.h my_dmap.h my_sprintf.h
.o/thing.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing.o: my_thing.h my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing.o: my_size.h my_thing_ai.h
.o/thing_ai.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_ai.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/thing_ai.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_ai.o: /usr/include/sys/_types/_va_list.h
.o/thing_ai.o: /usr/include/sys/_types/_size_t.h
.o/thing_ai.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_ai.o: /usr/include/sys/_types/_off_t.h
.o/thing_ai.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_ai.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_ai.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_ai.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_ai.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing_ai.o: my_math.h /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing_ai.o: /usr/include/sys/unistd.h
.o/thing_ai.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_ai.o: /usr/include/sys/_types/_seek_set.h
.o/thing_ai.o: /usr/include/sys/_types/_uid_t.h
.o/thing_ai.o: /usr/include/sys/_types/_gid_t.h
.o/thing_ai.o: /usr/include/sys/_types/_pid_t.h
.o/thing_ai.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_ai.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_def.h
.o/thing_ai.o: /usr/include/sys/_types/_timespec.h
.o/thing_ai.o: /usr/include/sys/_types/_timeval.h
.o/thing_ai.o: /usr/include/sys/_types/_time_t.h
.o/thing_ai.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_ai.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_set.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_ai.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_ai.o: /usr/include/sys/_types/_dev_t.h
.o/thing_ai.o: /usr/include/sys/_types/_mode_t.h
.o/thing_ai.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_ai.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_ai.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_ai.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_ai.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_ai.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_ai.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_ai.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_ai.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_ai.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_ai.o: my_depth.h my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/thing_ai.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/thing_anim.o: my_thing.h my_time.h /usr/include/assert.h
.o/thing_anim.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_anim.o: /usr/include/sys/_posix_availability.h /usr/include/unistd.h
.o/thing_anim.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_anim.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_anim.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_anim.o: /usr/include/sys/unistd.h
.o/thing_anim.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_anim.o: /usr/include/sys/_types/_seek_set.h
.o/thing_anim.o: /usr/include/sys/_types/_size_t.h
.o/thing_anim.o: /usr/include/_types/_uint64_t.h
.o/thing_anim.o: /usr/include/_types/_uint32_t.h /usr/include/Availability.h
.o/thing_anim.o: /usr/include/AvailabilityInternal.h
.o/thing_anim.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_anim.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_anim.o: /usr/include/sys/_types/_int8_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int16_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int32_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int64_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_anim.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_anim.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_anim.o: /usr/include/sys/_types/_uid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_gid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_off_t.h
.o/thing_anim.o: /usr/include/sys/_types/_pid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_anim.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/thing_anim.o: /usr/include/sys/appleapiopts.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_def.h
.o/thing_anim.o: /usr/include/sys/_types/_timespec.h
.o/thing_anim.o: /usr/include/sys/_types/_timeval.h
.o/thing_anim.o: /usr/include/sys/_types/_time_t.h
.o/thing_anim.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_anim.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_set.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_anim.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_anim.o: /usr/include/sys/_types/_mode_t.h
.o/thing_anim.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_anim.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_anim.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_anim.o: my_sdl.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_anim.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_anim.o: /usr/include/_types/_uint8_t.h
.o/thing_anim.o: /usr/include/_types/_uint16_t.h
.o/thing_anim.o: /usr/include/_types/_intmax_t.h
.o/thing_anim.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_anim.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_anim.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/thing_anim.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_anim.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_anim.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_anim.o: my_globals.h my_command.h my_token.h my_string.h
.o/thing_anim.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_anim.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_anim.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_anim.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_anim.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_anim.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_anim.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_anim.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_anim.o: my_size.h my_thing_ai.h my_dmap.h
.o/thing_api.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_api.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/thing_api.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_api.o: /usr/include/sys/_types/_va_list.h
.o/thing_api.o: /usr/include/sys/_types/_size_t.h
.o/thing_api.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_api.o: /usr/include/sys/_types/_off_t.h
.o/thing_api.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_api.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_api.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_api.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_api.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing_api.o: my_math.h /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing_api.o: /usr/include/sys/unistd.h
.o/thing_api.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_api.o: /usr/include/sys/_types/_seek_set.h
.o/thing_api.o: /usr/include/sys/_types/_uid_t.h
.o/thing_api.o: /usr/include/sys/_types/_gid_t.h
.o/thing_api.o: /usr/include/sys/_types/_pid_t.h
.o/thing_api.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_api.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_api.o: /usr/include/sys/_types/_fd_def.h
.o/thing_api.o: /usr/include/sys/_types/_timespec.h
.o/thing_api.o: /usr/include/sys/_types/_timeval.h
.o/thing_api.o: /usr/include/sys/_types/_time_t.h
.o/thing_api.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_api.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_api.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_api.o: /usr/include/sys/_types/_fd_set.h
.o/thing_api.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_api.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_api.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_api.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_api.o: /usr/include/sys/_types/_dev_t.h
.o/thing_api.o: /usr/include/sys/_types/_mode_t.h
.o/thing_api.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_api.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_api.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_api.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_api.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_api.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_api.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_api.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_api.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_api.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_api.o: my_depth.h my_color.h my_dmap.h my_game_status.h my_wid.h
.o/thing_api.o: my_size.h my_ascii.h my_tex.h my_tile.h my_wid_tiles.h
.o/thing_api.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_api.o: my_thing_ai.h
.o/thing_astar.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_astar.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_astar.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_astar.o: /usr/include/sys/_types/_va_list.h
.o/thing_astar.o: /usr/include/sys/_types/_size_t.h
.o/thing_astar.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_astar.o: /usr/include/sys/_types/_off_t.h
.o/thing_astar.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_astar.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_astar.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_astar.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_astar.o: c_plus_plus_serializer.h my_globals.h my_dmap.h my_point.h
.o/thing_astar.o: my_math.h /usr/include/math.h my_sprintf.h
.o/thing_astar.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_astar.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_astar.o: /usr/include/secure/_strings.h
.o/thing_astar.o: /usr/include/secure/_string.h my_thing.h my_time.h
.o/thing_astar.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_astar.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_astar.o: /usr/include/sys/_types/_seek_set.h
.o/thing_astar.o: /usr/include/sys/_types/_uid_t.h
.o/thing_astar.o: /usr/include/sys/_types/_gid_t.h
.o/thing_astar.o: /usr/include/sys/_types/_pid_t.h
.o/thing_astar.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_astar.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_def.h
.o/thing_astar.o: /usr/include/sys/_types/_timespec.h
.o/thing_astar.o: /usr/include/sys/_types/_timeval.h
.o/thing_astar.o: /usr/include/sys/_types/_time_t.h
.o/thing_astar.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_astar.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_set.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_astar.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_astar.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_astar.o: /usr/include/sys/_types/_mode_t.h
.o/thing_astar.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_astar.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_astar.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_astar.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_astar.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_astar.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_astar.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_astar.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_astar.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_astar.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_astar.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_astar.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_astar.o: my_color.h my_size.h my_thing_ai.h
.o/thing_attach.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_attach.o: /usr/include/sys/cdefs.h
.o/thing_attach.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_attach.o: /usr/include/sys/_posix_availability.h
.o/thing_attach.o: /usr/include/Availability.h
.o/thing_attach.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_attach.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_attach.o: /usr/include/i386/_types.h
.o/thing_attach.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_attach.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_attach.o: /usr/include/sys/_types/_int8_t.h
.o/thing_attach.o: /usr/include/sys/_types/_int16_t.h
.o/thing_attach.o: /usr/include/sys/_types/_int32_t.h
.o/thing_attach.o: /usr/include/sys/_types/_int64_t.h
.o/thing_attach.o: /usr/include/_types/_uint8_t.h
.o/thing_attach.o: /usr/include/_types/_uint16_t.h
.o/thing_attach.o: /usr/include/_types/_uint32_t.h
.o/thing_attach.o: /usr/include/_types/_uint64_t.h
.o/thing_attach.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_attach.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_attach.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_attach.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_attach.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_attach.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_attach.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_attach.o: /usr/include/_types/_intmax_t.h
.o/thing_attach.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_attach.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_attach.o: /usr/include/sys/_types/_va_list.h
.o/thing_attach.o: /usr/include/sys/_types/_size_t.h
.o/thing_attach.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_attach.o: /usr/include/sys/_types/_off_t.h
.o/thing_attach.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_attach.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_attach.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_attach.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_attach.o: c_plus_plus_serializer.h my_globals.h my_level.h
.o/thing_attach.o: my_point.h my_math.h /usr/include/math.h my_time.h
.o/thing_attach.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_attach.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_attach.o: /usr/include/sys/_types/_seek_set.h
.o/thing_attach.o: /usr/include/sys/_types/_uid_t.h
.o/thing_attach.o: /usr/include/sys/_types/_gid_t.h
.o/thing_attach.o: /usr/include/sys/_types/_pid_t.h
.o/thing_attach.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_attach.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_def.h
.o/thing_attach.o: /usr/include/sys/_types/_timespec.h
.o/thing_attach.o: /usr/include/sys/_types/_timeval.h
.o/thing_attach.o: /usr/include/sys/_types/_time_t.h
.o/thing_attach.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_attach.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_set.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_attach.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_attach.o: /usr/include/sys/_select.h
.o/thing_attach.o: /usr/include/sys/_types/_dev_t.h
.o/thing_attach.o: /usr/include/sys/_types/_mode_t.h
.o/thing_attach.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_attach.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_attach.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_attach.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_attach.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_attach.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_attach.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_attach.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_attach.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_attach.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_attach.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_attach.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/thing_attach.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/thing_attach.o: my_dmap.h
.o/thing_bounce.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_bounce.o: /usr/include/sys/cdefs.h
.o/thing_bounce.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_bounce.o: /usr/include/sys/_posix_availability.h
.o/thing_bounce.o: /usr/include/Availability.h
.o/thing_bounce.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_bounce.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_bounce.o: /usr/include/i386/_types.h
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
.o/thing_bounce.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_bounce.o: /usr/include/sys/_types/_va_list.h
.o/thing_bounce.o: /usr/include/sys/_types/_size_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_bounce.o: /usr/include/sys/_types/_off_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_bounce.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_bounce.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_bounce.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_bounce.o: c_plus_plus_serializer.h my_globals.h my_sdl.h
.o/thing_bounce.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_bounce.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_bounce.o: /usr/include/sys/_types/_clock_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_time_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_bounce.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_bounce.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_bounce.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_bounce.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_bounce.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_bounce.o: /usr/include/sys/unistd.h
.o/thing_bounce.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_bounce.o: /usr/include/sys/_types/_seek_set.h
.o/thing_bounce.o: /usr/include/sys/_types/_uid_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_gid_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_pid_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_bounce.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_def.h
.o/thing_bounce.o: /usr/include/sys/_types/_timeval.h
.o/thing_bounce.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_set.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_bounce.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_bounce.o: /usr/include/sys/_select.h
.o/thing_bounce.o: /usr/include/sys/_types/_dev_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_mode_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_bounce.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_bounce.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_bounce.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_bounce.o: my_tile.h my_color.h my_size.h my_thing_ai.h my_sprintf.h
.o/thing_bounce.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_bounce.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_bounce.o: /usr/include/secure/_strings.h
.o/thing_bounce.o: /usr/include/secure/_string.h my_gl.h
.o/thing_carry.o: my_thing.h my_time.h /usr/include/assert.h
.o/thing_carry.o: /usr/include/sys/cdefs.h
.o/thing_carry.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_carry.o: /usr/include/sys/_posix_availability.h
.o/thing_carry.o: /usr/include/unistd.h /usr/include/_types.h
.o/thing_carry.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_carry.o: /usr/include/i386/_types.h
.o/thing_carry.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_carry.o: /usr/include/sys/unistd.h
.o/thing_carry.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_carry.o: /usr/include/sys/_types/_seek_set.h
.o/thing_carry.o: /usr/include/sys/_types/_size_t.h
.o/thing_carry.o: /usr/include/_types/_uint64_t.h
.o/thing_carry.o: /usr/include/_types/_uint32_t.h /usr/include/Availability.h
.o/thing_carry.o: /usr/include/AvailabilityInternal.h
.o/thing_carry.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_carry.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_carry.o: /usr/include/sys/_types/_int8_t.h
.o/thing_carry.o: /usr/include/sys/_types/_int16_t.h
.o/thing_carry.o: /usr/include/sys/_types/_int32_t.h
.o/thing_carry.o: /usr/include/sys/_types/_int64_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_carry.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_carry.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_carry.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_carry.o: /usr/include/sys/_types/_uid_t.h
.o/thing_carry.o: /usr/include/sys/_types/_gid_t.h
.o/thing_carry.o: /usr/include/sys/_types/_off_t.h
.o/thing_carry.o: /usr/include/sys/_types/_pid_t.h
.o/thing_carry.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_carry.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/thing_carry.o: /usr/include/sys/appleapiopts.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_def.h
.o/thing_carry.o: /usr/include/sys/_types/_timespec.h
.o/thing_carry.o: /usr/include/sys/_types/_timeval.h
.o/thing_carry.o: /usr/include/sys/_types/_time_t.h
.o/thing_carry.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_carry.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_set.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_carry.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_carry.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_carry.o: /usr/include/sys/_types/_mode_t.h
.o/thing_carry.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_carry.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_carry.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_carry.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_main.h
.o/thing_carry.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_carry.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_carry.o: /usr/include/_types/_uint8_t.h
.o/thing_carry.o: /usr/include/_types/_uint16_t.h
.o/thing_carry.o: /usr/include/_types/_intmax_t.h
.o/thing_carry.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_carry.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_carry.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/thing_carry.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_carry.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_carry.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_carry.o: my_globals.h my_command.h my_token.h my_string.h
.o/thing_carry.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_carry.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_carry.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_carry.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_carry.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_carry.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_carry.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_carry.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_carry.o: my_size.h my_thing_ai.h my_dmap.h
.o/thing_collision.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_collision.o: /usr/include/sys/cdefs.h
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
.o/thing_collision.o: my_callstack.h /usr/include/stdio.h
.o/thing_collision.o: /usr/include/_stdio.h
.o/thing_collision.o: /usr/include/sys/_types/_va_list.h
.o/thing_collision.o: /usr/include/sys/_types/_size_t.h
.o/thing_collision.o: /usr/include/sys/_types/_null.h
.o/thing_collision.o: /usr/include/sys/stdio.h
.o/thing_collision.o: /usr/include/sys/_types/_off_t.h
.o/thing_collision.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_collision.o: /usr/include/secure/_stdio.h
.o/thing_collision.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_collision.o: my_bounds_check.h /usr/include/assert.h
.o/thing_collision.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_collision.o: my_globals.h my_tile.h my_sdl.h my_command.h my_token.h
.o/thing_collision.o: my_string.h /usr/include/wchar.h
.o/thing_collision.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_collision.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_collision.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_collision.o: /usr/include/sys/_types/_clock_t.h
.o/thing_collision.o: /usr/include/sys/_types/_time_t.h
.o/thing_collision.o: /usr/include/sys/_types/_timespec.h
.o/thing_collision.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_collision.o: /usr/include/sys/_types/_wint_t.h
.o/thing_collision.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_collision.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_collision.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_collision.o: my_game.h my_world.h my_level.h my_time.h
.o/thing_collision.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_collision.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_collision.o: /usr/include/sys/_types/_seek_set.h
.o/thing_collision.o: /usr/include/sys/_types/_uid_t.h
.o/thing_collision.o: /usr/include/sys/_types/_gid_t.h
.o/thing_collision.o: /usr/include/sys/_types/_pid_t.h
.o/thing_collision.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_collision.o: /usr/include/sys/select.h
.o/thing_collision.o: /usr/include/sys/appleapiopts.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_def.h
.o/thing_collision.o: /usr/include/sys/_types/_timeval.h
.o/thing_collision.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_collision.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_set.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_collision.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_collision.o: /usr/include/sys/_select.h
.o/thing_collision.o: /usr/include/sys/_types/_dev_t.h
.o/thing_collision.o: /usr/include/sys/_types/_mode_t.h
.o/thing_collision.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_collision.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_collision.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/thing_collision.o: my_dmap.h my_thing.h my_light.h my_thing_template.h
.o/thing_collision.o: my_dice.h my_size.h my_thing_ai.h
.o/thing_cursor.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_cursor.o: /usr/include/sys/cdefs.h
.o/thing_cursor.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_cursor.o: /usr/include/sys/_posix_availability.h
.o/thing_cursor.o: /usr/include/Availability.h
.o/thing_cursor.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_cursor.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_cursor.o: /usr/include/i386/_types.h
.o/thing_cursor.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_cursor.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_cursor.o: /usr/include/sys/_types/_int8_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_int16_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_int32_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_int64_t.h
.o/thing_cursor.o: /usr/include/_types/_uint8_t.h
.o/thing_cursor.o: /usr/include/_types/_uint16_t.h
.o/thing_cursor.o: /usr/include/_types/_uint32_t.h
.o/thing_cursor.o: /usr/include/_types/_uint64_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_cursor.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_cursor.o: /usr/include/_types/_intmax_t.h
.o/thing_cursor.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_cursor.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_cursor.o: /usr/include/sys/_types/_va_list.h
.o/thing_cursor.o: /usr/include/sys/_types/_size_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_cursor.o: /usr/include/sys/_types/_off_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_cursor.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_cursor.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_cursor.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_cursor.o: c_plus_plus_serializer.h my_globals.h my_sdl.h
.o/thing_cursor.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_cursor.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_cursor.o: /usr/include/sys/_types/_clock_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_time_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_cursor.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_cursor.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_cursor.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_cursor.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_cursor.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_cursor.o: /usr/include/sys/unistd.h
.o/thing_cursor.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_cursor.o: /usr/include/sys/_types/_seek_set.h
.o/thing_cursor.o: /usr/include/sys/_types/_uid_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_gid_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_pid_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_cursor.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_def.h
.o/thing_cursor.o: /usr/include/sys/_types/_timeval.h
.o/thing_cursor.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_set.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_cursor.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_cursor.o: /usr/include/sys/_select.h
.o/thing_cursor.o: /usr/include/sys/_types/_dev_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_mode_t.h
.o/thing_cursor.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_cursor.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_cursor.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_cursor.o: my_wid_console.h my_wid.h my_size.h my_ascii.h my_color.h
.o/thing_cursor.o: my_tex.h my_tile.h my_wid_tiles.h my_thing.h my_light.h
.o/thing_cursor.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_cursor_path.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_cursor_path.o: /usr/include/sys/cdefs.h
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
.o/thing_cursor_path.o: my_callstack.h /usr/include/stdio.h
.o/thing_cursor_path.o: /usr/include/_stdio.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_va_list.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_size_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_null.h
.o/thing_cursor_path.o: /usr/include/sys/stdio.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_off_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_cursor_path.o: /usr/include/secure/_stdio.h
.o/thing_cursor_path.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_cursor_path.o: my_bounds_check.h /usr/include/assert.h
.o/thing_cursor_path.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_cursor_path.o: my_globals.h my_game.h my_sdl.h my_command.h
.o/thing_cursor_path.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_clock_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_time_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_timespec.h
.o/thing_cursor_path.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_wint_t.h
.o/thing_cursor_path.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_cursor_path.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/thing_cursor_path.o: my_slre.h my_point.h my_math.h /usr/include/math.h
.o/thing_cursor_path.o: my_world.h my_level.h my_time.h /usr/include/unistd.h
.o/thing_cursor_path.o: /usr/include/sys/unistd.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_seek_set.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_uid_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_gid_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_pid_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_cursor_path.o: /usr/include/sys/select.h
.o/thing_cursor_path.o: /usr/include/sys/appleapiopts.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_def.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_timeval.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_set.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_cursor_path.o: /usr/include/sys/_select.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_dev_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_mode_t.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_cursor_path.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_cursor_path.o: /usr/include/sys/_types/_timeval64.h my_depth.h
.o/thing_cursor_path.o: my_dmap.h my_wid_console.h my_wid.h my_size.h
.o/thing_cursor_path.o: my_ascii.h my_color.h my_tex.h my_tile.h
.o/thing_cursor_path.o: my_wid_tiles.h my_thing.h my_light.h
.o/thing_cursor_path.o: my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_dead.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_dead.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_dead.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_dead.o: /usr/include/sys/_types/_va_list.h
.o/thing_dead.o: /usr/include/sys/_types/_size_t.h
.o/thing_dead.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_dead.o: /usr/include/sys/_types/_off_t.h
.o/thing_dead.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_dead.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_dead.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_dead.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_dead.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/thing_dead.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_dead.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_dead.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_dead.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_dead.o: /usr/include/sys/_types/_clock_t.h
.o/thing_dead.o: /usr/include/sys/_types/_time_t.h
.o/thing_dead.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_dead.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_dead.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_dead.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_dead.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_dead.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_dead.o: /usr/include/sys/unistd.h
.o/thing_dead.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_dead.o: /usr/include/sys/_types/_seek_set.h
.o/thing_dead.o: /usr/include/sys/_types/_uid_t.h
.o/thing_dead.o: /usr/include/sys/_types/_gid_t.h
.o/thing_dead.o: /usr/include/sys/_types/_pid_t.h
.o/thing_dead.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_dead.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_def.h
.o/thing_dead.o: /usr/include/sys/_types/_timeval.h
.o/thing_dead.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_dead.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_set.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_dead.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_dead.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_dead.o: /usr/include/sys/_types/_mode_t.h
.o/thing_dead.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_dead.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_dead.o: my_depth.h my_dmap.h my_color.h my_sprintf.h
.o/thing_dead.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_dead.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_dead.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing_dead.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_dead.o: my_tile.h my_size.h my_thing_ai.h
.o/thing_display.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_display.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_display.o: /usr/include/sys/_types/_va_list.h
.o/thing_display.o: /usr/include/sys/_types/_size_t.h
.o/thing_display.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_display.o: /usr/include/sys/_types/_off_t.h
.o/thing_display.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_display.o: /usr/include/secure/_stdio.h
.o/thing_display.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_display.o: my_bounds_check.h /usr/include/assert.h
.o/thing_display.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_display.o: my_globals.h my_game.h my_sdl.h my_command.h my_token.h
.o/thing_display.o: my_string.h /usr/include/wchar.h
.o/thing_display.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_display.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_display.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_display.o: /usr/include/sys/_types/_clock_t.h
.o/thing_display.o: /usr/include/sys/_types/_time_t.h
.o/thing_display.o: /usr/include/sys/_types/_timespec.h
.o/thing_display.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_display.o: /usr/include/sys/_types/_wint_t.h
.o/thing_display.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_display.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_display.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_display.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_display.o: /usr/include/sys/unistd.h
.o/thing_display.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_display.o: /usr/include/sys/_types/_seek_set.h
.o/thing_display.o: /usr/include/sys/_types/_uid_t.h
.o/thing_display.o: /usr/include/sys/_types/_gid_t.h
.o/thing_display.o: /usr/include/sys/_types/_pid_t.h
.o/thing_display.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_display.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_display.o: /usr/include/sys/_types/_fd_def.h
.o/thing_display.o: /usr/include/sys/_types/_timeval.h
.o/thing_display.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_display.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_display.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_display.o: /usr/include/sys/_types/_fd_set.h
.o/thing_display.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_display.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_display.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_display.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_display.o: /usr/include/sys/_select.h
.o/thing_display.o: /usr/include/sys/_types/_dev_t.h
.o/thing_display.o: /usr/include/sys/_types/_mode_t.h
.o/thing_display.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_display.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_display.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_display.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_display.o: my_tile.h my_color.h my_size.h my_thing_ai.h my_font.h
.o/thing_display.o: my_gl.h
.o/thing_enemy.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_enemy.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_enemy.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_enemy.o: /usr/include/sys/_types/_va_list.h
.o/thing_enemy.o: /usr/include/sys/_types/_size_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_enemy.o: /usr/include/sys/_types/_off_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_enemy.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_enemy.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_enemy.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_enemy.o: c_plus_plus_serializer.h my_globals.h my_tile.h my_sdl.h
.o/thing_enemy.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_enemy.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_enemy.o: /usr/include/sys/_types/_clock_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_time_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_enemy.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_enemy.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_enemy.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_enemy.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_enemy.o: my_thing.h my_time.h /usr/include/unistd.h
.o/thing_enemy.o: /usr/include/sys/unistd.h
.o/thing_enemy.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_enemy.o: /usr/include/sys/_types/_seek_set.h
.o/thing_enemy.o: /usr/include/sys/_types/_uid_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_gid_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_pid_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_enemy.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_def.h
.o/thing_enemy.o: /usr/include/sys/_types/_timeval.h
.o/thing_enemy.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_set.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_enemy.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_enemy.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_mode_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_enemy.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_enemy.o: /usr/include/sys/_types/_timeval64.h my_light.h
.o/thing_enemy.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/thing_enemy.o: my_dmap.h my_sprintf.h /usr/include/string.h
.o/thing_enemy.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_enemy.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_enemy.o: /usr/include/secure/_strings.h
.o/thing_enemy.o: /usr/include/secure/_string.h
.o/thing_fadeup.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_fadeup.o: /usr/include/sys/cdefs.h
.o/thing_fadeup.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_fadeup.o: /usr/include/sys/_posix_availability.h
.o/thing_fadeup.o: /usr/include/Availability.h
.o/thing_fadeup.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_fadeup.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_fadeup.o: /usr/include/i386/_types.h
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
.o/thing_fadeup.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_fadeup.o: /usr/include/sys/_types/_va_list.h
.o/thing_fadeup.o: /usr/include/sys/_types/_size_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_fadeup.o: /usr/include/sys/_types/_off_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_fadeup.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_fadeup.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_fadeup.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_fadeup.o: c_plus_plus_serializer.h my_globals.h my_sdl.h
.o/thing_fadeup.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_fadeup.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_fadeup.o: /usr/include/sys/_types/_clock_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_time_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_fadeup.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_fadeup.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_fadeup.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_fadeup.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_fadeup.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_fadeup.o: /usr/include/sys/unistd.h
.o/thing_fadeup.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_fadeup.o: /usr/include/sys/_types/_seek_set.h
.o/thing_fadeup.o: /usr/include/sys/_types/_uid_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_gid_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_pid_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_fadeup.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_def.h
.o/thing_fadeup.o: /usr/include/sys/_types/_timeval.h
.o/thing_fadeup.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_set.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_fadeup.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_fadeup.o: /usr/include/sys/_select.h
.o/thing_fadeup.o: /usr/include/sys/_types/_dev_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_mode_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_fadeup.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_fadeup.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_fadeup.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_fadeup.o: my_tile.h my_color.h my_size.h my_thing_ai.h my_sprintf.h
.o/thing_fadeup.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_fadeup.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_fadeup.o: /usr/include/secure/_strings.h
.o/thing_fadeup.o: /usr/include/secure/_string.h my_gl.h
.o/thing_health.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_health.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_health.o: /usr/include/sys/_types/_va_list.h
.o/thing_health.o: /usr/include/sys/_types/_size_t.h
.o/thing_health.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_health.o: /usr/include/sys/_types/_off_t.h
.o/thing_health.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_health.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_health.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_health.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_health.o: c_plus_plus_serializer.h my_globals.h my_tile.h my_sdl.h
.o/thing_health.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_health.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_health.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_health.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_health.o: /usr/include/sys/_types/_clock_t.h
.o/thing_health.o: /usr/include/sys/_types/_time_t.h
.o/thing_health.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_health.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_health.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_health.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_health.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_health.o: my_thing.h my_time.h /usr/include/unistd.h
.o/thing_health.o: /usr/include/sys/unistd.h
.o/thing_health.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_health.o: /usr/include/sys/_types/_seek_set.h
.o/thing_health.o: /usr/include/sys/_types/_uid_t.h
.o/thing_health.o: /usr/include/sys/_types/_gid_t.h
.o/thing_health.o: /usr/include/sys/_types/_pid_t.h
.o/thing_health.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_health.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_health.o: /usr/include/sys/_types/_fd_def.h
.o/thing_health.o: /usr/include/sys/_types/_timeval.h
.o/thing_health.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_health.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_health.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_health.o: /usr/include/sys/_types/_fd_set.h
.o/thing_health.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_health.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_health.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_health.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_health.o: /usr/include/sys/_select.h
.o/thing_health.o: /usr/include/sys/_types/_dev_t.h
.o/thing_health.o: /usr/include/sys/_types/_mode_t.h
.o/thing_health.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_health.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_health.o: /usr/include/sys/_types/_timeval64.h my_light.h
.o/thing_health.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/thing_health.o: my_dmap.h
.o/thing_hit.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_hit.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/thing_hit.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_hit.o: /usr/include/sys/_types/_va_list.h
.o/thing_hit.o: /usr/include/sys/_types/_size_t.h
.o/thing_hit.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_hit.o: /usr/include/sys/_types/_off_t.h
.o/thing_hit.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_hit.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_hit.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_hit.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_hit.o: c_plus_plus_serializer.h my_globals.h my_tile.h my_sdl.h
.o/thing_hit.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_hit.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_hit.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_hit.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_hit.o: /usr/include/sys/_types/_clock_t.h
.o/thing_hit.o: /usr/include/sys/_types/_time_t.h
.o/thing_hit.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_hit.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_hit.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_hit.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_hit.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_hit.o: my_thing.h my_time.h /usr/include/unistd.h
.o/thing_hit.o: /usr/include/sys/unistd.h
.o/thing_hit.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_hit.o: /usr/include/sys/_types/_seek_set.h
.o/thing_hit.o: /usr/include/sys/_types/_uid_t.h
.o/thing_hit.o: /usr/include/sys/_types/_gid_t.h
.o/thing_hit.o: /usr/include/sys/_types/_pid_t.h
.o/thing_hit.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_hit.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_def.h
.o/thing_hit.o: /usr/include/sys/_types/_timeval.h
.o/thing_hit.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_hit.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_set.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_hit.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_hit.o: /usr/include/sys/_types/_dev_t.h
.o/thing_hit.o: /usr/include/sys/_types/_mode_t.h
.o/thing_hit.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_hit.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_hit.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/thing_hit.o: my_thing_ai.h my_dmap.h my_sprintf.h /usr/include/string.h
.o/thing_hit.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_hit.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_hit.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing_hunger.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_hunger.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_hunger.o: /usr/include/sys/_types/_va_list.h
.o/thing_hunger.o: /usr/include/sys/_types/_size_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_hunger.o: /usr/include/sys/_types/_off_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_hunger.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_hunger.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_hunger.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_hunger.o: c_plus_plus_serializer.h my_globals.h my_tile.h my_sdl.h
.o/thing_hunger.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_hunger.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_hunger.o: /usr/include/sys/_types/_clock_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_time_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_hunger.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_hunger.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_hunger.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_hunger.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_hunger.o: my_thing.h my_time.h /usr/include/unistd.h
.o/thing_hunger.o: /usr/include/sys/unistd.h
.o/thing_hunger.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_hunger.o: /usr/include/sys/_types/_seek_set.h
.o/thing_hunger.o: /usr/include/sys/_types/_uid_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_gid_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_pid_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_hunger.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_def.h
.o/thing_hunger.o: /usr/include/sys/_types/_timeval.h
.o/thing_hunger.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_set.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_hunger.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_hunger.o: /usr/include/sys/_select.h
.o/thing_hunger.o: /usr/include/sys/_types/_dev_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_mode_t.h
.o/thing_hunger.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_hunger.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_hunger.o: /usr/include/sys/_types/_timeval64.h my_light.h
.o/thing_hunger.o: my_thing_template.h my_dice.h my_size.h my_thing_ai.h
.o/thing_hunger.o: my_dmap.h
.o/thing_id.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_id.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/thing_id.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_id.o: /usr/include/sys/_types/_va_list.h
.o/thing_id.o: /usr/include/sys/_types/_size_t.h
.o/thing_id.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_id.o: /usr/include/sys/_types/_off_t.h
.o/thing_id.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_id.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_id.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_id.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_id.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing_id.o: my_math.h /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing_id.o: /usr/include/sys/unistd.h
.o/thing_id.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_id.o: /usr/include/sys/_types/_seek_set.h
.o/thing_id.o: /usr/include/sys/_types/_uid_t.h
.o/thing_id.o: /usr/include/sys/_types/_gid_t.h
.o/thing_id.o: /usr/include/sys/_types/_pid_t.h
.o/thing_id.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_id.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_id.o: /usr/include/sys/_types/_fd_def.h
.o/thing_id.o: /usr/include/sys/_types/_timespec.h
.o/thing_id.o: /usr/include/sys/_types/_timeval.h
.o/thing_id.o: /usr/include/sys/_types/_time_t.h
.o/thing_id.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_id.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_id.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_id.o: /usr/include/sys/_types/_fd_set.h
.o/thing_id.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_id.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_id.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_id.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_id.o: /usr/include/sys/_types/_dev_t.h
.o/thing_id.o: /usr/include/sys/_types/_mode_t.h
.o/thing_id.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_id.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_id.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_id.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_id.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_id.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_id.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_id.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_id.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_id.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_id.o: my_depth.h my_color.h my_dmap.h my_thing.h my_light.h
.o/thing_id.o: my_thing_template.h my_dice.h my_tile.h my_size.h
.o/thing_id.o: my_thing_ai.h
.o/thing_items.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_items.o: /usr/include/sys/cdefs.h
.o/thing_items.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_items.o: /usr/include/sys/_posix_availability.h
.o/thing_items.o: /usr/include/Availability.h
.o/thing_items.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_items.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_items.o: /usr/include/i386/_types.h
.o/thing_items.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_items.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_items.o: /usr/include/sys/_types/_int8_t.h
.o/thing_items.o: /usr/include/sys/_types/_int16_t.h
.o/thing_items.o: /usr/include/sys/_types/_int32_t.h
.o/thing_items.o: /usr/include/sys/_types/_int64_t.h
.o/thing_items.o: /usr/include/_types/_uint8_t.h
.o/thing_items.o: /usr/include/_types/_uint16_t.h
.o/thing_items.o: /usr/include/_types/_uint32_t.h
.o/thing_items.o: /usr/include/_types/_uint64_t.h
.o/thing_items.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_items.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_items.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_items.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_items.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_items.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_items.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_items.o: /usr/include/_types/_intmax_t.h
.o/thing_items.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_items.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_items.o: /usr/include/sys/_types/_va_list.h
.o/thing_items.o: /usr/include/sys/_types/_size_t.h
.o/thing_items.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_items.o: /usr/include/sys/_types/_off_t.h
.o/thing_items.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_items.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_items.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_items.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_items.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/thing_items.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_items.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_items.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_items.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_items.o: /usr/include/sys/_types/_clock_t.h
.o/thing_items.o: /usr/include/sys/_types/_time_t.h
.o/thing_items.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_items.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_items.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_items.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_items.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_items.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_items.o: /usr/include/sys/unistd.h
.o/thing_items.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_items.o: /usr/include/sys/_types/_seek_set.h
.o/thing_items.o: /usr/include/sys/_types/_uid_t.h
.o/thing_items.o: /usr/include/sys/_types/_gid_t.h
.o/thing_items.o: /usr/include/sys/_types/_pid_t.h
.o/thing_items.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_items.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_items.o: /usr/include/sys/_types/_fd_def.h
.o/thing_items.o: /usr/include/sys/_types/_timeval.h
.o/thing_items.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_items.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_items.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_items.o: /usr/include/sys/_types/_fd_set.h
.o/thing_items.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_items.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_items.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_items.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_items.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_items.o: /usr/include/sys/_types/_mode_t.h
.o/thing_items.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_items.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_items.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_items.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_items.o: my_tile.h my_color.h my_size.h my_thing_ai.h my_sprintf.h
.o/thing_items.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_items.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_items.o: /usr/include/secure/_strings.h
.o/thing_items.o: /usr/include/secure/_string.h my_gl.h
.o/thing_lava.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_lava.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_lava.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_lava.o: /usr/include/sys/_types/_va_list.h
.o/thing_lava.o: /usr/include/sys/_types/_size_t.h
.o/thing_lava.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_lava.o: /usr/include/sys/_types/_off_t.h
.o/thing_lava.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_lava.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_lava.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_lava.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_lava.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing_lava.o: my_math.h /usr/include/math.h my_time.h
.o/thing_lava.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_lava.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_lava.o: /usr/include/sys/_types/_seek_set.h
.o/thing_lava.o: /usr/include/sys/_types/_uid_t.h
.o/thing_lava.o: /usr/include/sys/_types/_gid_t.h
.o/thing_lava.o: /usr/include/sys/_types/_pid_t.h
.o/thing_lava.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_lava.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_def.h
.o/thing_lava.o: /usr/include/sys/_types/_timespec.h
.o/thing_lava.o: /usr/include/sys/_types/_timeval.h
.o/thing_lava.o: /usr/include/sys/_types/_time_t.h
.o/thing_lava.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_lava.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_set.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_lava.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_lava.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_lava.o: /usr/include/sys/_types/_mode_t.h
.o/thing_lava.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_lava.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_lava.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_lava.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_lava.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_lava.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_lava.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_lava.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_lava.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_lava.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_lava.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/thing_lava.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/thing_lava.o: my_dmap.h my_sprintf.h /usr/include/string.h
.o/thing_lava.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_lava.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_lava.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing_level.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_level.o: /usr/include/sys/cdefs.h
.o/thing_level.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_level.o: /usr/include/sys/_posix_availability.h
.o/thing_level.o: /usr/include/Availability.h
.o/thing_level.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_level.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_level.o: /usr/include/i386/_types.h
.o/thing_level.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_level.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_level.o: /usr/include/sys/_types/_int8_t.h
.o/thing_level.o: /usr/include/sys/_types/_int16_t.h
.o/thing_level.o: /usr/include/sys/_types/_int32_t.h
.o/thing_level.o: /usr/include/sys/_types/_int64_t.h
.o/thing_level.o: /usr/include/_types/_uint8_t.h
.o/thing_level.o: /usr/include/_types/_uint16_t.h
.o/thing_level.o: /usr/include/_types/_uint32_t.h
.o/thing_level.o: /usr/include/_types/_uint64_t.h
.o/thing_level.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_level.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_level.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_level.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_level.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_level.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_level.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_level.o: /usr/include/_types/_intmax_t.h
.o/thing_level.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_level.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_level.o: /usr/include/sys/_types/_va_list.h
.o/thing_level.o: /usr/include/sys/_types/_size_t.h
.o/thing_level.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_level.o: /usr/include/sys/_types/_off_t.h
.o/thing_level.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_level.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_level.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_level.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_level.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/thing_level.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_level.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_level.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_level.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_level.o: /usr/include/sys/_types/_clock_t.h
.o/thing_level.o: /usr/include/sys/_types/_time_t.h
.o/thing_level.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_level.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_level.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_level.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_level.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_level.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_level.o: /usr/include/sys/unistd.h
.o/thing_level.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_level.o: /usr/include/sys/_types/_seek_set.h
.o/thing_level.o: /usr/include/sys/_types/_uid_t.h
.o/thing_level.o: /usr/include/sys/_types/_gid_t.h
.o/thing_level.o: /usr/include/sys/_types/_pid_t.h
.o/thing_level.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_level.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_level.o: /usr/include/sys/_types/_fd_def.h
.o/thing_level.o: /usr/include/sys/_types/_timeval.h
.o/thing_level.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_level.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_level.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_level.o: /usr/include/sys/_types/_fd_set.h
.o/thing_level.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_level.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_level.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_level.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_level.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_level.o: /usr/include/sys/_types/_mode_t.h
.o/thing_level.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_level.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_level.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_level.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_level.o: my_tile.h my_color.h my_size.h my_thing_ai.h
.o/thing_lifespan.o: my_thing.h my_time.h /usr/include/assert.h
.o/thing_lifespan.o: /usr/include/sys/cdefs.h
.o/thing_lifespan.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_lifespan.o: /usr/include/sys/_posix_availability.h
.o/thing_lifespan.o: /usr/include/unistd.h /usr/include/_types.h
.o/thing_lifespan.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_lifespan.o: /usr/include/i386/_types.h
.o/thing_lifespan.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_lifespan.o: /usr/include/sys/unistd.h
.o/thing_lifespan.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_lifespan.o: /usr/include/sys/_types/_seek_set.h
.o/thing_lifespan.o: /usr/include/sys/_types/_size_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint64_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint32_t.h
.o/thing_lifespan.o: /usr/include/Availability.h
.o/thing_lifespan.o: /usr/include/AvailabilityInternal.h
.o/thing_lifespan.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_lifespan.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int8_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int16_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int32_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_int64_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_uid_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_gid_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_off_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_pid_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_null.h
.o/thing_lifespan.o: /usr/include/sys/select.h
.o/thing_lifespan.o: /usr/include/sys/appleapiopts.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_def.h
.o/thing_lifespan.o: /usr/include/sys/_types/_timespec.h
.o/thing_lifespan.o: /usr/include/sys/_types/_timeval.h
.o/thing_lifespan.o: /usr/include/sys/_types/_time_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_set.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_lifespan.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_lifespan.o: /usr/include/sys/_select.h
.o/thing_lifespan.o: /usr/include/sys/_types/_dev_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_mode_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_lifespan.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_lifespan.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_lifespan.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_main.h
.o/thing_lifespan.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_lifespan.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_lifespan.o: /usr/include/_types/_uint8_t.h
.o/thing_lifespan.o: /usr/include/_types/_uint16_t.h
.o/thing_lifespan.o: /usr/include/_types/_intmax_t.h
.o/thing_lifespan.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_lifespan.o: my_callstack.h /usr/include/stdio.h
.o/thing_lifespan.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_lifespan.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/thing_lifespan.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_lifespan.o: my_bounds_check.h my_vector_bounds_check.h
.o/thing_lifespan.o: c_plus_plus_serializer.h my_globals.h my_command.h
.o/thing_lifespan.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_lifespan.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_lifespan.o: /usr/include/__wctype.h
.o/thing_lifespan.o: /usr/include/sys/_types/_wint_t.h
.o/thing_lifespan.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_lifespan.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_lifespan.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_lifespan.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_lifespan.o: my_size.h my_thing_ai.h my_dmap.h my_sprintf.h
.o/thing_lifespan.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_lifespan.o: /usr/include/sys/_types/_errno_t.h
.o/thing_lifespan.o: /usr/include/strings.h /usr/include/secure/_strings.h
.o/thing_lifespan.o: /usr/include/secure/_string.h
.o/thing_log.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/thing_log.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_log.o: /usr/include/sys/_types/_va_list.h
.o/thing_log.o: /usr/include/sys/_types/_size_t.h
.o/thing_log.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_log.o: /usr/include/sys/_types/_off_t.h
.o/thing_log.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_log.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_log.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_log.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_log.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/thing_log.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_log.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_log.o: /usr/include/sys/_types/_clock_t.h
.o/thing_log.o: /usr/include/sys/_types/_time_t.h
.o/thing_log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_log.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_log.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_log.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_log.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_log.o: /usr/include/sys/unistd.h
.o/thing_log.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_log.o: /usr/include/sys/_types/_seek_set.h
.o/thing_log.o: /usr/include/sys/_types/_uid_t.h
.o/thing_log.o: /usr/include/sys/_types/_gid_t.h
.o/thing_log.o: /usr/include/sys/_types/_pid_t.h
.o/thing_log.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_log.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_log.o: /usr/include/sys/_types/_fd_def.h
.o/thing_log.o: /usr/include/sys/_types/_timeval.h
.o/thing_log.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_log.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_log.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_log.o: /usr/include/sys/_types/_fd_set.h
.o/thing_log.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_log.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_log.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_log.o: /usr/include/sys/_types/_dev_t.h
.o/thing_log.o: /usr/include/sys/_types/_mode_t.h
.o/thing_log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_log.o: my_depth.h my_dmap.h my_traceback.h my_console.h
.o/thing_log.o: my_wid_console.h my_wid.h my_size.h my_ascii.h my_color.h
.o/thing_log.o: my_tex.h my_tile.h my_wid_tiles.h my_log.h my_thing.h
.o/thing_log.o: my_light.h my_thing_template.h my_dice.h my_thing_ai.h
.o/thing_lunge.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_lunge.o: /usr/include/sys/cdefs.h
.o/thing_lunge.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_lunge.o: /usr/include/sys/_posix_availability.h
.o/thing_lunge.o: /usr/include/Availability.h
.o/thing_lunge.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_lunge.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_lunge.o: /usr/include/i386/_types.h
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
.o/thing_lunge.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_lunge.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_lunge.o: /usr/include/sys/_types/_va_list.h
.o/thing_lunge.o: /usr/include/sys/_types/_size_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_lunge.o: /usr/include/sys/_types/_off_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_lunge.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_lunge.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_lunge.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_lunge.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/thing_lunge.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_lunge.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_lunge.o: /usr/include/sys/_types/_clock_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_time_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_lunge.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_lunge.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_lunge.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_lunge.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_lunge.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_lunge.o: /usr/include/sys/unistd.h
.o/thing_lunge.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_lunge.o: /usr/include/sys/_types/_seek_set.h
.o/thing_lunge.o: /usr/include/sys/_types/_uid_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_gid_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_pid_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_lunge.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_def.h
.o/thing_lunge.o: /usr/include/sys/_types/_timeval.h
.o/thing_lunge.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_set.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_lunge.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_lunge.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_mode_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_lunge.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_lunge.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_lunge.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_lunge.o: my_tile.h my_color.h my_size.h my_thing_ai.h my_sprintf.h
.o/thing_lunge.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_lunge.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_lunge.o: /usr/include/secure/_strings.h
.o/thing_lunge.o: /usr/include/secure/_string.h my_gl.h
.o/thing_minimap.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_minimap.o: /usr/include/sys/cdefs.h
.o/thing_minimap.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_minimap.o: /usr/include/sys/_posix_availability.h
.o/thing_minimap.o: /usr/include/Availability.h
.o/thing_minimap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_minimap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_minimap.o: /usr/include/i386/_types.h
.o/thing_minimap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_minimap.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_minimap.o: /usr/include/sys/_types/_int8_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_int16_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_int32_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_int64_t.h
.o/thing_minimap.o: /usr/include/_types/_uint8_t.h
.o/thing_minimap.o: /usr/include/_types/_uint16_t.h
.o/thing_minimap.o: /usr/include/_types/_uint32_t.h
.o/thing_minimap.o: /usr/include/_types/_uint64_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_minimap.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_minimap.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_minimap.o: /usr/include/_types/_intmax_t.h
.o/thing_minimap.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_minimap.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_minimap.o: /usr/include/sys/_types/_va_list.h
.o/thing_minimap.o: /usr/include/sys/_types/_size_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_minimap.o: /usr/include/sys/_types/_off_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_minimap.o: /usr/include/secure/_stdio.h
.o/thing_minimap.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_minimap.o: my_bounds_check.h /usr/include/assert.h
.o/thing_minimap.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_minimap.o: my_globals.h my_game.h my_sdl.h my_command.h my_token.h
.o/thing_minimap.o: my_string.h /usr/include/wchar.h
.o/thing_minimap.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_minimap.o: /usr/include/sys/_types/_clock_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_time_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_timespec.h
.o/thing_minimap.o: /usr/include/_wctype.h /usr/include/__wctype.h
.o/thing_minimap.o: /usr/include/sys/_types/_wint_t.h
.o/thing_minimap.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_minimap.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_minimap.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_minimap.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_minimap.o: /usr/include/sys/unistd.h
.o/thing_minimap.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_minimap.o: /usr/include/sys/_types/_seek_set.h
.o/thing_minimap.o: /usr/include/sys/_types/_uid_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_gid_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_pid_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_minimap.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_def.h
.o/thing_minimap.o: /usr/include/sys/_types/_timeval.h
.o/thing_minimap.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_set.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_minimap.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_minimap.o: /usr/include/sys/_select.h
.o/thing_minimap.o: /usr/include/sys/_types/_dev_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_mode_t.h
.o/thing_minimap.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_minimap.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_minimap.o: /usr/include/sys/_types/_timeval64.h my_depth.h my_dmap.h
.o/thing_minimap.o: my_tile.h my_color.h my_tex.h my_gl.h my_thing.h
.o/thing_minimap.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/thing_minimap.o: my_thing_ai.h
.o/thing_move.o: my_game.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_move.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_move.o: /usr/include/sys/_posix_availability.h
.o/thing_move.o: /usr/include/Availability.h
.o/thing_move.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/thing_move.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_move.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_move.o: /usr/include/sys/_types/_va_list.h
.o/thing_move.o: /usr/include/sys/_types/_size_t.h
.o/thing_move.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_move.o: /usr/include/sys/_types/_off_t.h
.o/thing_move.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_move.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_move.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_move.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_move.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/thing_move.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_move.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_move.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_move.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_move.o: /usr/include/sys/_types/_clock_t.h
.o/thing_move.o: /usr/include/sys/_types/_time_t.h
.o/thing_move.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_move.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_move.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_move.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_move.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_move.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_move.o: /usr/include/sys/unistd.h
.o/thing_move.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_move.o: /usr/include/sys/_types/_seek_set.h
.o/thing_move.o: /usr/include/sys/_types/_uid_t.h
.o/thing_move.o: /usr/include/sys/_types/_gid_t.h
.o/thing_move.o: /usr/include/sys/_types/_pid_t.h
.o/thing_move.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_move.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_move.o: /usr/include/sys/_types/_fd_def.h
.o/thing_move.o: /usr/include/sys/_types/_timeval.h
.o/thing_move.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_move.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_move.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_move.o: /usr/include/sys/_types/_fd_set.h
.o/thing_move.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_move.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_move.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_move.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_move.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_move.o: /usr/include/sys/_types/_mode_t.h
.o/thing_move.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_move.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_move.o: my_depth.h my_dmap.h my_thing.h my_light.h
.o/thing_move.o: my_thing_template.h my_dice.h my_tile.h my_color.h my_size.h
.o/thing_move.o: my_thing_ai.h my_sprintf.h /usr/include/string.h
.o/thing_move.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_move.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_move.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing_move.o: my_gl.h
.o/thing_move_dir.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_move_dir.o: /usr/include/sys/cdefs.h
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
.o/thing_move_dir.o: my_callstack.h /usr/include/stdio.h
.o/thing_move_dir.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_move_dir.o: /usr/include/sys/_types/_size_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_move_dir.o: /usr/include/sys/_types/_off_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_move_dir.o: /usr/include/secure/_stdio.h
.o/thing_move_dir.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_move_dir.o: my_bounds_check.h /usr/include/assert.h
.o/thing_move_dir.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_move_dir.o: my_globals.h my_level.h my_point.h my_math.h
.o/thing_move_dir.o: /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing_move_dir.o: /usr/include/sys/unistd.h
.o/thing_move_dir.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_move_dir.o: /usr/include/sys/_types/_seek_set.h
.o/thing_move_dir.o: /usr/include/sys/_types/_uid_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_gid_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_pid_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_move_dir.o: /usr/include/sys/select.h
.o/thing_move_dir.o: /usr/include/sys/appleapiopts.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_def.h
.o/thing_move_dir.o: /usr/include/sys/_types/_timespec.h
.o/thing_move_dir.o: /usr/include/sys/_types/_timeval.h
.o/thing_move_dir.o: /usr/include/sys/_types/_time_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_set.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_move_dir.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_move_dir.o: /usr/include/sys/_select.h
.o/thing_move_dir.o: /usr/include/sys/_types/_dev_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_mode_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_move_dir.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_move_dir.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_move_dir.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_move_dir.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_move_dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_move_dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_move_dir.o: /usr/include/__wctype.h
.o/thing_move_dir.o: /usr/include/sys/_types/_wint_t.h
.o/thing_move_dir.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_move_dir.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_move_dir.o: my_depth.h my_color.h my_dmap.h my_thing.h my_light.h
.o/thing_move_dir.o: my_thing_template.h my_dice.h my_tile.h my_size.h
.o/thing_move_dir.o: my_thing_ai.h
.o/thing_msg.o: my_thing.h my_time.h /usr/include/assert.h
.o/thing_msg.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_msg.o: /usr/include/sys/_posix_availability.h /usr/include/unistd.h
.o/thing_msg.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_msg.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_msg.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_msg.o: /usr/include/sys/unistd.h
.o/thing_msg.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_msg.o: /usr/include/sys/_types/_seek_set.h
.o/thing_msg.o: /usr/include/sys/_types/_size_t.h
.o/thing_msg.o: /usr/include/_types/_uint64_t.h
.o/thing_msg.o: /usr/include/_types/_uint32_t.h /usr/include/Availability.h
.o/thing_msg.o: /usr/include/AvailabilityInternal.h
.o/thing_msg.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_msg.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_msg.o: /usr/include/sys/_types/_int8_t.h
.o/thing_msg.o: /usr/include/sys/_types/_int16_t.h
.o/thing_msg.o: /usr/include/sys/_types/_int32_t.h
.o/thing_msg.o: /usr/include/sys/_types/_int64_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_msg.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_msg.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_msg.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_msg.o: /usr/include/sys/_types/_uid_t.h
.o/thing_msg.o: /usr/include/sys/_types/_gid_t.h
.o/thing_msg.o: /usr/include/sys/_types/_off_t.h
.o/thing_msg.o: /usr/include/sys/_types/_pid_t.h
.o/thing_msg.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_msg.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/thing_msg.o: /usr/include/sys/appleapiopts.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_def.h
.o/thing_msg.o: /usr/include/sys/_types/_timespec.h
.o/thing_msg.o: /usr/include/sys/_types/_timeval.h
.o/thing_msg.o: /usr/include/sys/_types/_time_t.h
.o/thing_msg.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_msg.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_set.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_msg.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_msg.o: /usr/include/sys/_types/_dev_t.h
.o/thing_msg.o: /usr/include/sys/_types/_mode_t.h
.o/thing_msg.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_msg.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_msg.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_msg.o: my_sdl.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_msg.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_msg.o: /usr/include/_types/_uint8_t.h
.o/thing_msg.o: /usr/include/_types/_uint16_t.h
.o/thing_msg.o: /usr/include/_types/_intmax_t.h
.o/thing_msg.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/thing_msg.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_msg.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/thing_msg.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_msg.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_msg.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_msg.o: my_globals.h my_command.h my_token.h my_string.h
.o/thing_msg.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_msg.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_msg.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_msg.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_msg.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_msg.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_msg.o: my_light.h my_thing_template.h my_dice.h my_tile.h my_point.h
.o/thing_msg.o: my_math.h /usr/include/math.h my_color.h my_size.h
.o/thing_msg.o: my_thing_ai.h my_dmap.h my_sprintf.h /usr/include/string.h
.o/thing_msg.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_msg.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_msg.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing_name.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_name.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_name.o: /usr/include/sys/_posix_availability.h
.o/thing_name.o: /usr/include/Availability.h
.o/thing_name.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_name.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_name.o: /usr/include/i386/_types.h
.o/thing_name.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_name.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_name.o: /usr/include/sys/_types/_int8_t.h
.o/thing_name.o: /usr/include/sys/_types/_int16_t.h
.o/thing_name.o: /usr/include/sys/_types/_int32_t.h
.o/thing_name.o: /usr/include/sys/_types/_int64_t.h
.o/thing_name.o: /usr/include/_types/_uint8_t.h
.o/thing_name.o: /usr/include/_types/_uint16_t.h
.o/thing_name.o: /usr/include/_types/_uint32_t.h
.o/thing_name.o: /usr/include/_types/_uint64_t.h
.o/thing_name.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_name.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_name.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_name.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_name.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_name.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_name.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_name.o: /usr/include/_types/_intmax_t.h
.o/thing_name.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_name.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_name.o: /usr/include/sys/_types/_va_list.h
.o/thing_name.o: /usr/include/sys/_types/_size_t.h
.o/thing_name.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_name.o: /usr/include/sys/_types/_off_t.h
.o/thing_name.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_name.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_name.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_name.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_name.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing_name.o: my_math.h /usr/include/math.h my_time.h
.o/thing_name.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_name.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_name.o: /usr/include/sys/_types/_seek_set.h
.o/thing_name.o: /usr/include/sys/_types/_uid_t.h
.o/thing_name.o: /usr/include/sys/_types/_gid_t.h
.o/thing_name.o: /usr/include/sys/_types/_pid_t.h
.o/thing_name.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_name.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_name.o: /usr/include/sys/_types/_fd_def.h
.o/thing_name.o: /usr/include/sys/_types/_timespec.h
.o/thing_name.o: /usr/include/sys/_types/_timeval.h
.o/thing_name.o: /usr/include/sys/_types/_time_t.h
.o/thing_name.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_name.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_name.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_name.o: /usr/include/sys/_types/_fd_set.h
.o/thing_name.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_name.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_name.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_name.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_name.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_name.o: /usr/include/sys/_types/_mode_t.h
.o/thing_name.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_name.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_name.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_name.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_name.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_name.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_name.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_name.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_name.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_name.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_name.o: my_depth.h my_color.h my_dmap.h my_sprintf.h
.o/thing_name.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_name.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_name.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/thing_name.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_name.o: my_tile.h my_size.h my_thing_ai.h
.o/thing_on_fire.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_on_fire.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_on_fire.o: /usr/include/sys/_types/_va_list.h
.o/thing_on_fire.o: /usr/include/sys/_types/_size_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_on_fire.o: /usr/include/sys/_types/_off_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_on_fire.o: /usr/include/secure/_stdio.h
.o/thing_on_fire.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_on_fire.o: my_bounds_check.h /usr/include/assert.h
.o/thing_on_fire.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_on_fire.o: my_globals.h my_level.h my_point.h my_math.h
.o/thing_on_fire.o: /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing_on_fire.o: /usr/include/sys/unistd.h
.o/thing_on_fire.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_on_fire.o: /usr/include/sys/_types/_seek_set.h
.o/thing_on_fire.o: /usr/include/sys/_types/_uid_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_gid_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_pid_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_on_fire.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_def.h
.o/thing_on_fire.o: /usr/include/sys/_types/_timespec.h
.o/thing_on_fire.o: /usr/include/sys/_types/_timeval.h
.o/thing_on_fire.o: /usr/include/sys/_types/_time_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_set.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_on_fire.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_on_fire.o: /usr/include/sys/_select.h
.o/thing_on_fire.o: /usr/include/sys/_types/_dev_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_mode_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_on_fire.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_on_fire.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_on_fire.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_on_fire.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_on_fire.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_on_fire.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_on_fire.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_on_fire.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_on_fire.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/thing_on_fire.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/thing_on_fire.o: my_dmap.h my_sprintf.h /usr/include/string.h
.o/thing_on_fire.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_on_fire.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_on_fire.o: /usr/include/secure/_strings.h
.o/thing_on_fire.o: /usr/include/secure/_string.h
.o/thing_path.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_path.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_path.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_path.o: /usr/include/sys/_types/_va_list.h
.o/thing_path.o: /usr/include/sys/_types/_size_t.h
.o/thing_path.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_path.o: /usr/include/sys/_types/_off_t.h
.o/thing_path.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_path.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_path.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_path.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_path.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/thing_path.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_path.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_path.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_path.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_path.o: /usr/include/sys/_types/_clock_t.h
.o/thing_path.o: /usr/include/sys/_types/_time_t.h
.o/thing_path.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_path.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_path.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_path.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_path.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_path.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_path.o: /usr/include/sys/unistd.h
.o/thing_path.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_path.o: /usr/include/sys/_types/_seek_set.h
.o/thing_path.o: /usr/include/sys/_types/_uid_t.h
.o/thing_path.o: /usr/include/sys/_types/_gid_t.h
.o/thing_path.o: /usr/include/sys/_types/_pid_t.h
.o/thing_path.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_path.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_path.o: /usr/include/sys/_types/_fd_def.h
.o/thing_path.o: /usr/include/sys/_types/_timeval.h
.o/thing_path.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_path.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_path.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_path.o: /usr/include/sys/_types/_fd_set.h
.o/thing_path.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_path.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_path.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_path.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_path.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_path.o: /usr/include/sys/_types/_mode_t.h
.o/thing_path.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_path.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_path.o: my_depth.h my_dmap.h my_wid_console.h my_wid.h my_size.h
.o/thing_path.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/thing_path.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_path.o: my_thing_ai.h
.o/thing_shove.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_shove.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_shove.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_shove.o: /usr/include/sys/_types/_va_list.h
.o/thing_shove.o: /usr/include/sys/_types/_size_t.h
.o/thing_shove.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_shove.o: /usr/include/sys/_types/_off_t.h
.o/thing_shove.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_shove.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_shove.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_shove.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_shove.o: c_plus_plus_serializer.h my_globals.h my_level.h my_point.h
.o/thing_shove.o: my_math.h /usr/include/math.h my_time.h
.o/thing_shove.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_shove.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_shove.o: /usr/include/sys/_types/_seek_set.h
.o/thing_shove.o: /usr/include/sys/_types/_uid_t.h
.o/thing_shove.o: /usr/include/sys/_types/_gid_t.h
.o/thing_shove.o: /usr/include/sys/_types/_pid_t.h
.o/thing_shove.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_shove.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_def.h
.o/thing_shove.o: /usr/include/sys/_types/_timespec.h
.o/thing_shove.o: /usr/include/sys/_types/_timeval.h
.o/thing_shove.o: /usr/include/sys/_types/_time_t.h
.o/thing_shove.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_shove.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_set.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_shove.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_shove.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_shove.o: /usr/include/sys/_types/_mode_t.h
.o/thing_shove.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_shove.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_shove.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_shove.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_shove.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_shove.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_shove.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_shove.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_shove.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_shove.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_shove.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_shove.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/thing_shove.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/thing_shove.o: my_dmap.h my_sprintf.h /usr/include/string.h
.o/thing_shove.o: /usr/include/sys/_types/_rsize_t.h
.o/thing_shove.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_shove.o: /usr/include/secure/_strings.h
.o/thing_shove.o: /usr/include/secure/_string.h
.o/thing_string.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_string.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_string.o: /usr/include/sys/_types/_va_list.h
.o/thing_string.o: /usr/include/sys/_types/_size_t.h
.o/thing_string.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_string.o: /usr/include/sys/_types/_off_t.h
.o/thing_string.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_string.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_string.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_string.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_string.o: c_plus_plus_serializer.h my_globals.h my_level.h
.o/thing_string.o: my_point.h my_math.h /usr/include/math.h my_time.h
.o/thing_string.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_string.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_string.o: /usr/include/sys/_types/_seek_set.h
.o/thing_string.o: /usr/include/sys/_types/_uid_t.h
.o/thing_string.o: /usr/include/sys/_types/_gid_t.h
.o/thing_string.o: /usr/include/sys/_types/_pid_t.h
.o/thing_string.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_string.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_string.o: /usr/include/sys/_types/_fd_def.h
.o/thing_string.o: /usr/include/sys/_types/_timespec.h
.o/thing_string.o: /usr/include/sys/_types/_timeval.h
.o/thing_string.o: /usr/include/sys/_types/_time_t.h
.o/thing_string.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_string.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_string.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_string.o: /usr/include/sys/_types/_fd_set.h
.o/thing_string.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_string.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_string.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_string.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_string.o: /usr/include/sys/_select.h
.o/thing_string.o: /usr/include/sys/_types/_dev_t.h
.o/thing_string.o: /usr/include/sys/_types/_mode_t.h
.o/thing_string.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_string.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_string.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_string.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_string.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_string.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_string.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_string.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_string.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_string.o: my_depth.h my_color.h my_dmap.h my_sprintf.h
.o/thing_string.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/thing_string.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/thing_string.o: /usr/include/secure/_strings.h
.o/thing_string.o: /usr/include/secure/_string.h my_thing.h my_light.h
.o/thing_string.o: my_thing_template.h my_dice.h my_tile.h my_size.h
.o/thing_string.o: my_thing_ai.h
.o/thing_template.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_template.o: /usr/include/sys/cdefs.h
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
.o/thing_template.o: my_callstack.h /usr/include/stdio.h
.o/thing_template.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_template.o: /usr/include/sys/_types/_size_t.h
.o/thing_template.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_template.o: /usr/include/sys/_types/_off_t.h
.o/thing_template.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_template.o: /usr/include/secure/_stdio.h
.o/thing_template.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_template.o: my_bounds_check.h /usr/include/assert.h
.o/thing_template.o: my_vector_bounds_check.h c_plus_plus_serializer.h
.o/thing_template.o: my_globals.h my_level.h my_point.h my_math.h
.o/thing_template.o: /usr/include/math.h my_time.h /usr/include/unistd.h
.o/thing_template.o: /usr/include/sys/unistd.h
.o/thing_template.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_template.o: /usr/include/sys/_types/_seek_set.h
.o/thing_template.o: /usr/include/sys/_types/_uid_t.h
.o/thing_template.o: /usr/include/sys/_types/_gid_t.h
.o/thing_template.o: /usr/include/sys/_types/_pid_t.h
.o/thing_template.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_template.o: /usr/include/sys/select.h
.o/thing_template.o: /usr/include/sys/appleapiopts.h
.o/thing_template.o: /usr/include/sys/_types/_fd_def.h
.o/thing_template.o: /usr/include/sys/_types/_timespec.h
.o/thing_template.o: /usr/include/sys/_types/_timeval.h
.o/thing_template.o: /usr/include/sys/_types/_time_t.h
.o/thing_template.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_template.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_template.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_template.o: /usr/include/sys/_types/_fd_set.h
.o/thing_template.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_template.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_template.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_template.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_template.o: /usr/include/sys/_select.h
.o/thing_template.o: /usr/include/sys/_types/_dev_t.h
.o/thing_template.o: /usr/include/sys/_types/_mode_t.h
.o/thing_template.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_template.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_template.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_template.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_command.h
.o/thing_template.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_template.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_template.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_template.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_template.o: /usr/include/__wctype.h
.o/thing_template.o: /usr/include/sys/_types/_wint_t.h
.o/thing_template.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_template.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_template.o: my_depth.h my_thing_template.h my_dice.h my_tile.h
.o/thing_template.o: my_color.h my_size.h
.o/thing_tick.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_tick.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_tick.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_tick.o: /usr/include/sys/_types/_va_list.h
.o/thing_tick.o: /usr/include/sys/_types/_size_t.h
.o/thing_tick.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_tick.o: /usr/include/sys/_types/_off_t.h
.o/thing_tick.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_tick.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_tick.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_tick.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_tick.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/thing_tick.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_tick.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_tick.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_tick.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_tick.o: /usr/include/sys/_types/_clock_t.h
.o/thing_tick.o: /usr/include/sys/_types/_time_t.h
.o/thing_tick.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_tick.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_tick.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_tick.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_tick.o: my_point.h my_math.h /usr/include/math.h my_world.h
.o/thing_tick.o: my_level.h my_time.h /usr/include/unistd.h
.o/thing_tick.o: /usr/include/sys/unistd.h
.o/thing_tick.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_tick.o: /usr/include/sys/_types/_seek_set.h
.o/thing_tick.o: /usr/include/sys/_types/_uid_t.h
.o/thing_tick.o: /usr/include/sys/_types/_gid_t.h
.o/thing_tick.o: /usr/include/sys/_types/_pid_t.h
.o/thing_tick.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_tick.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_def.h
.o/thing_tick.o: /usr/include/sys/_types/_timeval.h
.o/thing_tick.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_tick.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_set.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_tick.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_tick.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_tick.o: /usr/include/sys/_types/_mode_t.h
.o/thing_tick.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_tick.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_tick.o: my_depth.h my_dmap.h my_wid_console.h my_wid.h my_size.h
.o/thing_tick.o: my_ascii.h my_color.h my_tex.h my_tile.h my_wid_tiles.h
.o/thing_tick.o: my_thing.h my_light.h my_thing_template.h my_dice.h
.o/thing_tick.o: my_thing_ai.h
.o/thing_tile.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_tile.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_tile.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_tile.o: /usr/include/sys/_types/_va_list.h
.o/thing_tile.o: /usr/include/sys/_types/_size_t.h
.o/thing_tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_tile.o: /usr/include/sys/_types/_off_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_tile.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_tile.o: my_array_bounds_check.h my_bounds_check.h
.o/thing_tile.o: /usr/include/assert.h my_vector_bounds_check.h
.o/thing_tile.o: c_plus_plus_serializer.h my_globals.h my_tile.h my_sdl.h
.o/thing_tile.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/thing_tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/thing_tile.o: /usr/include/sys/_types/_clock_t.h
.o/thing_tile.o: /usr/include/sys/_types/_time_t.h
.o/thing_tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/thing_tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_tile.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_tile.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_tile.o: my_thing.h my_time.h /usr/include/unistd.h
.o/thing_tile.o: /usr/include/sys/unistd.h
.o/thing_tile.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_tile.o: /usr/include/sys/_types/_seek_set.h
.o/thing_tile.o: /usr/include/sys/_types/_uid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_gid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_pid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_tile.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_def.h
.o/thing_tile.o: /usr/include/sys/_types/_timeval.h
.o/thing_tile.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_tile.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_set.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_tile.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/thing_tile.o: /usr/include/sys/_types/_mode_t.h
.o/thing_tile.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_tile.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_tile.o: my_light.h my_thing_template.h my_dice.h my_size.h
.o/thing_tile.o: my_thing_ai.h my_dmap.h
.o/thing_weapon.o: my_thing.h my_time.h /usr/include/assert.h
.o/thing_weapon.o: /usr/include/sys/cdefs.h
.o/thing_weapon.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_weapon.o: /usr/include/sys/_posix_availability.h
.o/thing_weapon.o: /usr/include/unistd.h /usr/include/_types.h
.o/thing_weapon.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_weapon.o: /usr/include/i386/_types.h
.o/thing_weapon.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_weapon.o: /usr/include/sys/unistd.h
.o/thing_weapon.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_weapon.o: /usr/include/sys/_types/_seek_set.h
.o/thing_weapon.o: /usr/include/sys/_types/_size_t.h
.o/thing_weapon.o: /usr/include/_types/_uint64_t.h
.o/thing_weapon.o: /usr/include/_types/_uint32_t.h
.o/thing_weapon.o: /usr/include/Availability.h
.o/thing_weapon.o: /usr/include/AvailabilityInternal.h
.o/thing_weapon.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_weapon.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_weapon.o: /usr/include/sys/_types/_int8_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_int16_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_int32_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_int64_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_uid_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_gid_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_off_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_pid_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/thing_weapon.o: /usr/include/sys/appleapiopts.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_def.h
.o/thing_weapon.o: /usr/include/sys/_types/_timespec.h
.o/thing_weapon.o: /usr/include/sys/_types/_timeval.h
.o/thing_weapon.o: /usr/include/sys/_types/_time_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_set.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_weapon.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_weapon.o: /usr/include/sys/_select.h
.o/thing_weapon.o: /usr/include/sys/_types/_dev_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_mode_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_weapon.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_weapon.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_weapon.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_main.h
.o/thing_weapon.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_weapon.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_weapon.o: /usr/include/_types/_uint8_t.h
.o/thing_weapon.o: /usr/include/_types/_uint16_t.h
.o/thing_weapon.o: /usr/include/_types/_intmax_t.h
.o/thing_weapon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/thing_weapon.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/thing_weapon.o: /usr/include/sys/_types/_va_list.h
.o/thing_weapon.o: /usr/include/sys/stdio.h /usr/include/secure/_stdio.h
.o/thing_weapon.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/thing_weapon.o: my_bounds_check.h my_vector_bounds_check.h
.o/thing_weapon.o: c_plus_plus_serializer.h my_globals.h my_command.h
.o/thing_weapon.o: my_token.h my_string.h /usr/include/wchar.h
.o/thing_weapon.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_weapon.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_weapon.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_weapon.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_weapon.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/thing_weapon.o: my_light.h my_thing_template.h my_dice.h my_tile.h
.o/thing_weapon.o: my_point.h my_math.h /usr/include/math.h my_color.h
.o/thing_weapon.o: my_size.h my_thing_ai.h my_dmap.h
.o/tile.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/tile.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/tile.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/tile.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tile.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/tile.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/tile.o: c_plus_plus_serializer.h my_globals.h my_depth.h my_gl.h
.o/tile.o: my_color.h my_point.h my_math.h /usr/include/math.h my_tile.h
.o/tile.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/tile.o: /usr/include/sys/_types/_mbstate_t.h
.o/tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/tile.o: /usr/include/sys/_types/_clock_t.h
.o/tile.o: /usr/include/sys/_types/_time_t.h
.o/tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tile.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/tile.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_tex.h
.o/tile.o: my_pixel.h my_size.h my_thing_template.h my_dice.h my_dmap.h
.o/time.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/time.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/time.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/time.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/time.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/time.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/time.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/time.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/time.o: c_plus_plus_serializer.h my_globals.h my_string.h
.o/time.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/time.o: /usr/include/sys/_types/_ct_rune_t.h
.o/time.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/time.o: /usr/include/sys/_types/_clock_t.h
.o/time.o: /usr/include/sys/_types/_time_t.h
.o/time.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/time.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/time.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/time.o: /usr/include/_ctype.h /usr/include/runetype.h my_time.h
.o/time.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/time.o: /usr/include/sys/_types/_posix_vdisable.h
.o/time.o: /usr/include/sys/_types/_seek_set.h
.o/time.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/time.o: /usr/include/sys/_types/_pid_t.h
.o/time.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/time.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/time.o: /usr/include/sys/_types/_timeval.h
.o/time.o: /usr/include/sys/_types/_suseconds_t.h
.o/time.o: /usr/include/sys/_types/_sigset_t.h
.o/time.o: /usr/include/sys/_types/_fd_setsize.h
.o/time.o: /usr/include/sys/_types/_fd_set.h
.o/time.o: /usr/include/sys/_types/_fd_clr.h
.o/time.o: /usr/include/sys/_types/_fd_isset.h
.o/time.o: /usr/include/sys/_types/_fd_zero.h
.o/time.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/time.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/time.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/time.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/time.o: my_sdl.h my_command.h my_token.h my_slre.h
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
.o/token.o: /usr/include/secure/_string.h my_main.h my_pcg_basic.h
.o/token.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/token.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/token.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/token.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/token.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/token.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/token.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/token.o: /usr/include/sys/_types/_off_t.h /usr/include/secure/_stdio.h
.o/token.o: my_array_bounds_check.h my_bounds_check.h /usr/include/assert.h
.o/token.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/token.o: my_slre.h my_token.h my_string.h /usr/include/wchar.h
.o/token.o: /usr/include/sys/_types/_mbstate_t.h
.o/token.o: /usr/include/sys/_types/_ct_rune_t.h
.o/token.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/token.o: /usr/include/sys/_types/_clock_t.h
.o/token.o: /usr/include/sys/_types/_time_t.h
.o/token.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/token.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/token.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/token.o: /usr/include/_ctype.h /usr/include/runetype.h
.o/traceback.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/traceback.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/traceback.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/traceback.o: /usr/include/sys/_types/_va_list.h
.o/traceback.o: /usr/include/sys/_types/_size_t.h
.o/traceback.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/traceback.o: /usr/include/sys/_types/_off_t.h
.o/traceback.o: /usr/include/sys/_types/_ssize_t.h
.o/traceback.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/traceback.o: my_array_bounds_check.h my_bounds_check.h
.o/traceback.o: /usr/include/assert.h my_vector_bounds_check.h
.o/traceback.o: c_plus_plus_serializer.h my_globals.h my_traceback.h
.o/traceback.o: my_sprintf.h /usr/include/string.h
.o/traceback.o: /usr/include/sys/_types/_rsize_t.h
.o/traceback.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/traceback.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
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
.o/traceback.o: /usr/include/sys/_types/_mode_t.h /usr/include/execinfo.h
.o/traceback.o: /usr/include/cxxabi.h /usr/include/stddef.h
.o/traceback.o: /usr/include/sys/_types/_offsetof.h
.o/traceback.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/traceback.o: /usr/include/sys/_types/_wint_t.h
.o/traceback.o: /usr/include/__cxxabi_config.h
.o/ttf.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/ttf.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/ttf.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/ttf.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/ttf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ttf.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/ttf.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/ttf.o: c_plus_plus_serializer.h my_globals.h my_gl.h my_color.h my_point.h
.o/ttf.o: my_math.h /usr/include/math.h my_wid.h my_size.h my_ascii.h
.o/ttf.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ttf.o: /usr/include/sys/_types/_clock_t.h
.o/ttf.o: /usr/include/sys/_types/_time_t.h
.o/ttf.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ttf.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/ttf.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ttf.o: /usr/include/_ctype.h /usr/include/runetype.h my_tex.h my_tile.h
.o/ttf.o: my_sdl.h my_command.h my_token.h my_string.h my_slre.h
.o/ttf.o: my_wid_tiles.h my_ttf.h my_font.h my_ramdisk.h my_time.h
.o/ttf.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ttf.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ttf.o: /usr/include/sys/_types/_seek_set.h
.o/ttf.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/ttf.o: /usr/include/sys/_types/_pid_t.h
.o/ttf.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/ttf.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/ttf.o: /usr/include/sys/_types/_timeval.h
.o/ttf.o: /usr/include/sys/_types/_suseconds_t.h
.o/ttf.o: /usr/include/sys/_types/_sigset_t.h
.o/ttf.o: /usr/include/sys/_types/_fd_setsize.h
.o/ttf.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/ttf.o: /usr/include/sys/_types/_fd_isset.h
.o/ttf.o: /usr/include/sys/_types/_fd_zero.h
.o/ttf.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ttf.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/ttf.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ttf.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ttf.o: my_bits.h my_pixel.h stb_image.h /usr/include/stdlib.h
.o/ttf.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/ttf.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/ttf.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ttf.o: /usr/include/i386/_mcontext.h /usr/include/mach/machine/_structs.h
.o/ttf.o: /usr/include/mach/i386/_structs.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ttf.o: /usr/include/sys/_types/_sigaltstack.h
.o/ttf.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
.o/ttf.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ttf.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/ttf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ttf.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/ttf.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/ttf.o: /usr/include/sys/_types/_rsize_t.h /usr/include/string.h
.o/ttf.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ttf.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/ttf.o: /usr/include/limits.h /usr/include/machine/limits.h
.o/ttf.o: /usr/include/i386/limits.h /usr/include/i386/_limits.h
.o/ttf.o: /usr/include/sys/syslimits.h stb_image_write.h
.o/util.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/util.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/util.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/util.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/util.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/util.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/util.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/util.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/util.o: c_plus_plus_serializer.h my_globals.h /usr/include/stdlib.h
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
.o/util.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/util.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/util.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/util.o: /usr/include/libkern/_OSByteOrder.h
.o/util.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/util.o: /usr/include/sys/_types/_ct_rune_t.h
.o/util.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_dev_t.h
.o/util.o: /usr/include/sys/_types/_mode_t.h /usr/include/string.h
.o/util.o: /usr/include/sys/_types/_rsize_t.h
.o/util.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/util.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/wid.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/wid.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/wid.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/wid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/wid.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/wid.o: c_plus_plus_serializer.h my_globals.h my_game.h my_sdl.h
.o/wid.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid.o: /usr/include/sys/_types/_clock_t.h
.o/wid.o: /usr/include/sys/_types/_time_t.h
.o/wid.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h my_point.h
.o/wid.o: my_math.h /usr/include/math.h my_world.h my_level.h my_time.h
.o/wid.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/wid.o: /usr/include/sys/_types/_posix_vdisable.h
.o/wid.o: /usr/include/sys/_types/_seek_set.h
.o/wid.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/wid.o: /usr/include/sys/_types/_pid_t.h
.o/wid.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/wid.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/wid.o: /usr/include/sys/_types/_timeval.h
.o/wid.o: /usr/include/sys/_types/_suseconds_t.h
.o/wid.o: /usr/include/sys/_types/_sigset_t.h
.o/wid.o: /usr/include/sys/_types/_fd_setsize.h
.o/wid.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/wid.o: /usr/include/sys/_types/_fd_isset.h
.o/wid.o: /usr/include/sys/_types/_fd_zero.h
.o/wid.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/wid.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/wid.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/wid.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/wid.o: my_depth.h my_dmap.h my_wid.h my_size.h my_ascii.h my_color.h
.o/wid.o: my_tex.h my_tile.h my_wid_tiles.h my_wid_console.h my_wid_minicon.h
.o/wid.o: my_sprintf.h /usr/include/string.h
.o/wid.o: /usr/include/sys/_types/_rsize_t.h
.o/wid.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/wid.o: /usr/include/secure/_strings.h /usr/include/secure/_string.h
.o/wid.o: my_gl.h
.o/wid_console.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_console.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_console.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_console.o: /usr/include/sys/_types/_va_list.h
.o/wid_console.o: /usr/include/sys/_types/_size_t.h
.o/wid_console.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_console.o: /usr/include/sys/_types/_off_t.h
.o/wid_console.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_console.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_console.o: my_array_bounds_check.h my_bounds_check.h
.o/wid_console.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_console.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/wid_console.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_console.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_console.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_console.o: /usr/include/sys/_types/_clock_t.h
.o/wid_console.o: /usr/include/sys/_types/_time_t.h
.o/wid_console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_console.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_console.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_console.o: my_wid_console.h my_wid.h my_point.h my_math.h
.o/wid_console.o: /usr/include/math.h my_size.h my_ascii.h my_color.h
.o/wid_console.o: my_tex.h my_tile.h my_wid_tiles.h my_ttf.h my_font.h
.o/wid_log.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_log.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/wid_log.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_log.o: /usr/include/sys/_types/_va_list.h
.o/wid_log.o: /usr/include/sys/_types/_size_t.h
.o/wid_log.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_log.o: /usr/include/sys/_types/_off_t.h
.o/wid_log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid_log.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/wid_log.o: my_bounds_check.h /usr/include/assert.h
.o/wid_log.o: my_vector_bounds_check.h c_plus_plus_serializer.h my_globals.h
.o/wid_minicon.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_minicon.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/wid_minicon.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_minicon.o: /usr/include/sys/_types/_va_list.h
.o/wid_minicon.o: /usr/include/sys/_types/_size_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_minicon.o: /usr/include/sys/_types/_off_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_minicon.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_minicon.o: my_array_bounds_check.h my_bounds_check.h
.o/wid_minicon.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_minicon.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/wid_minicon.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_minicon.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_minicon.o: /usr/include/sys/_types/_clock_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_time_t.h
.o/wid_minicon.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_minicon.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_minicon.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_minicon.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_minicon.o: my_wid_minicon.h my_point.h my_math.h /usr/include/math.h
.o/wid_minicon.o: my_size.h my_wid.h my_ascii.h my_color.h my_tex.h my_tile.h
.o/wid_minicon.o: my_wid_tiles.h my_ttf.h my_font.h
.o/wid_popup.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_popup.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/wid_popup.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_popup.o: /usr/include/sys/_types/_va_list.h
.o/wid_popup.o: /usr/include/sys/_types/_size_t.h
.o/wid_popup.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_popup.o: /usr/include/sys/_types/_off_t.h
.o/wid_popup.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_popup.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_popup.o: my_array_bounds_check.h my_bounds_check.h
.o/wid_popup.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_popup.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/wid_popup.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_popup.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_popup.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_popup.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_popup.o: /usr/include/sys/_types/_clock_t.h
.o/wid_popup.o: /usr/include/sys/_types/_time_t.h
.o/wid_popup.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_popup.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_popup.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_popup.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_popup.o: my_wid_popup.h my_wid_text_box.h my_wid.h my_point.h
.o/wid_popup.o: my_math.h /usr/include/math.h my_size.h my_ascii.h my_color.h
.o/wid_popup.o: my_tex.h my_tile.h my_wid_tiles.h my_ttf.h my_font.h
.o/wid_test.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_test.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/wid_test.o: /usr/include/sys/_posix_availability.h
.o/wid_test.o: /usr/include/Availability.h
.o/wid_test.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_test.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_test.o: /usr/include/i386/_types.h
.o/wid_test.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_test.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/wid_test.o: /usr/include/sys/_types/_int8_t.h
.o/wid_test.o: /usr/include/sys/_types/_int16_t.h
.o/wid_test.o: /usr/include/sys/_types/_int32_t.h
.o/wid_test.o: /usr/include/sys/_types/_int64_t.h
.o/wid_test.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/wid_test.o: /usr/include/_types/_uint32_t.h
.o/wid_test.o: /usr/include/_types/_uint64_t.h
.o/wid_test.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_test.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_test.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_test.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_test.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_test.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_test.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_test.o: /usr/include/_types/_intmax_t.h
.o/wid_test.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/wid_test.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_test.o: /usr/include/sys/_types/_va_list.h
.o/wid_test.o: /usr/include/sys/_types/_size_t.h
.o/wid_test.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_test.o: /usr/include/sys/_types/_off_t.h
.o/wid_test.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_test.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_test.o: my_array_bounds_check.h my_bounds_check.h
.o/wid_test.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_test.o: c_plus_plus_serializer.h my_globals.h my_sdl.h my_command.h
.o/wid_test.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid_test.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_test.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_test.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_test.o: /usr/include/sys/_types/_clock_t.h
.o/wid_test.o: /usr/include/sys/_types/_time_t.h
.o/wid_test.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_test.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_test.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_test.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_test.o: my_wid_test.h my_wid.h my_point.h my_math.h
.o/wid_test.o: /usr/include/math.h my_size.h my_ascii.h my_color.h my_tex.h
.o/wid_test.o: my_tile.h my_wid_tiles.h my_ttf.h my_font.h my_wid_popup.h
.o/wid_test.o: my_wid_text_box.h
.o/wid_text_box.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_text_box.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_text_box.o: /usr/include/sys/_types/_va_list.h
.o/wid_text_box.o: /usr/include/sys/_types/_size_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_text_box.o: /usr/include/sys/_types/_off_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_text_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_text_box.o: my_array_bounds_check.h my_bounds_check.h
.o/wid_text_box.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_text_box.o: c_plus_plus_serializer.h my_globals.h my_sdl.h
.o/wid_text_box.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/wid_text_box.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_text_box.o: /usr/include/sys/_types/_clock_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_time_t.h
.o/wid_text_box.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_text_box.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_text_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_text_box.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_text_box.o: my_wid_text_box.h my_wid.h my_point.h my_math.h
.o/wid_text_box.o: /usr/include/math.h my_size.h my_ascii.h my_color.h
.o/wid_text_box.o: my_tex.h my_tile.h my_wid_tiles.h my_ttf.h my_font.h
.o/wid_tiles.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_tiles.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h my_callstack.h
.o/wid_tiles.o: /usr/include/stdio.h /usr/include/_stdio.h
.o/wid_tiles.o: /usr/include/sys/_types/_va_list.h
.o/wid_tiles.o: /usr/include/sys/_types/_size_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_tiles.o: /usr/include/sys/_types/_off_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_tiles.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_tiles.o: my_array_bounds_check.h my_bounds_check.h
.o/wid_tiles.o: /usr/include/assert.h my_vector_bounds_check.h
.o/wid_tiles.o: c_plus_plus_serializer.h my_globals.h my_gl.h my_color.h
.o/wid_tiles.o: my_point.h my_math.h /usr/include/math.h my_wid_tiles.h
.o/wid_tiles.o: my_tile.h my_sdl.h my_command.h my_token.h my_string.h
.o/wid_tiles.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid_tiles.o: /usr/include/sys/_types/_clock_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_time_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_tiles.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_tiles.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_tiles.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/wid_tiles.o: my_tex.h
.o/world.o: my_dungeon.h my_room.h my_main.h my_pcg_basic.h
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
.o/world.o: my_ptrcheck.h my_callstack.h /usr/include/stdio.h
.o/world.o: /usr/include/_stdio.h /usr/include/sys/_types/_va_list.h
.o/world.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/world.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/world.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/world.o: /usr/include/secure/_common.h my_array_bounds_check.h
.o/world.o: my_bounds_check.h /usr/include/assert.h my_vector_bounds_check.h
.o/world.o: c_plus_plus_serializer.h my_globals.h my_point.h my_math.h
.o/world.o: /usr/include/math.h my_depth.h my_charmap.h my_dmap.h
.o/world.o: my_level_static.h my_dungeon_grid.h my_thing.h my_time.h
.o/world.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/world.o: /usr/include/sys/_types/_posix_vdisable.h
.o/world.o: /usr/include/sys/_types/_seek_set.h
.o/world.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/world.o: /usr/include/sys/_types/_pid_t.h
.o/world.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/world.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/world.o: /usr/include/sys/_types/_timespec.h
.o/world.o: /usr/include/sys/_types/_timeval.h
.o/world.o: /usr/include/sys/_types/_time_t.h
.o/world.o: /usr/include/sys/_types/_suseconds_t.h
.o/world.o: /usr/include/sys/_types/_sigset_t.h
.o/world.o: /usr/include/sys/_types/_fd_setsize.h
.o/world.o: /usr/include/sys/_types/_fd_set.h
.o/world.o: /usr/include/sys/_types/_fd_clr.h
.o/world.o: /usr/include/sys/_types/_fd_isset.h
.o/world.o: /usr/include/sys/_types/_fd_zero.h
.o/world.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/world.o: /usr/include/sys/_types/_dev_t.h
.o/world.o: /usr/include/sys/_types/_mode_t.h
.o/world.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/world.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/world.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/world.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/world.o: /usr/include/sys/_types/_mbstate_t.h
.o/world.o: /usr/include/sys/_types/_ct_rune_t.h
.o/world.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/world.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/world.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/world.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/world.o: my_light.h my_thing_template.h my_dice.h my_tile.h my_color.h
.o/world.o: my_size.h my_thing_ai.h
.o/world_fini.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/world_fini.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/world_fini.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/world_fini.o: /usr/include/sys/_types/_va_list.h
.o/world_fini.o: /usr/include/sys/_types/_size_t.h
.o/world_fini.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/world_fini.o: /usr/include/sys/_types/_off_t.h
.o/world_fini.o: /usr/include/sys/_types/_ssize_t.h
.o/world_fini.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/world_fini.o: my_array_bounds_check.h my_bounds_check.h
.o/world_fini.o: /usr/include/assert.h my_vector_bounds_check.h
.o/world_fini.o: c_plus_plus_serializer.h my_globals.h my_world.h my_point.h
.o/world_fini.o: my_math.h /usr/include/math.h my_level.h my_time.h
.o/world_fini.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/world_fini.o: /usr/include/sys/_types/_posix_vdisable.h
.o/world_fini.o: /usr/include/sys/_types/_seek_set.h
.o/world_fini.o: /usr/include/sys/_types/_uid_t.h
.o/world_fini.o: /usr/include/sys/_types/_gid_t.h
.o/world_fini.o: /usr/include/sys/_types/_pid_t.h
.o/world_fini.o: /usr/include/sys/_types/_useconds_t.h
.o/world_fini.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/world_fini.o: /usr/include/sys/_types/_fd_def.h
.o/world_fini.o: /usr/include/sys/_types/_timespec.h
.o/world_fini.o: /usr/include/sys/_types/_timeval.h
.o/world_fini.o: /usr/include/sys/_types/_time_t.h
.o/world_fini.o: /usr/include/sys/_types/_suseconds_t.h
.o/world_fini.o: /usr/include/sys/_types/_sigset_t.h
.o/world_fini.o: /usr/include/sys/_types/_fd_setsize.h
.o/world_fini.o: /usr/include/sys/_types/_fd_set.h
.o/world_fini.o: /usr/include/sys/_types/_fd_clr.h
.o/world_fini.o: /usr/include/sys/_types/_fd_isset.h
.o/world_fini.o: /usr/include/sys/_types/_fd_zero.h
.o/world_fini.o: /usr/include/sys/_types/_fd_copy.h
.o/world_fini.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/world_fini.o: /usr/include/sys/_types/_mode_t.h
.o/world_fini.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/world_fini.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/world_fini.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/world_fini.o: my_sdl.h my_command.h my_token.h my_string.h
.o/world_fini.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/world_fini.o: /usr/include/sys/_types/_ct_rune_t.h
.o/world_fini.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/world_fini.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/world_fini.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/world_fini.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/world_fini.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/world_fini.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/world_fini.o: my_dmap.h
.o/world_init.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/world_init.o: /usr/include/_types/_uintmax_t.h my_ptrcheck.h
.o/world_init.o: my_callstack.h /usr/include/stdio.h /usr/include/_stdio.h
.o/world_init.o: /usr/include/sys/_types/_va_list.h
.o/world_init.o: /usr/include/sys/_types/_size_t.h
.o/world_init.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/world_init.o: /usr/include/sys/_types/_off_t.h
.o/world_init.o: /usr/include/sys/_types/_ssize_t.h
.o/world_init.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/world_init.o: my_array_bounds_check.h my_bounds_check.h
.o/world_init.o: /usr/include/assert.h my_vector_bounds_check.h
.o/world_init.o: c_plus_plus_serializer.h my_globals.h my_world.h my_point.h
.o/world_init.o: my_math.h /usr/include/math.h my_level.h my_time.h
.o/world_init.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/world_init.o: /usr/include/sys/_types/_posix_vdisable.h
.o/world_init.o: /usr/include/sys/_types/_seek_set.h
.o/world_init.o: /usr/include/sys/_types/_uid_t.h
.o/world_init.o: /usr/include/sys/_types/_gid_t.h
.o/world_init.o: /usr/include/sys/_types/_pid_t.h
.o/world_init.o: /usr/include/sys/_types/_useconds_t.h
.o/world_init.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/world_init.o: /usr/include/sys/_types/_fd_def.h
.o/world_init.o: /usr/include/sys/_types/_timespec.h
.o/world_init.o: /usr/include/sys/_types/_timeval.h
.o/world_init.o: /usr/include/sys/_types/_time_t.h
.o/world_init.o: /usr/include/sys/_types/_suseconds_t.h
.o/world_init.o: /usr/include/sys/_types/_sigset_t.h
.o/world_init.o: /usr/include/sys/_types/_fd_setsize.h
.o/world_init.o: /usr/include/sys/_types/_fd_set.h
.o/world_init.o: /usr/include/sys/_types/_fd_clr.h
.o/world_init.o: /usr/include/sys/_types/_fd_isset.h
.o/world_init.o: /usr/include/sys/_types/_fd_zero.h
.o/world_init.o: /usr/include/sys/_types/_fd_copy.h
.o/world_init.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/world_init.o: /usr/include/sys/_types/_mode_t.h
.o/world_init.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/world_init.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/world_init.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/world_init.o: my_sdl.h my_command.h my_token.h my_string.h
.o/world_init.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/world_init.o: /usr/include/sys/_types/_ct_rune_t.h
.o/world_init.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/world_init.o: /usr/include/__wctype.h /usr/include/sys/_types/_wint_t.h
.o/world_init.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/world_init.o: /usr/include/_ctype.h /usr/include/runetype.h my_slre.h
.o/world_init.o: my_depth.h my_thing.h my_light.h my_thing_template.h
.o/world_init.o: my_dice.h my_tile.h my_color.h my_size.h my_thing_ai.h
.o/world_init.o: my_dmap.h
