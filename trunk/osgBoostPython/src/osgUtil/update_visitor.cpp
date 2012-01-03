#include "boost/python.hpp"
#include <osgUtil/UpdateVisitor>

using namespace osg;
using namespace osgUtil;
using namespace boost::python;

#include "defaults.h"

void export_UpdateVisitor() {

  scope in_UpdateVisitor = 
    class_<UpdateVisitor, bases<NodeVisitor>, ref_ptr<UpdateVisitor> >("UpdateVisitor")
    ;
 }
