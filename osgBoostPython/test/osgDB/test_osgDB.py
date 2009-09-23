#!/bin/python
import osg
import osgDB
import unittest
import os,sys

class osgDBTest(unittest.TestCase):
    def test_000_readCow(self):
        cow = osgDB.readNodeFile("cow.osg")
        self.failUnless(cow,  'failed to read cow.osg')
    def test_000_environmentVariablesSet(self):
        if not os.environ.has_key('OSG_FILE_PATH'):
            self.fail('Environment variable OSG_FILE_PATH is not set! Cannot find testing data files.')
    
#    def test_001_exceptionWhenFileNotFound(self):
#        testOk = False
#        try:
#            anotherCow = osgDB.readNodeFile("this_file_must_not_exist.osg")
#        except Exception, inst:
#            testOk = True
#        self.failUnless(testOk, "Trying to load non-existing file does not raise an exception")

allTests = ['test_000_readCow']

# To be able to run one single test from the command line. Could be name-based instead of index-based...
if __name__ == "__main__":
    import sys
    testToRun = -1
    if (len(sys.argv) == 2):
        testToRun = int(sys.argv[1])

    if (testToRun == -1):
        unittest.main()
    else:
        tests = [allTests[testToRun]]
        suite = unittest.TestSuite(map(osgDBTest, tests))
        unittest.TextTestRunner().run(suite)
