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
#include <osg/CoordinateSystemNode> 
using namespace osg;

#include "defaults.h"

EllipsoidModel*(CoordinateSystemNode::*get_model)() = &CoordinateSystemNode::getEllipsoidModel;

void set_coordinate_system_node( CoordinateSystemNode& dest, CoordinateSystemNode& src) {
  dest.set( src );
}

void export_CoordinateSystemNode()
{

  class_<EllipsoidModel, bases<Object>, ref_ptr<EllipsoidModel> >("EllipsoidModel")
    .def( init< optional<double, double> >() )
    .def("convertLatLongHeightToXYZ", &EllipsoidModel::convertLatLongHeightToXYZ )
    .def("convertXYZToLatLongHeight", &EllipsoidModel::convertXYZToLatLongHeight )
    .def("computeLocalToWorldTransformFromLatLongHeight", &EllipsoidModel::computeLocalToWorldTransformFromLatLongHeight )
    .def("computeLocalToWorldTransformFromXYZ", &EllipsoidModel::computeLocalToWorldTransformFromXYZ )
    .def("computeCoordinateFrame", &EllipsoidModel::computeCoordinateFrame )
    .def("computeLocalUpVector", &EllipsoidModel::computeLocalUpVector )
    .add_property("isWGS84", &EllipsoidModel::isWGS84 )
    .add_property("radiusEquator", &EllipsoidModel::getRadiusEquator, &EllipsoidModel::setRadiusEquator )		  
    .add_property("radiusPolar", &EllipsoidModel::getRadiusPolar, &EllipsoidModel::setRadiusPolar )
    .def( self == self )
    ;

  class_<CoordinateSystemNode, bases<Group>, ref_ptr<CoordinateSystemNode>, boost::noncopyable >("CoordinateSystemNode")
    .def( init<std::string&, std::string&>() )
    .def("set", set_coordinate_system_node )
    .add_property("format", make_function( &CoordinateSystemNode::getFormat, osgBoostPython::default_const_reference_policy() ) ,
		  &CoordinateSystemNode::setFormat )
    .add_property("coordinateSystem", make_function( &CoordinateSystemNode::getCoordinateSystem, 
						     osgBoostPython::default_const_reference_policy() ) ,
		  &CoordinateSystemNode::setCoordinateSystem )
    .def("getEllipsoidModel", get_model , osgBoostPython::default_pointer_policy() )
    .def("computeLocalCoordinateFrame", &CoordinateSystemNode::computeLocalCoordinateFrame )
    .def("computeLocalUpVector", &CoordinateSystemNode::computeLocalUpVector )
    ;
}
