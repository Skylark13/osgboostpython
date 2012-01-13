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
#include <osg/Viewport>
using namespace osg;

#include "defaults.h"

void set_x( Viewport& vp, double x){ vp.x() = x; };
double get_x( Viewport& vp, double x){ return vp.x(); };

void export_Viewport(){
  class_<Viewport, bases<StateAttribute>, ref_ptr<Viewport> >
    ("Viewport", init<double, double, double, double> () )
    .def("setViewport", &Viewport::setViewport)
    .add_property("x", get_x, set_x)
    ;
}
