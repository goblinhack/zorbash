pre:
	@build/check_files.sh
	@build/ramdisk.py

all: pre
	@if [ ! -f src/Makefile ]; then \
	    (./RUNME;) \
	fi
	(cd src; $(MAKE) $@)

format:
	(cd python/things ; sh ../../build/tidy_python.sh do)
	(cd src ; sh ../build/tidy_source.sh do)
	build/format.sh

tidy:
	build/tidy_source.sh

clean:
	(cd src; $(MAKE) $@)
	/bin/rm -rf data/sounds
	/bin/rm -rf data/gfx

clobber: clean
	(cd src; $(MAKE) $@)

.PHONY: all clean clobber format tidy pre

.DEFAULT_GOAL := all
