:: build osgBoostPython
@echo off

:: %1 expected to be clean, release, debug or empty (=debug).
bjam %1

if not %ERRORLEVEL%==0 goto error
if [%1]==[clean] goto end

set BUILD=%1
if not [%BUILD%]==[] goto copy
set BUILD=debug

:copy
xcopy /Y bin\msvc-8.0\%BUILD%\threading-multi\_osg.pyd lib\osg
xcopy /Y bin\msvc-8.0\%BUILD%\threading-multi\_osgDB.pyd lib\osgDB
xcopy /Y bin\msvc-8.0\%BUILD%\threading-multi\_osgGA.pyd lib\osgGA
xcopy /Y bin\msvc-8.0\%BUILD%\threading-multi\_osgViewer.pyd lib\osgViewer
goto end

:error
echo Error compiling.

:end