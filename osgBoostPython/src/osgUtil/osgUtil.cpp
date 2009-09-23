#include <boost/python.hpp>
using namespace boost::python;

void export_linesegmentintersector();
void export_intersector();
void export_intersectorgroup();
void export_intersectionvisitor();

BOOST_PYTHON_MODULE(_osgUtil)
{
    export_intersector();
    export_intersectorgroup();	
    export_linesegmentintersector();
    export_intersectionvisitor();
}
