COMPILER_FLAGS=-Werror -I/opt/local/include/SDL2 -D_THREAD_SAFE -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -Wsign-compare -fno-common -dynamic -DNDEBUG -g -Wall   -arch x86_64 -g  -DVERSION=\"0.0.1\" -g -ggdb3 -O2 # AUTOGEN
    
CLANG_COMPILER_WARNINGS=-Wall -fmessage-length=0 -fdiagnostics-print-source-range-info -fdiagnostics-show-category=id -fdiagnostics-parseable-fixits -Wno-trigraphs -Wmissing-prototypes -Wreturn-type -Wparentheses -Wswitch -Wno-unused-parameter -Wunused-variable -Wunused-value -Wno-sign-conversion -std=c++11 -stdlib=libc++ # AUTOGEN
GXX_COMPILER_WARNINGS=-x c++ -Wall -fmessage-length=0 -Wno-trigraphs -Wreturn-type -Wparentheses -Wswitch -Wno-unused-parameter -Wunused-variable -Wunused-value -std=c++11 -fstack-protector-all -fstack-protector-strong # AUTOGEN
COMPILER_WARNINGS=$(CLANG_COMPILER_WARNINGS) # AUTOGEN
COMPILER_WARNINGS=$(GXX_COMPILER_WARNINGS) # AUTOGEN
# CC=clang++ # AUTOGEN
CC=g++ # AUTOGEN
    
EXE= # AUTOGEN
DSYM=dsymutil ../zorbash # AUTOGEN
LDLIBS=-L/opt/local/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer -L/Library/Frameworks/Python.framework/Versions/3.6/lib/python3.6/config-3.6m-darwin -lpython3.6m -ldl -framework CoreFoundation -funwind-tables -rdynamic -Wl,-framework,Opengl # AUTOGEN
CFLAGS=$(COMPILER_FLAGS) $(COMPILER_WARNINGS) # AUTOGEN

NAME=zorbash
OBJDIR=.o

#include Makefile.ramdisk.deps
#    $(RAMDISK_OBJ)			

GAME_OBJECTS=				\
    $(OBJDIR)/ascii.o 		        \
    $(OBJDIR)/ascii_box.o 		\
    $(OBJDIR)/ascii_button.o 		\
    $(OBJDIR)/backtrace.o 		\
    $(OBJDIR)/color.o			\
    $(OBJDIR)/command.o 		\
    $(OBJDIR)/config.o			\
    $(OBJDIR)/dir.o 			\
    $(OBJDIR)/dmap.o 			\
    $(OBJDIR)/file.o 			\
    $(OBJDIR)/font.o 			\
    $(OBJDIR)/game.o 			\
    $(OBJDIR)/geo.o 			\
    $(OBJDIR)/gl.o 			\
    $(OBJDIR)/hacklib.o 		\
    $(OBJDIR)/log.o 			\
    $(OBJDIR)/main.o 			\
    $(OBJDIR)/math.o 			\
    $(OBJDIR)/music.o 			\
    $(OBJDIR)/pcg_basic.o 		\
    $(OBJDIR)/pixel.o 			\
    $(OBJDIR)/point.o 			\
    $(OBJDIR)/ptrcheck.o 		\
    $(OBJDIR)/py_dmap.o 		\
    $(OBJDIR)/py_game.o 		\
    $(OBJDIR)/py_sdl.o 			\
    $(OBJDIR)/py_tex.o 			\
    $(OBJDIR)/py_thing.o 		\
    $(OBJDIR)/py_tile.o 		\
    $(OBJDIR)/py_tp.o 			\
    $(OBJDIR)/py_ttf.o 			\
    $(OBJDIR)/py_wid.o 			\
    $(OBJDIR)/py_wid_tiles.o 		\
    $(OBJDIR)/python.o 			\
    $(OBJDIR)/ramdisk_read.o 		\
    $(OBJDIR)/rand.o 			\
    $(OBJDIR)/sdl.o 			\
    $(OBJDIR)/slre.o 			\
    $(OBJDIR)/sound.o 			\
    $(OBJDIR)/stb_image.o 		\
    $(OBJDIR)/string.o 			\
    $(OBJDIR)/term.o 		        \
    $(OBJDIR)/tex.o 			\
    $(OBJDIR)/thing.o 			\
    $(OBJDIR)/thing_anim.o 		\
    $(OBJDIR)/thing_dir.o 		\
    $(OBJDIR)/thing_map.o 		\
    $(OBJDIR)/thing_template.o 		\
    $(OBJDIR)/thing_tile.o 		\
    $(OBJDIR)/tile.o 			\
    $(OBJDIR)/time.o 			\
    $(OBJDIR)/timer.o 			\
    $(OBJDIR)/token.o 			\
    $(OBJDIR)/ttf.o 			\
    $(OBJDIR)/util.o 			\
    $(OBJDIR)/wid.o 			\
    $(OBJDIR)/wid_anim.o 		\
    $(OBJDIR)/wid_console.o 		\
    $(OBJDIR)/wid_tiles.o 		\
    $(OBJDIR)/map_jigsaw.o 		\
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

#include Makefile.ramdisk
# DO NOT DELETE

