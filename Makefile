pre:
	@scripts/check_files.sh
	@scripts/ramdisk.py

all: pre
	@if [ ! -f src/Makefile ]; then \
	    (RUNME;) \
	fi
	(cd src; $(MAKE) $@)

clean:
	(cd src; $(MAKE) $@)
	/bin/rm -rf data/gfx

clobber:
	(cd src; $(MAKE) $@)
	rm src/Makefile
	/bin/rm -rf data/gfx

.DEFAULT_GOAL := all
