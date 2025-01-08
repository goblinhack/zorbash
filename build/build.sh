#!/bin/bash
#
# Copyright (C) 2014 Neil McGill
#
# This game is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This game is distributed in the hope that it will be fun,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this game; if not, write to the Free
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

. ./build/common.sh

TARGET=zorbash

# The default MINGW32 and MINGW64 environments build binaries using the older
#  MSVCRT library that should be present on all Windows systems.
MINGW_TYPE=mingw64
MINGW_PKG_TYPE=mingw-w64

# The MINGW UCRT environments build binaries using the newer UCRT library that
# is only known to be present on Windows 10. It should produce binaries more
# compatible with MSVC-compiled binaries, but not with the MSVCRT environment.
MINGW_TYPE=ucrt64
MINGW_PKG_TYPE=mingw-w64-ucrt

# Determine OS platform
# https://askubuntu.com/questions/459402/how-to-know-if-the-running-platform-is-ubuntu-or-centos-with-help-of-a-bash-scri
UNAME=$(uname | tr "[:upper:]" "[:lower:]")
# If Linux, try to determine specific distribution
if [ "$UNAME" == "linux" ]; then
    # If available, use LSB to identify distribution
    if [ -f /etc/lsb-release -o -d /etc/lsb-release.d ]; then
        export DISTRO=$(lsb_release -i | cut -d: -f2 | sed s/'^\t'//)
    # Otherwise, use release info file
    else
        export DISTRO=$(ls -d /etc/[A-Za-z]*[_-][rv]e[lr]* | grep -v "lsb" | cut -d'/' -f3 | cut -d'-' -f1 | cut -d'_' -f1)
    fi
fi

# For everything else (or if above failed), just use generic identifier
[ "$DISTRO" == "" ] && export DISTRO=$UNAME
unset UNAME

log_info "Distro                     : $DISTRO"

help_full()
{
    case $(uname) in
    Linux)
      log_warn "For Fedora, you may need to install:"
      log_warn "  dnf install -y findutils"
      log_warn "  dnf install -y SDL2_mixer-devel SDL2_mixer"
      log_warn "  dnf install -y SDL2 SDL2-devel"
      log_warn "  dnf install -y SDL2_image SDL2_image-devel"
      log_warn "  dnf install -y python3"
      log_warn "  dnf install -y python3-devel"
      log_warn "  dnf install -y git"
      log_warn "  dnf install -y make automake gcc-c++"
      log_warn "  dnf install -y vim"
      log_warn "  dnf install -y libmikmod-devel"
      log_warn "  dnf install -y libfishsound-devel"
      log_warn " "
      set -x
      log_warn "Install the following for Ubuntu?"
      apt-get install -y build-essential \
                      g++ \
                      git \
                      libegl1 \
                      libfishsound1-dev \
                      libflac-dev \
                      libfluidsynth-dev \
                      libfreetype6-dev \
                      libgl1 \
                      libglvnd0 \
                      libglx0 \
                      libmikmod-dev \
                      liboggz2-dev \
                      libsdl2-2.0-0 \
                      libsdl2-dev \
                      libsdl2-mixer-2.0-0 \
                      libsdl2-mixer-dev \
                      libsmpeg-dev \
                      libx11-6 \
                      libxext6 \
                      python3 \
                      python3-dev \
                      ssh \
                      vim \
                      xutils-dev
      set +x
      log_warn "Now re-run RUNME"
      ;;
    *MING*|*MSYS*)
      log_warn "Install the following?"
      set -x
      pacman -S git \
        make vim base-devel --needed \
        ${MINGW_PKG_TYPE}-x86_64-SDL \
        ${MINGW_PKG_TYPE}-x86_64-SDL2 \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_gfx \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_image \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_mixer \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_net \
        ${MINGW_PKG_TYPE}-x86_64-SDL2_ttf \
        ${MINGW_PKG_TYPE}-x86_64-ag \
        ${MINGW_PKG_TYPE}-x86_64-binutils \
        ${MINGW_PKG_TYPE}-x86_64-bzip2 \
        ${MINGW_PKG_TYPE}-x86_64-clang \
        ${MINGW_PKG_TYPE}-x86_64-clang-tools-extra \
        ${MINGW_PKG_TYPE}-x86_64-crt-git \
        ${MINGW_PKG_TYPE}-x86_64-expat \
        ${MINGW_PKG_TYPE}-x86_64-flac \
        ${MINGW_PKG_TYPE}-x86_64-fluidsynth \
        ${MINGW_PKG_TYPE}-x86_64-gcc \
        ${MINGW_PKG_TYPE}-x86_64-gcc-libs \
        ${MINGW_PKG_TYPE}-x86_64-gdb \
        ${MINGW_PKG_TYPE}-x86_64-gdbm \
        ${MINGW_PKG_TYPE}-x86_64-gettext \
        ${MINGW_PKG_TYPE}-x86_64-giflib \
        ${MINGW_PKG_TYPE}-x86_64-glib2 \
        ${MINGW_PKG_TYPE}-x86_64-gmp \
        ${MINGW_PKG_TYPE}-x86_64-headers-git \
        ${MINGW_PKG_TYPE}-x86_64-isl \
        ${MINGW_PKG_TYPE}-x86_64-libffi \
        ${MINGW_PKG_TYPE}-x86_64-libiconv \
        ${MINGW_PKG_TYPE}-x86_64-libjpeg-turbo \
        ${MINGW_PKG_TYPE}-x86_64-libmad \
        ${MINGW_PKG_TYPE}-x86_64-libmodplug \
        ${MINGW_PKG_TYPE}-x86_64-libogg \
        ${MINGW_PKG_TYPE}-x86_64-libpng \
        ${MINGW_PKG_TYPE}-x86_64-libsndfile \
        ${MINGW_PKG_TYPE}-x86_64-libsystre \
        ${MINGW_PKG_TYPE}-x86_64-libtiff \
        ${MINGW_PKG_TYPE}-x86_64-libtre-git \
        ${MINGW_PKG_TYPE}-x86_64-libunwind \
        ${MINGW_PKG_TYPE}-x86_64-libvorbis \
        ${MINGW_PKG_TYPE}-x86_64-libwebp \
        ${MINGW_PKG_TYPE}-x86_64-libwinpthread-git \
        ${MINGW_PKG_TYPE}-x86_64-lld \
        ${MINGW_PKG_TYPE}-x86_64-mpc \
        ${MINGW_PKG_TYPE}-x86_64-mpfr \
        ${MINGW_PKG_TYPE}-x86_64-ncurses \
        ${MINGW_PKG_TYPE}-x86_64-openssl \
        ${MINGW_PKG_TYPE}-x86_64-portaudio \
        ${MINGW_PKG_TYPE}-x86_64-python \
        ${MINGW_PKG_TYPE}-x86_64-python-pip \
        ${MINGW_PKG_TYPE}-x86_64-readline \
        ${MINGW_PKG_TYPE}-x86_64-smpeg2 \
        ${MINGW_PKG_TYPE}-x86_64-speex \
        ${MINGW_PKG_TYPE}-x86_64-speexdsp \
        ${MINGW_PKG_TYPE}-x86_64-termcap \
        ${MINGW_PKG_TYPE}-x86_64-windows-default-manifest \
        ${MINGW_PKG_TYPE}-x86_64-winpthreads-git \
        ${MINGW_PKG_TYPE}-x86_64-xz \
        ${MINGW_PKG_TYPE}-x86_64-zlib
      set +x
      log_warn "Now re-run RUNME"
      ;;
    *Darwin*)
      log_warn "Install MAC ports then install:"
      log_warn "  sudo port install libsdl2"
      log_warn "  sudo port install libsdl2_mixer"
      ;;
  esac
}

