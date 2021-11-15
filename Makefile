pre:
	@build/check_files.sh
	@build/ramdisk.py

all: pre
	@if [ ! -f src/Makefile ]; then \
	    (./RUNME;) \
	fi
	(cd src; $(MAKE) $@)

format:
	git diff -U0 HEAD^ | clang-format-diff -i -p1

clean:
	(cd src; $(MAKE) $@)
	/bin/rm -rf data/gfx

clobber:
	(cd src; $(MAKE) $@)
	rm src/Makefile
	/bin/rm -rf data/gfx

.PHONY: all clean clobber format pre

.DEFAULT_GOAL := all
