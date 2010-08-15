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
import unittest

class osgBlendFuncTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.BlendFunc()
    def test_001_testEnumsAvailable(self):
        osg.BlendFunc.DST_ALPHA
        osg.BlendFunc.DST_COLOR
        osg.BlendFunc.ONE
        osg.BlendFunc.ONE_MINUS_DST_ALPHA
        osg.BlendFunc.ONE_MINUS_DST_COLOR
        osg.BlendFunc.ONE_MINUS_SRC_ALPHA
        osg.BlendFunc.ONE_MINUS_SRC_COLOR
        osg.BlendFunc.SRC_ALPHA
        osg.BlendFunc.SRC_ALPHA_SATURATE
        osg.BlendFunc.SRC_COLOR
        osg.BlendFunc.CONSTANT_COLOR
        osg.BlendFunc.ONE_MINUS_CONSTANT_COLOR
        osg.BlendFunc.CONSTANT_ALPHA
        osg.BlendFunc.ONE_MINUS_CONSTANT_ALPHA
        osg.BlendFunc.ZERO
                
    def test_002_testMethodsAvailable(self):
        o = osg.BlendFunc()
#        o.getModeUsage(osg::StateAttribute::ModeUsage & usage)
        o.setFunction(osg.BlendFunc.ONE, osg.BlendFunc.ONE)
 #       o.setFunction(GLenum source_rgb, GLenum destination_rgb, GLenum source_alpha, GLenum destination_alpha)
#        o.setSource(GLenum source)
#        o.getSource()
#        o.setSourceRGB(GLenum source)
        o.getSourceRGB()
#        o.setSourceAlpha(GLenum source)
        o.getSourceAlpha()
#        o.setDestination(GLenum destination)
        o.getDestination()
#        o.setDestinationRGB(GLenum destination)
        o.getDestinationRGB()
 #       o.setDestinationAlpha(GLenum destination)
        o.getDestinationAlpha()
#        o.apply(osg.State())
#        o.setBlendFuncSeparateSupported(bool flag)
#        o.isBlendFuncSeparateSupported()
  #      o.glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha)

allTests = ['test_000_testClassAvailable',
            'test_001_testEnumsAvailable',
            'test_002_testMethodsAvailable', ]

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
        suite = unittest.TestSuite(map(osgBlendFuncTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
