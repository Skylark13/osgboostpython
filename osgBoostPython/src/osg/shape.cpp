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

#include <osg/Object>
#include <osg/Shape>

using namespace osg;

#include "defaults.h"

void export_Shape()
{

    // Abstract class
    class_<Shape, bases<Object>, ref_ptr<Shape>, boost::noncopyable >("Shape", no_init)
    ;

    class_<Sphere, bases<Shape>, ref_ptr<Sphere> >("Sphere")
        .def(init<Vec3f, float>())
        .def("set", &Sphere::set)
        .add_property("center", make_function(&Sphere::getCenter, osgBoostPython::default_const_reference_policy()), &Sphere::setCenter)
        .add_property("radius", &Sphere::getRadius, &Sphere::setRadius)
    ;

    class_<Box, bases<Shape>, ref_ptr<Box> >("Box")
      .def(init<Vec3f, float>())
      .def(init<Vec3f, float, float, float>())
      .def("set", &Box::set)
      .add_property("center", make_function(&Box::getCenter, osgBoostPython::default_const_reference_policy()), &Box::setCenter )
      .add_property("halfLengths", make_function(&Box::getHalfLengths, osgBoostPython::default_const_reference_policy()), &Box::setHalfLengths )
      .add_property("rotation", make_function(&Box::getRotation, osgBoostPython::default_const_reference_policy()), &Box::setRotation )
      .def("computeRotationMatrix", &Box::computeRotationMatrix )
      .def("zeroRotation", &Box::zeroRotation )
    ;

    class_<Cone, bases<Shape>, ref_ptr<Cone> >("Cone")
      .def(init<Vec3f, float, float>())
      .def("set", &Cone::set)
      .add_property("center", make_function(&Cone::getCenter, osgBoostPython::default_const_reference_policy()), &Cone::setCenter)
      .add_property("radius", &Cone::getRadius, &Cone::setRadius)
      .add_property("height", &Cone::getHeight, &Cone::setHeight)
      .add_property("rotation", make_function(&Cone::getRotation, osgBoostPython::default_const_reference_policy()), &Cone::setRotation )
      .def("computeRotationMatrix", &Cone::computeRotationMatrix )
      .def("zeroRotation", &Cone::zeroRotation )
      .add_property("baseOffsetFactor", &Cone::getBaseOffsetFactor )
      .add_property("baseOffset", &Cone::getBaseOffset )
    ;

    class_<Cylinder, bases<Shape>, ref_ptr<Cylinder> >("Cylinder")
      .def(init<Vec3f, float, float>())
      .def("set", &Cylinder::set)
      .add_property("center", make_function(&Cylinder::getCenter, osgBoostPython::default_const_reference_policy()), &Cylinder::setCenter)
      .add_property("radius", &Cylinder::getRadius, &Cylinder::setRadius)
      .add_property("height", &Cylinder::getHeight, &Cylinder::setHeight)
      .add_property("rotation", make_function(&Cylinder::getRotation, osgBoostPython::default_const_reference_policy()), &Cylinder::setRotation )
      .def("computeRotationMatrix", &Cylinder::computeRotationMatrix )
      .def("zeroRotation", &Cylinder::zeroRotation )
    ;

    class_<Capsule, bases<Shape>, ref_ptr<Capsule> >("Capsule")
      .def(init<Vec3f, float, float>())
      .def("set", &Capsule::set)
      .add_property("center", make_function(&Capsule::getCenter, osgBoostPython::default_const_reference_policy()), &Capsule::setCenter)
      .add_property("radius", &Capsule::getRadius, &Capsule::setRadius)
      .add_property("height", &Capsule::getHeight, &Capsule::setHeight)
      .add_property("rotation", make_function(&Capsule::getRotation, osgBoostPython::default_const_reference_policy()), &Capsule::setRotation )
      .def("computeRotationMatrix", &Capsule::computeRotationMatrix )
      .def("zeroRotation", &Capsule::zeroRotation )
    ;

}
