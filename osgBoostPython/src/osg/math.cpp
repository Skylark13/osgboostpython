#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Vec3f>
#include <osg/Vec3d>
#include <osg/Matrixf>
#include <osg/Matrixd>
#include <osg/BoundingSphere>

using namespace osg;

void export_math()
{
    class_<Vec3f>("Vec3f")
        // TODO
    ;

    class_<Vec3d>("Vec3d")
        // TODO
    ;

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
        .def(init<BoundingSphere::vec_type, BoundingSphere::value_type>())
        .def(init<BoundingSphere>())
        // TODO: BoundingBox
        //.def(init<BoundingBox>())
        .def("init", &BoundingSphere::init)
        .def("valid", &BoundingSphere::valid)
        // TODO: expand methods
        // TODO: contains and intersects methods
    ;
}