.o/ascii.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/ascii.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii.o: /usr/include/sys/_posix_availability.h
.o/ascii.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/ascii.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/ascii.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ascii.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii.o: /usr/include/sys/_types/_va_list.h
.o/ascii.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/ascii.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ascii.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ascii.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/ascii.o: /usr/include/sys/_types/_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/ascii.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ascii.o: /usr/include/_types/_uint64_t.h
.o/ascii.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ascii.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/ascii.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/ascii.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/ascii.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/ascii.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/ascii.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/ascii.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/ascii.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/ascii.o: /usr/include/mach/i386/_structs.h
.o/ascii.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ascii.o: /usr/include/sys/_types/_sigaltstack.h
.o/ascii.o: /usr/include/sys/_types/_ucontext.h
.o/ascii.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/ascii.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/ascii.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/ascii.o: /usr/include/libkern/_OSByteOrder.h
.o/ascii.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ascii.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/ascii.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii.o: /usr/include/sys/_types/_dev_t.h
.o/ascii.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/ascii.o: my_thing_template.h my_thing.h my_time_util.h
.o/ascii.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ascii.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii.o: /usr/include/sys/_types/_seek_set.h
.o/ascii.o: /usr/include/sys/_types/_gid_t.h
.o/ascii.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/ascii.o: /usr/include/sys/_types/_fd_def.h
.o/ascii.o: /usr/include/sys/_types/_timespec.h
.o/ascii.o: /usr/include/sys/_types/_time_t.h
.o/ascii.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii.o: /usr/include/sys/_types/_fd_set.h
.o/ascii.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ascii.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ascii.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ascii.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/ascii.o: my_game.h my_dmap.h my_tile.h ./my_sdl.h my_tile_private.h
.o/ascii.o: my_glapi.h my_string.h my_enum.h /usr/include/wchar.h
.o/ascii.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/ascii.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/ascii.o: /usr/include/ctype.h /usr/include/runetype.h my_tex.h
.o/ascii.o: my_thing_tile.h my_ttf.h my_font.h my_ascii.h
.o/ascii.o: /usr/include/string.h /usr/include/sys/_types/_rsize_t.h
.o/ascii.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ascii.o: /usr/include/secure/_string.h
.o/ascii_box.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/ascii_box.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii_box.o: /usr/include/sys/_posix_availability.h
.o/ascii_box.o: /usr/include/Availability.h
.o/ascii_box.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ascii_box.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ascii_box.o: /usr/include/i386/_types.h
.o/ascii_box.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii_box.o: /usr/include/sys/_types/_va_list.h
.o/ascii_box.o: /usr/include/sys/_types/_size_t.h
.o/ascii_box.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ascii_box.o: /usr/include/sys/_types/_off_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ssize_t.h
.o/ascii_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ascii_box.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_int64_t.h
.o/ascii_box.o: /usr/include/_types/_uint8_t.h
.o/ascii_box.o: /usr/include/_types/_uint16_t.h
.o/ascii_box.o: /usr/include/_types/_uint32_t.h
.o/ascii_box.o: /usr/include/_types/_uint64_t.h
.o/ascii_box.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii_box.o: /usr/include/_types/_intmax_t.h
.o/ascii_box.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/ascii_box.o: my_pcg_basic.h /usr/include/inttypes.h
.o/ascii_box.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/ascii_box.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/ascii_box.o: /usr/include/math.h /usr/include/stdlib.h
.o/ascii_box.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/ascii_box.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/ascii_box.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/ascii_box.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ascii_box.o: /usr/include/i386/_mcontext.h
.o/ascii_box.o: /usr/include/mach/i386/_structs.h
.o/ascii_box.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_sigaltstack.h
.o/ascii_box.o: /usr/include/sys/_types/_ucontext.h
.o/ascii_box.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii_box.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/ascii_box.o: /usr/include/sys/_types/_timeval.h
.o/ascii_box.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ascii_box.o: /usr/include/sys/_endian.h
.o/ascii_box.o: /usr/include/libkern/_OSByteOrder.h
.o/ascii_box.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/ascii_box.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/ascii_box.o: /usr/include/sys/_types/_rune_t.h
.o/ascii_box.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii_box.o: /usr/include/sys/_types/_dev_t.h
.o/ascii_box.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/ascii_box.o: my_thing_template.h my_thing.h my_time_util.h
.o/ascii_box.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ascii_box.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii_box.o: /usr/include/sys/_types/_seek_set.h
.o/ascii_box.o: /usr/include/sys/_types/_gid_t.h
.o/ascii_box.o: /usr/include/sys/_types/_useconds_t.h
.o/ascii_box.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/ascii_box.o: /usr/include/sys/_types/_timespec.h
.o/ascii_box.o: /usr/include/sys/_types/_time_t.h
.o/ascii_box.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_set.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ascii_box.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ascii_box.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ascii_box.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ascii_box.o: my_sdl.h my_game.h my_dmap.h my_tile.h ./my_sdl.h
.o/ascii_box.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/ascii_box.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/ascii_box.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/ascii_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii_box.o: /usr/include/runetype.h my_thing_tile.h my_ttf.h my_ascii.h
.o/ascii_box.o: my_font.h /usr/include/string.h
.o/ascii_box.o: /usr/include/sys/_types/_rsize_t.h
.o/ascii_box.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ascii_box.o: /usr/include/secure/_string.h
.o/ascii_button.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/ascii_button.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii_button.o: /usr/include/sys/_posix_availability.h
.o/ascii_button.o: /usr/include/Availability.h
.o/ascii_button.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ascii_button.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ascii_button.o: /usr/include/i386/_types.h
.o/ascii_button.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii_button.o: /usr/include/sys/_types/_va_list.h
.o/ascii_button.o: /usr/include/sys/_types/_size_t.h
.o/ascii_button.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ascii_button.o: /usr/include/sys/_types/_off_t.h
.o/ascii_button.o: /usr/include/sys/_types/_ssize_t.h
.o/ascii_button.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ascii_button.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/ascii_button.o: /usr/include/sys/_types/_int16_t.h
.o/ascii_button.o: /usr/include/sys/_types/_int32_t.h
.o/ascii_button.o: /usr/include/sys/_types/_int64_t.h
.o/ascii_button.o: /usr/include/_types/_uint8_t.h
.o/ascii_button.o: /usr/include/_types/_uint16_t.h
.o/ascii_button.o: /usr/include/_types/_uint32_t.h
.o/ascii_button.o: /usr/include/_types/_uint64_t.h
.o/ascii_button.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii_button.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii_button.o: /usr/include/_types/_intmax_t.h
.o/ascii_button.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/ascii_button.o: my_pcg_basic.h /usr/include/inttypes.h
.o/ascii_button.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/ascii_button.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/ascii_button.o: /usr/include/math.h /usr/include/stdlib.h
.o/ascii_button.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/ascii_button.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/ascii_button.o: /usr/include/sys/appleapiopts.h
.o/ascii_button.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/ascii_button.o: /usr/include/machine/_mcontext.h
.o/ascii_button.o: /usr/include/i386/_mcontext.h
.o/ascii_button.o: /usr/include/mach/i386/_structs.h
.o/ascii_button.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ascii_button.o: /usr/include/sys/_types/_sigaltstack.h
.o/ascii_button.o: /usr/include/sys/_types/_ucontext.h
.o/ascii_button.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii_button.o: /usr/include/sys/_types/_uid_t.h
.o/ascii_button.o: /usr/include/sys/resource.h
.o/ascii_button.o: /usr/include/sys/_types/_timeval.h
.o/ascii_button.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ascii_button.o: /usr/include/sys/_endian.h
.o/ascii_button.o: /usr/include/libkern/_OSByteOrder.h
.o/ascii_button.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/ascii_button.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/ascii_button.o: /usr/include/sys/_types/_rune_t.h
.o/ascii_button.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii_button.o: /usr/include/sys/_types/_dev_t.h
.o/ascii_button.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/ascii_button.o: my_thing_template.h my_thing.h my_time_util.h
.o/ascii_button.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ascii_button.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii_button.o: /usr/include/sys/_types/_seek_set.h
.o/ascii_button.o: /usr/include/sys/_types/_gid_t.h
.o/ascii_button.o: /usr/include/sys/_types/_useconds_t.h
.o/ascii_button.o: /usr/include/sys/select.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_def.h
.o/ascii_button.o: /usr/include/sys/_types/_timespec.h
.o/ascii_button.o: /usr/include/sys/_types/_time_t.h
.o/ascii_button.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_set.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_copy.h
.o/ascii_button.o: /usr/include/sys/_select.h
.o/ascii_button.o: /usr/include/sys/_types/_uuid_t.h
.o/ascii_button.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/ascii_button.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/ascii_button.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_game.h
.o/ascii_button.o: my_dmap.h my_tile.h ./my_sdl.h my_tile_private.h
.o/ascii_button.o: my_glapi.h my_string.h my_enum.h /usr/include/wchar.h
.o/ascii_button.o: /usr/include/sys/_types/_mbstate_t.h
.o/ascii_button.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/ascii_button.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii_button.o: /usr/include/runetype.h my_thing_tile.h my_ttf.h
.o/ascii_button.o: my_ascii.h /usr/include/string.h
.o/ascii_button.o: /usr/include/sys/_types/_rsize_t.h
.o/ascii_button.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ascii_button.o: /usr/include/secure/_string.h
.o/backtrace.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/backtrace.o: /usr/include/sys/_symbol_aliasing.h
.o/backtrace.o: /usr/include/sys/_posix_availability.h
.o/backtrace.o: /usr/include/Availability.h
.o/backtrace.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/backtrace.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/backtrace.o: /usr/include/i386/_types.h
.o/backtrace.o: /usr/include/sys/_pthread/_pthread_types.h
.o/backtrace.o: /usr/include/sys/_types/_va_list.h
.o/backtrace.o: /usr/include/sys/_types/_size_t.h
.o/backtrace.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/backtrace.o: /usr/include/sys/_types/_off_t.h
.o/backtrace.o: /usr/include/sys/_types/_ssize_t.h
.o/backtrace.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/backtrace.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/backtrace.o: /usr/include/sys/_types/_int16_t.h
.o/backtrace.o: /usr/include/sys/_types/_int32_t.h
.o/backtrace.o: /usr/include/sys/_types/_int64_t.h
.o/backtrace.o: /usr/include/_types/_uint8_t.h
.o/backtrace.o: /usr/include/_types/_uint16_t.h
.o/backtrace.o: /usr/include/_types/_uint32_t.h
.o/backtrace.o: /usr/include/_types/_uint64_t.h
.o/backtrace.o: /usr/include/sys/_types/_intptr_t.h
.o/backtrace.o: /usr/include/sys/_types/_uintptr_t.h
.o/backtrace.o: /usr/include/_types/_intmax_t.h
.o/backtrace.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/backtrace.o: my_pcg_basic.h /usr/include/inttypes.h
.o/backtrace.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/backtrace.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/backtrace.o: /usr/include/math.h /usr/include/stdlib.h
.o/backtrace.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/backtrace.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/backtrace.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/backtrace.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/backtrace.o: /usr/include/i386/_mcontext.h
.o/backtrace.o: /usr/include/mach/i386/_structs.h
.o/backtrace.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/backtrace.o: /usr/include/sys/_types/_sigaltstack.h
.o/backtrace.o: /usr/include/sys/_types/_ucontext.h
.o/backtrace.o: /usr/include/sys/_types/_sigset_t.h
.o/backtrace.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/backtrace.o: /usr/include/sys/_types/_timeval.h
.o/backtrace.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/backtrace.o: /usr/include/sys/_endian.h
.o/backtrace.o: /usr/include/libkern/_OSByteOrder.h
.o/backtrace.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/backtrace.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/backtrace.o: /usr/include/sys/_types/_rune_t.h
.o/backtrace.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/backtrace.o: /usr/include/sys/_types/_u_int8_t.h
.o/backtrace.o: /usr/include/sys/_types/_u_int16_t.h
.o/backtrace.o: /usr/include/sys/_types/_u_int32_t.h
.o/backtrace.o: /usr/include/sys/_types/_u_int64_t.h
.o/backtrace.o: /usr/include/sys/_types/_dev_t.h
.o/backtrace.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/backtrace.o: my_thing_template.h my_thing.h my_time_util.h
.o/backtrace.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/backtrace.o: /usr/include/sys/_types/_posix_vdisable.h
.o/backtrace.o: /usr/include/sys/_types/_seek_set.h
.o/backtrace.o: /usr/include/sys/_types/_gid_t.h
.o/backtrace.o: /usr/include/sys/_types/_useconds_t.h
.o/backtrace.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/backtrace.o: /usr/include/sys/_types/_timespec.h
.o/backtrace.o: /usr/include/sys/_types/_time_t.h
.o/backtrace.o: /usr/include/sys/_types/_suseconds_t.h
.o/backtrace.o: /usr/include/sys/_types/_fd_setsize.h
.o/backtrace.o: /usr/include/sys/_types/_fd_set.h
.o/backtrace.o: /usr/include/sys/_types/_fd_clr.h
.o/backtrace.o: /usr/include/sys/_types/_fd_isset.h
.o/backtrace.o: /usr/include/sys/_types/_fd_zero.h
.o/backtrace.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/backtrace.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/backtrace.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/backtrace.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/backtrace.o: my_sdl.h my_game.h my_dmap.h my_backtrace.h
.o/backtrace.o: /usr/include/execinfo.h /usr/include/cxxabi.h
.o/backtrace.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/backtrace.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/backtrace.o: /usr/include/sys/_types/_rsize_t.h
.o/backtrace.o: /usr/include/sys/_types/_wint_t.h
.o/backtrace.o: /usr/include/__cxxabi_config.h
.o/color.o: my_glapi.h /usr/include/stdlib.h /usr/include/Availability.h
.o/color.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/color.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/color.o: /usr/include/sys/_symbol_aliasing.h
.o/color.o: /usr/include/sys/_posix_availability.h
.o/color.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/color.o: /usr/include/sys/_pthread/_pthread_types.h
.o/color.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/color.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/color.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/color.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/color.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/color.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/color.o: /usr/include/sys/_types/_sigaltstack.h
.o/color.o: /usr/include/sys/_types/_ucontext.h
.o/color.o: /usr/include/sys/_types/_sigset_t.h
.o/color.o: /usr/include/sys/_types/_size_t.h
.o/color.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/color.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/color.o: /usr/include/sys/_types/_int16_t.h
.o/color.o: /usr/include/sys/_types/_int32_t.h
.o/color.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/color.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/color.o: /usr/include/_types/_uint64_t.h
.o/color.o: /usr/include/sys/_types/_intptr_t.h
.o/color.o: /usr/include/sys/_types/_uintptr_t.h
.o/color.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/color.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/color.o: /usr/include/libkern/_OSByteOrder.h
.o/color.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/color.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color.o: /usr/include/sys/_types/_rune_t.h
.o/color.o: /usr/include/sys/_types/_wchar_t.h
.o/color.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
.o/color.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/color.o: /usr/include/sys/_types/_u_int16_t.h
.o/color.o: /usr/include/sys/_types/_u_int32_t.h
.o/color.o: /usr/include/sys/_types/_u_int64_t.h
.o/color.o: /usr/include/sys/_types/_dev_t.h
.o/color.o: /usr/include/sys/_types/_mode_t.h my_main.h /usr/include/stdio.h
.o/color.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/color.o: /usr/include/sys/_types/_off_t.h
.o/color.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/color.o: /usr/include/secure/_common.h /usr/include/assert.h
.o/color.o: my_pcg_basic.h /usr/include/inttypes.h my_config.h my_color.h
.o/color.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/color.o: my_point.h my_size.h my_thing_template.h my_thing.h
.o/color.o: my_time_util.h /usr/include/unistd.h /usr/include/sys/unistd.h
.o/color.o: /usr/include/sys/_types/_posix_vdisable.h
.o/color.o: /usr/include/sys/_types/_seek_set.h
.o/color.o: /usr/include/sys/_types/_gid_t.h
.o/color.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/color.o: /usr/include/sys/_types/_fd_def.h
.o/color.o: /usr/include/sys/_types/_timespec.h
.o/color.o: /usr/include/sys/_types/_time_t.h
.o/color.o: /usr/include/sys/_types/_suseconds_t.h
.o/color.o: /usr/include/sys/_types/_fd_setsize.h
.o/color.o: /usr/include/sys/_types/_fd_set.h
.o/color.o: /usr/include/sys/_types/_fd_clr.h
.o/color.o: /usr/include/sys/_types/_fd_isset.h
.o/color.o: /usr/include/sys/_types/_fd_zero.h
.o/color.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/color.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/color.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/color.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/color.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/color.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/color.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/color.o: /usr/include/ctype.h /usr/include/runetype.h
.o/command.o: /usr/include/fcntl.h /usr/include/sys/fcntl.h
.o/command.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/command.o: /usr/include/sys/_symbol_aliasing.h
.o/command.o: /usr/include/sys/_posix_availability.h
.o/command.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/command.o: /usr/include/sys/_pthread/_pthread_types.h
.o/command.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/command.o: /usr/include/sys/_types/_size_t.h
.o/command.o: /usr/include/sys/_types/_mode_t.h
.o/command.o: /usr/include/sys/_types/_off_t.h
.o/command.o: /usr/include/sys/_types/_pid_t.h
.o/command.o: /usr/include/sys/_types/_o_sync.h
.o/command.o: /usr/include/sys/_types/_o_dsync.h
.o/command.o: /usr/include/sys/_types/_seek_set.h
.o/command.o: /usr/include/sys/_types/_s_ifmt.h
.o/command.o: /usr/include/sys/_types/_timespec.h
.o/command.o: /usr/include/sys/_types/_filesec_t.h my_slre.h
.o/command.o: /usr/include/stdlib.h /usr/include/_types.h
.o/command.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/command.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/command.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/command.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/command.o: /usr/include/mach/i386/_structs.h
.o/command.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/command.o: /usr/include/sys/_types/_sigaltstack.h
.o/command.o: /usr/include/sys/_types/_ucontext.h
.o/command.o: /usr/include/sys/_types/_sigset_t.h
.o/command.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/command.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/command.o: /usr/include/sys/_types/_int16_t.h
.o/command.o: /usr/include/sys/_types/_int32_t.h
.o/command.o: /usr/include/sys/_types/_int64_t.h
.o/command.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/command.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/command.o: /usr/include/sys/_types/_intptr_t.h
.o/command.o: /usr/include/sys/_types/_uintptr_t.h
.o/command.o: /usr/include/_types/_intmax_t.h
.o/command.o: /usr/include/_types/_uintmax_t.h
.o/command.o: /usr/include/sys/_types/_timeval.h
.o/command.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/command.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/command.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/command.o: /usr/include/sys/_types/_ct_rune_t.h
.o/command.o: /usr/include/sys/_types/_rune_t.h
.o/command.o: /usr/include/sys/_types/_wchar_t.h
.o/command.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
.o/command.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/command.o: /usr/include/sys/_types/_u_int16_t.h
.o/command.o: /usr/include/sys/_types/_u_int32_t.h
.o/command.o: /usr/include/sys/_types/_u_int64_t.h
.o/command.o: /usr/include/sys/_types/_dev_t.h my_main.h /usr/include/stdio.h
.o/command.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/command.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/command.o: /usr/include/secure/_common.h /usr/include/assert.h
.o/command.o: my_pcg_basic.h /usr/include/inttypes.h my_config.h my_color.h
.o/command.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/command.o: my_point.h my_size.h my_thing_template.h my_thing.h
.o/command.o: my_time_util.h /usr/include/unistd.h /usr/include/sys/unistd.h
.o/command.o: /usr/include/sys/_types/_posix_vdisable.h
.o/command.o: /usr/include/sys/_types/_gid_t.h
.o/command.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/command.o: /usr/include/sys/_types/_fd_def.h
.o/command.o: /usr/include/sys/_types/_time_t.h
.o/command.o: /usr/include/sys/_types/_suseconds_t.h
.o/command.o: /usr/include/sys/_types/_fd_setsize.h
.o/command.o: /usr/include/sys/_types/_fd_set.h
.o/command.o: /usr/include/sys/_types/_fd_clr.h
.o/command.o: /usr/include/sys/_types/_fd_isset.h
.o/command.o: /usr/include/sys/_types/_fd_zero.h
.o/command.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/command.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/command.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/command.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/command.o: my_game.h my_dmap.h my_command.h my_token.h my_string.h
.o/command.o: my_enum.h /usr/include/wchar.h
.o/command.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/command.o: /usr/include/sys/_types/_wint_t.h
.o/command.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/command.o: /usr/include/runetype.h my_wid.h my_timer.h my_python.h
.o/config.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/config.o: /usr/include/sys/_symbol_aliasing.h
.o/config.o: /usr/include/sys/_posix_availability.h
.o/config.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/config.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/config.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/config.o: /usr/include/sys/_pthread/_pthread_types.h
.o/config.o: /usr/include/sys/_types/_va_list.h
.o/config.o: /usr/include/sys/_types/_size_t.h
.o/config.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/config.o: /usr/include/sys/_types/_off_t.h
.o/config.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/config.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/config.o: /usr/include/sys/_types/_int8_t.h
.o/config.o: /usr/include/sys/_types/_int16_t.h
.o/config.o: /usr/include/sys/_types/_int32_t.h
.o/config.o: /usr/include/sys/_types/_int64_t.h
.o/config.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/config.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/config.o: /usr/include/sys/_types/_intptr_t.h
.o/config.o: /usr/include/sys/_types/_uintptr_t.h
.o/config.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/config.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/config.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/config.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/config.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/config.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/config.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/config.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/config.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/config.o: /usr/include/mach/i386/_structs.h
.o/config.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/config.o: /usr/include/sys/_types/_sigaltstack.h
.o/config.o: /usr/include/sys/_types/_ucontext.h
.o/config.o: /usr/include/sys/_types/_sigset_t.h
.o/config.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/config.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/config.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/config.o: /usr/include/libkern/_OSByteOrder.h
.o/config.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/config.o: /usr/include/sys/_types/_ct_rune_t.h
.o/config.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/config.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/config.o: /usr/include/sys/_types/_u_int16_t.h
.o/config.o: /usr/include/sys/_types/_u_int32_t.h
.o/config.o: /usr/include/sys/_types/_u_int64_t.h
.o/config.o: /usr/include/sys/_types/_dev_t.h
.o/config.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/config.o: my_thing_template.h my_thing.h my_time_util.h
.o/config.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/config.o: /usr/include/sys/_types/_posix_vdisable.h
.o/config.o: /usr/include/sys/_types/_seek_set.h
.o/config.o: /usr/include/sys/_types/_gid_t.h
.o/config.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/config.o: /usr/include/sys/_types/_fd_def.h
.o/config.o: /usr/include/sys/_types/_timespec.h
.o/config.o: /usr/include/sys/_types/_time_t.h
.o/config.o: /usr/include/sys/_types/_suseconds_t.h
.o/config.o: /usr/include/sys/_types/_fd_setsize.h
.o/config.o: /usr/include/sys/_types/_fd_set.h
.o/config.o: /usr/include/sys/_types/_fd_clr.h
.o/config.o: /usr/include/sys/_types/_fd_isset.h
.o/config.o: /usr/include/sys/_types/_fd_zero.h
.o/config.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/config.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/config.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/config.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/config.o: my_game.h my_dmap.h my_python.h
.o/dir.o: /usr/include/dirent.h /usr/include/_types.h
.o/dir.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/dir.o: /usr/include/sys/_symbol_aliasing.h
.o/dir.o: /usr/include/sys/_posix_availability.h
.o/dir.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dir.o: /usr/include/sys/dirent.h /usr/include/sys/_types/_ino_t.h
.o/dir.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/dir.o: /usr/include/sys/param.h /usr/include/sys/_types/_null.h
.o/dir.o: /usr/include/sys/types.h /usr/include/sys/appleapiopts.h
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
.o/dir.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/machine/endian.h
.o/dir.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/dir.o: /usr/include/libkern/_OSByteOrder.h
.o/dir.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/dir.o: /usr/include/sys/_types/_dev_t.h
.o/dir.o: /usr/include/sys/_types/_blkcnt_t.h
.o/dir.o: /usr/include/sys/_types/_blksize_t.h
.o/dir.o: /usr/include/sys/_types/_gid_t.h
.o/dir.o: /usr/include/sys/_types/_in_addr_t.h
.o/dir.o: /usr/include/sys/_types/_in_port_t.h
.o/dir.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
.o/dir.o: /usr/include/sys/_types/_mode_t.h
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
.o/dir.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/dir.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/dir.o: /usr/include/mach/i386/_structs.h
.o/dir.o: /usr/include/sys/_types/_sigaltstack.h
.o/dir.o: /usr/include/sys/_types/_ucontext.h
.o/dir.o: /usr/include/sys/_types/_sigset_t.h my_main.h /usr/include/stdio.h
.o/dir.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/dir.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/dir.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/dir.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dir.o: /usr/include/_types/_uint64_t.h /usr/include/_types/_intmax_t.h
.o/dir.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/dir.o: my_pcg_basic.h /usr/include/inttypes.h
.o/dir.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/dir.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/dir.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/dir.o: /usr/include/sys/resource.h /usr/include/sys/_types/_timeval.h
.o/dir.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/dir.o: /usr/include/sys/_types/_rune_t.h my_point.h my_size.h
.o/dir.o: my_thing_template.h my_thing.h my_time_util.h /usr/include/unistd.h
.o/dir.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/dir.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/select.h
.o/dir.o: /usr/include/sys/_types/_timespec.h /usr/include/sys/_select.h
.o/dir.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/dir.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/dir.o: /usr/include/time.h my_sdl.h my_game.h my_dmap.h my_dir.h
.o/dir.o: my_string.h my_enum.h /usr/include/wchar.h
.o/dir.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/dir.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/dir.o: /usr/include/ctype.h /usr/include/runetype.h my_ramdisk.h
.o/dmap.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/dmap.o: /usr/include/sys/_symbol_aliasing.h
.o/dmap.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/dmap.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/dmap.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/dmap.o: /usr/include/i386/_types.h
.o/dmap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dmap.o: /usr/include/sys/_types/_va_list.h
.o/dmap.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/dmap.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/dmap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dmap.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/dmap.o: /usr/include/sys/_types/_int8_t.h
.o/dmap.o: /usr/include/sys/_types/_int16_t.h
.o/dmap.o: /usr/include/sys/_types/_int32_t.h
.o/dmap.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/dmap.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dmap.o: /usr/include/_types/_uint64_t.h
.o/dmap.o: /usr/include/sys/_types/_intptr_t.h
.o/dmap.o: /usr/include/sys/_types/_uintptr_t.h
.o/dmap.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dmap.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/dmap.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/dmap.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/dmap.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/dmap.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/dmap.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/dmap.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/dmap.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/dmap.o: /usr/include/mach/i386/_structs.h
.o/dmap.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/dmap.o: /usr/include/sys/_types/_sigaltstack.h
.o/dmap.o: /usr/include/sys/_types/_ucontext.h
.o/dmap.o: /usr/include/sys/_types/_sigset_t.h
.o/dmap.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/dmap.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/dmap.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/dmap.o: /usr/include/libkern/_OSByteOrder.h
.o/dmap.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/dmap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dmap.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/dmap.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/dmap.o: /usr/include/sys/_types/_u_int16_t.h
.o/dmap.o: /usr/include/sys/_types/_u_int32_t.h
.o/dmap.o: /usr/include/sys/_types/_u_int64_t.h
.o/dmap.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/dmap.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/dmap.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/dmap.o: /usr/include/sys/_types/_posix_vdisable.h
.o/dmap.o: /usr/include/sys/_types/_seek_set.h
.o/dmap.o: /usr/include/sys/_types/_gid_t.h
.o/dmap.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/dmap.o: /usr/include/sys/_types/_fd_def.h
.o/dmap.o: /usr/include/sys/_types/_timespec.h
.o/dmap.o: /usr/include/sys/_types/_time_t.h
.o/dmap.o: /usr/include/sys/_types/_suseconds_t.h
.o/dmap.o: /usr/include/sys/_types/_fd_setsize.h
.o/dmap.o: /usr/include/sys/_types/_fd_set.h
.o/dmap.o: /usr/include/sys/_types/_fd_clr.h
.o/dmap.o: /usr/include/sys/_types/_fd_isset.h
.o/dmap.o: /usr/include/sys/_types/_fd_zero.h
.o/dmap.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/dmap.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/dmap.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/dmap.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/dmap.o: my_game.h my_dmap.h
.o/file.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/file.o: /usr/include/sys/_symbol_aliasing.h
.o/file.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/file.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/file.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/file.o: /usr/include/i386/_types.h
.o/file.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file.o: /usr/include/sys/_types/_va_list.h
.o/file.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/file.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/file.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/file.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/file.o: /usr/include/sys/_types/_int8_t.h
.o/file.o: /usr/include/sys/_types/_int16_t.h
.o/file.o: /usr/include/sys/_types/_int32_t.h
.o/file.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/file.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/file.o: /usr/include/_types/_uint64_t.h
.o/file.o: /usr/include/sys/_types/_intptr_t.h
.o/file.o: /usr/include/sys/_types/_uintptr_t.h
.o/file.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/file.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/file.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/file.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/file.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/file.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/file.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/file.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/file.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/file.o: /usr/include/mach/i386/_structs.h
.o/file.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/file.o: /usr/include/sys/_types/_sigaltstack.h
.o/file.o: /usr/include/sys/_types/_ucontext.h
.o/file.o: /usr/include/sys/_types/_sigset_t.h
.o/file.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/file.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/file.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/file.o: /usr/include/libkern/_OSByteOrder.h
.o/file.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/file.o: /usr/include/sys/_types/_ct_rune_t.h
.o/file.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/file.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/file.o: /usr/include/sys/_types/_u_int16_t.h
.o/file.o: /usr/include/sys/_types/_u_int32_t.h
.o/file.o: /usr/include/sys/_types/_u_int64_t.h
.o/file.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/file.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/file.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/file.o: /usr/include/sys/_types/_posix_vdisable.h
.o/file.o: /usr/include/sys/_types/_seek_set.h
.o/file.o: /usr/include/sys/_types/_gid_t.h
.o/file.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/file.o: /usr/include/sys/_types/_fd_def.h
.o/file.o: /usr/include/sys/_types/_timespec.h
.o/file.o: /usr/include/sys/_types/_time_t.h
.o/file.o: /usr/include/sys/_types/_suseconds_t.h
.o/file.o: /usr/include/sys/_types/_fd_setsize.h
.o/file.o: /usr/include/sys/_types/_fd_set.h
.o/file.o: /usr/include/sys/_types/_fd_clr.h
.o/file.o: /usr/include/sys/_types/_fd_isset.h
.o/file.o: /usr/include/sys/_types/_fd_zero.h
.o/file.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/file.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/file.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/file.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/file.o: my_game.h my_dmap.h my_file.h
.o/font.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/font.o: /usr/include/sys/_symbol_aliasing.h
.o/font.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/font.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/font.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/font.o: /usr/include/i386/_types.h
.o/font.o: /usr/include/sys/_pthread/_pthread_types.h
.o/font.o: /usr/include/sys/_types/_va_list.h
.o/font.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/font.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/font.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/font.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/font.o: /usr/include/sys/_types/_int8_t.h
.o/font.o: /usr/include/sys/_types/_int16_t.h
.o/font.o: /usr/include/sys/_types/_int32_t.h
.o/font.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/font.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/font.o: /usr/include/_types/_uint64_t.h
.o/font.o: /usr/include/sys/_types/_intptr_t.h
.o/font.o: /usr/include/sys/_types/_uintptr_t.h
.o/font.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/font.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/font.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/font.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/font.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/font.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/font.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/font.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/font.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/font.o: /usr/include/mach/i386/_structs.h
.o/font.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/font.o: /usr/include/sys/_types/_sigaltstack.h
.o/font.o: /usr/include/sys/_types/_ucontext.h
.o/font.o: /usr/include/sys/_types/_sigset_t.h
.o/font.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/font.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/font.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/font.o: /usr/include/libkern/_OSByteOrder.h
.o/font.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/font.o: /usr/include/sys/_types/_ct_rune_t.h
.o/font.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/font.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/font.o: /usr/include/sys/_types/_u_int16_t.h
.o/font.o: /usr/include/sys/_types/_u_int32_t.h
.o/font.o: /usr/include/sys/_types/_u_int64_t.h
.o/font.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/font.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/font.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/font.o: /usr/include/sys/_types/_posix_vdisable.h
.o/font.o: /usr/include/sys/_types/_seek_set.h
.o/font.o: /usr/include/sys/_types/_gid_t.h
.o/font.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/font.o: /usr/include/sys/_types/_fd_def.h
.o/font.o: /usr/include/sys/_types/_timespec.h
.o/font.o: /usr/include/sys/_types/_time_t.h
.o/font.o: /usr/include/sys/_types/_suseconds_t.h
.o/font.o: /usr/include/sys/_types/_fd_setsize.h
.o/font.o: /usr/include/sys/_types/_fd_set.h
.o/font.o: /usr/include/sys/_types/_fd_clr.h
.o/font.o: /usr/include/sys/_types/_fd_isset.h
.o/font.o: /usr/include/sys/_types/_fd_zero.h
.o/font.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/font.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/font.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/font.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/font.o: my_game.h my_dmap.h my_ttf.h my_enum.h my_font.h my_tile.h
.o/font.o: ./my_sdl.h my_tile_private.h my_glapi.h my_string.h
.o/font.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/font.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/font.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/font.o: /usr/include/runetype.h
.o/game.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/game.o: /usr/include/sys/_symbol_aliasing.h
.o/game.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/game.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/game.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/game.o: /usr/include/i386/_types.h
.o/game.o: /usr/include/sys/_pthread/_pthread_types.h
.o/game.o: /usr/include/sys/_types/_va_list.h
.o/game.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/game.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/game.o: /usr/include/sys/_types/_int8_t.h
.o/game.o: /usr/include/sys/_types/_int16_t.h
.o/game.o: /usr/include/sys/_types/_int32_t.h
.o/game.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/game.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/game.o: /usr/include/_types/_uint64_t.h
.o/game.o: /usr/include/sys/_types/_intptr_t.h
.o/game.o: /usr/include/sys/_types/_uintptr_t.h
.o/game.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/game.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/game.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/game.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/game.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/game.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/game.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/game.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/game.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/game.o: /usr/include/mach/i386/_structs.h
.o/game.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/game.o: /usr/include/sys/_types/_sigaltstack.h
.o/game.o: /usr/include/sys/_types/_ucontext.h
.o/game.o: /usr/include/sys/_types/_sigset_t.h
.o/game.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/game.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/game.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/game.o: /usr/include/libkern/_OSByteOrder.h
.o/game.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/game.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/game.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/game.o: /usr/include/sys/_types/_u_int16_t.h
.o/game.o: /usr/include/sys/_types/_u_int32_t.h
.o/game.o: /usr/include/sys/_types/_u_int64_t.h
.o/game.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/game.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/game.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/game.o: /usr/include/sys/_types/_posix_vdisable.h
.o/game.o: /usr/include/sys/_types/_seek_set.h
.o/game.o: /usr/include/sys/_types/_gid_t.h
.o/game.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/game.o: /usr/include/sys/_types/_fd_def.h
.o/game.o: /usr/include/sys/_types/_timespec.h
.o/game.o: /usr/include/sys/_types/_time_t.h
.o/game.o: /usr/include/sys/_types/_suseconds_t.h
.o/game.o: /usr/include/sys/_types/_fd_setsize.h
.o/game.o: /usr/include/sys/_types/_fd_set.h
.o/game.o: /usr/include/sys/_types/_fd_clr.h
.o/game.o: /usr/include/sys/_types/_fd_isset.h
.o/game.o: /usr/include/sys/_types/_fd_zero.h
.o/game.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/game.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/game.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/game.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/game.o: my_game.h my_dmap.h my_glapi.h my_string.h my_enum.h
.o/game.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/game.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/game.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/game.o: /usr/include/runetype.h my_tile.h ./my_sdl.h my_tile_private.h
.o/game.o: my_python.h my_ascii.h
.o/geo.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/geo.o: /usr/include/sys/_symbol_aliasing.h
.o/geo.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/geo.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/geo.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/geo.o: /usr/include/i386/_types.h
.o/geo.o: /usr/include/sys/_pthread/_pthread_types.h
.o/geo.o: /usr/include/sys/_types/_va_list.h
.o/geo.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/geo.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/geo.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/geo.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/geo.o: /usr/include/sys/_types/_int8_t.h
.o/geo.o: /usr/include/sys/_types/_int16_t.h
.o/geo.o: /usr/include/sys/_types/_int32_t.h
.o/geo.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/geo.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/geo.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/geo.o: /usr/include/sys/_types/_uintptr_t.h
.o/geo.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/geo.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/geo.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/geo.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/geo.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/geo.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/geo.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/geo.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/geo.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/geo.o: /usr/include/mach/i386/_structs.h
.o/geo.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/geo.o: /usr/include/sys/_types/_sigaltstack.h
.o/geo.o: /usr/include/sys/_types/_ucontext.h
.o/geo.o: /usr/include/sys/_types/_sigset_t.h
.o/geo.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/geo.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/geo.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/geo.o: /usr/include/libkern/_OSByteOrder.h
.o/geo.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/geo.o: /usr/include/sys/_types/_ct_rune_t.h
.o/geo.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/geo.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/geo.o: /usr/include/sys/_types/_u_int16_t.h
.o/geo.o: /usr/include/sys/_types/_u_int32_t.h
.o/geo.o: /usr/include/sys/_types/_u_int64_t.h
.o/geo.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/geo.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/geo.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/geo.o: /usr/include/sys/_types/_posix_vdisable.h
.o/geo.o: /usr/include/sys/_types/_seek_set.h
.o/geo.o: /usr/include/sys/_types/_gid_t.h
.o/geo.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/geo.o: /usr/include/sys/_types/_fd_def.h
.o/geo.o: /usr/include/sys/_types/_timespec.h
.o/geo.o: /usr/include/sys/_types/_time_t.h
.o/geo.o: /usr/include/sys/_types/_suseconds_t.h
.o/geo.o: /usr/include/sys/_types/_fd_setsize.h
.o/geo.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/geo.o: /usr/include/sys/_types/_fd_isset.h
.o/geo.o: /usr/include/sys/_types/_fd_zero.h
.o/geo.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/geo.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/geo.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/geo.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/geo.o: my_game.h my_dmap.h my_geo.h
.o/gl.o: my_glapi.h /usr/include/stdlib.h /usr/include/Availability.h
.o/gl.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/gl.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/gl.o: /usr/include/sys/_symbol_aliasing.h
.o/gl.o: /usr/include/sys/_posix_availability.h /usr/include/machine/_types.h
.o/gl.o: /usr/include/i386/_types.h
.o/gl.o: /usr/include/sys/_pthread/_pthread_types.h /usr/include/sys/wait.h
.o/gl.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/gl.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/gl.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/gl.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/gl.o: /usr/include/mach/i386/_structs.h
.o/gl.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/gl.o: /usr/include/sys/_types/_sigaltstack.h
.o/gl.o: /usr/include/sys/_types/_ucontext.h
.o/gl.o: /usr/include/sys/_types/_sigset_t.h
.o/gl.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
.o/gl.o: /usr/include/sys/resource.h /usr/include/stdint.h
.o/gl.o: /usr/include/sys/_types/_int8_t.h /usr/include/sys/_types/_int16_t.h
.o/gl.o: /usr/include/sys/_types/_int32_t.h
.o/gl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/gl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/gl.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/gl.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
.o/gl.o: /usr/include/_types/_uintmax_t.h /usr/include/sys/_types/_timeval.h
.o/gl.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/gl.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/gl.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/gl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gl.o: /usr/include/sys/_types/_rune_t.h /usr/include/sys/_types/_wchar_t.h
.o/gl.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
.o/gl.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/gl.o: /usr/include/sys/_types/_u_int16_t.h
.o/gl.o: /usr/include/sys/_types/_u_int32_t.h
.o/gl.o: /usr/include/sys/_types/_u_int64_t.h
.o/gl.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/gl.o: my_main.h /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/gl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/gl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/gl.o: /usr/include/secure/_common.h /usr/include/assert.h my_pcg_basic.h
.o/gl.o: /usr/include/inttypes.h my_config.h my_color.h my_callstack.h
.o/gl.o: my_ptrcheck.h my_math_util.h /usr/include/math.h my_point.h
.o/gl.o: my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/gl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/gl.o: /usr/include/sys/_types/_posix_vdisable.h
.o/gl.o: /usr/include/sys/_types/_seek_set.h /usr/include/sys/_types/_gid_t.h
.o/gl.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/gl.o: /usr/include/sys/_types/_fd_def.h
.o/gl.o: /usr/include/sys/_types/_timespec.h
.o/gl.o: /usr/include/sys/_types/_time_t.h
.o/gl.o: /usr/include/sys/_types/_suseconds_t.h
.o/gl.o: /usr/include/sys/_types/_fd_setsize.h
.o/gl.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/gl.o: /usr/include/sys/_types/_fd_isset.h
.o/gl.o: /usr/include/sys/_types/_fd_zero.h
.o/gl.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/gl.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/gl.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/gl.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/gl.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/gl.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/gl.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/gl.o: /usr/include/ctype.h /usr/include/runetype.h
.o/hacklib.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/hacklib.o: /usr/include/sys/_symbol_aliasing.h
.o/hacklib.o: /usr/include/sys/_posix_availability.h
.o/hacklib.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/hacklib.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/hacklib.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/hacklib.o: /usr/include/sys/_pthread/_pthread_types.h
.o/hacklib.o: /usr/include/sys/_types/_va_list.h
.o/hacklib.o: /usr/include/sys/_types/_size_t.h
.o/hacklib.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/hacklib.o: /usr/include/sys/_types/_off_t.h
.o/hacklib.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/hacklib.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/hacklib.o: /usr/include/sys/_types/_int8_t.h
.o/hacklib.o: /usr/include/sys/_types/_int16_t.h
.o/hacklib.o: /usr/include/sys/_types/_int32_t.h
.o/hacklib.o: /usr/include/sys/_types/_int64_t.h
.o/hacklib.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/hacklib.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/hacklib.o: /usr/include/sys/_types/_intptr_t.h
.o/hacklib.o: /usr/include/sys/_types/_uintptr_t.h
.o/hacklib.o: /usr/include/_types/_intmax_t.h
.o/hacklib.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/hacklib.o: my_pcg_basic.h /usr/include/inttypes.h
.o/hacklib.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/hacklib.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/hacklib.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/hacklib.o: /usr/include/sys/_types/_pid_t.h
.o/hacklib.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/hacklib.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/hacklib.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/hacklib.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/hacklib.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/hacklib.o: /usr/include/sys/_types/_sigaltstack.h
.o/hacklib.o: /usr/include/sys/_types/_ucontext.h
.o/hacklib.o: /usr/include/sys/_types/_sigset_t.h
.o/hacklib.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/hacklib.o: /usr/include/sys/_types/_timeval.h
.o/hacklib.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/hacklib.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/hacklib.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/hacklib.o: /usr/include/sys/_types/_ct_rune_t.h
.o/hacklib.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/hacklib.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/hacklib.o: /usr/include/sys/_types/_u_int16_t.h
.o/hacklib.o: /usr/include/sys/_types/_u_int32_t.h
.o/hacklib.o: /usr/include/sys/_types/_u_int64_t.h
.o/hacklib.o: /usr/include/sys/_types/_dev_t.h
.o/hacklib.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/hacklib.o: my_thing_template.h my_thing.h my_time_util.h
.o/hacklib.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/hacklib.o: /usr/include/sys/_types/_posix_vdisable.h
.o/hacklib.o: /usr/include/sys/_types/_seek_set.h
.o/hacklib.o: /usr/include/sys/_types/_gid_t.h
.o/hacklib.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/hacklib.o: /usr/include/sys/_types/_fd_def.h
.o/hacklib.o: /usr/include/sys/_types/_timespec.h
.o/hacklib.o: /usr/include/sys/_types/_time_t.h
.o/hacklib.o: /usr/include/sys/_types/_suseconds_t.h
.o/hacklib.o: /usr/include/sys/_types/_fd_setsize.h
.o/hacklib.o: /usr/include/sys/_types/_fd_set.h
.o/hacklib.o: /usr/include/sys/_types/_fd_clr.h
.o/hacklib.o: /usr/include/sys/_types/_fd_isset.h
.o/hacklib.o: /usr/include/sys/_types/_fd_zero.h
.o/hacklib.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/hacklib.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/hacklib.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/hacklib.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/hacklib.o: my_game.h my_dmap.h my_hacklib.h
.o/log.o: my_slre.h my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/log.o: /usr/include/sys/_symbol_aliasing.h
.o/log.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/log.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/log.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/log.o: /usr/include/i386/_types.h
.o/log.o: /usr/include/sys/_pthread/_pthread_types.h
.o/log.o: /usr/include/sys/_types/_va_list.h
.o/log.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/log.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/log.o: /usr/include/sys/_types/_int8_t.h
.o/log.o: /usr/include/sys/_types/_int16_t.h
.o/log.o: /usr/include/sys/_types/_int32_t.h
.o/log.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/log.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/log.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/log.o: /usr/include/sys/_types/_uintptr_t.h
.o/log.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/log.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/log.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/log.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/log.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/log.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/log.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/log.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/log.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/log.o: /usr/include/mach/i386/_structs.h
.o/log.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/log.o: /usr/include/sys/_types/_sigaltstack.h
.o/log.o: /usr/include/sys/_types/_ucontext.h
.o/log.o: /usr/include/sys/_types/_sigset_t.h
.o/log.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/log.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/log.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/log.o: /usr/include/libkern/_OSByteOrder.h
.o/log.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/log.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/log.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/log.o: /usr/include/sys/_types/_u_int16_t.h
.o/log.o: /usr/include/sys/_types/_u_int32_t.h
.o/log.o: /usr/include/sys/_types/_u_int64_t.h
.o/log.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/log.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/log.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/log.o: /usr/include/sys/_types/_posix_vdisable.h
.o/log.o: /usr/include/sys/_types/_seek_set.h
.o/log.o: /usr/include/sys/_types/_gid_t.h
.o/log.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/log.o: /usr/include/sys/_types/_fd_def.h
.o/log.o: /usr/include/sys/_types/_timespec.h
.o/log.o: /usr/include/sys/_types/_time_t.h
.o/log.o: /usr/include/sys/_types/_suseconds_t.h
.o/log.o: /usr/include/sys/_types/_fd_setsize.h
.o/log.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/log.o: /usr/include/sys/_types/_fd_isset.h
.o/log.o: /usr/include/sys/_types/_fd_zero.h
.o/log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/log.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/log.o: my_game.h my_dmap.h my_backtrace.h /usr/include/execinfo.h
.o/log.o: /usr/include/cxxabi.h /usr/include/stddef.h
.o/log.o: /usr/include/sys/_types/_offsetof.h
.o/log.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/log.o: /usr/include/sys/_types/_rsize_t.h
.o/log.o: /usr/include/sys/_types/_wint_t.h /usr/include/__cxxabi_config.h
.o/log.o: my_wid.h my_enum.h my_timer.h my_command.h my_token.h
.o/log.o: my_wid_tooltip.h my_sound.h my_wid_console.h my_python.h my_term.h
.o/log.o: my_string.h /usr/include/wchar.h
.o/log.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/log.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/log.o: /usr/include/runetype.h
.o/main.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/main.o: /usr/include/sys/_symbol_aliasing.h
.o/main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/main.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/main.o: /usr/include/i386/_types.h
.o/main.o: /usr/include/sys/_pthread/_pthread_types.h
.o/main.o: /usr/include/sys/_types/_va_list.h
.o/main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/main.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/main.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/main.o: /usr/include/sys/_types/_int8_t.h
.o/main.o: /usr/include/sys/_types/_int16_t.h
.o/main.o: /usr/include/sys/_types/_int32_t.h
.o/main.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/main.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/main.o: /usr/include/_types/_uint64_t.h
.o/main.o: /usr/include/sys/_types/_intptr_t.h
.o/main.o: /usr/include/sys/_types/_uintptr_t.h
.o/main.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/main.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/main.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/main.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/main.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/main.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/main.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/main.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/main.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/main.o: /usr/include/mach/i386/_structs.h
.o/main.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/main.o: /usr/include/sys/_types/_sigaltstack.h
.o/main.o: /usr/include/sys/_types/_ucontext.h
.o/main.o: /usr/include/sys/_types/_sigset_t.h
.o/main.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/main.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/main.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/main.o: /usr/include/libkern/_OSByteOrder.h
.o/main.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/main.o: /usr/include/sys/_types/_ct_rune_t.h
.o/main.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/main.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/main.o: /usr/include/sys/_types/_u_int16_t.h
.o/main.o: /usr/include/sys/_types/_u_int32_t.h
.o/main.o: /usr/include/sys/_types/_u_int64_t.h
.o/main.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/main.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/main.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/main.o: /usr/include/sys/_types/_posix_vdisable.h
.o/main.o: /usr/include/sys/_types/_seek_set.h
.o/main.o: /usr/include/sys/_types/_gid_t.h
.o/main.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/main.o: /usr/include/sys/_types/_fd_def.h
.o/main.o: /usr/include/sys/_types/_timespec.h
.o/main.o: /usr/include/sys/_types/_time_t.h
.o/main.o: /usr/include/sys/_types/_suseconds_t.h
.o/main.o: /usr/include/sys/_types/_fd_setsize.h
.o/main.o: /usr/include/sys/_types/_fd_set.h
.o/main.o: /usr/include/sys/_types/_fd_clr.h
.o/main.o: /usr/include/sys/_types/_fd_isset.h
.o/main.o: /usr/include/sys/_types/_fd_zero.h
.o/main.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/main.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/main.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/main.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/main.o: my_game.h my_dmap.h /usr/include/libgen.h my_slre.h my_python.h
.o/main.o: my_glapi.h my_string.h my_enum.h /usr/include/wchar.h
.o/main.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/main.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/main.o: /usr/include/ctype.h /usr/include/runetype.h my_wid.h my_timer.h
.o/main.o: my_wid_console.h my_command.h my_token.h my_ttf.h my_font.h
.o/main.o: my_tile.h ./my_sdl.h my_tile_private.h my_tex.h my_wid_tiles.h
.o/main.o: my_music.h my_sound.h my_dir.h my_file.h my_ramdisk.h my_term.h
.o/map_jigsaw.o: /usr/include/time.h /usr/include/_types.h
.o/map_jigsaw.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/map_jigsaw.o: /usr/include/sys/_symbol_aliasing.h
.o/map_jigsaw.o: /usr/include/sys/_posix_availability.h
.o/map_jigsaw.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/map_jigsaw.o: /usr/include/sys/_pthread/_pthread_types.h
.o/map_jigsaw.o: /usr/include/Availability.h
.o/map_jigsaw.o: /usr/include/AvailabilityInternal.h
.o/map_jigsaw.o: /usr/include/sys/_types/_clock_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_null.h
.o/map_jigsaw.o: /usr/include/sys/_types/_size_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_time_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_timespec.h /usr/include/unistd.h
.o/map_jigsaw.o: /usr/include/sys/unistd.h
.o/map_jigsaw.o: /usr/include/sys/_types/_posix_vdisable.h
.o/map_jigsaw.o: /usr/include/sys/_types/_seek_set.h
.o/map_jigsaw.o: /usr/include/_types/_uint64_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_ssize_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_uid_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_gid_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_intptr_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_off_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_pid_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_useconds_t.h
.o/map_jigsaw.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_def.h
.o/map_jigsaw.o: /usr/include/sys/_types/_timeval.h
.o/map_jigsaw.o: /usr/include/sys/_types/_suseconds_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_sigset_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_setsize.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_set.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_clr.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_isset.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_zero.h
.o/map_jigsaw.o: /usr/include/sys/_types/_fd_copy.h
.o/map_jigsaw.o: /usr/include/sys/_select.h /usr/include/sys/_types/_dev_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_mode_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/map_jigsaw.o: my_main.h /usr/include/stdio.h
.o/map_jigsaw.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/map_jigsaw.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/map_jigsaw.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_int16_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_int32_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_int64_t.h
.o/map_jigsaw.o: /usr/include/_types/_uint8_t.h
.o/map_jigsaw.o: /usr/include/_types/_uint16_t.h
.o/map_jigsaw.o: /usr/include/_types/_uint32_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_uintptr_t.h
.o/map_jigsaw.o: /usr/include/_types/_intmax_t.h
.o/map_jigsaw.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/map_jigsaw.o: my_pcg_basic.h /usr/include/inttypes.h
.o/map_jigsaw.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/map_jigsaw.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/map_jigsaw.o: /usr/include/math.h /usr/include/stdlib.h
.o/map_jigsaw.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/map_jigsaw.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/map_jigsaw.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/map_jigsaw.o: /usr/include/i386/_mcontext.h
.o/map_jigsaw.o: /usr/include/mach/i386/_structs.h
.o/map_jigsaw.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_sigaltstack.h
.o/map_jigsaw.o: /usr/include/sys/_types/_ucontext.h
.o/map_jigsaw.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
.o/map_jigsaw.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/map_jigsaw.o: /usr/include/libkern/_OSByteOrder.h
.o/map_jigsaw.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/map_jigsaw.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_rune_t.h
.o/map_jigsaw.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/map_jigsaw.o: /usr/include/sys/_types/_u_int8_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_u_int16_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_u_int32_t.h
.o/map_jigsaw.o: /usr/include/sys/_types/_u_int64_t.h my_point.h my_size.h
.o/map_jigsaw.o: my_thing_template.h my_thing.h my_time_util.h
.o/map_jigsaw.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/map_jigsaw.o: my_sdl.h my_game.h my_dmap.h map_jigsaw.h my_bits.h
.o/math.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/math.o: /usr/include/sys/_symbol_aliasing.h
.o/math.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/math.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/math.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/math.o: /usr/include/i386/_types.h
.o/math.o: /usr/include/sys/_pthread/_pthread_types.h
.o/math.o: /usr/include/sys/_types/_va_list.h
.o/math.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/math.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/math.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/math.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/math.o: /usr/include/sys/_types/_int8_t.h
.o/math.o: /usr/include/sys/_types/_int16_t.h
.o/math.o: /usr/include/sys/_types/_int32_t.h
.o/math.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/math.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/math.o: /usr/include/_types/_uint64_t.h
.o/math.o: /usr/include/sys/_types/_intptr_t.h
.o/math.o: /usr/include/sys/_types/_uintptr_t.h
.o/math.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/math.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/math.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/math.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/math.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/math.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/math.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/math.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/math.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/math.o: /usr/include/mach/i386/_structs.h
.o/math.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/math.o: /usr/include/sys/_types/_sigaltstack.h
.o/math.o: /usr/include/sys/_types/_ucontext.h
.o/math.o: /usr/include/sys/_types/_sigset_t.h
.o/math.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/math.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/math.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/math.o: /usr/include/libkern/_OSByteOrder.h
.o/math.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/math.o: /usr/include/sys/_types/_ct_rune_t.h
.o/math.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/math.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/math.o: /usr/include/sys/_types/_u_int16_t.h
.o/math.o: /usr/include/sys/_types/_u_int32_t.h
.o/math.o: /usr/include/sys/_types/_u_int64_t.h
.o/math.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/math.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/math.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/math.o: /usr/include/sys/_types/_posix_vdisable.h
.o/math.o: /usr/include/sys/_types/_seek_set.h
.o/math.o: /usr/include/sys/_types/_gid_t.h
.o/math.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/math.o: /usr/include/sys/_types/_fd_def.h
.o/math.o: /usr/include/sys/_types/_timespec.h
.o/math.o: /usr/include/sys/_types/_time_t.h
.o/math.o: /usr/include/sys/_types/_suseconds_t.h
.o/math.o: /usr/include/sys/_types/_fd_setsize.h
.o/math.o: /usr/include/sys/_types/_fd_set.h
.o/math.o: /usr/include/sys/_types/_fd_clr.h
.o/math.o: /usr/include/sys/_types/_fd_isset.h
.o/math.o: /usr/include/sys/_types/_fd_zero.h
.o/math.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/math.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/math.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/math.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/math.o: my_game.h my_dmap.h
.o/music.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/music.o: /usr/include/sys/_symbol_aliasing.h
.o/music.o: /usr/include/sys/_posix_availability.h
.o/music.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/music.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/music.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/music.o: /usr/include/sys/_pthread/_pthread_types.h
.o/music.o: /usr/include/sys/_types/_va_list.h
.o/music.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/music.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/music.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/music.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/music.o: /usr/include/sys/_types/_int8_t.h
.o/music.o: /usr/include/sys/_types/_int16_t.h
.o/music.o: /usr/include/sys/_types/_int32_t.h
.o/music.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/music.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/music.o: /usr/include/_types/_uint64_t.h
.o/music.o: /usr/include/sys/_types/_intptr_t.h
.o/music.o: /usr/include/sys/_types/_uintptr_t.h
.o/music.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/music.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/music.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/music.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/music.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/music.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/music.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/music.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/music.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/music.o: /usr/include/mach/i386/_structs.h
.o/music.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/music.o: /usr/include/sys/_types/_sigaltstack.h
.o/music.o: /usr/include/sys/_types/_ucontext.h
.o/music.o: /usr/include/sys/_types/_sigset_t.h
.o/music.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/music.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/music.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/music.o: /usr/include/libkern/_OSByteOrder.h
.o/music.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/music.o: /usr/include/sys/_types/_ct_rune_t.h
.o/music.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/music.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/music.o: /usr/include/sys/_types/_u_int16_t.h
.o/music.o: /usr/include/sys/_types/_u_int32_t.h
.o/music.o: /usr/include/sys/_types/_u_int64_t.h
.o/music.o: /usr/include/sys/_types/_dev_t.h
.o/music.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/music.o: my_thing_template.h my_thing.h my_time_util.h
.o/music.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/music.o: /usr/include/sys/_types/_posix_vdisable.h
.o/music.o: /usr/include/sys/_types/_seek_set.h
.o/music.o: /usr/include/sys/_types/_gid_t.h
.o/music.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/music.o: /usr/include/sys/_types/_fd_def.h
.o/music.o: /usr/include/sys/_types/_timespec.h
.o/music.o: /usr/include/sys/_types/_time_t.h
.o/music.o: /usr/include/sys/_types/_suseconds_t.h
.o/music.o: /usr/include/sys/_types/_fd_setsize.h
.o/music.o: /usr/include/sys/_types/_fd_set.h
.o/music.o: /usr/include/sys/_types/_fd_clr.h
.o/music.o: /usr/include/sys/_types/_fd_isset.h
.o/music.o: /usr/include/sys/_types/_fd_zero.h
.o/music.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/music.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/music.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/music.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/music.o: my_game.h my_dmap.h my_music.h my_ramdisk.h my_sound.h
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
.o/pcg_basic.o: /usr/include/sys/_types/_uintptr_t.h
.o/pcg_basic.o: /usr/include/_types/_intmax_t.h
.o/pcg_basic.o: /usr/include/_types/_uintmax_t.h
.o/ptrcheck.o: my_slre.h my_main.h /usr/include/stdio.h
.o/ptrcheck.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ptrcheck.o: /usr/include/sys/_posix_availability.h
.o/ptrcheck.o: /usr/include/Availability.h
.o/ptrcheck.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ptrcheck.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ptrcheck.o: /usr/include/i386/_types.h
.o/ptrcheck.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ptrcheck.o: /usr/include/sys/_types/_va_list.h
.o/ptrcheck.o: /usr/include/sys/_types/_size_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ptrcheck.o: /usr/include/sys/_types/_off_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ssize_t.h
.o/ptrcheck.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ptrcheck.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int64_t.h
.o/ptrcheck.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ptrcheck.o: /usr/include/_types/_uint32_t.h
.o/ptrcheck.o: /usr/include/_types/_uint64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_intptr_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uintptr_t.h
.o/ptrcheck.o: /usr/include/_types/_intmax_t.h
.o/ptrcheck.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/ptrcheck.o: my_pcg_basic.h /usr/include/inttypes.h
.o/ptrcheck.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/ptrcheck.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/ptrcheck.o: /usr/include/math.h /usr/include/stdlib.h
.o/ptrcheck.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/ptrcheck.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/ptrcheck.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ptrcheck.o: /usr/include/i386/_mcontext.h
.o/ptrcheck.o: /usr/include/mach/i386/_structs.h
.o/ptrcheck.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_sigaltstack.h
.o/ptrcheck.o: /usr/include/sys/_types/_ucontext.h
.o/ptrcheck.o: /usr/include/sys/_types/_sigset_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/ptrcheck.o: /usr/include/sys/_types/_timeval.h
.o/ptrcheck.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ptrcheck.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/ptrcheck.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ptrcheck.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/ptrcheck.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_u_int64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_dev_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/ptrcheck.o: my_thing_template.h my_thing.h my_time_util.h
.o/ptrcheck.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ptrcheck.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ptrcheck.o: /usr/include/sys/_types/_seek_set.h
.o/ptrcheck.o: /usr/include/sys/_types/_gid_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_useconds_t.h
.o/ptrcheck.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/ptrcheck.o: /usr/include/sys/_types/_timespec.h
.o/ptrcheck.o: /usr/include/sys/_types/_time_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_suseconds_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_setsize.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_set.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_clr.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_isset.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_zero.h
.o/ptrcheck.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ptrcheck.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ptrcheck.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ptrcheck.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ptrcheck.o: my_sdl.h my_game.h my_dmap.h my_backtrace.h
.o/ptrcheck.o: /usr/include/execinfo.h /usr/include/cxxabi.h
.o/ptrcheck.o: /usr/include/stddef.h /usr/include/sys/_types/_offsetof.h
.o/ptrcheck.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_rsize_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_wint_t.h
.o/ptrcheck.o: /usr/include/__cxxabi_config.h my_command.h my_token.h
.o/py_dmap.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_dmap.o: /usr/include/sys/_symbol_aliasing.h
.o/py_dmap.o: /usr/include/sys/_posix_availability.h
.o/py_dmap.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_dmap.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_dmap.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_dmap.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_dmap.o: /usr/include/sys/_types/_va_list.h
.o/py_dmap.o: /usr/include/sys/_types/_size_t.h
.o/py_dmap.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_dmap.o: /usr/include/sys/_types/_off_t.h
.o/py_dmap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_dmap.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_dmap.o: /usr/include/sys/_types/_int8_t.h
.o/py_dmap.o: /usr/include/sys/_types/_int16_t.h
.o/py_dmap.o: /usr/include/sys/_types/_int32_t.h
.o/py_dmap.o: /usr/include/sys/_types/_int64_t.h
.o/py_dmap.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_dmap.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_dmap.o: /usr/include/sys/_types/_intptr_t.h
.o/py_dmap.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_dmap.o: /usr/include/_types/_intmax_t.h
.o/py_dmap.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/py_dmap.o: my_pcg_basic.h /usr/include/inttypes.h
.o/py_dmap.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_dmap.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_dmap.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_dmap.o: /usr/include/sys/_types/_pid_t.h
.o/py_dmap.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/py_dmap.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/py_dmap.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/py_dmap.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/py_dmap.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_dmap.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_dmap.o: /usr/include/sys/_types/_ucontext.h
.o/py_dmap.o: /usr/include/sys/_types/_sigset_t.h
.o/py_dmap.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_dmap.o: /usr/include/sys/_types/_timeval.h
.o/py_dmap.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/py_dmap.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/py_dmap.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_dmap.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_dmap.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_dmap.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_dmap.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_dmap.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_dmap.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_dmap.o: /usr/include/sys/_types/_dev_t.h
.o/py_dmap.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_dmap.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_dmap.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_dmap.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_dmap.o: /usr/include/sys/_types/_seek_set.h
.o/py_dmap.o: /usr/include/sys/_types/_gid_t.h
.o/py_dmap.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_def.h
.o/py_dmap.o: /usr/include/sys/_types/_timespec.h
.o/py_dmap.o: /usr/include/sys/_types/_time_t.h
.o/py_dmap.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_set.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_clr.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_isset.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_zero.h
.o/py_dmap.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_dmap.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_dmap.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_dmap.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_dmap.o: my_game.h my_dmap.h my_python.h my_tile.h ./my_sdl.h
.o/py_dmap.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/py_dmap.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_dmap.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_dmap.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_dmap.o: /usr/include/runetype.h
.o/py_game.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_game.o: /usr/include/sys/_symbol_aliasing.h
.o/py_game.o: /usr/include/sys/_posix_availability.h
.o/py_game.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_game.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_game.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_game.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_game.o: /usr/include/sys/_types/_va_list.h
.o/py_game.o: /usr/include/sys/_types/_size_t.h
.o/py_game.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_game.o: /usr/include/sys/_types/_off_t.h
.o/py_game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_game.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_game.o: /usr/include/sys/_types/_int8_t.h
.o/py_game.o: /usr/include/sys/_types/_int16_t.h
.o/py_game.o: /usr/include/sys/_types/_int32_t.h
.o/py_game.o: /usr/include/sys/_types/_int64_t.h
.o/py_game.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_game.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_game.o: /usr/include/sys/_types/_intptr_t.h
.o/py_game.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_game.o: /usr/include/_types/_intmax_t.h
.o/py_game.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/py_game.o: my_pcg_basic.h /usr/include/inttypes.h
.o/py_game.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_game.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_game.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_game.o: /usr/include/sys/_types/_pid_t.h
.o/py_game.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/py_game.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/py_game.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/py_game.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/py_game.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_game.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_game.o: /usr/include/sys/_types/_ucontext.h
.o/py_game.o: /usr/include/sys/_types/_sigset_t.h
.o/py_game.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_game.o: /usr/include/sys/_types/_timeval.h
.o/py_game.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/py_game.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/py_game.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_game.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_game.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_game.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_game.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_game.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_game.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_game.o: /usr/include/sys/_types/_dev_t.h
.o/py_game.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_game.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_game.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_game.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_game.o: /usr/include/sys/_types/_seek_set.h
.o/py_game.o: /usr/include/sys/_types/_gid_t.h
.o/py_game.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_game.o: /usr/include/sys/_types/_fd_def.h
.o/py_game.o: /usr/include/sys/_types/_timespec.h
.o/py_game.o: /usr/include/sys/_types/_time_t.h
.o/py_game.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_game.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_game.o: /usr/include/sys/_types/_fd_set.h
.o/py_game.o: /usr/include/sys/_types/_fd_clr.h
.o/py_game.o: /usr/include/sys/_types/_fd_isset.h
.o/py_game.o: /usr/include/sys/_types/_fd_zero.h
.o/py_game.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_game.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_game.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_game.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_game.o: my_game.h my_dmap.h my_python.h my_py_game.h my_wid.h my_enum.h
.o/py_game.o: my_timer.h my_tile.h ./my_sdl.h my_tile_private.h my_glapi.h
.o/py_game.o: my_string.h /usr/include/wchar.h
.o/py_game.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/py_game.o: /usr/include/sys/_types/_wint_t.h
.o/py_game.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_game.o: /usr/include/runetype.h
.o/py_sdl.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_sdl.o: /usr/include/sys/_symbol_aliasing.h
.o/py_sdl.o: /usr/include/sys/_posix_availability.h
.o/py_sdl.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_sdl.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_sdl.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_sdl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_sdl.o: /usr/include/sys/_types/_va_list.h
.o/py_sdl.o: /usr/include/sys/_types/_size_t.h
.o/py_sdl.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_sdl.o: /usr/include/sys/_types/_off_t.h
.o/py_sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_sdl.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_sdl.o: /usr/include/sys/_types/_int8_t.h
.o/py_sdl.o: /usr/include/sys/_types/_int16_t.h
.o/py_sdl.o: /usr/include/sys/_types/_int32_t.h
.o/py_sdl.o: /usr/include/sys/_types/_int64_t.h
.o/py_sdl.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_sdl.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_sdl.o: /usr/include/sys/_types/_intptr_t.h
.o/py_sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_sdl.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_sdl.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_sdl.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_sdl.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_sdl.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/py_sdl.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/py_sdl.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/py_sdl.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/py_sdl.o: /usr/include/mach/i386/_structs.h
.o/py_sdl.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_sdl.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_sdl.o: /usr/include/sys/_types/_ucontext.h
.o/py_sdl.o: /usr/include/sys/_types/_sigset_t.h
.o/py_sdl.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_sdl.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/py_sdl.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/py_sdl.o: /usr/include/libkern/_OSByteOrder.h
.o/py_sdl.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_sdl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_sdl.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_sdl.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_sdl.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_sdl.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_sdl.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_sdl.o: /usr/include/sys/_types/_dev_t.h
.o/py_sdl.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_sdl.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_sdl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_sdl.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_sdl.o: /usr/include/sys/_types/_seek_set.h
.o/py_sdl.o: /usr/include/sys/_types/_gid_t.h
.o/py_sdl.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_def.h
.o/py_sdl.o: /usr/include/sys/_types/_timespec.h
.o/py_sdl.o: /usr/include/sys/_types/_time_t.h
.o/py_sdl.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_set.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_clr.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_isset.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_zero.h
.o/py_sdl.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_sdl.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_sdl.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_sdl.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_sdl.o: my_game.h my_dmap.h my_python.h my_py_sdl.h
.o/py_tex.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_tex.o: /usr/include/sys/_symbol_aliasing.h
.o/py_tex.o: /usr/include/sys/_posix_availability.h
.o/py_tex.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tex.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_tex.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_tex.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tex.o: /usr/include/sys/_types/_va_list.h
.o/py_tex.o: /usr/include/sys/_types/_size_t.h
.o/py_tex.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_tex.o: /usr/include/sys/_types/_off_t.h
.o/py_tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tex.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_tex.o: /usr/include/sys/_types/_int8_t.h
.o/py_tex.o: /usr/include/sys/_types/_int16_t.h
.o/py_tex.o: /usr/include/sys/_types/_int32_t.h
.o/py_tex.o: /usr/include/sys/_types/_int64_t.h
.o/py_tex.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_tex.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_tex.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tex.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tex.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tex.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_tex.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_tex.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_tex.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/py_tex.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/py_tex.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/py_tex.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/py_tex.o: /usr/include/mach/i386/_structs.h
.o/py_tex.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_tex.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_tex.o: /usr/include/sys/_types/_ucontext.h
.o/py_tex.o: /usr/include/sys/_types/_sigset_t.h
.o/py_tex.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_tex.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/py_tex.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/py_tex.o: /usr/include/libkern/_OSByteOrder.h
.o/py_tex.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_tex.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tex.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_tex.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tex.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tex.o: /usr/include/sys/_types/_dev_t.h
.o/py_tex.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_tex.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_tex.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_tex.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_tex.o: /usr/include/sys/_types/_seek_set.h
.o/py_tex.o: /usr/include/sys/_types/_gid_t.h
.o/py_tex.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_tex.o: /usr/include/sys/_types/_fd_def.h
.o/py_tex.o: /usr/include/sys/_types/_timespec.h
.o/py_tex.o: /usr/include/sys/_types/_time_t.h
.o/py_tex.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_tex.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_tex.o: /usr/include/sys/_types/_fd_set.h
.o/py_tex.o: /usr/include/sys/_types/_fd_clr.h
.o/py_tex.o: /usr/include/sys/_types/_fd_isset.h
.o/py_tex.o: /usr/include/sys/_types/_fd_zero.h
.o/py_tex.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_tex.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_tex.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_tex.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_tex.o: my_game.h my_dmap.h my_glapi.h my_string.h my_enum.h
.o/py_tex.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_tex.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tex.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tex.o: /usr/include/runetype.h my_python.h my_tex.h my_pixel.h
.o/py_thing.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_thing.o: /usr/include/sys/_symbol_aliasing.h
.o/py_thing.o: /usr/include/sys/_posix_availability.h
.o/py_thing.o: /usr/include/Availability.h
.o/py_thing.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/py_thing.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/py_thing.o: /usr/include/i386/_types.h
.o/py_thing.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_thing.o: /usr/include/sys/_types/_va_list.h
.o/py_thing.o: /usr/include/sys/_types/_size_t.h
.o/py_thing.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_thing.o: /usr/include/sys/_types/_off_t.h
.o/py_thing.o: /usr/include/sys/_types/_ssize_t.h
.o/py_thing.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/py_thing.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/py_thing.o: /usr/include/sys/_types/_int16_t.h
.o/py_thing.o: /usr/include/sys/_types/_int32_t.h
.o/py_thing.o: /usr/include/sys/_types/_int64_t.h
.o/py_thing.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_thing.o: /usr/include/_types/_uint32_t.h
.o/py_thing.o: /usr/include/_types/_uint64_t.h
.o/py_thing.o: /usr/include/sys/_types/_intptr_t.h
.o/py_thing.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_thing.o: /usr/include/_types/_intmax_t.h
.o/py_thing.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/py_thing.o: my_pcg_basic.h /usr/include/inttypes.h
.o/py_thing.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_thing.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/py_thing.o: /usr/include/math.h /usr/include/stdlib.h
.o/py_thing.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/py_thing.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/py_thing.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/py_thing.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/py_thing.o: /usr/include/i386/_mcontext.h
.o/py_thing.o: /usr/include/mach/i386/_structs.h
.o/py_thing.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_thing.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_thing.o: /usr/include/sys/_types/_ucontext.h
.o/py_thing.o: /usr/include/sys/_types/_sigset_t.h
.o/py_thing.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_thing.o: /usr/include/sys/_types/_timeval.h
.o/py_thing.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/py_thing.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/py_thing.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_thing.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_thing.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_thing.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_thing.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_thing.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_thing.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_thing.o: /usr/include/sys/_types/_dev_t.h
.o/py_thing.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_thing.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_thing.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_thing.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_thing.o: /usr/include/sys/_types/_seek_set.h
.o/py_thing.o: /usr/include/sys/_types/_gid_t.h
.o/py_thing.o: /usr/include/sys/_types/_useconds_t.h
.o/py_thing.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/py_thing.o: /usr/include/sys/_types/_timespec.h
.o/py_thing.o: /usr/include/sys/_types/_time_t.h
.o/py_thing.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_thing.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_thing.o: /usr/include/sys/_types/_fd_set.h
.o/py_thing.o: /usr/include/sys/_types/_fd_clr.h
.o/py_thing.o: /usr/include/sys/_types/_fd_isset.h
.o/py_thing.o: /usr/include/sys/_types/_fd_zero.h
.o/py_thing.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_thing.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_thing.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_thing.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/py_thing.o: my_sdl.h my_game.h my_dmap.h my_python.h my_py_thing.h
.o/py_tile.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_tile.o: /usr/include/sys/_symbol_aliasing.h
.o/py_tile.o: /usr/include/sys/_posix_availability.h
.o/py_tile.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tile.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_tile.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tile.o: /usr/include/sys/_types/_va_list.h
.o/py_tile.o: /usr/include/sys/_types/_size_t.h
.o/py_tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_tile.o: /usr/include/sys/_types/_off_t.h
.o/py_tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tile.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_tile.o: /usr/include/sys/_types/_int8_t.h
.o/py_tile.o: /usr/include/sys/_types/_int16_t.h
.o/py_tile.o: /usr/include/sys/_types/_int32_t.h
.o/py_tile.o: /usr/include/sys/_types/_int64_t.h
.o/py_tile.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_tile.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_tile.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tile.o: /usr/include/_types/_intmax_t.h
.o/py_tile.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/py_tile.o: my_pcg_basic.h /usr/include/inttypes.h
.o/py_tile.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_tile.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_tile.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_tile.o: /usr/include/sys/_types/_pid_t.h
.o/py_tile.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/py_tile.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/py_tile.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/py_tile.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/py_tile.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_tile.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_tile.o: /usr/include/sys/_types/_ucontext.h
.o/py_tile.o: /usr/include/sys/_types/_sigset_t.h
.o/py_tile.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_tile.o: /usr/include/sys/_types/_timeval.h
.o/py_tile.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/py_tile.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/py_tile.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_tile.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tile.o: /usr/include/sys/_types/_dev_t.h
.o/py_tile.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_tile.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_tile.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_tile.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_tile.o: /usr/include/sys/_types/_seek_set.h
.o/py_tile.o: /usr/include/sys/_types/_gid_t.h
.o/py_tile.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_tile.o: /usr/include/sys/_types/_fd_def.h
.o/py_tile.o: /usr/include/sys/_types/_timespec.h
.o/py_tile.o: /usr/include/sys/_types/_time_t.h
.o/py_tile.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_tile.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_tile.o: /usr/include/sys/_types/_fd_set.h
.o/py_tile.o: /usr/include/sys/_types/_fd_clr.h
.o/py_tile.o: /usr/include/sys/_types/_fd_isset.h
.o/py_tile.o: /usr/include/sys/_types/_fd_zero.h
.o/py_tile.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_tile.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_tile.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_tile.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_tile.o: my_game.h my_dmap.h my_python.h my_tile.h ./my_sdl.h
.o/py_tile.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/py_tile.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_tile.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tile.o: /usr/include/runetype.h
.o/py_tp.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_tp.o: /usr/include/sys/_symbol_aliasing.h
.o/py_tp.o: /usr/include/sys/_posix_availability.h
.o/py_tp.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tp.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_tp.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_tp.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tp.o: /usr/include/sys/_types/_va_list.h
.o/py_tp.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/py_tp.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_tp.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tp.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_tp.o: /usr/include/sys/_types/_int8_t.h
.o/py_tp.o: /usr/include/sys/_types/_int16_t.h
.o/py_tp.o: /usr/include/sys/_types/_int32_t.h
.o/py_tp.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/py_tp.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/py_tp.o: /usr/include/_types/_uint64_t.h
.o/py_tp.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tp.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tp.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tp.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tp.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_tp.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_tp.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_tp.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/py_tp.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/py_tp.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/py_tp.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/py_tp.o: /usr/include/mach/i386/_structs.h
.o/py_tp.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_tp.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_tp.o: /usr/include/sys/_types/_ucontext.h
.o/py_tp.o: /usr/include/sys/_types/_sigset_t.h
.o/py_tp.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_tp.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/py_tp.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/py_tp.o: /usr/include/libkern/_OSByteOrder.h
.o/py_tp.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_tp.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tp.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_tp.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_tp.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_tp.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_tp.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_tp.o: /usr/include/sys/_types/_dev_t.h
.o/py_tp.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_tp.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_tp.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_tp.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_tp.o: /usr/include/sys/_types/_seek_set.h
.o/py_tp.o: /usr/include/sys/_types/_gid_t.h
.o/py_tp.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_tp.o: /usr/include/sys/_types/_fd_def.h
.o/py_tp.o: /usr/include/sys/_types/_timespec.h
.o/py_tp.o: /usr/include/sys/_types/_time_t.h
.o/py_tp.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_tp.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_tp.o: /usr/include/sys/_types/_fd_set.h
.o/py_tp.o: /usr/include/sys/_types/_fd_clr.h
.o/py_tp.o: /usr/include/sys/_types/_fd_isset.h
.o/py_tp.o: /usr/include/sys/_types/_fd_zero.h
.o/py_tp.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_tp.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_tp.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_tp.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_tp.o: my_game.h my_dmap.h my_python.h my_tile.h ./my_sdl.h
.o/py_tp.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/py_tp.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_tp.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_tp.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tp.o: /usr/include/runetype.h my_py_tp.h my_thing_tile.h
.o/py_ttf.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_ttf.o: /usr/include/sys/_symbol_aliasing.h
.o/py_ttf.o: /usr/include/sys/_posix_availability.h
.o/py_ttf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_ttf.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_ttf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_ttf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_ttf.o: /usr/include/sys/_types/_va_list.h
.o/py_ttf.o: /usr/include/sys/_types/_size_t.h
.o/py_ttf.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_ttf.o: /usr/include/sys/_types/_off_t.h
.o/py_ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_ttf.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_ttf.o: /usr/include/sys/_types/_int8_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int16_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int32_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int64_t.h
.o/py_ttf.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_ttf.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_ttf.o: /usr/include/sys/_types/_intptr_t.h
.o/py_ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_ttf.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_ttf.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_ttf.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_ttf.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_ttf.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/py_ttf.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/py_ttf.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/py_ttf.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/py_ttf.o: /usr/include/mach/i386/_structs.h
.o/py_ttf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_ttf.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_ttf.o: /usr/include/sys/_types/_ucontext.h
.o/py_ttf.o: /usr/include/sys/_types/_sigset_t.h
.o/py_ttf.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_ttf.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/py_ttf.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/py_ttf.o: /usr/include/libkern/_OSByteOrder.h
.o/py_ttf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_ttf.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_ttf.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_ttf.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_ttf.o: /usr/include/sys/_types/_dev_t.h
.o/py_ttf.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_ttf.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_ttf.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_ttf.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_ttf.o: /usr/include/sys/_types/_seek_set.h
.o/py_ttf.o: /usr/include/sys/_types/_gid_t.h
.o/py_ttf.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_def.h
.o/py_ttf.o: /usr/include/sys/_types/_timespec.h
.o/py_ttf.o: /usr/include/sys/_types/_time_t.h
.o/py_ttf.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_set.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_clr.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_isset.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_zero.h
.o/py_ttf.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_ttf.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_ttf.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_ttf.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_ttf.o: my_game.h my_dmap.h my_python.h my_font.h my_tile.h ./my_sdl.h
.o/py_ttf.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/py_ttf.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_ttf.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/py_ttf.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_ttf.o: /usr/include/runetype.h my_ttf.h my_ascii.h
.o/py_wid.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_wid.o: /usr/include/sys/_symbol_aliasing.h
.o/py_wid.o: /usr/include/sys/_posix_availability.h
.o/py_wid.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_wid.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_wid.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_wid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_wid.o: /usr/include/sys/_types/_va_list.h
.o/py_wid.o: /usr/include/sys/_types/_size_t.h
.o/py_wid.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_wid.o: /usr/include/sys/_types/_off_t.h
.o/py_wid.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_wid.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/py_wid.o: /usr/include/sys/_types/_int8_t.h
.o/py_wid.o: /usr/include/sys/_types/_int16_t.h
.o/py_wid.o: /usr/include/sys/_types/_int32_t.h
.o/py_wid.o: /usr/include/sys/_types/_int64_t.h
.o/py_wid.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_wid.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_wid.o: /usr/include/sys/_types/_intptr_t.h
.o/py_wid.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_wid.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_wid.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_wid.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_wid.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/py_wid.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/py_wid.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/py_wid.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/py_wid.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/py_wid.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/py_wid.o: /usr/include/mach/i386/_structs.h
.o/py_wid.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_wid.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_wid.o: /usr/include/sys/_types/_ucontext.h
.o/py_wid.o: /usr/include/sys/_types/_sigset_t.h
.o/py_wid.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/py_wid.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/py_wid.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/py_wid.o: /usr/include/libkern/_OSByteOrder.h
.o/py_wid.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/py_wid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_wid.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/py_wid.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/py_wid.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_wid.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_wid.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_wid.o: /usr/include/sys/_types/_dev_t.h
.o/py_wid.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_wid.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_wid.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_wid.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_wid.o: /usr/include/sys/_types/_seek_set.h
.o/py_wid.o: /usr/include/sys/_types/_gid_t.h
.o/py_wid.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_wid.o: /usr/include/sys/_types/_fd_def.h
.o/py_wid.o: /usr/include/sys/_types/_timespec.h
.o/py_wid.o: /usr/include/sys/_types/_time_t.h
.o/py_wid.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_wid.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_wid.o: /usr/include/sys/_types/_fd_set.h
.o/py_wid.o: /usr/include/sys/_types/_fd_clr.h
.o/py_wid.o: /usr/include/sys/_types/_fd_isset.h
.o/py_wid.o: /usr/include/sys/_types/_fd_zero.h
.o/py_wid.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_wid.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_wid.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_wid.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_wid.o: my_game.h my_dmap.h my_python.h my_py_wid.h my_string.h
.o/py_wid.o: my_enum.h /usr/include/wchar.h
.o/py_wid.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/py_wid.o: /usr/include/sys/_types/_wint_t.h
.o/py_wid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_wid.o: /usr/include/runetype.h my_wid.h my_timer.h my_wid_tiles.h
.o/py_wid.o: my_ascii.h
.o/py_wid_tiles.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/py_wid_tiles.o: /usr/include/sys/_symbol_aliasing.h
.o/py_wid_tiles.o: /usr/include/sys/_posix_availability.h
.o/py_wid_tiles.o: /usr/include/Availability.h
.o/py_wid_tiles.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/py_wid_tiles.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/py_wid_tiles.o: /usr/include/i386/_types.h
.o/py_wid_tiles.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_va_list.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_size_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_off_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_ssize_t.h
.o/py_wid_tiles.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/py_wid_tiles.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_int16_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_int32_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_int64_t.h
.o/py_wid_tiles.o: /usr/include/_types/_uint8_t.h
.o/py_wid_tiles.o: /usr/include/_types/_uint16_t.h
.o/py_wid_tiles.o: /usr/include/_types/_uint32_t.h
.o/py_wid_tiles.o: /usr/include/_types/_uint64_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_intptr_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_wid_tiles.o: /usr/include/_types/_intmax_t.h
.o/py_wid_tiles.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/py_wid_tiles.o: my_pcg_basic.h /usr/include/inttypes.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/py_wid_tiles.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/py_wid_tiles.o: /usr/include/math.h /usr/include/stdlib.h
.o/py_wid_tiles.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/py_wid_tiles.o: /usr/include/sys/appleapiopts.h
.o/py_wid_tiles.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/py_wid_tiles.o: /usr/include/machine/_mcontext.h
.o/py_wid_tiles.o: /usr/include/i386/_mcontext.h
.o/py_wid_tiles.o: /usr/include/mach/i386/_structs.h
.o/py_wid_tiles.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_sigaltstack.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_ucontext.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_sigset_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_uid_t.h
.o/py_wid_tiles.o: /usr/include/sys/resource.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_timeval.h
.o/py_wid_tiles.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/py_wid_tiles.o: /usr/include/sys/_endian.h
.o/py_wid_tiles.o: /usr/include/libkern/_OSByteOrder.h
.o/py_wid_tiles.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/py_wid_tiles.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_rune_t.h
.o/py_wid_tiles.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_u_int8_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_u_int16_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_u_int32_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_u_int64_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_dev_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/py_wid_tiles.o: my_thing_template.h my_thing.h my_time_util.h
.o/py_wid_tiles.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_seek_set.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_gid_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_useconds_t.h
.o/py_wid_tiles.o: /usr/include/sys/select.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_def.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_timespec.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_time_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_set.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_clr.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_isset.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_zero.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_fd_copy.h
.o/py_wid_tiles.o: /usr/include/sys/_select.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_uuid_t.h
.o/py_wid_tiles.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/py_wid_tiles.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_game.h
.o/py_wid_tiles.o: my_dmap.h my_python.h my_wid_tiles.h
.o/python.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/python.o: /usr/include/sys/_symbol_aliasing.h
.o/python.o: /usr/include/sys/_posix_availability.h
.o/python.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/python.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/python.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/python.o: /usr/include/sys/_pthread/_pthread_types.h
.o/python.o: /usr/include/sys/_types/_va_list.h
.o/python.o: /usr/include/sys/_types/_size_t.h
.o/python.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/python.o: /usr/include/sys/_types/_off_t.h
.o/python.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/python.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/python.o: /usr/include/sys/_types/_int8_t.h
.o/python.o: /usr/include/sys/_types/_int16_t.h
.o/python.o: /usr/include/sys/_types/_int32_t.h
.o/python.o: /usr/include/sys/_types/_int64_t.h
.o/python.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/python.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/python.o: /usr/include/sys/_types/_intptr_t.h
.o/python.o: /usr/include/sys/_types/_uintptr_t.h
.o/python.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/python.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/python.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/python.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/python.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/python.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/python.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/python.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/python.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/python.o: /usr/include/mach/i386/_structs.h
.o/python.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/python.o: /usr/include/sys/_types/_sigaltstack.h
.o/python.o: /usr/include/sys/_types/_ucontext.h
.o/python.o: /usr/include/sys/_types/_sigset_t.h
.o/python.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/python.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/python.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/python.o: /usr/include/libkern/_OSByteOrder.h
.o/python.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/python.o: /usr/include/sys/_types/_ct_rune_t.h
.o/python.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/python.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/python.o: /usr/include/sys/_types/_u_int16_t.h
.o/python.o: /usr/include/sys/_types/_u_int32_t.h
.o/python.o: /usr/include/sys/_types/_u_int64_t.h
.o/python.o: /usr/include/sys/_types/_dev_t.h
.o/python.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/python.o: my_thing_template.h my_thing.h my_time_util.h
.o/python.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/python.o: /usr/include/sys/_types/_posix_vdisable.h
.o/python.o: /usr/include/sys/_types/_seek_set.h
.o/python.o: /usr/include/sys/_types/_gid_t.h
.o/python.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/python.o: /usr/include/sys/_types/_fd_def.h
.o/python.o: /usr/include/sys/_types/_timespec.h
.o/python.o: /usr/include/sys/_types/_time_t.h
.o/python.o: /usr/include/sys/_types/_suseconds_t.h
.o/python.o: /usr/include/sys/_types/_fd_setsize.h
.o/python.o: /usr/include/sys/_types/_fd_set.h
.o/python.o: /usr/include/sys/_types/_fd_clr.h
.o/python.o: /usr/include/sys/_types/_fd_isset.h
.o/python.o: /usr/include/sys/_types/_fd_zero.h
.o/python.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/python.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/python.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/python.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/python.o: my_game.h my_dmap.h my_python.h my_py_tp.h my_py_thing.h
.o/python.o: my_py_wid.h my_py_game.h my_py_sdl.h my_string.h my_enum.h
.o/python.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/python.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/python.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/python.o: /usr/include/runetype.h my_wid.h my_timer.h my_ascii.h
.o/python.o: my_wid_console.h
.o/ramdisk_data.o: my_ramdisk.h
.o/ramdisk_read.o: my_string.h my_main.h /usr/include/stdio.h
.o/ramdisk_read.o: /usr/include/sys/cdefs.h
.o/ramdisk_read.o: /usr/include/sys/_symbol_aliasing.h
.o/ramdisk_read.o: /usr/include/sys/_posix_availability.h
.o/ramdisk_read.o: /usr/include/Availability.h
.o/ramdisk_read.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ramdisk_read.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ramdisk_read.o: /usr/include/i386/_types.h
.o/ramdisk_read.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ramdisk_read.o: /usr/include/sys/_types/_va_list.h
.o/ramdisk_read.o: /usr/include/sys/_types/_size_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ramdisk_read.o: /usr/include/sys/_types/_off_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_ssize_t.h
.o/ramdisk_read.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ramdisk_read.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_int16_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_int32_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_int64_t.h
.o/ramdisk_read.o: /usr/include/_types/_uint8_t.h
.o/ramdisk_read.o: /usr/include/_types/_uint16_t.h
.o/ramdisk_read.o: /usr/include/_types/_uint32_t.h
.o/ramdisk_read.o: /usr/include/_types/_uint64_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_intptr_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_uintptr_t.h
.o/ramdisk_read.o: /usr/include/_types/_intmax_t.h
.o/ramdisk_read.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/ramdisk_read.o: my_pcg_basic.h /usr/include/inttypes.h
.o/ramdisk_read.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/ramdisk_read.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/ramdisk_read.o: /usr/include/math.h /usr/include/stdlib.h
.o/ramdisk_read.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/ramdisk_read.o: /usr/include/sys/appleapiopts.h
.o/ramdisk_read.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/ramdisk_read.o: /usr/include/machine/_mcontext.h
.o/ramdisk_read.o: /usr/include/i386/_mcontext.h
.o/ramdisk_read.o: /usr/include/mach/i386/_structs.h
.o/ramdisk_read.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_sigaltstack.h
.o/ramdisk_read.o: /usr/include/sys/_types/_ucontext.h
.o/ramdisk_read.o: /usr/include/sys/_types/_sigset_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_uid_t.h
.o/ramdisk_read.o: /usr/include/sys/resource.h
.o/ramdisk_read.o: /usr/include/sys/_types/_timeval.h
.o/ramdisk_read.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ramdisk_read.o: /usr/include/sys/_endian.h
.o/ramdisk_read.o: /usr/include/libkern/_OSByteOrder.h
.o/ramdisk_read.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/ramdisk_read.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_rune_t.h
.o/ramdisk_read.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ramdisk_read.o: /usr/include/sys/_types/_u_int8_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_u_int16_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_u_int32_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_u_int64_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_dev_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/ramdisk_read.o: my_thing_template.h my_thing.h my_time_util.h
.o/ramdisk_read.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ramdisk_read.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ramdisk_read.o: /usr/include/sys/_types/_seek_set.h
.o/ramdisk_read.o: /usr/include/sys/_types/_gid_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_useconds_t.h
.o/ramdisk_read.o: /usr/include/sys/select.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_def.h
.o/ramdisk_read.o: /usr/include/sys/_types/_timespec.h
.o/ramdisk_read.o: /usr/include/sys/_types/_time_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_suseconds_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_setsize.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_set.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_clr.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_isset.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_zero.h
.o/ramdisk_read.o: /usr/include/sys/_types/_fd_copy.h
.o/ramdisk_read.o: /usr/include/sys/_select.h
.o/ramdisk_read.o: /usr/include/sys/_types/_uuid_t.h
.o/ramdisk_read.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/ramdisk_read.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/ramdisk_read.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_game.h
.o/ramdisk_read.o: my_dmap.h my_enum.h /usr/include/wchar.h
.o/ramdisk_read.o: /usr/include/sys/_types/_mbstate_t.h
.o/ramdisk_read.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/ramdisk_read.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ramdisk_read.o: /usr/include/runetype.h my_file.h ramdisk_data.cpp
.o/ramdisk_read.o: my_ramdisk.h
.o/rand.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/rand.o: /usr/include/sys/_symbol_aliasing.h
.o/rand.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/rand.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/rand.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/rand.o: /usr/include/i386/_types.h
.o/rand.o: /usr/include/sys/_pthread/_pthread_types.h
.o/rand.o: /usr/include/sys/_types/_va_list.h
.o/rand.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/rand.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/rand.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/rand.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/rand.o: /usr/include/sys/_types/_int8_t.h
.o/rand.o: /usr/include/sys/_types/_int16_t.h
.o/rand.o: /usr/include/sys/_types/_int32_t.h
.o/rand.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/rand.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/rand.o: /usr/include/_types/_uint64_t.h
.o/rand.o: /usr/include/sys/_types/_intptr_t.h
.o/rand.o: /usr/include/sys/_types/_uintptr_t.h
.o/rand.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/rand.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/rand.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/rand.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/rand.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/rand.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/rand.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/rand.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/rand.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/rand.o: /usr/include/mach/i386/_structs.h
.o/rand.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/rand.o: /usr/include/sys/_types/_sigaltstack.h
.o/rand.o: /usr/include/sys/_types/_ucontext.h
.o/rand.o: /usr/include/sys/_types/_sigset_t.h
.o/rand.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/rand.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/rand.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/rand.o: /usr/include/libkern/_OSByteOrder.h
.o/rand.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/rand.o: /usr/include/sys/_types/_ct_rune_t.h
.o/rand.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/rand.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/rand.o: /usr/include/sys/_types/_u_int16_t.h
.o/rand.o: /usr/include/sys/_types/_u_int32_t.h
.o/rand.o: /usr/include/sys/_types/_u_int64_t.h
.o/rand.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/rand.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/rand.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/rand.o: /usr/include/sys/_types/_posix_vdisable.h
.o/rand.o: /usr/include/sys/_types/_seek_set.h
.o/rand.o: /usr/include/sys/_types/_gid_t.h
.o/rand.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/rand.o: /usr/include/sys/_types/_fd_def.h
.o/rand.o: /usr/include/sys/_types/_timespec.h
.o/rand.o: /usr/include/sys/_types/_time_t.h
.o/rand.o: /usr/include/sys/_types/_suseconds_t.h
.o/rand.o: /usr/include/sys/_types/_fd_setsize.h
.o/rand.o: /usr/include/sys/_types/_fd_set.h
.o/rand.o: /usr/include/sys/_types/_fd_clr.h
.o/rand.o: /usr/include/sys/_types/_fd_isset.h
.o/rand.o: /usr/include/sys/_types/_fd_zero.h
.o/rand.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/rand.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/rand.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/rand.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/rand.o: my_game.h my_dmap.h
.o/sdl.o: my_glapi.h /usr/include/stdlib.h /usr/include/Availability.h
.o/sdl.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/sdl.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/sdl.o: /usr/include/sys/_symbol_aliasing.h
.o/sdl.o: /usr/include/sys/_posix_availability.h
.o/sdl.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_types.h /usr/include/sys/wait.h
.o/sdl.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/sdl.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/sdl.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/sdl.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/sdl.o: /usr/include/mach/i386/_structs.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sdl.o: /usr/include/sys/_types/_sigaltstack.h
.o/sdl.o: /usr/include/sys/_types/_ucontext.h
.o/sdl.o: /usr/include/sys/_types/_sigset_t.h
.o/sdl.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
.o/sdl.o: /usr/include/sys/resource.h /usr/include/stdint.h
.o/sdl.o: /usr/include/sys/_types/_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/sdl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sdl.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/sdl.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/sdl.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/sdl.o: /usr/include/libkern/_OSByteOrder.h
.o/sdl.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/sdl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl.o: /usr/include/sys/_types/_rune_t.h
.o/sdl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_null.h
.o/sdl.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/sdl.o: /usr/include/sys/_types/_u_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_u_int64_t.h
.o/sdl.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/sdl.o: my_main.h /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/sdl.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/sdl.o: /usr/include/secure/_common.h /usr/include/assert.h my_pcg_basic.h
.o/sdl.o: /usr/include/inttypes.h my_config.h my_color.h my_callstack.h
.o/sdl.o: my_ptrcheck.h my_math_util.h /usr/include/math.h my_point.h
.o/sdl.o: my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/sdl.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/sdl.o: /usr/include/sys/_types/_posix_vdisable.h
.o/sdl.o: /usr/include/sys/_types/_seek_set.h
.o/sdl.o: /usr/include/sys/_types/_gid_t.h
.o/sdl.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/sdl.o: /usr/include/sys/_types/_fd_def.h
.o/sdl.o: /usr/include/sys/_types/_timespec.h
.o/sdl.o: /usr/include/sys/_types/_time_t.h
.o/sdl.o: /usr/include/sys/_types/_suseconds_t.h
.o/sdl.o: /usr/include/sys/_types/_fd_setsize.h
.o/sdl.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/sdl.o: /usr/include/sys/_types/_fd_isset.h
.o/sdl.o: /usr/include/sys/_types/_fd_zero.h
.o/sdl.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/sdl.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/sdl.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/sdl.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/sdl.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/sdl.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/sdl.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/sdl.o: /usr/include/ctype.h /usr/include/runetype.h my_ttf.h my_slre.h
.o/sdl.o: my_command.h my_token.h my_term.h my_python.h my_wid.h my_timer.h
.o/slre.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/slre.o: /usr/include/sys/_symbol_aliasing.h
.o/slre.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/slre.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/slre.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/slre.o: /usr/include/i386/_types.h
.o/slre.o: /usr/include/sys/_pthread/_pthread_types.h
.o/slre.o: /usr/include/sys/_types/_va_list.h
.o/slre.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/slre.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/slre.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/slre.o: /usr/include/secure/_common.h /usr/include/assert.h
.o/slre.o: /usr/include/ctype.h /usr/include/runetype.h
.o/slre.o: /usr/include/sys/_types/_ct_rune_t.h
.o/slre.o: /usr/include/sys/_types/_rune_t.h
.o/slre.o: /usr/include/sys/_types/_wchar_t.h
.o/slre.o: /usr/include/sys/_types/_wint_t.h /usr/include/string.h
.o/slre.o: /usr/include/sys/_types/_rsize_t.h
.o/slre.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/slre.o: /usr/include/secure/_string.h my_slre.h
.o/sound.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/sound.o: /usr/include/sys/_symbol_aliasing.h
.o/sound.o: /usr/include/sys/_posix_availability.h
.o/sound.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/sound.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/sound.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/sound.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sound.o: /usr/include/sys/_types/_va_list.h
.o/sound.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/sound.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/sound.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/sound.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/sound.o: /usr/include/sys/_types/_int8_t.h
.o/sound.o: /usr/include/sys/_types/_int16_t.h
.o/sound.o: /usr/include/sys/_types/_int32_t.h
.o/sound.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/sound.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sound.o: /usr/include/_types/_uint64_t.h
.o/sound.o: /usr/include/sys/_types/_intptr_t.h
.o/sound.o: /usr/include/sys/_types/_uintptr_t.h
.o/sound.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/sound.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/sound.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/sound.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/sound.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/sound.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/sound.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/sound.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/sound.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/sound.o: /usr/include/mach/i386/_structs.h
.o/sound.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/sound.o: /usr/include/sys/_types/_sigaltstack.h
.o/sound.o: /usr/include/sys/_types/_ucontext.h
.o/sound.o: /usr/include/sys/_types/_sigset_t.h
.o/sound.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/sound.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/sound.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/sound.o: /usr/include/libkern/_OSByteOrder.h
.o/sound.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/sound.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sound.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/sound.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/sound.o: /usr/include/sys/_types/_u_int16_t.h
.o/sound.o: /usr/include/sys/_types/_u_int32_t.h
.o/sound.o: /usr/include/sys/_types/_u_int64_t.h
.o/sound.o: /usr/include/sys/_types/_dev_t.h
.o/sound.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/sound.o: my_thing_template.h my_thing.h my_time_util.h
.o/sound.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/sound.o: /usr/include/sys/_types/_posix_vdisable.h
.o/sound.o: /usr/include/sys/_types/_seek_set.h
.o/sound.o: /usr/include/sys/_types/_gid_t.h
.o/sound.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/sound.o: /usr/include/sys/_types/_fd_def.h
.o/sound.o: /usr/include/sys/_types/_timespec.h
.o/sound.o: /usr/include/sys/_types/_time_t.h
.o/sound.o: /usr/include/sys/_types/_suseconds_t.h
.o/sound.o: /usr/include/sys/_types/_fd_setsize.h
.o/sound.o: /usr/include/sys/_types/_fd_set.h
.o/sound.o: /usr/include/sys/_types/_fd_clr.h
.o/sound.o: /usr/include/sys/_types/_fd_isset.h
.o/sound.o: /usr/include/sys/_types/_fd_zero.h
.o/sound.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/sound.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/sound.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/sound.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/sound.o: my_game.h my_dmap.h my_sound.h my_ramdisk.h my_music.h
.o/stb_image.o: my_stb_image.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/stb_image.o: /usr/include/sys/_symbol_aliasing.h
.o/stb_image.o: /usr/include/sys/_posix_availability.h
.o/stb_image.o: /usr/include/Availability.h
.o/stb_image.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/stb_image.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/stb_image.o: /usr/include/i386/_types.h
.o/stb_image.o: /usr/include/sys/_pthread/_pthread_types.h
.o/stb_image.o: /usr/include/sys/_types/_va_list.h
.o/stb_image.o: /usr/include/sys/_types/_size_t.h
.o/stb_image.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/stb_image.o: /usr/include/sys/_types/_off_t.h
.o/stb_image.o: /usr/include/sys/_types/_ssize_t.h
.o/stb_image.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/stb_image.o: my_main.h /usr/include/stdint.h
.o/stb_image.o: /usr/include/sys/_types/_int8_t.h
.o/stb_image.o: /usr/include/sys/_types/_int16_t.h
.o/stb_image.o: /usr/include/sys/_types/_int32_t.h
.o/stb_image.o: /usr/include/sys/_types/_int64_t.h
.o/stb_image.o: /usr/include/_types/_uint8_t.h
.o/stb_image.o: /usr/include/_types/_uint16_t.h
.o/stb_image.o: /usr/include/_types/_uint32_t.h
.o/stb_image.o: /usr/include/_types/_uint64_t.h
.o/stb_image.o: /usr/include/sys/_types/_intptr_t.h
.o/stb_image.o: /usr/include/sys/_types/_uintptr_t.h
.o/stb_image.o: /usr/include/_types/_intmax_t.h
.o/stb_image.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/stb_image.o: my_pcg_basic.h /usr/include/inttypes.h
.o/stb_image.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/stb_image.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/stb_image.o: /usr/include/math.h /usr/include/stdlib.h
.o/stb_image.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/stb_image.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/stb_image.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/stb_image.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/stb_image.o: /usr/include/i386/_mcontext.h
.o/stb_image.o: /usr/include/mach/i386/_structs.h
.o/stb_image.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/stb_image.o: /usr/include/sys/_types/_sigaltstack.h
.o/stb_image.o: /usr/include/sys/_types/_ucontext.h
.o/stb_image.o: /usr/include/sys/_types/_sigset_t.h
.o/stb_image.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/stb_image.o: /usr/include/sys/_types/_timeval.h
.o/stb_image.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/stb_image.o: /usr/include/sys/_endian.h
.o/stb_image.o: /usr/include/libkern/_OSByteOrder.h
.o/stb_image.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/stb_image.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/stb_image.o: /usr/include/sys/_types/_rune_t.h
.o/stb_image.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/stb_image.o: /usr/include/sys/_types/_u_int8_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int16_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int32_t.h
.o/stb_image.o: /usr/include/sys/_types/_u_int64_t.h
.o/stb_image.o: /usr/include/sys/_types/_dev_t.h
.o/stb_image.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/stb_image.o: my_thing_template.h my_thing.h my_time_util.h
.o/stb_image.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/stb_image.o: /usr/include/sys/_types/_posix_vdisable.h
.o/stb_image.o: /usr/include/sys/_types/_seek_set.h
.o/stb_image.o: /usr/include/sys/_types/_gid_t.h
.o/stb_image.o: /usr/include/sys/_types/_useconds_t.h
.o/stb_image.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/stb_image.o: /usr/include/sys/_types/_timespec.h
.o/stb_image.o: /usr/include/sys/_types/_time_t.h
.o/stb_image.o: /usr/include/sys/_types/_suseconds_t.h
.o/stb_image.o: /usr/include/sys/_types/_fd_setsize.h
.o/stb_image.o: /usr/include/sys/_types/_fd_set.h
.o/stb_image.o: /usr/include/sys/_types/_fd_clr.h
.o/stb_image.o: /usr/include/sys/_types/_fd_isset.h
.o/stb_image.o: /usr/include/sys/_types/_fd_zero.h
.o/stb_image.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/stb_image.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/stb_image.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/stb_image.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/stb_image.o: my_sdl.h my_game.h my_dmap.h
.o/string.o: /usr/include/libgen.h /usr/include/sys/cdefs.h
.o/string.o: /usr/include/sys/_symbol_aliasing.h
.o/string.o: /usr/include/sys/_posix_availability.h
.o/string.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/string.o: my_main.h /usr/include/stdio.h /usr/include/_types.h
.o/string.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/string.o: /usr/include/i386/_types.h
.o/string.o: /usr/include/sys/_pthread/_pthread_types.h
.o/string.o: /usr/include/sys/_types/_va_list.h
.o/string.o: /usr/include/sys/_types/_size_t.h
.o/string.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/string.o: /usr/include/sys/_types/_off_t.h
.o/string.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/string.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/string.o: /usr/include/sys/_types/_int8_t.h
.o/string.o: /usr/include/sys/_types/_int16_t.h
.o/string.o: /usr/include/sys/_types/_int32_t.h
.o/string.o: /usr/include/sys/_types/_int64_t.h
.o/string.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/string.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/string.o: /usr/include/sys/_types/_intptr_t.h
.o/string.o: /usr/include/sys/_types/_uintptr_t.h
.o/string.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/string.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/string.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/string.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/string.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/string.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/string.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/string.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/string.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/string.o: /usr/include/mach/i386/_structs.h
.o/string.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/string.o: /usr/include/sys/_types/_sigaltstack.h
.o/string.o: /usr/include/sys/_types/_ucontext.h
.o/string.o: /usr/include/sys/_types/_sigset_t.h
.o/string.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/string.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/string.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/string.o: /usr/include/libkern/_OSByteOrder.h
.o/string.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/string.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/string.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/string.o: /usr/include/sys/_types/_u_int16_t.h
.o/string.o: /usr/include/sys/_types/_u_int32_t.h
.o/string.o: /usr/include/sys/_types/_u_int64_t.h
.o/string.o: /usr/include/sys/_types/_dev_t.h
.o/string.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/string.o: my_thing_template.h my_thing.h my_time_util.h
.o/string.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/string.o: /usr/include/sys/_types/_posix_vdisable.h
.o/string.o: /usr/include/sys/_types/_seek_set.h
.o/string.o: /usr/include/sys/_types/_gid_t.h
.o/string.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/string.o: /usr/include/sys/_types/_fd_def.h
.o/string.o: /usr/include/sys/_types/_timespec.h
.o/string.o: /usr/include/sys/_types/_time_t.h
.o/string.o: /usr/include/sys/_types/_suseconds_t.h
.o/string.o: /usr/include/sys/_types/_fd_setsize.h
.o/string.o: /usr/include/sys/_types/_fd_set.h
.o/string.o: /usr/include/sys/_types/_fd_clr.h
.o/string.o: /usr/include/sys/_types/_fd_isset.h
.o/string.o: /usr/include/sys/_types/_fd_zero.h
.o/string.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/string.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/string.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/string.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/string.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/string.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/string.o: /usr/include/sys/_types/_wint_t.h
.o/string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/string.o: /usr/include/runetype.h my_tex.h my_tile.h ./my_sdl.h
.o/string.o: my_tile_private.h my_glapi.h my_wid.h my_timer.h
.o/term.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/term.o: /usr/include/sys/_symbol_aliasing.h
.o/term.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/term.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/term.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/term.o: /usr/include/i386/_types.h
.o/term.o: /usr/include/sys/_pthread/_pthread_types.h
.o/term.o: /usr/include/sys/_types/_va_list.h
.o/term.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/term.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/term.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/term.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/term.o: /usr/include/sys/_types/_int8_t.h
.o/term.o: /usr/include/sys/_types/_int16_t.h
.o/term.o: /usr/include/sys/_types/_int32_t.h
.o/term.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/term.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/term.o: /usr/include/_types/_uint64_t.h
.o/term.o: /usr/include/sys/_types/_intptr_t.h
.o/term.o: /usr/include/sys/_types/_uintptr_t.h
.o/term.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/term.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/term.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/term.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/term.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/term.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/term.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/term.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/term.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/term.o: /usr/include/mach/i386/_structs.h
.o/term.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/term.o: /usr/include/sys/_types/_sigaltstack.h
.o/term.o: /usr/include/sys/_types/_ucontext.h
.o/term.o: /usr/include/sys/_types/_sigset_t.h
.o/term.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/term.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/term.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/term.o: /usr/include/libkern/_OSByteOrder.h
.o/term.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/term.o: /usr/include/sys/_types/_ct_rune_t.h
.o/term.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/term.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/term.o: /usr/include/sys/_types/_u_int16_t.h
.o/term.o: /usr/include/sys/_types/_u_int32_t.h
.o/term.o: /usr/include/sys/_types/_u_int64_t.h
.o/term.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/term.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/term.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/term.o: /usr/include/sys/_types/_posix_vdisable.h
.o/term.o: /usr/include/sys/_types/_seek_set.h
.o/term.o: /usr/include/sys/_types/_gid_t.h
.o/term.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/term.o: /usr/include/sys/_types/_fd_def.h
.o/term.o: /usr/include/sys/_types/_timespec.h
.o/term.o: /usr/include/sys/_types/_time_t.h
.o/term.o: /usr/include/sys/_types/_suseconds_t.h
.o/term.o: /usr/include/sys/_types/_fd_setsize.h
.o/term.o: /usr/include/sys/_types/_fd_set.h
.o/term.o: /usr/include/sys/_types/_fd_clr.h
.o/term.o: /usr/include/sys/_types/_fd_isset.h
.o/term.o: /usr/include/sys/_types/_fd_zero.h
.o/term.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/term.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/term.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/term.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/term.o: my_game.h my_dmap.h my_term.h
.o/tex.o: my_stb_image.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/tex.o: /usr/include/sys/_symbol_aliasing.h
.o/tex.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/tex.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/tex.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/tex.o: /usr/include/i386/_types.h
.o/tex.o: /usr/include/sys/_pthread/_pthread_types.h
.o/tex.o: /usr/include/sys/_types/_va_list.h
.o/tex.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/tex.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tex.o: /usr/include/secure/_common.h my_glapi.h /usr/include/stdlib.h
.o/tex.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/tex.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/tex.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/tex.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/tex.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/tex.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/tex.o: /usr/include/sys/_types/_sigaltstack.h
.o/tex.o: /usr/include/sys/_types/_ucontext.h
.o/tex.o: /usr/include/sys/_types/_sigset_t.h
.o/tex.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/tex.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/tex.o: /usr/include/sys/_types/_int16_t.h
.o/tex.o: /usr/include/sys/_types/_int32_t.h
.o/tex.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/tex.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tex.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/tex.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/tex.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/tex.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/tex.o: /usr/include/libkern/_OSByteOrder.h
.o/tex.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/tex.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tex.o: /usr/include/sys/_types/_rune_t.h
.o/tex.o: /usr/include/sys/_types/_wchar_t.h /usr/include/machine/types.h
.o/tex.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/tex.o: /usr/include/sys/_types/_u_int16_t.h
.o/tex.o: /usr/include/sys/_types/_u_int32_t.h
.o/tex.o: /usr/include/sys/_types/_u_int64_t.h
.o/tex.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/tex.o: my_main.h /usr/include/assert.h my_pcg_basic.h
.o/tex.o: /usr/include/inttypes.h my_config.h my_color.h my_callstack.h
.o/tex.o: my_ptrcheck.h my_math_util.h /usr/include/math.h my_point.h
.o/tex.o: my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/tex.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/tex.o: /usr/include/sys/_types/_posix_vdisable.h
.o/tex.o: /usr/include/sys/_types/_seek_set.h
.o/tex.o: /usr/include/sys/_types/_gid_t.h
.o/tex.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/tex.o: /usr/include/sys/_types/_fd_def.h
.o/tex.o: /usr/include/sys/_types/_timespec.h
.o/tex.o: /usr/include/sys/_types/_time_t.h
.o/tex.o: /usr/include/sys/_types/_suseconds_t.h
.o/tex.o: /usr/include/sys/_types/_fd_setsize.h
.o/tex.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/tex.o: /usr/include/sys/_types/_fd_isset.h
.o/tex.o: /usr/include/sys/_types/_fd_zero.h
.o/tex.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/tex.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/tex.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/tex.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/tex.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/tex.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/tex.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/tex.o: /usr/include/ctype.h /usr/include/runetype.h my_tex.h my_ramdisk.h
.o/tex.o: my_pixel.h
.o/thing.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/thing.o: /usr/include/sys/_symbol_aliasing.h
.o/thing.o: /usr/include/sys/_posix_availability.h
.o/thing.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/thing.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing.o: /usr/include/sys/_types/_va_list.h
.o/thing.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/thing.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/thing.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/thing.o: /usr/include/sys/_types/_int8_t.h
.o/thing.o: /usr/include/sys/_types/_int16_t.h
.o/thing.o: /usr/include/sys/_types/_int32_t.h
.o/thing.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/thing.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/thing.o: /usr/include/_types/_uint64_t.h
.o/thing.o: /usr/include/sys/_types/_intptr_t.h
.o/thing.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/thing.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/thing.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/thing.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/thing.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/thing.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/thing.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/thing.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/thing.o: /usr/include/mach/i386/_structs.h
.o/thing.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/thing.o: /usr/include/sys/_types/_sigaltstack.h
.o/thing.o: /usr/include/sys/_types/_ucontext.h
.o/thing.o: /usr/include/sys/_types/_sigset_t.h
.o/thing.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/thing.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/thing.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/thing.o: /usr/include/libkern/_OSByteOrder.h
.o/thing.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/thing.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/thing.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/thing.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing.o: /usr/include/sys/_types/_dev_t.h
.o/thing.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/thing.o: my_thing_template.h my_thing.h my_time_util.h
.o/thing.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing.o: /usr/include/sys/_types/_seek_set.h
.o/thing.o: /usr/include/sys/_types/_gid_t.h
.o/thing.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/thing.o: /usr/include/sys/_types/_fd_def.h
.o/thing.o: /usr/include/sys/_types/_timespec.h
.o/thing.o: /usr/include/sys/_types/_time_t.h
.o/thing.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing.o: /usr/include/sys/_types/_fd_set.h
.o/thing.o: /usr/include/sys/_types/_fd_clr.h
.o/thing.o: /usr/include/sys/_types/_fd_isset.h
.o/thing.o: /usr/include/sys/_types/_fd_zero.h
.o/thing.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/thing.o: my_game.h my_dmap.h my_tile.h ./my_sdl.h my_tile_private.h
.o/thing.o: my_glapi.h my_string.h my_enum.h /usr/include/wchar.h
.o/thing.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/thing.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/thing.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_tile.h
.o/thing.o: my_python.h
.o/thing_anim.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/thing_anim.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_anim.o: /usr/include/sys/_posix_availability.h
.o/thing_anim.o: /usr/include/Availability.h
.o/thing_anim.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_anim.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_anim.o: /usr/include/i386/_types.h
.o/thing_anim.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_anim.o: /usr/include/sys/_types/_va_list.h
.o/thing_anim.o: /usr/include/sys/_types/_size_t.h
.o/thing_anim.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_anim.o: /usr/include/sys/_types/_off_t.h
.o/thing_anim.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_anim.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_anim.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int16_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int32_t.h
.o/thing_anim.o: /usr/include/sys/_types/_int64_t.h
.o/thing_anim.o: /usr/include/_types/_uint8_t.h
.o/thing_anim.o: /usr/include/_types/_uint16_t.h
.o/thing_anim.o: /usr/include/_types/_uint32_t.h
.o/thing_anim.o: /usr/include/_types/_uint64_t.h
.o/thing_anim.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_anim.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_anim.o: /usr/include/_types/_intmax_t.h
.o/thing_anim.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/thing_anim.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_anim.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/thing_anim.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/thing_anim.o: /usr/include/math.h /usr/include/stdlib.h
.o/thing_anim.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/thing_anim.o: /usr/include/sys/appleapiopts.h
.o/thing_anim.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/thing_anim.o: /usr/include/machine/_mcontext.h
.o/thing_anim.o: /usr/include/i386/_mcontext.h
.o/thing_anim.o: /usr/include/mach/i386/_structs.h
.o/thing_anim.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/thing_anim.o: /usr/include/sys/_types/_sigaltstack.h
.o/thing_anim.o: /usr/include/sys/_types/_ucontext.h
.o/thing_anim.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_anim.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/thing_anim.o: /usr/include/sys/_types/_timeval.h
.o/thing_anim.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/thing_anim.o: /usr/include/sys/_endian.h
.o/thing_anim.o: /usr/include/libkern/_OSByteOrder.h
.o/thing_anim.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/thing_anim.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/thing_anim.o: /usr/include/sys/_types/_rune_t.h
.o/thing_anim.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_anim.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_anim.o: /usr/include/sys/_types/_dev_t.h
.o/thing_anim.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/thing_anim.o: my_thing_template.h my_thing.h my_time_util.h
.o/thing_anim.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_anim.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_anim.o: /usr/include/sys/_types/_seek_set.h
.o/thing_anim.o: /usr/include/sys/_types/_gid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_anim.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/thing_anim.o: /usr/include/sys/_types/_timespec.h
.o/thing_anim.o: /usr/include/sys/_types/_time_t.h
.o/thing_anim.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_set.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_anim.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_anim.o: /usr/include/sys/_select.h /usr/include/sys/_types/_uuid_t.h
.o/thing_anim.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_anim.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_anim.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_game.h
.o/thing_anim.o: my_dmap.h my_tile.h ./my_sdl.h my_tile_private.h my_glapi.h
.o/thing_anim.o: my_string.h my_enum.h /usr/include/wchar.h
.o/thing_anim.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/thing_anim.o: /usr/include/sys/_types/_wint_t.h
.o/thing_anim.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_anim.o: /usr/include/runetype.h my_thing_tile.h
.o/thing_dir.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/thing_dir.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_dir.o: /usr/include/sys/_posix_availability.h
.o/thing_dir.o: /usr/include/Availability.h
.o/thing_dir.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_dir.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_dir.o: /usr/include/i386/_types.h
.o/thing_dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_dir.o: /usr/include/sys/_types/_va_list.h
.o/thing_dir.o: /usr/include/sys/_types/_size_t.h
.o/thing_dir.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_dir.o: /usr/include/sys/_types/_off_t.h
.o/thing_dir.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_dir.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_dir.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_dir.o: /usr/include/sys/_types/_int16_t.h
.o/thing_dir.o: /usr/include/sys/_types/_int32_t.h
.o/thing_dir.o: /usr/include/sys/_types/_int64_t.h
.o/thing_dir.o: /usr/include/_types/_uint8_t.h
.o/thing_dir.o: /usr/include/_types/_uint16_t.h
.o/thing_dir.o: /usr/include/_types/_uint32_t.h
.o/thing_dir.o: /usr/include/_types/_uint64_t.h
.o/thing_dir.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_dir.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_dir.o: /usr/include/_types/_intmax_t.h
.o/thing_dir.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/thing_dir.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_dir.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/thing_dir.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/thing_dir.o: /usr/include/math.h /usr/include/stdlib.h
.o/thing_dir.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/thing_dir.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/thing_dir.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/thing_dir.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/thing_dir.o: /usr/include/i386/_mcontext.h
.o/thing_dir.o: /usr/include/mach/i386/_structs.h
.o/thing_dir.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/thing_dir.o: /usr/include/sys/_types/_sigaltstack.h
.o/thing_dir.o: /usr/include/sys/_types/_ucontext.h
.o/thing_dir.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_dir.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/thing_dir.o: /usr/include/sys/_types/_timeval.h
.o/thing_dir.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/thing_dir.o: /usr/include/sys/_endian.h
.o/thing_dir.o: /usr/include/libkern/_OSByteOrder.h
.o/thing_dir.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/thing_dir.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/thing_dir.o: /usr/include/sys/_types/_rune_t.h
.o/thing_dir.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_dir.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_dir.o: /usr/include/sys/_types/_dev_t.h
.o/thing_dir.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/thing_dir.o: my_thing_template.h my_thing.h my_time_util.h
.o/thing_dir.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_dir.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_dir.o: /usr/include/sys/_types/_seek_set.h
.o/thing_dir.o: /usr/include/sys/_types/_gid_t.h
.o/thing_dir.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_dir.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/thing_dir.o: /usr/include/sys/_types/_timespec.h
.o/thing_dir.o: /usr/include/sys/_types/_time_t.h
.o/thing_dir.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_dir.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_dir.o: /usr/include/sys/_types/_fd_set.h
.o/thing_dir.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_dir.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_dir.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_dir.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_dir.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_dir.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_dir.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_dir.o: my_sdl.h my_game.h my_dmap.h
.o/thing_map.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/thing_map.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_map.o: /usr/include/sys/_posix_availability.h
.o/thing_map.o: /usr/include/Availability.h
.o/thing_map.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_map.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_map.o: /usr/include/i386/_types.h
.o/thing_map.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_map.o: /usr/include/sys/_types/_va_list.h
.o/thing_map.o: /usr/include/sys/_types/_size_t.h
.o/thing_map.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_map.o: /usr/include/sys/_types/_off_t.h
.o/thing_map.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_map.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_map.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_map.o: /usr/include/sys/_types/_int16_t.h
.o/thing_map.o: /usr/include/sys/_types/_int32_t.h
.o/thing_map.o: /usr/include/sys/_types/_int64_t.h
.o/thing_map.o: /usr/include/_types/_uint8_t.h
.o/thing_map.o: /usr/include/_types/_uint16_t.h
.o/thing_map.o: /usr/include/_types/_uint32_t.h
.o/thing_map.o: /usr/include/_types/_uint64_t.h
.o/thing_map.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_map.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_map.o: /usr/include/_types/_intmax_t.h
.o/thing_map.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/thing_map.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_map.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/thing_map.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/thing_map.o: /usr/include/math.h /usr/include/stdlib.h
.o/thing_map.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/thing_map.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/thing_map.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/thing_map.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/thing_map.o: /usr/include/i386/_mcontext.h
.o/thing_map.o: /usr/include/mach/i386/_structs.h
.o/thing_map.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/thing_map.o: /usr/include/sys/_types/_sigaltstack.h
.o/thing_map.o: /usr/include/sys/_types/_ucontext.h
.o/thing_map.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_map.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/thing_map.o: /usr/include/sys/_types/_timeval.h
.o/thing_map.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/thing_map.o: /usr/include/sys/_endian.h
.o/thing_map.o: /usr/include/libkern/_OSByteOrder.h
.o/thing_map.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/thing_map.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/thing_map.o: /usr/include/sys/_types/_rune_t.h
.o/thing_map.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_map.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_map.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_map.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_map.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_map.o: /usr/include/sys/_types/_dev_t.h
.o/thing_map.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/thing_map.o: my_thing_template.h my_thing.h my_time_util.h
.o/thing_map.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_map.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_map.o: /usr/include/sys/_types/_seek_set.h
.o/thing_map.o: /usr/include/sys/_types/_gid_t.h
.o/thing_map.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_map.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/thing_map.o: /usr/include/sys/_types/_timespec.h
.o/thing_map.o: /usr/include/sys/_types/_time_t.h
.o/thing_map.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_map.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_map.o: /usr/include/sys/_types/_fd_set.h
.o/thing_map.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_map.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_map.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_map.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_map.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_map.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_map.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_map.o: my_sdl.h my_game.h my_dmap.h my_python.h my_tile.h ./my_sdl.h
.o/thing_map.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/thing_map.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_map.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_map.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_map.o: /usr/include/runetype.h my_thing_tile.h my_tex.h
.o/thing_template.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/thing_template.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_template.o: /usr/include/sys/_posix_availability.h
.o/thing_template.o: /usr/include/Availability.h
.o/thing_template.o: /usr/include/AvailabilityInternal.h
.o/thing_template.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/thing_template.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/thing_template.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_template.o: /usr/include/sys/_types/_va_list.h
.o/thing_template.o: /usr/include/sys/_types/_size_t.h
.o/thing_template.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_template.o: /usr/include/sys/_types/_off_t.h
.o/thing_template.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_template.o: /usr/include/secure/_stdio.h
.o/thing_template.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/thing_template.o: /usr/include/sys/_types/_int8_t.h
.o/thing_template.o: /usr/include/sys/_types/_int16_t.h
.o/thing_template.o: /usr/include/sys/_types/_int32_t.h
.o/thing_template.o: /usr/include/sys/_types/_int64_t.h
.o/thing_template.o: /usr/include/_types/_uint8_t.h
.o/thing_template.o: /usr/include/_types/_uint16_t.h
.o/thing_template.o: /usr/include/_types/_uint32_t.h
.o/thing_template.o: /usr/include/_types/_uint64_t.h
.o/thing_template.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_template.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_template.o: /usr/include/_types/_intmax_t.h
.o/thing_template.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/thing_template.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_template.o: /usr/include/sys/_types/_wchar_t.h my_config.h
.o/thing_template.o: my_color.h my_callstack.h my_ptrcheck.h my_math_util.h
.o/thing_template.o: /usr/include/math.h /usr/include/stdlib.h
.o/thing_template.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/thing_template.o: /usr/include/sys/_types/_id_t.h
.o/thing_template.o: /usr/include/sys/signal.h
.o/thing_template.o: /usr/include/sys/appleapiopts.h
.o/thing_template.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/thing_template.o: /usr/include/machine/_mcontext.h
.o/thing_template.o: /usr/include/i386/_mcontext.h
.o/thing_template.o: /usr/include/mach/i386/_structs.h
.o/thing_template.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/thing_template.o: /usr/include/sys/_types/_sigaltstack.h
.o/thing_template.o: /usr/include/sys/_types/_ucontext.h
.o/thing_template.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_template.o: /usr/include/sys/_types/_uid_t.h
.o/thing_template.o: /usr/include/sys/resource.h
.o/thing_template.o: /usr/include/sys/_types/_timeval.h
.o/thing_template.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/thing_template.o: /usr/include/sys/_endian.h
.o/thing_template.o: /usr/include/libkern/_OSByteOrder.h
.o/thing_template.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/thing_template.o: /usr/include/alloca.h
.o/thing_template.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_template.o: /usr/include/sys/_types/_rune_t.h
.o/thing_template.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_template.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_template.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_template.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_template.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_template.o: /usr/include/sys/_types/_dev_t.h
.o/thing_template.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/thing_template.o: my_thing_template.h my_thing.h my_time_util.h
.o/thing_template.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_template.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_template.o: /usr/include/sys/_types/_seek_set.h
.o/thing_template.o: /usr/include/sys/_types/_gid_t.h
.o/thing_template.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_template.o: /usr/include/sys/select.h
.o/thing_template.o: /usr/include/sys/_types/_fd_def.h
.o/thing_template.o: /usr/include/sys/_types/_timespec.h
.o/thing_template.o: /usr/include/sys/_types/_time_t.h
.o/thing_template.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_template.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_template.o: /usr/include/sys/_types/_fd_set.h
.o/thing_template.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_template.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_template.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_template.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_template.o: /usr/include/sys/_select.h
.o/thing_template.o: /usr/include/sys/_types/_uuid_t.h
.o/thing_template.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_template.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_template.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_game.h
.o/thing_template.o: my_dmap.h my_thing_tile.h my_tile.h ./my_sdl.h
.o/thing_template.o: my_tile_private.h my_glapi.h my_string.h my_enum.h
.o/thing_template.o: /usr/include/wchar.h
.o/thing_template.o: /usr/include/sys/_types/_mbstate_t.h
.o/thing_template.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/thing_template.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_template.o: /usr/include/runetype.h
.o/thing_tile.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/thing_tile.o: /usr/include/sys/_symbol_aliasing.h
.o/thing_tile.o: /usr/include/sys/_posix_availability.h
.o/thing_tile.o: /usr/include/Availability.h
.o/thing_tile.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_tile.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_tile.o: /usr/include/i386/_types.h
.o/thing_tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_tile.o: /usr/include/sys/_types/_va_list.h
.o/thing_tile.o: /usr/include/sys/_types/_size_t.h
.o/thing_tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_tile.o: /usr/include/sys/_types/_off_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_tile.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_tile.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/thing_tile.o: /usr/include/sys/_types/_int16_t.h
.o/thing_tile.o: /usr/include/sys/_types/_int32_t.h
.o/thing_tile.o: /usr/include/sys/_types/_int64_t.h
.o/thing_tile.o: /usr/include/_types/_uint8_t.h
.o/thing_tile.o: /usr/include/_types/_uint16_t.h
.o/thing_tile.o: /usr/include/_types/_uint32_t.h
.o/thing_tile.o: /usr/include/_types/_uint64_t.h
.o/thing_tile.o: /usr/include/sys/_types/_intptr_t.h
.o/thing_tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_tile.o: /usr/include/_types/_intmax_t.h
.o/thing_tile.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/thing_tile.o: my_pcg_basic.h /usr/include/inttypes.h
.o/thing_tile.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/thing_tile.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/thing_tile.o: /usr/include/math.h /usr/include/stdlib.h
.o/thing_tile.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/thing_tile.o: /usr/include/sys/appleapiopts.h
.o/thing_tile.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/thing_tile.o: /usr/include/machine/_mcontext.h
.o/thing_tile.o: /usr/include/i386/_mcontext.h
.o/thing_tile.o: /usr/include/mach/i386/_structs.h
.o/thing_tile.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/thing_tile.o: /usr/include/sys/_types/_sigaltstack.h
.o/thing_tile.o: /usr/include/sys/_types/_ucontext.h
.o/thing_tile.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_tile.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/thing_tile.o: /usr/include/sys/_types/_timeval.h
.o/thing_tile.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/thing_tile.o: /usr/include/sys/_endian.h
.o/thing_tile.o: /usr/include/libkern/_OSByteOrder.h
.o/thing_tile.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/thing_tile.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/thing_tile.o: /usr/include/sys/_types/_rune_t.h
.o/thing_tile.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int8_t.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/thing_tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/thing_tile.o: /usr/include/sys/_types/_dev_t.h
.o/thing_tile.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/thing_tile.o: my_thing_template.h my_thing.h my_time_util.h
.o/thing_tile.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_tile.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_tile.o: /usr/include/sys/_types/_seek_set.h
.o/thing_tile.o: /usr/include/sys/_types/_gid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_tile.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/thing_tile.o: /usr/include/sys/_types/_timespec.h
.o/thing_tile.o: /usr/include/sys/_types/_time_t.h
.o/thing_tile.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_set.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_copy.h
.o/thing_tile.o: /usr/include/sys/_select.h /usr/include/sys/_types/_uuid_t.h
.o/thing_tile.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/thing_tile.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/thing_tile.o: /usr/include/sys/_types/_clock_t.h my_sdl.h my_game.h
.o/thing_tile.o: my_dmap.h my_tile.h ./my_sdl.h my_tile_private.h my_glapi.h
.o/thing_tile.o: my_string.h my_enum.h /usr/include/wchar.h
.o/thing_tile.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/thing_tile.o: /usr/include/sys/_types/_wint_t.h
.o/thing_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_tile.o: /usr/include/runetype.h my_thing_tile.h my_python.h
.o/tile.o: my_glapi.h /usr/include/stdlib.h /usr/include/Availability.h
.o/tile.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/tile.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/tile.o: /usr/include/sys/_symbol_aliasing.h
.o/tile.o: /usr/include/sys/_posix_availability.h
.o/tile.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/tile.o: /usr/include/sys/_pthread/_pthread_types.h /usr/include/sys/wait.h
.o/tile.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/tile.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/tile.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/tile.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/tile.o: /usr/include/mach/i386/_structs.h
.o/tile.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/tile.o: /usr/include/sys/_types/_sigaltstack.h
.o/tile.o: /usr/include/sys/_types/_ucontext.h
.o/tile.o: /usr/include/sys/_types/_sigset_t.h
.o/tile.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
.o/tile.o: /usr/include/sys/resource.h /usr/include/stdint.h
.o/tile.o: /usr/include/sys/_types/_int8_t.h
.o/tile.o: /usr/include/sys/_types/_int16_t.h
.o/tile.o: /usr/include/sys/_types/_int32_t.h
.o/tile.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/tile.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tile.o: /usr/include/_types/_uint64_t.h
.o/tile.o: /usr/include/sys/_types/_intptr_t.h
.o/tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/tile.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/tile.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/tile.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/tile.o: /usr/include/libkern/_OSByteOrder.h
.o/tile.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tile.o: /usr/include/sys/_types/_rune_t.h
.o/tile.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_null.h
.o/tile.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/tile.o: /usr/include/sys/_types/_u_int8_t.h
.o/tile.o: /usr/include/sys/_types/_u_int16_t.h
.o/tile.o: /usr/include/sys/_types/_u_int32_t.h
.o/tile.o: /usr/include/sys/_types/_u_int64_t.h
.o/tile.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/tile.o: my_main.h /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tile.o: /usr/include/secure/_common.h /usr/include/assert.h my_pcg_basic.h
.o/tile.o: /usr/include/inttypes.h my_config.h my_color.h my_callstack.h
.o/tile.o: my_ptrcheck.h my_math_util.h /usr/include/math.h my_point.h
.o/tile.o: my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/tile.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/tile.o: /usr/include/sys/_types/_posix_vdisable.h
.o/tile.o: /usr/include/sys/_types/_seek_set.h
.o/tile.o: /usr/include/sys/_types/_gid_t.h
.o/tile.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/tile.o: /usr/include/sys/_types/_fd_def.h
.o/tile.o: /usr/include/sys/_types/_timespec.h
.o/tile.o: /usr/include/sys/_types/_time_t.h
.o/tile.o: /usr/include/sys/_types/_suseconds_t.h
.o/tile.o: /usr/include/sys/_types/_fd_setsize.h
.o/tile.o: /usr/include/sys/_types/_fd_set.h
.o/tile.o: /usr/include/sys/_types/_fd_clr.h
.o/tile.o: /usr/include/sys/_types/_fd_isset.h
.o/tile.o: /usr/include/sys/_types/_fd_zero.h
.o/tile.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/tile.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/tile.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/tile.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/tile.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/tile.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/tile.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/tile.o: /usr/include/ctype.h /usr/include/runetype.h my_tile.h ./my_sdl.h
.o/tile.o: my_tile_private.h my_tex.h my_pixel.h
.o/time.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/time.o: /usr/include/sys/_symbol_aliasing.h
.o/time.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/time.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/time.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/time.o: /usr/include/i386/_types.h
.o/time.o: /usr/include/sys/_pthread/_pthread_types.h
.o/time.o: /usr/include/sys/_types/_va_list.h
.o/time.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/time.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/time.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/time.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/time.o: /usr/include/sys/_types/_int8_t.h
.o/time.o: /usr/include/sys/_types/_int16_t.h
.o/time.o: /usr/include/sys/_types/_int32_t.h
.o/time.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/time.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/time.o: /usr/include/_types/_uint64_t.h
.o/time.o: /usr/include/sys/_types/_intptr_t.h
.o/time.o: /usr/include/sys/_types/_uintptr_t.h
.o/time.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/time.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/time.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/time.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/time.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/time.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/time.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/time.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/time.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/time.o: /usr/include/mach/i386/_structs.h
.o/time.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/time.o: /usr/include/sys/_types/_sigaltstack.h
.o/time.o: /usr/include/sys/_types/_ucontext.h
.o/time.o: /usr/include/sys/_types/_sigset_t.h
.o/time.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/time.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/time.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/time.o: /usr/include/libkern/_OSByteOrder.h
.o/time.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/time.o: /usr/include/sys/_types/_ct_rune_t.h
.o/time.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/time.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/time.o: /usr/include/sys/_types/_u_int16_t.h
.o/time.o: /usr/include/sys/_types/_u_int32_t.h
.o/time.o: /usr/include/sys/_types/_u_int64_t.h
.o/time.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/time.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/time.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/time.o: /usr/include/sys/_types/_posix_vdisable.h
.o/time.o: /usr/include/sys/_types/_seek_set.h
.o/time.o: /usr/include/sys/_types/_gid_t.h
.o/time.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/time.o: /usr/include/sys/_types/_fd_def.h
.o/time.o: /usr/include/sys/_types/_timespec.h
.o/time.o: /usr/include/sys/_types/_time_t.h
.o/time.o: /usr/include/sys/_types/_suseconds_t.h
.o/time.o: /usr/include/sys/_types/_fd_setsize.h
.o/time.o: /usr/include/sys/_types/_fd_set.h
.o/time.o: /usr/include/sys/_types/_fd_clr.h
.o/time.o: /usr/include/sys/_types/_fd_isset.h
.o/time.o: /usr/include/sys/_types/_fd_zero.h
.o/time.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/time.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/time.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/time.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/time.o: my_game.h my_dmap.h
.o/timer.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/timer.o: /usr/include/sys/_symbol_aliasing.h
.o/timer.o: /usr/include/sys/_posix_availability.h
.o/timer.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/timer.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/timer.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/timer.o: /usr/include/sys/_pthread/_pthread_types.h
.o/timer.o: /usr/include/sys/_types/_va_list.h
.o/timer.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/timer.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/timer.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/timer.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/timer.o: /usr/include/sys/_types/_int8_t.h
.o/timer.o: /usr/include/sys/_types/_int16_t.h
.o/timer.o: /usr/include/sys/_types/_int32_t.h
.o/timer.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/timer.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/timer.o: /usr/include/_types/_uint64_t.h
.o/timer.o: /usr/include/sys/_types/_intptr_t.h
.o/timer.o: /usr/include/sys/_types/_uintptr_t.h
.o/timer.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/timer.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/timer.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/timer.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/timer.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/timer.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/timer.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/timer.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/timer.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/timer.o: /usr/include/mach/i386/_structs.h
.o/timer.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/timer.o: /usr/include/sys/_types/_sigaltstack.h
.o/timer.o: /usr/include/sys/_types/_ucontext.h
.o/timer.o: /usr/include/sys/_types/_sigset_t.h
.o/timer.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/timer.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/timer.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/timer.o: /usr/include/libkern/_OSByteOrder.h
.o/timer.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/timer.o: /usr/include/sys/_types/_ct_rune_t.h
.o/timer.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/timer.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/timer.o: /usr/include/sys/_types/_u_int16_t.h
.o/timer.o: /usr/include/sys/_types/_u_int32_t.h
.o/timer.o: /usr/include/sys/_types/_u_int64_t.h
.o/timer.o: /usr/include/sys/_types/_dev_t.h
.o/timer.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/timer.o: my_thing_template.h my_thing.h my_time_util.h
.o/timer.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/timer.o: /usr/include/sys/_types/_posix_vdisable.h
.o/timer.o: /usr/include/sys/_types/_seek_set.h
.o/timer.o: /usr/include/sys/_types/_gid_t.h
.o/timer.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/timer.o: /usr/include/sys/_types/_fd_def.h
.o/timer.o: /usr/include/sys/_types/_timespec.h
.o/timer.o: /usr/include/sys/_types/_time_t.h
.o/timer.o: /usr/include/sys/_types/_suseconds_t.h
.o/timer.o: /usr/include/sys/_types/_fd_setsize.h
.o/timer.o: /usr/include/sys/_types/_fd_set.h
.o/timer.o: /usr/include/sys/_types/_fd_clr.h
.o/timer.o: /usr/include/sys/_types/_fd_isset.h
.o/timer.o: /usr/include/sys/_types/_fd_zero.h
.o/timer.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/timer.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/timer.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/timer.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/timer.o: my_game.h my_dmap.h my_timer.h
.o/token.o: my_slre.h my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/token.o: /usr/include/sys/_symbol_aliasing.h
.o/token.o: /usr/include/sys/_posix_availability.h
.o/token.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/token.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/token.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/token.o: /usr/include/sys/_pthread/_pthread_types.h
.o/token.o: /usr/include/sys/_types/_va_list.h
.o/token.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/token.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/token.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/token.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/token.o: /usr/include/sys/_types/_int8_t.h
.o/token.o: /usr/include/sys/_types/_int16_t.h
.o/token.o: /usr/include/sys/_types/_int32_t.h
.o/token.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/token.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/token.o: /usr/include/_types/_uint64_t.h
.o/token.o: /usr/include/sys/_types/_intptr_t.h
.o/token.o: /usr/include/sys/_types/_uintptr_t.h
.o/token.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/token.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/token.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/token.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/token.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/token.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/token.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/token.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/token.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/token.o: /usr/include/mach/i386/_structs.h
.o/token.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/token.o: /usr/include/sys/_types/_sigaltstack.h
.o/token.o: /usr/include/sys/_types/_ucontext.h
.o/token.o: /usr/include/sys/_types/_sigset_t.h
.o/token.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/token.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/token.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/token.o: /usr/include/libkern/_OSByteOrder.h
.o/token.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/token.o: /usr/include/sys/_types/_ct_rune_t.h
.o/token.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/token.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/token.o: /usr/include/sys/_types/_u_int16_t.h
.o/token.o: /usr/include/sys/_types/_u_int32_t.h
.o/token.o: /usr/include/sys/_types/_u_int64_t.h
.o/token.o: /usr/include/sys/_types/_dev_t.h
.o/token.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/token.o: my_thing_template.h my_thing.h my_time_util.h
.o/token.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/token.o: /usr/include/sys/_types/_posix_vdisable.h
.o/token.o: /usr/include/sys/_types/_seek_set.h
.o/token.o: /usr/include/sys/_types/_gid_t.h
.o/token.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/token.o: /usr/include/sys/_types/_fd_def.h
.o/token.o: /usr/include/sys/_types/_timespec.h
.o/token.o: /usr/include/sys/_types/_time_t.h
.o/token.o: /usr/include/sys/_types/_suseconds_t.h
.o/token.o: /usr/include/sys/_types/_fd_setsize.h
.o/token.o: /usr/include/sys/_types/_fd_set.h
.o/token.o: /usr/include/sys/_types/_fd_clr.h
.o/token.o: /usr/include/sys/_types/_fd_isset.h
.o/token.o: /usr/include/sys/_types/_fd_zero.h
.o/token.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/token.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/token.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/token.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/token.o: my_game.h my_dmap.h my_token.h
.o/ttf.o: my_glapi.h /usr/include/stdlib.h /usr/include/Availability.h
.o/ttf.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ttf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/ttf.o: /usr/include/sys/_symbol_aliasing.h
.o/ttf.o: /usr/include/sys/_posix_availability.h
.o/ttf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_types.h /usr/include/sys/wait.h
.o/ttf.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/ttf.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/ttf.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/ttf.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/ttf.o: /usr/include/mach/i386/_structs.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ttf.o: /usr/include/sys/_types/_sigaltstack.h
.o/ttf.o: /usr/include/sys/_types/_ucontext.h
.o/ttf.o: /usr/include/sys/_types/_sigset_t.h
.o/ttf.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_uid_t.h
.o/ttf.o: /usr/include/sys/resource.h /usr/include/stdint.h
.o/ttf.o: /usr/include/sys/_types/_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/ttf.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ttf.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ttf.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/ttf.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/ttf.o: /usr/include/libkern/_OSByteOrder.h
.o/ttf.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_wchar_t.h /usr/include/sys/_types/_null.h
.o/ttf.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ttf.o: /usr/include/sys/_types/_u_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_u_int64_t.h
.o/ttf.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/ttf.o: my_main.h /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/ttf.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ttf.o: /usr/include/secure/_common.h /usr/include/assert.h my_pcg_basic.h
.o/ttf.o: /usr/include/inttypes.h my_config.h my_color.h my_callstack.h
.o/ttf.o: my_ptrcheck.h my_math_util.h /usr/include/math.h my_point.h
.o/ttf.o: my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/ttf.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/ttf.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ttf.o: /usr/include/sys/_types/_seek_set.h
.o/ttf.o: /usr/include/sys/_types/_gid_t.h
.o/ttf.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/ttf.o: /usr/include/sys/_types/_fd_def.h
.o/ttf.o: /usr/include/sys/_types/_timespec.h
.o/ttf.o: /usr/include/sys/_types/_time_t.h
.o/ttf.o: /usr/include/sys/_types/_suseconds_t.h
.o/ttf.o: /usr/include/sys/_types/_fd_setsize.h
.o/ttf.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/ttf.o: /usr/include/sys/_types/_fd_isset.h
.o/ttf.o: /usr/include/sys/_types/_fd_zero.h
.o/ttf.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ttf.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ttf.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ttf.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/ttf.o: my_game.h my_dmap.h my_string.h my_enum.h /usr/include/wchar.h
.o/ttf.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/ttf.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/ttf.o: /usr/include/ctype.h /usr/include/runetype.h my_wid.h my_timer.h
.o/ttf.o: my_tex.h my_tile.h ./my_sdl.h my_tile_private.h my_ttf.h
.o/ttf.o: my_ramdisk.h my_thing_tile.h my_font.h my_bits.h my_pixel.h
.o/ttf.o: my_stb_image.h
.o/util.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/util.o: /usr/include/sys/_symbol_aliasing.h
.o/util.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/util.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/util.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/util.o: /usr/include/i386/_types.h
.o/util.o: /usr/include/sys/_pthread/_pthread_types.h
.o/util.o: /usr/include/sys/_types/_va_list.h
.o/util.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/util.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/util.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/util.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/util.o: /usr/include/sys/_types/_int8_t.h
.o/util.o: /usr/include/sys/_types/_int16_t.h
.o/util.o: /usr/include/sys/_types/_int32_t.h
.o/util.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/util.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/util.o: /usr/include/_types/_uint64_t.h
.o/util.o: /usr/include/sys/_types/_intptr_t.h
.o/util.o: /usr/include/sys/_types/_uintptr_t.h
.o/util.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/util.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/util.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/util.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/util.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/util.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/util.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/util.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/util.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
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
.o/util.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/util.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/util.o: /usr/include/sys/_types/_u_int16_t.h
.o/util.o: /usr/include/sys/_types/_u_int32_t.h
.o/util.o: /usr/include/sys/_types/_u_int64_t.h
.o/util.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/util.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/util.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/util.o: /usr/include/sys/_types/_posix_vdisable.h
.o/util.o: /usr/include/sys/_types/_seek_set.h
.o/util.o: /usr/include/sys/_types/_gid_t.h
.o/util.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/util.o: /usr/include/sys/_types/_fd_def.h
.o/util.o: /usr/include/sys/_types/_timespec.h
.o/util.o: /usr/include/sys/_types/_time_t.h
.o/util.o: /usr/include/sys/_types/_suseconds_t.h
.o/util.o: /usr/include/sys/_types/_fd_setsize.h
.o/util.o: /usr/include/sys/_types/_fd_set.h
.o/util.o: /usr/include/sys/_types/_fd_clr.h
.o/util.o: /usr/include/sys/_types/_fd_isset.h
.o/util.o: /usr/include/sys/_types/_fd_zero.h
.o/util.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/util.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/util.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/util.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/util.o: my_game.h my_dmap.h
.o/wid.o: my_slre.h my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/wid.o: /usr/include/sys/_symbol_aliasing.h
.o/wid.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/wid.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid.o: /usr/include/i386/_types.h
.o/wid.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid.o: /usr/include/sys/_types/_va_list.h
.o/wid.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/wid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid.o: /usr/include/secure/_common.h /usr/include/stdint.h
.o/wid.o: /usr/include/sys/_types/_int8_t.h
.o/wid.o: /usr/include/sys/_types/_int16_t.h
.o/wid.o: /usr/include/sys/_types/_int32_t.h
.o/wid.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/wid.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/wid.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/wid.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/wid.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/wid.o: my_callstack.h my_ptrcheck.h my_math_util.h /usr/include/math.h
.o/wid.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/wid.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_id_t.h
.o/wid.o: /usr/include/sys/signal.h /usr/include/sys/appleapiopts.h
.o/wid.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/wid.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/wid.o: /usr/include/mach/i386/_structs.h
.o/wid.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/wid.o: /usr/include/sys/_types/_sigaltstack.h
.o/wid.o: /usr/include/sys/_types/_ucontext.h
.o/wid.o: /usr/include/sys/_types/_sigset_t.h
.o/wid.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/wid.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/wid.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/wid.o: /usr/include/libkern/_OSByteOrder.h
.o/wid.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/wid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/wid.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/wid.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/wid.o: my_point.h my_size.h my_thing_template.h my_thing.h my_time_util.h
.o/wid.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/wid.o: /usr/include/sys/_types/_posix_vdisable.h
.o/wid.o: /usr/include/sys/_types/_seek_set.h
.o/wid.o: /usr/include/sys/_types/_gid_t.h
.o/wid.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/wid.o: /usr/include/sys/_types/_fd_def.h
.o/wid.o: /usr/include/sys/_types/_timespec.h
.o/wid.o: /usr/include/sys/_types/_time_t.h
.o/wid.o: /usr/include/sys/_types/_suseconds_t.h
.o/wid.o: /usr/include/sys/_types/_fd_setsize.h
.o/wid.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/wid.o: /usr/include/sys/_types/_fd_isset.h
.o/wid.o: /usr/include/sys/_types/_fd_zero.h
.o/wid.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/wid.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/wid.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/wid.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/wid.o: my_game.h my_dmap.h my_wid.h my_enum.h my_timer.h my_tex.h
.o/wid.o: my_tile.h ./my_sdl.h my_tile_private.h my_glapi.h my_string.h
.o/wid.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/wid.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid.o: /usr/include/runetype.h my_thing_tile.h my_command.h my_token.h
.o/wid.o: my_wid_console.h my_wid_tooltip.h my_sound.h my_wid_tiles.h
.o/wid.o: my_ascii.h
.o/wid_anim.o: my_main.h /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/wid_anim.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_anim.o: /usr/include/sys/_posix_availability.h
.o/wid_anim.o: /usr/include/Availability.h
.o/wid_anim.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_anim.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_anim.o: /usr/include/i386/_types.h
.o/wid_anim.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_anim.o: /usr/include/sys/_types/_va_list.h
.o/wid_anim.o: /usr/include/sys/_types/_size_t.h
.o/wid_anim.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_anim.o: /usr/include/sys/_types/_off_t.h
.o/wid_anim.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_anim.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_anim.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/wid_anim.o: /usr/include/sys/_types/_int16_t.h
.o/wid_anim.o: /usr/include/sys/_types/_int32_t.h
.o/wid_anim.o: /usr/include/sys/_types/_int64_t.h
.o/wid_anim.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/wid_anim.o: /usr/include/_types/_uint32_t.h
.o/wid_anim.o: /usr/include/_types/_uint64_t.h
.o/wid_anim.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_anim.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_anim.o: /usr/include/_types/_intmax_t.h
.o/wid_anim.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/wid_anim.o: my_pcg_basic.h /usr/include/inttypes.h
.o/wid_anim.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/wid_anim.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/wid_anim.o: /usr/include/math.h /usr/include/stdlib.h
.o/wid_anim.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/wid_anim.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/wid_anim.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/wid_anim.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/wid_anim.o: /usr/include/i386/_mcontext.h
.o/wid_anim.o: /usr/include/mach/i386/_structs.h
.o/wid_anim.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/wid_anim.o: /usr/include/sys/_types/_sigaltstack.h
.o/wid_anim.o: /usr/include/sys/_types/_ucontext.h
.o/wid_anim.o: /usr/include/sys/_types/_sigset_t.h
.o/wid_anim.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/wid_anim.o: /usr/include/sys/_types/_timeval.h
.o/wid_anim.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/wid_anim.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/wid_anim.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/wid_anim.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_anim.o: /usr/include/sys/_types/_rune_t.h /usr/include/machine/types.h
.o/wid_anim.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/wid_anim.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_anim.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_anim.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_anim.o: /usr/include/sys/_types/_dev_t.h
.o/wid_anim.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/wid_anim.o: my_thing_template.h my_thing.h my_time_util.h
.o/wid_anim.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/wid_anim.o: /usr/include/sys/_types/_posix_vdisable.h
.o/wid_anim.o: /usr/include/sys/_types/_seek_set.h
.o/wid_anim.o: /usr/include/sys/_types/_gid_t.h
.o/wid_anim.o: /usr/include/sys/_types/_useconds_t.h
.o/wid_anim.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/wid_anim.o: /usr/include/sys/_types/_timespec.h
.o/wid_anim.o: /usr/include/sys/_types/_time_t.h
.o/wid_anim.o: /usr/include/sys/_types/_suseconds_t.h
.o/wid_anim.o: /usr/include/sys/_types/_fd_setsize.h
.o/wid_anim.o: /usr/include/sys/_types/_fd_set.h
.o/wid_anim.o: /usr/include/sys/_types/_fd_clr.h
.o/wid_anim.o: /usr/include/sys/_types/_fd_isset.h
.o/wid_anim.o: /usr/include/sys/_types/_fd_zero.h
.o/wid_anim.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/wid_anim.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/wid_anim.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/wid_anim.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_anim.o: my_sdl.h my_game.h my_dmap.h my_thing_tile.h my_wid.h
.o/wid_anim.o: my_enum.h my_timer.h
.o/wid_console.o: my_sdl.h my_main.h /usr/include/stdio.h
.o/wid_console.o: /usr/include/sys/cdefs.h
.o/wid_console.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_console.o: /usr/include/sys/_posix_availability.h
.o/wid_console.o: /usr/include/Availability.h
.o/wid_console.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_console.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/wid_console.o: /usr/include/i386/_types.h
.o/wid_console.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_console.o: /usr/include/sys/_types/_va_list.h
.o/wid_console.o: /usr/include/sys/_types/_size_t.h
.o/wid_console.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_console.o: /usr/include/sys/_types/_off_t.h
.o/wid_console.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_console.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_console.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/wid_console.o: /usr/include/sys/_types/_int16_t.h
.o/wid_console.o: /usr/include/sys/_types/_int32_t.h
.o/wid_console.o: /usr/include/sys/_types/_int64_t.h
.o/wid_console.o: /usr/include/_types/_uint8_t.h
.o/wid_console.o: /usr/include/_types/_uint16_t.h
.o/wid_console.o: /usr/include/_types/_uint32_t.h
.o/wid_console.o: /usr/include/_types/_uint64_t.h
.o/wid_console.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_console.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_console.o: /usr/include/_types/_intmax_t.h
.o/wid_console.o: /usr/include/_types/_uintmax_t.h /usr/include/assert.h
.o/wid_console.o: my_pcg_basic.h /usr/include/inttypes.h
.o/wid_console.o: /usr/include/sys/_types/_wchar_t.h my_config.h my_color.h
.o/wid_console.o: my_callstack.h my_ptrcheck.h my_math_util.h
.o/wid_console.o: /usr/include/math.h /usr/include/stdlib.h
.o/wid_console.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/wid_console.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/wid_console.o: /usr/include/sys/appleapiopts.h
.o/wid_console.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/wid_console.o: /usr/include/machine/_mcontext.h
.o/wid_console.o: /usr/include/i386/_mcontext.h
.o/wid_console.o: /usr/include/mach/i386/_structs.h
.o/wid_console.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/wid_console.o: /usr/include/sys/_types/_sigaltstack.h
.o/wid_console.o: /usr/include/sys/_types/_ucontext.h
.o/wid_console.o: /usr/include/sys/_types/_sigset_t.h
.o/wid_console.o: /usr/include/sys/_types/_uid_t.h
.o/wid_console.o: /usr/include/sys/resource.h
.o/wid_console.o: /usr/include/sys/_types/_timeval.h
.o/wid_console.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/wid_console.o: /usr/include/sys/_endian.h
.o/wid_console.o: /usr/include/libkern/_OSByteOrder.h
.o/wid_console.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/wid_console.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/wid_console.o: /usr/include/sys/_types/_rune_t.h
.o/wid_console.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid_console.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_console.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_console.o: /usr/include/sys/_types/_dev_t.h
.o/wid_console.o: /usr/include/sys/_types/_mode_t.h my_point.h my_size.h
.o/wid_console.o: my_thing_template.h my_thing.h my_time_util.h
.o/wid_console.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/wid_console.o: /usr/include/sys/_types/_posix_vdisable.h
.o/wid_console.o: /usr/include/sys/_types/_seek_set.h
.o/wid_console.o: /usr/include/sys/_types/_gid_t.h
.o/wid_console.o: /usr/include/sys/_types/_useconds_t.h
.o/wid_console.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/wid_console.o: /usr/include/sys/_types/_timespec.h
.o/wid_console.o: /usr/include/sys/_types/_time_t.h
.o/wid_console.o: /usr/include/sys/_types/_suseconds_t.h
.o/wid_console.o: /usr/include/sys/_types/_fd_setsize.h
.o/wid_console.o: /usr/include/sys/_types/_fd_set.h
.o/wid_console.o: /usr/include/sys/_types/_fd_clr.h
.o/wid_console.o: /usr/include/sys/_types/_fd_isset.h
.o/wid_console.o: /usr/include/sys/_types/_fd_zero.h
.o/wid_console.o: /usr/include/sys/_types/_fd_copy.h
.o/wid_console.o: /usr/include/sys/_select.h
.o/wid_console.o: /usr/include/sys/_types/_uuid_t.h
.o/wid_console.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/wid_console.o: /usr/include/sys/_types/_timeval64.h /usr/include/time.h
.o/wid_console.o: /usr/include/sys/_types/_clock_t.h my_game.h my_dmap.h
.o/wid_console.o: my_slre.h my_wid_console.h my_command.h my_token.h my_ttf.h
.o/wid_console.o: my_enum.h my_string.h /usr/include/wchar.h
.o/wid_console.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/_wctype.h
.o/wid_console.o: /usr/include/sys/_types/_wint_t.h
.o/wid_console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_console.o: /usr/include/runetype.h my_wid.h my_timer.h my_ascii.h
.o/wid_tiles.o: my_glapi.h /usr/include/stdlib.h /usr/include/Availability.h
.o/wid_tiles.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/wid_tiles.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/wid_tiles.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_tiles.o: /usr/include/sys/_posix_availability.h
.o/wid_tiles.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_tiles.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_tiles.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/wid_tiles.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/wid_tiles.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/wid_tiles.o: /usr/include/i386/_mcontext.h
.o/wid_tiles.o: /usr/include/mach/i386/_structs.h
.o/wid_tiles.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_sigaltstack.h
.o/wid_tiles.o: /usr/include/sys/_types/_ucontext.h
.o/wid_tiles.o: /usr/include/sys/_types/_sigset_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_size_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/wid_tiles.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int16_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int32_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_int64_t.h
.o/wid_tiles.o: /usr/include/_types/_uint8_t.h
.o/wid_tiles.o: /usr/include/_types/_uint16_t.h
.o/wid_tiles.o: /usr/include/_types/_uint32_t.h
.o/wid_tiles.o: /usr/include/_types/_uint64_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_intptr_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_tiles.o: /usr/include/_types/_intmax_t.h
.o/wid_tiles.o: /usr/include/_types/_uintmax_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_timeval.h
.o/wid_tiles.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/wid_tiles.o: /usr/include/sys/_endian.h
.o/wid_tiles.o: /usr/include/libkern/_OSByteOrder.h
.o/wid_tiles.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/wid_tiles.o: /usr/include/alloca.h /usr/include/sys/_types/_ct_rune_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_rune_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_wchar_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_null.h /usr/include/machine/types.h
.o/wid_tiles.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_dev_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_mode_t.h my_main.h
.o/wid_tiles.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_tiles.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_tiles.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_tiles.o: /usr/include/assert.h my_pcg_basic.h /usr/include/inttypes.h
.o/wid_tiles.o: my_config.h my_color.h my_callstack.h my_ptrcheck.h
.o/wid_tiles.o: my_math_util.h /usr/include/math.h my_point.h my_size.h
.o/wid_tiles.o: my_thing_template.h my_thing.h my_time_util.h
.o/wid_tiles.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/wid_tiles.o: /usr/include/sys/_types/_posix_vdisable.h
.o/wid_tiles.o: /usr/include/sys/_types/_seek_set.h
.o/wid_tiles.o: /usr/include/sys/_types/_gid_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_useconds_t.h
.o/wid_tiles.o: /usr/include/sys/select.h /usr/include/sys/_types/_fd_def.h
.o/wid_tiles.o: /usr/include/sys/_types/_timespec.h
.o/wid_tiles.o: /usr/include/sys/_types/_time_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_suseconds_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_fd_setsize.h
.o/wid_tiles.o: /usr/include/sys/_types/_fd_set.h
.o/wid_tiles.o: /usr/include/sys/_types/_fd_clr.h
.o/wid_tiles.o: /usr/include/sys/_types/_fd_isset.h
.o/wid_tiles.o: /usr/include/sys/_types/_fd_zero.h
.o/wid_tiles.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/wid_tiles.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/wid_tiles.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/wid_tiles.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_tiles.o: my_sdl.h my_game.h my_dmap.h my_string.h my_enum.h
.o/wid_tiles.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/wid_tiles.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/wid_tiles.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_tiles.o: /usr/include/runetype.h my_wid_tiles.h my_tile.h ./my_sdl.h
.o/wid_tiles.o: my_tile_private.h my_tex.h
