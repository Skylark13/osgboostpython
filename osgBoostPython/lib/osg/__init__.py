from _osg import *

# As a test of the capacity to create osg::Geometry through python, this
# useful utility function is not wrapped through C++ but is instead re-written
# in python and used that way.
def createTexturedQuadGeometry(corner, widthVec, heightVec, l, b, r, t):
    #print "Creating a quad through osg::Geometry"
    g = _osg.Geometry()

    #print "Creating and adding vertex array"
    vertices = _osg.Vec3Array()
    vertices.append(corner+widthVec)
    vertices.append(corner)
    vertices.append(corner+heightVec)
    vertices.append(corner+widthVec+heightVec)
    g.setVertexArray(vertices)

    #print "Creating and adding texcoord array"
    texcoords = _osg.Vec2Array()
    texcoords.append(_osg.Vec2f(l,t))
    texcoords.append(_osg.Vec2f(l,b))
    texcoords.append(_osg.Vec2f(r,b))
    texcoords.append(_osg.Vec2f(r,t))
    g.setTexCoordArray(0, texcoords)

    #print "Creating and adding color array"
    colors = _osg.Vec4Array()
    colors.append(_osg.Vec4f(1,1,1,1))
    g.setColorArray(colors)
    g.colorBinding = _osg.Geometry.AttributeBinding.BIND_OVERALL

    #print "Creating and adding normal array"
    normals = _osg.Vec3Array()
    normals.append(_osg.Vec3f(0,-1,0))
    g.setNormalArray(normals)
    g.normalBinding = _osg.Geometry.AttributeBinding.BIND_OVERALL

    #print "Adding PrimitiveSet"
    g.addPrimitiveSet(_osg.DrawArrays(_osg.PrimitiveSet.Mode.QUADS, 0, 4))

    return g
