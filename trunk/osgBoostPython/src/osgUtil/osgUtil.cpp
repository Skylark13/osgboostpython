// Many parts taken from:
// Wrapper by Brett Hartshorn.  bhartshorn@opart.org
// Permission to copy, use, sell and distribute this software is granted
// provided this copyright notice appears in all copies.
// Permission to modify the code and to distribute modified code is granted
// provided this copyright notice appears in all copies, and a notice
// that the code was modified is included with the copyright notice.
//
// This software is provided "as is" without express or implied warranty,
// and with no claim as to its suitability for any purpose.


#include <boost/python.hpp>
using namespace boost::python;

#include <osgUtil/IntersectionVisitor>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/PolytopeIntersector>
#include <osgUtil/IntersectVisitor>

using namespace osg;
using namespace osgUtil;

typedef osgUtil::LineSegmentIntersector::Intersection Intersection;
//typedef osgUtil::LineSegmentIntersector LineSegmentIntersector;

osg::NodePath* getNodePath(osgUtil::Hit * self)
{
    return & self->getNodePath();
}


inline osgUtil::Hit::VecIndexList * vecIndexList(osgUtil::Hit * self)
{
    return &self->_vecIndexList;
}

int __getitem__(osgUtil::Hit::VecIndexList * self, int idx)
{
    return (*self)[idx];
}

void export_hit()
{
    class_<Hit>("Hit")
        .def(init<>())
         .def_readonly("ratio", &osgUtil::Hit::_ratio)
         .def_readonly("nodePath", &osgUtil::Hit::_nodePath)
         .def_readonly("drawable", &osgUtil::Hit::_drawable)
         .def_readonly("matrix", &osgUtil::Hit::_matrix)
         .def_readonly("vecIndexList", &osgUtil::Hit::_vecIndexList)
         .def_readonly("primitiveIndex", &osgUtil::Hit::_primitiveIndex)
         .def_readonly("geode", &osgUtil::Hit::_geode)
         .def_readonly("matrix", &osgUtil::Hit::_matrix)
         .def_readonly("inverse", &osgUtil::Hit::_inverse)

           .def("getLocalIntersectPoint", &osgUtil::Hit::getLocalIntersectPoint,return_internal_reference<>())
           .def("getWorldIntersectPoint", &osgUtil::Hit::getWorldIntersectPoint)
           .def("getLocalIntersectNormal", &osgUtil::Hit::getLocalIntersectNormal,return_internal_reference<>())
           .def("getWorldIntersectNormal", &osgUtil::Hit::getWorldIntersectNormal)

//         .def("getLocalIntersectPoint", &osgUtil::Hit::getLocalIntersectPoint, return_internal_reference<>())
//          .def("getLocalIntersectNormal",            &osgUtil::Hit::getLocalIntersectNormal, return_internal_reference<>())
//          .def("getWorldIntersectPoint",                        &osgUtil::Hit::getWorldIntersectPoint)
//          .def("getWorldIntersectNormal",                        &osgUtil::Hit::getWorldIntersectNormal)
//          .def("getRatio",                        &osgUtil::Hit::getRatio)
//          .def("getNodePath",                                         &getNodePath, return_internal_reference<>())
//          .def("getGeode",            (osg::Geode *(osgUtil::Hit::*)()) &osgUtil::Hit::getGeode) //TODO: policy?, return_value_policy<manage_osg_object>())
// //         .def("geode",                                         &geode, return_internal_reference<>())
//          .def("drawable",                                         &drawable, return_internal_reference<>())
//          .def("vecIndexList",                                         &vecIndexList, return_internal_reference<>())
//          .def_readonly("_ratio",    &osgUtil::Hit::_ratio)
    //    make_getter( &geode, return_value_policy<manage_osg_object>())); FIXME - manage the object
    //    hit.add_property("_geode", make_getter(&geode, return_internal_reference<>()));
    //    hit.add_property("_drawable", &drawable);
    //    hit.add_property("_matrix", &matrix);
    //    hit.add_property("_inverse", &inverse);
    ;

    class_<osgUtil::Hit::VecIndexList>("VecIndexList")
        .def("__iter__", iterator<osgUtil::Hit::VecIndexList>())
        .def("size", &osgUtil::Hit::VecIndexList::size)
        .def("__getitem__", __getitem__)
    ;
}

osgUtil::Hit * hitlist_front(osgUtil::IntersectVisitor::HitList &hlist)
{
    return &hlist.front();
}

