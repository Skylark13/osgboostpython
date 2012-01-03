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
#include <osg/Transform>
#include <osg/PositionAttitudeTransform>

using namespace osg;

#include "defaults.h"

void export_PositionAttitudeTransform()
{

    class_<PositionAttitudeTransform, bases<Transform>, ref_ptr<PositionAttitudeTransform> >("PositionAttitudeTransform")
        .def(init<>())
        .add_property("position",   make_function(&PositionAttitudeTransform::getPosition, osgBoostPython::default_const_reference_policy()), 
		      &PositionAttitudeTransform::setPosition  )
        .add_property("attitude",   make_function(&PositionAttitudeTransform::getAttitude,   osgBoostPython::default_const_reference_policy()),  
		      &PositionAttitudeTransform::setAttitude  )
        .add_property("scale",      make_function(&PositionAttitudeTransform::getScale,      osgBoostPython::default_const_reference_policy()), 
		      &PositionAttitudeTransform::setScale     )
        .add_property("pivotPoint", make_function(&PositionAttitudeTransform::getPivotPoint, osgBoostPython::default_const_reference_policy()), 
		      &PositionAttitudeTransform::setPivotPoint)
        //.def("computeLocalToWorldMatrix", &MatrixTransform::computeLocalToWorldMatrix)
        //.def("computeWorldToLocalMatrix", &MatrixTransform::computeWorldToLocalMatrix)
    ;
}
