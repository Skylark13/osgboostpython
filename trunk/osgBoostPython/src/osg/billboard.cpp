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
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;

#include <osg/ref_ptr>
#include <osg/Billboard>
using namespace osg;

#include "defaults.h"

bool(Billboard::*add_drawable1)(Drawable*) = &Billboard::addDrawable;
bool(Billboard::*add_drawable2)(Drawable*, const Vec3&) = &Billboard::addDrawable;
Billboard::PositionList&(Billboard::*get_position_list)() = &Billboard::getPositionList;

void export_Billboard() {

  scope in_Billboard = class_<Billboard, bases<Geode>, ref_ptr<Billboard> >("Billboard")
    .add_property("mode", &Billboard::getMode, &Billboard::setMode)
    .add_property("axis", make_function( &Billboard::getAxis, osgBoostPython::default_const_reference_policy() ),
		 &Billboard::setAxis )
    .add_property("normal", make_function( &Billboard::getNormal, osgBoostPython::default_const_reference_policy() ),
		  &Billboard::setNormal )
    .add_property("position", make_function( &Billboard::getPosition, osgBoostPython::default_const_reference_policy() ),
		  &Billboard::setPosition )
    .add_property("positionList", make_function( get_position_list, osgBoostPython::default_reference_policy() ),
		  &Billboard::setPositionList )
    .def("addDrawable", add_drawable1)
    .def("addDrawable", add_drawable2)
    .def("removeDrawable", &Billboard::removeDrawable)
    .def("computeMatrix", &Billboard::computeMatrix)
    .def("computeBound", &Billboard::computeBound)
    ;  
    
  enum_<Billboard::Mode>("Mode");
  scope().attr("POINT_ROT_EYE") = Billboard::POINT_ROT_EYE;

  class_< Billboard::PositionList >("PositionList")
    .def( vector_indexing_suite< Billboard::PositionList >() )
    ;

}
