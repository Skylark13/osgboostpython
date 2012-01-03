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
#include <osg/Referenced>
#include <osg/Object>
#include <osg/Node> 
#include <osg/Group> 
#include <osg/NodeVisitor> 
using namespace osg;

#include "defaults.h"

void export_Node()
{

  FUNC_PTR0_CONST(const Node::ParentList&, Node, Node_getParents1, Node::getParents);
  FUNC_PTR1(Group*, Node, Node_getParent1, unsigned int, Node::getParent);
  FUNC_PTR0_CONST(const NodeCallback*, Node, Node_getUpdateCallback1, Node::getUpdateCallback);
  FUNC_PTR0_CONST(const NodeCallback*, Node, Node_getEventCallback1, Node::getEventCallback);
  FUNC_PTR0_CONST(const NodeCallback*, Node, Node_getCullCallback1, Node::getCullCallback);
    
  scope in_Node = class_<Node, bases<Object>, ref_ptr<Node> >("Node")
    .def("getNumParents", &Node::getNumParents)
    .def("getParents", Node_getParents1, osgBoostPython::default_value_policy())
    .def("getParent", Node_getParent1, osgBoostPython::default_pointer_policy())
    // TODO: NodePathList
    //.def("getParentalNodePaths", &Node::getParentalNodePaths)
    // TODO: MatrixList
    //.def("getWorldMatrices", &Node::getWorldMatrices)
    .def("accept", &Node::accept)
    .def("setUpdateCallback", &Node::setUpdateCallback)
    .def("getUpdateCallback", Node_getUpdateCallback1, osgBoostPython::default_pointer_policy())
    .def("addUpdateCallback", &Node::addUpdateCallback)
    .def("removeUpdateCallback", &Node::removeUpdateCallback)
    .def("setEventCallback", &Node::setEventCallback)
    .def("getEventCallback", Node_getEventCallback1, osgBoostPython::default_pointer_policy())
    .def("addEventCallback", &Node::addEventCallback)
    .def("removeEventCallback", &Node::removeEventCallback)
    .def("setCullCallback", &Node::setCullCallback)
    .def("getCullCallback", Node_getCullCallback1, osgBoostPython::default_pointer_policy())
    .def("addCullCallback", &Node::addCullCallback)
    .def("removeCullCallback", &Node::removeCullCallback)
    .add_property("cullingActive", &Node::getCullingActive, &Node::setCullingActive)
    .add_property("nodeMask", &Node::getNodeMask, &Node::setNodeMask)
    // TODO: Need methods related to descriptions?
    .add_property("className", &Node::className )
    .add_property("stateSet", make_function(&Node::getOrCreateStateSet, osgBoostPython::default_pointer_policy()), &Node::setStateSet)
    // TODO: wrapper returning ref_ptr for getOrCreateStateSet()
    .def("setStateSet", &Node::setStateSet)     // same call as in c++
    .def("getOrCreateStateSet", &Node::getOrCreateStateSet, osgBoostPython::default_pointer_policy())            
    .def("setInitialBound", &Node::setInitialBound)
    .def("getInitialBound", &Node::getInitialBound, osgBoostPython::default_const_reference_policy())
    .def("dirtyBound", &Node::dirtyBound)
    .def("getBound", &Node::getBound, osgBoostPython::default_const_reference_policy())
    .def("computeBound", &Node::computeBound)
    // TODO: Methods to set/get the ComputeBSphereCallback
    ;

  class_<Node::ParentList>("ParentList")
    .def( vector_indexing_suite< Node::ParentList >() )
    ;

}
