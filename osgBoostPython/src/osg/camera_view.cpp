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

#include <osg/CameraView>

using namespace osg;

#include "defaults.h"

void export_CameraView()
{
  scope in_CameraView = class_<CameraView, bases<Transform>, ref_ptr<CameraView> >("CameraView")
    .add_property("position", make_function( &CameraView::getPosition, osgBoostPython::default_const_reference_policy() ),
		  &CameraView::setPosition )
    .add_property("attitude", make_function( &CameraView::getAttitude, osgBoostPython::default_const_reference_policy() ),
		  &CameraView::setAttitude )
    .add_property("fieldOfView", &CameraView::getFieldOfView, &CameraView::setFieldOfView )
    .add_property("fieldOfViewMode", &CameraView::getFieldOfViewMode, &CameraView::setFieldOfViewMode )
    .add_property("focalLength", &CameraView::getFocalLength, &CameraView::setFocalLength )    
    //.def("computeLocalToWorldMatrix", &CameraView::computeLocalToWorldMatrix )
    //.def("computeWorldToLocalMatrix", &CameraView::computeWorldToLocalMatrix )
    ;
  
   
  enum_<CameraView::FieldOfViewMode>("FieldOfViewMode");
  scope().attr("UNCONSTRAINED") = CameraView::UNCONSTRAINED;
  scope().attr("HORIZONTAL") = CameraView::HORIZONTAL;
  scope().attr("VERTICAL") = CameraView::VERTICAL;
   
}
