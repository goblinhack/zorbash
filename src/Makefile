COMPILER_FLAGS=-Werror -I/opt/local/include/SDL2 -D_THREAD_SAFE -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -I/Library/Frameworks/Python.framework/Versions/3.6/include/python3.6m -Wsign-compare -fno-common -dynamic -DNDEBUG -g -Wall   -arch x86_64 -g  -DVERSION=\"0.0.1\" -I../cereal/include -g -ggdb3 -O2 # AUTOGEN
    
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
    $(OBJDIR)/cereal.o			\
    $(OBJDIR)/command.o 		\
    $(OBJDIR)/dir.o 			\
    $(OBJDIR)/dmap.o 			\
    $(OBJDIR)/file.o 			\
    $(OBJDIR)/font.o 			\
    $(OBJDIR)/game.o 			\
    $(OBJDIR)/gl.o 			\
    $(OBJDIR)/hacklib.o 		\
    $(OBJDIR)/log.o 			\
    $(OBJDIR)/main.o 			\
    $(OBJDIR)/pcg_basic.o 		\
    $(OBJDIR)/pixel.o 			\
    $(OBJDIR)/point.o 			\
    $(OBJDIR)/ptrcheck.o 		\
    $(OBJDIR)/py_sdl.o 			\
    $(OBJDIR)/py_tex.o 			\
    $(OBJDIR)/py_room.o 		\
    $(OBJDIR)/py_tile.o 		\
    $(OBJDIR)/py_tp.o 			\
    $(OBJDIR)/py_ttf.o 			\
    $(OBJDIR)/python.o 			\
    $(OBJDIR)/ramdisk_read.o 		\
    $(OBJDIR)/sdl.o 			\
    $(OBJDIR)/slre.o 			\
    $(OBJDIR)/stb_image.o 		\
    $(OBJDIR)/string.o 			\
    $(OBJDIR)/term.o 		        \
    $(OBJDIR)/tex.o 			\
    $(OBJDIR)/thing.o 			\
    $(OBJDIR)/thing_anim.o 		\
    $(OBJDIR)/thing_map.o 		\
    $(OBJDIR)/thing_template.o 		\
    $(OBJDIR)/thing_tile.o 		\
    $(OBJDIR)/tile.o 			\
    $(OBJDIR)/time.o 			\
    $(OBJDIR)/token.o 			\
    $(OBJDIR)/ttf.o 			\
    $(OBJDIR)/util.o 			\
    $(OBJDIR)/wid.o 			\
    $(OBJDIR)/wid_console.o 		\
    $(OBJDIR)/wid_tiles.o 		\
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

