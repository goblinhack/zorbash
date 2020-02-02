
source ./python.version.sh
if [[ "$PYTHONVERSION" = "" ]]; then
    echo "$0: python.version.sh does not have PYTHONVERSION set"
    exit 1
fi

/bin/rm -rf python${PYTHONVERSION}.tar
/bin/rm -rf python${PYTHONVERSION}

echo
echo Zipping python files
echo tar -cf python${PYTHONVERSION}.tar --exclude __pycache__ /mingw64/lib/python${PYTHONVERSION}
tar -cf python${PYTHONVERSION}.tar --exclude __pycache__ /mingw64/lib/python${PYTHONVERSION}

ls -la python${PYTHONVERSION}.tar
echo
echo Unzipping python files
echo tar -xf python${PYTHONVERSION}.tar
tar -xf python${PYTHONVERSION}.tar

"/c/Program Files (x86)/BitRock InstallBuilder Enterprise 19.12.0/bin/builder-cli.exe" build windows.xml 
if [[ $? -ne 0 ]];
then
    exit 1
fi

ls -la /c/Users/nmcgill/Documents/InstallBuilder/output/
cp /c/Users/nmcgill/Documents/InstallBuilder/output/* ..