BOOST_PYTHON_MODULE(_osgUtil)
{
    export_hit();

    class_<osgUtil::IntersectVisitor, bases<osg::NodeVisitor>, boost::noncopyable > intersect_visitor("IntersectVisitor", no_init);
    {
        scope intersect_visitor_scope(intersect_visitor);

        class_<osgUtil::IntersectVisitor::HitList> hitlist("HitList");
        hitlist
            .def("__iter__", iterator<osgUtil::IntersectVisitor::HitList>())
               // , return_internal_reference<>()
//            >())
           .def("empty",&osgUtil::IntersectVisitor::HitList::empty)
           .def("size",&osgUtil::IntersectVisitor::HitList::size)
           .def("max_size",&osgUtil::IntersectVisitor::HitList::max_size)
           .def("capacity",&osgUtil::IntersectVisitor::HitList::capacity)
           .def("front",
                //&osgUtil::IntersectVisitor::HitList::front,
                &hitlist_front,
                return_internal_reference<>())
        ;

        intersect_visitor
            .def(init<>())
            .def("reset", &osgUtil::IntersectVisitor::reset)
            .def("addLineSegment", &osgUtil::IntersectVisitor::addLineSegment)
                /** Add a line segment to use for intersection testing during scene traversal.*/
            .def("setEyePoint", &osgUtil::IntersectVisitor::setEyePoint)
            .def("getHitList", &osgUtil::IntersectVisitor::getHitList, return_internal_reference<>())
            .def("getNumHits", &osgUtil::IntersectVisitor::getNumHits)
            .def("hits", &osgUtil::IntersectVisitor::hits)
        ;
    }

//    class_<osgUtil::LineSegmentIntersector>("LineSegmentIntersector") //, bases<osgUtil::Intersector>, ref_ptr<osgUtil::LineSegmentIntersector> >("LineSegmentIntersector")
//        .def(init<const osg::Vec3d&, const osg::Vec3d&>())
//        .def("getIntersections", &LineSegmentIntersector::getIntersections)
//         .def("getFirstIntersection", &LineSegmentIntersector::getFirstIntersection)
//         .def("setStart", &LineSegmentIntersector::setStart)
//         .def("getStart", &LineSegmentIntersector::getStart)
//         .def("setEnd", &LineSegmentIntersector::setEnd)
//         .def("getEnd", &LineSegmentIntersector::getEnd)
//         .def("intersect", &LineSegmentIntersector::intersect)
//         .def("reset", &LineSegmentIntersector::reset)
//         .def("containsIntersections", &LineSegmentIntersector::containsIntersections)
//    ;
//
//     class_<Intersection>("LineSegmentIntersector_Intersection")
//         .def_readonly("ratio", &Intersection::ratio)
//         .def_readonly("nodePath", &Intersection::nodePath)
//         .def_readonly("drawable", &Intersection::drawable)
//         .def_readonly("matrix", &Intersection::matrix)
// //see get method        .def_readonly("localIntersectionPoint", &Intersection::localIntersectionPoint)
// //see get method        .def_readonly("localIntersectionNormal", &Intersection::localIntersectionNormal)
//         .def_readonly("indexList", &Intersection::indexList)
//         .def_readonly("ratioList", &Intersection::ratioList)
//         .def_readonly("primitiveIndex", &Intersection::primitiveIndex)
// 
//         .def_readonly("getLocalIntersectPoint", &Intersection::getLocalIntersectPoint)
//         .def_readonly("getWorldIntersectPoint", &Intersection::getWorldIntersectPoint)
// 
//         .def_readonly("getLocalIntersectNormal", &Intersection::getLocalIntersectNormal)
//         .def_readonly("getWorldIntersectNormal", &Intersection::getWorldIntersectNormal)
//     ;

//
//         /** Construct a LineSegmentIntersector the runs between the specified start and end points in MODEL coordinates. */
//         LineSegmentIntersector(const osg::Vec3d& start, const osg::Vec3d& end);
//
//         /** Construct a LineSegmentIntersector the runs between the specified start and end points in the specified coordinate frame. */
//         LineSegmentIntersector(CoordinateFrame cf, const osg::Vec3d& start, const osg::Vec3d& end);
//
//         /** Convenience constructor for supporting picking in WINDOW, or PROJECTION coordinates
//           * In WINDOW coordinates creates a start value of (x,y,0) and end value of (x,y,1).
//           * In PROJECTION coordinates (clip space cube) creates a start value of (x,y,-1) and end value of (x,y,1).
//           * In VIEW and MODEL coordinates creates a start value of (x,y,0) and end value of (x,y,1).*/
//         LineSegmentIntersector(CoordinateFrame cf, double x, double y);

//         struct Intersection
//         {
//             Intersection():
//                 ratio(-1.0),
//                 primitiveIndex(0) {}
// 
//             bool operator < (const Intersection& rhs) const { return ratio < rhs.ratio; }
// 
//             typedef std::vector<unsigned int>   IndexList;
//             typedef std::vector<double>         RatioList;
// 

}
