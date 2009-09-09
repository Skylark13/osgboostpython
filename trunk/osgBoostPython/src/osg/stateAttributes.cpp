#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Texture>
#include <osg/Texture2D>

using namespace osg;

#include "defaults.h"


void (Texture2D::*Texture2D_setImage1)(Image*) = &Texture2D::setImage;
Image* (Texture2D::*Texture2D_getImage1)() = &Texture2D::getImage;

void export_stateAttributes()
{
    {
        scope in_Texture = class_<Texture, bases<StateAttribute>, ref_ptr<Texture>, boost::noncopyable >("Texture", no_init)
        ;
    }

    {
        scope in_Texture2D = class_<Texture2D, bases<Texture>, ref_ptr<Texture2D> >("Texture2D")
            .def(init<>())
            .def(init<Image*>())
            .def("setImage", Texture2D_setImage1)
            .def("getImage", Texture2D_getImage1, osgBoostPython::default_pointer_policy())
        ;
    }
}
