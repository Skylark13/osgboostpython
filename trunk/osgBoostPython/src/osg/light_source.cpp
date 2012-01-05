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
#include <osg/LightSource> 
using namespace osg;

#include "defaults.h"

Light*(LightSource::*get_light)() = &LightSource::getLight;

void export_LightSource()
{

  scope in_LightSource = class_<LightSource, bases<Group>, ref_ptr<LightSource> >("LightSource")
    .add_property("referenceFrame", &LightSource::getReferenceFrame, &LightSource::setReferenceFrame )		  
    .add_property("light", make_function( get_light, osgBoostPython::default_pointer_policy() ) ,
		  &LightSource::setLight )
    .def("setStateSetModes", &LightSource::setStateSetModes )
    .def("setLocalStateSetModes", &LightSource::setLocalStateSetModes )
    .def("setThreadSafeRefUnref", &LightSource::setThreadSafeRefUnref )
    .def("computeBound", &LightSource::computeBound )
    ;

  enum_<LightSource::ReferenceFrame>("ReferenceFrame");
  scope().attr("RELATIVE_RF") = LightSource::RELATIVE_RF ;
  scope().attr("ABSOLUTE_RF") = LightSource::ABSOLUTE_RF ;

  
}
