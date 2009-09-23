#!/bin/python
import osg
import unittest

class osgStencilTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.Stencil()
    def test_001_testEnumsAvailable(self):
        #Functions
        osg.Stencil.NEVER
        osg.Stencil.NEVER
        osg.Stencil.LESS
        osg.Stencil.EQUAL
        osg.Stencil.LEQUAL
        osg.Stencil.GREATER
        osg.Stencil.NOTEQUAL
        osg.Stencil.GEQUAL
        osg.Stencil.ALWAYS
        #Operations
        osg.Stencil.KEEP
        osg.Stencil.ZERO
        osg.Stencil.REPLACE
        osg.Stencil.INCR
        osg.Stencil.DECR
        osg.Stencil.INVERT
        osg.Stencil.INCR_WRAP
        osg.Stencil.DECR_WRAP
    def test_002_testMethodsAvailable(self):
        s = osg.Stencil()
        s.setOperation(osg.Stencil.KEEP,osg.Stencil.ZERO,osg.Stencil.REPLACE )
        s.setWriteMask( 0xff56 )
        s.getWriteMask()
        s.setStencilFailOperation(osg.Stencil.REPLACE )
        s.getStencilFailOperation()
        s.setFunction(osg.Stencil.GREATER)
        s.getFunction()
        s.setFunction(osg.Stencil.ALWAYS, 0, 0x4545)
        s.setFunctionMask( 0x3434 )
        s.getFunctionMask()
        s.setStencilPassAndDepthPassOperation(osg.Stencil.INCR_WRAP)
        s.setStencilPassAndDepthFailOperation(osg.Stencil.DECR_WRAP)
        s.getStencilPassAndDepthPassOperation()
        s.getStencilPassAndDepthFailOperation()
        ##//s.getModeUsage() ##todo 
        s.getType()
        s.setFunctionRef(5)
        s.getFunctionRef()
        

allTests = ['test_000_testMethodsAvailable',
            'test_001_testEnumsAvailable',
            'test_002_testMethodsAvailable', ]

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
        suite = unittest.TestSuite(map(osgStencilTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
