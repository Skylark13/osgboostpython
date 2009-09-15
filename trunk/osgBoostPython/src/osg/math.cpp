#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Vec2f>
#include <osg/Vec2d>
#include <osg/Vec3f>
#include <osg/Vec3d>
#include <osg/Vec4f>
#include <osg/Vec4d>
#include <osg/Matrixf>
#include <osg/Matrixd>
#include <osg/BoundingSphere>
#include <osg/BoundingBox>

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

template<typename VecType>
struct Vec2Wrapper : public VecWrapper<VecType>
{
    static void       setX(VecType& vec, value_type x) { vec.x() = x;    }
    static value_type getX(VecType& vec)               { return vec.x(); }
    static void       setY(VecType& vec, value_type y) { vec.y() = y;    }
    static value_type getY(VecType& vec)               { return vec.y(); }

    static void set_2_components(VecType& vec, value_type x, value_type y)
    {
        vec.set(x, y);
    }

    static class_t wrap(const std::string& name)
    {
        class_t result = VecWrapper::wrap(name);
        result
            .def(init<value_type, value_type>())
            .add_property("x", getX, setX)
            .add_property("y", getY, setY)
            .def("set", set_2_components)
        ;
        return result;
    }
};

template<typename VecType>
struct Vec3Wrapper : public Vec2Wrapper<VecType>
{
    static void       setZ(VecType& vec, value_type z) { vec.z() = z;    }
    static value_type getZ(VecType& vec)               { return vec.z(); }

    static void set_3_components(VecType& vec, value_type x, value_type y, value_type z)
    {
        vec.set(x, y, z);
    }

    static class_t wrap(const std::string& name)
    {
        class_t result = VecWrapper::wrap(name);
        result
            .def(init<value_type, value_type, value_type>())
            .add_property("x", getX, setX)
            .add_property("y", getY, setY)
            .add_property("z", getZ, setZ)
            .def("set", set_3_components)
            .def("cross", &VecType::operator^)
        ;
        return result;
    }
};

template<typename VecType>
struct Vec4Wrapper : public Vec3Wrapper<VecType>
{
    static void       setW(VecType& vec, value_type w) { vec.w() = w;    }
    static value_type getW(VecType& vec)               { return vec.w(); }

    static void set_4_components(VecType& vec, value_type x, value_type y, value_type z, value_type w)
    {
        vec.set(x, y, z, w);
    }

    static class_t wrap(const std::string& name)
    {
        class_t result = VecWrapper::wrap(name);
        result
            .def(init<value_type, value_type, value_type, value_type>())
            .add_property("x", getX, setX)
            .add_property("y", getY, setY)
            .add_property("z", getZ, setZ)
            .add_property("w", getW, setW)
            .add_property("r", getX, setX)
            .add_property("g", getY, setY)
            .add_property("b", getZ, setZ)
            .add_property("a", getW, setW)
            .def("set", set_4_components)
            .def("asRGBA", &VecType::asRGBA)
            .def("asABGR", &VecType::asABGR)
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


    class_<Matrixf>("Matrixf")
        .def(init<Matrixf>())
        .def("valid", &Matrixf::valid)
        // TODO
    ;

    class_<Matrixd>("Matrixd")
        .def(init<Matrixd>())
        .def("valid", &Matrixd::valid)
        // TODO
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
