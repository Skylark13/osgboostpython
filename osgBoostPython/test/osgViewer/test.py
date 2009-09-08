#!/bin/python
import osg
import osgGA
import osgViewer

def test_osgViewerSetups():
    print "Testing osgViewer across all screens"
    viewer = osgViewer.Viewer()
    viewer.setUpViewAcrossAllScreens();
    viewer.run()
    del viewer
    print "Testing osgViewer on single screen (0)"
    viewer = osgViewer.Viewer()
    viewer.setUpViewOnSingleScreen(0);
    viewer.run()
    del viewer
    print "Testing osgViewer in window"
    viewer = osgViewer.Viewer()
    viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.run()
    del viewer

def test_osgViewerAndShapeDrawable(testStateSet, inWindow):
    print "Testing osgViewer with a ShapeDrawable"
    shape = osg.ShapeDrawable(osg.Sphere(), None)
    geode = osg.Geode()
    geode.addDrawable(shape)
    if (testStateSet):
        print "Will disable lighting"
        s = geode.stateSet
        s.setMode(osg.GL_LIGHTING, osg.StateAttribute.Values.OFF)
    viewer = osgViewer.Viewer()
    if (inWindow):
        viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.addEventHandler(osgGA.StateSetManipulator(geode.stateSet))
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(geode)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewerAndCow(testStateSet, inWindow):
    print "Testing osgViewer with cow.osg"
    import osgDB
    cow = osgDB.readNodeFile("cow.osg")
    if (testStateSet):
        print "Will disable texturing"
        s = cow.stateSet
        s.setTextureMode(0, osg.GL_TEXTURE_2D, osg.StateAttribute.Values.OFF + osg.StateAttribute.Values.OVERRIDE)
    viewer = osgViewer.Viewer()
    if (inWindow):
        viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.addEventHandler(osgGA.StateSetManipulator(cow.stateSet))
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(cow)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewerAndGeometry(testStateSet, inWindow):
    print "Testing osgViewer with osg::Geometry"
    g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
    g.getColorArray()[0] = osg.Vec4f(1,1,1,0.5)
    geode = osg.Geode()
    geode.addDrawable(g)
    if (testStateSet):
        print "Will add a texture"
        import osgDB
        i = osgDB.readImageFile("Images/osg256.png")
        t = osg.Texture2D(i)
        s = geode.stateSet
        s.setTextureAttributeAndModes(0, t, osg.StateAttribute.Values.ON)
        s.setRenderingHint(osg.StateSet.RenderingHint.TRANSPARENT_BIN)
        s.setMode(osg.GL_BLEND, osg.StateAttribute.Values.ON)
    viewer = osgViewer.Viewer()
    if (inWindow):
        viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.addEventHandler(osgGA.StateSetManipulator(geode.stateSet))
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(geode)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewerAndOverriddenGUIEventHandler(inWindow):
    class TrialHandler(osgGA.GUIEventHandler):
        def handle(self, ea, aa):
            print "python handle"
            if (ea):
                pass
            else:
                print "ea is NULL"
            if (aa):
                pass
            else:
                print "aa is NULL"
            return False

    import osgDB
    viewer = osgViewer.Viewer()
    if (inWindow):
        viewer.setUpViewInWindow(50, 50, 1024, 768);
    t = TrialHandler()
    viewer.addEventHandler(t)
    viewer.addEventHandler(osgViewer.StatsHandler())
    cow = osgDB.readNodeFile("cow.osg")
    viewer.setSceneData(cow)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewerAndOverriddenNodeCallback(inWindow):
    class TrialCallback(osg.NodeCallback):
        def call(self, node, nv):
            print "python callback"
            self.traverse(node, nv)     # Seems like this chops off the node, it thinks it's an osg::Node instead of an osg::Group.

    import osgDB
    viewer = osgViewer.Viewer()
    if (inWindow):
        viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.addEventHandler(osgViewer.StatsHandler())
    cow = osgDB.readNodeFile("cow.osg")
    t = TrialCallback()
    cow.setUpdateCallback(t)
    viewer.setSceneData(cow)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

def test_osgViewer(testToRun):
    if (testToRun == -1 or testToRun == 0): test_osgViewerSetups()
    if (testToRun == -1 or testToRun == 1): test_osgViewerAndShapeDrawable(False, True)
    if (testToRun == -1 or testToRun == 2): test_osgViewerAndCow(False, True)
    if (testToRun == -1 or testToRun == 3): test_osgViewerAndGeometry(False, True)
    if (testToRun == -1): print "Now, let's re-test the sphere and cow with changes to the StateSets to see if StateSet works."
    if (testToRun == -1 or testToRun == 4): test_osgViewerAndShapeDrawable(True, True)
    if (testToRun == -1 or testToRun == 5): test_osgViewerAndCow(True, True)
    if (testToRun == -1 or testToRun == 6): test_osgViewerAndGeometry(True, True)
    if (testToRun == -1 or testToRun == 7): test_osgViewerAndOverriddenGUIEventHandler(True)
    if (testToRun == -1 or testToRun == 8): test_osgViewerAndOverriddenNodeCallback(True)

testToRun = -1
if __name__ == "__main__":
    import sys
    if (len(sys.argv) == 2):
        testToRun = int(sys.argv[1])

test_osgViewer(testToRun)