.o/ascii.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ascii.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ascii.o: /usr/include/sys/_posix_availability.h
.o/ascii.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/ascii.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/ascii.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ascii.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ascii.o: /usr/include/sys/_types/_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/ascii.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ascii.o: /usr/include/_types/_uint64_t.h
.o/ascii.o: /usr/include/sys/_types/_intptr_t.h
.o/ascii.o: /usr/include/sys/_types/_uintptr_t.h
.o/ascii.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ascii.o: my_callstack.h /usr/include/stdio.h
.o/ascii.o: /usr/include/sys/_types/_va_list.h
.o/ascii.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/ascii.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/ascii.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/ascii.o: /usr/include/secure/_common.h my_sdl.h my_command.h my_token.h
.o/ascii.o: my_string.h /usr/include/wchar.h
.o/ascii.o: /usr/include/sys/_types/_mbstate_t.h
.o/ascii.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ascii.o: /usr/include/sys/_types/_clock_t.h
.o/ascii.o: /usr/include/sys/_types/_time_t.h
.o/ascii.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/ascii.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/ascii.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/ascii.o: my_math_util.h my_color.h my_tex.h my_slre.h my_time_util.h
.o/ascii.o: /usr/include/assert.h /usr/include/unistd.h
.o/ascii.o: /usr/include/sys/unistd.h
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
.o/ascii.o: my_ttf.h my_enum.h my_font.h my_ascii.h my_game.h my_dmap.h
.o/ascii.o: my_thing.h my_glapi.h /usr/include/string.h
.o/ascii.o: /usr/include/sys/_types/_rsize_t.h
.o/ascii.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ascii.o: /usr/include/secure/_string.h /usr/include/stdlib.h
.o/ascii.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/ascii.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/ascii.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ascii.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/ascii.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ascii.o: /usr/include/sys/_types/_sigaltstack.h
.o/ascii.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
.o/ascii.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/ascii.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/ascii.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/ascii.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/ascii.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii_box.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ascii_box.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ascii_box.o: /usr/include/sys/_posix_availability.h
.o/ascii_box.o: /usr/include/Availability.h
.o/ascii_box.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ascii_box.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ascii_box.o: /usr/include/i386/_types.h
.o/ascii_box.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii_box.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ascii_box.o: /usr/include/sys/_types/_int8_t.h
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
.o/ascii_box.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ascii_box.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/ascii_box.o: /usr/include/sys/_types/_size_t.h
.o/ascii_box.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ascii_box.o: /usr/include/sys/_types/_off_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ssize_t.h
.o/ascii_box.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ascii_box.o: my_sdl.h my_command.h my_token.h my_string.h
.o/ascii_box.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/ascii_box.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii_box.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ascii_box.o: /usr/include/sys/_types/_clock_t.h
.o/ascii_box.o: /usr/include/sys/_types/_time_t.h
.o/ascii_box.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii_box.o: /usr/include/sys/_types/_wint_t.h
.o/ascii_box.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii_box.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/ascii_box.o: my_ptrcheck.h my_tile.h my_config.h my_point.h my_math_util.h
.o/ascii_box.o: my_color.h my_tex.h my_slre.h my_time_util.h
.o/ascii_box.o: /usr/include/assert.h /usr/include/unistd.h
.o/ascii_box.o: /usr/include/sys/unistd.h
.o/ascii_box.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii_box.o: /usr/include/sys/_types/_seek_set.h
.o/ascii_box.o: /usr/include/sys/_types/_uid_t.h
.o/ascii_box.o: /usr/include/sys/_types/_gid_t.h
.o/ascii_box.o: /usr/include/sys/_types/_pid_t.h
.o/ascii_box.o: /usr/include/sys/_types/_useconds_t.h
.o/ascii_box.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_def.h
.o/ascii_box.o: /usr/include/sys/_types/_timeval.h
.o/ascii_box.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii_box.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_set.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii_box.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/ascii_box.o: /usr/include/sys/_types/_dev_t.h
.o/ascii_box.o: /usr/include/sys/_types/_mode_t.h
.o/ascii_box.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/ascii_box.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/ascii_box.o: my_ttf.h my_enum.h my_font.h my_ascii.h /usr/include/string.h
.o/ascii_box.o: /usr/include/sys/_types/_rsize_t.h
.o/ascii_box.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ascii_box.o: /usr/include/secure/_string.h /usr/include/stdlib.h
.o/ascii_box.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/ascii_box.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/ascii_box.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/ascii_box.o: /usr/include/i386/_mcontext.h
.o/ascii_box.o: /usr/include/mach/i386/_structs.h
.o/ascii_box.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ascii_box.o: /usr/include/sys/_types/_sigaltstack.h
.o/ascii_box.o: /usr/include/sys/_types/_ucontext.h
.o/ascii_box.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
.o/ascii_box.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/ascii_box.o: /usr/include/libkern/_OSByteOrder.h
.o/ascii_box.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/ascii_box.o: /usr/include/alloca.h /usr/include/machine/types.h
.o/ascii_box.o: /usr/include/i386/types.h /usr/include/sys/_types/_u_int8_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii_box.o: /usr/include/sys/_types/_u_int64_t.h
.o/ascii_button.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ascii_button.o: /usr/include/sys/cdefs.h
.o/ascii_button.o: /usr/include/sys/_symbol_aliasing.h
.o/ascii_button.o: /usr/include/sys/_posix_availability.h
.o/ascii_button.o: /usr/include/Availability.h
.o/ascii_button.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ascii_button.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ascii_button.o: /usr/include/i386/_types.h
.o/ascii_button.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ascii_button.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ascii_button.o: /usr/include/sys/_types/_int8_t.h
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
.o/ascii_button.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ascii_button.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/ascii_button.o: /usr/include/sys/_types/_size_t.h
.o/ascii_button.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ascii_button.o: /usr/include/sys/_types/_off_t.h
.o/ascii_button.o: /usr/include/sys/_types/_ssize_t.h
.o/ascii_button.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ascii_button.o: my_sdl.h my_command.h my_token.h my_string.h
.o/ascii_button.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/ascii_button.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ascii_button.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ascii_button.o: /usr/include/sys/_types/_clock_t.h
.o/ascii_button.o: /usr/include/sys/_types/_time_t.h
.o/ascii_button.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ascii_button.o: /usr/include/sys/_types/_wint_t.h
.o/ascii_button.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ascii_button.o: /usr/include/runetype.h my_thing_template.h
.o/ascii_button.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h
.o/ascii_button.o: my_point.h my_math_util.h my_color.h my_tex.h my_slre.h
.o/ascii_button.o: my_time_util.h /usr/include/assert.h /usr/include/unistd.h
.o/ascii_button.o: /usr/include/sys/unistd.h
.o/ascii_button.o: /usr/include/sys/_types/_posix_vdisable.h
.o/ascii_button.o: /usr/include/sys/_types/_seek_set.h
.o/ascii_button.o: /usr/include/sys/_types/_uid_t.h
.o/ascii_button.o: /usr/include/sys/_types/_gid_t.h
.o/ascii_button.o: /usr/include/sys/_types/_pid_t.h
.o/ascii_button.o: /usr/include/sys/_types/_useconds_t.h
.o/ascii_button.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_def.h
.o/ascii_button.o: /usr/include/sys/_types/_timeval.h
.o/ascii_button.o: /usr/include/sys/_types/_suseconds_t.h
.o/ascii_button.o: /usr/include/sys/_types/_sigset_t.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_setsize.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_set.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_clr.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_isset.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_zero.h
.o/ascii_button.o: /usr/include/sys/_types/_fd_copy.h
.o/ascii_button.o: /usr/include/sys/_select.h
.o/ascii_button.o: /usr/include/sys/_types/_dev_t.h
.o/ascii_button.o: /usr/include/sys/_types/_mode_t.h
.o/ascii_button.o: /usr/include/sys/_types/_uuid_t.h
.o/ascii_button.o: /usr/include/gethostuuid.h /usr/include/sys/time.h
.o/ascii_button.o: /usr/include/sys/_types/_timeval64.h my_ttf.h my_enum.h
.o/ascii_button.o: my_font.h my_ascii.h /usr/include/string.h
.o/ascii_button.o: /usr/include/sys/_types/_rsize_t.h
.o/ascii_button.o: /usr/include/sys/_types/_errno_t.h /usr/include/strings.h
.o/ascii_button.o: /usr/include/secure/_string.h /usr/include/stdlib.h
.o/ascii_button.o: /usr/include/sys/wait.h /usr/include/sys/_types/_id_t.h
.o/ascii_button.o: /usr/include/sys/signal.h /usr/include/machine/signal.h
.o/ascii_button.o: /usr/include/i386/signal.h
.o/ascii_button.o: /usr/include/machine/_mcontext.h
.o/ascii_button.o: /usr/include/i386/_mcontext.h
.o/ascii_button.o: /usr/include/mach/i386/_structs.h
.o/ascii_button.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/ascii_button.o: /usr/include/sys/_types/_sigaltstack.h
.o/ascii_button.o: /usr/include/sys/_types/_ucontext.h
.o/ascii_button.o: /usr/include/sys/resource.h /usr/include/machine/endian.h
.o/ascii_button.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/ascii_button.o: /usr/include/libkern/_OSByteOrder.h
.o/ascii_button.o: /usr/include/libkern/i386/_OSByteOrder.h
.o/ascii_button.o: /usr/include/alloca.h /usr/include/machine/types.h
.o/ascii_button.o: /usr/include/i386/types.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int8_t.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int16_t.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int32_t.h
.o/ascii_button.o: /usr/include/sys/_types/_u_int64_t.h
.o/backtrace.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/backtrace.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/backtrace.o: /usr/include/sys/_posix_availability.h
.o/backtrace.o: /usr/include/Availability.h
.o/backtrace.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/backtrace.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/backtrace.o: /usr/include/i386/_types.h
.o/backtrace.o: /usr/include/sys/_pthread/_pthread_types.h
.o/backtrace.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/backtrace.o: /usr/include/sys/_types/_int8_t.h
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
.o/backtrace.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/backtrace.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/backtrace.o: /usr/include/sys/_types/_size_t.h
.o/backtrace.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/backtrace.o: /usr/include/sys/_types/_off_t.h
.o/backtrace.o: /usr/include/sys/_types/_ssize_t.h
.o/backtrace.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/backtrace.o: my_backtrace.h /usr/include/stdlib.h /usr/include/sys/wait.h
.o/backtrace.o: /usr/include/sys/_types/_pid_t.h
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
.o/backtrace.o: /usr/include/sys/_types/_mode_t.h /usr/include/execinfo.h
.o/backtrace.o: /usr/include/cxxabi.h /usr/include/stddef.h
.o/backtrace.o: /usr/include/sys/_types/_offsetof.h
.o/backtrace.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/backtrace.o: /usr/include/sys/_types/_rsize_t.h
.o/backtrace.o: /usr/include/sys/_types/_wint_t.h
.o/backtrace.o: /usr/include/__cxxabi_config.h
.o/cereal.o: my_ptrcheck.h my_game.h my_sdl.h my_command.h my_token.h
.o/cereal.o: my_string.h /usr/include/wchar.h /usr/include/_types.h
.o/cereal.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/cereal.o: /usr/include/sys/_symbol_aliasing.h
.o/cereal.o: /usr/include/sys/_posix_availability.h
.o/cereal.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/cereal.o: /usr/include/sys/_pthread/_pthread_types.h
.o/cereal.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/cereal.o: /usr/include/sys/_types/_null.h
.o/cereal.o: /usr/include/sys/_types/_size_t.h
.o/cereal.o: /usr/include/sys/_types/_mbstate_t.h
.o/cereal.o: /usr/include/sys/_types/_ct_rune_t.h
.o/cereal.o: /usr/include/sys/_types/_rune_t.h
.o/cereal.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/cereal.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/cereal.o: /usr/include/sys/_types/_off_t.h
.o/cereal.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/cereal.o: /usr/include/secure/_common.h /usr/include/time.h
.o/cereal.o: /usr/include/sys/_types/_clock_t.h
.o/cereal.o: /usr/include/sys/_types/_time_t.h
.o/cereal.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/cereal.o: /usr/include/sys/_types/_wint_t.h
.o/cereal.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/cereal.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/cereal.o: my_tile.h my_config.h my_point.h my_math_util.h my_color.h
.o/cereal.o: my_tex.h my_slre.h my_dmap.h my_thing.h my_time_util.h
.o/cereal.o: /usr/include/assert.h /usr/include/unistd.h
.o/cereal.o: /usr/include/sys/unistd.h
.o/cereal.o: /usr/include/sys/_types/_posix_vdisable.h
.o/cereal.o: /usr/include/sys/_types/_seek_set.h
.o/cereal.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_uid_t.h
.o/cereal.o: /usr/include/sys/_types/_gid_t.h
.o/cereal.o: /usr/include/sys/_types/_intptr_t.h
.o/cereal.o: /usr/include/sys/_types/_pid_t.h
.o/cereal.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/cereal.o: /usr/include/sys/appleapiopts.h
.o/cereal.o: /usr/include/sys/_types/_fd_def.h
.o/cereal.o: /usr/include/sys/_types/_timeval.h
.o/cereal.o: /usr/include/sys/_types/_suseconds_t.h
.o/cereal.o: /usr/include/sys/_types/_sigset_t.h
.o/cereal.o: /usr/include/sys/_types/_fd_setsize.h
.o/cereal.o: /usr/include/sys/_types/_fd_set.h
.o/cereal.o: /usr/include/sys/_types/_fd_clr.h
.o/cereal.o: /usr/include/sys/_types/_fd_isset.h
.o/cereal.o: /usr/include/sys/_types/_fd_zero.h
.o/cereal.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/cereal.o: /usr/include/sys/_types/_dev_t.h
.o/cereal.o: /usr/include/sys/_types/_mode_t.h
.o/cereal.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/cereal.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/cereal.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/cereal.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/cereal.o: /usr/include/sys/_types/_int16_t.h
.o/cereal.o: /usr/include/sys/_types/_int32_t.h
.o/cereal.o: /usr/include/sys/_types/_int64_t.h
.o/cereal.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/cereal.o: /usr/include/_types/_uint32_t.h
.o/cereal.o: /usr/include/sys/_types/_uintptr_t.h
.o/cereal.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/cereal.o: my_callstack.h
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
.o/color.o: /usr/include/sys/_types/_intptr_t.h
.o/color.o: /usr/include/sys/_types/_uintptr_t.h
.o/color.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/color.o: my_callstack.h /usr/include/stdio.h
.o/color.o: /usr/include/sys/_types/_va_list.h
.o/color.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/color.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/color.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/color.o: /usr/include/secure/_common.h my_color.h my_glapi.h my_string.h
.o/color.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/color.o: /usr/include/sys/_types/_ct_rune_t.h
.o/color.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/color.o: /usr/include/sys/_types/_clock_t.h
.o/color.o: /usr/include/sys/_types/_time_t.h
.o/color.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/color.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/color.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/color.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/color.o: my_math_util.h my_tex.h /usr/include/stdlib.h
.o/color.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/color.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/color.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/color.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/color.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
.o/color.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/color.o: /usr/include/sys/_types/_sigaltstack.h
.o/color.o: /usr/include/sys/_types/_ucontext.h
.o/color.o: /usr/include/sys/_types/_sigset_t.h
.o/color.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/resource.h
.o/color.o: /usr/include/sys/_types/_timeval.h /usr/include/machine/endian.h
.o/color.o: /usr/include/i386/endian.h /usr/include/sys/_endian.h
.o/color.o: /usr/include/libkern/_OSByteOrder.h
.o/color.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/color.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/color.o: /usr/include/sys/_types/_u_int8_t.h
.o/color.o: /usr/include/sys/_types/_u_int16_t.h
.o/color.o: /usr/include/sys/_types/_u_int32_t.h
.o/color.o: /usr/include/sys/_types/_u_int64_t.h
.o/color.o: /usr/include/sys/_types/_dev_t.h
.o/color.o: /usr/include/sys/_types/_mode_t.h
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
.o/command.o: /usr/include/sys/_types/_dev_t.h my_main.h my_pcg_basic.h
.o/command.o: /usr/include/inttypes.h my_callstack.h /usr/include/stdio.h
.o/command.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/command.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/command.o: /usr/include/secure/_common.h my_command.h my_token.h
.o/command.o: my_string.h /usr/include/wchar.h
.o/command.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/time.h
.o/command.o: /usr/include/sys/_types/_clock_t.h
.o/command.o: /usr/include/sys/_types/_time_t.h /usr/include/_wctype.h
.o/command.o: /usr/include/sys/_types/_wint_t.h
.o/command.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/command.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/command.o: my_ptrcheck.h my_tile.h my_config.h my_point.h my_math_util.h
.o/command.o: my_color.h my_tex.h my_wid.h my_sdl.h my_enum.h my_size.h
.o/command.o: my_wid_tiles.h my_python.h
.o/dir.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
.o/dir.o: /usr/include/sys/_symbol_aliasing.h
.o/dir.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/dir.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/dir.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/dir.o: /usr/include/i386/_types.h
.o/dir.o: /usr/include/sys/_pthread/_pthread_types.h
.o/dir.o: /usr/include/sys/_types/_va_list.h
.o/dir.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/dir.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/dir.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dir.o: /usr/include/secure/_common.h /usr/include/dirent.h
.o/dir.o: /usr/include/sys/dirent.h /usr/include/sys/_types/_ino_t.h
.o/dir.o: /usr/include/sys/param.h /usr/include/sys/types.h
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
.o/dir.o: /usr/include/sys/_types/_dev_t.h
.o/dir.o: /usr/include/sys/_types/_blkcnt_t.h
.o/dir.o: /usr/include/sys/_types/_blksize_t.h
.o/dir.o: /usr/include/sys/_types/_gid_t.h
.o/dir.o: /usr/include/sys/_types/_in_addr_t.h
.o/dir.o: /usr/include/sys/_types/_in_port_t.h
.o/dir.o: /usr/include/sys/_types/_ino64_t.h /usr/include/sys/_types/_key_t.h
.o/dir.o: /usr/include/sys/_types/_mode_t.h
.o/dir.o: /usr/include/sys/_types/_nlink_t.h /usr/include/sys/_types/_id_t.h
.o/dir.o: /usr/include/sys/_types/_pid_t.h /usr/include/sys/_types/_uid_t.h
.o/dir.o: /usr/include/sys/_types/_clock_t.h
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
.o/dir.o: /usr/include/sys/_types/_sigset_t.h /usr/include/unistd.h
.o/dir.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/dir.o: /usr/include/sys/_types/_seek_set.h /usr/include/_types/_uint64_t.h
.o/dir.o: /usr/include/sys/select.h /usr/include/sys/_types/_timespec.h
.o/dir.o: /usr/include/sys/_types/_timeval.h /usr/include/sys/_select.h
.o/dir.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/dir.o: /usr/include/sys/stat.h /usr/include/sys/_types/_s_ifmt.h
.o/dir.o: /usr/include/sys/_types/_filesec_t.h my_main.h my_pcg_basic.h
.o/dir.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/dir.o: /usr/include/stdint.h /usr/include/_types/_uint8_t.h
.o/dir.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/dir.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dir.o: my_callstack.h my_dir.h my_string.h /usr/include/wchar.h
.o/dir.o: /usr/include/sys/_types/_mbstate_t.h
.o/dir.o: /usr/include/sys/_types/_ct_rune_t.h
.o/dir.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/dir.o: /usr/include/_wctype.h /usr/include/sys/_types/_wint_t.h
.o/dir.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/dir.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/dir.o: my_ptrcheck.h my_tile.h my_config.h my_point.h my_math_util.h
.o/dir.o: my_color.h my_tex.h my_ramdisk.h
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
.o/dmap.o: /usr/include/sys/_types/_intptr_t.h
.o/dmap.o: /usr/include/sys/_types/_uintptr_t.h
.o/dmap.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/dmap.o: my_callstack.h /usr/include/stdio.h
.o/dmap.o: /usr/include/sys/_types/_va_list.h
.o/dmap.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/dmap.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/dmap.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/dmap.o: /usr/include/secure/_common.h my_dmap.h my_config.h my_point.h
.o/dmap.o: my_math_util.h
.o/file.o: /usr/include/sys/errno.h /usr/include/sys/cdefs.h
.o/file.o: /usr/include/sys/_symbol_aliasing.h
.o/file.o: /usr/include/sys/_posix_availability.h
.o/file.o: /usr/include/sys/_types/_errno_t.h /usr/include/sys/stat.h
.o/file.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/file.o: /usr/include/i386/_types.h
.o/file.o: /usr/include/sys/_pthread/_pthread_types.h
.o/file.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/file.o: /usr/include/sys/_types/_timespec.h
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
.o/file.o: /usr/include/sys/_types/_ssize_t.h
.o/file.o: /usr/include/sys/_types/_intptr_t.h
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
.o/file.o: /usr/include/sys/_types/_int8_t.h
.o/file.o: /usr/include/sys/_types/_int16_t.h
.o/file.o: /usr/include/sys/_types/_int32_t.h
.o/file.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/file.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/file.o: /usr/include/sys/_types/_uintptr_t.h
.o/file.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/file.o: my_callstack.h /usr/include/stdio.h
.o/file.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/file.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/file.o: my_file.h my_ptrcheck.h
.o/font.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/font.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
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
.o/font.o: /usr/include/sys/_types/_intptr_t.h
.o/font.o: /usr/include/sys/_types/_uintptr_t.h
.o/font.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/font.o: my_callstack.h /usr/include/stdio.h
.o/font.o: /usr/include/sys/_types/_va_list.h
.o/font.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/font.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/font.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/font.o: /usr/include/secure/_common.h my_sdl.h my_command.h my_token.h
.o/font.o: my_string.h /usr/include/wchar.h
.o/font.o: /usr/include/sys/_types/_mbstate_t.h
.o/font.o: /usr/include/sys/_types/_ct_rune_t.h
.o/font.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/font.o: /usr/include/sys/_types/_clock_t.h
.o/font.o: /usr/include/sys/_types/_time_t.h
.o/font.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/font.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/font.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/font.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/font.o: my_math_util.h my_color.h my_tex.h my_slre.h my_ttf.h my_enum.h
.o/font.o: my_font.h
.o/game.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/game.o: /usr/include/sys/_types/_intptr_t.h
.o/game.o: /usr/include/sys/_types/_uintptr_t.h
.o/game.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/game.o: my_callstack.h /usr/include/stdio.h
.o/game.o: /usr/include/sys/_types/_va_list.h
.o/game.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/game.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/game.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/game.o: /usr/include/secure/_common.h my_sdl.h my_command.h my_token.h
.o/game.o: my_string.h /usr/include/wchar.h
.o/game.o: /usr/include/sys/_types/_mbstate_t.h
.o/game.o: /usr/include/sys/_types/_ct_rune_t.h
.o/game.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/game.o: /usr/include/sys/_types/_clock_t.h
.o/game.o: /usr/include/sys/_types/_time_t.h
.o/game.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/game.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/game.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/game.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/game.o: my_math_util.h my_color.h my_tex.h my_slre.h my_game.h my_dmap.h
.o/game.o: my_thing.h my_time_util.h /usr/include/assert.h
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
.o/game.o: my_glapi.h my_python.h my_ascii.h
.o/gl.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/gl.o: /usr/include/sys/_types/_uintptr_t.h /usr/include/_types/_intmax_t.h
.o/gl.o: /usr/include/_types/_uintmax_t.h my_callstack.h /usr/include/stdio.h
.o/gl.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/_types/_size_t.h
.o/gl.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/gl.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
.o/gl.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h my_game.h
.o/gl.o: my_sdl.h my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/gl.o: /usr/include/sys/_types/_mbstate_t.h
.o/gl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/gl.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/gl.o: /usr/include/sys/_types/_clock_t.h /usr/include/sys/_types/_time_t.h
.o/gl.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/gl.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/gl.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/gl.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/gl.o: my_math_util.h my_color.h my_tex.h my_slre.h my_dmap.h my_thing.h
.o/gl.o: my_time_util.h /usr/include/assert.h /usr/include/unistd.h
.o/gl.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
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
.o/gl.o: my_glapi.h
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
.o/hacklib.o: /usr/include/sys/_types/_uintptr_t.h
.o/hacklib.o: /usr/include/_types/_intmax_t.h
.o/hacklib.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/hacklib.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/hacklib.o: /usr/include/sys/_types/_size_t.h
.o/hacklib.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/hacklib.o: /usr/include/sys/_types/_off_t.h
.o/hacklib.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/hacklib.o: /usr/include/secure/_common.h my_hacklib.h
.o/log.o: my_slre.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/log.o: /usr/include/sys/_types/_uintptr_t.h
.o/log.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/log.o: my_callstack.h /usr/include/stdio.h
.o/log.o: /usr/include/sys/_types/_va_list.h
.o/log.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/log.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/log.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/log.o: /usr/include/secure/_common.h my_sdl.h my_command.h my_token.h
.o/log.o: my_string.h /usr/include/wchar.h
.o/log.o: /usr/include/sys/_types/_mbstate_t.h
.o/log.o: /usr/include/sys/_types/_ct_rune_t.h
.o/log.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/log.o: /usr/include/sys/_types/_clock_t.h
.o/log.o: /usr/include/sys/_types/_time_t.h
.o/log.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/log.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/log.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/log.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/log.o: my_math_util.h my_color.h my_tex.h my_backtrace.h
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
.o/log.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/log.o: /usr/include/sys/_types/_u_int8_t.h
.o/log.o: /usr/include/sys/_types/_u_int16_t.h
.o/log.o: /usr/include/sys/_types/_u_int32_t.h
.o/log.o: /usr/include/sys/_types/_u_int64_t.h
.o/log.o: /usr/include/sys/_types/_dev_t.h /usr/include/sys/_types/_mode_t.h
.o/log.o: /usr/include/execinfo.h /usr/include/cxxabi.h /usr/include/stddef.h
.o/log.o: /usr/include/sys/_types/_offsetof.h
.o/log.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/log.o: /usr/include/sys/_types/_rsize_t.h /usr/include/__cxxabi_config.h
.o/log.o: my_wid.h my_enum.h my_size.h my_wid_tiles.h my_time_util.h
.o/log.o: /usr/include/assert.h /usr/include/unistd.h
.o/log.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/log.o: /usr/include/sys/_types/_seek_set.h
.o/log.o: /usr/include/sys/_types/_gid_t.h
.o/log.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/log.o: /usr/include/sys/_types/_fd_def.h
.o/log.o: /usr/include/sys/_types/_suseconds_t.h
.o/log.o: /usr/include/sys/_types/_fd_setsize.h
.o/log.o: /usr/include/sys/_types/_fd_set.h /usr/include/sys/_types/_fd_clr.h
.o/log.o: /usr/include/sys/_types/_fd_isset.h
.o/log.o: /usr/include/sys/_types/_fd_zero.h
.o/log.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/log.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/log.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/log.o: my_wid_console.h my_python.h my_term.h my_thing.h
.o/main.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/main.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/main.o: /usr/include/sys/_posix_availability.h /usr/include/Availability.h
.o/main.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
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
.o/main.o: /usr/include/sys/_types/_intptr_t.h
.o/main.o: /usr/include/sys/_types/_uintptr_t.h
.o/main.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/main.o: my_callstack.h /usr/include/stdio.h
.o/main.o: /usr/include/sys/_types/_va_list.h
.o/main.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/main.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/main.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/main.o: /usr/include/secure/_common.h /usr/include/stdlib.h
.o/main.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/main.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/main.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/main.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/main.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
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
.o/main.o: /usr/include/libgen.h my_slre.h my_python.h my_point.h
.o/main.o: my_math_util.h my_glapi.h my_color.h my_wid.h my_sdl.h
.o/main.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/main.o: /usr/include/sys/_types/_mbstate_t.h /usr/include/time.h
.o/main.o: /usr/include/sys/_types/_clock_t.h /usr/include/_wctype.h
.o/main.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/main.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/main.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_tex.h
.o/main.o: my_enum.h my_size.h my_wid_tiles.h my_wid_console.h my_ttf.h
.o/main.o: my_font.h my_dir.h my_file.h my_ramdisk.h my_term.h
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
.o/ptrcheck.o: my_slre.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ptrcheck.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/ptrcheck.o: /usr/include/sys/_posix_availability.h
.o/ptrcheck.o: /usr/include/Availability.h
.o/ptrcheck.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ptrcheck.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ptrcheck.o: /usr/include/i386/_types.h
.o/ptrcheck.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ptrcheck.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ptrcheck.o: /usr/include/sys/_types/_int8_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int16_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int32_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_int64_t.h
.o/ptrcheck.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/ptrcheck.o: /usr/include/_types/_uint32_t.h
.o/ptrcheck.o: /usr/include/_types/_uint64_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_intptr_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_uintptr_t.h
.o/ptrcheck.o: /usr/include/_types/_intmax_t.h
.o/ptrcheck.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ptrcheck.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/ptrcheck.o: /usr/include/sys/_types/_size_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ptrcheck.o: /usr/include/sys/_types/_off_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_ssize_t.h
.o/ptrcheck.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ptrcheck.o: my_backtrace.h /usr/include/stdlib.h /usr/include/sys/wait.h
.o/ptrcheck.o: /usr/include/sys/_types/_pid_t.h
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
.o/ptrcheck.o: /usr/include/sys/_types/_mode_t.h /usr/include/execinfo.h
.o/ptrcheck.o: /usr/include/cxxabi.h /usr/include/stddef.h
.o/ptrcheck.o: /usr/include/sys/_types/_offsetof.h
.o/ptrcheck.o: /usr/include/sys/_types/_ptrdiff_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_rsize_t.h
.o/ptrcheck.o: /usr/include/sys/_types/_wint_t.h
.o/ptrcheck.o: /usr/include/__cxxabi_config.h my_time_util.h
.o/ptrcheck.o: /usr/include/assert.h /usr/include/unistd.h
.o/ptrcheck.o: /usr/include/sys/unistd.h
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
.o/ptrcheck.o: my_sdl.h my_command.h my_token.h my_string.h
.o/ptrcheck.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/ptrcheck.o: /usr/include/_wctype.h /usr/include/_types/_wctype_t.h
.o/ptrcheck.o: /usr/include/ctype.h /usr/include/runetype.h
.o/ptrcheck.o: my_thing_template.h my_thing_tile.h my_ptrcheck.h my_tile.h
.o/ptrcheck.o: my_config.h my_point.h my_math_util.h my_color.h my_tex.h
.o/py_room.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_room.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_room.o: /usr/include/sys/_posix_availability.h
.o/py_room.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_room.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_room.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_room.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_room.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_room.o: /usr/include/sys/_types/_int8_t.h
.o/py_room.o: /usr/include/sys/_types/_int16_t.h
.o/py_room.o: /usr/include/sys/_types/_int32_t.h
.o/py_room.o: /usr/include/sys/_types/_int64_t.h
.o/py_room.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_room.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_room.o: /usr/include/sys/_types/_intptr_t.h
.o/py_room.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_room.o: /usr/include/_types/_intmax_t.h
.o/py_room.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/py_room.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/py_room.o: /usr/include/sys/_types/_size_t.h
.o/py_room.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_room.o: /usr/include/sys/_types/_off_t.h
.o/py_room.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_room.o: /usr/include/secure/_common.h my_python.h my_point.h
.o/py_room.o: my_math_util.h my_tile.h my_config.h my_color.h my_tex.h
.o/py_room.o: my_thing_template.h my_thing_tile.h my_ptrcheck.h
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
.o/py_sdl.o: /usr/include/sys/_types/_intptr_t.h
.o/py_sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_sdl.o: my_callstack.h /usr/include/stdio.h
.o/py_sdl.o: /usr/include/sys/_types/_va_list.h
.o/py_sdl.o: /usr/include/sys/_types/_size_t.h
.o/py_sdl.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_sdl.o: /usr/include/sys/_types/_off_t.h
.o/py_sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_sdl.o: /usr/include/secure/_common.h my_python.h my_point.h
.o/py_sdl.o: my_math_util.h my_py_sdl.h
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
.o/py_tex.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tex.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tex.o: my_callstack.h /usr/include/stdio.h
.o/py_tex.o: /usr/include/sys/_types/_va_list.h
.o/py_tex.o: /usr/include/sys/_types/_size_t.h
.o/py_tex.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_tex.o: /usr/include/sys/_types/_off_t.h
.o/py_tex.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tex.o: /usr/include/secure/_common.h my_glapi.h my_color.h my_python.h
.o/py_tex.o: my_point.h my_math_util.h my_sdl.h my_command.h my_token.h
.o/py_tex.o: my_string.h /usr/include/wchar.h
.o/py_tex.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_tex.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tex.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/py_tex.o: /usr/include/sys/_types/_clock_t.h
.o/py_tex.o: /usr/include/sys/_types/_time_t.h
.o/py_tex.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_tex.o: /usr/include/sys/_types/_wint_t.h
.o/py_tex.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_tex.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/py_tex.o: my_ptrcheck.h my_tile.h my_config.h my_tex.h my_slre.h
.o/py_tex.o: my_pixel.h
.o/py_tile.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tile.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tile.o: /usr/include/sys/_posix_availability.h
.o/py_tile.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_tile.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_tile.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_tile.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_tile.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_tile.o: /usr/include/sys/_types/_int8_t.h
.o/py_tile.o: /usr/include/sys/_types/_int16_t.h
.o/py_tile.o: /usr/include/sys/_types/_int32_t.h
.o/py_tile.o: /usr/include/sys/_types/_int64_t.h
.o/py_tile.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_tile.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_tile.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tile.o: /usr/include/_types/_intmax_t.h
.o/py_tile.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/py_tile.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/py_tile.o: /usr/include/sys/_types/_size_t.h
.o/py_tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_tile.o: /usr/include/sys/_types/_off_t.h
.o/py_tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tile.o: /usr/include/secure/_common.h my_python.h my_point.h
.o/py_tile.o: my_math_util.h my_tile.h my_config.h my_color.h my_tex.h
.o/py_tile.o: my_thing_template.h my_thing_tile.h my_ptrcheck.h
.o/py_tp.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_tp.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_tp.o: /usr/include/sys/_posix_availability.h
.o/py_tp.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
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
.o/py_tp.o: /usr/include/sys/_types/_intptr_t.h
.o/py_tp.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_tp.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_tp.o: my_callstack.h /usr/include/stdio.h
.o/py_tp.o: /usr/include/sys/_types/_va_list.h
.o/py_tp.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/py_tp.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/py_tp.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_tp.o: /usr/include/secure/_common.h my_python.h my_point.h
.o/py_tp.o: my_math_util.h my_tile.h my_config.h my_color.h my_tex.h
.o/py_tp.o: my_thing_template.h my_thing_tile.h my_ptrcheck.h my_py_tp.h
.o/py_tp.o: my_thing.h my_time_util.h /usr/include/assert.h
.o/py_tp.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/py_tp.o: /usr/include/sys/_types/_posix_vdisable.h
.o/py_tp.o: /usr/include/sys/_types/_seek_set.h
.o/py_tp.o: /usr/include/sys/_types/_uid_t.h /usr/include/sys/_types/_gid_t.h
.o/py_tp.o: /usr/include/sys/_types/_pid_t.h
.o/py_tp.o: /usr/include/sys/_types/_useconds_t.h /usr/include/sys/select.h
.o/py_tp.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/py_tp.o: /usr/include/sys/_types/_timespec.h
.o/py_tp.o: /usr/include/sys/_types/_timeval.h
.o/py_tp.o: /usr/include/sys/_types/_time_t.h
.o/py_tp.o: /usr/include/sys/_types/_suseconds_t.h
.o/py_tp.o: /usr/include/sys/_types/_sigset_t.h
.o/py_tp.o: /usr/include/sys/_types/_fd_setsize.h
.o/py_tp.o: /usr/include/sys/_types/_fd_set.h
.o/py_tp.o: /usr/include/sys/_types/_fd_clr.h
.o/py_tp.o: /usr/include/sys/_types/_fd_isset.h
.o/py_tp.o: /usr/include/sys/_types/_fd_zero.h
.o/py_tp.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/py_tp.o: /usr/include/sys/_types/_dev_t.h
.o/py_tp.o: /usr/include/sys/_types/_mode_t.h
.o/py_tp.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/py_tp.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/py_tp.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_sdl.h
.o/py_tp.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/py_tp.o: /usr/include/sys/_types/_mbstate_t.h
.o/py_tp.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_tp.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/py_tp.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/py_tp.o: /usr/include/ctype.h /usr/include/runetype.h my_slre.h
.o/py_ttf.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/py_ttf.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/py_ttf.o: /usr/include/sys/_posix_availability.h
.o/py_ttf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/py_ttf.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/py_ttf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/py_ttf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/py_ttf.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/py_ttf.o: /usr/include/sys/_types/_int8_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int16_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int32_t.h
.o/py_ttf.o: /usr/include/sys/_types/_int64_t.h
.o/py_ttf.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/py_ttf.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/py_ttf.o: /usr/include/sys/_types/_intptr_t.h
.o/py_ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/py_ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/py_ttf.o: my_callstack.h /usr/include/stdio.h
.o/py_ttf.o: /usr/include/sys/_types/_va_list.h
.o/py_ttf.o: /usr/include/sys/_types/_size_t.h
.o/py_ttf.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/py_ttf.o: /usr/include/sys/_types/_off_t.h
.o/py_ttf.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/py_ttf.o: /usr/include/secure/_common.h my_python.h my_point.h
.o/py_ttf.o: my_math_util.h my_sdl.h my_command.h my_token.h my_string.h
.o/py_ttf.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/py_ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/py_ttf.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/py_ttf.o: /usr/include/sys/_types/_clock_t.h
.o/py_ttf.o: /usr/include/sys/_types/_time_t.h
.o/py_ttf.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/py_ttf.o: /usr/include/sys/_types/_wint_t.h
.o/py_ttf.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/py_ttf.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/py_ttf.o: my_ptrcheck.h my_tile.h my_config.h my_color.h my_tex.h
.o/py_ttf.o: my_slre.h my_font.h my_ttf.h my_enum.h my_ascii.h
.o/python.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/python.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/python.o: /usr/include/sys/_posix_availability.h
.o/python.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/python.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/python.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/python.o: /usr/include/sys/_pthread/_pthread_types.h
.o/python.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/python.o: /usr/include/sys/_types/_int8_t.h
.o/python.o: /usr/include/sys/_types/_int16_t.h
.o/python.o: /usr/include/sys/_types/_int32_t.h
.o/python.o: /usr/include/sys/_types/_int64_t.h
.o/python.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/python.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/python.o: /usr/include/sys/_types/_intptr_t.h
.o/python.o: /usr/include/sys/_types/_uintptr_t.h
.o/python.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/python.o: my_callstack.h /usr/include/stdio.h
.o/python.o: /usr/include/sys/_types/_va_list.h
.o/python.o: /usr/include/sys/_types/_size_t.h
.o/python.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/python.o: /usr/include/sys/_types/_off_t.h
.o/python.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/python.o: /usr/include/secure/_common.h my_python.h my_point.h
.o/python.o: my_math_util.h my_py_tp.h my_py_game.h my_py_sdl.h my_config.h
.o/python.o: my_string.h /usr/include/wchar.h
.o/python.o: /usr/include/sys/_types/_mbstate_t.h
.o/python.o: /usr/include/sys/_types/_ct_rune_t.h
.o/python.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/python.o: /usr/include/sys/_types/_clock_t.h
.o/python.o: /usr/include/sys/_types/_time_t.h
.o/python.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/python.o: /usr/include/sys/_types/_wint_t.h
.o/python.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/python.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/python.o: my_ptrcheck.h my_tile.h my_color.h my_tex.h my_wid.h my_sdl.h
.o/python.o: my_command.h my_token.h my_slre.h my_enum.h my_size.h
.o/python.o: my_wid_tiles.h my_ascii.h
.o/ramdisk_read.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/ramdisk_read.o: /usr/include/sys/cdefs.h
.o/ramdisk_read.o: /usr/include/sys/_symbol_aliasing.h
.o/ramdisk_read.o: /usr/include/sys/_posix_availability.h
.o/ramdisk_read.o: /usr/include/Availability.h
.o/ramdisk_read.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/ramdisk_read.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/ramdisk_read.o: /usr/include/i386/_types.h
.o/ramdisk_read.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ramdisk_read.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/ramdisk_read.o: /usr/include/sys/_types/_int8_t.h
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
.o/ramdisk_read.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/ramdisk_read.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/ramdisk_read.o: /usr/include/sys/_types/_size_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/ramdisk_read.o: /usr/include/sys/_types/_off_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_ssize_t.h
.o/ramdisk_read.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ramdisk_read.o: my_string.h /usr/include/wchar.h
.o/ramdisk_read.o: /usr/include/sys/_types/_mbstate_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/ramdisk_read.o: /usr/include/sys/_types/_clock_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_time_t.h
.o/ramdisk_read.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ramdisk_read.o: /usr/include/sys/_types/_wint_t.h
.o/ramdisk_read.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/ramdisk_read.o: /usr/include/runetype.h my_thing_template.h
.o/ramdisk_read.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h
.o/ramdisk_read.o: my_point.h my_math_util.h my_color.h my_tex.h my_file.h
.o/sdl.o: my_glapi.h my_color.h my_time_util.h /usr/include/assert.h
.o/sdl.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/sdl.o: /usr/include/sys/_posix_availability.h /usr/include/unistd.h
.o/sdl.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/sdl.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/sdl.o: /usr/include/sys/_pthread/_pthread_types.h
.o/sdl.o: /usr/include/sys/unistd.h /usr/include/sys/_types/_posix_vdisable.h
.o/sdl.o: /usr/include/sys/_types/_seek_set.h
.o/sdl.o: /usr/include/sys/_types/_size_t.h /usr/include/_types/_uint64_t.h
.o/sdl.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/sdl.o: /usr/include/sys/_types/_ssize_t.h /usr/include/sys/_types/_uid_t.h
.o/sdl.o: /usr/include/sys/_types/_gid_t.h
.o/sdl.o: /usr/include/sys/_types/_intptr_t.h
.o/sdl.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_pid_t.h
.o/sdl.o: /usr/include/sys/_types/_useconds_t.h
.o/sdl.o: /usr/include/sys/_types/_null.h /usr/include/sys/select.h
.o/sdl.o: /usr/include/sys/appleapiopts.h /usr/include/sys/_types/_fd_def.h
.o/sdl.o: /usr/include/sys/_types/_timespec.h
.o/sdl.o: /usr/include/sys/_types/_timeval.h
.o/sdl.o: /usr/include/sys/_types/_time_t.h
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
.o/sdl.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h my_main.h
.o/sdl.o: my_pcg_basic.h /usr/include/inttypes.h
.o/sdl.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/sdl.o: /usr/include/sys/_types/_int8_t.h
.o/sdl.o: /usr/include/sys/_types/_int16_t.h
.o/sdl.o: /usr/include/sys/_types/_int32_t.h
.o/sdl.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/sdl.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/sdl.o: /usr/include/sys/_types/_uintptr_t.h
.o/sdl.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/sdl.o: my_callstack.h /usr/include/stdio.h
.o/sdl.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/sdl.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h my_sdl.h
.o/sdl.o: my_command.h my_token.h my_string.h /usr/include/wchar.h
.o/sdl.o: /usr/include/sys/_types/_mbstate_t.h
.o/sdl.o: /usr/include/sys/_types/_ct_rune_t.h
.o/sdl.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/sdl.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/sdl.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/sdl.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/sdl.o: my_math_util.h my_tex.h my_slre.h my_ttf.h my_enum.h my_font.h
.o/sdl.o: my_term.h my_python.h my_game.h my_dmap.h my_thing.h my_wid.h
.o/sdl.o: my_size.h my_wid_tiles.h
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
.o/stb_image.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/stb_image.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
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
.o/stb_image.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/stb_image.o: /usr/include/stdlib.h /usr/include/sys/wait.h
.o/stb_image.o: /usr/include/sys/_types/_pid_t.h
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
.o/stb_image.o: /usr/include/sys/_types/_mode_t.h /usr/include/math.h
.o/string.o: /usr/include/libgen.h /usr/include/sys/cdefs.h
.o/string.o: /usr/include/sys/_symbol_aliasing.h
.o/string.o: /usr/include/sys/_posix_availability.h
.o/string.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/string.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/string.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/string.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/string.o: /usr/include/sys/_pthread/_pthread_types.h
.o/string.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/string.o: /usr/include/sys/_types/_int8_t.h
.o/string.o: /usr/include/sys/_types/_int16_t.h
.o/string.o: /usr/include/sys/_types/_int32_t.h
.o/string.o: /usr/include/sys/_types/_int64_t.h
.o/string.o: /usr/include/_types/_uint8_t.h /usr/include/_types/_uint16_t.h
.o/string.o: /usr/include/_types/_uint32_t.h /usr/include/_types/_uint64_t.h
.o/string.o: /usr/include/sys/_types/_intptr_t.h
.o/string.o: /usr/include/sys/_types/_uintptr_t.h
.o/string.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/string.o: my_callstack.h /usr/include/stdio.h
.o/string.o: /usr/include/sys/_types/_va_list.h
.o/string.o: /usr/include/sys/_types/_size_t.h
.o/string.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/string.o: /usr/include/sys/_types/_off_t.h
.o/string.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/string.o: /usr/include/secure/_common.h my_sdl.h my_command.h my_token.h
.o/string.o: my_string.h /usr/include/wchar.h
.o/string.o: /usr/include/sys/_types/_mbstate_t.h
.o/string.o: /usr/include/sys/_types/_ct_rune_t.h
.o/string.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/string.o: /usr/include/sys/_types/_clock_t.h
.o/string.o: /usr/include/sys/_types/_time_t.h
.o/string.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/string.o: /usr/include/sys/_types/_wint_t.h
.o/string.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/string.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/string.o: my_ptrcheck.h my_tile.h my_config.h my_point.h my_math_util.h
.o/string.o: my_color.h my_tex.h my_slre.h my_wid.h my_enum.h my_size.h
.o/string.o: my_wid_tiles.h
.o/term.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
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
.o/term.o: /usr/include/secure/_common.h my_main.h my_pcg_basic.h
.o/term.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/term.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/term.o: /usr/include/sys/_types/_int16_t.h
.o/term.o: /usr/include/sys/_types/_int32_t.h
.o/term.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/term.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/term.o: /usr/include/_types/_uint64_t.h
.o/term.o: /usr/include/sys/_types/_intptr_t.h
.o/term.o: /usr/include/sys/_types/_uintptr_t.h
.o/term.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/term.o: my_callstack.h my_term.h my_string.h /usr/include/wchar.h
.o/term.o: /usr/include/sys/_types/_mbstate_t.h
.o/term.o: /usr/include/sys/_types/_ct_rune_t.h
.o/term.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/term.o: /usr/include/sys/_types/_clock_t.h
.o/term.o: /usr/include/sys/_types/_time_t.h
.o/term.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/term.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/term.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/term.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/term.o: my_math_util.h my_color.h my_tex.h
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
.o/tex.o: /usr/include/secure/_common.h my_glapi.h my_color.h my_tex.h
.o/tex.o: my_ramdisk.h my_pixel.h my_main.h my_pcg_basic.h
.o/tex.o: /usr/include/inttypes.h /usr/include/sys/_types/_wchar_t.h
.o/tex.o: /usr/include/stdint.h /usr/include/sys/_types/_int8_t.h
.o/tex.o: /usr/include/sys/_types/_int16_t.h
.o/tex.o: /usr/include/sys/_types/_int32_t.h
.o/tex.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/tex.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/tex.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/tex.o: /usr/include/sys/_types/_uintptr_t.h
.o/tex.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/tex.o: my_callstack.h my_math_util.h my_string.h /usr/include/wchar.h
.o/tex.o: /usr/include/sys/_types/_mbstate_t.h
.o/tex.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tex.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/tex.o: /usr/include/sys/_types/_clock_t.h
.o/tex.o: /usr/include/sys/_types/_time_t.h
.o/tex.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tex.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/tex.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/tex.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
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
.o/thing.o: /usr/include/sys/_types/_intptr_t.h
.o/thing.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/thing.o: my_callstack.h /usr/include/stdio.h
.o/thing.o: /usr/include/sys/_types/_va_list.h
.o/thing.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/thing.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/thing.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/thing.o: /usr/include/secure/_common.h my_tile.h my_config.h my_point.h
.o/thing.o: my_math_util.h my_color.h my_tex.h my_thing_template.h
.o/thing.o: my_thing_tile.h my_ptrcheck.h my_python.h my_time_util.h
.o/thing.o: /usr/include/assert.h /usr/include/unistd.h
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
.o/thing.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/thing.o: /usr/include/ctype.h /usr/include/runetype.h my_slre.h my_thing.h
.o/thing.o: my_game.h my_dmap.h
.o/thing_anim.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/thing_anim.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_anim.o: /usr/include/_types/_intmax_t.h
.o/thing_anim.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/thing_anim.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_anim.o: /usr/include/sys/_types/_size_t.h
.o/thing_anim.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_anim.o: /usr/include/sys/_types/_off_t.h
.o/thing_anim.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_anim.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_anim.o: my_tile.h my_config.h my_point.h my_math_util.h my_color.h
.o/thing_anim.o: my_tex.h my_thing_template.h my_thing_tile.h my_ptrcheck.h
.o/thing_anim.o: my_time_util.h /usr/include/assert.h /usr/include/unistd.h
.o/thing_anim.o: /usr/include/sys/unistd.h
.o/thing_anim.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_anim.o: /usr/include/sys/_types/_seek_set.h
.o/thing_anim.o: /usr/include/sys/_types/_uid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_gid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_pid_t.h
.o/thing_anim.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_anim.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
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
.o/thing_anim.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_anim.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_anim.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_anim.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_anim.o: /usr/include/sys/_types/_wint_t.h
.o/thing_anim.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_anim.o: /usr/include/runetype.h my_slre.h my_thing.h
.o/thing_map.o: my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/thing_map.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/thing_map.o: /usr/include/sys/_posix_availability.h
.o/thing_map.o: /usr/include/Availability.h
.o/thing_map.o: /usr/include/AvailabilityInternal.h /usr/include/_types.h
.o/thing_map.o: /usr/include/sys/_types.h /usr/include/machine/_types.h
.o/thing_map.o: /usr/include/i386/_types.h
.o/thing_map.o: /usr/include/sys/_pthread/_pthread_types.h
.o/thing_map.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/thing_map.o: /usr/include/sys/_types/_int8_t.h
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
.o/thing_map.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/thing_map.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_map.o: /usr/include/sys/_types/_size_t.h
.o/thing_map.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_map.o: /usr/include/sys/_types/_off_t.h
.o/thing_map.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_map.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_map.o: my_python.h my_point.h my_math_util.h my_thing.h my_config.h
.o/thing_map.o: my_thing_template.h my_thing_tile.h my_ptrcheck.h my_tile.h
.o/thing_map.o: my_color.h my_tex.h my_time_util.h /usr/include/assert.h
.o/thing_map.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_map.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_map.o: /usr/include/sys/_types/_seek_set.h
.o/thing_map.o: /usr/include/sys/_types/_uid_t.h
.o/thing_map.o: /usr/include/sys/_types/_gid_t.h
.o/thing_map.o: /usr/include/sys/_types/_pid_t.h
.o/thing_map.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_map.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_map.o: /usr/include/sys/_types/_fd_def.h
.o/thing_map.o: /usr/include/sys/_types/_timespec.h
.o/thing_map.o: /usr/include/sys/_types/_timeval.h
.o/thing_map.o: /usr/include/sys/_types/_time_t.h
.o/thing_map.o: /usr/include/sys/_types/_suseconds_t.h
.o/thing_map.o: /usr/include/sys/_types/_sigset_t.h
.o/thing_map.o: /usr/include/sys/_types/_fd_setsize.h
.o/thing_map.o: /usr/include/sys/_types/_fd_set.h
.o/thing_map.o: /usr/include/sys/_types/_fd_clr.h
.o/thing_map.o: /usr/include/sys/_types/_fd_isset.h
.o/thing_map.o: /usr/include/sys/_types/_fd_zero.h
.o/thing_map.o: /usr/include/sys/_types/_fd_copy.h /usr/include/sys/_select.h
.o/thing_map.o: /usr/include/sys/_types/_dev_t.h
.o/thing_map.o: /usr/include/sys/_types/_mode_t.h
.o/thing_map.o: /usr/include/sys/_types/_uuid_t.h /usr/include/gethostuuid.h
.o/thing_map.o: /usr/include/sys/time.h /usr/include/sys/_types/_timeval64.h
.o/thing_map.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_map.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_map.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_map.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_map.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_map.o: /usr/include/sys/_types/_wint_t.h
.o/thing_map.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_map.o: /usr/include/runetype.h my_slre.h
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
.o/thing_template.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_template.o: /usr/include/_types/_intmax_t.h
.o/thing_template.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/thing_template.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_template.o: /usr/include/sys/_types/_size_t.h
.o/thing_template.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_template.o: /usr/include/sys/_types/_off_t.h
.o/thing_template.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_template.o: /usr/include/secure/_stdio.h
.o/thing_template.o: /usr/include/secure/_common.h my_thing_tile.h
.o/thing_template.o: my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/thing_template.o: my_math_util.h my_color.h my_tex.h my_thing_template.h
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
.o/thing_tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/thing_tile.o: /usr/include/_types/_intmax_t.h
.o/thing_tile.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/thing_tile.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/thing_tile.o: /usr/include/sys/_types/_size_t.h
.o/thing_tile.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/thing_tile.o: /usr/include/sys/_types/_off_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ssize_t.h
.o/thing_tile.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/thing_tile.o: my_tile.h my_config.h my_point.h my_math_util.h my_color.h
.o/thing_tile.o: my_tex.h my_thing_template.h my_thing_tile.h my_ptrcheck.h
.o/thing_tile.o: my_thing.h my_time_util.h /usr/include/assert.h
.o/thing_tile.o: /usr/include/unistd.h /usr/include/sys/unistd.h
.o/thing_tile.o: /usr/include/sys/_types/_posix_vdisable.h
.o/thing_tile.o: /usr/include/sys/_types/_seek_set.h
.o/thing_tile.o: /usr/include/sys/_types/_uid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_gid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_pid_t.h
.o/thing_tile.o: /usr/include/sys/_types/_useconds_t.h
.o/thing_tile.o: /usr/include/sys/select.h /usr/include/sys/appleapiopts.h
.o/thing_tile.o: /usr/include/sys/_types/_fd_def.h
.o/thing_tile.o: /usr/include/sys/_types/_timespec.h
.o/thing_tile.o: /usr/include/sys/_types/_timeval.h
.o/thing_tile.o: /usr/include/sys/_types/_time_t.h
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
.o/thing_tile.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/thing_tile.o: my_sdl.h my_command.h my_token.h my_string.h
.o/thing_tile.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/thing_tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/thing_tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/_wctype.h
.o/thing_tile.o: /usr/include/sys/_types/_wint_t.h
.o/thing_tile.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/thing_tile.o: /usr/include/runetype.h my_slre.h my_python.h
.o/tile.o: my_glapi.h my_color.h my_tile.h my_config.h my_point.h
.o/tile.o: my_math_util.h my_tex.h my_thing_template.h my_thing_tile.h
.o/tile.o: my_ptrcheck.h my_pixel.h my_main.h my_pcg_basic.h
.o/tile.o: /usr/include/inttypes.h /usr/include/sys/cdefs.h
.o/tile.o: /usr/include/sys/_symbol_aliasing.h
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
.o/tile.o: /usr/include/sys/_types/_intptr_t.h
.o/tile.o: /usr/include/sys/_types/_uintptr_t.h
.o/tile.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/tile.o: my_callstack.h /usr/include/stdio.h
.o/tile.o: /usr/include/sys/_types/_va_list.h
.o/tile.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/tile.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/tile.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/tile.o: /usr/include/secure/_common.h my_size.h my_string.h
.o/tile.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/tile.o: /usr/include/sys/_types/_ct_rune_t.h
.o/tile.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/tile.o: /usr/include/sys/_types/_clock_t.h
.o/tile.o: /usr/include/sys/_types/_time_t.h
.o/tile.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/tile.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/tile.o: /usr/include/ctype.h /usr/include/runetype.h
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
.o/time.o: /usr/include/sys/_types/_intptr_t.h
.o/time.o: /usr/include/sys/_types/_uintptr_t.h
.o/time.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/time.o: my_callstack.h /usr/include/stdio.h
.o/time.o: /usr/include/sys/_types/_va_list.h
.o/time.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/time.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/time.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/time.o: /usr/include/secure/_common.h my_string.h /usr/include/wchar.h
.o/time.o: /usr/include/sys/_types/_mbstate_t.h
.o/time.o: /usr/include/sys/_types/_ct_rune_t.h
.o/time.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/time.o: /usr/include/sys/_types/_clock_t.h
.o/time.o: /usr/include/sys/_types/_time_t.h
.o/time.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/time.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/time.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/time.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/time.o: my_math_util.h my_color.h my_tex.h my_game.h my_sdl.h my_command.h
.o/time.o: my_token.h my_slre.h my_dmap.h my_thing.h my_time_util.h
.o/time.o: /usr/include/assert.h /usr/include/unistd.h
.o/time.o: /usr/include/sys/unistd.h
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
.o/token.o: my_slre.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
.o/token.o: /usr/include/sys/cdefs.h /usr/include/sys/_symbol_aliasing.h
.o/token.o: /usr/include/sys/_posix_availability.h
.o/token.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/token.o: /usr/include/_types.h /usr/include/sys/_types.h
.o/token.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/token.o: /usr/include/sys/_pthread/_pthread_types.h
.o/token.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdint.h
.o/token.o: /usr/include/sys/_types/_int8_t.h
.o/token.o: /usr/include/sys/_types/_int16_t.h
.o/token.o: /usr/include/sys/_types/_int32_t.h
.o/token.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/token.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/token.o: /usr/include/_types/_uint64_t.h
.o/token.o: /usr/include/sys/_types/_intptr_t.h
.o/token.o: /usr/include/sys/_types/_uintptr_t.h
.o/token.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/token.o: my_callstack.h /usr/include/stdio.h
.o/token.o: /usr/include/sys/_types/_va_list.h
.o/token.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/token.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/token.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/token.o: /usr/include/secure/_common.h my_token.h my_string.h
.o/token.o: /usr/include/wchar.h /usr/include/sys/_types/_mbstate_t.h
.o/token.o: /usr/include/sys/_types/_ct_rune_t.h
.o/token.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/token.o: /usr/include/sys/_types/_clock_t.h
.o/token.o: /usr/include/sys/_types/_time_t.h
.o/token.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/token.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/token.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/token.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/token.o: my_math_util.h my_color.h my_tex.h
.o/ttf.o: my_glapi.h my_color.h my_wid.h my_sdl.h my_command.h my_token.h
.o/ttf.o: my_string.h /usr/include/wchar.h /usr/include/_types.h
.o/ttf.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/ttf.o: /usr/include/sys/_symbol_aliasing.h
.o/ttf.o: /usr/include/sys/_posix_availability.h
.o/ttf.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/ttf.o: /usr/include/sys/_pthread/_pthread_types.h
.o/ttf.o: /usr/include/Availability.h /usr/include/AvailabilityInternal.h
.o/ttf.o: /usr/include/sys/_types/_null.h /usr/include/sys/_types/_size_t.h
.o/ttf.o: /usr/include/sys/_types/_mbstate_t.h
.o/ttf.o: /usr/include/sys/_types/_ct_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_rune_t.h
.o/ttf.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/ttf.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/ttf.o: /usr/include/sys/_types/_off_t.h /usr/include/sys/_types/_ssize_t.h
.o/ttf.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/ttf.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/ttf.o: /usr/include/sys/_types/_time_t.h
.o/ttf.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/ttf.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/ttf.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/ttf.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/ttf.o: my_math_util.h my_tex.h my_slre.h my_enum.h my_size.h
.o/ttf.o: my_wid_tiles.h my_ttf.h my_font.h my_main.h my_pcg_basic.h
.o/ttf.o: /usr/include/inttypes.h /usr/include/stdint.h
.o/ttf.o: /usr/include/sys/_types/_int8_t.h
.o/ttf.o: /usr/include/sys/_types/_int16_t.h
.o/ttf.o: /usr/include/sys/_types/_int32_t.h
.o/ttf.o: /usr/include/sys/_types/_int64_t.h /usr/include/_types/_uint8_t.h
.o/ttf.o: /usr/include/_types/_uint16_t.h /usr/include/_types/_uint32_t.h
.o/ttf.o: /usr/include/_types/_uint64_t.h /usr/include/sys/_types/_intptr_t.h
.o/ttf.o: /usr/include/sys/_types/_uintptr_t.h
.o/ttf.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/ttf.o: my_callstack.h my_ramdisk.h my_time_util.h /usr/include/assert.h
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
.o/ttf.o: my_bits.h my_pixel.h my_stb_image.h
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
.o/util.o: /usr/include/sys/_types/_intptr_t.h
.o/util.o: /usr/include/sys/_types/_uintptr_t.h
.o/util.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/util.o: my_callstack.h /usr/include/stdio.h
.o/util.o: /usr/include/sys/_types/_va_list.h
.o/util.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/util.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/util.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/util.o: /usr/include/secure/_common.h /usr/include/stdlib.h
.o/util.o: /usr/include/sys/wait.h /usr/include/sys/_types/_pid_t.h
.o/util.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/util.o: /usr/include/sys/appleapiopts.h /usr/include/machine/signal.h
.o/util.o: /usr/include/i386/signal.h /usr/include/machine/_mcontext.h
.o/util.o: /usr/include/i386/_mcontext.h /usr/include/mach/i386/_structs.h
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
.o/wid.o: my_slre.h my_main.h my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid.o: /usr/include/_types/_intmax_t.h /usr/include/_types/_uintmax_t.h
.o/wid.o: my_callstack.h /usr/include/stdio.h
.o/wid.o: /usr/include/sys/_types/_va_list.h
.o/wid.o: /usr/include/sys/_types/_size_t.h /usr/include/sys/_types/_null.h
.o/wid.o: /usr/include/sys/stdio.h /usr/include/sys/_types/_off_t.h
.o/wid.o: /usr/include/sys/_types/_ssize_t.h /usr/include/secure/_stdio.h
.o/wid.o: /usr/include/secure/_common.h my_wid.h my_sdl.h my_command.h
.o/wid.o: my_token.h my_string.h /usr/include/wchar.h
.o/wid.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid.o: /usr/include/sys/_types/_rune_t.h /usr/include/time.h
.o/wid.o: /usr/include/sys/_types/_clock_t.h
.o/wid.o: /usr/include/sys/_types/_time_t.h
.o/wid.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid.o: /usr/include/sys/_types/_wint_t.h /usr/include/_types/_wctype_t.h
.o/wid.o: /usr/include/ctype.h /usr/include/runetype.h my_thing_template.h
.o/wid.o: my_thing_tile.h my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/wid.o: my_math_util.h my_color.h my_tex.h my_enum.h my_size.h
.o/wid.o: my_wid_tiles.h my_time_util.h /usr/include/assert.h
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
.o/wid.o: my_wid_console.h my_thing.h my_game.h my_dmap.h my_ascii.h
.o/wid.o: my_glapi.h /usr/include/stdlib.h /usr/include/sys/wait.h
.o/wid.o: /usr/include/sys/_types/_id_t.h /usr/include/sys/signal.h
.o/wid.o: /usr/include/machine/signal.h /usr/include/i386/signal.h
.o/wid.o: /usr/include/machine/_mcontext.h /usr/include/i386/_mcontext.h
.o/wid.o: /usr/include/mach/i386/_structs.h
.o/wid.o: /usr/include/sys/_pthread/_pthread_attr_t.h
.o/wid.o: /usr/include/sys/_types/_sigaltstack.h
.o/wid.o: /usr/include/sys/_types/_ucontext.h /usr/include/sys/resource.h
.o/wid.o: /usr/include/machine/endian.h /usr/include/i386/endian.h
.o/wid.o: /usr/include/sys/_endian.h /usr/include/libkern/_OSByteOrder.h
.o/wid.o: /usr/include/libkern/i386/_OSByteOrder.h /usr/include/alloca.h
.o/wid.o: /usr/include/machine/types.h /usr/include/i386/types.h
.o/wid.o: /usr/include/sys/_types/_u_int8_t.h
.o/wid.o: /usr/include/sys/_types/_u_int16_t.h
.o/wid.o: /usr/include/sys/_types/_u_int32_t.h
.o/wid.o: /usr/include/sys/_types/_u_int64_t.h
.o/wid_console.o: my_sdl.h my_command.h my_token.h my_string.h
.o/wid_console.o: /usr/include/wchar.h /usr/include/_types.h
.o/wid_console.o: /usr/include/sys/_types.h /usr/include/sys/cdefs.h
.o/wid_console.o: /usr/include/sys/_symbol_aliasing.h
.o/wid_console.o: /usr/include/sys/_posix_availability.h
.o/wid_console.o: /usr/include/machine/_types.h /usr/include/i386/_types.h
.o/wid_console.o: /usr/include/sys/_pthread/_pthread_types.h
.o/wid_console.o: /usr/include/Availability.h
.o/wid_console.o: /usr/include/AvailabilityInternal.h
.o/wid_console.o: /usr/include/sys/_types/_null.h
.o/wid_console.o: /usr/include/sys/_types/_size_t.h
.o/wid_console.o: /usr/include/sys/_types/_mbstate_t.h
.o/wid_console.o: /usr/include/sys/_types/_ct_rune_t.h
.o/wid_console.o: /usr/include/sys/_types/_rune_t.h
.o/wid_console.o: /usr/include/sys/_types/_wchar_t.h /usr/include/stdio.h
.o/wid_console.o: /usr/include/sys/_types/_va_list.h /usr/include/sys/stdio.h
.o/wid_console.o: /usr/include/sys/_types/_off_t.h
.o/wid_console.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_console.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_console.o: /usr/include/time.h /usr/include/sys/_types/_clock_t.h
.o/wid_console.o: /usr/include/sys/_types/_time_t.h
.o/wid_console.o: /usr/include/sys/_types/_timespec.h /usr/include/_wctype.h
.o/wid_console.o: /usr/include/sys/_types/_wint_t.h
.o/wid_console.o: /usr/include/_types/_wctype_t.h /usr/include/ctype.h
.o/wid_console.o: /usr/include/runetype.h my_thing_template.h my_thing_tile.h
.o/wid_console.o: my_ptrcheck.h my_tile.h my_config.h my_point.h
.o/wid_console.o: my_math_util.h my_color.h my_tex.h my_slre.h my_main.h
.o/wid_console.o: my_pcg_basic.h /usr/include/inttypes.h
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
.o/wid_console.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_console.o: my_wid_console.h my_wid.h my_enum.h my_size.h
.o/wid_console.o: my_wid_tiles.h my_ttf.h my_font.h my_ascii.h
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
.o/wid_tiles.o: /usr/include/sys/_types/_uintptr_t.h
.o/wid_tiles.o: /usr/include/_types/_intmax_t.h
.o/wid_tiles.o: /usr/include/_types/_uintmax_t.h my_callstack.h
.o/wid_tiles.o: /usr/include/stdio.h /usr/include/sys/_types/_va_list.h
.o/wid_tiles.o: /usr/include/sys/_types/_size_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_null.h /usr/include/sys/stdio.h
.o/wid_tiles.o: /usr/include/sys/_types/_off_t.h
.o/wid_tiles.o: /usr/include/sys/_types/_ssize_t.h
.o/wid_tiles.o: /usr/include/secure/_stdio.h /usr/include/secure/_common.h
.o/wid_tiles.o: my_glapi.h my_color.h my_wid_tiles.h my_tile.h my_config.h
.o/wid_tiles.o: my_point.h my_math_util.h my_tex.h my_thing_template.h
.o/wid_tiles.o: my_thing_tile.h my_ptrcheck.h
