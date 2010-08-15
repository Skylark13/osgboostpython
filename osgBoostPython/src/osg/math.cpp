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

#include <osg/Vec2f>
#include <osg/Vec2d>
#include <osg/Vec3f>
#include <osg/Vec3d>
#include <osg/Vec4f>
#include <osg/Vec4d>
#include <osg/BoundingSphere>
#include <osg/BoundingBox>
#include <osg/Quat>

using namespace osg;

#include "defaults.h"
#include "ContainerUtils.h"


void (BoundingBox::*BoundingBox_set1)( BoundingBox::value_type, BoundingBox::value_type, BoundingBox::value_type, 
                                       BoundingBox::value_type, BoundingBox::value_type, BoundingBox::value_type ) = &BoundingBox::set;
void (BoundingBox::*BoundingBox_set2)( const BoundingBox::vec_type&, const BoundingBox::vec_type& ) = &BoundingBox::set;
BoundingBox::value_type& (BoundingBox::*BoundingBox_xMin1)( ) = &BoundingBox::xMin;
BoundingBox::value_type& (BoundingBox::*BoundingBox_yMin1)( ) = &BoundingBox::yMin;
BoundingBox::value_type& (BoundingBox::*BoundingBox_zMin1)( ) = &BoundingBox::zMin;
BoundingBox::value_type& (BoundingBox::*BoundingBox_xMax1)( ) = &BoundingBox::xMax;
BoundingBox::value_type& (BoundingBox::*BoundingBox_yMax1)( ) = &BoundingBox::yMax;
BoundingBox::value_type& (BoundingBox::*BoundingBox_zMax1)( ) = &BoundingBox::zMax;

template <typename VecType>
std::string Vector_str(VecType * self)
{
    std::ostringstream ost;
    ost << "[";
    for (unsigned int i=0 ; i< VecType::num_components ; i++) {
        ost << (*self)[i];
        if (i != VecType::num_components-1) ost << ",";
    }
    ost << "]";
    return ost.str();
}

template<typename VecType>
struct VecWrapper
{
    typedef typename VecType::value_type value_type;
    typedef boost::python::class_<VecType> class_t;

    static class_t wrap(const std::string& name)
    {
        value_type (VecType::*dot) (const VecType& rhs) const = &VecType::operator*;

        class_t result(name.c_str());
        result
            .def_readonly("_v", &VecType::_v)                                             // Should be readwrite...

            // default ctor
            .def(init<VecType>())

            .def("dot", dot)
            .def("length", &VecType::length)
            .def("length2", &VecType::length2)
            .def("normalize", &VecType::normalize)
            .def("valid", &VecType::valid)
            .def("isNaN", &VecType::isNaN)

            // Operators
            .def(-self)                // __neg__
            .def(self + self)          // __add__
            .def(self - self)          // __sub__
            .def(self * value_type())  // __mul__ (heterogenous)
            .def(self / value_type())  // __div__ (heterogenous)
            .def(self == self)         // __eq__
            .def(self != self)         // __ne__
            .def(self < self)          // ?

            // TODO:
            //.def("__neg__", neg_a)          // done
            //.def("__add__", add_a_a)        // done
            //.def("__sub__", sub_a_a)        // done
            //.def("__mul__", mul_a_a)        // doesn't make sense
            //.def("__div__", div_a_a)        // doesn't make sense
            //.def("__truediv__", div_a_a)    // ?
            //.def("__add__", add_a_s)        // doesn't make sense
            //.def("__radd__", add_a_s)       // ?
            //.def("__sub__", sub_a_s)        // doesn't make sense
            //.def("__rsub__", rsub_a_s)      // ?
            //.def("__mul__", mul_a_s)        // done for VecType * value_type
            //.def("__rmul__", mul_a_s)       // ?
            //.def("__div__", div_a_s)        // done for VecType / value_type
            //.def("__truediv__", div_a_s)    // ?
            //.def("__rdiv__", rdiv_a_s)      // ?
            //.def("__rtruediv__", rdiv_a_s)  // ?
            //.def("__iadd__", iadd_a_a)      // ?
            //.def("__isub__", isub_a_a)      // ?
            //.def("__imul__", imul_a_a)      // ?
            //.def("__idiv__", idiv_a_a)      // ?
            //.def("__itruediv__", idiv_a_a)  // ?
            //.def("__iadd__", iadd_a_s)      // ?
            //.def("__isub__", isub_a_s)      // ?
            //.def("__imul__", imul_a_s)      // ?
            //.def("__idiv__", idiv_a_s)      // ?
            //.def("__itruediv__", idiv_a_s)  // ?
            //.def("__eq__", eq_a_a)          // done
            //.def("__ne__", ne_a_a)          // done
            //.def("__eq__", eq_a_s)          // doesn't make sense
            //.def("__ne__", ne_a_s)          // doesn't make sense

        ;

        osgBoostPython::array_utils::to_tuple_mapping< value_type[VecType::num_components], VecType::num_components >();

        return result;
    }
};