MY_OS_NAME=$(uname)
case "$MY_OS_NAME" in
    *MING*|*MSYS*)
        for i in \
            $(which sdl2-config) \
            /${MINGW_TYPE}/bin/sdl2-config
        do
            if [ -x "$i" ]; then
                SDL2_CONFIG=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which sdl2-config) \
            /opt/local/bin/sdl2-config \
            /usr/bin/sdl2-config
        do
            if [ -x "$i" ]; then
                SDL2_CONFIG=$i
                break
            fi
        done
    ;;
esac

sdl_help()
{
    log_err "No SDL2 found"
    help_full
    exit 1
}

gcc_help()
{
    log_err "No g++ or clang compiler found"
    help_full
    exit 1
}

SDL2_SCORE=0

if [ "$SDL2_CONFIG" != "" ]; then
    SDL2_INC_PATH=$($SDL2_CONFIG --cflags | sed -e 's/.*-I\([a-zA-Z\/@_0-9:\.]*\) .*/\1/g' -e 's/\-.*//g')

    if [[ "$SDL2_INC_PATH" != "" ]]; then
        find "$SDL2_INC_PATH" | grep -q SDL_mixer.h
        if [ $? -eq 0 ]; then
            SDL2_SCORE=$((SDL2_SCORE + 1))
            SDL2_MIXER=$(find "$SDL2_INC_PATH" -name SDL_mixer.h)
        fi
    fi
