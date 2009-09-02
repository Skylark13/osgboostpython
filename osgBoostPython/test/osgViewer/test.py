#!/bin/python
import osg
import osgGA
import osgViewer

def test_osgViewerAndShapeDrawable():
    print "Testing osgViewer with a ShapeDrawable"
    shape = osg.ShapeDrawable(osg.Sphere(), None)
    geode = osg.Geode()
    geode.addDrawable(shape)
    viewer = osgViewer.Viewer()
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(geode)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewerAndCow():
    print "Testing osgViewer with cow.osg"
    import osgDB
    cow = osgDB.readNodeFile("cow.osg")
    viewer = osgViewer.Viewer()
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(cow)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewerAndGeometry():
    print "Testing osgViewer with osg::Geometry"
    g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
    geode = osg.Geode()
    geode.addDrawable(g)
    viewer = osgViewer.Viewer()
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(geode)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewer():
    test_osgViewerAndShapeDrawable()
    test_osgViewerAndCow()
    test_osgViewerAndGeometry()

test_osgViewer()
