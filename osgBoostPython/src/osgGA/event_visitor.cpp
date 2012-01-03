#include "boost/python.hpp"
#include <osgGA/EventVisitor>

using namespace osg;
using namespace osgGA;
using namespace boost::python;

#include "defaults.h"

void export_EventVisitor() {

  scope in_EventVisitor = 
    class_<EventVisitor, bases<NodeVisitor>, ref_ptr<EventVisitor> >("EventVisitor")
    .add_property("traversalMode", &EventVisitor::getTraversalMode, &EventVisitor::setTraversalMode )
    .add_property("className", &EventVisitor::className )
    ;
 }
