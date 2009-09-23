#include <boost/python.hpp>
using namespace boost::python;

#include <osgViewer/View>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

using namespace osg;
using namespace osgViewer;

#include "defaults.h"

// Generates thin wrappers for methods that have default arguments
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/python/functions.html#python.default_arguments
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(osgViewer_frame_overloads, frame, 0, 1)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(osgViewer_setUpViewInWindow_overloads, setUpViewInWindow, 4, 5)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(osgViewer_setUpViewOnSingleScreen_overloads, setUpViewOnSingleScreen, 0, 1)

//Node* (Drawable::*Drawable_getParent1)( unsigned int ) = &Drawable::getParent;
osg::Camera* (Viewer::*Viewer_getCameraWithFocus1)() = &Viewer::getCameraWithFocus;

BOOST_PYTHON_MODULE(_osgViewer)
{
    class_<ViewerBase, bases<Object>, ref_ptr<ViewerBase>, boost::noncopyable>("ViewerBase", no_init)
    ;

    // TODO: Wrap osgViewer::View at least, then osgViewer::ViewerBase and osgViewer::CompositeViewer.
    class_<osgViewer::View, bases<osg::View, osgGA::GUIActionAdapter>, ref_ptr<osgViewer::View> >("View")
        .def("setUpViewAcrossAllScreens", &osgViewer::View::setUpViewAcrossAllScreens)
        .def("setUpViewInWindow", &osgViewer::View::setUpViewInWindow, osgViewer_setUpViewInWindow_overloads())
        .def("setUpViewOnSingleScreen", &osgViewer::View::setUpViewOnSingleScreen, osgViewer_setUpViewOnSingleScreen_overloads())
    ;

    // Need wrapper for osgViewer::View, which needs wrapper for osg::View, ...
    class_<Viewer, bases<osgViewer::View, osgViewer::ViewerBase>, ref_ptr<Viewer> >("Viewer")
        .def("run", &Viewer::run)
        .def("done", &Viewer::done)
        .def("frame", &Viewer::frame, osgViewer_frame_overloads())
        .def("addEventHandler", &Viewer::addEventHandler)
        .def("setSceneData", &Viewer::setSceneData)
        .def("getCameraWithFocus", Viewer_getCameraWithFocus1, osgBoostPython::default_pointer_policy())
    ;

    class_<HelpHandler, bases<osgGA::GUIEventHandler>, ref_ptr<HelpHandler> >("HelpHandler")
    ;

    class_<StatsHandler, bases<osgGA::GUIEventHandler>, ref_ptr<StatsHandler> >("StatsHandler")
    ;
}
