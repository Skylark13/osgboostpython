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

#include <osg/Image>
#include <osgQt/QWidgetImage>
using namespace osg;
using namespace osgQt;

#include "defaults.h"

void export_QWidgetImage()
{

  class_<QWidgetImage, bases<Image> >
    ("QWidgetImage", init< optional<QWidget*> >() )
    .def("getQWidget", &QWidgetImage::getQWidget, osgBoostPython::default_pointer_policy() )
    .def("getQGraphicsViewAdapter", &QWidgetImage::getQGraphicsViewAdapter, osgBoostPython::default_pointer_policy() )
    .def("clearWriteBuffer", &QWidgetImage::clearWriteBuffer )
    .def("render", &QWidgetImage::render )
    .def("scaleImage", &QWidgetImage::scaleImage )
    .def("sendFocusHint", &QWidgetImage::sendFocusHint )
    .def("sendPointerEvent", &QWidgetImage::sendPointerEvent )
    .def("sendKeyEvent", &QWidgetImage::sendKeyEvent )
    .def("setFrameLastRendered", &QWidgetImage::setFrameLastRendered )
    ;
    
}
