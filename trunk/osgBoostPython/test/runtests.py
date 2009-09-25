#!/bin/python

# http://docs.python.org/library/unittest.html
# http://www.doughellmann.com/PyMOTW/unittest/
import unittest
import glob
import imp

print os.getcwd()

testsToSkip = ['test_osgViewer'] #needs user interaction
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
