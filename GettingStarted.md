# Introduction #
This page is intended to provide new users with information to get up and running as quickly as possible.  There's information on external libs that need to be installed as well as platforms that are currently supported.

## Platform Support ##
The intention is to support as many platforms as possible.  All three operating systems will continue to be supported and we're working on extending the versions of each.
  * Linux - Ubuntu 10.10 and 10.04
  * MacOSX - 10.6.8 (Snow Leopard)
  * Windows - Windows 7

## Library Dependencies ##
You will need to have the following packages installed on your system.  The Open Scene Graph, boost, and python libraries and header files are found by the cmake macros, so most _standard_ installations should be picked up without problems.
  * [cmake](http://www.cmake.org/) - The minimum version required is 2.8.
  * [OpenSceneGraph](http://www.openscenegraph.org/projects/osg) - Currently testing on 3.0.1.
  * [boost](http://www.boost.org) - Currently testing on 1.47.0.  Many of the libraries are header-only, but you will need to built Boost.Python.
  * [python](http://www.python.org/) - Currently testing on python 2.6

## Building osgBoostPython ##
Currently the build is in-source, but may change in the future as the project goes.  To build osgBoostPython simply :
  1. svn co http://osgboostpython.googlecode.com/svn/trunk
  1. cd trunk/osgBoostPython
  1. cmake .
  1. make