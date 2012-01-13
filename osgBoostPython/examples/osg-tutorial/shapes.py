#!/usr/bin/env python

# the order of import is important here
import osg
import osgGA
import osgViewer

viewer = osgViewer.Viewer()

# note that you need OSG_FILE_PATH to point to the location of this file
shape1 = osg.ShapeDrawable( osg.Box( osg.Vec3f( -3, 0, 0 ), 2, 2, 1 ) ) 

shape2 = osg.ShapeDrawable( osg.Sphere( osg.Vec3f( 3, 0, 0 ), 1 ) )
shape2.color =  osg.Vec4f( 0, 0, 1, 1 ) 

shape3 = osg.ShapeDrawable( osg.Cone( osg.Vec3f( 0, 0, 0 ), 1 , 1 ) )
shape3.color =  osg.Vec4f( 0, 1, 0, 1 ) 

shape4 = osg.ShapeDrawable( osg.Cylinder( osg.Vec3f( 0, 0, 3 ), 1 , 1 ) )
shape4.color =  osg.Vec4f( 1, 0, 0, 1 ) 

shape5 = osg.ShapeDrawable( osg.Capsule( osg.Vec3f( 0, 0, -3 ), 1 , 1 ) )
shape5.color =  osg.Vec4f( 1, 1, 0, 1 ) 

root = osg.Geode()
root.addDrawable( shape1 )
root.addDrawable( shape2 )
root.addDrawable( shape3 )
root.addDrawable( shape4 )
root.addDrawable( shape5 )

viewer.setSceneData( root )

viewer.run()
