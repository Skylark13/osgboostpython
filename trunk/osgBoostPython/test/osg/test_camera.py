#!/bin/python
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
import unittest
import re
import os

class TestFile:
    """
    Read a textfile and search for patterns in it.
    """
    def __init__(self,filename,utest):
        fh = open(filename,'r')
        self._s = fh.read()
        fh.close()
        self._t = utest
        self._fname = file
    def shouldContain(self, pattern):
        if re.search(pattern, self._s) != None:
            return True
        else:
            return False

class osgCameraTest(unittest.TestCase):
    def test_000_osgCamera(self):
        cam = osg.Camera()
        cam.setViewport(0,0,480,320) #tested
        cam.setClearColor(osg.Vec4f(0,1,45,0)) #tested
        cam.setClearMask(0x4030) #availability, test below
        #try:
        #    cam.setClearMask(0xfffffffff)
        #    self.fail('No overflow when setting extremely large clear mask')
        #except OverflowError:
        #    pass

        cam.setProjectionMatrixAsFrustum(-10,100,-20,10,0.0,100.0)
        mt = osg.Matrixd()
        cam.setReferenceFrame(osg.Camera.ABSOLUTE_RF) #tested
        cam.setViewMatrixAsLookAt(osg.Vec3d(),osg.Vec3d(),osg.Vec3d())
        cam.setRenderOrder(osg.Camera.POST_RENDER,0); #tested
        cam.setRenderTargetImplementation(osg.Camera.FRAME_BUFFER_OBJECT) #tested
        cam.setDefaultClearMask() #availability
        texture = osg.Texture2D()
        cam.attach(osg.Camera.COLOR_BUFFER, texture, 0, 0, False, 0, 0); #tested
        cam.addChild(osg.Geode()) #tested
        cam.setClearMask(0x4545) #tested
        #write scene graph to disc
        if os.path.exists('out.osg'):
            os.remove('out.osg')
        osgDB.writeNodeFile(cam, 'out.osg')
        #read in scene graph file in text and search for specified patterns
        t = TestFile('out.osg',self)
        re.DOTALL = True #whitespace pattern \s shall match newline, too
        self.assert_(t.shouldContain('.*FRAME_BUFFER_OBJECT.*'))
        self.assert_(t.shouldContain('referenceFrame ABSOLUTE'))
        self.assert_(t.shouldContain('renderOrder POST_RENDER'))
        self.assert_(not t.shouldContain('i am a string that should not appear' ))
        self.assert_(t.shouldContain('clearMask 0x4545'))
        self.assert_(t.shouldContain('bufferComponent COLOR_BUFFER'))
        self.assert_(t.shouldContain('clearColor 0 1 45 0'))
        self.assert_(t.shouldContain(r'x\s+0\s+y\s+0\s+width\s+480\s+height\s+320'))
        self.assert_(t.shouldContain('Geode'))
        if os.path.exists('out.osg'):
            os.remove('out.osg')

    def test_001_testEnumsAvailable(self):
        osg.Camera.FRAME_BUFFER_OBJECT;
        osg.Camera.PIXEL_BUFFER_RTT;
        osg.Camera.PIXEL_BUFFER;
        osg.Camera.FRAME_BUFFER;
        osg.Camera.SEPERATE_WINDOW;

        #enum_<osg.Camera.RenderOrder>("RenderOrder");
        osg.Camera.PRE_RENDER;
        osg.Camera.NESTED_RENDER;
        osg.Camera.POST_RENDER;

        #enum_<osg.Camera.BufferComponent>("BufferComponent");
        osg.Camera.DEPTH_BUFFER;
        osg.Camera.STENCIL_BUFFER;
        osg.Camera.PACKED_DEPTH_STENCIL_BUFFER;
        osg.Camera.COLOR_BUFFER;
        osg.Camera.COLOR_BUFFER0;
        osg.Camera.COLOR_BUFFER1;
        osg.Camera.COLOR_BUFFER2;
        osg.Camera.COLOR_BUFFER3;
        osg.Camera.COLOR_BUFFER4;
        osg.Camera.COLOR_BUFFER5;
        osg.Camera.COLOR_BUFFER6;
        osg.Camera.COLOR_BUFFER7;
        osg.Camera.COLOR_BUFFER8;
        osg.Camera.COLOR_BUFFER9;
        osg.Camera.COLOR_BUFFER10;
        osg.Camera.COLOR_BUFFER11;
        osg.Camera.COLOR_BUFFER12;
        osg.Camera.COLOR_BUFFER13;
        osg.Camera.COLOR_BUFFER14;
        osg.Camera.COLOR_BUFFER15;

        #enum_< osg.Camera.ProjectionResizePolicy>("ProjectionResizePolicy");
        osg.Camera.FIXED;
        osg.Camera.HORIZONTAL;
        osg.Camera.VERTICAL;

        #enum_< osg.Camera.TransformOrder>("TransformOrder");
        osg.Camera.PRE_MULTIPLY;
        osg.Camera.POST_MULTIPLY;

allTests = ['test_000_osgCamera',
            'test_001_testEnumsAvailable', ]

# To be able to run one single test from the command line. Could be name-based instead of index-based...
if __name__ == "__main__":
    import sys
    testToRun = -1
    if (len(sys.argv) == 2):
        testToRun = int(sys.argv[1])

    if (testToRun == -1):
        unittest.main()
    else:
        tests = [allTests[testToRun]]
        suite = unittest.TestSuite(map(osgCameraTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
