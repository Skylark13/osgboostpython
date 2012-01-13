#!/usr/bin/env python

# the order of import is important here
import osg
import osgGA
import osgViewer

vertices = osg.Vec3Array()
vertices.append( osg.Vec3f( 0, 0, 1) )
vertices.append( osg.Vec3f( -0.5, -0.5, 0) )
vertices.append( osg.Vec3f( 0.5, -0.5, 0) )
vertices.append( osg.Vec3f( 0.5, 0.5, 0) )
vertices.append( osg.Vec3f( -0.5, 0.5, 0) )
vertices.append( osg.Vec3f( 0, 0, -1 ) )

indices = osg.DrawElementsUInt( osg.PrimitiveSet.TRIANGLES, 24 )
indices[0] = 0
indices[1] = 1
indices[2] = 2
indices[3] = 0
indices[4] = 2
indices[5] = 3
indices[6] = 0
indices[7] = 3
indices[8] = 4
indices[9] = 0
indices[10] = 4 
indices[11] = 1
indices[12] = 5
indices[13] = 2
indices[14] = 1
indices[15] = 5
indices[16] = 3
indices[17] = 2
indices[18] = 5
indices[19] = 4
indices[20] = 3
indices[21] = 5
indices[22] = 1
indices[23] = 4

geom = osg.Geometry()
geom.setVertexArray( vertices )
geom.addPrimitiveSet( indices )

#osgUtil.SmoothingVisitor.smooth( geom )

viewer = osgViewer.Viewer()

root = osg.Geode()
root.addDrawable( geom )

viewer.setSceneData( root )

viewer.run()