fi

log_info "SDL2 config                : $SDL2_CONFIG"
log_info "SDL2 version               : "$($SDL2_CONFIG --version)
log_info "SDL2 libs                  : "$($SDL2_CONFIG --libs)
log_info "SDL2 static libs           : "$($SDL2_CONFIG --static-libs)
log_info "SDL2 cflags                : "$($SDL2_CONFIG --cflags)
log_info "SDL2 prefix                : "$($SDL2_CONFIG --prefix)
log_info "SDL2 exec-prefix           : "$($SDL2_CONFIG --exec-prefix)
log_info "SDL2 include path          : $SDL2_INC_PATH"
log_info "SDL2 mixer.h               : $SDL2_MIXER"
#log_info "SDL2 found                 : $SDL2_SCORE"

if [[ $SDL2_SCORE != "1" ]]; then
    log_err "I need SDL2 and SDL2 mixer installed"
    sdl_help
    exit 1
fi

#
# Gives warnings at runtime on MACOS
#
SDL_LIBS=$($SDL2_CONFIG --libs)
if [ $? -ne 0 ]
then
    log_err "Please install SDL2."
    sdl_help
    exit 1
fi

C_FLAGS=$($SDL2_CONFIG --cflags | sed 's/ \-D_REENTRANT//g')
if [ $? -ne 0 ]
then
    log_err "Please install SDL2."
    sdl_help
    exit 1
fi

#
# -funwind-tables and -rdynamic for backtrace info on linux.
# But it seemed to help little.
#
LDLIBS="$SDL_LIBS"
LDLIBS="$LDLIBS -lSDL2_mixer"

case $MY_OS_NAME in
    *MING*|*MSYS*)
        for i in \
            $(which python3-config) \
            /${MINGW_TYPE}/bin/python3-config
        do
            if [ -x "$i" ]; then
                Python3_CONFIG=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which python3-config) \
            /usr/local/bin/python3-config \
            /usr/bin/python3-config
        do
            if [ -x "$i" ]; then
                Python3_CONFIG=$i
                break
            fi
        done
    ;;
esac

case $MY_OS_NAME in
    *MING*|*MSYS*)
        for i in \
            $(which python3) \
            /${MINGW_TYPE}/bin/python3
        do
            if [ -x "$i" ]; then
                Python3=$i
                break
            fi
        done
    ;;
    *)
        for i in \
            $(which python3) \
            /opt/local/bin/python3 \
            /usr/bin/python3
        do
            if [ -x "$i" ]; then
                Python3=$i
                break
            fi
        done
    ;;
esac

python_help()
{
    log_warn "No python3 found"
    help_full
    exit 1
}

Python3_SCORE=0

if [ "$Python3_CONFIG" != "" ]; then
    Python3_INC_PATH=$($Python3_CONFIG --cflags | sed -e 's/.*-I\([a-zA-Z\/@_0-9:\.]*\) .*/\1/g' -e 's/\-.*//g')

    if [[ "$Python3_INC_PATH" != "" ]]; then
        find "$Python3_INC_PATH" | grep -q Python.h
        if [ $? -eq 0 ]; then
            Python3_SCORE=$((Python3_SCORE + 1))
        fi
    fi
fi

if [[ "$Python3_CONFIG" != "" ]]; then
    log_info "Python3                    : $Python3"
    log_info "Python3 config             : $Python3_CONFIG"
    log_info "Python3 include path       : $Python3_INC_PATH"
    log_info "Python3 prefix             : "$($Python3_CONFIG --prefix)
    log_info "Python3 exec-prefix        : "$($Python3_CONFIG --exec-prefix)
    log_info "Python3 includes           : "$($Python3_CONFIG --includes)
    log_info "Python3 libs               : "$($Python3_CONFIG --libs)
    log_info "Python3 cflags             : "$($Python3_CONFIG --cflags)
    log_info "Python3 ldflags            : "$($Python3_CONFIG --ldflags)
    log_info "Python3 embed              : "$($Python3_CONFIG --embed)
    #log_info "Python3 found              : $Python3_SCORE"
