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

#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/Uniform>

using namespace osg;

#include "defaults.h"

// Parents
const StateSet::ParentList& (StateSet::*StateSet_getParents1)() const = &StateSet::getParents;
Object* (StateSet::*StateSet_getParent1)( unsigned int ) = &StateSet::getParent;

// Modes
void (StateSet::*StateSet_setMode1)(StateAttribute::GLMode, StateAttribute::GLModeValue) = &StateSet::setMode;
StateAttribute::GLModeValue (StateSet::*StateSet_getMode1)(StateAttribute::GLMode) const = &StateSet::getMode;
void (StateSet::*StateSet_removeMode1)(StateAttribute::GLMode) = &StateSet::removeMode;

// Attributes
void (StateSet::*StateSet_setAttribute1)(StateAttribute*, StateAttribute::OverrideValue) = &StateSet::setAttribute;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_setAttribute_overloads, setAttribute, 1, 2)

// getAttribute and removeAttribute have a default value on the second 
// argument, the BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS allows us to use them.
StateAttribute* (StateSet::*StateSet_getAttribute1)(StateAttribute::Type, unsigned int) = &StateSet::getAttribute;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_getAttribute_overloads, getAttribute, 1, 2)
void (StateSet::*StateSet_removeAttribute1)(StateAttribute::Type, unsigned int) = &StateSet::removeAttribute;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_removeAttribute_overloads, removeAttribute, 1, 2)
void (StateSet::*StateSet_removeAttribute2)(StateAttribute*) = &StateSet::removeAttribute;

// TextureAttributes
void (StateSet::*StateSet_setTextureAttribute1)(unsigned int, StateAttribute*, StateAttribute::OverrideValue) = &StateSet::setTextureAttribute;
StateAttribute* (StateSet::*StateSet_getTextureAttribute1)(unsigned int, StateAttribute::Type) = &StateSet::getTextureAttribute;
void (StateSet::*StateSet_removeTextureAttribute1)(unsigned int, StateAttribute::Type) = &StateSet::removeTextureAttribute;
void (StateSet::*StateSet_removeTextureAttribute2)(unsigned int, StateAttribute*) = &StateSet::removeTextureAttribute;

// Uniforms
Uniform* (StateSet::*StateSet_getUniform1)(const std::string&) = &StateSet::getUniform;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_getOrCreateUniform_overloads, getOrCreateUniform, 2, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_addUniform_overloads, addUniform, 1, 2)
void (StateSet::*StateSet_removeUniform1)(const std::string&) = &StateSet::removeUniform;
void (StateSet::*StateSet_removeUniform2)(Uniform*) = &StateSet::removeUniform;

// RenderBin
void (StateSet::*StateSet_setRenderBinDetails1)(int, const std::string&, StateSet::RenderBinMode) = &StateSet::setRenderBinDetails;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_setRenderBinDetails_overloads, setRenderBinDetails, 2, 3)

void export_StateSet()
{
  
  scope in_StateSet = class_<StateSet, bases<Object>, ref_ptr<StateSet> >("StateSet")
    .def("getNumParents", &StateSet::getNumParents)
    .def("getParents", StateSet_getParents1, osgBoostPython::default_value_policy())
    .def("getParent", StateSet_getParent1, osgBoostPython::default_pointer_policy())
    .def("setMode", StateSet_setMode1)
    .def("removeMode", StateSet_removeMode1)
    .def("getMode", StateSet_getMode1)
    .def("setAttribute", StateSet_setAttribute1, StateSet_setAttribute_overloads())
    .def("setAttributeAndModes", &StateSet::setAttributeAndModes)
    .def("removeAttribute", StateSet_removeAttribute1, StateSet_removeAttribute_overloads())
    .def("removeAttribute", StateSet_removeAttribute2)
    .def("getAttribute", StateSet_getAttribute1, osgBoostPython::default_pointer_policy(), StateSet_getAttribute_overloads())
    .def("setTextureMode", &StateSet::setTextureMode)
    .def("removeTextureMode", &StateSet::removeTextureMode)
    .def("getTextureMode", &StateSet::getTextureMode)
    .def("setTextureAttribute", StateSet_setTextureAttribute1)
    .def("setTextureAttributeAndModes", &StateSet::setTextureAttributeAndModes)
    .def("removeTextureAttribute", StateSet_removeTextureAttribute1)
    .def("removeTextureAttribute", StateSet_removeTextureAttribute2)
    .def("getTextureAttribute", StateSet_getTextureAttribute1, osgBoostPython::default_pointer_policy())
    .def("setRenderingHint", &StateSet::setRenderingHint)
    .def("getRenderingHint", &StateSet::getRenderingHint)
    .def("addUniform", &StateSet::addUniform, StateSet_addUniform_overloads())
    .def("removeUniform", StateSet_removeUniform1)
    .def("removeUniform", StateSet_removeUniform2)
    .def("getUniform", StateSet_getUniform1, osgBoostPython::default_pointer_policy())
    .def("getOrCreateUniform", &StateSet::getOrCreateUniform, osgBoostPython::default_pointer_policy(), StateSet_getOrCreateUniform_overloads())
    .def("setRenderBinDetails", StateSet_setRenderBinDetails1, StateSet_setRenderBinDetails_overloads())
    ;
  
  enum_<StateSet::RenderingHint>("RenderingHint");
  scope().attr("DEFAULT_BIN") = StateSet::DEFAULT_BIN;
  scope().attr("OPAQUE_BIN") = StateSet::OPAQUE_BIN;
  scope().attr("TRANSPARENT_BIN") = StateSet::TRANSPARENT_BIN;
  
  enum_<StateSet::RenderBinMode>("RenderBinMode");
  scope().attr("INHERIT_RENDERBIN_DETAILS") = StateSet::INHERIT_RENDERBIN_DETAILS;
  scope().attr("USE_RENDERBIN_DETAILS") = StateSet::USE_RENDERBIN_DETAILS;
  scope().attr("OVERRIDE_RENDERBIN_DETAILS") = StateSet::OVERRIDE_RENDERBIN_DETAILS;
  
}
