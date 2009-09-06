#include <boost/python.hpp>
#include <boost/python/override.hpp>
using namespace boost::python;

#define WIN32

#include <osgGA/GUIEventHandler>
#include <osgGA/StateSetManipulator>
#include <osgViewer/View>

#include <iostream>

using namespace osg;
using namespace osgGA;

/*
struct GUIEventHandlerBaseWrapper : GUIEventHandler
{
    virtual bool handle1(const GUIEventAdapter* ea, GUIActionAdapter* aa, osg::Object* obj, osg::NodeVisitor* nv)
    {
        std::cout << "In Base::handle1" << std::endl;
        return GUIEventHandler::handle(*ea, *aa, obj, nv);
    }

    virtual bool handle2(const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        std::cout << "In Base::handle2" << std::endl;
        return GUIEventHandler::handle(*ea, *aa);
    }

    bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
    {
        //std::cout << "In handle1" << std::endl;
        return handle1(&ea, &aa, obj, nv);
    }

    bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
    {
        //std::cout << "In handle2" << std::endl;
        return handle2(&ea, &aa);
    }
};


struct GUIEventHandlerDerivedWrapper : GUIEventHandlerBaseWrapper, wrapper<GUIEventHandlerDerivedWrapper>
{
    //bool handle1(const GUIEventAdapter* ea, GUIActionAdapter* aa, osg::Object* obj, osg::NodeVisitor* nv)
    //{
    //    std::cout << "In Derived::handle1" << std::endl;
    //    if (boost::python::override handle1_override = this->get_override("handle1"))
    //    {
    //        std::cout << "Calling override" << std::cout;
    //        return handle1_override(ea, aa, obj, nv);
    //    }
    //    return GUIEventHandlerBaseWrapper::handle1(ea, aa, obj, nv);
    //}

    //bool default_handle1(const GUIEventAdapter* ea, GUIActionAdapter* aa, osg::Object* obj, osg::NodeVisitor* nv)
    //{
    //    std::cout << "In Derived::default_handle1" << std::endl;
    //    return GUIEventHandlerBaseWrapper::handle1(ea, aa, obj, nv);
    //}

    bool handle2(const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        std::cout << "In Derived::handle2" << std::endl;
        if (boost::python::override handle2_override = this->get_override("handle"))
        {
            std::cout << "Calling override" << std::endl;
            return handle2_override(ea, aa);
        }
        return GUIEventHandlerBaseWrapper::handle2(ea, aa);
    }

    bool default_handle2(const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        std::cout << "In Derived::default_handle2" << std::endl;
        return GUIEventHandlerBaseWrapper::handle2(ea, aa);
    }
};
*/

struct GUIEventHandler_callback : public GUIEventHandler
{
    // GUIEventHandler constructor storing initial self parameter
    GUIEventHandler_callback(PyObject *p)
        : GUIEventHandler(), self(p) {}

    // In case GUIEventHandler is returned by-value from a wrapped function
    GUIEventHandler_callback(PyObject *p, const GUIEventHandler& x)
        : GUIEventHandler(x), self(p) {}

    // Override handle to call back into Python
    bool handle(const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        std::cout << "in handle() - call_method" << std::endl;
        return call_method<bool>(self, "handle", ea, NULL);     // Can't pass aa because python wants a to_python_converter for the abstract class
    }

    bool handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
    {
        std::cout << "in handle() - calling other version" << std::endl;
        return handle(&ea, &aa);
    }

    // Supplies the default implementation of handle
    bool default_handle(GUIEventHandler& self_, const GUIEventAdapter* ea, GUIActionAdapter* aa)
    {
        std::cout << "in default_handle()" << std::endl;
        return self_.GUIEventHandler::handle(*ea, *aa);
    }

 private:
    PyObject* self;
};

BOOST_PYTHON_MODULE(_osgGA)
{

    {
        scope in_GUIEventAdapter = class_<GUIEventAdapter, bases<osg::Object>, ref_ptr<GUIEventAdapter> >("GUIEventAdapter")
            .def(init<>())
        ;

        // TODO: many enums here...
    }

    // Abstract base class for osgViewer::View
    class_<GUIActionAdapter, boost::noncopyable>("GUIActionAdapter", no_init)
    ;

    // Just so the class is wrapped for the overrides (StateSetManipulator 
    // and others in osgViewer). It should not be derived from Python.
    /*class_<GUIEventHandler, bases<osg::NodeCallback, osg::Drawable::DrawCallback>, ref_ptr<GUIEventHandler> >("placeholder_GUIEventHandler")
    ;*/

    // This is the class to derive in Python to make a new GUIEventHandler.
    class_<GUIEventHandler, GUIEventHandler_callback, bases<osg::NodeCallback, osg::Drawable::DrawCallback>, ref_ptr<GUIEventHandler> >("GUIEventHandler")
        .def(init<>())
        .def("handle", &GUIEventHandler_callback::default_handle)
        //.def("handle", &GUIEventHandlerBaseWrapper::handle2, &GUIEventHandlerDerivedWrapper::default_handle2)
        //.def("handleWithCheckAgainstIgnoreHandledEventsMask", &GUIEventHandler_handleWithCheckAgainstIgnoreHandledEventsMask1)
        //.def("handleWithCheckAgainstIgnoreHandledEventsMask", &GUIEventHandler_handleWithCheckAgainstIgnoreHandledEventsMask2)
    ;

    class_<StateSetManipulator, bases<GUIEventHandler>, ref_ptr<StateSetManipulator> >("StateSetManipulator")
        .def(init<StateSet*>())
    ;
}

#include "G:/boost_1_35_0/libs/python/test/module_tail.cpp"
