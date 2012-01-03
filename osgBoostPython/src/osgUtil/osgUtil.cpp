#include <boost/python.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
using namespace boost::python;
#include "defaults.h"

#define EXPORT_THESE \
  (IntersectionVisitor) \
    (LineSegmentIntersector) \
  (Simplifier) \
  (CullVisitor) \
  (UpdateVisitor) 

OSGBP_MODULE( _osgUtil, EXPORT_THESE )

