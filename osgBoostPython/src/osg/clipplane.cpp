#include <boost/python.hpp>
//#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

//#include <osg/StateAttribute>
#include <osg/ClipPlane>
using namespace osg;

#include "defaults.h"

void (ClipPlane::*ClipPlane_setClipPlane1)(osg::Plane const & plane) = & ClipPlane::setClipPlane;
void (ClipPlane::*ClipPlane_setClipPlane2)(double a, double b, double c, double d) = & ClipPlane::setClipPlane;
void (ClipPlane::*ClipPlane_setClipPlane3)(osg::Vec4d const & plane) = & ClipPlane::setClipPlane;

void export_clipplane() {

    class_<ClipPlane, bases<StateAttribute>, ref_ptr<ClipPlane>, boost::noncopyable >("ClipPlane")
        .def(init<>())
        .def("getType", &ClipPlane::getType)
        //.def("getClipPlane", &ClipPlane::getClipPlane) //returns const Vec4d &
        .def("setClipPlane", ClipPlane_setClipPlane3)
        .def("setClipPlane", ClipPlane_setClipPlane2)
        //.def("getModeUsage", &ClipPlane::getModeUsage)
        .def("setClipPlane", ClipPlane_setClipPlane1)
        .def("getMember", &ClipPlane::getMember)
        .def("setClipPlaneNum", &ClipPlane::setClipPlaneNum)
        .def("getClipPlaneNum", &ClipPlane::getClipPlaneNum)
    ; 
    
}
