#!/bin/python
import osg
import osgGA
import unittest

class osgGATest(unittest.TestCase):
    pass

allTests = []

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
        suite = unittest.TestSuite(map(osgGATest, tests))
        unittest.TextTestRunner().run(suite)
