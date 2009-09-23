#!/bin/python
import osg
import osgDB
import unittest

class osgClipNodeTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.ClipNode()
    def test_001_testEnumsAvailable(self):
        osg.ClipNode.ABSOLUTE_RF #using scope().attr
        osg.ClipNode.RELATIVE_RF
    def test_002_testMethodsAvailable(self):
        o = osg.ClipNode()
        o.className()
        #o.libraryName()
        n = osg.NodeVisitor()
        o.accept(n)
        o.setReferenceFrame(osg.ClipNode.ABSOLUTE_RF)
        o.getReferenceFrame()
        o.createClipBox(osg.BoundingBox(), 3) # const & bb, unsigned int clipPlaneNumberBase)
        cp = osg.ClipPlane()
        o.addClipPlane(cp)
        o.addClipPlane(cp)
        o.removeClipPlane(cp) # * clipplane)
        #o.removeClipPlane(unsigned int pos)
        o.addClipPlane(cp)
        o.getNumClipPlanes()
        o.getClipPlane(1)
        o.getClipPlane(1)
        #o.setClipPlaneList(std::vector<osg::ref_ptr<osg::ClipPlane>, std::allocator<osg::ref_ptr<osg::ClipPlane> > > const & cpl)
        #o.getClipPlaneList()
        o.setStateSetModes(osg.StateSet(), osg.GL_COLOR_MATERIAL)
        #o.setLocalStateSetModes(unsigned int arg0) #todo
        o.computeBound()


allTests = ['test_000_testClassAvailable',
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
        suite = unittest.TestSuite(map(osgClipNodeTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
