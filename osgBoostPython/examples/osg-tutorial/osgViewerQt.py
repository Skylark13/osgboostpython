#!/usr/bin/env python
from PyQt4.QtCore import QTimer
from PyQt4.QtGui import QWidget
from PyQt4.QtGui import QApplication
from PyQt4.QtGui import QGridLayout

import osg
import osgDB
import osgGA
import osgViewer
import osgQt

class ViewerWidget( QWidget ) :
    def __init__( self, threadingModel = osgViewer.ViewerBase.SingleThreaded ):

        self.viewer = osgViewer.CompositeViewer( )
        self.viewer.threadingModel = threadingModel 
        
        self._timer = QTimer()

        camera1 = self.createCamera(0,0,100,100)
        model1 = osgDB.readNodeFile("cow.osgt")
        widget1 = self.addViewWidget( camera1, model1 )

        camera2 = self.createCamera(0,0,100,100)
        model2 = osgDB.readNodeFile("glider.osgt")
        widget2 = self.addViewWidget( camera2, model2 )

        camera3 = self.createCamera(0,0,100,100)
        model3 = osgDB.readNodeFile("axes.osgt")
        widget3 = self.addViewWidget( camera3, model3 )

        camera4 = self.createCamera(0,0,100,100)
        model4 = osgDB.readNodeFile("fountain.osgt")
        widget4 = self.addViewWidget( camera4, model4 )

        camera5 = self.createCamera(900,100,320,240,"Popup Window", True)
        model5 = osgDB.readNodeFile("dumptruck.osgt")
        popupWidget = self.addViewWidget( camera5, model5 )
        popupWidget.show()

        grid = QGridLayout()
        grid.addWidget( widget1, 0,0)
        grid.addWidget( widget2, 0,1)
        grid.addWidget( widget3, 1,0)
        grid.addWidget( widget4, 1,1)
        self.setLayout( grid )

        # figure this out later
        #self.connect( self._timer, SIGNAL("timeout()"), self, )
        self._timer.start( 10 )


    def addViewWidget(self, camera, scene ):
        view = osgViewer.View()
        view.setCamera( camera )
        self.viewer.addView( view )

        view.setSceneData( scene )
        sh = osgViewer.StatsHandler()
        view.addEventHandler( sh )
        tm = osgGA.TrackballManipulator()
        view.setCameraManipulator( tm, True )

        gw = camera.getGraphicsContext()
        return gw.glWidget

    def createCamera(self, x, y, w, h, name="", windowDecoration = False ):
        ds = osg.DisplaySettings()

        traits = osg.GraphicsContext.Traits()
        traits.windowName = name
        traits.windowDecoration = windowDecoration
        traits.x = x
        traits.y = y
        traits.width = w
        traits.height = h
        traits.doubleBuffer = True
        traits.alpha = ds.getMinimumNumAlphaBits()
        traits.stencil = ds.getMinimumNumStencilBits()
        traits.sampleBuffers = ds.getMultiSamples()
        traits.samples = ds.getNumMultiSamples()

        camera = osg.Camera()
        gwQt = osgQt.GraphicsWindowQt( traits ) 
        camera.setGraphicsContext( gwQt )
        vp = osg.Viewport( 0, 0, traits.width, traits.height )
        camera.setViewport( vp )
        camera.setProjectionMatrixAsPerspective( 30, float(traits.width)/float(traits.height), 1, 10000)
        return camera

    def paintEvent(self, event ):
        #super( ViewerWidget, self ).frame()
        self.viewer.frame()
    

import sys

print "This isn't working and it's not clear when ( if ever ) it will work."
print "This currently segfaults.  If you want to tackle the problem, please"\
      "send an email to the mailing list for more background ( or check the docs )."
sys.exit()

threadingModel = osgViewer.ViewerBase.CullDrawThreadPerContext

app = QApplication( sys.argv )

viewWidget = ViewerWidget( threadingModel )
viewWidget.setGeometry( 100, 100, 800, 600 )
viewWidget.show()

app.exec_()



