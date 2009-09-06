#include <boost/python.hpp>

using namespace boost::python;

#define WIN32

#include <osgDB/ReadFile>

using namespace osgDB;

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

// Boost.Python and Smart Pointers
// http://wiki.python.org/moin/boost.python/PointersAndSmartPointers
// http://www.language-binding.net/pyplusplus/troubleshooting_guide/smart_ptrs/smart_ptrs.html
BOOST_PYTHON_MODULE(_osgDB)
{
    def("readNodeFile", readNodeFileWrapper);
    def("readImageFile", readImageFileWrapper);
    def("readShaderFile", readShaderFileWrapper);
}