fi

if [[ $Python3_SCORE = "0" ]]; then
    log_err "I need Python3"
    python_help
    exit 1
fi

Python_CONFIG=$Python3_CONFIG
Python=$Python3
PYVER=$($Python --version | sed -e 's/Python //g' -e 's/\.[0-9]*$//g')
echo "PYVER=$PYVER" > build/windows/python.version.sh

log_info "Python lib version         : $PYVER"

/bin/rm -f data/zorbash-hiscore.txt data/zorbash-config.txt

#
# Make the makefile
#
(
cd src || exit
rm -f Makefile
sed '/DO NOT DELETE/,$d' Makefile.base > Makefile.tmp
mv Makefile.tmp Makefile
)

PYTHONPATH=$($Python -c "import os, sys; print(os.pathsep.join(x for x in sys.path if x))")

case "$MY_OS_NAME" in
    *Darwin*)
        echo "$PYTHONPATH" | grep -q -i anaconda
        if [[ $? -eq 0 ]];
        then
          log_info "Python anaconda is installed"
          Python_LIBS=$($Python_CONFIG --ldflags)
          if [ $? -ne 0 ]; then
              log_err "Please install Python 3. $Python_CONFIG failed."
              exit 1
          fi
        else
          log_info "Python anaconda is not installed"
          Python_LIBS=$($Python_CONFIG --ldflags --embed 2>/dev/null)
          if [ $? -ne 0 ]; then
              Python_LIBS=$($Python_CONFIG --ldflags)
              if [ $? -ne 0 ]; then
                  log_err "Please install Python 3. $Python_CONFIG failed."
                  exit 1
              fi
          fi
        fi
      ;;
    *)
        Python_LIBS=$($Python_CONFIG --ldflags --embed 2>/dev/null)
        if [ $? -ne 0 ]; then
            Python_LIBS=$($Python_CONFIG --ldflags)
            if [ $? -ne 0 ]; then
                log_err "Please install Python 3. $Python_CONFIG failed."
                exit 1
            fi
        fi
      ;;
esac

#
# Filter some junk out of the python config that can cause link errors
#
C_FLAGS+=" $($Python_CONFIG --cflags       | \
           tr ' ' '\n' | sort | uniq       | \
           grep  "\-I"                     | \
           tr '\n' ' '                     | \
           sed 's/\-fstack-protector/ /g'  | \
           sed 's/\-arch i386/ /g'           \
           )"
#
# -funwind-tables and -rdynamic for backtrace info on linux.
# But it seemed to help little.
#
LDLIBS="$LDLIBS $Python_LIBS"

#
# Common config file
#
CONFIG_H=src/config.h
echo "#include \"my_config.hpp\"" > $CONFIG_H
C_FLAGS+="-include config.h"

