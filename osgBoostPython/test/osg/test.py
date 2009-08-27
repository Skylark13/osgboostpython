#!/bin/python
import osg
print "Testing osg::Matrixd"
m = osg.Matrixd()
m.valid()

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
