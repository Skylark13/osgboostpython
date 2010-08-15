#!/bin/python
#
# This source file is part of the osgBoostPython library
# 
# Copyright (C) 2009-2010 Jean-Sebastien Guay
# 
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free Software
# Foundation; either version 3 of the License, or (at your option) any later
# version.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
# http://www.gnu.org/copyleft/lesser.txt.
#

import osg
import osgUtil
import osgDB
import unittest
import time

class osgLineSegmentIntersectorTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        o = osgUtil.LineSegmentIntersector(osg.Vec3d(0,0,0),osg.Vec3d(100,0,0))
        g1 = osgUtil.IntersectorGroup()
        v1 = osgUtil.IntersectionVisitor(g1)
    def test_001_testMethodsAvailable(self):
        o = osgUtil.LineSegmentIntersector(osg.Vec3d(0,0,0),osg.Vec3d(100,0,0))
        #o.insertIntersection(osgUtil::LineSegmentIntersector::Intersection const & intersection)
        #o.getIntersections()
        #o.getFirstIntersection()
        o.setStart(osg.Vec3d(7,8,9))
        o.getStart()
        o.setEnd(osg.Vec3d(700,8,9))
        o.getEnd()
        #o.clone(osgUtil::IntersectionVisitor & iv)
        #o.enter(osg::Node const & node)
        #o.leave()
        #o.intersect(osgUtil::IntersectionVisitor & iv, osg::Drawable * drawable)
        o.reset()
        o.containsIntersections()
        #o.operator<(osgUtil::LineSegmentIntersector::Intersection const & rhs)
        #o.getLocalIntersectPoint()
        #o.getWorldIntersectPoint()
        #o.getLocalIntersectNormal()
        #o.getWorldIntersectNormal()

    def test_002_testIntersectionOnCow(self):
        """
        Setting up two linesegment tests on cow. One linesegment should hit the other should not.
        """
        model = osgDB.readNodeFile('cow.osg')
        group = osg.Group()
        group.addChild(model)

        g1 = osgUtil.IntersectorGroup()
        l1 = osgUtil.LineSegmentIntersector(osg.Vec3d(0,0,0),osg.Vec3d(100,0,0))
        g1.addIntersector(l1)
        v1 = osgUtil.IntersectionVisitor(g1)

        group.accept(v1)
        self.assert_(g1.containsIntersections())  # _____ cow should be hit _____

        g2 = osgUtil.IntersectorGroup()
        l2 = osgUtil.LineSegmentIntersector(osg.Vec3d(90,0,0),osg.Vec3d(100,0,0))
        g2.addIntersector(l2)
        v2 = osgUtil.IntersectionVisitor(g2)

        group.accept(v2)
        self.assert_(not g2.containsIntersections())  # _____ no hit ______

        isect = l1.getFirstIntersection()
        isect.drawable
        n = isect.getLocalIntersectNormal()
        p = isect.getLocalIntersectPoint()
        wn = isect.getWorldIntersectNormal()
        wp = isect.getWorldIntersectPoint()
        #isect.indexList
        lin = isect.localIntersectionNormal
        lip = isect.localIntersectionPoint
        #isect.matrix
        npath = isect.nodePath
        pi = isect.primitiveIndex
        r = isect.ratio
        #isect.ratioList
        (str(n),str(p),str(wn),str(wp))

#        for i in g1.getIntersectors():
 #           print i

    def test_003_testIntersectionPerformance(self):
        osgDB.Registry().setBuildKdTreesHint(osgDB.Options.BUILD_KDTREES);
#        osgDB.Registry().setBuildKdTreesHint(osgDB.Options.DO_NOT_BUILD_KDTREES);
        group = osg.Group()
        for name in ['cow.osg', 'cessna.osg', 'spaceship.osg', 'dumptruck.osg']:
            model = osgDB.readNodeFile(name)
            group.addChild(model)

        g1 = osgUtil.IntersectorGroup()
        for x in range(100):
            for y in range(100):
                lsi = osgUtil.LineSegmentIntersector(osg.Vec3d(x*0.02,y*0.02,-5),osg.Vec3d(x*0.1,y*0.1,5))
                g1.addIntersector(lsi)
        v1 = osgUtil.IntersectionVisitor(g1)
        v1.setUseKdTreeWhenAvailable(True)

        start = time.clock()
        for i in range(1):
            group.accept(v1)
        end = time.clock()
        seconds_needed = end - start
        #print 'Needed %f seconds.' % seconds_needed
        self.assert_(seconds_needed < 1.0) #without kdtree it should take 50x longer...


allTests = ['test_000_testClassAvailable',
            'test_000_testMethodsAvailable',
            'test_002_testIntersectionOnCow',
            'test_003_testIntersectionPerformance', ]

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
        suite = unittest.TestSuite(map(osgLineSegmentIntersectorTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
