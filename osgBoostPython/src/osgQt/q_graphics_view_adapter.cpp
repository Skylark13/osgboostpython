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

#include <osgQt/QGraphicsViewAdapter>
using namespace osg;
using namespace osgQt;

#include "defaults.h"

void export_QGraphicsViewAdapter()
{

  class_<QGraphicsViewAdapter, bases<QObject>, boost::noncopyable >
    ("QGraphicsViewAdapter", init<Image*, QWidget* >() )
    .def("setUpKeyMap", &QGraphicsViewAdapter::setUpKeyMap )
    .def("sendPointerEvent", &QGraphicsViewAdapter::sendPointerEvent )
    .def("sendKeyEvent", &QGraphicsViewAdapter::sendKeyEvent )
    .def("setFrameLastRendered", &QGraphicsViewAdapter::setFrameLastRendered )
    .def("clearWriteBuffer", &QGraphicsViewAdapter::clearWriteBuffer )
    .def("render", &QGraphicsViewAdapter::render )
    .def("assignImage", &QGraphicsViewAdapter::assignImage )
    .def("resize", &QGraphicsViewAdapter::resize )
    .add_property("backgroundColor", &QGraphicsViewAdapter::getBackgroundColor, &QGraphicsViewAdapter::setBackgroundColor )    
    .def("getQGraphicsView", &QGraphicsViewAdapter::getQGraphicsView,  osgBoostPython::default_pointer_policy() )    
    .def("getQGraphicsScene", &QGraphicsViewAdapter::getQGraphicsScene,  osgBoostPython::default_pointer_policy() )    
    ;
    
}
