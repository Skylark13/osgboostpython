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

class osgStateAttributeTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.StateAttribute #Class cannot be instantiated from python ...
    def test_001_testEnumsAvailable_partial(self):
        #Functions
        osg.StateSet.INHERIT_RENDERBIN_DETAILS
        osg.StateSet.USE_RENDERBIN_DETAILS
        osg.StateSet.OVERRIDE_RENDERBIN_DETAILS
        
    def test_002_testMethodsAvailable(self):
        #todo
        s = osg.StateSet()
        s.setRenderBinDetails(1, 'test')
        
    def test_003_testDepthEnumsAvailable(self):
        osg.Depth.NEVER;
        osg.Depth.LESS;
        osg.Depth.EQUAL;
        osg.Depth.LEQUAL;
        osg.Depth.GREATER;
        osg.Depth.NOTEQUAL;
        osg.Depth.GEQUAL;
        osg.Depth.ALWAYS;    

allTests = ['test_000_testClassAvailable',
            'test_001_testEnumsAvailable_partial',
            'test_002_testMethodsAvailable',
            'test_003_testDepthEnumsAvailable', ]

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
        suite = unittest.TestSuite(map(osgStateAttributeTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
