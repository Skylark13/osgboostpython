#include <boost/python.hpp>
#include <boost/python/override.hpp>
using namespace boost::python;

#include <osgGA/GUIEventHandler>
#include <osgGA/StateSetManipulator>
#include <osgViewer/View>

#include <iostream>

using namespace osg;
using namespace osgGA;

void export_guieventadapter();

struct GUIEventHandler_wrapper : public GUIEventHandler
{
    // GUIEventHandler constructor storing initial self parameter
    GUIEventHandler_wrapper(PyObject *p)
        : GUIEventHandler(), self(p) {}

    // In case GUIEventHandler is returned by-value from a wrapped function
    GUIEventHandler_wrapper(PyObject *p, const GUIEventHandler& x)
        : GUIEventHandler(x), self(p) {}

    // Override handle to call back into Python
    bool handle(const GUIEventAdapter* ea, GUIActionAdapter* aa, osg::Object* obj, osg::NodeVisitor* nv)
    {
        return call_method<bool>(self, "handle", ptr(ea), ptr(aa), ptr(obj), ptr(nv));
    }

    // This version will be called by OSG, and calls the other version.
    bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
    {
        return handle(&ea, &aa, obj, nv);
    }

    // Supplies the default implementation of handle
    bool default_handle1(GUIEventHandler& self_, const GUIEventAdapter* ea, GUIActionAdapter* aa, osg::Object* obj, osg::NodeVisitor* nv)
    {
        return self_.GUIEventHandler::handle(*ea, *aa, obj, nv);
    }

    // Override handle to call back into Python
    bool handle(const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        return call_method<bool>(self, "handle", ptr(ea), ptr(aa));
    }

    // This version will be called by OSG, and calls the other version.
    bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
    {
        return handle(&ea, &aa);
    }

    // Supplies the default implementation of handle
    bool default_handle2(GUIEventHandler& self_, const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        return self_.GUIEventHandler::handle(*ea, *aa);
    }

 private:
    PyObject* self;
};

BOOST_PYTHON_MODULE(_osgGA)
{

    export_guieventadapter();

    // Abstract base class for osgViewer::View
    class_<GUIActionAdapter, boost::noncopyable>("GUIActionAdapter", no_init)
    ;

    class_<GUIEventHandler, GUIEventHandler_wrapper, bases<osg::NodeCallback, osg::Drawable::DrawCallback>, ref_ptr<GUIEventHandler> >("GUIEventHandler")
        .def(init<>())
        .def("handle", &GUIEventHandler_wrapper::default_handle1)
        .def("handle", &GUIEventHandler_wrapper::default_handle2)
        //.def("handleWithCheckAgainstIgnoreHandledEventsMask", &GUIEventHandler_handleWithCheckAgainstIgnoreHandledEventsMask1)
        //.def("handleWithCheckAgainstIgnoreHandledEventsMask", &GUIEventHandler_handleWithCheckAgainstIgnoreHandledEventsMask2)
    ;

    class_<StateSetManipulator, bases<GUIEventHandler>, ref_ptr<StateSetManipulator> >("StateSetManipulator")
        .def(init<StateSet*>())
    ;
}
