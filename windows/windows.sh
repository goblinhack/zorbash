
"/c/Program Files (x86)/BitRock InstallBuilder for Windows 19.12.0/bin/builder-cli.exe" build windows.xml 
if [[ $? -ne 0 ]];
then
    exit 1
fi

ls -la /c/Users/nmcgill/Documents/InstallBuilder/output/
cp /c/Users/nmcgill/Documents/InstallBuilder/output/zorbash-0.0.1-windows-installer.exe
