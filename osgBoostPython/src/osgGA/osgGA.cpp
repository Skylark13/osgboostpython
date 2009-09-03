#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osgGA/GUIEventHandler>
#include <osgGA/StateSetManipulator>

using namespace osg;
using namespace osgGA;

BOOST_PYTHON_MODULE(_osgGA)
{
    class_<GUIEventHandler, bases<osg::NodeCallback, osg::Drawable::DrawCallback>, ref_ptr<GUIEventHandler> >("GUIEventHandler")
    ;

    class_<StateSetManipulator, bases<GUIEventHandler>, ref_ptr<StateSetManipulator> >("StateSetManipulator")
        .def(init<StateSet*>())
    ;
}
