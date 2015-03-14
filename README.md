osgBoostPython
==============

Note: this project is not active anymore, and has been moved here from Google Code in case it is still useful to someone.

boost.python bindings for OpenSceneGraph. Hand-written to hopefully be more optimized, and also to be able to offer a more python-esque view of the OSG data structures.

See the README.txt file in the sources for how to build and use the wrappers.

They are still very much a work in progress, but basic things work well. For example, we can translate osg::createTexturedQuadGeometry() which is in src/osg/Geometry.cpp almost literally to Python:

    # As a test of the capacity to create osg::Geometry through python, this
    # useful utility function is not wrapped through C++ but is instead re-written
    # in python and used that way.
    def createTexturedQuadGeometry(corner, widthVec, heightVec, l, b, r, t):
        g = osg.Geometry()

        # Create vertex array
        vertices = osg.Vec3Array()
        vertices.append(corner+widthVec)
        vertices.append(corner)
        vertices.append(corner+heightVec)
        vertices.append(corner+widthVec+heightVec)
        g.setVertexArray(vertices)

        # Create texcoord array
        texcoords = osg.Vec2Array()
        texcoords.append(osg.Vec2f(l,t))
        texcoords.append(osg.Vec2f(l,b))
        texcoords.append(osg.Vec2f(r,b))
        texcoords.append(osg.Vec2f(r,t))
        g.setTexCoordArray(0, texcoords)

        # Create color array (single value, white)
        colors = osg.Vec4Array()
        colors.append(osg.Vec4f(1,1,1,1))
        g.setColorArray(colors)
        g.colorBinding = osg.Geometry.BIND_OVERALL

        # Create normal array (single value for all vertices)
        normals = osg.Vec3Array()
        normals.append(osg.Vec3f(0,-1,0))
        g.setNormalArray(normals)
        g.normalBinding = osg.Geometry.BIND_OVERALL

        # Add primitive set
        g.addPrimitiveSet(osg.DrawArrays(osg.PrimitiveSet.QUADS, 0, 4))

        return g

We can then use this function to create a quad, apply a texture onto it, and view the result in an osgViewer::Viewer:

    import osg
    import osgDB
    import osgGA
    import osgViewer

    # Create a 1x1 quad in XZ plane
    g = osg.createTexturedQuadGeometry(osg.Vec3f(0,0,0), osg.Vec3f(1,0,0), osg.Vec3f(0,0,1), 0, 0, 1, 1)
    g.getColorArray()[0] = osg.Vec4f(1,1,1,0.5)  # change color to semitransparent

    # Add it to a geode
    geode = osg.Geode()
    geode.addDrawable(g)

    # Add texture
    i = osgDB.readImageFile("Images/osg256.png")
    t = osg.Texture2D(i)
    s = geode.stateSet
    s.setTextureAttributeAndModes(0, t, osg.StateAttribute.Values.ON)

    # Make sure blending is active and the geode is in the transparent (depth sorted) bin
    s.setRenderingHint(osg.StateSet.TRANSPARENT_BIN)
    s.setMode(osg.GL_BLEND, osg.StateAttribute.ON)

    # Create viewer, add some standard handlers to it and run it
    viewer = osgViewer.Viewer()
    viewer.setUpViewInWindow(50, 50, 1024, 768);
    viewer.addEventHandler(osgGA.StateSetManipulator(geode.stateSet))
    viewer.addEventHandler(osgViewer.HelpHandler())
    viewer.addEventHandler(osgViewer.StatsHandler())
    viewer.setSceneData(geode)
    viewer.run()
    del viewer      # To cause the dtor to be called, hence the window to be destroyed.

Some python-esque things work already, like some uses of slices on arrays:

    v4array = osg.Vec4Array()

    # Append objects using append()
    v4array.append(osg.Vec4f(1,2,3,4))
    v4array.append(osg.Vec4f(2,3,4,5))
    v4array.append(osg.Vec4f(3,4,5,6))

    # v4array now contains [ (1,2,3,4), (2,3,4,5), (3,4,5,6) ]

    # Create from slice of existing array
    v4array2 = v4array[0:2]

    # v4array2 now contains [ (1,2,3,4), (2,3,4,5) ]

    # Assign one object
    v4array[2] = osg.Vec4f(1,2,3,4)

    # v4array now contains [ (1,1,1,1), (2,2,2,2), (1,2,3,4) ]

But lots of things are missing, some of which are pretty basic.

The WrappingCookbook wiki page has some tips for how to wrap things - it's mostly a reminder to myself but if someone wants to help it will be useful too. Most things are pretty simple to wrap, but reading the whole boost.python documentation, FAQ, wiki, and scattered mail posts and web pages takes a long time, so it's useful to collect all that info in one place.

Contributions welcome, you can either post to the cplusplus-sig or osg-users mailings lists or directly to my e-mail address. That goes for questions as well.
