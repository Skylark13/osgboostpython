#include <boost/python.hpp>
using namespace boost::python;

#include <osg/Depth>

using namespace osg;

#include "defaults.h"

void export_depth() {

    scope in_Depth = class_<Depth, bases<StateAttribute>, ref_ptr<Depth>, boost::noncopyable>("Depth")
        .def(init<>())
//      .def(init<Depth::Function, double, double, bool>())
        .def("setFunction", &Depth::setFunction)
        .def("setRange", &Depth::setRange)
    ;

    enum_<Depth::Function>("Function");
        scope().attr("NEVER") = Depth::NEVER;
        scope().attr("LESS") = Depth::LESS;
        scope().attr("EQUAL") = Depth::EQUAL;
        scope().attr("LEQUAL") = Depth::LEQUAL;
        scope().attr("GREATER") = Depth::GREATER;
        scope().attr("NOTEQUAL") = Depth::NOTEQUAL;
        scope().attr("GEQUAL") = Depth::GEQUAL;
        scope().attr("ALWAYS") = Depth::ALWAYS;

}

