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
#include <osg/State> 
#include <osg/Light> 
using namespace osg;

#include "defaults.h"

void export_Light()
{

  scope in_Light = class_<Light, bases<StateAttribute>, ref_ptr<Light> >("Light")
    .def( init<unsigned int>() )
    //.def("compare", &Light::compare )
    .add_property("member", &Light::getMember )
    .def("getModeUsage", &Light::getModeUsage )
    .add_property("lightNum", &Light::getLightNum, &Light::setLightNum )		  
    .add_property("ambient", make_function( &Light::getAmbient, osgBoostPython::default_const_reference_policy() ) ,
		  &Light::setAmbient )
    .add_property("diffuse", make_function( &Light::getDiffuse, osgBoostPython::default_const_reference_policy() ) ,
		  &Light::setDiffuse )
    .add_property("specular", make_function( &Light::getSpecular, osgBoostPython::default_const_reference_policy() ) ,
		  &Light::setSpecular )
    .add_property("position", make_function( &Light::getPosition, osgBoostPython::default_const_reference_policy() ) ,
		  &Light::setPosition )
    .add_property("direction", make_function( &Light::getDirection, osgBoostPython::default_const_reference_policy() ) ,
		  &Light::setDirection )
    .add_property("constantAttenuation", &Light::getConstantAttenuation, &Light::setConstantAttenuation )		  
    .add_property("linearAttenuation", &Light::getLinearAttenuation, &Light::setLinearAttenuation )		  
    .add_property("quadraticAttenuation", &Light::getQuadraticAttenuation, &Light::setQuadraticAttenuation )		  
    .add_property("spotExponent", &Light::getSpotExponent, &Light::setSpotExponent )		  
    .add_property("spotCutoff", &Light::getSpotCutoff, &Light::setSpotCutoff )		  
    .def("captureLightState", &Light::captureLightState )
    .def("apply", &Light::apply )
   ;

}
