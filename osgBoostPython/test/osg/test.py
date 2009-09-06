#!/bin/python
import osg

def test_osgVec4():
    print "-"*78
    print "Testing osg::Vec4d (for now we assume if this works, then Vec2{d|f}, Vec3{d|f} and Vec4f work too)"
    v4d = osg.Vec4d()
    print "v4d contains", v4d._v
    v4d.set(1,2,3,4)
    print "v4d contains", v4d._v
    print "Can also print by component:", v4d.x(), v4d.y(), v4d.z(), v4d.w()

def test_osgVec4Array():
    print "-"*78
    print "Testing osg::Vec4Array (for now we assume if this works, then Vec2Array and Vec3Array work too)"
    v4array = osg.Vec4Array()
    v4array.append(osg.Vec4f(1,2,3,4))
    v4array.append(osg.Vec4f(2,3,4,5))
    v4array.append(osg.Vec4f(3,4,5,6))
    print "v4array contains", len(v4array), "items"
    v4array2 = v4array[0:2]
    print "v4array2 created from a slice contains", len(v4array2), "items"
    v4 = v4array.pop()
    print "popped", v4._v, ", v4array now has", len(v4array), "items"
    # Should test all methods...

def test_osgMatrix():
    print "-"*78
    print "Testing osg::Matrixd"
    m = osg.Matrixd()
    print "Matrix valid =", m.valid()

def test_osgBoundingSphere():
    print "-"*78
    print "Testing osg::BoundingSphere"
    bs = osg.BoundingSphere()
    print "bs initial values: center =", bs._center._v, "radius =", bs._radius
    print "valid =", bs.valid()
    bs._center = osg.Vec3f(0,0,0)
    bs._radius = 1
    print "bs new values: center =", bs._center._v, "radius =", bs._radius
    print "valid =", bs.valid()

def test_osgNodeAndGroup():
    print "-"*78
    print "Testing osg::Node and osg::Group"
    print "  Creating objects"
    n = osg.Node()
    n.name = "node"
    print "    Node n is called [", n.name, "]"
    print "    Node has", n.getNumParents(), "parents"
    g = osg.Group()
    g.name = "group"
    print "    Group g is called [", g.name, "]"
    print "    Group has", g.getNumChildren(), "children"
    print "  Adding child to group"
    g.addChild(n)
    print "    Node has", n.getNumParents(), "parents"
    print "    Group has", g.getNumChildren(), "children"
    print "  Getting parent list"
    parents = n.getParents()
    print "    Parent list has", len(parents), "nodes"
    print "    Parent 0 is called [", parents[0].name, "]"

def test_osgGeodeAndShapeDrawable():
    print "-"*78
    print "Testing osg::Geode and osg::ShapeDrawable"
    print "  Creating ShapeDrawable and Geode"
    sd = osg.ShapeDrawable(osg.Sphere(), None)
    sd.name = "sphere"
    print "    ShapeDrawable sd is called [", sd.name, "]"
    #print "    ShapeDrawable has", sd.getNumParents(), "parents"   # Not wrapped yet
    geode = osg.Geode()
    geode.name = "geode"
    print "    Geode geode is called [", geode.name, "]"
    print "    Geode has", geode.getNumDrawables(), "drawables"
    print "  Adding drawable to geode"
    geode.addDrawable(sd)
    print "    Geode now has", geode.getNumDrawables(), "drawables"
    print "  Getting drawable list"
    drawables = geode.getDrawableList()
    print "    Drawable list has", len(drawables), "drawables"
    #print "    Drawable 0 is called [", drawables[0].name, "]"   # Doesn't quite work yet.

def test_osgGeometry():
    print "-"*78
    print "Testing osg::Geometry and osg::DrawArrays - run osgViewer tests to see the results"
    g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
    print "  g has", g.getNumPrimitiveSets(), "primitive sets,", len(g.getVertexArray()), "vertices"

def test_osgStateSet():
    print "-"*78
    print "Testing osg::StateSet - run osgViewer tests to see the results"
    g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
    s = g.stateSet
    print "g's StateSet is", s
    print "g has lighting state:", s.getMode(osg.GL_LIGHTING)
    print "setting g's lighting state to on"
    s.setMode(osg.GL_LIGHTING, osg.StateAttribute.Values.ON)
    print "g has lighting state:", s.getMode(osg.GL_LIGHTING)
    print "setting g's lighting state to off"
    s.setMode(osg.GL_LIGHTING, osg.StateAttribute.Values.OFF)
    print "g has lighting state:", s.getMode(osg.GL_LIGHTING)

def test_osgUniform():
    print "-"*78
    print "Testing osg::Uniform"
    u = osg.Uniform(osg.Uniform.Type.FLOAT, "uFloat")
    print "u is a FLOAT uniform variable"
    print "u's initial value is", u.getFloat()
    print "setting it to 1.3"
    u.setFloat(1.3)
    print "u's value is now", u.getFloat()
    u = osg.Uniform(osg.Uniform.Type.BOOL_VEC4, "uBVec4")
    print "u is now a BOOL_VEC4 uniform variable"
    print "u's initial value is", u.getBool4()
    print "setting to (False, True, True, False)"
    u.setBool4(False, True, True, False)
    print "u's value is now", u.getBool4()
    print "setting to (True, False, True, False) with a tuple"
    values = (True, False, True, False)
    u.setBool4(*values)
    print "u's value is now", u.getBool4()

def test_overriddenNodeVisitor():
    print "-"*78
    print "Testing osg::NodeVisitor derived in python code"
    class DerivedVisitor(osg.NodeVisitor):
        def __init__(self, tm = osg.NodeVisitor.TraversalMode.TRAVERSE_NONE):
            osg.NodeVisitor.__init__(self, tm)  # call parent class constructor with argument
        def apply_Node(self, node):
            print "python apply_Node - node name:", node.name
            self.traverse(node)     # Seems like this chops off the node, it thinks it's an osg::Node instead of an osg::Group.
        def apply_Group(self, node):
            print "python apply_Group - node name:", node.name
            self.traverse(node)     # Seems like this chops off the node, it thinks it's an osg::Node instead of an osg::Group.

    g1 = osg.Group()
    g1.name = "g1"
    g2 = osg.Group()
    g2.name = "g2"
    g1.addChild(g2)
    n = osg.Node()
    n.name = "n"
    g2.addChild(n)
    nv = DerivedVisitor(osg.NodeVisitor.TraversalMode.TRAVERSE_ALL_CHILDREN)
    g1.accept(nv)

def test_osg(testToRun):
    if (testToRun == -1 or testToRun == 0): test_osgVec4()
    if (testToRun == -1 or testToRun == 1): test_osgVec4Array()
    if (testToRun == -1 or testToRun == 2): test_osgMatrix()
    if (testToRun == -1 or testToRun == 3): test_osgBoundingSphere()
    if (testToRun == -1 or testToRun == 4): test_osgNodeAndGroup()
    if (testToRun == -1 or testToRun == 5): test_osgGeodeAndShapeDrawable()
    if (testToRun == -1 or testToRun == 6): test_osgGeometry()
    if (testToRun == -1 or testToRun == 7): test_osgStateSet()
    if (testToRun == -1 or testToRun == 8): test_osgUniform()
    if (testToRun == -1 or testToRun == 9): test_overriddenNodeVisitor()

testToRun = -1
if __name__ == "__main__":
    import sys
    if (len(sys.argv) == 2):
        testToRun = int(sys.argv[1])

test_osg(testToRun)