#
# for backtraces, but it doesn't help much
#
case "$MY_OS_NAME" in
    *MSYS*)
        log_err "Please compile for ming64, not msys"
        exit 1
        ;;
    *MING*|*MSYS*)
        PATH=/${MINGW_TYPE}/bin:$PATH
        EXE=".exe"
        C_FLAGS+=" -I/${MINGW_TYPE}/ginclude "
        LDLIBS+=" -L/${MINGW_TYPE}/glib/"
        LDLIBS=$(echo $LDLIBS | sed -e 's/-lmingw32 //g')
        LDLIBS+=" -funwind-tables"
        LDLIBS+=" -static-libstdc++"
        LDLIBS+=" -static-libgcc"
        LDLIBS+=" -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic"
        LDLIBS+=" -lopengl32"
        LDLIBS+=" -lpthread"
        LDLIBS+=" /${MINGW_TYPE}/lib/libSDL2_mixer.a"
        LDLIBS+=" -L/${MINGW_TYPE}/lib/binutils -lbfd -lintl -ldbghelp -liberty -lz"

        if [ -f /${MINGW_TYPE}/lib/libunwind.a ]; then
          echo "#define HAVE_LIBUNWIND" >> $CONFIG_H
          LDLIBS+=" -lunwind"
          log_info "Have libunwind             : Yes"
        else
          log_info "Have libunwind             : No"
        fi

        #
        # Clang supports PDB debug file creation, but you need to do
        # the following to enable it.
        #
        C_FLAGS+=" -g -gcodeview"

        #
        # Needed to create PDB files
        #
        if [ -x /${MINGW_TYPE}/bin/lld ]; then
          LDFLAGS+=" -fuse-ld=lld "
        fi

        #
        # The space after pdb= is intentional to use the executable name for PDB file generation.
        #
        LDFLAGS+=" -g -Wl,--pdb= "
        ;;
    *Darwin*)
        EXE=""
        LDLIBS+=" -funwind-tables"
        LDLIBS+=" -rdynamic"
        LDLIBS+=" -Wl,-framework,Opengl"
        DSYM="dsymutil ../${TARGET}"

        if [[ $OPT_DEV2 != "" ]]; then
            C_FLAGS+=" -fsanitize=address -fno-omit-frame-pointer"
            LDFLAGS+=" -fsanitize=address"
        fi
        ;;
    *inux*)
        EXE=""
        LDFLAGS+=' -rdynamic'
        LDLIBS+="-lGL "

        if [[ $OPT_DEV2 != "" ]]; then
            C_FLAGS+=" -fsanitize=address -fno-omit-frame-pointer -fno-common"
            LDFLAGS+=" -fsanitize=address"
        fi

        pkg-config --print-provides libunwind >/dev/null 2>/dev/null
        if [[ $? -eq 0 ]]; then
          echo "#define HAVE_LIBUNWIND" >> $CONFIG_H
          LDLIBS+=" -lunwind"
          log_info "Have libunwind             : Yes"
        else
          log_info "Have libunwind             : No"
        fi
        ;;
    *)
        EXE=""
        ;;
esac

GCC_WARN=""

#
# Better to leave off for production
#
WERROR=""
if [[ $OPT_DEV1 != "" ]]; then
    WERROR="-Werror"
fi

echo "#define MYVER \"$MYVER\"" >> $CONFIG_H
echo "#define PYVER \"$PYVER\"" >> $CONFIG_H

# log_info "PYVER                      : $PYVER"
# log_info "PYTHONPATH                 : $PYTHONPATH"
log_info "VERSION (game)             : $MYVER"

cd src || exit

# Example timings at -j12
# -O0 138 header cleanup... 91
# -O1                       106
# -O3 155 header cleanup... 109

if [[ $OPT_PROF != "" ]]; then
    C_FLAGS+=" -pg"
    LDFLAGS+=" -pg"
fi

if [[ $OPT_DEV1 != "" ]]; then
    echo "COMPILER_FLAGS=$WERROR $C_FLAGS -g # AUTOGEN" > .Makefile
else
    echo "COMPILER_FLAGS=$WERROR $C_FLAGS -O3 # AUTOGEN" > .Makefile
fi

if [[ $OPT_DEV2 != "" ]]; then
    GCC_STACK_CHECK="-fstack-protector-all -D_FORTIFY_SOURCE=2"
    GCC_STACK_CHECK="-fstack-protector-all"
else
    GCC_STACK_CHECK=
fi

cat >>.Makefile <<%%
CLANG_COMPILER_WARNINGS=-Wall $GCC_WARN -std=c++2a # AUTOGEN
GCC_COMPILER_WARNINGS=-x c++ -Wall $GCC_WARN -std=c++2a $GCC_STACK_CHECK # AUTOGEN
LDFLAGS=$LDFLAGS
%%

GOT_CC=

g++ --version > /dev/null
if [ $? -eq 0 ]
then
    echo "COMPILER_WARNINGS=\$(GCC_COMPILER_WARNINGS) # AUTOGEN" >> .Makefile
    echo "CC=g++ # AUTOGEN" >> .Makefile
    GOT_CC=1
fi

#
# Prefer clang as its faster
#
if [[ $OPT_GCC = "" ]]; then
  clang++ --version > /dev/null
  if [ $? -eq 0 ]; then
      echo "COMPILER_WARNINGS=\$(CLANG_COMPILER_WARNINGS) # AUTOGEN" >> .Makefile
      echo "CC=clang++ # AUTOGEN" >> .Makefile
      GOT_CC=1
  fi
