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
#include <osg/OccluderNode> 
using namespace osg;

#include "defaults.h"

ConvexPlanarOccluder*(OccluderNode::*get_occluder)() = &OccluderNode::getOccluder;

void export_OccluderNode()
{

  scope in_OccluderNode = class_<OccluderNode, bases<Group>, ref_ptr<OccluderNode> >("OccluderNode")
    .add_property("occluder", make_function( get_occluder, osgBoostPython::default_pointer_policy() ) 
		  ,&OccluderNode::setOccluder )
    .def("computeBound", &OccluderNode::computeBound )
    ;

}
