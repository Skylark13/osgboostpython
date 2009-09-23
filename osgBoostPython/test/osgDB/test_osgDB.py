#!/bin/python
import osg
import osgDB
import unittest

class osgDBTest(unittest.TestCase):
    def test_000_readCow(self):
        cow = osgDB.readNodeFile("cow.osg")
        self.failUnless(cow,  'failed to read cow.osg')

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
