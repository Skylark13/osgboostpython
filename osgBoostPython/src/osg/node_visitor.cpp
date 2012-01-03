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

#include <osg/NodeVisitor>
#include <osg/Group>
#include <osg/Node>
#include <osg/Switch>

using namespace osg;

#include "defaults.h"
#include <boost/preprocessor/seq/for_each.hpp>

#define WRAP_THESE \
  (Node)(Group)(Switch)
 
#define APPLY_WRAP( r, data, classname )					\
  void apply(classname& node) {     \
    try{     \
      call_method<void>(self, "apply_"#classname, boost::ref(node));  \
    } catch (error_already_set) {     \
      NodeVisitor::apply( node ); \
    }                              \
 }	\
  void BOOST_PP_CAT(apply_,classname)  ( classname& node ){ NodeVisitor::apply(node); }

#define APPLY_DEF( r, data, classname )					\
  .def("apply_"#classname, BOOST_PP_CAT(&NodeVisitor_wrapper::apply_ , classname) )


struct NodeVisitor_wrapper : public NodeVisitor
{
    // NodeVisitor constructors storing initial self parameter
    NodeVisitor_wrapper(PyObject *p, NodeVisitor::TraversalMode tm = NodeVisitor::TRAVERSE_NONE)
        : NodeVisitor(tm), self(p) {}

    NodeVisitor_wrapper(PyObject *p, NodeVisitor::VisitorType type, NodeVisitor::TraversalMode tm = NodeVisitor::TRAVERSE_NONE)
        : NodeVisitor(type, tm), self(p) {}

    // In case NodeVisitor is returned by-value from a wrapped function
    NodeVisitor_wrapper(PyObject *p, const NodeVisitor& x)
        : NodeVisitor(x), self(p) {}

  BOOST_PP_SEQ_FOR_EACH( APPLY_WRAP,,WRAP_THESE ) 

  // Override apply to call back into Python
  const char* className(){ 
    try{
      return call_method<const char *>(self, "className");
    } catch (error_already_set) {
      return NodeVisitor::className();
    }
  }
  // Supplies the default implementation
  const char*class_name(){ return NodeVisitor::className(); }

 private:
    PyObject* self;
};

void export_NodeVisitor()
{

  scope in_NodeVisitor = class_<NodeVisitor, NodeVisitor_wrapper, bases<Referenced>, ref_ptr<NodeVisitor> >("NodeVisitor")
    .def(init<NodeVisitor::TraversalMode>())
    .def(init<NodeVisitor::VisitorType, NodeVisitor::TraversalMode>())
    .def("traverse", &NodeVisitor::traverse)
    BOOST_PP_SEQ_FOR_EACH(APPLY_DEF,,WRAP_THESE)
    .add_property("traversalMode", &NodeVisitor::getTraversalMode, &NodeVisitor::setTraversalMode)
    .def("getFrameStamp", &NodeVisitor::getFrameStamp, osgBoostPython::default_pointer_policy())
    .add_property("className", &NodeVisitor_wrapper::class_name  )
    .add_property("visitorType", &NodeVisitor::getVisitorType)
    ;
  
  enum_<NodeVisitor::TraversalMode>("TraversalMode");
  scope().attr("TRAVERSE_NONE") = NodeVisitor::TRAVERSE_NONE;
  scope().attr("TRAVERSE_PARENTS") = NodeVisitor::TRAVERSE_PARENTS;
  scope().attr("TRAVERSE_ALL_CHILDREN") = NodeVisitor::TRAVERSE_ALL_CHILDREN;
  scope().attr("TRAVERSE_ACTIVE_CHILDREN") = NodeVisitor::TRAVERSE_ACTIVE_CHILDREN;
  
  enum_<NodeVisitor::VisitorType>("VisitorType");
  scope().attr("NODE_VISITOR") = NodeVisitor::NODE_VISITOR;
  scope().attr("UPDATE_VISITOR") = NodeVisitor::UPDATE_VISITOR;
  scope().attr("EVENT_VISITOR") = NodeVisitor::EVENT_VISITOR;
  scope().attr("COLLECT_OCCLUDER_VISITOR") = NodeVisitor::COLLECT_OCCLUDER_VISITOR;
  scope().attr("CULL_VISITOR") = NodeVisitor::CULL_VISITOR;

 }
