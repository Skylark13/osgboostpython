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

using namespace osg;

#include "defaults.h"

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(Group_removeChild2_overloads, removeChild, 1, 2)

void export_Group()
{
  FUNC_PTR1(Node*, Group, Group_getChild1, unsigned int, Group::getChild);
  FUNC_PTR1(bool, Group, Group_removeChild1, osg::Node*, Group::removeChild);
  FUNC_PTR2(bool, Group, Group_removeChild2, unsigned int, unsigned int, Group::removeChild);
    
  class_<Group, bases<Node>, ref_ptr<Group> >("Group")
    .def("getNumChildren", &Group::getNumChildren)
    .def("getChild", Group_getChild1, osgBoostPython::default_pointer_policy())
    .def("addChild", &Group::addChild)
    .def("insertChild", &Group::insertChild)
    .def("removeChild", Group_removeChild1)
    .def("removeChild", Group_removeChild2, Group_removeChild2_overloads())
    .def("removeChildren", &Group::removeChildren)
    .def("replaceChild", &Group::replaceChild)
    .def("setChild", &Group::setChild)
    .def("containsNode", &Group::containsNode)
    .def("getChildIndex", &Group::getChildIndex)
    .def("traverse", &Group::traverse )
    ;
}
