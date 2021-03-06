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
import unittest

class osgTest(unittest.TestCase):
    def test_000_osgVec4(self):
        v4d = osg.Vec4d()
        self.failUnless(v4d.x == 0.0 and v4d.y == 0.0 and v4d.z == 0.0 and v4d.w == 0.0)
        self.failUnless(v4d == osg.Vec4d(0,0,0,0))  # test ==
        v4d.set(1,2,3,4)
        self.failUnless(v4d == osg.Vec4d(1,2,3,4))
        v4d2 = osg.Vec4d(4,5,6,7)
        result = v4d2 + v4d
        self.failUnless(result == osg.Vec4d(5,7,9,11))
        result = v4d2 - v4d
        self.failUnless(result == osg.Vec4d(3,3,3,3))
        result = v4d * 2
        self.failUnless(result == osg.Vec4d(2,4,6,8))
        result = result / 2             # v4d * 2 / 2 == v4d
        self.failUnless(result == v4d)
        self.failUnless(result != v4d2) # test !=

    def test_001_osgVec4Array(self):
        v4array = osg.Vec4Array()
        v4array.append(osg.Vec4f(1,2,3,4))
        v4array.append(osg.Vec4f(2,3,4,5))
        v4array.append(osg.Vec4f(3,4,5,6))

        self.failUnless(len(v4array) == 3)
        self.failUnless(v4array[0].x == 1.0 and v4array[0].y == 2.0 and v4array[0].z == 3.0 and v4array[0].w == 4.0)
        self.failUnless(v4array[1].x == 2.0 and v4array[1].y == 3.0 and v4array[1].z == 4.0 and v4array[1].w == 5.0)
        self.failUnless(v4array[2].x == 3.0 and v4array[2].y == 4.0 and v4array[2].z == 5.0 and v4array[2].w == 6.0)

        v4array2 = v4array[0:2]
        self.failUnless(len(v4array2) == 2)
        self.failUnless(v4array2[0].x == 1.0 and v4array2[0].y == 2.0 and v4array2[0].z == 3.0 and v4array2[0].w == 4.0)
        self.failUnless(v4array2[1].x == 2.0 and v4array2[1].y == 3.0 and v4array2[1].z == 4.0 and v4array2[1].w == 5.0)

        v4 = v4array.pop()
        self.failUnless(len(v4array) == 2)
        self.failUnless(v4array[0].x == 1.0 and v4array[0].y == 2.0 and v4array[0].z == 3.0 and v4array[0].w == 4.0)
        self.failUnless(v4array[1].x == 2.0 and v4array[1].y == 3.0 and v4array[1].z == 4.0 and v4array[1].w == 5.0)
        self.failUnless(v4.x == 3.0 and v4.y == 4.0 and v4.z == 5.0 and v4.w == 6.0)

        # Should test all methods...

    def test_002_osgMatrix(self):
        m = osg.Matrixd()
        self.failUnless(m.valid())

    def test_003_osgBoundingSphere(self):
        bs = osg.BoundingSphere()
        c = bs._center
        self.failUnless(c.x == 0.0 and c.y == 0.0 and c.z == 0.0 and bs._radius == -1)
        self.failIf(bs.valid())     # bs is not initially valid
        bs._center = osg.Vec3f(0,0,0)
        bs._radius = 1
        self.failUnless(c.x == 0.0 and c.y == 0.0 and c.z == 0.0 and bs._radius == 1)
        self.failUnless(bs.valid())     # bs should now be valid

    def test_004_osgNodeAndGroup(self):
        n = osg.Node()
        n.name = "node"
        self.failUnless(n)
        self.failUnless(n.name == "node")
        self.failUnless(n.getNumParents() == 0)

        g = osg.Group()
        g.name = "group"
        self.failUnless(g)
        self.failUnless(g.name == "group")
        self.failUnless(g.getNumParents() == 0)
        self.failUnless(g.getNumChildren() == 0)

        g.addChild(n)
        self.failUnless(n.getNumParents() == 1)
        self.failUnless(g.getNumChildren() == 1)
        self.failUnless(n.getParent(0) == g)
        n0 = n
        self.failUnless(n0 == n)
        n1 = g.getChild(0)
        self.failUnless(n1 == n)
        self.failUnless(g.getChild(0) == n)

        parents = n.getParents()
        self.failUnless(len(parents) == 1)
        self.failUnless(parents[0] == g)

    def test_005_osgGeodeAndShapeDrawable(self):
        sd = osg.ShapeDrawable(osg.Sphere(), None)
        sd.name = "sphere"
        self.failUnless(sd)
        self.failUnless(sd.name == "sphere")

        geode = osg.Geode()
        geode.name = "geode"
        self.failUnless(geode)
        self.failUnless(geode.name == "geode")
        self.failUnless(geode.getNumDrawables() == 0)

        geode.addDrawable(sd)
        self.failUnless(geode.getNumDrawables() == 1)
        parent = sd.getParent(0)
        self.failUnless(parent == geode)
        self.failUnless(sd.getParent(0) == geode)
        self.failUnless(geode.getDrawable(0) == sd)

        drawables = geode.getDrawableList()
        self.failUnless(len(drawables) == 1)
        self.failUnless(drawables[0] == sd)

    def test_006_osgGeometry(self):
        g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
        self.failUnless(g.getNumPrimitiveSets() == 1)
        self.failUnless(len(g.getVertexArray()) == 4)
        self.failUnless(len(g.getTexCoordArray(0)) == 4)
        self.failUnless(len(g.getColorArray()) == 1)
        self.failUnless(len(g.getNormalArray()) == 1)

    def test_007_osgStateSet(self):
        g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
        s = g.stateSet
        self.failUnless(s)
        self.failUnless(s.getMode(osg.GL_LIGHTING))     # Initially on
        s.setMode(osg.GL_LIGHTING, osg.StateAttribute.OFF)
        self.failIf(s.getMode(osg.GL_LIGHTING))     # We set it off
        s.setMode(osg.GL_LIGHTING, osg.StateAttribute.ON)
        self.failUnless(s.getMode(osg.GL_LIGHTING))     # We set it on

    def test_008_osgUniform(self):
        u = osg.Uniform(osg.Uniform.FLOAT, "uFloat")
        self.failUnless(u.getFloat() == 0.0)
        u.setFloat(1.3)
        self.failUnlessAlmostEqual(u.getFloat(),  1.3)
        u = osg.Uniform(osg.Uniform.BOOL_VEC4, "uBVec4")
        # Should return a tuple not a list... Unless I should be setting from a list not a tuple? Anyways, it should be consistent.
        self.failUnless(u.getBool4() == [False,  False,  False,  False])
        u.setBool4(False, True, True, False)
        self.failUnless(u.getBool4() == [False, True, True, False])
        values = [True, False, True, False]
        u.setBool4(*values)
        self.failUnless(u.getBool4() == values)

    def test_009_overriddenNodeVisitor(self):
        # Not quite sure how to use unittest for this one... For now we'll just let it print out and if it ran to completion, we'll assume success.

        # DerivedVisitor1 verifies that apply_Node will be called for all node
        # subclasses if other apply_* methods are not overridden.
        class DerivedVisitor1(osg.NodeVisitor):
            def __init__(self):
                # call parent class constructor with argument
                super(DerivedVisitor1,  self).__init__(osg.NodeVisitor.TRAVERSE_ALL_CHILDREN)
            def apply_Node(self, node):
                print "python apply_Node - node name:", node.name
                self.traverse(node)

        # DerivedVisitor2 verifies that apply_Node and apply_Group are called for
        # their respective node arguments.
        class DerivedVisitor2(osg.NodeVisitor):
            def __init__(self):
                # call parent class constructor with argument
                super(DerivedVisitor2,  self).__init__(osg.NodeVisitor.TRAVERSE_ALL_CHILDREN)
            def apply_Node(self, node):
                print "python apply_Node - node name:", node.name
                self.traverse(node)
            def apply_Group(self, node):
                print "python apply_Group - node name:", node.name
                self.traverse(node)

        g1 = osg.Group()
        g1.name = "g1"
        g2 = osg.Group()
        g2.name = "g2"
        g1.addChild(g2)
        n = osg.Node()
        n.name = "n"
        g2.addChild(n)

        print ""
        nv1 = DerivedVisitor1()
        g1.accept(nv1)

        print ""
        nv2 = DerivedVisitor2()
        g1.accept(nv2)

        self.failUnless(True)

allTests = ['test_000_osgVec4',
            'test_001_osgVec4Array',
            'test_002_osgMatrix',
            'test_003_osgBoundingSphere',
            'test_004_osgNodeAndGroup',
            'test_005_osgGeodeAndShapeDrawable',
            'test_006_osgGeometry',
            'test_007_osgStateSet',
            'test_008_osgUniform',
            'test_009_overriddenNodeVisitor']

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
        suite = unittest.TestSuite(map(osgTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
