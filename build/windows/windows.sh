
source ./python.version.sh
if [[ "$PYVER" = "" ]]; then
    echo "$0: python.version.sh does not have PYVER set"
    exit 1
fi

/bin/rm -rf python${PYVER}.tar
/bin/rm -rf python${PYVER}

echo
echo Zipping python files
echo ====================
tar -cf python${PYVER}.tar \
  --exclude __pycache__ \
  --exclude /mingw64/lib/python${PYVER}/test \
  --exclude /mingw64/lib/python${PYVER}/tkinter \
  --exclude /mingw64/lib/python${PYVER}/turtledemo \
  --exclude /mingw64/lib/python${PYVER}/unittest \
  /mingw64/lib/python${PYVER}

ls -la python${PYVER}.tar

echo
echo Unzipping python files
echo ======================
echo tar -xf python${PYVER}.tar
tar -xf python${PYVER}.tar

mv mingw64/lib/python${PYVER} .
/bin/rm -rf mingw64

echo
echo Final files to package
echo ======================
ls -la

echo
echo Package with bitrock
echo ====================
"/c/Program Files (x86)/BitRock InstallBuilder Enterprise 19.12.0/bin/builder-cli.exe" build windows.xml
if [[ $? -ne 0 ]];
then
    exit 1
fi

echo
echo Installer
echo =========
ls -la /c/Users/nmcgill/Documents/InstallBuilder/output/
cp /c/Users/nmcgill/Documents/InstallBuilder/output/* ..
