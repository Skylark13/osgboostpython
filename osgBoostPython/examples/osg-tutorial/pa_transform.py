#!/usr/bin/env python

# the order of import is important here
import osg
import osgDB
import osgGA
import osgViewer

from math import pi

model = osgDB.readNodeFile("cessna.osg")
model2 = osgDB.readNodeFile("cessnafire.osg")

transform1 = osg.PositionAttitudeTransform()
transform1.position = osg.Vec3d( -25, 0, 0 ) 
transform1.attitude = osg.Quat( pi, osg.Vec3d( 0,0,1 ) )
transform1.addChild( model )

switch = osg.Switch()
switch.addChild( model )
switch.addChild( model2 )
switch[0] = False
switch[1] = True

transform2 = osg.PositionAttitudeTransform()
transform2.position =  osg.Vec3d( 25, 0, 0 ) 
transform2.addChild( switch )

viewer = osgViewer.Viewer()

root = osg.Group()
root.addChild( transform1 )
root.addChild( transform2 )

viewer.setSceneData( root )

viewer.run()
