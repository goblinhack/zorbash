
LOGNAME=$(whoami)

source ./python.version.sh
if [[ "$PYVER" = "" ]]; then
    echo "$0: python.version.sh does not have PYVER set. Did you do a RUNME first ?"
    exit 1
fi

/bin/rm -rf python${PYVER}.tar
/bin/rm -rf python${PYVER}

echo
echo Zipping python files
echo ====================
tar -cf python${PYVER}.tar \
  --exclude __pycache__ \
  --exclude /ucrt64/lib/python${PYVER}/test \
  --exclude /ucrt64/lib/python${PYVER}/tkinter \
  --exclude /ucrt64/lib/python${PYVER}/turtledemo \
  --exclude /ucrt64/lib/python${PYVER}/unittest \
  --exclude /ucrt64/lib/python${PYVER}/site-packages \
  /ucrt64/lib/python${PYVER}

ls -la python${PYVER}.tar

echo
echo Unzipping python files
echo ======================
echo tar -xf python${PYVER}.tar
tar -xf python${PYVER}.tar

mv ucrt64/lib/python${PYVER} .
/bin/rm -rf ucrt64

echo
echo Final files to package
echo ======================
ls -la

echo
echo Package with bitrock
echo ====================
/bin/rm -f /c/Users/${LOGNAME}/Documents/InstallBuilder/output/*orbash*exe
ls -la /c/Users/${LOGNAME}/Documents/InstallBuilder/output/
"/c/Program Files/InstallBuilder Enterprise 23.4.0/bin/builder-cli.exe" build windows.xml

if [[ $? -ne 0 ]];
then
    exit 1
fi
ls -la /c/Users/${LOGNAME}/Documents/InstallBuilder/output/

/bin/rm -rf python${PYVER}
/bin/rm -rf python${PYVER}.tar

echo Installer
echo =========
/bin/rm -f ../../*installer.exe
ls -la /c/Users/${LOGNAME}/Documents/InstallBuilder/output/
cp /c/Users/${LOGNAME}/Documents/InstallBuilder/output/* ../..
cp /c/Users/${LOGNAME}/Documents/InstallBuilder/output/* /c/Documents\ and\ Settings/${LOGNAME}/Desktop/
