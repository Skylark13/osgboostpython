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

#include <osg/Object>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/PrimitiveSet>

#include <osg/Shape>

using namespace osg;

#include "defaults.h"

Array* (Geometry::*Geometry_getVertexArray1)() = &Geometry::getVertexArray;
Array* (Geometry::*Geometry_getNormalArray1)() = &Geometry::getNormalArray;
Array* (Geometry::*Geometry_getColorArray1)() = &Geometry::getColorArray;
Array* (Geometry::*Geometry_getSecondaryColorArray1)() = &Geometry::getSecondaryColorArray;
Array* (Geometry::*Geometry_getTexCoordArray1)(unsigned int unit) = &Geometry::getTexCoordArray;
Array* (Geometry::*Geometry_getVertexAttribArray1)(unsigned int index) = &Geometry::getVertexAttribArray;

PrimitiveSet* (Geometry::*Geometry_getPrimitiveSet1)(unsigned int pos) = &Geometry::getPrimitiveSet;

void export_Geometry()
{
  scope in_Geometry = class_<Geometry, bases<Drawable>, ref_ptr<Geometry> >("Geometry")
    // Could have gone for properties, but it doesn't work well for those that need arguments like texcoords...
    .def("setVertexArray", &Geometry::setVertexArray)
    .def("getVertexArray", Geometry_getVertexArray1, osgBoostPython::default_pointer_policy())
    .add_property("normalBinding", &Geometry::getNormalBinding, &Geometry::setNormalBinding)
    .def("setNormalArray", &Geometry::setNormalArray)
    .def("getNormalArray", Geometry_getNormalArray1, osgBoostPython::default_pointer_policy())
    .add_property("colorBinding", &Geometry::getColorBinding, &Geometry::setColorBinding)
    .def("setColorArray", &Geometry::setColorArray)
    .def("getColorArray", Geometry_getColorArray1, osgBoostPython::default_pointer_policy())
            .add_property("secondaryColorBinding", &Geometry::getSecondaryColorBinding, &Geometry::setSecondaryColorBinding)
    .def("setSecondaryColorArray", &Geometry::setSecondaryColorArray)
    .def("getSecondaryColorArray", Geometry_getSecondaryColorArray1, osgBoostPython::default_pointer_policy())
    .def("setTexCoordArray", &Geometry::setTexCoordArray)
    .def("getTexCoordArray", Geometry_getTexCoordArray1, osgBoostPython::default_pointer_policy())
    .def("setVertexAttribArray", &Geometry::setVertexAttribArray)
    .def("getVertexAttribArray", Geometry_getVertexAttribArray1, osgBoostPython::default_pointer_policy())
    .def("addPrimitiveSet", &Geometry::addPrimitiveSet)
    .def("getNumPrimitiveSets", &Geometry::getNumPrimitiveSets)
    .def("getPrimitiveSet", Geometry_getPrimitiveSet1, osgBoostPython::default_pointer_policy())
    .def("removePrimitiveSet", &Geometry::removePrimitiveSet)
    ;

  enum_<Geometry::AttributeBinding>("AttributeBinding");
  scope().attr("BIND_OFF") =               Geometry::BIND_OFF;
  scope().attr("BIND_OVERALL") =           Geometry::BIND_OVERALL;
  scope().attr("BIND_PER_PRIMITIVE_SET") = Geometry::BIND_PER_PRIMITIVE_SET;
  scope().attr("BIND_PER_PRIMITIVE") =     Geometry::BIND_PER_PRIMITIVE;
  scope().attr("BIND_PER_VERTEX") =        Geometry::BIND_PER_VERTEX;
  
}
