#!/bin/python

# Shouldn't have to do this, but for some reason Eric doesn't add PYTHONPATH to sys.path by default...
import sys
import os
sys.path = os.environ.get("PYTHONPATH").split(";") + sys.path[:]
print "sys.path=",  sys.path

#print "-"*78
#execfile("test/osg/test.py")
#print "-"*78
#execfile("test/osgDB/test.py")
#print "-"*78
#execfile("test/osgGA/test.py")
#print "-"*78
#execfile("test/osgViewer/test.py")
#print "-"*78
