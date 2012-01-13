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

#include <osgViewer/ViewerBase>

using namespace osg;
using namespace osgViewer;

#include "defaults.h"

void export_ViewerBase()
{
  scope in_ViewerBase = class_<ViewerBase, bases<Object>, boost::noncopyable>("ViewerBase", no_init)
    .add_property("threadingModel", &ViewerBase::getThreadingModel, &ViewerBase::setThreadingModel )
    .def("frame", &ViewerBase::frame)
    ;

    enum_<ViewerBase::ThreadingModel>("ThreadingModel");
    scope().attr("SingleThreaded") = ViewerBase::SingleThreaded ;
    scope().attr("CullDrawThreadPerContext") = ViewerBase::CullDrawThreadPerContext ;
    scope().attr("ThreadPerContext") = ViewerBase::ThreadPerContext ;
    scope().attr("DrawThreadPerContext") = ViewerBase::DrawThreadPerContext ;
    scope().attr("CullThreadPerCameraDrawThreadPerContext") = ViewerBase::CullThreadPerCameraDrawThreadPerContext ;
    scope().attr("ThreadPerCamera") = ViewerBase::ThreadPerCamera ;
    scope().attr("AutomaticSelection") = ViewerBase::AutomaticSelection ;

    enum_<ViewerBase::BarrierPosition>("BarrierPosition");
    scope().attr("BeforeSwapBuffers") = ViewerBase::BeforeSwapBuffers ;
    scope().attr("AfterSwapBuffers") = ViewerBase::AfterSwapBuffers ;

}
