#!/bin/python
import osg
import osgGA
import osgDB
import osgViewer
import unittest

# These tests are hard to wrap with unittest. We'll assume visual inspection.

inWindow = True

def runViewer(sceneRoot, handler = None):
    viewer = osgViewer.Viewer()
    if (inWindow):
        viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    if (sceneRoot):
        viewer.addEventHandler(osgGA.StateSetManipulator(sceneRoot.stateSet))
        viewer.setSceneData(sceneRoot)
    if (handler):
        viewer.addEventHandler(handler)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

class osgViewerTest(unittest.TestCase):
    def test_000_osgViewerSetups(self):
        print "-"*40
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
        self.failUnless(True)

    def test_001_osgViewerAndShapeDrawable1(self):
        self.osgViewerAndShapeDrawable(False)
        self.failUnless(True)

    def test_002_osgViewerAndShapeDrawable2(self):
        self.osgViewerAndShapeDrawable(True)
        self.failUnless(True)

    def osgViewerAndShapeDrawable(self,  testStateSet):
        print "-"*40
        print "Testing osgViewer with a ShapeDrawable"
        shape = osg.ShapeDrawable(osg.Sphere(), None)
        geode = osg.Geode()
        geode.addDrawable(shape)
        if (testStateSet):
            print "Will disable lighting"
            s = geode.stateSet
            s.setMode(osg.GL_LIGHTING, osg.StateAttribute.Values.OFF)
        runViewer(geode)

    def test_003_osgViewerAndCow1(self):
        self.osgViewerAndCow(False)

    def test_004_osgViewerAndCow2(self):
        self.osgViewerAndCow(True)

    def osgViewerAndCow(self,  testStateSet):
        print "-"*40
        print "Testing osgViewer with cow.osg"
        cow = osgDB.readNodeFile("cow.osg")
        if (testStateSet):
            print "Will disable texturing"
            s = cow.stateSet
            s.setTextureMode(0, osg.GL_TEXTURE_2D, osg.StateAttribute.Values.OFF + osg.StateAttribute.Values.OVERRIDE)
        runViewer(cow)
        self.failUnless(True)

    def test_005_osgViewerAndGeometry1(self):
        self.osgViewerAndGeometry(False)

    def test_006_osgViewerAndGeometry2(self):
        self.osgViewerAndGeometry(True)

    def osgViewerAndGeometry(self,  testStateSet):
        print "-"*40
        print "Testing osgViewer with osg::Geometry"
        g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
        g.getColorArray()[0] = osg.Vec4f(1,1,1,0.5)
        geode = osg.Geode()
        geode.addDrawable(g)

        if (testStateSet):
            print "Will add a texture"
            i = osgDB.readImageFile("Images/osg256.png")
            t = osg.Texture2D(i)
            s = geode.stateSet
            s.setTextureAttributeAndModes(0, t, osg.StateAttribute.Values.ON)
            s.setRenderingHint(osg.StateSet.RenderingHint.TRANSPARENT_BIN)
            s.setMode(osg.GL_BLEND, osg.StateAttribute.Values.ON)

        runViewer(geode)
        self.failUnless(True)

    def test_007_osgViewerAndOverriddenGUIEventHandler(self):
        print "-"*40
        print "Testing osgViewer with a GUIEventHandler derived in python code"
        class DerivedHandler(osgGA.GUIEventHandler):
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

        cow = osgDB.readNodeFile("cow.osg")

        runViewer(cow, DerivedHandler())
        self.failUnless(True)

    def test_008_osgViewerAndOverriddenNodeCallback(self):
        print "-"*40
        print "Will add a trivial CullCallback to the model - since traverse() is called the model should still be rendered."
        class DerivedCallback(osg.NodeCallback):
            def call(self, node, nv):
                print "python callback"
                self.traverse(node, nv)     # Seems like this slices off the node, it thinks it's an osg::Node instead of an osg::Group.

        cow = osgDB.readNodeFile("cow.osg")
        cb = DerivedCallback()
        cow.setCullCallback(cb)

        runViewer(cow)
        self.failUnless(True)

allTests = ['test_000_osgViewerSetups',
            'test_001_osgViewerAndShapeDrawable1',
            'test_002_osgViewerAndShapeDrawable2',
            'test_003_osgViewerAndCow1',
            'test_004_osgViewerAndCow2',
            'test_005_osgViewerAndGeometry1',
            'test_006_osgViewerAndGeometry2',
            'test_007_osgViewerAndOverriddenGUIEventHandler',
            'test_008_osgViewerAndOverriddenNodeCallback']

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
        suite = unittest.TestSuite(map(osgViewerTest, tests))
        unittest.TextTestRunner().run(suite)
