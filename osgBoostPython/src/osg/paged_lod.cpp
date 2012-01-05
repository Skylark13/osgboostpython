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
#include <osg/PagedLOD>

using namespace osg;

#include "defaults.h"


bool (PagedLOD::*add_child_node)(Node *) = &PagedLOD::addChild;
bool (PagedLOD::*add_child_node_min_max)(Node *, float, float) = &PagedLOD::addChild;
bool (PagedLOD::*add_child_node_min_max_fn_flt_flt)(Node *, float, float, const std::string&, float, float) = &PagedLOD::addChild;

bool add_child1( PagedLOD& p, Node* node, float min, float max, const std::string& filename, float priorityOffset){
  return p.addChild( node, min, max, filename, priorityOffset );
}
bool add_child2( PagedLOD& p, Node* node, float min, float max, const std::string& filename ){
  return p.addChild( node, min, max, filename );
}

Referenced*(PagedLOD::*get_db_opt)() = &PagedLOD::getDatabaseOptions;
const std::string& (PagedLOD::*get_db_path)() = &PagedLOD::getDatabasePath;

void export_PagedLOD()
{
 
  scope  in_PagedLOD = 
    class_<PagedLOD, bases<LOD>, ref_ptr<PagedLOD> >("PagedLOD")
    .def("traverse", &PagedLOD::traverse )
    .def("addChild", add_child_node )
    .def("addChild", add_child_node_min_max )
    .def("addChild", add_child_node_min_max_fn_flt_flt )
    .def("addChild", add_child1 )
    .def("addChild", add_child2 )
    .def("removeChildren", &PagedLOD::removeChildren )
    .add_property("databaseOptions", make_function( get_db_opt, osgBoostPython::default_pointer_policy() ),
	 &PagedLOD::setDatabaseOptions )
    .add_property("databasePath", make_function( get_db_path, osgBoostPython::default_const_reference_policy() ),
	 &PagedLOD::setDatabasePath )
    
    ;
  
  class_<PagedLOD::PerRangeData>("PerRangeData")
    .def_readwrite("filename", &PagedLOD::PerRangeData::_filename)
    .def_readwrite("priorityOffset", &PagedLOD::PerRangeData::_priorityOffset)
    .def_readwrite("priorityScale", &PagedLOD::PerRangeData::_priorityScale)
    .def_readwrite("timeStamp", &PagedLOD::PerRangeData::_timeStamp)
    .def_readwrite("frameNumber", &PagedLOD::PerRangeData::_frameNumber)
    .def_readwrite("frameNumberOfLastReleaseGLObjects", &PagedLOD::PerRangeData::_frameNumberOfLastReleaseGLObjects)
    .def_readwrite("databaseRequest", &PagedLOD::PerRangeData::_databaseRequest)
    ;


}
