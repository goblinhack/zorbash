all:
	scripts/check_files.sh
	scripts/ramdisk.py
	if [ ! -f src/Makefile ]; then \
	    (RUNME;) \
	fi
	(cd src; make $@)

clean:
	(cd src; make $@)
	/bin/rm -rf data/gfx

clobber:
	(cd src; make $@)
	rm src/Makefile
	/bin/rm -rf data/gfx
# DO NOT DELETE
