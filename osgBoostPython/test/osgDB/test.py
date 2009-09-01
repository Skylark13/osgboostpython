#!/bin/python
import osg
import osgDB

def test_osgDBReadCow():
    print "Reading cow.osg"
    cow = osgDB.readNodeFile("cow.osg")
    print "Done"
    
def test_osgDB():
    test_osgDBReadCow()
    
test_osgDB()
