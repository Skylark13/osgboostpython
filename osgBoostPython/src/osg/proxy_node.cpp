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
#include <osg/ProxyNode> 
using namespace osg;

#include "defaults.h"

bool(ProxyNode::*add_child1)( Node* ) = &ProxyNode::addChild;
bool(ProxyNode::*add_child2)( Node*, const std::string& ) = &ProxyNode::addChild;

Referenced*(ProxyNode::*get_db_opt) () = &ProxyNode::getDatabaseOptions;
ref_ptr<Referenced>&(ProxyNode::*get_db_req) (unsigned int ) = &ProxyNode::getDatabaseRequest;


void export_ProxyNode()
{

  scope in_ProxyNode = class_<ProxyNode, bases<Group>, ref_ptr<ProxyNode> >("ProxyNode")
    .def("traverse", &ProxyNode::traverse )
    .def("addChild", add_child1 )
    .def("addChild", add_child2 )
    .def("removeChildren", &ProxyNode::removeChildren )
    .def("getDatabaseOptions", get_db_opt, osgBoostPython::default_pointer_policy() )
    .add_property("databasePath", make_function( &ProxyNode::getDatabasePath, osgBoostPython::default_const_reference_policy() ) ,
		  &ProxyNode::setDatabasePath )
    .def("setFileName", &ProxyNode::setFileName )
    .def("getFileName", &ProxyNode::getFileName, osgBoostPython::default_const_reference_policy() )
    .def("getNumFileNames", &ProxyNode::getNumFileNames )
    .def("getDatabaseRequest", get_db_req, osgBoostPython::default_reference_policy() )    
    .add_property("centerMode", &ProxyNode::getCenterMode, &ProxyNode::setCenterMode )
    .add_property("loadingExternalReferenceMode", &ProxyNode::getLoadingExternalReferenceMode, 
		  &ProxyNode::setLoadingExternalReferenceMode )
    .add_property("center", make_function( &ProxyNode::getCenter, osgBoostPython::default_const_reference_policy() ),
		  &ProxyNode::setCenter )
    .add_property("radius", &ProxyNode::getRadius, &ProxyNode::setRadius)
    .def("computeBound", &ProxyNode::computeBound)
    ;

  enum_<ProxyNode::CenterMode>("CenterMode");
  scope().attr("USE_BOUNDING_SPHERE_CENTER") = ProxyNode::USE_BOUNDING_SPHERE_CENTER;
  scope().attr("USER_DEFINED_CENTER") = ProxyNode::USER_DEFINED_CENTER ;

  enum_<ProxyNode::LoadingExternalReferenceMode>("LoadingExternalReferenceMode");
  scope().attr("LOAD_IMMEDIATELY") = ProxyNode::LOAD_IMMEDIATELY ;
  scope().attr("DEFER_LOADING_TO_DATABASE_PAGER") = ProxyNode::DEFER_LOADING_TO_DATABASE_PAGER ;
  scope().attr("NO_AUTOMATIC_LOADING") = ProxyNode::NO_AUTOMATIC_LOADING ;

}
