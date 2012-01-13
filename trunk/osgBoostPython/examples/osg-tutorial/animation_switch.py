#!/usr/bin/env python

import sys

# the order of import is important here
import osg
import osgDB
import osgGA
import osgViewer

# This currently isn't working.  In order to
# prevent slicing you need to wrap the reference
# in Switch_wrapper::traverse.  This fails however
# for NodeVisitors that are not wrapped and are
# not going to be wrapped ( e.g. CollectParentPaths )
# because they are not part of the API. 
# There might be an easy fix, where you just catch
# the throw from python, but I haven't tried this yet.

class AnimationSwitch( osg.Switch ):
    def __init__(self):
        super(AnimationSwitch, self).__init__()
        self.count = 0

    def traverse( self, nv ):

        self.count += 1
        if not (self.count % 60 ) :
            self.valueList[0] = not self.valueList[0]
            self.valueList[1] = not self.valueList[1]

        super(AnimationSwitch, self).traverse( nv )   

    def className( self ):
        return "AnimationSwitch"
        
# deepcopy not supported yet
model1 = osgDB.readNodeFile("cessna.osg")
model2 = osgDB.readNodeFile("cessnafire.osg")

root = AnimationSwitch()
print root.addChild( model1, False )
print root.addChild( model2, True )

viewer = osgViewer.Viewer()

viewer.setSceneData( root )

viewer.run()
