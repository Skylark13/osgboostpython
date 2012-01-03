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

#include <osg/Node>
#include <osg/NodeVisitor>
#include <osg/NodeCallback>

using namespace osg;

#include "defaults.h"

#include <iostream>

/// Note, need a way to document that the method that needs to be 
/// implemented in Python is call, not operator() or __call__ or
/// anything like that.
struct NodeCallback_wrapper : public NodeCallback
{
    // NodeCallback constructor storing initial self parameter
    NodeCallback_wrapper(PyObject *p)
        : NodeCallback(), self(p)
    {
        std::cout << "NodeCallback_wrapper(p) : ref count is " << this->referenceCount() << std::endl;
    }

    // In case NodeCallback is returned by-value from a wrapped function
    NodeCallback_wrapper(PyObject *p, const NodeCallback& x)
        : NodeCallback(x), self(p)
    {
        std::cout << "NodeCallback_wrapper(p,x) : ref count is " << this->referenceCount() << std::endl;
        std::cout << "x had " << x.referenceCount() << " refs" << std::endl;
    }

    // Override operator() to call back into Python
    void operator()(Node* node, NodeVisitor* nv)
    {
      try {
	call_method<void>(self, "call", ptr(node), ptr(nv));
      } catch (error_already_set) {
	NodeCallback::operator()(node, nv);
      }
    }

    // Supplies the default implementation of operator()
    void default_call(Node* node, NodeVisitor* nv)
    {
      NodeCallback::operator()(node, nv);
    }

//protected:
  ~NodeCallback_wrapper()
     {
        //PyDECREF(self);
       std::cout << "~NodeCallback_wrapper : ref count is " << this->referenceCount() << std::endl;
       //this->unref();
   }


 private:
    PyObject* self;
};

void export_NodeCallback()
{
    class_<NodeCallback, NodeCallback_wrapper, bases<Object>, ref_ptr<NodeCallback> >("NodeCallback")
      .def("call", &NodeCallback::operator(), &NodeCallback_wrapper::default_call)
      .def("traverse", &NodeCallback::traverse)
    ;
}
