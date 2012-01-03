#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/IntersectionVisitor>
//Marked *deprecated* in osgUtil: #include <osgUtil/IntersectVisitor>

using namespace osg;
using namespace osgUtil;
using namespace boost::python;

#include "defaults.h"

void (IntersectionVisitor::*IntersectionVisitor_reset2)() = & IntersectionVisitor::reset;
osgUtil::Intersector * (IntersectionVisitor::*IntersectionVisitor_getIntersector3)() = & IntersectionVisitor::getIntersector;
osgUtil::Intersector const * (IntersectionVisitor::*IntersectionVisitor_getIntersector4)()const = & IntersectionVisitor::getIntersector;
osgUtil::IntersectionVisitor::ReadCallback * (IntersectionVisitor::*IntersectionVisitor_getReadCallback5)() = & IntersectionVisitor::getReadCallback;
osgUtil::IntersectionVisitor::ReadCallback const * (IntersectionVisitor::*IntersectionVisitor_getReadCallback6)() const = & IntersectionVisitor::getReadCallback;
void (IntersectionVisitor::*IntersectionVisitor_pushWindowMatrix7)(osg::RefMatrix * matrix) = & IntersectionVisitor::pushWindowMatrix;
void (IntersectionVisitor::*IntersectionVisitor_pushWindowMatrix8)(osg::Viewport * viewport) = & IntersectionVisitor::pushWindowMatrix;
osg::RefMatrix * (IntersectionVisitor::*IntersectionVisitor_getWindowMatrix9)() = & IntersectionVisitor::getWindowMatrix;
osg::RefMatrix const * (IntersectionVisitor::*IntersectionVisitor_getWindowMatrix10)() const = & IntersectionVisitor::getWindowMatrix;
osg::RefMatrix * (IntersectionVisitor::*IntersectionVisitor_getProjectionMatrix11)() = & IntersectionVisitor::getProjectionMatrix;
osg::RefMatrix const * (IntersectionVisitor::*IntersectionVisitor_getProjectionMatrix12)() const = & IntersectionVisitor::getProjectionMatrix;
osg::RefMatrix * (IntersectionVisitor::*IntersectionVisitor_getViewMatrix13)() = & IntersectionVisitor::getViewMatrix;
osg::RefMatrix const * (IntersectionVisitor::*IntersectionVisitor_getViewMatrix14)() const = & IntersectionVisitor::getViewMatrix;
osg::RefMatrix * (IntersectionVisitor::*IntersectionVisitor_getModelMatrix15)() = & IntersectionVisitor::getModelMatrix;
osg::RefMatrix const * (IntersectionVisitor::*IntersectionVisitor_getModelMatrix16)() const = & IntersectionVisitor::getModelMatrix;
void (IntersectionVisitor::*IntersectionVisitor_apply17)(osg::Node & node) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply18)(osg::Geode & geode) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply19)(osg::Billboard & geode) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply20)(osg::Group & group) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply21)(osg::LOD & lod) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply22)(osg::PagedLOD & lod) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply23)(osg::Transform & transform) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply24)(osg::Projection & projection) = & IntersectionVisitor::apply;
void (IntersectionVisitor::*IntersectionVisitor_apply25)(osg::Camera & camera) = & IntersectionVisitor::apply;
osgUtil::Intersector * (Intersector::*Intersector_clone28)(osgUtil::IntersectionVisitor & iv) = & Intersector::clone;
bool (Intersector::*Intersector_enter29)(osg::Node const & node) = & Intersector::enter;
void (Intersector::*Intersector_leave30)() = & Intersector::leave;
void (Intersector::*Intersector_intersect31)(osgUtil::IntersectionVisitor & iv, osg::Drawable * drawable) = & Intersector::intersect;
void (Intersector::*Intersector_reset32)() = & Intersector::reset;
bool (Intersector::*Intersector_containsIntersections33)() = & Intersector::containsIntersections;
osgUtil::Intersector * (IntersectorGroup::*IntersectorGroup_clone35)(osgUtil::IntersectionVisitor & iv) = & IntersectorGroup::clone;
bool (IntersectorGroup::*IntersectorGroup_enter36)(osg::Node const & node) = & IntersectorGroup::enter;
void (IntersectorGroup::*IntersectorGroup_leave37)() = & IntersectorGroup::leave;
void (IntersectorGroup::*IntersectorGroup_intersect38)(osgUtil::IntersectionVisitor & iv, osg::Drawable * drawable) = & IntersectorGroup::intersect;
void (IntersectorGroup::*IntersectorGroup_reset39)() = & IntersectorGroup::reset;
bool (IntersectorGroup::*IntersectorGroup_containsIntersections40)() = & IntersectorGroup::containsIntersections;

