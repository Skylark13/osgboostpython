#!/usr/bin/env python

# the order of import is important here
import osg
import osgGA
import osgDB
import osgViewer

# note that you need OSG_FILE_PATH to point to the location of this file
model1 = osgDB.readNodeFile("cessna.osg")
model2 = osgDB.readNodeFile("cow.osg")

root = osg.Group()
root.addChild( model1 )
root.addChild( model2 )

viewer = osgViewer.Viewer()

viewer.setSceneData( root )

viewer.run()
