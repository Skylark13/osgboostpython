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
#include <osg/State>
#include <osg/Node> 
#include <osg/Group> 
#include <osg/NodeVisitor> 
using namespace osg;

#include "defaults.h"

NodePathList get_parental_node_paths0(Node& self){
  return self.getParentalNodePaths();
}
NodePathList get_parental_node_paths1(Node& self, Node* node){
  return self.getParentalNodePaths( node );
}

MatrixList get_world_matrices0(Node& self){
  return self.getWorldMatrices();
}

MatrixList get_world_matrices1(Node& self, Node* node){
  return self.getWorldMatrices( node );
}

struct ComputeBoundingSphereCallback_wrapper : public Node::ComputeBoundingSphereCallback
{
    // ComputeBoundingSphereCallback constructor storing initial self parameter
    ComputeBoundingSphereCallback_wrapper(PyObject *p)
        : ComputeBoundingSphereCallback(), self(p){}

    // In case ComputeBoundingSphereCallback is returned by-value from a wrapped function
    ComputeBoundingSphereCallback_wrapper(PyObject *p, const ComputeBoundingSphereCallback& x)
        : ComputeBoundingSphereCallback(x), self(p) {}

    // Override operator() to call back into Python
    BoundingSphere computeBound( const Node& node ) const {
      try {
	call_method<void>(self, "computeBound", boost::cref(node) );
      } catch (error_already_set) {
	ComputeBoundingSphereCallback::computeBound( node );
      }
    }

    // Supplies the default implementation of operator()
  BoundingSphere default_computeBound( const Node& node ) const {
    ComputeBoundingSphereCallback::computeBound( node );
  }

 private:
    PyObject* self;
};

void release_gl_objects1( Node& self, State* s ){ self.releaseGLObjects( s ); }
void release_gl_objects0( Node& self ){ self.releaseGLObjects( ); }

