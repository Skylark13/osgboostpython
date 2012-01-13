#!/usr/bin/env python

# the order of import is important here
import osg
import osgDB
import osgGA
import osgViewer

model = osgDB.readNodeFile("cessna.osg")

transform1 = osg.MatrixTransform()
transform1.setMatrix( osg.Matrixd.translate( -25, 0, 0 ) )
transform1.addChild( model )

transform2 = osg.MatrixTransform()
transform2.setMatrix( osg.Matrixd.translate( 25, 0, 0 ) )
transform2.addChild( model )

viewer = osgViewer.Viewer()

root = osg.Group()
root.addChild( transform1 )
root.addChild( transform2 )

viewer.setSceneData( root )

viewer.run()
