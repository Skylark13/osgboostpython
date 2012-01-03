#include "boost/python.hpp"
#include <osgUtil/Simplifier>

using namespace osg;
using namespace osgUtil;
using namespace boost::python;

#include "defaults.h"

void export_Simplifier() {

  scope in_Simplifier = 
    class_<Simplifier, bases<NodeVisitor>, ref_ptr<Simplifier> >("Simplifier")
    .def(init<double, double, double>() )    
    .add_property("sampleRatio", &Simplifier::getSampleRatio, &Simplifier::setSampleRatio )
    ;

 }
