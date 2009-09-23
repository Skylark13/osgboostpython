#!/bin/python
import osg
import unittest

class osgStateAttributeTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.StateAttribute #Class cannot be instantiated from python ...
    def test_001_testEnumsAvailable_partial(self):
        #Functions
        osg.StateSet.INHERIT_RENDERBIN_DETAILS
        osg.StateSet.USE_RENDERBIN_DETAILS
        osg.StateSet.OVERRIDE_RENDERBIN_DETAILS
        
    def test_002_testMethodsAvailable(self):
        #todo
        s = osg.StateSet()
        s.setRenderBinDetails(1, 'test')
        
    def test_003_testDepthEnumsAvailable(self):
        osg.Depth.NEVER;
        osg.Depth.LESS;
        osg.Depth.EQUAL;
        osg.Depth.LEQUAL;
        osg.Depth.GREATER;
        osg.Depth.NOTEQUAL;
        osg.Depth.GEQUAL;
        osg.Depth.ALWAYS;    

allTests = ['test_000_testClassAvailable',
            'test_001_testEnumsAvailable_partial',
            'test_002_testMethodsAvailable',
            'test_003_testDepthEnumsAvailable', ]

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
        suite = unittest.TestSuite(map(osgStateAttributeTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
