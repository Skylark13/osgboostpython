#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"

//#include <osg/ref_ptr>

//#include <osg/Referenced>
//#include <osg/Object>

#include <osgUtil/LineSegmentIntersector>
//#include <osgUtil/IntersectionVisitor>
//#include <osgUtil/IntersectVisitor>

using namespace osg;
using namespace osgUtil;
using namespace boost::python;

#include "defaults.h"

Vec3 const & (LineSegmentIntersector::Intersection::*get_loc_int_norm)(void) const = &::LineSegmentIntersector::Intersection::getLocalIntersectNormal;
Vec3d const & ( LineSegmentIntersector::Intersection::*get_loc_int_pt )(void) const = &::LineSegmentIntersector::Intersection::getLocalIntersectPoint;
Vec3 ( LineSegmentIntersector::Intersection::*get_world_int_norm )(void) const =  &::LineSegmentIntersector::Intersection::getWorldIntersectNormal;
Vec3d ( LineSegmentIntersector::Intersection::*get_world_int_pt )(void) const = &::LineSegmentIntersector::Intersection::getWorldIntersectPoint;    
    
void export_linesegmentintersector() {
 
  class_<LineSegmentIntersector, bases<Intersector>, ref_ptr<LineSegmentIntersector>, boost::noncopyable >
      lsi( "LineSegmentIntersector",  init< Intersector::CoordinateFrame, double, double >(( arg("cf"), arg("x"), arg("y") )) );

    scope in_LineSegmentIntersector(lsi);

    class_< LineSegmentIntersector::Intersection >( "Intersection", init< >() )    
      .def(  "getLocalIntersectNormal", get_loc_int_norm, return_value_policy< copy_const_reference >() )    
      .def(  "getLocalIntersectPoint", get_loc_int_pt, return_value_policy< copy_const_reference >() )    
      .def(  "getWorldIntersectNormal", get_world_int_norm )    
      .def(  "getWorldIntersectPoint", get_world_int_pt )    
      .def( self < self )    
      .def_readwrite( "drawable", &LineSegmentIntersector::Intersection::drawable )    
      .def_readwrite( "indexList", &LineSegmentIntersector::Intersection::indexList )    
      .def_readwrite( "localIntersectionNormal", &LineSegmentIntersector::Intersection::localIntersectionNormal )    
      .def_readwrite( "localIntersectionPoint", &LineSegmentIntersector::Intersection::localIntersectionPoint )    
      .def_readwrite( "matrix", &LineSegmentIntersector::Intersection::matrix )    
      .def_readwrite( "nodePath", &LineSegmentIntersector::Intersection::nodePath )    
      .def_readwrite( "primitiveIndex", &LineSegmentIntersector::Intersection::primitiveIndex )    
      .def_readwrite( "ratio", &LineSegmentIntersector::Intersection::ratio )    
      .def_readwrite( "ratioList", &LineSegmentIntersector::Intersection::ratioList );
        
    lsi
      .def( init< Intersector::CoordinateFrame, Vec3d const &, Vec3d const & >(( arg("cf"), arg("start"), arg("end") )) )
      .def( init< Intersector::CoordinateFrame, double, double >(( arg("cf"), arg("x"), arg("y") ) ))        
      //.def("leave", &LineSegmentIntersector::leave)
      //.def("operator=", LineSegmentIntersector_operator=1)
      .def("insertIntersection", &LineSegmentIntersector::insertIntersection)
      .def("setStart", &LineSegmentIntersector::setStart)
      .def("containsIntersections", &LineSegmentIntersector::containsIntersections)
      //.def("enter", &LineSegmentIntersector::enter)
      //.def("clone", &LineSegmentIntersector::clone)
      //.def("operator=", Intersection_operator=2)
      .def("intersect", &LineSegmentIntersector::intersect)
      .def("setEnd", &LineSegmentIntersector::setEnd)
      .def("getEnd", &LineSegmentIntersector::getEnd, osgBoostPython::default_const_reference_policy())
      .def("getStart", &LineSegmentIntersector::getStart, osgBoostPython::default_const_reference_policy())
      .def("reset", &LineSegmentIntersector::reset)
      //.def("operator<", &LineSegmentIntersector::Intersection::operator<)
      .def("getFirstIntersection", &LineSegmentIntersector::getFirstIntersection, osgBoostPython::default_value_policy())
      .def("getIntersections", &LineSegmentIntersector::getIntersections, osgBoostPython::default_reference_policy()) //compiles, but doesn't work.
      .def( init< Vec3d const &, Vec3d const & >(( arg("start"), arg("end") ) ))        
      ;
    
}
