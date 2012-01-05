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
#include <osg/TexGenNode> 
using namespace osg;

#include "defaults.h"

TexGen*(TexGenNode::*get_tex_gen)() = &TexGenNode::getTexGen;

void export_TexGenNode()
{

  scope in_TexGenNode = class_<TexGenNode, bases<Group>, ref_ptr<TexGenNode> >("TexGenNode")
    .def( init<TexGen*>() )
    .add_property("referenceFrame", &TexGenNode::getReferenceFrame, &TexGenNode::setReferenceFrame )		  
    .add_property("textureUnit", &TexGenNode::getTextureUnit, &TexGenNode::setTextureUnit )		  
    .add_property("texGen", make_function( get_tex_gen, osgBoostPython::default_pointer_policy() ),
		  &TexGenNode::setTexGen )		  
    .def("setThreadSafeRefUnref", &TexGenNode::setThreadSafeRefUnref )
    ;

  enum_<TexGenNode::ReferenceFrame>("ReferenceFrame");
  scope().attr("RELATIVE_RF") = TexGenNode::RELATIVE_RF ;
  scope().attr("ABSOLUTE_RF") = TexGenNode::ABSOLUTE_RF ;

}
