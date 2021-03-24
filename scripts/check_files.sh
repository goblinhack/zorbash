#!/bin/bash

COUNT=$(find data -newer data/gfx.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then 
    echo $0: Need to retar graphics tarball due to updates
    tar zcvf data/gfx.tgz data/gfx
fi

echo $0: Unzip graphics
tar zxf data/gfx.tgz
