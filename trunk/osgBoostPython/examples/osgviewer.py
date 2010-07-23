#!/usr/bin/env python

#import the needed modules
import osg
import osgDB
import osgGA
import osgViewer
import osgUtil
osg.Vec3 = osg.Vec3f
osg.Matrix = osg.Matrixd
import sys

modelFile = 'cow.osg'
try:
    modelFile = sys.argv[1]
except:
    print 'You did not specify a model file. Using cow.osg as default.'

#load the model
loadedModel = osgDB.readNodeFile( modelFile )
if loadedModel == None:
    raise Exception('Loading model file failed')

root = osg.Group()
dynamicTransform1 = osg.MatrixTransform()
dynamicTransform1.addChild(loadedModel)
root.addChild(dynamicTransform1)

#create the viewer, set the scene and run
viewer = osgViewer.Viewer()
viewer.setSceneData(root)
viewer.addEventHandler(osgViewer.StatsHandler());
viewer.run()
