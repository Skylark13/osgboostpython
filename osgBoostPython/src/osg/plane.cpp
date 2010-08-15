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
//#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#include <osg/Plane>
using namespace osg;

#include "defaults.h"

void (Plane::*Plane_set1)(osg::Plane const & pl) = & Plane::set;
void (Plane::*Plane_set2)(double a, double b, double c, double d) = & Plane::set;
void (Plane::*Plane_set3)(osg::Vec4f const & vec) = & Plane::set;
void (Plane::*Plane_set4)(osg::Vec4d const & vec) = & Plane::set;
void (Plane::*Plane_set5)(osg::Vec3d const & norm, double d) = & Plane::set;
void (Plane::*Plane_set6)(osg::Vec3d const & v1, osg::Vec3d const & v2, osg::Vec3d const & v3) = & Plane::set;
void (Plane::*Plane_set7)(osg::Vec3d const & norm, osg::Vec3d const & point) = & Plane::set;
// double * (Plane::*Plane_ptr8)() = & Plane::ptr;
// double const * (Plane::*Plane_ptr9)() = & Plane::ptr;
// double & (Plane::*Plane_operator[]10)(unsigned int i) = & Plane::operator[];
// double (Plane::*Plane_operator[]11)(unsigned int i) = & Plane::operator[];
float (Plane::*Plane_distance12 )(osg::Vec3f const & ) const = &Plane::distance;
double (Plane::*Plane_distance13)(osg::Vec3d const & ) const = &Plane::distance;
float (Plane::*Plane_dotProductNormal14)(osg::Vec3f const & v) const = & Plane::dotProductNormal;
double (Plane::*Plane_dotProductNormal15)(osg::Vec3d const & v) const = & Plane::dotProductNormal;
// int (Plane::*Plane_intersect16)(std::vector<osg::Vec3f, std::allocator<osg::Vec3f> > const & vertices) = & Plane::intersect;
// int (Plane::*Plane_intersect17)(std::vector<osg::Vec3d, std::allocator<osg::Vec3d> > const & vertices) = & Plane::intersect;
int (Plane::*Plane_intersect18)(osg::BoundingSphere const & bs) const = & Plane::intersect;
int (Plane::*Plane_intersect19)(osg::BoundingBox const & bb) const = & Plane::intersect;

void export_plane() {

    class_<Plane, boost::noncopyable >("Plane")
        .def(init<>())
        //	    .def(init< osg::Plane const & >(( arg("pl") )) )
        .def( init< double, double, double, double >(( arg("a"), arg("b"), arg("c"), arg("d") )) )
        .def( init< osg::Vec4f const & >(( arg("vec") )) )
        //        implicitly_convertible< osg::Vec4f const &, osg::Plane >()
        .def( init< osg::Vec4d const & >(( arg("vec") )) )
        //        implicitly_convertible< osg::Vec4d const &, osg::Plane >()
        .def( init< osg::Vec3d const &, double >(( arg("norm"), arg("d") )) )
        .def( init< osg::Vec3d const &, osg::Vec3d const &, osg::Vec3d const & >(( arg("v1"), arg("v2"), arg("v3") )) )
        .def( init< osg::Vec3d const &, osg::Vec3d const & >(( arg("norm"), arg("point") )) )
        
        .def("set", Plane_set7)
        .def("set", Plane_set6)
        .def("set", Plane_set5)
        .def("set", Plane_set4)
        .def("set", Plane_set3)
        .def("set", Plane_set2)
        .def("set", Plane_set1)
        .def("asVec4", &Plane::asVec4)
        .def("isNaN", &Plane::isNaN)
        .def("transformProvidingInverse", &Plane::transformProvidingInverse)
        .def("getNormal", &Plane::getNormal)
        .def("transform", &Plane::transform)
        //.def("intersect", Plane_intersect16)
        //.def("intersect", Plane_intersect17)
        .def("intersect", Plane_intersect18)
        .def("intersect", Plane_intersect19)
        //.def("ptr", Plane_ptr9)
        //.def("ptr", Plane_ptr8)
        .def("makeUnitLength", &Plane::makeUnitLength)
        .def("distance", Plane_distance13)
        .def("distance", Plane_distance12)
        .def("valid", &Plane::valid)
        .def("calculateUpperLowerBBCorners", &Plane::calculateUpperLowerBBCorners)
        .def("dotProductNormal", Plane_dotProductNormal15)
        .def("dotProductNormal", Plane_dotProductNormal14)
        .def("flip", &Plane::flip)
    ; 
}
