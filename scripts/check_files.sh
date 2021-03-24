#!/bin/bash

COUNT=$(find data -newer data/gfx.tgz -type f | wc -l)
if [[ $COUNT -gt 0 ]];
then 
    echo $0: Need to retar graphics tarball due to updates
    (cd data ; tar zcvf gfx.tgz gfx)
fi

echo $0: Unzip graphics
(cd data ; tar zxf gfx.tgz)
