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

#include "ContainerUtils.h"

using namespace osg;


Vec2f::value_type& (Vec2f::*Vec2f_x1)( ) = &Vec2f::x;
Vec2f::value_type& (Vec2f::*Vec2f_y1)( ) = &Vec2f::y;
void (Vec2f::*Vec2f_set1)( Vec2f::value_type, Vec2f::value_type ) = &Vec2f::set; 

Vec2d::value_type& (Vec2d::*Vec2d_x1)( ) = &Vec2d::x;
Vec2d::value_type& (Vec2d::*Vec2d_y1)( ) = &Vec2d::y;
void (Vec2d::*Vec2d_set1)( Vec2d::value_type, Vec2d::value_type ) = &Vec2d::set; 

Vec3f::value_type& (Vec3f::*Vec3f_x1)( ) = &Vec3f::x;
Vec3f::value_type& (Vec3f::*Vec3f_y1)( ) = &Vec3f::y;
Vec3f::value_type& (Vec3f::*Vec3f_z1)( ) = &Vec3f::z;
void (Vec3f::*Vec3f_set1)( Vec3f::value_type, Vec3f::value_type, Vec3f::value_type ) = &Vec3f::set; 

Vec3d::value_type& (Vec3d::*Vec3d_x1)( ) = &Vec3d::x;
Vec3d::value_type& (Vec3d::*Vec3d_y1)( ) = &Vec3d::y;
Vec3d::value_type& (Vec3d::*Vec3d_z1)( ) = &Vec3d::z;
void (Vec3d::*Vec3d_set1)( Vec3d::value_type, Vec3d::value_type, Vec3d::value_type ) = &Vec3d::set; 

Vec4f::value_type& (Vec4f::*Vec4f_x1)( ) = &Vec4f::x;
Vec4f::value_type& (Vec4f::*Vec4f_y1)( ) = &Vec4f::y;
Vec4f::value_type& (Vec4f::*Vec4f_z1)( ) = &Vec4f::z;
Vec4f::value_type& (Vec4f::*Vec4f_w1)( ) = &Vec4f::w;
void (Vec4f::*Vec4f_set1)( Vec4f::value_type, Vec4f::value_type, Vec4f::value_type, Vec4f::value_type ) = &Vec4f::set; 

Vec4d::value_type& (Vec4d::*Vec4d_x1)( ) = &Vec4d::x;
Vec4d::value_type& (Vec4d::*Vec4d_y1)( ) = &Vec4d::y;
Vec4d::value_type& (Vec4d::*Vec4d_z1)( ) = &Vec4d::z;
Vec4d::value_type& (Vec4d::*Vec4d_w1)( ) = &Vec4d::w;
void (Vec4d::*Vec4d_set1)( Vec4d::value_type, Vec4d::value_type, Vec4d::value_type, Vec4d::value_type ) = &Vec4d::set; 

void (BoundingBox::*BoundingBox_set1)( BoundingBox::value_type, BoundingBox::value_type, BoundingBox::value_type, 
                                       BoundingBox::value_type, BoundingBox::value_type, BoundingBox::value_type ) = &BoundingBox::set;
void (BoundingBox::*BoundingBox_set2)( const BoundingBox::vec_type&, const BoundingBox::vec_type& ) = &BoundingBox::set;
BoundingBox::value_type& (BoundingBox::*BoundingBox_xMin1)( ) = &BoundingBox::xMin;
BoundingBox::value_type& (BoundingBox::*BoundingBox_yMin1)( ) = &BoundingBox::yMin;
BoundingBox::value_type& (BoundingBox::*BoundingBox_zMin1)( ) = &BoundingBox::zMin;
BoundingBox::value_type& (BoundingBox::*BoundingBox_xMax1)( ) = &BoundingBox::xMax;
BoundingBox::value_type& (BoundingBox::*BoundingBox_yMax1)( ) = &BoundingBox::yMax;
BoundingBox::value_type& (BoundingBox::*BoundingBox_zMax1)( ) = &BoundingBox::zMax;


