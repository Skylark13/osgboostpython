#!/bin/python
import osg

print "Testing osg::Vec4d (for now we assume if this works, then Vec2{d|f}, Vec3{d|f} and Vec4f work too"
v4d = osg.Vec4d()
print "v4d contains", v4d._v
v4d.set(1,2,3,4)
print "v4d contains", v4d._v
print "Can also print by component:", v4d.x(), v4d.y(), v4d.z(), v4d.w()

print "Testing osg::Matrixd"
m = osg.Matrixd()
print "Matrix valid =", m.valid()

print "Testing osg::BoundingSphere"
bs = osg.BoundingSphere()
print "bs initial values: center =", bs._center._v, "radius =", bs._radius
print "valid =", bs.valid()
bs._center = osg.Vec3f(0,0,0)
bs._radius = 1
print "bs new values: center =", bs._center._v, "radius =", bs._radius
print "valid =", bs.valid()

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

