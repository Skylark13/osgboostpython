import osg
import osgGA
import osgDB
import osgViewer
import unittest

cow = osgDB.readNodeFile("cow.osg")
sceneRoot = osg.Group()
sceneRoot.addChild(cow)
viewer = osgViewer.Viewer()
viewer.setUpViewInWindow(50, 50, 1024, 768);
viewer.addEventHandler(osgViewer.HelpHandler())
viewer.addEventHandler(osgViewer.StatsHandler())
viewer.addEventHandler(osgGA.StateSetManipulator(sceneRoot.stateSet))
viewer.setSceneData(sceneRoot)
viewer.run()
del viewer
