Quick notes
-----------------------------------------------------------------------------
To start working
------------------

In general, make sure your path contains the path to bjam
(BOOST_ROOT/tools/jam/src/bin.PLATFORM) and the boost libraries
(BOOST_ROOT/lib), and that your PYTHONPATH contains osgBoostPython/lib

(Windows)
setenv.bat does that for you when run from the osgBoostPython root directory.

To build
------------------
Make sure OSG_ROOT and BOOST_ROOT are set properly. In general, run

bjam release

This will copy the resulting python modules into lib/osg/, lib/osgDB, etc.

(Windows)
Make sure you run it with the "release" argument to avoid "release executable
calling into debug DLL" problems. (.pyd modules are basically DLLs)

Note that the Visual Studio solution and project files in build/ are NOT for
actually building this project! They are just there for convenience when
working on the source.

To run tests
------------------
python test/test_all.py

or individually:

python test/test_osg.py
python test/test_osgGA.py
python test/test_osgDB.py
python test/test_osgViewer.py

or

Run python from the osgBoostPython root and copy-paste the tests into the
command prompt window a line at a time.

or

You can also use the Eric4 project in test/ to run, edit and debug the tests.

The individual test scripts are all rigged so you can run all tests by
specifying no arguments on the command line, or run individual tests by
specifying an integer (0 to ntests-1).

Python version
------------------
Whenever you change your Python version, jam will rebuild boost_python*.dll.
You need to either copy the new dll into <boost_root>/lib or into the
osgBoostPython root directory otherwise it will try to use the DLL for the
previous version of Python and will give an ImportError. This is on Windows,
I'm not sure if this applies to Linux and other OSes.