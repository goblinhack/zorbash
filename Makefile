    
CLANG_COMPILER_WARNINGS=-Wall  -std=c++1z -stdlib=libc++ # AUTOGEN
GCC_COMPILER_WARNINGS=-x c++ -Wall -std=c++2a -ffast-math  # AUTOGEN
COMPILER_WARNINGS=$(CLANG_COMPILER_WARNINGS) # AUTOGEN
COMPILER_WARNINGS=$(GCC_COMPILER_WARNINGS) # AUTOGEN
# CC=clang++ # AUTOGEN
CC=g++ # AUTOGEN
CC=/mingw64/bin/x86_64-w64-mingw32-g++.exe # AUTOGEN
    
EXE=.exe # AUTOGEN
DSYM= # AUTOGEN
LDLIBS=-L/mingw64/lib -lSDL2main -lSDL2 -mwindows -lSDL2_mixer -lSDL2_ttf -LC:/msys64/mingw64/lib -lpython3.8 -lm -lversion -lshlwapi -lm -L/mingw64/x86_64-w64-mingw32/lib/ -funwind-tables -static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic -lopengl32 -lpthread /mingw64/lib/libSDL2_mixer.a /mingw64/lib/libSDL2_ttf.a -L/mingw64/lib/binutils -lbfd -lintl -ldbghelp -liberty -lz -lmingw32 -lSDL2main -lSDL2 -mwindows /mingw64/lib/libSDL2main.a -L/mingw64/lib -lSDL2main -lSDL2 # AUTOGEN
CFLAGS=$(COMPILER_FLAGS) $(COMPILER_WARNINGS) # AUTOGEN

all:
	if [ ! -f src/Makefile ]; then \
	    (RUNME;) \
	fi
	(cd src; make $@)

clean:
	(cd src; make $@)

clobber:
	(cd src; make $@)
	rm src/Makefile
# DO NOT DELETE
