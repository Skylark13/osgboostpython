#!/usr/bin/env python

# the order of import is important here
import osg
import osgDB
import osgGA
import osgUtil
import osgViewer

from math import pi
import sys

# to see the switching explicity use the following configuration
#model1 = osgDB.readNodeFile("cow.osg")
#model2 = osgDB.readNodeFile("cessna.osg")
#model3 = osgDB.readNodeFile("cessnafire.osg")

# deepcopy not supported yet
model1 = osgDB.readNodeFile("cessna.osg")
model2 = osgDB.readNodeFile("cessna.osg")
model3 = osgDB.readNodeFile("cessna.osg")

simplifier = osgUtil.Simplifier()
simplifier.sampleRatio = 0.5
model2.accept( simplifier )
simplifier.sampleRatio = 0.1
model1.accept( simplifier )
 

viewer = osgViewer.Viewer()

root = osg.LOD()
root.addChild( model1, 200, sys.float_info.max ) 
root.addChild( model2, 50, 200)
root.addChild( model3, 0, 50)

viewer.setSceneData( root )

viewer.run()
