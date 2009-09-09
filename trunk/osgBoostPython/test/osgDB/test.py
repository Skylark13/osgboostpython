#!/bin/python
import osg
import osgDB

def test_osgDBReadCow():
    print "-"*40
    print "Reading cow.osg"
    cow = osgDB.readNodeFile("cow.osg")
    print "Done"

def test_osgDB(testToRun):
    if (testToRun == -1 or testToRun == 0): test_osgDBReadCow()

testToRun = -1
if __name__ == "__main__":
    import sys
    if (len(sys.argv) == 2):
        testToRun = int(sys.argv[1])

test_osgDB(testToRun)
