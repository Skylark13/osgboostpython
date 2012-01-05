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

#include <osg/CopyOp>

using namespace osg;
#include "defaults.h"

void export_CopyOp()
{

  scope in_CopyOp = class_<CopyOp>("CopyOp")
    .add_property("copyFlags", &CopyOp::getCopyFlags, &CopyOp::setCopyFlags )
    ;

  enum_<CopyOp::Options>("Options");
  scope().attr("SHALLOW_COPY") = CopyOp::SHALLOW_COPY ;
  scope().attr("DEEP_COPY_OBJECTS") = CopyOp::DEEP_COPY_OBJECTS ;
  scope().attr("DEEP_COPY_NODES") = CopyOp::DEEP_COPY_NODES ;
  scope().attr("DEEP_COPY_DRAWABLES") = CopyOp::DEEP_COPY_DRAWABLES ;
  scope().attr("DEEP_COPY_STATESETS") = CopyOp::DEEP_COPY_STATESETS ;
  scope().attr("DEEP_COPY_STATEATTRIBUTES ") = CopyOp::DEEP_COPY_STATEATTRIBUTES  ;
  scope().attr("DEEP_COPY_TEXTURES") = CopyOp::DEEP_COPY_TEXTURES ;
  scope().attr("DEEP_COPY_IMAGES") = CopyOp::DEEP_COPY_IMAGES ;
  scope().attr("DEEP_COPY_ARRAYS ") = CopyOp::DEEP_COPY_ARRAYS  ;
  scope().attr("DEEP_COPY_PRIMITIVES") = CopyOp::DEEP_COPY_PRIMITIVES ;
  scope().attr("DEEP_COPY_SHAPES") = CopyOp::DEEP_COPY_SHAPES ;
  scope().attr("DEEP_COPY_UNIFORMS") = CopyOp::DEEP_COPY_UNIFORMS ;
  scope().attr("DEEP_COPY_CALLBACKS") = CopyOp::DEEP_COPY_CALLBACKS ;
  scope().attr("DEEP_COPY_USERDATA") = CopyOp::DEEP_COPY_USERDATA ;
  scope().attr("DEEP_COPY_ALL") = CopyOp::DEEP_COPY_ALL ;

}

