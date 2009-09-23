#include <boost/python.hpp>

using namespace boost::python;

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgDB/Registry>

class Node;

using namespace osgDB;

#include "defaults.h"

void export_registry();
void export_options();

osg::ref_ptr<osg::Node> readNodeFileWrapper(const std::string& filename)
{
    return osg::ref_ptr<osg::Node>(osgDB::readNodeFile(filename));
}

osg::ref_ptr<osg::Image> readImageFileWrapper(const std::string& filename)
{
    return osg::ref_ptr<osg::Image>(osgDB::readImageFile(filename));
}

osg::ref_ptr<osg::Shader> readShaderFileWrapper(const std::string& filename)
{
    return osg::ref_ptr<osg::Shader>(osgDB::readShaderFile(filename));
}

bool writeNodeFileWrapper(const osg::Node* node, const std::string& filename)
{
    return osgDB::writeNodeFile(*node, filename,Registry::instance()->getOptions());
}

static osg::ref_ptr<osgDB::Registry> getRegistry() {
    return osg::ref_ptr<osgDB::Registry>(osgDB::Registry::instance());
}


// Boost.Python and Smart Pointers
// http://wiki.python.org/moin/boost.python/PointersAndSmartPointers
// http://www.language-binding.net/pyplusplus/troubleshooting_guide/smart_ptrs/smart_ptrs.html
BOOST_PYTHON_MODULE(_osgDB)
{
    def("readNodeFile", readNodeFileWrapper);
    def("readImageFile", readImageFileWrapper);
    def("readShaderFile", readShaderFileWrapper);
    def("writeNodeFile", writeNodeFileWrapper);
    
    export_options();
    export_registry();
    def("Registry", &getRegistry);
}
