Quick notes
-----------------------------------------------------------------------------
To start working
------------------

In general, make sure your path contains the path to bjam
(BOOST_ROOT/tools/jam/src/bin.PLATFORM) and the boost libraries
(BOOST_ROOT/lib), and that your PYTHONPATH contains osgBoostPython/lib

(Windows)
setenv.bat does that for you when run from the osgBoostPython root directory.

To build with bjam
------------------
Make sure OSG_ROOT and BOOST_ROOT are set properly. Run

bjam release

This will copy the resulting python modules into lib/osg/, lib/osgDB, etc.

(Windows)
Both building in release and debug should work (bjam release, bjam debug).
You need to have the appropriate boost_python lib+dll for the type of build
you're doing of course (see below). You also need the OSG libs+dlls for that
type of build. Once it's built in debug, you can attach the Visual Studio 
debugger to the running python.exe process and put breakpoints in OSG code
or your wrapping code to debug it. It can be useful to put a raw_input() call
at the beginning of your python program so that it waits for input, at which
time you can attach the debugger and then press any key to continue.

Note that the Visual Studio solution and project files in build/ are NOT for
actually building this project! They are just there for convenience when
working on the source.

To build with cmake
------------------
NOTE : This has only been tested on Linux/Ubuntu 10.04 with cmake 2.8,
boost 1.47.0, python 2.6, and OSG 3.0.1.

In the source directory :
     
     $ cmake .
     $ make
     $ ./setenv.sh
     
Like the bjam build above this adds python modules into lib/osg, lib/osgDB/, etc...
The last step adds the path to the python modules to your PYTHONPATH ( currently
only bash shell is supported ).

To run tests
------------------
python test/runtests.py

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
Whenever you change your Python version, jam will rebuild boost_python*.dll
to match your new Python version. By default it will be built into 

  %BOOST_ROOT%\bin.v2\libs\python\build\msvc-9.0\release

You should copy the new DLL into the osgBoostPython root directory so it finds
it first when running a script that uses osgBoostPython, otherwise it will try 
to use the DLL for the previous version of Python (or the one that ships with 
boost) and will give an ImportError. This is on Windows, I'm not sure if this 
applies to Linux and other OSes.

Just to summarize, when building osgBoostPython, bjam will link with the 

  boost_python-vc90-mt-x_y.lib    (release)
  boost_python-vc90-mt-gd-x_y.lib (debug)
  
that ships with boost, but at runtime you need to use the 

  boost_python-vc90-x_y.dll    (release)
  boost_python-vc90-gd-x_y.dll (debug)
  
that's built when building osgBoostPython to match your Python version.
