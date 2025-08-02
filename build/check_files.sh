#!/bin/bash

untar() {
    tar -zxf $*
    if [[ $? -ne 0 ]]; then
        echo $0: Failed to extract archive $*
        exit 1
    fi
}

make_tar() {
    # https://stackoverflow.com/questions/51655657/tar-ignoring-unknown-extended-header-keyword-libarchive-xattr-security-selinux
    COPYFILE_DISABLE=1 tar --no-xattrs -zcvf $*
    if [[ $? -ne 0 ]]; then
        tar zcvf $*
        if [[ $? -ne 0 ]]; then
            echo $0: Failed to create archive $*
            exit 1
        fi
    fi
}

if [[ ! -d data/gfx ]]; then
    echo $0: Need to extract graphics archive
    untar data/gfx.tgz
    DONE=1
fi

if [[ ! -d data/sounds ]]; then
    echo $0: Need to extract sounds archive
    untar data/sounds.tgz
    DONE=1
fi

if [[ $DONE -eq 1 ]]; then
    exit 0
fi

#
# Remove mac dot underscore files
#
find . -type f -name '._*' -delete

COUNT=$(find data/gfx -newer data/gfx.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then
    echo $0: Need to retar graphics tarball due to updates
    make_tar data/gfx.tgz data/gfx
fi

COUNT=$(find data/sounds -newer data/sounds.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then
    echo $0: Need to retar sounds tarball due to updates
    make_tar data/sounds.tgz data/sounds
fi

#
# Remove mac dot underscore files
#
find . -type f -name '._*' -delete
