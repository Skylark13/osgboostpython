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

# the import has to be here
# need to read up on python frames
# to understand why...it doesn't
# end up in globals() or locals()...dunno
from PyQt4.QtCore import QObject
from PyQt4.QtGui import QWidget
from PyQt4.QtOpenGL import QGLWidget

from osg import Object
from osgGA import GUIActionAdapter
from osgViewer import GraphicsWindow

from osg import Image

from _osgQt import *


