#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osg/NodeCallback>

using namespace osg;

void export_util()
{
    class_<NodeCallback, bases<Object>, ref_ptr<NodeCallback> >("NodeCallback")
    ;


}
