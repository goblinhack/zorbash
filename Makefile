
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
