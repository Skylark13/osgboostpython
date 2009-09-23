#!/bin/python

# Shouldn't have to do this, but for some reason Eric doesn't add PYTHONPATH to sys.path by default...
import sys
import os
sys.path = os.environ.get("PYTHONPATH").split(";") + sys.path[:] 
#print "sys.path=", sys.path

# http://docs.python.org/library/unittest.html
# http://www.doughellmann.com/PyMOTW/unittest/
import unittest
import glob
import imp

print os.getcwd()

testsToSkip = ['test_osgViewer','test_all'] #needs user interaction
suites = []

for t in glob.glob('test/*/test_*.py'):
###glob.glob(os.path.join(os.getcwd() ,'test/est_*.py')):
    (modulename,waste) =  os.path.basename(t).split('.py',1)
    if modulename in testsToSkip:
        continue
    m = imp.load_source(modulename, t )
    
    for module_member in dir(m):
        handle = getattr(m, module_member)
        try:
            if issubclass(handle, unittest.TestCase):
                suites.append(unittest.TestLoader().loadTestsFromTestCase( handle ) )
                print 'Found test: ' + module_member 
        except:
            pass
alltests = unittest.TestSuite(suites)
unittest.TextTestRunner(verbosity = 2).run(alltests)

#
## Import all test modules
#import test_osg
#import test_osgDB
#import test_osgGA
#import test_osgViewer
#
#osgTestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osg.osgTest)
#osgDBTestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osgDB.osgDBTest)
#osgGATestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osgGA.osgGATest)
#osgViewerTestSuite = unittest.TestLoader().loadTestsFromTestCase(test_osgViewer.osgViewerTest)
#
#alltests = unittest.TestSuite([osgTestSuite, osgDBTestSuite, osgGATestSuite, osgViewerTestSuite])
#
## Run all tests
#unittest.TextTestRunner().run(alltests)
