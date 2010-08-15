#!/usr/bin/env python
#
# This source file is part of the osgBoostPython library
# 
# Copyright (C) 2009-2010 Jean-Sebastien Guay
# 
# This program is free software; you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free Software
# Foundation; either version 3 of the License, or (at your option) any later
# version.
# 
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
# http://www.gnu.org/copyleft/lesser.txt.
#

import osg
import osgDB
import osgGA
import osgViewer
import unittest
osg.Vec3 = osg.Vec3f
osg.Matrix = osg.Matrixd
import sys
from tempfile import *
import os


class CollectStdErr:
    ##Code taken from distutils
    ##see http://aspn.activestate.com/ASPN/Mail/Message/565864
     def capture_output (self):
         """Temporarily redirect stdout and stderr to files, the
         contents of which will be returned by 'stop_capture()'."""
         self.out_filename = mktemp()
         self.err_filename = mktemp()
         self.out_file = open(self.out_filename, 'w')
         self.err_file = open(self.err_filename, 'w')
         self.save_stdout = os.dup(1)
         self.save_stderr = os.dup(2)
         os.close(1)
         if os.dup(self.out_file.fileno()) != 1:
             raise RuntimeError, "couldn't redirect stdout - dup() error"
         os.close(2)
         if os.dup(self.err_file.fileno()) != 2:
             raise RuntimeError, "couldn't redirect stderr - dup() error"
 
     def stop_capture (self):
         os.close(1)
         os.dup(self.save_stdout)
         os.close(2)
         os.dup(self.save_stderr)
 
         self.out_file.close()
         self.err_file.close()
 
         out_file = open(self.out_filename)
         output = out_file.read()
         out_file.close()
         os.unlink (self.out_filename)
 
         err_file = open(self.err_filename)
         error = err_file.read()
         err_file.close()
         os.unlink (self.err_filename)
 
         return (output, error)
        
class DerivedHandler(osgGA.GUIEventHandler):
    def __init__(self):
        osgGA.GUIEventHandler.__init__(self)

    def handle(self, ea, aa, obj, nv):
        return True

class osgGADerivedGUIEventHandlerTest(unittest.TestCase):
    def tearDown(self):
        (output,collectedErrMessages) = self._coll.stop_capture()
        if len( collectedErrMessages ) > 5:
            self.fail('Error message after viewer.run(): '+ collectedErrMessages)
    def test_000_segfaultOnShutdown(self):
        modelFile = 'cow.osg'
        #load the model
        loadedModel = osgDB.readNodeFile( modelFile )
        if loadedModel == None:
            raise Exception('Loading model file failed')
        
        root = osg.Group()
        root.addChild(loadedModel)
        #create the viewer, set the scene and run
        viewer = osgViewer.Viewer()
        viewer.setUpViewInWindow(50, 50, 640,480);
        viewer.setSceneData(root)

        h = DerivedHandler()
        viewer.addEventHandler(h);
        #run the viewer 
        viewer.frame()
        self._coll = CollectStdErr() #start error collection after viewer...
        self._coll.capture_output()
        
if __name__ == "__main__":
        unittest.main()