void export_math()
{
    class_<Vec2f>("Vec2f")
        .def_readonly("_v", &Vec2f::_v)                                             // Should be readwrite...

        // default ctor
        .def(init<Vec2f>())
        // ctor that takes x, y.
        .def(init<Vec2f::value_type, Vec2f::value_type>())

        .def("x", Vec2f_x1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("y", Vec2f_y1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("set", Vec2f_set1)
        // TODO
    ;

    array_utils::to_tuple_mapping< float[2], 2 >();

    class_<Vec2d>("Vec2d")
        .def_readonly("_v", &Vec2d::_v)                                             // Should be readwrite...

        // default ctor
        .def(init<Vec2d>())
        // ctor that takes x, y.
        .def(init<Vec2d::value_type, Vec2d::value_type>())
        // TODO: Conversion from Vec2f

        .def("x", Vec2d_x1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("y", Vec2d_y1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("set", Vec2d_set1)
        // TODO
    ;

    array_utils::to_tuple_mapping< double[2], 2 >();

    class_<Vec3f>("Vec3f")
        .def_readonly("_v", &Vec3f::_v)                                             // Should be readwrite...

        // default ctor
        .def(init<Vec3f>())
        // ctor that takes x, y, z.
        .def(init<Vec3f::value_type, Vec3f::value_type, Vec3f::value_type>())
        // ctor that takes a vec2(x,y) and z.
        .def(init<const Vec2f&, Vec3f::value_type>())

        .def("x", Vec3f_x1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("y", Vec3f_y1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("z", Vec3f_z1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("set", Vec3f_set1)
        // TODO
    ;

    array_utils::to_tuple_mapping< float[3], 3 >();

    class_<Vec3d>("Vec3d")
        .def_readonly("_v", &Vec3d::_v)                                             // Should be readwrite...

        // default ctor
        .def(init<Vec3d>())
        // ctor that takes x, y, z.
        .def(init<Vec3d::value_type, Vec3d::value_type, Vec3d::value_type>())
        // ctor that takes a vec2(x,y) and z.
        .def(init<const Vec2d&, Vec3d::value_type>())
        // TODO: Conversion from Vec3f

        .def("x", Vec3d_x1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("y", Vec3d_y1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("z", Vec3d_z1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("set", Vec3d_set1)
        // TODO
    ;

    array_utils::to_tuple_mapping< double[3], 3 >();

    class_<Vec4f>("Vec4f")
        .def_readonly("_v", &Vec4f::_v)                                             // Should be readwrite...

        // default ctor
        .def(init<Vec4f>())
        // ctor that takes x, y, z, w.
        .def(init<Vec4f::value_type, Vec4f::value_type, Vec4f::value_type, Vec4f::value_type>())
        // ctor that takes a vec3(x,y,z) and w.
        .def(init<const Vec3f&, Vec4f::value_type>())

        .def("x", Vec4f_x1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("y", Vec4f_y1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("z", Vec4f_z1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("w", Vec4f_w1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("set", Vec4f_set1)
        // TODO
    ;

    array_utils::to_tuple_mapping< float[4], 4 >();

    class_<Vec4d>("Vec4d")
        .def_readonly("_v", &Vec4d::_v)                                             // Should be readwrite...

        // default ctor
        .def(init<Vec4d>())
        // ctor that takes x, y, z, w.
        .def(init<Vec4d::value_type, Vec4d::value_type, Vec4d::value_type, Vec4d::value_type>())
        // ctor that takes a vec3(x,y,z) and w.
        .def(init<const Vec3d&, Vec4d::value_type>())
        // TODO: Conversion from Vec4f

        .def("x", Vec4d_x1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("y", Vec4d_y1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("z", Vec4d_z1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("w", Vec4d_w1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("set", Vec4d_set1)
        // TODO
    ;

    array_utils::to_tuple_mapping< double[4], 4 >();

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
        .def("xMin", BoundingBox_xMin1, return_value_policy<copy_non_const_reference>())        // Will this work when setting?
        .def("yMin", BoundingBox_yMin1, return_value_policy<copy_non_const_reference>())
        .def("zMin", BoundingBox_zMin1, return_value_policy<copy_non_const_reference>())
        .def("xMax", BoundingBox_xMax1, return_value_policy<copy_non_const_reference>())
        .def("yMax", BoundingBox_yMax1, return_value_policy<copy_non_const_reference>())
        .def("zMax", BoundingBox_zMax1, return_value_policy<copy_non_const_reference>())
        .def("center", &BoundingBox::center)
        .def("radius", &BoundingBox::radius)
        .def("radius2", &BoundingBox::radius2)
        .def("corner", &BoundingBox::corner)
        // TODO: expand methods
        // TODO: contains and intersects methods
    ;
}
