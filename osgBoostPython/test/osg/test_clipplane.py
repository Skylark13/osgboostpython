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

class osgClipPlaneTest(unittest.TestCase):
    def test_000_testClassAvailable(self):
        s = osg.ClipPlane()
    def test_001_testEnumsAvailable_partial(self):
        pass #No enums defined in ClipPlane
    def test_002_testMethodsAvailable(self):
        #todo
        o = osg.ClipPlane()
        o.getType()
        o.getMember()
        #o.getModeUsage( xxx ) #todo
        o.setClipPlane(osg.Plane())
        o.setClipPlane(1.0,2.0,3.0,4.0)
        o.setClipPlane(osg.Vec4d(5.0,6.0,7.0,8.0))
        #o.getClipPlane() #todo
        o.setClipPlaneNum(3)
        o.getClipPlaneNum()

allTests = ['test_000_testClassAvailable',
            'test_001_testEnumsAvailable_partial',
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
        suite = unittest.TestSuite(map(osgClipPlaneTest, tests))
        unittest.TextTestRunner(verbosity = 2).run(suite)
