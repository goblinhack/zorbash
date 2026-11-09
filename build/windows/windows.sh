
LOGNAME=$(whoami)

echo
echo Final files to package
echo ======================
ls -la

echo
echo Package with bitrock
echo ====================
/bin/rm -f /c/Users/${LOGNAME}/Documents/InstallBuilder/output/*orbash*exe
ls -la /c/Users/${LOGNAME}/Documents/InstallBuilder/output/
"/c/Program Files/InstallBuilder Enterprise 26.8.0/bin/builder-cli.exe" build windows.xml

if [[ $? -ne 0 ]];
then
    exit 1
fi
ls -la /c/Users/${LOGNAME}/Documents/InstallBuilder/output/

echo Installer
echo =========
/bin/rm -f ../../*installer.exe
ls -la /c/Users/${LOGNAME}/Documents/InstallBuilder/output/
cp /c/Users/${LOGNAME}/Documents/InstallBuilder/output/* ../..
cp /c/Users/${LOGNAME}/Documents/InstallBuilder/output/* /c/Documents\ and\ Settings/${LOGNAME}/Desktop/
