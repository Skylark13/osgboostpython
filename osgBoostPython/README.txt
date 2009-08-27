Quick notes
-----------------------------------------------------------------------------
To start working
------------------
cd /d G:\OSG-Nodekits\___myprojects\osgBoostPython
for /F "Tokens=1" %I in ('cd') do set osgBoostPython_Lib=%I\lib
set PYTHONPATH=%PYTHONPATH%;%osgBoostPython_Lib%
set PATH=%PATH%;G:\boost_1_35_0\tools\jam\src\bin.ntx86;G:\boost_1_35_0\lib;%OSG_BIN_PATH%

To build
------------------
cls && build release

To run tests
------------------
python test/osg/test.py

or

Run python from the osgBoostPython root and copy-paste the tests into the
command prompt window.

Python version
------------------
Whenever you change your Python version, jam will rebuild boost_python*.dll.
You need to either copy the new dll into <boost_root>/lib or into the
osgBoostPython root directory otherwise it will try to use the DLL for the
previous version of Python and will give an ImportError.