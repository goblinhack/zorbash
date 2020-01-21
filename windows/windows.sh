
"/c/Program Files (x86)/BitRock InstallBuilder Enterprise 16.11.1/bin/builder-cli.exe" build windows.xml 
if [[ $? -ne 0 ]];
then
    exit 1
fi

cp /c/Users/goblinhack/Documents/InstallBuilder/output/mundusmeus-0.01-windows-installer.exe ../mundusmeus-installer.exe
if [ -d /c/Users/goblinhack/Google\ Drive/ ]; then
    cp ../mundusmeus-installer.exe  /c/Users/goblinhack/Google\ Drive/
fi
