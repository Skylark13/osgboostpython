#!/bin/python
import osg
import osgDB

print "Reading cow.osg"
cow = osgDB.readNodeFile("cow.osg")
print "Done"