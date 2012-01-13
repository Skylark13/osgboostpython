#!/usr/bin/env python

import sys

# the order of import is important here
import osg
import osgDB
import osgGA
import osgViewer

class InfoVisitor( osg.NodeVisitor ):
    def __init__(self):
        super(InfoVisitor, self).__init__()
        self.level = 0
        self.traversalMode = osg.NodeVisitor.TRAVERSE_ALL_CHILDREN

    def apply_Node( self, node ):
        print self.level * 2 * " ", node.className
        self.level += 1
        super(InfoVisitor, self).traverse( node )
        self.level -= 1

    def apply_Geode( self, node ):
        print self.level * 2 * " ", node.className
        self.level += 1
        # iterate over drawables
        for n in node.getDrawableList() :
            print self.level * 2 * " ", n.className
        super(InfoVisitor, self).traverse( node )
        self.level -= 1
    
root = osgDB.readNodeFile("cessna.osg")

infoVisitor = InfoVisitor()
root.accept( infoVisitor )

viewer = osgViewer.Viewer()

viewer.setSceneData( root )

viewer.run()
