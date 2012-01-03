#include "boost/python.hpp"
#include <osgUtil/CullVisitor>

using namespace osg;
using namespace osgUtil;
using namespace boost::python;

#include "defaults.h"

void export_CullVisitor() {

  scope in_CullVisitor = 
    class_<CullVisitor, bases<NodeVisitor>, ref_ptr<CullVisitor> >("CullVisitor")
    .add_property("traversalMode", &CullVisitor::getTraversalMode, &CullVisitor::setTraversalMode )
    .add_property("className", &CullVisitor::className )
    ;

 }
