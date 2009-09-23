#!/bin/python
import osg
import unittest

class osgPlaneTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.Plane()
    def test_001_testEnumsAvailable_partial(self):
        pass #No enums defined in class
    def test_002_testMethodsAvailable(self):
        #todo
        o = osg.Plane()
        p = osg.Plane()
        o.set(p)
        o.set(2.0,3.0,4.0,5.0)
        o.set(osg.Vec4f(3,4,5,7))
        o.set(osg.Vec4d(3,4,5,6))
        o.set(osg.Vec3d(0,0,1), 4.5)
        o.set(osg.Vec3d(0,0,1), osg.Vec3d(1,0,0), osg.Vec3d(0,1,0))
        o.set(osg.Vec3d(0,0,1), osg.Vec3d(0,0,4.5))
        o.flip()
        o.makeUnitLength()
        o.calculateUpperLowerBBCorners()
        o.valid()
        o.isNaN()
        o.asVec4()
        o.getNormal()
        o.distance(osg.Vec3f(7,8,9))
        o.distance(osg.Vec3d(9,8,7))
        o.dotProductNormal(osg.Vec3f(4,5,4))
        o.dotProductNormal(osg.Vec3d(5,4,5))
        o.intersect(osg.BoundingSphere())
        o.intersect(osg.BoundingBox())
        o.transform(osg.Matrixd())
        o.transformProvidingInverse(osg.Matrixd())


allTests = ['test_000_testClassAvailable',
            'test_001_testEnumsAvailable_partial',
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
        suite = unittest.TestSuite(map(osgPlaneTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
