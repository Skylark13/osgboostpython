#!/usr/bin/env python

import sys

# the order of import is important here
import osg
import osgDB
import osgGA
import osgViewer

class SwitchingCallback( osg.NodeCallback ):
    def __init__(self):
        super(SwitchingCallback, self).__init__()
        self.count = 0

    def call( self, node, nv ):
        # need a python way to only operate on Switch nodes
        # osg::Switch* switchNode = static_cast<osg::Switch*>( node );        
        # this is *very* hacky...in fact this sucks
        # TODO : need to wrap this in NodeCallback as call_Switch
        if node.className() == "Switch" :
            self.count += 1
            if not (self.count % 60 ) :
                node.valueList = [ not node.valueList[0], not node.valueList[1] ]

        super(SwitchingCallback, self).traverse( node, nv )

    def className( self ):
        return "SwitchingCallback"

        
# deepcopy not supported yet
model1 = osgDB.readNodeFile("cessna.osg")
model2 = osgDB.readNodeFile("cessnafire.osg")

root = osg.Switch()
root.addChild( model1, False )
root.addChild( model2, True )

# this gives slightly different results than
# simply root.setUpdateCallback( SwitchingCallback() )
# the above segfaults

sc = SwitchingCallback()
root.setUpdateCallback( sc )

viewer = osgViewer.Viewer()

viewer.setSceneData( root )

viewer.run()
