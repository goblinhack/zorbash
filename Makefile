pre:
	@build/check_files.sh
	@build/ramdisk.py

DIRS=src

all: pre
	@if [ ! -f src/Makefile ]; then \
	    (./RUNME;) \
	fi
	(cd src; $(MAKE) $@)

format:
	(cd python/things ; sh ../../build/tidy_python.sh do)
	(cd src ; sh ../build/tidy_source.sh do)
	build/format.sh
	build/list_types.sh do

tidy:
	build/tidy_source.sh

clean_files:
	/bin/rm -rf data/sounds/
	/bin/rm -rf data/gfx/
	/bin/rm -rf appdata/
	/bin/rm -f build.log

clean: clean_files
	$(foreach var,$(DIRS), $(MAKE) -C $(var) $@; )

clobber: clean_files
	$(foreach var,$(DIRS), $(MAKE) -C $(var) $@; )

.PHONY: all clean_files clean clobber format pre

.DEFAULT_GOAL := all
