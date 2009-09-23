#include <boost/python.hpp>
using namespace boost::python;

#include <osg/ColorMask>
using namespace osg;

#include "defaults.h"

void export_colormask() {

    class_<ColorMask, bases<StateAttribute>, ref_ptr<ColorMask>, boost::noncopyable >("ColorMask")
       .def(init<>())
       .def(init<bool,bool,bool,bool>())
       .def("setMask", &ColorMask::setMask)
   ; 

}
