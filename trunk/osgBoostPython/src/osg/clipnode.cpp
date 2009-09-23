#include <boost/python.hpp>
using namespace boost::python;

#include <osg/ClipNode>
using namespace osg;

#include "defaults.h"

bool (ClipNode::*ClipNode_removeClipPlane1)(osg::ClipPlane * clipplane) = & ClipNode::removeClipPlane;
bool (ClipNode::*ClipNode_removeClipPlane2)(unsigned int pos) = & ClipNode::removeClipPlane;
osg::ClipPlane * (ClipNode::*ClipNode_getClipPlane3)(unsigned int pos) = & ClipNode::getClipPlane;
osg::ClipPlane const * (ClipNode::*ClipNode_getClipPlane4)(unsigned int pos) const = & ClipNode::getClipPlane;
std::vector<osg::ref_ptr<osg::ClipPlane>, std::allocator<osg::ref_ptr<osg::ClipPlane> > > & (ClipNode::*ClipNode_getClipPlaneList5)() = & ClipNode::getClipPlaneList;
//std::vector<osg::ref_ptr<osg::ClipPlane>, std::allocator<osg::ref_ptr<osg::ClipPlane> > > const & (ClipNode::*ClipNode_getClipPlaneList6)() = & ClipNode::getClipPlaneList;

void export_clipnode() {

    scope in_ClipNode=
    class_<ClipNode, bases<Group>, ref_ptr<ClipNode>, boost::noncopyable >("ClipNode")
        .def("createClipBox", &ClipNode::createClipBox)
        .def("getClipPlane", ClipNode_getClipPlane3,  osgBoostPython::default_pointer_policy())
        .def("isSameKindAs", &ClipNode::isSameKindAs)
        .def("setStateSetModes", &ClipNode::setStateSetModes)
        .def("removeClipPlane", ClipNode_removeClipPlane1)
        .def("removeClipPlane", ClipNode_removeClipPlane2)
        .def("getNumClipPlanes", &ClipNode::getNumClipPlanes)
        .def("addClipPlane", &ClipNode::addClipPlane)
        .def("accept", &ClipNode::accept)
        .def("getReferenceFrame", &ClipNode::getReferenceFrame)
        .def("setClipPlaneList", &ClipNode::setClipPlaneList)
        //.def("getClipPlaneList", ClipNode_getClipPlaneList5)
        .def("className", &ClipNode::className)
        .def("setReferenceFrame", &ClipNode::setReferenceFrame)
        ////.def("getClipPlaneList", ClipNode_getClipPlaneList6)
        .def("setLocalStateSetModes", &ClipNode::setLocalStateSetModes)
        .def("computeBound", &ClipNode::computeBound)
        //.def("getClipPlane", ClipNode_getClipPlane4)
    ; 

    enum_<ClipNode::ReferenceFrame>("ReferenceFrame");
	scope().attr("RELATIVE_RF") = ClipNode::RELATIVE_RF;
	scope().attr("ABSOLUTE_RF") = ClipNode::ABSOLUTE_RF;
    
}