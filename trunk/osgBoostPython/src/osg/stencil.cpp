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

#include <osg/Stencil>
using namespace osg;

#include "defaults.h"

void (Stencil::*Stencil_setFunction1)(osg::Stencil::Function func, int ref, unsigned int mask) = & Stencil::setFunction;
void (Stencil::*Stencil_setFunction2)(osg::Stencil::Function func) = & Stencil::setFunction;

void export_stencil() {

    scope in_Stencil = class_<Stencil, bases<StateAttribute>, ref_ptr<Stencil>, boost::noncopyable >("Stencil")
        .def(init<>())
        .def("getType", &Stencil::getType)
        .def("setStencilFailOperation", &Stencil::setStencilFailOperation)
        .def("getFunctionRef", &Stencil::getFunctionRef)
        .def("setFunctionMask", &Stencil::setFunctionMask)
        .def("isSameKindAs", &Stencil::isSameKindAs)
        .def("setStencilPassAndDepthPassOperation", &Stencil::setStencilPassAndDepthPassOperation)
        .def("getFunctionMask", &Stencil::getFunctionMask)
        .def("getStencilPassAndDepthPassOperation", &Stencil::getStencilPassAndDepthPassOperation)
        .def("setOperation", &Stencil::setOperation)
        .def("setWriteMask", &Stencil::setWriteMask)
        .def("getStencilFailOperation", &Stencil::getStencilFailOperation)
        .def("setFunctionRef", &Stencil::setFunctionRef)
        .def("getWriteMask", &Stencil::getWriteMask)
        .def("getFunction", &Stencil::getFunction)
        .def("setStencilPassAndDepthFailOperation", &Stencil::setStencilPassAndDepthFailOperation)
        //.def("apply", &Stencil::apply)
        //.def("compare", &Stencil::compare)
        .def("setFunction", Stencil_setFunction2)
        .def("setFunction", Stencil_setFunction1)
        .def("getStencilPassAndDepthFailOperation", &Stencil::getStencilPassAndDepthFailOperation)
        .def("getModeUsage", &Stencil::getModeUsage)

   ;
   
    enum_< Stencil::Function>("Function");
        scope().attr("NEVER") = Stencil::NEVER;
        scope().attr("LESS") = Stencil::LESS;
        scope().attr("EQUAL") = Stencil::EQUAL;
        scope().attr("LEQUAL") = Stencil::LEQUAL;
        scope().attr("GREATER") = Stencil::GREATER;
        scope().attr("NOTEQUAL") = Stencil::NOTEQUAL;
        scope().attr("GEQUAL") = Stencil::GEQUAL;
        scope().attr("ALWAYS") = Stencil::ALWAYS;

    enum_< Stencil::Operation>("Operation");
        scope().attr("KEEP") = Stencil::KEEP;
        scope().attr("ZERO") = Stencil::ZERO;
        scope().attr("REPLACE") = Stencil::REPLACE;
        scope().attr("INCR") = Stencil::INCR;
        scope().attr("DECR") = Stencil::DECR;
        scope().attr("INVERT") = Stencil::INVERT;
        scope().attr("INCR_WRAP") = Stencil::INCR_WRAP;
        scope().attr("DECR_WRAP") = Stencil::DECR_WRAP;
   
}