void export_Node()
{

  FUNC_PTR0_CONST(const Node::ParentList&, Node, Node_getParents1, Node::getParents);
  FUNC_PTR1(Group*, Node, Node_getParent1, unsigned int, Node::getParent);
  FUNC_PTR0_CONST(const NodeCallback*, Node, Node_getUpdateCallback1, Node::getUpdateCallback);
  FUNC_PTR0_CONST(const NodeCallback*, Node, Node_getEventCallback1, Node::getEventCallback);
  FUNC_PTR0_CONST(const NodeCallback*, Node, Node_getCullCallback1, Node::getCullCallback);
    
  const Node::DescriptionList&(Node::*get_descriptions)() const = &Node::getDescriptions;
  const std::string&(Node::*get_description)(unsigned int) const = &Node::getDescription;
  const Node::ComputeBoundingSphereCallback* (Node::*get_compute_bounding_sphere_callback)() const = 
    &Node::getComputeBoundingSphereCallback;

  {
    scope in_Node = class_<Node, bases<Object>, ref_ptr<Node> >("Node")
      .def("getNumParents", &Node::getNumParents)
      .def("getParents", Node_getParents1, osgBoostPython::default_value_policy())
      .def("getParent", Node_getParent1, osgBoostPython::default_pointer_policy())
      .def("getParentalNodePaths", get_parental_node_paths0)
      .def("getParentalNodePaths", get_parental_node_paths1)
      .def("getWorldMatrices", get_world_matrices0)
      .def("getWorldMatrices", get_world_matrices1)
      .def("accept", &Node::accept)
      .def("ascend", &Node::ascend)
      .def("setUpdateCallback", &Node::setUpdateCallback)
      .def("getUpdateCallback", Node_getUpdateCallback1, osgBoostPython::default_pointer_policy())
      .def("addUpdateCallback", &Node::addUpdateCallback)
      .def("removeUpdateCallback", &Node::removeUpdateCallback)
      .add_property("numChildrenRequiringUpdateTraversal", &Node::getNumChildrenRequiringUpdateTraversal )
      .def("setEventCallback", &Node::setEventCallback)
      .def("getEventCallback", Node_getEventCallback1, osgBoostPython::default_pointer_policy())
      .def("addEventCallback", &Node::addEventCallback)
      .def("removeEventCallback", &Node::removeEventCallback)
      .add_property("numChildrenRequiringEventTraversal", &Node::getNumChildrenRequiringEventTraversal )
      .def("setCullCallback", &Node::setCullCallback)
      .def("getCullCallback", Node_getCullCallback1, osgBoostPython::default_pointer_policy())
      .def("addCullCallback", &Node::addCullCallback)
      .def("removeCullCallback", &Node::removeCullCallback)
      .add_property("numChildrenWithCullingDisabled", &Node::getNumChildrenWithCullingDisabled )
      .add_property("cullingActive", &Node::getCullingActive, &Node::setCullingActive)
      .add_property("isCullingActive", &Node::isCullingActive )
      .add_property("numChildrenWithOccluderNodes", &Node::getNumChildrenWithOccluderNodes )
      .add_property("containsOccluderNodes", &Node::containsOccluderNodes )
      .add_property("nodeMask", &Node::getNodeMask, &Node::setNodeMask)
      // this should allow us to copy from python w/o using the copy module 
      .def("cloneType", &Node::cloneType, osgBoostPython::default_pointer_policy() )
      .def("clone", &Node::clone, osgBoostPython::default_pointer_policy() ) 
      .def("isSameKindAs", &Node::isSameKindAs )
      .add_property("libraryName", &Node::libraryName )
      .add_property("className", &Node::className )
      // not going to wrap the 'as' methods
      // these shouldn't be needed on the python side
      // I don't see why they're needed on the C++ side, but we'll see...
      .add_property("stateSet", make_function(&Node::getOrCreateStateSet, osgBoostPython::default_pointer_policy()), &Node::setStateSet)
      .def("setStateSet", &Node::setStateSet)     // same call as in c++
      .def("getOrCreateStateSet", &Node::getOrCreateStateSet, osgBoostPython::default_pointer_policy())
      .add_property("descriptions", make_function( get_descriptions, osgBoostPython::default_const_reference_policy()),
		    &Node::setDescriptions ) // probably going to need list to vector<string> converter
      .def("getDescription", get_description, osgBoostPython::default_const_reference_policy() )	   
      .def("addDescription", &Node::addDescription) 
      .def("setInitialBound", &Node::setInitialBound)
      .def("getInitialBound", &Node::getInitialBound, osgBoostPython::default_const_reference_policy())
      .def("dirtyBound", &Node::dirtyBound)
      .def("getBound", &Node::getBound, osgBoostPython::default_const_reference_policy())
      .def("computeBound", &Node::computeBound)
      .add_property("computeBoundingSphereCallback", 
		    make_function( get_compute_bounding_sphere_callback, osgBoostPython::default_pointer_policy() ),
		    &Node::setComputeBoundingSphereCallback)
      .def("setThreadSafeRefUnref", &Node::setThreadSafeRefUnref )
      .def("resizeGLObjectBuffers", &Node::resizeGLObjectBuffers )
      .def("releaseGLObjects", release_gl_objects0 )
      .def("releaseGLObjects", release_gl_objects1 )
      ;
    
    class_<Node::ParentList>("ParentList")
      .def( vector_indexing_suite< Node::ParentList >() )
      ;

    class_<Node::DescriptionList>("DescriptionList")
      .def( vector_indexing_suite< Node::DescriptionList >() )
      ;

    class_<Node::ComputeBoundingSphereCallback, ComputeBoundingSphereCallback_wrapper, 
      bases<Object>, ref_ptr<Node::ComputeBoundingSphereCallback> >("ComputeBoundingSphereCallback")
      //.def("computeBound", &Node::ComputeBoundingSphereCallback::computeBound, 
      //	   &ComputeBoundingSphereCallback_wrapper::default_computeBound)
      // Node's protected destructor is causing problems here because of the const reference.
      // going to punt for the time being
    ;

  }

  // python warns that there's a duplicate registration of vector<Node*>
  // though I haven't found it yet.  not going to worry about it right now.
  //class_<NodePath>("NodePath")
  //  .def( vector_indexing_suite< NodePath >() )
  //  ;
  
  class_<NodePathList>("NodePathList")
    .def( vector_indexing_suite< NodePathList >() )
    ;
  
  class_<MatrixList>("MatrixList")
    .def( vector_indexing_suite< MatrixList >() )
    ;

}
