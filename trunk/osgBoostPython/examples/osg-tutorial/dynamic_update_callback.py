#!/usr/bin/env python

# the order of import is important here
import osg
import osgGA
import osgViewer

vertices = osg.Vec3Array()
vertices.append( osg.Vec3f( 0, 0, 0 ) )
vertices.append( osg.Vec3f( 1, 0, 0 ) )
vertices.append( osg.Vec3f( 1, 0, 1 ) )
vertices.append( osg.Vec3f( 0, 0, 1 ) )

normals = osg.Vec3Array()
normals.append( osg.Vec3f( 0, -1, 0 ) )

colors = osg.Vec4Array()
colors.append( osg.Vec4f( 1, 0, 0, 1 ) )
colors.append( osg.Vec4f( 0, 1, 0, 1 ) )
colors.append( osg.Vec4f( 0, 0, 1, 1 ) )
colors.append( osg.Vec4f( 1, 1, 1, 1 ) )

quad = osg.Geometry()
quad.setVertexArray( vertices )
quad.setNormalArray( normals )
quad.normalBinding = osg.Geometry.BIND_OVERALL
quad.setColorArray( colors )
quad.colorBinding = osg.Geometry.BIND_PER_VERTEX 

quad.addPrimitiveSet( osg.DrawArrays( osg.PrimitiveSet.QUADS, 0, 4 ) )

class DynamicCallbackQuad( osg.Drawable.UpdateCallback ):
    def __init__(self):
        super( DynamicCallbackQuad, self ).__init__()

    def update( self, nv, drawable ) :
        if drawable.className == "Geometry" :
            vertices = drawable.vertexArray
            quat = osg.Quat( osg.PI * 0.01, osg.X_AXIS )
            vertices[ -1 ] = quat * vertices[ -1 ]
            quad.dirtyDisplayList()
            quad.dirtyBound()
    

viewer = osgViewer.Viewer()

root = osg.Geode()
root.addDrawable( quad )

viewer.setSceneData( root )

viewer.run()
