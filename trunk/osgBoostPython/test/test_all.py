#!/bin/python

# Shouldn't have to do this, but for some reason Eric doesn't add PYTHONPATH to sys.path by default...
import sys
import os
sys.path = os.environ.get("PYTHONPATH").split(";") + sys.path[:]
print "sys.path=",  sys.path

import unittest

# Import all test modules
import test_osg
import test_osgDB
import test_osgGA
import test_osgViewer

osgTestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osg.osgTest)
osgDBTestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osgDB.osgDBTest)
osgGATestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osgGA.osgGATest)
osgViewerTestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osgViewer.osgViewerTest)

alltests = unittest.TestSuite([osgTestSuite, osgDBTestSuite, osgGATestSuite, osgViewerTestSuite])

# Run all tests
unittest.TextTestRunner().run(alltests)
