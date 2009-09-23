#include <boost/python.hpp>
using namespace boost::python;

#include <osgGA/GUIEventHandler>

using namespace osg;
using namespace osgGA;

#include "defaults.h"

void export_guieventadapter() {

    {
        scope in_GUIEventAdapter = 
        class_<GUIEventAdapter, bases<osg::Object>, ref_ptr<GUIEventAdapter> >("GUIEventAdapter")
            .def(init<>())
            .def("getEventType", &GUIEventAdapter::getEventType, osgBoostPython::default_value_policy())
            .def("getX", &GUIEventAdapter::getX, osgBoostPython::default_value_policy())
            .def("getY", &GUIEventAdapter::getY, osgBoostPython::default_value_policy())
            .def("getXnormalized", &GUIEventAdapter::getXnormalized, osgBoostPython::default_value_policy())
            .def("getYnormalized", &GUIEventAdapter::getYnormalized, osgBoostPython::default_value_policy())
        ;

        enum_<GUIEventAdapter::MouseButtonMask>("MouseButtonMask");
            scope().attr("LEFT_MOUSE_BUTTON") = GUIEventAdapter::LEFT_MOUSE_BUTTON;
            scope().attr("MIDDLE_MOUSE_BUTTON") = GUIEventAdapter::MIDDLE_MOUSE_BUTTON;
            scope().attr("RIGHT_MOUSE_BUTTON") = GUIEventAdapter::RIGHT_MOUSE_BUTTON;

        enum_<GUIEventAdapter::EventType>("EventType");
            scope().attr("NONE") = GUIEventAdapter::NONE;
            scope().attr("PUSH") = GUIEventAdapter::PUSH;
            scope().attr("RELEASE") = GUIEventAdapter::RELEASE;
            scope().attr("DOUBLECLICK") = GUIEventAdapter::DOUBLECLICK;
            scope().attr("DRAG") = GUIEventAdapter::DRAG;
            scope().attr("MOVE") = GUIEventAdapter::MOVE;
            scope().attr("KEYDOWN") = GUIEventAdapter::KEYDOWN;
            scope().attr("KEYUP") = GUIEventAdapter::KEYUP;
            scope().attr("FRAME") = GUIEventAdapter::FRAME;
            scope().attr("RESIZE") = GUIEventAdapter::RESIZE;
            scope().attr("SCROLL") = GUIEventAdapter::SCROLL;
            scope().attr("PEN_PRESSURE") = GUIEventAdapter::PEN_PRESSURE;
            scope().attr("PEN_ORIENTATION") = GUIEventAdapter::PEN_ORIENTATION;
            scope().attr("PEN_PROXIMITY_ENTER") = GUIEventAdapter::PEN_PROXIMITY_ENTER;
            scope().attr("PEN_PROXIMITY_LEAVE") = GUIEventAdapter::PEN_PROXIMITY_LEAVE;
            scope().attr("CLOSE_WINDOW") = GUIEventAdapter::CLOSE_WINDOW;
            scope().attr("QUIT_APPLICATION") = GUIEventAdapter::QUIT_APPLICATION;
            scope().attr("USER") = GUIEventAdapter::USER;

    }
}

