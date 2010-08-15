#!/bin/python
#
# This source file is part of the osgBoostPython library
# 
# Copyright (C) 2009-2010 Jean-Sébastien Guay
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
import os,sys

class osgDBTest(unittest.TestCase):
    def test_000_readCow(self):
        cow = osgDB.readNodeFile("cow.osg")
        self.failUnless(cow,  'failed to read cow.osg')
    def test_000_environmentVariablesSet(self):
        if not os.environ.has_key('OSG_FILE_PATH'):
            self.fail('Environment variable OSG_FILE_PATH is not set! Cannot find testing data files.')
    
#    def test_001_exceptionWhenFileNotFound(self):
#        testOk = False
#        try:
#            anotherCow = osgDB.readNodeFile("this_file_must_not_exist.osg")
#        except Exception, inst:
#            testOk = True
#        self.failUnless(testOk, "Trying to load non-existing file does not raise an exception")

allTests = ['test_000_readCow']

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
        suite = unittest.TestSuite(map(osgDBTest, tests))
        unittest.TextTestRunner().run(suite)
