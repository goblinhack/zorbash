
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
  --exclude __pycache__ 
/mingw64/lib/python3.8
/mingw64/lib/python3.8/asyncio
/mingw64/lib/python3.8/collections
/mingw64/lib/python3.8/concurrent
/mingw64/lib/python3.8/concurrent/futures
/mingw64/lib/python3.8/config-3.8
/mingw64/lib/python3.8/ctypes
/mingw64/lib/python3.8/ctypes/macholib
/mingw64/lib/python3.8/ctypes/test
/mingw64/lib/python3.8/curses
/mingw64/lib/python3.8/dbm
/mingw64/lib/python3.8/distutils
/mingw64/lib/python3.8/distutils/command
/mingw64/lib/python3.8/distutils/tests
/mingw64/lib/python3.8/email
/mingw64/lib/python3.8/email/mime
/mingw64/lib/python3.8/encodings
/mingw64/lib/python3.8/ensurepip
/mingw64/lib/python3.8/ensurepip/_bundled
/mingw64/lib/python3.8/html
/mingw64/lib/python3.8/http
/mingw64/lib/python3.8/idlelib
/mingw64/lib/python3.8/idlelib/Icons
/mingw64/lib/python3.8/idlelib/idle_test
/mingw64/lib/python3.8/importlib
/mingw64/lib/python3.8/json
/mingw64/lib/python3.8/lib-dynload
/mingw64/lib/python3.8/lib2to3
/mingw64/lib/python3.8/lib2to3/fixes
/mingw64/lib/python3.8/lib2to3/pgen2
/mingw64/lib/python3.8/lib2to3/tests
/mingw64/lib/python3.8/lib2to3/tests/data
/mingw64/lib/python3.8/lib2to3/tests/data/fixers
/mingw64/lib/python3.8/lib2to3/tests/data/fixers/myfixes
/mingw64/lib/python3.8/logging
/mingw64/lib/python3.8/msilib
/mingw64/lib/python3.8/multiprocessing
/mingw64/lib/python3.8/multiprocessing/dummy
/mingw64/lib/python3.8/pydoc_data
/mingw64/lib/python3.8/site-packages
/mingw64/lib/python3.8/site-packages/apipkg
/mingw64/lib/python3.8/site-packages/apipkg-1.5-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/appdirs-1.4.3-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/attr
/mingw64/lib/python3.8/site-packages/attrs-19.3.0-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/cachecontrol
/mingw64/lib/python3.8/site-packages/cachecontrol/caches
/mingw64/lib/python3.8/site-packages/CacheControl-0.12.6-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/certifi
/mingw64/lib/python3.8/site-packages/certifi-2019.11.28-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/chardet
/mingw64/lib/python3.8/site-packages/chardet/cli
/mingw64/lib/python3.8/site-packages/chardet-3.0.4-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/colorama
/mingw64/lib/python3.8/site-packages/colorama-0.4.3-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/colored
/mingw64/lib/python3.8/site-packages/colored-1.4.2-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/contextlib2-0.6.0-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/data
/mingw64/lib/python3.8/site-packages/distlib
/mingw64/lib/python3.8/site-packages/distlib/_backport
/mingw64/lib/python3.8/site-packages/entrypoints-0.3.dist-info
/mingw64/lib/python3.8/site-packages/flake8
/mingw64/lib/python3.8/site-packages/flake8/api
/mingw64/lib/python3.8/site-packages/flake8/formatting
/mingw64/lib/python3.8/site-packages/flake8/main
/mingw64/lib/python3.8/site-packages/flake8/options
/mingw64/lib/python3.8/site-packages/flake8/plugins
/mingw64/lib/python3.8/site-packages/flake8-3.7.9.dist-info
/mingw64/lib/python3.8/site-packages/hexdump-3.3-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/html5lib
/mingw64/lib/python3.8/site-packages/html5lib/filters
/mingw64/lib/python3.8/site-packages/html5lib/treeadapters
/mingw64/lib/python3.8/site-packages/html5lib/treebuilders
/mingw64/lib/python3.8/site-packages/html5lib/treewalkers
/mingw64/lib/python3.8/site-packages/html5lib/_trie
/mingw64/lib/python3.8/site-packages/html5lib-1.0.1-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/idna
/mingw64/lib/python3.8/site-packages/idna-2.8-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/iniconfig-1.0.0-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/lockfile
/mingw64/lib/python3.8/site-packages/lockfile-0.12.2-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/mccabe-0.6.1.dist-info
/mingw64/lib/python3.8/site-packages/msgpack
/mingw64/lib/python3.8/site-packages/msgpack-0.6.2-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/ordered_set-3.1.1-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/packaging
/mingw64/lib/python3.8/site-packages/packaging-19.2-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/pep517
/mingw64/lib/python3.8/site-packages/pip
/mingw64/lib/python3.8/site-packages/pip/_internal
/mingw64/lib/python3.8/site-packages/pip/_internal/cli
/mingw64/lib/python3.8/site-packages/pip/_internal/commands
/mingw64/lib/python3.8/site-packages/pip/_internal/distributions
/mingw64/lib/python3.8/site-packages/pip/_internal/distributions/source
/mingw64/lib/python3.8/site-packages/pip/_internal/models
/mingw64/lib/python3.8/site-packages/pip/_internal/network
/mingw64/lib/python3.8/site-packages/pip/_internal/operations
/mingw64/lib/python3.8/site-packages/pip/_internal/req
/mingw64/lib/python3.8/site-packages/pip/_internal/utils
/mingw64/lib/python3.8/site-packages/pip/_internal/vcs
/mingw64/lib/python3.8/site-packages/pip/_vendor
/mingw64/lib/python3.8/site-packages/pip-19.3.1-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/pkg_resources
/mingw64/lib/python3.8/site-packages/progress
/mingw64/lib/python3.8/site-packages/progress-1.5-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/py
/mingw64/lib/python3.8/site-packages/py/_code
/mingw64/lib/python3.8/site-packages/py/_io
/mingw64/lib/python3.8/site-packages/py/_log
/mingw64/lib/python3.8/site-packages/py/_path
/mingw64/lib/python3.8/site-packages/py/_process
/mingw64/lib/python3.8/site-packages/py-1.8.1-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/pycodestyle-2.5.0.dist-info
/mingw64/lib/python3.8/site-packages/pyflakes
/mingw64/lib/python3.8/site-packages/pyflakes/scripts
/mingw64/lib/python3.8/site-packages/pyflakes/test
/mingw64/lib/python3.8/site-packages/pyflakes-2.1.1.dist-info
/mingw64/lib/python3.8/site-packages/pyparsing-2.4.6-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/pytoml
/mingw64/lib/python3.8/site-packages/pytoml-0.1.21-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/requests
/mingw64/lib/python3.8/site-packages/requests-2.22.0-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/retrying-1.3.3-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/setuptools
/mingw64/lib/python3.8/site-packages/setuptools/command
/mingw64/lib/python3.8/site-packages/setuptools-43.0.0-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/six-1.13.0-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/urllib3
/mingw64/lib/python3.8/site-packages/urllib3/contrib
/mingw64/lib/python3.8/site-packages/urllib3/contrib/_securetransport
/mingw64/lib/python3.8/site-packages/urllib3/packages
/mingw64/lib/python3.8/site-packages/urllib3/packages/backports
/mingw64/lib/python3.8/site-packages/urllib3/packages/ssl_match_hostname
/mingw64/lib/python3.8/site-packages/urllib3/util
/mingw64/lib/python3.8/site-packages/urllib3-1.25.7-py3.8.egg-info
/mingw64/lib/python3.8/site-packages/webencodings
/mingw64/lib/python3.8/site-packages/webencodings-0.5.1-py3.8.egg-info
/mingw64/lib/python3.8/sqlite3
/mingw64/lib/python3.8/sqlite3/test
/mingw64/lib/python3.8/test
/mingw64/lib/python3.8/test/audiodata
/mingw64/lib/python3.8/test/capath
/mingw64/lib/python3.8/test/cjkencodings
/mingw64/lib/python3.8/test/data
/mingw64/lib/python3.8/test/decimaltestdata
/mingw64/lib/python3.8/test/dtracedata
/mingw64/lib/python3.8/test/eintrdata
/mingw64/lib/python3.8/test/encoded_modules
/mingw64/lib/python3.8/test/imghdrdata
/mingw64/lib/python3.8/test/libregrtest
/mingw64/lib/python3.8/test/sndhdrdata
/mingw64/lib/python3.8/test/subprocessdata
/mingw64/lib/python3.8/test/support
/mingw64/lib/python3.8/test/test_asyncio
/mingw64/lib/python3.8/test/test_email
/mingw64/lib/python3.8/test/test_email/data
/mingw64/lib/python3.8/test/test_import
/mingw64/lib/python3.8/test/test_import/data
/mingw64/lib/python3.8/test/test_import/data/circular_imports
/mingw64/lib/python3.8/test/test_import/data/circular_imports/subpkg
/mingw64/lib/python3.8/test/test_import/data/package
/mingw64/lib/python3.8/test/test_import/data/package2
/mingw64/lib/python3.8/test/test_importlib
/mingw64/lib/python3.8/test/test_importlib/builtin
/mingw64/lib/python3.8/test/test_importlib/data
/mingw64/lib/python3.8/test/test_importlib/data01
/mingw64/lib/python3.8/test/test_importlib/data01/subdirectory
/mingw64/lib/python3.8/test/test_importlib/data02
/mingw64/lib/python3.8/test/test_importlib/data02/one
/mingw64/lib/python3.8/test/test_importlib/data02/two
/mingw64/lib/python3.8/test/test_importlib/data03
/mingw64/lib/python3.8/test/test_importlib/data03/namespace
/mingw64/lib/python3.8/test/test_importlib/data03/namespace/portion1
/mingw64/lib/python3.8/test/test_importlib/data03/namespace/portion2
/mingw64/lib/python3.8/test/test_importlib/extension
/mingw64/lib/python3.8/test/test_importlib/frozen
/mingw64/lib/python3.8/test/test_importlib/import_
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/both_portions
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/both_portions/foo
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/module_and_namespace_package
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/module_and_namespace_package/a_test
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/not_a_namespace_pkg
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/not_a_namespace_pkg/foo
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/portion1
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/portion1/foo
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/portion2
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/portion2/foo
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project1
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project1/parent
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project1/parent/child
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project2
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project2/parent
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project2/parent/child
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project3
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project3/parent
/mingw64/lib/python3.8/test/test_importlib/namespace_pkgs/project3/parent/child
/mingw64/lib/python3.8/test/test_importlib/source
/mingw64/lib/python3.8/test/test_importlib/zipdata01
/mingw64/lib/python3.8/test/test_importlib/zipdata02
/mingw64/lib/python3.8/test/test_json
/mingw64/lib/python3.8/test/test_tools
/mingw64/lib/python3.8/test/test_warnings
/mingw64/lib/python3.8/test/test_warnings/data
/mingw64/lib/python3.8/test/tracedmodules
/mingw64/lib/python3.8/test/xmltestdata
/mingw64/lib/python3.8/test/xmltestdata/c14n-20
/mingw64/lib/python3.8/test/ziptestdata
/mingw64/lib/python3.8/tkinter
/mingw64/lib/python3.8/tkinter/test
/mingw64/lib/python3.8/tkinter/test/test_tkinter
/mingw64/lib/python3.8/tkinter/test/test_ttk
/mingw64/lib/python3.8/Tools
/mingw64/lib/python3.8/Tools/i18n
/mingw64/lib/python3.8/Tools/scripts
/mingw64/lib/python3.8/turtledemo
/mingw64/lib/python3.8/unittest
/mingw64/lib/python3.8/unittest/test
/mingw64/lib/python3.8/unittest/test/testmock
/mingw64/lib/python3.8/urllib
/mingw64/lib/python3.8/venv
/mingw64/lib/python3.8/venv/scripts
/mingw64/lib/python3.8/venv/scripts/common
/mingw64/lib/python3.8/venv/scripts/posix
/mingw64/lib/python3.8/wsgiref
/mingw64/lib/python3.8/xml
/mingw64/lib/python3.8/xml/dom
/mingw64/lib/python3.8/xml/etree
/mingw64/lib/python3.8/xml/parsers
/mingw64/lib/python3.8/xml/sax
/mingw64/lib/python3.8/xmlrpc
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
