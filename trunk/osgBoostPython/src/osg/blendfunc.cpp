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

#include <osg/Export>
#include <osg/StateAttribute>
#include <osg/BlendFunc>

using namespace osg;

#include "defaults.h"

void (BlendFunc::*BlendFunc_setFunction1)(GLenum source, GLenum destination) = & BlendFunc::setFunction;
void (BlendFunc::*BlendFunc_setFunction2)(GLenum source_rgb, GLenum destination_rgb, GLenum source_alpha, GLenum destination_alpha) = & BlendFunc::setFunction;

void export_blendfunc() {

    scope in_BlendFunc = class_<BlendFunc, bases<StateAttribute>, ref_ptr<BlendFunc>, boost::noncopyable >("BlendFunc")
        .def(init<>())
        .def("setDestinationAlpha", &BlendFunc::setDestinationAlpha)
        //.def("compare", &BlendFunc::compare)
        .def("setFunction", BlendFunc_setFunction1)
        .def("setFunction", BlendFunc_setFunction2)
        .def("setDestinationRGB", &BlendFunc::setDestinationRGB)
        .def("setSourceRGB", &BlendFunc::setSourceRGB)
        .def("setSource", &BlendFunc::setSource)
        .def("setDestination", &BlendFunc::setDestination)
        .def("getSource", &BlendFunc::getSource)
        //.def("apply", &BlendFunc::apply)
        .def("getDestination", &BlendFunc::getDestination)
        //.def("setExtensions", &BlendFunc::setExtensions)
        .def("getSourceAlpha", &BlendFunc::getSourceAlpha)
        //.def("glBlendFuncSeparate", &Extensions::glBlendFuncSeparate)
        //.def("getExtensions", &BlendFunc::getExtensions)
        .def("setSourceAlpha", &BlendFunc::setSourceAlpha)
        //.def("setBlendFuncSeparateSupported", &Extensions::setBlendFuncSeparateSupported)
        //.def("isSameKindAs", &BlendFunc::isSameKindAs)
        //.def("getType", &BlendFunc::getType)
        .def("getSourceRGB", &BlendFunc::getSourceRGB)
        .def("getDestinationAlpha", &BlendFunc::getDestinationAlpha)
        //.def("setupGLExtensions", &Extensions::setupGLExtensions)
        //.def("clone", &BlendFunc::clone)
        //.def("libraryName", &BlendFunc::libraryName)
        //.def("lowestCommonDenominator", &Extensions::lowestCommonDenominator)
        //.def("cloneType", &BlendFunc::cloneType)
        //.def("getModeUsage", &BlendFunc::getModeUsage)
        //.def("isBlendFuncSeparateSupported", &Extensions::isBlendFuncSeparateSupported)
        //.def("className", &BlendFunc::className)
        .def("getDestinationRGB", &BlendFunc::getDestinationRGB)
    ;       

    enum_<BlendFunc::BlendFuncMode>("BlendFuncMode"); //enum must be mentioned, otherwise no to-python converter available
        scope().attr("DST_ALPHA") = BlendFunc::DST_ALPHA;
        scope().attr("DST_COLOR") = BlendFunc::DST_COLOR;
        scope().attr("ONE") = BlendFunc::ONE;
        scope().attr("ONE_MINUS_DST_ALPHA") = BlendFunc::ONE_MINUS_DST_ALPHA;
        scope().attr("ONE_MINUS_DST_COLOR") = BlendFunc::ONE_MINUS_DST_COLOR;
        scope().attr("ONE_MINUS_SRC_ALPHA") = BlendFunc::ONE_MINUS_SRC_ALPHA;
        scope().attr("ONE_MINUS_SRC_COLOR") = BlendFunc::ONE_MINUS_SRC_COLOR;
        scope().attr("SRC_ALPHA") = BlendFunc::SRC_ALPHA;
        scope().attr("SRC_ALPHA_SATURATE") = BlendFunc::SRC_ALPHA_SATURATE;
        scope().attr("SRC_COLOR") = BlendFunc::SRC_COLOR;
        scope().attr("CONSTANT_COLOR") = BlendFunc::CONSTANT_COLOR;
        scope().attr("ONE_MINUS_CONSTANT_COLOR") = BlendFunc::ONE_MINUS_CONSTANT_COLOR;
        scope().attr("CONSTANT_ALPHA") = BlendFunc::CONSTANT_ALPHA;
        scope().attr("ONE_MINUS_CONSTANT_ALPHA") = BlendFunc::ONE_MINUS_CONSTANT_ALPHA;
        scope().attr("ZERO") = BlendFunc::ZERO;
        
}