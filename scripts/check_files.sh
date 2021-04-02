#!/bin/bash

if [[ ! -d data/gfx ]]; then
    echo $0: Need untar graphics tarball
    tar zxf data/gfx.tgz
    exit 0
fi

COUNT=$(find data -newer data/gfx.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then 
    echo $0: Need to retar graphics tarball due to updates
    (
        tar zcvf data/gfx.tgz data/gfx
	if [[ $? -ne 0 ]];
	then
	    echo $0: Failed to zip data/gfx.tgz
	    exit 1
	fi
    )
fi

if [[ ! -d data ]];
then
    echo $0: Unzip graphics
    tar zxf data/gfx.tgz
    if [[ $? -ne 0 ]];
    then
        echo $0: Failed to unzip data/gfx.tgz
        exit 1
    fi
fi
