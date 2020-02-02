
source python.version.sh
tar -c python${PYTHONVERSION}.tar --exclude __pycache__ /mingw64/lib/python${PYTHONVERSION}
tar -xvf python${PYTHONVERSION}.tar

"/c/Program Files (x86)/BitRock InstallBuilder Enterprise 19.12.0/bin/builder-cli.exe" build windows.xml 
if [[ $? -ne 0 ]];
then
    exit 1
fi

ls -la /c/Users/nmcgill/Documents/InstallBuilder/output/
cp /c/Users/nmcgill/Documents/InstallBuilder/output/* ..
