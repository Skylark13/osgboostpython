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

#include <osg/Depth>

using namespace osg;

#include "defaults.h"

void export_depth() {

    scope in_Depth = class_<Depth, bases<StateAttribute>, ref_ptr<Depth>, boost::noncopyable>("Depth")
        .def(init<>())
//      .def(init<Depth::Function, double, double, bool>())
        .def("setFunction", &Depth::setFunction)
        .def("setRange", &Depth::setRange)
    ;

    enum_<Depth::Function>("Function");
        scope().attr("NEVER") = Depth::NEVER;
        scope().attr("LESS") = Depth::LESS;
        scope().attr("EQUAL") = Depth::EQUAL;
        scope().attr("LEQUAL") = Depth::LEQUAL;
        scope().attr("GREATER") = Depth::GREATER;
        scope().attr("NOTEQUAL") = Depth::NOTEQUAL;
        scope().attr("GEQUAL") = Depth::GEQUAL;
        scope().attr("ALWAYS") = Depth::ALWAYS;

}

