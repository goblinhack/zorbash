
"/c/Program Files (x86)/BitRock InstallBuilder Enterprise 19.12.0/bin/builder-cli.exe" build windows.xml 
if [[ $? -ne 0 ]];
then
    exit 1
fi

cp /c/Users/nmcgill/Documents/InstallBuilder/output/zorbash-0.01-windows-installer.exe ../zorbash-installer.exe
if [ -d /c/Users/nmcgill/Google\ Drive/ ]; then
    cp ../zorbash-installer.exe  /c/Users/nmcgill/Google\ Drive/
fi
