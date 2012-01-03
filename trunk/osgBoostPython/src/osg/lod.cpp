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

#include <osg/Referenced>
#include <osg/Object>
#include <osg/Node>
#include <osg/Group>
#include <osg/LOD>

using namespace osg;

#include "defaults.h"

void export_LOD()
{
 
  bool (LOD::*add_child_node)(Node *) = &LOD::addChild;
  bool (LOD::*add_child_node_min_max)(Node *, float, float) = &LOD::addChild;

  scope  in_LOD = 
    class_<LOD, bases<Group>, ref_ptr<LOD> >("LOD")
    .def("traverse", &LOD::traverse )
    .def("addChild", add_child_node )
    .def("addChild", add_child_node_min_max )
    .def("removeChildren", &LOD::removeChildren )
    .add_property("centerMode", &LOD::getCenterMode, &LOD::setCenterMode )
    .add_property("center", make_function( &LOD::getCenter, osgBoostPython::default_const_reference_policy() ), 
		  &LOD::setCenter )
    .add_property("radius", &LOD::getRadius, &LOD::setRadius )
    .add_property("rangeMode", &LOD::getRangeMode, &LOD::setRangeMode )
    .def("setRange", &LOD::setRange )
    .def("getMinRange", &LOD::getMinRange )
    .def("getMaxRange", &LOD::getMaxRange )
    .def("getNumRanges", &LOD::getNumRanges )
    .add_property("rangeList", make_function( &LOD::getRangeList, osgBoostPython::default_const_reference_policy() ), 
		  &LOD::setRangeList )
    .def("computeBound", &LOD::computeBound ) 
    ;
  
  enum_<LOD::CenterMode>("CenterMode");
  scope().attr("USE_BOUNDING_SPHERE_CENTER") = LOD::USE_BOUNDING_SPHERE_CENTER;
  scope().attr("USER_DEFINED_CENTER") = LOD::USER_DEFINED_CENTER;
  ;

  enum_<LOD::RangeMode>("RangeMode");
  scope().attr("DISTANCE_FROM_EYE_POINT") = LOD::DISTANCE_FROM_EYE_POINT;
  scope().attr("PIXEL_SIZE_ON_SCREEN") = LOD::PIXEL_SIZE_ON_SCREEN;
  ;

}
