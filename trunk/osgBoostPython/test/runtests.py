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

# http://docs.python.org/library/unittest.html
# http://www.doughellmann.com/PyMOTW/unittest/
import unittest
import glob
import imp
import os

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
