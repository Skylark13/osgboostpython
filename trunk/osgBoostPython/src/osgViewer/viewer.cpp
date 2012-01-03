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

#include <osgViewer/Viewer>

using namespace osg;
using namespace osgViewer;

#include "defaults.h"

// Generates thin wrappers for methods that have default arguments
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/python/functions.html#python.default_arguments
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(osgViewer_frame_overloads, frame, 0, 1)

//Node* (Drawable::*Drawable_getParent1)( unsigned int ) = &Drawable::getParent;
osg::Camera* (Viewer::*Viewer_getCameraWithFocus1)() = &Viewer::getCameraWithFocus;

void export_Viewer()
{

    // Need wrapper for osgViewer::View, which needs wrapper for osg::View, ...
    class_<Viewer, bases<osgViewer::View, osgViewer::ViewerBase>, ref_ptr<Viewer> >("Viewer")
        .def("run", &Viewer::run)
        .def("done", &Viewer::done)
        .def("frame", &Viewer::frame, osgViewer_frame_overloads())
        .def("addEventHandler", &Viewer::addEventHandler)
        .def("setSceneData", &Viewer::setSceneData)
        .def("getCameraWithFocus", Viewer_getCameraWithFocus1, osgBoostPython::default_pointer_policy())
    ;

}
