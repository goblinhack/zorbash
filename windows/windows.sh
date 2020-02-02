
source ./python.version.sh
if [[ "$PYTHONVERSION" = "" ]]; then
    echo "$0: python.version.sh does not have PYTHONVERSION set"
    exit 1
fi

/bin/rm -rf python${PYTHONVERSION}.tar
/bin/rm -rf python${PYTHONVERSION}

echo
echo Zipping python files
echo ====================
tar -cf python${PYTHONVERSION}.tar \
  --exclude __pycache__ \
  --exclude /mingw64/lib/python3.8 \
  --exclude /mingw64/lib/python3.8/asyncio \
  --exclude /mingw64/lib/python3.8/collections \
  --exclude /mingw64/lib/python3.8/concurrent \
  --exclude /mingw64/lib/python3.8/concurrent/futures \
  --exclude /mingw64/lib/python3.8/config-3.8 \
  --exclude /mingw64/lib/python3.8/ctypes \
  --exclude /mingw64/lib/python3.8/ctypes/macholib \
  --exclude /mingw64/lib/python3.8/ctypes/test \
  --exclude /mingw64/lib/python3.8/curses \
  --exclude /mingw64/lib/python3.8/dbm \
  --exclude /mingw64/lib/python3.8/distutils \
  --exclude /mingw64/lib/python3.8/distutils/command \
  --exclude /mingw64/lib/python3.8/distutils/tests \
  --exclude /mingw64/lib/python3.8/email \
  --exclude /mingw64/lib/python3.8/email/mime \
  --exclude /mingw64/lib/python3.8/encodings \
  --exclude /mingw64/lib/python3.8/ensurepip \
  --exclude /mingw64/lib/python3.8/ensurepip/_bundled \
  --exclude /mingw64/lib/python3.8/html \
  --exclude /mingw64/lib/python3.8/http \
  --exclude /mingw64/lib/python3.8/idlelib \
  --exclude /mingw64/lib/python3.8/idlelib/Icons \
  --exclude /mingw64/lib/python3.8/idlelib/idle_test \
  --exclude /mingw64/lib/python3.8/importlib \
  --exclude /mingw64/lib/python3.8/json \
  --exclude /mingw64/lib/python3.8/lib-dynload \
  --exclude /mingw64/lib/python3.8/lib2to3 \
  --exclude /mingw64/lib/python3.8/logging \
  --exclude /mingw64/lib/python3.8/msilib \
  --exclude /mingw64/lib/python3.8/multiprocessing \
  --exclude /mingw64/lib/python3.8/multiprocessing/dummy \
  --exclude /mingw64/lib/python3.8/pydoc_data \
  --exclude /mingw64/lib/python3.8/site-packages \
  --exclude /mingw64/lib/python3.8/site-packages/py \
  --exclude /mingw64/lib/python3.8/site-packages/py/_code \
  --exclude /mingw64/lib/python3.8/site-packages/py/_io \
  --exclude /mingw64/lib/python3.8/site-packages/py/_log \
  --exclude /mingw64/lib/python3.8/site-packages/py/_path \
  --exclude /mingw64/lib/python3.8/site-packages/py/_process \
  --exclude /mingw64/lib/python3.8/site-packages/py-1.8.1-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/pycodestyle-2.5.0.dist-info \
  --exclude /mingw64/lib/python3.8/site-packages/pyflakes \
  --exclude /mingw64/lib/python3.8/site-packages/pyflakes/scripts \
  --exclude /mingw64/lib/python3.8/site-packages/pyflakes/test \
  --exclude /mingw64/lib/python3.8/site-packages/pyflakes-2.1.1.dist-info \
  --exclude /mingw64/lib/python3.8/site-packages/pyparsing-2.4.6-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/pytoml \
  --exclude /mingw64/lib/python3.8/site-packages/pytoml-0.1.21-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/requests \
  --exclude /mingw64/lib/python3.8/site-packages/requests-2.22.0-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/retrying-1.3.3-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/setuptools \
  --exclude /mingw64/lib/python3.8/site-packages/setuptools/command \
  --exclude /mingw64/lib/python3.8/site-packages/setuptools-43.0.0-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/six-1.13.0-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3 \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3/contrib \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3/contrib/_securetransport \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3/packages \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3/packages/backports \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3/packages/ssl_match_hostname \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3/util \
  --exclude /mingw64/lib/python3.8/site-packages/urllib3-1.25.7-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/site-packages/webencodings \
  --exclude /mingw64/lib/python3.8/site-packages/webencodings-0.5.1-py3.8.egg-info \
  --exclude /mingw64/lib/python3.8/sqlite3 \
  --exclude /mingw64/lib/python3.8/sqlite3/test \
  --exclude /mingw64/lib/python3.8/test \
  --exclude /mingw64/lib/python3.8/tkinter \
  --exclude /mingw64/lib/python3.8/Tools \
  --exclude /mingw64/lib/python3.8/Tools/i18n \
  --exclude /mingw64/lib/python3.8/Tools/scripts \
  --exclude /mingw64/lib/python3.8/turtledemo \
  --exclude /mingw64/lib/python3.8/unittest \
  --exclude /mingw64/lib/python3.8/urllib \
  --exclude /mingw64/lib/python3.8/venv \
  --exclude /mingw64/lib/python3.8/venv/scripts \
  --exclude /mingw64/lib/python3.8/venv/scripts/common \
  --exclude /mingw64/lib/python3.8/venv/scripts/posix \
  --exclude /mingw64/lib/python3.8/wsgiref \
  --exclude /mingw64/lib/python3.8/xml \
  --exclude /mingw64/lib/python3.8/xml/dom \
  --exclude /mingw64/lib/python3.8/xml/etree \
  --exclude /mingw64/lib/python3.8/xml/parsers \
  --exclude /mingw64/lib/python3.8/xml/sax \
  --exclude /mingw64/lib/python3.8/xmlrpc \
  /mingw64/lib/python${PYTHONVERSION}

ls -la python${PYTHONVERSION}.tar

echo
echo Unzipping python files
echo ======================
echo tar -xf python${PYTHONVERSION}.tar
tar -xf python${PYTHONVERSION}.tar

mv mingw64/lib/python${PYTHONVERSION} .
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
