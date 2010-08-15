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
//#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

//#include <osg/StateAttribute>
#include <osg/ClipPlane>
using namespace osg;

#include "defaults.h"

void (ClipPlane::*ClipPlane_setClipPlane1)(osg::Plane const & plane) = & ClipPlane::setClipPlane;
void (ClipPlane::*ClipPlane_setClipPlane2)(double a, double b, double c, double d) = & ClipPlane::setClipPlane;
void (ClipPlane::*ClipPlane_setClipPlane3)(osg::Vec4d const & plane) = & ClipPlane::setClipPlane;

void export_clipplane() {

    class_<ClipPlane, bases<StateAttribute>, ref_ptr<ClipPlane>, boost::noncopyable >("ClipPlane")
        .def(init<>())
        .def("getType", &ClipPlane::getType)
        //.def("getClipPlane", &ClipPlane::getClipPlane) //returns const Vec4d &
        .def("setClipPlane", ClipPlane_setClipPlane3)
        .def("setClipPlane", ClipPlane_setClipPlane2)
        //.def("getModeUsage", &ClipPlane::getModeUsage)
        .def("setClipPlane", ClipPlane_setClipPlane1)
        .def("getMember", &ClipPlane::getMember)
        .def("setClipPlaneNum", &ClipPlane::setClipPlaneNum)
        .def("getClipPlaneNum", &ClipPlane::getClipPlaneNum)
    ; 
    
}
