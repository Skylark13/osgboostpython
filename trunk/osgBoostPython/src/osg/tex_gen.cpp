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
#include <osg/TexGen> 
#include <osg/State> 
using namespace osg;

#include "defaults.h"

Plane&(TexGen::*get_plane)(TexGen::Coord) = &TexGen::getPlane;

void export_TexGen()
{

  scope in_TexGen = class_<TexGen, bases<StateAttribute>, ref_ptr<TexGen> >("TexGen")
    .add_property("isTextureAttribute", &TexGen::isTextureAttribute )
    //.def("compare", &TexGen::compare )
    .def("getModeUsage", &TexGen::getModeUsage )
    .def("apply", &TexGen::apply )
    .add_property("mode", &TexGen::getMode, &TexGen::setMode )
    .def("setPlane", &TexGen::setPlane)
    .def("getPlane", get_plane, osgBoostPython::default_reference_policy() )
    .def("setPlanesFromMatrix", &TexGen::setPlanesFromMatrix)
    ;

  enum_<TexGen::Mode>("Mode");
  scope().attr("OBJECT_LINEAR") = TexGen::OBJECT_LINEAR;
  scope().attr("EYE_LINEAR") = TexGen::EYE_LINEAR;
  scope().attr("SPHERE_MAP") = TexGen::SPHERE_MAP;
  scope().attr("NORMAL_MAP") = TexGen::NORMAL_MAP;
  scope().attr("REFLECTION_MAP") = TexGen::REFLECTION_MAP;

  enum_<TexGen::Coord>("Coord");
  scope().attr("S") = TexGen::S;
  scope().attr("T") = TexGen::T;
  scope().attr("R") = TexGen::R;
  scope().attr("Q") = TexGen::Q;

}