#define VEC_PROPERTY_HELPER(x) static value_type get##x(VecType& vec)                 { return vec.x(); } \
                               static void       set##x(VecType& vec, value_type val) { vec.x() = val;  }

template<typename VecType>
struct Vec2Wrapper : public VecWrapper<VecType>
{
    typedef typename VecType::value_type value_type;
    typedef boost::python::class_<VecType> class_t;

    VEC_PROPERTY_HELPER(x)
    VEC_PROPERTY_HELPER(y)

    static void set_2_components(VecType& vec, value_type x, value_type y)
    {
        vec.set(x, y);
    }
    
    static class_t wrap(const std::string& name)
    {
        class_t result = VecWrapper<VecType>::wrap(name);
        result
            .def(init<value_type, value_type>())
            .add_property("x", getx, setx)
            .add_property("y", gety, sety)
            .def("set", set_2_components)
            .def("__getitem__", (value_type& (VecType::*)(int)) &VecType::operator[], return_value_policy<copy_non_const_reference>())
            .def("__str__", &Vector_str<VecType>)
        ;
        return result;
    }
};

template<typename VecType>
struct Vec3Wrapper : public Vec2Wrapper<VecType>
{
    typedef typename VecType::value_type value_type; 
    typedef boost::python::class_<VecType> class_t;

    VEC_PROPERTY_HELPER(x)
    VEC_PROPERTY_HELPER(y)
    VEC_PROPERTY_HELPER(z)

    static void set_3_components(VecType& vec, value_type x, value_type y, value_type z)
    {
        vec.set(x, y, z);
    }

    static class_t wrap(const std::string& name)
    {
        class_t result = VecWrapper<VecType>::wrap(name);
        result
            .def(init<value_type, value_type, value_type>())
            .add_property("x", getx, setx)
            .add_property("y", gety, sety)
            .add_property("z", getz, setz)
            .def("set", set_3_components)
            .def("__getitem__", (value_type& (VecType::*)(int)) &VecType::operator[], return_value_policy<copy_non_const_reference>())
            .def("cross", &VecType::operator^)
            .def("__str__", &Vector_str<VecType>)
        ;
        return result;
    }
};

template<typename VecType>
struct Vec4Wrapper : public Vec3Wrapper<VecType>
{
    typedef typename VecType::value_type value_type;
    typedef boost::python::class_<VecType> class_t;

    VEC_PROPERTY_HELPER(x)
    VEC_PROPERTY_HELPER(y)
    VEC_PROPERTY_HELPER(z)
    VEC_PROPERTY_HELPER(w)

    static void set_4_components(VecType& vec, value_type x, value_type y, value_type z, value_type w)
    {
        vec.set(x, y, z, w);
    }

    static class_t wrap(const std::string& name)
    {
        class_t result = VecWrapper<VecType>::wrap(name);
        result
            .def(init<value_type, value_type, value_type, value_type>())
            .add_property("x", getx, setx)
            .add_property("y", gety, sety)
            .add_property("z", getz, setz)
            .add_property("w", getw, setw)
            .add_property("r", getx, setx)
            .add_property("g", gety, sety)
            .add_property("b", getz, setz)
            .add_property("a", getw, setw)
            .def("set", set_4_components)
            .def("__getitem__", (value_type& (VecType::*)(unsigned int)) &VecType::operator[], return_value_policy<copy_non_const_reference>())
            .def("asRGBA", &VecType::asRGBA)
            .def("asABGR", &VecType::asABGR)
            .def("__str__", &Vector_str<VecType>)
        ;
        return result;
    }
};

