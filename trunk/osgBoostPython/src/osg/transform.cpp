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

#include <osg/ref_ptr>
#include <osg/Transform>
using namespace osg;

#include "defaults.h"

void export_Transform()
{
  // Abstract class
  scope in_Transform = class_<Transform, bases<Group>, ref_ptr<Transform>, boost::noncopyable >("Transform", no_init)
    .add_property("referenceFrame", &Transform::getReferenceFrame, &Transform::setReferenceFrame)
    .def("computeLocalToWorldMatrix", &Transform::computeLocalToWorldMatrix)
    .def("computeWorldToLocalMatrix", &Transform::computeWorldToLocalMatrix)
    ;

  enum_<Transform::ReferenceFrame>("ReferenceFrame");
  scope().attr("RELATIVE_RF") = Transform::RELATIVE_RF;
  scope().attr("ABSOLUTE_RF") = Transform::ABSOLUTE_RF;
  scope().attr("ABSOLUTE_RF_INHERIT_VIEWPOINT") = Transform::ABSOLUTE_RF_INHERIT_VIEWPOINT;
  
}
