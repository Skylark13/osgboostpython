/*
* This source file is part of the osgBoostPython library
* 
* Copyright (C) 2009-2010 Jean-Sébastien Guay
* 
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License as published by the Free Software
* Foundation; either version 3 of the License, or (at your option) any later
* version.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
* http://www.gnu.org/copyleft/lesser.txt.
*/

#include <boost/python.hpp>
using namespace boost::python;

#include <osgViewer/ViewerEventHandlers>

using namespace osg;
using namespace osgViewer;

#include "defaults.h"

void export_ViewerEventHandlers()
{
    class_<HelpHandler, bases<osgGA::GUIEventHandler>, ref_ptr<HelpHandler> >("HelpHandler")
    ;

    class_<StatsHandler, bases<osgGA::GUIEventHandler>, ref_ptr<StatsHandler> >("StatsHandler")
    ;
}