typedef std::vector<Intersector*> IntersectorList; 
// const IntersectorList& (IntersectorGroup::*IntersectorGroup_getIntersectorList)() const = &IntersectorGroup::getIntersectors;

void export_IntersectionVisitor() {

  {
    scope in_Intersector = 
      class_<Intersector, bases<Referenced>, ref_ptr<Intersector>, boost::noncopyable>("Intersector", no_init)
      //.def("incrementDisabledCount", &Intersector::incrementDisabledCount)
      //.def("enter", Intersector_enter29)
      //.def("leave", Intersector_leave30)
      .def("setCoordinateFrame", &Intersector::setCoordinateFrame)
      //.def("clone", Intersector_clone28)
      //.def("containsIntersections", Intersector_containsIntersections33)
      //.def("disabled", &Intersector::disabled)
      //.def("getCoordinateFrame", &Intersector::getCoordinateFrame)
      //.def("reset", Intersector_reset32)
      //.def("decrementDisabledCount", &Intersector::decrementDisabledCount)
      //.def("operator=", Intersector_operator=27)
      //.def("intersect", Intersector_intersect31)
      ;
    
    enum_<Intersector::CoordinateFrame>("CoordinateFrame");
    scope().attr("WINDOW") = Intersector::WINDOW;
    scope().attr("PROJECTION") = Intersector::PROJECTION;
    scope().attr("VIEW") = Intersector::VIEW;
    scope().attr("MODEL") = Intersector::MODEL;
    ;
   
  } 

  class_<IntersectorList>("IntersectorList")
    .def( vector_indexing_suite< IntersectorList >() )
    ;	
    
  class_<IntersectorGroup, bases<Intersector>, ref_ptr<IntersectorGroup>, boost::noncopyable>("IntersectorGroup", init<>())
    //.def("clone", IntersectorGroup_clone35)
    //.def("leave", IntersectorGroup_leave37)
    .def("addIntersector", &IntersectorGroup::addIntersector)
    //.def("reset", IntersectorGroup_reset39)
    //.def("enter", IntersectorGroup_enter36)
    //.def("clear", &IntersectorGroup::clear)
    .def("getIntersectors", &IntersectorGroup::getIntersectors, osgBoostPython::default_value_policy())
    //.def("getIntersectors", IntersectorGroup_getIntersectorList, osgBoostPython::default_value_policy()) // &IntersectorGroup::getIntersectors)
    //.def("intersect", IntersectorGroup_intersect38)
    //.def("operator=", IntersectorGroup_operator=34)
    .def("containsIntersections", IntersectorGroup_containsIntersections40)
    ;

  {
    scope in_IntersectionVisitor =
      class_<IntersectionVisitor, bases<osg::NodeVisitor>, ref_ptr<IntersectionVisitor>, boost::noncopyable >( "IntersectionVisitor",  init<Intersector*, optional<IntersectionVisitor::ReadCallback*> >() )
      //.def("apply", IntersectionVisitor_apply20)
      //.def("popProjectionMatrix", &IntersectionVisitor::popProjectionMatrix)
      //.def("popWindowMatrix", &IntersectionVisitor::popWindowMatrix)
      //.def("getReferenceEyePointCoordinateFrame", &IntersectionVisitor::getReferenceEyePointCoordinateFrame)
      //.def("getLODSelectionMode", &IntersectionVisitor::getLODSelectionMode)
      .def("setUseKdTreeWhenAvailable", &IntersectionVisitor::setUseKdTreeWhenAvailable)
      .def("setReferenceEyePoint", &IntersectionVisitor::setReferenceEyePoint)
      //.def("pushViewMatrix", &IntersectionVisitor::pushViewMatrix)
      //.def("getReferenceEyePoint", &IntersectionVisitor::getReferenceEyePoint)
      //.def("popModelMatrix", &IntersectionVisitor::popModelMatrix)
      .def("setReferenceEyePointCoordinateFrame", &IntersectionVisitor::setReferenceEyePointCoordinateFrame)
      .def("reset", IntersectionVisitor_reset2)
      .def("setLODSelectionMode", &IntersectionVisitor::setLODSelectionMode)
      //.def("getViewMatrix", IntersectionVisitor_getViewMatrix13)
      //.def("apply", IntersectionVisitor_apply18)
      //.def("apply", IntersectionVisitor_apply19)
      .def("setIntersector", &IntersectionVisitor::setIntersector)
      //.def("getIntersector", IntersectionVisitor_getIntersector4)
      //.def("getDoDummyTraversal", &IntersectionVisitor::getDoDummyTraversal)
      //.def("pushModelMatrix", &IntersectionVisitor::pushModelMatrix)
      //.def("getIntersector", IntersectionVisitor_getIntersector3)
      .def("setDoDummyTraversal", &IntersectionVisitor::setDoDummyTraversal)
      //.def("getEyePoint", &IntersectionVisitor::getEyePoint)
      //.def("libraryName", &IntersectionVisitor::libraryName)
      //.def("getModelMatrix", IntersectionVisitor_getModelMatrix15)
      //.def("getModelMatrix", IntersectionVisitor_getModelMatrix16)
      //.def("popViewMatrix", &IntersectionVisitor::popViewMatrix)
      //.def("operator=", IntersectionVisitor_operator=1)
      .def("setReadCallback", &IntersectionVisitor::setReadCallback)
      //.def("className", &IntersectionVisitor::className)
      //.def("getDistanceToEyePoint", &IntersectionVisitor::getDistanceToEyePoint)
      //.def("getWindowMatrix", IntersectionVisitor_getWindowMatrix9)
      //.def("getProjectionMatrix", IntersectionVisitor_getProjectionMatrix11)
      //.def("getProjectionMatrix", IntersectionVisitor_getProjectionMatrix12)
      //.def("apply", IntersectionVisitor_apply17)
      //.def("apply", IntersectionVisitor_apply23)
      //.def("apply", IntersectionVisitor_apply22)
      //.def("apply", IntersectionVisitor_apply21)
      //todo: return_policy:   .def("getReadCallback", IntersectionVisitor_getReadCallback6)
      //.def("apply", IntersectionVisitor_apply25)
      //.def("apply", IntersectionVisitor_apply24)
      //todo: return_policy:   .def("getReadCallback", IntersectionVisitor_getReadCallback5)
      //.def("pushWindowMatrix", IntersectionVisitor_pushWindowMatrix7)
      //.def("pushProjectionMatrix", &IntersectionVisitor::pushProjectionMatrix)
      //.def("getUseKdTreeWhenAvailable", &IntersectionVisitor::getUseKdTreeWhenAvailable)
      //.def("getViewMatrix", IntersectionVisitor_getViewMatrix14)
      //.def("getWindowMatrix", IntersectionVisitor_getWindowMatrix10)
      //.def("pushWindowMatrix", IntersectionVisitor_pushWindowMatrix8)
      ;
    
    //.def("operator=", ReadCallback_operator=26)
    //.def("readNodeFile", &ReadCallback::readNodeFile)  
    
  }
  
}
