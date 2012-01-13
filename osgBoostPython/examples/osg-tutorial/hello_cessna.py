#!/usr/bin/env python

# the order of import is important here
import osg
import osgGA
import osgDB
import osgViewer

viewer = osgViewer.Viewer()

# note that you need OSG_FILE_PATH to point to the location of this file
root = osgDB.readNodeFile("cessna.osg")
viewer.setSceneData( root )

viewer.run()