void export_math()
{
    // Vec2f
    VecWrapper<Vec2f>::class_t v2fwrapper = Vec2Wrapper<Vec2f>::wrap("Vec2f");

    // Vec2d
    VecWrapper<Vec2d>::class_t v2dwrapper = Vec2Wrapper<Vec2d>::wrap("Vec2d");
    v2dwrapper
        .def(init<Vec2f>());

    // Vec3f
    VecWrapper<Vec3f>::class_t v3fwrapper = Vec3Wrapper<Vec3f>::wrap("Vec3f");
    v3fwrapper
        .def(init<Vec2f, Vec3f::value_type>());

    // Vec3d
    VecWrapper<Vec3d>::class_t v3dwrapper = Vec3Wrapper<Vec3d>::wrap("Vec3d");
    v3dwrapper
        .def(init<Vec3f>())
        .def(init<Vec2d, Vec3d::value_type>());

    // Vec4f
    VecWrapper<Vec4f>::class_t v4fwrapper = Vec4Wrapper<Vec4f>::wrap("Vec4f");
    v4fwrapper
        .def(init<Vec3f, Vec4f::value_type>());

    // Vec4d
    VecWrapper<Vec4d>::class_t v4dwrapper = Vec4Wrapper<Vec4d>::wrap("Vec4d");
    v4dwrapper
        .def(init<Vec4f>())
        .def(init<Vec3d, Vec4d::value_type>());

    class_<Quat>("Quat")
        .def(init<>())
        // TODO: other constructors
        .def("makeRotate",
            (void (Quat::*)(const osg::Vec3&, const osg::Vec3&))
            &Quat::makeRotate)
        .def("makeRotate",
            (void (Quat::*)(double, const osg::Vec3&))
            &Quat::makeRotate)
        .def("makeRotate",
            (void (Quat::*)(double, const osg::Vec3&, double, const osg::Vec3&, double, const osg::Vec3&))
            &Quat::makeRotate)
        .def("makeRotate",
            (void (Quat::*)(double, double, double, double))
            &Quat::makeRotate)
        // TODO: expand methods
    ;


    class_<BoundingSphere>("BoundingSphere")
        .def_readwrite("_center", &BoundingSphere::_center)
        .def_readwrite("_radius", &BoundingSphere::_radius)

        // default ctor
        .def(init<BoundingSphere>())
        // ctor that takes center and radius
        .def(init<BoundingSphere::vec_type, BoundingSphere::value_type>())
        // ctor that takes a bbox
        .def(init<BoundingBox>())

        .def("init", &BoundingSphere::init)
        .def("valid", &BoundingSphere::valid)
        .def("set", &BoundingSphere::set)
        // TODO: expand methods
        // TODO: contains and intersects methods
    ;

    class_<BoundingBox>("BoundingBox")
        .def_readwrite("_min", &BoundingBox::_min)
        .def_readwrite("_max", &BoundingBox::_max)

        // default ctor
        .def(init<BoundingBox>())
        // ctor that takes xmin, ymin, zmin, xmax, ymax, zmax.
        .def(init<BoundingBox::value_type, BoundingBox::value_type, BoundingBox::value_type,
                  BoundingBox::value_type, BoundingBox::value_type, BoundingBox::value_type>())
        // ctor that takes min and max
        .def(init<BoundingBox::vec_type, BoundingBox::vec_type>())

        .def("init", &BoundingBox::init)
        .def("valid", &BoundingBox::valid)
        .def("set", BoundingBox_set1)   // with 6 floats
        .def("set", BoundingBox_set2)   // with 2 vectors
        .def("xMin", BoundingBox_xMin1, osgBoostPython::default_reference_policy())        // Will this work when setting?
        .def("yMin", BoundingBox_yMin1, osgBoostPython::default_reference_policy())
        .def("zMin", BoundingBox_zMin1, osgBoostPython::default_reference_policy())
        .def("xMax", BoundingBox_xMax1, osgBoostPython::default_reference_policy())
        .def("yMax", BoundingBox_yMax1, osgBoostPython::default_reference_policy())
        .def("zMax", BoundingBox_zMax1, osgBoostPython::default_reference_policy())
        .def("center", &BoundingBox::center)
        .def("radius", &BoundingBox::radius)
        .def("radius2", &BoundingBox::radius2)
        .def("corner", &BoundingBox::corner)
        // TODO: expand methods
        // TODO: contains and intersects methods
    ;
}