fi

if [[ $GOT_CC = "" ]]; then
    gcc_help
    exit 1
fi

case "$MY_OS_NAME" in
    *MING*|*MSYS*)
        echo "CC=/${MINGW_TYPE}/bin/clang++.exe # AUTOGEN" >> .Makefile
        #
        # To resolve WinMain, add these at the end again
        #
        LDLIBS="$LDLIBS -lmingw32 -lSDL2main -lSDL2 -mwindows /${MINGW_TYPE}/lib/libSDL2main.a -L/${MINGW_TYPE}/lib -lSDL2main -lSDL2"
    ;;
esac

#
# Create the makefile
#
cat >>.Makefile <<%%
EXE=$EXE # AUTOGEN
DSYM=$DSYM # AUTOGEN
LDLIBS=$LDLIBS # AUTOGEN
CFLAGS=\$(COMPILER_FLAGS) \$(COMPILER_WARNINGS) # AUTOGEN
%%

grep -v AUTOGEN Makefile | grep -v "^    $" >> .Makefile

if [ -s .Makefile ]
then
    mv .Makefile Makefile
    if [ ! -f Makefile ]
    then
        log_err "No makefile?!"
        exit 1
    fi
else
    log_err "Makefile create fail?!"
    exit 1
fi

#
# Cleanup pre-build
#
log_info "Cleaning"
make clobber | sed 's/^/  /g'

#
# How many cores?
#
CORES=""

case "$MY_OS_NAME" in
    *Darwin*)
      CORES=$(/usr/sbin/system_profiler -detailLevel full SPHardwareDataType  | grep Cores | sed 's/.*: //g' | awk '{print $1}')
    ;;
    *inux*)
      CORES=$(grep -E -c "cpu cores|processor" /proc/cpuinfo)
    ;;
    *MING*|*MSYS*)
      CORES=$(grep -E -c "cpu cores|processor" /proc/cpuinfo)
    ;;
esac

if [ "$CORES" != "" ]
then
    log_info "Compiling ($CORES cpus)"

    CORES="-j $CORES"
else
    log_info "Compiling"
fi

cd ..

echo make -f build/Makefile $CORES "$@" all
make -f build/Makefile $CORES "$@" all

if [ $? -eq 0 ]
then
    case "$MY_OS_NAME" in
        *MING*|*MSYS*)
            log_info "Run:"

            cat >${TARGET}-create-release.sh <<%%
#!/bin/sh
###############################################################################
# Execute the following to build the release
###############################################################################
#
# Clean up the old installs
#
rm ${TARGET}.*installer.exe

#
# Update the version
#
echo \$0: updating the version to $MYVER
sed -i "s/<version>.*/<version>$MYVER<\/version>/g" build/windows/windows.xml
(cd build/windows/ ; ./windows.sh)


#
# All commits since last tag
#
echo \$0: all commits since last tag
git log \$(git describe --tags --abbrev=0)..HEAD --oneline | grep -E "feat:|bug:" | sort +1 -r

#
# Lay a tag
#
echo \$0: laying a tag
git tag -m "tag: $MYVER" -a v$MYVER
git push origin --tags

echo \$0: all done
%%
            chmod +x ${TARGET}-create-release.sh

            cat >${TARGET}.sh <<%%

#!/bin/sh
###############################################################################
# Execute the following, or run ./${TARGET}.sh
###############################################################################
PYTHONPATH=/${MINGW_TYPE}/lib/python${PYVER}/:/${MINGW_TYPE}/lib/python${PYVER}/lib-dynload:/${MINGW_TYPE}/lib/python${PYVER}/site-packages PYTHONHOME=/${MINGW_TYPE}/bin ./${TARGET}.exe \$*
%%

            cat ${TARGET}.sh
            chmod +x ${TARGET}.sh
            ;;
        Linux)
            if [[ $OPT_GITHUB = "" ]]; then
              ./build/list_monsters.sh ./${TARGET} do-it
              ./build/list_weapons.sh ./${TARGET} do-it
            fi
            log_info "Run:"
            echo "  ./${TARGET}"
            ;;
        *)
            log_info "Run:"
            echo "  ./${TARGET}"
            ;;
    esac

    rm -f Makefile.bak
else
    log_die "Build failed"
    exit 1
fi

exit 0
