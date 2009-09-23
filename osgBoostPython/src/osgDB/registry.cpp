#include "boost/python.hpp"

#include <osgDB/Registry>
using namespace osg;
using namespace osgDB;
using namespace boost::python;

#include "defaults.h"

std::vector<osg::ref_ptr<osgDB::ReaderWriter>, std::allocator<osg::ref_ptr<osgDB::ReaderWriter> > > & (Registry::*Registry_getReaderWriterList4)() = & Registry::getReaderWriterList;
std::vector<osg::ref_ptr<osgDB::ReaderWriter>, std::allocator<osg::ref_ptr<osgDB::ReaderWriter> > > const & (Registry::*Registry_getReaderWriterList5)() const = & Registry::getReaderWriterList;
osg::Object * (Registry::*Registry_readObjectOfType6)(osg::Object const & compObj, osgDB::Input & fr) = & Registry::readObjectOfType;
osg::Object * (Registry::*Registry_readObjectOfType7)(osgDB::basic_type_wrapper const & btw, osgDB::Input & fr) = & Registry::readObjectOfType;
osg::Object * (Registry::*Registry_readObject8)(osgDB::Input & fr) = & Registry::readObject;
osg::Image * (Registry::*Registry_readImage9)(osgDB::Input & fr) = & Registry::readImage;
osg::Node * (Registry::*Registry_readNode10)(osgDB::Input & fr) = & Registry::readNode;
osg::Shader * (Registry::*Registry_readShader11)(osgDB::Input & fr) = & Registry::readShader;
bool (Registry::*Registry_writeObject12)(osg::Object const & obj, osgDB::Output & fw) = & Registry::writeObject;
osgDB::FindFileCallback * (Registry::*Registry_getFindFileCallback13)() = & Registry::getFindFileCallback;
osgDB::FindFileCallback const * (Registry::*Registry_getFindFileCallback14)() const = & Registry::getFindFileCallback;
osgDB::ReadFileCallback * (Registry::*Registry_getReadFileCallback15)() = & Registry::getReadFileCallback;
osgDB::ReadFileCallback const * (Registry::*Registry_getReadFileCallback16)() const = & Registry::getReadFileCallback;
osgDB::ReaderWriter::ReadResult (Registry::*Registry_readObject17)(std::string const & fileName, osgDB::Options const * options, bool buildKdTreeIfRequired) = & Registry::readObject;
osgDB::ReaderWriter::ReadResult (Registry::*Registry_readImage18)(std::string const & fileName, osgDB::Options const * options) = & Registry::readImage;
osgDB::ReaderWriter::ReadResult (Registry::*Registry_readNode19)(std::string const & fileName, osgDB::Options const * options, bool buildKdTreeIfRequired) = & Registry::readNode;
osgDB::ReaderWriter::ReadResult (Registry::*Registry_readShader20)(std::string const & fileName, osgDB::Options const * options) = & Registry::readShader;
osgDB::WriteFileCallback * (Registry::*Registry_getWriteFileCallback21)() = & Registry::getWriteFileCallback;
osgDB::WriteFileCallback const * (Registry::*Registry_getWriteFileCallback22)() const = & Registry::getWriteFileCallback;
osgDB::ReaderWriter::WriteResult (Registry::*Registry_writeObject23)(osg::Object const & obj, std::string const & fileName, osgDB::Options const * options) = & Registry::writeObject;
osgDB::FileCache * (Registry::*Registry_getFileCache24)() = & Registry::getFileCache;
osgDB::FileCache const * (Registry::*Registry_getFileCache25)() const = & Registry::getFileCache;
osgDB::AuthenticationMap * (Registry::*Registry_getAuthenticationMap26)() = & Registry::getAuthenticationMap;
osgDB::AuthenticationMap const * (Registry::*Registry_getAuthenticationMap27)() const = & Registry::getAuthenticationMap;
osgDB::Options * (Registry::*Registry_getOptions28)() = & Registry::getOptions;
osgDB::Options const * (Registry::*Registry_getOptions29)() const = & Registry::getOptions;
void (Registry::*Registry_setDataFilePathList30)(osgDB::FilePathList const & filepath) = & Registry::setDataFilePathList;
void (Registry::*Registry_setDataFilePathList31)(std::string const & paths) = & Registry::setDataFilePathList;
osgDB::FilePathList & (Registry::*Registry_getDataFilePathList32)() = & Registry::getDataFilePathList;
osgDB::FilePathList const & (Registry::*Registry_getDataFilePathList33)() const = & Registry::getDataFilePathList;
void (Registry::*Registry_setLibraryFilePathList34)(osgDB::FilePathList const & filepath) = & Registry::setLibraryFilePathList;
void (Registry::*Registry_setLibraryFilePathList35)(std::string const & paths) = & Registry::setLibraryFilePathList;
osgDB::FilePathList & (Registry::*Registry_getLibraryFilePathList36)() = & Registry::getLibraryFilePathList;
osgDB::FilePathList const & (Registry::*Registry_getLibraryFilePathList37)() const = & Registry::getLibraryFilePathList;
// bool (ReadFunctor::*ReadFunctor_isValid39)(osgDB::ReaderWriter::ReadResult & readResult) = & ReadFunctor::isValid;
// bool (ReadFunctor::*ReadFunctor_isValid40)(osg::Object * object) = & ReadFunctor::isValid;


void export_registry() {
 
    class_<Registry, bases<osg::Referenced>, ref_ptr<Registry>, boost::noncopyable >( "Registry", no_init ) 
        //.def("writeObjectImplementation", &Registry::writeObjectImplementation)
        //.def("clearObjectCache", &Registry::clearObjectCache)
        //.def("getFromObjectCache", &Registry::getFromObjectCache)
        //.def("getLibrary", &Registry::getLibrary)
        //.def("writeObject", Registry_writeObject23)
        //.def("getLibraryFilePathList", Registry_getLibraryFilePathList36)
        //.def("getLibraryFilePathList", Registry_getLibraryFilePathList37)
        //.def("findLibraryFileImplementation", &Registry::findLibraryFileImplementation)
        //.def("initFilePathLists", &Registry::initFilePathLists)
        //.def("getCreateNodeFromImage", &Registry::getCreateNodeFromImage)
        //.def("addDotOsgWrapper", &Registry::addDotOsgWrapper)
        //.def("addArchiveExtension", &Registry::addArchiveExtension)
        //.def("getFileCache", Registry_getFileCache25)
        //.def("getFileCache", Registry_getFileCache24)
        //.def("initDataFilePathList", &Registry::initDataFilePathList)
        //.def("findDataFileImplementation", &Registry::findDataFileImplementation)
        //.def("isValid", ReadFunctor_isValid39)
        //.def("readObject", Registry_readObject17)
        //.def("setFileLocationCallback", &Registry::setFileLocationCallback)
        //.def("_buildKdTreeIfRequired", &Registry::_buildKdTreeIfRequired)
        //.def("readObjectImplementation", &Registry::readObjectImplementation)
        //.def("addToArchiveCache", &Registry::addToArchiveCache)
        //.def("readImageImplementation", &Registry::readImageImplementation)
        //.def("getReaderWriterList", Registry_getReaderWriterList5)
        //.def("getReaderWriterList", Registry_getReaderWriterList4)
        //.def("removeReaderWriter", &Registry::removeReaderWriter)
        //.def("removeExpiredObjectsInCache", &Registry::removeExpiredObjectsInCache)
        //.def("setSharedStateManager", &Registry::setSharedStateManager)
        //.def("isProtocolRegistered", &Registry::isProtocolRegistered)
        //.def("getOrCreateSharedStateManager", &Registry::getOrCreateSharedStateManager)
        //.def("releaseGLObjects", &Registry::releaseGLObjects)
        //.def("findDataFile", &Registry::findDataFile)
        .def("getBuildKdTreesHint", &Registry::getBuildKdTreesHint)
        //.def("setOptions", &Registry::setOptions)
        //.def("readNode", Registry_readNode19)
        //.def("getDataFilePathList", Registry_getDataFilePathList32)
        //.def("getReadFileCallback", Registry_getReadFileCallback16)
        //.def("getFindFileCallback", Registry_getFindFileCallback14)
        //.def("getFindFileCallback", Registry_getFindFileCallback13)
        //.def("operator=", basic_type_wrapper_operator=1)
        //.def("writeImageImplementation", &Registry::writeImageImplementation)
        //.def("getAuthenticationMap", Registry_getAuthenticationMap27)
        //.def("getAuthenticationMap", Registry_getAuthenticationMap26)
        //.def("getOptions", Registry_getOptions29)
        //.def("getOptions", Registry_getOptions28)
        //.def("readObject", Registry_readObject8)
        //.def("setFindFileCallback", &Registry::setFindFileCallback)
        //.def("setWriteFileCallback", &Registry::setWriteFileCallback)
        //.def("addEntryToObjectCache", &Registry::addEntryToObjectCache)
        //.def("removeDotOsgWrapper", &Registry::removeDotOsgWrapper)
        //.def("registerProtocol", &Registry::registerProtocol)
        //.def("operator=", PluginFunctionProxy_operator=3)
        //.def("getReaderWriterForExtension", &Registry::getReaderWriterForExtension)
        //.def("createLibraryNameForFile", &Registry::createLibraryNameForFile)
        //.def("getWriteFileCallback", Registry_getWriteFileCallback22)
        //.def("getWriteFileCallback", Registry_getWriteFileCallback21)
        //.def("readObjectOfType", Registry_readObjectOfType6)
        //.def("readObjectOfType", Registry_readObjectOfType7)
        //.def("getFromArchiveCache", &Registry::getFromArchiveCache)
        //.def("loadLibrary", &Registry::loadLibrary)
        //.def("getSharedStateManager", &Registry::getSharedStateManager)
        //.def("getFileLocationCallback", &Registry::getFileLocationCallback)
        //.def("removeFromArchiveCache", &Registry::removeFromArchiveCache)
        //.def("readDrawable", &Registry::readDrawable)
        //.def("setCreateNodeFromImage", &Registry::setCreateNodeFromImage)
        //.def("getKdTreeBuilder", &Registry::getKdTreeBuilder)
        .def("setBuildKdTreesHint", &Registry::setBuildKdTreesHint)
        //.def("writeImage", &Registry::writeImage)
        //.def("setLibraryFilePathList", Registry_setLibraryFilePathList34)
        //.def("setLibraryFilePathList", Registry_setLibraryFilePathList35)
        //.def("readShader", Registry_readShader11)
        //.def("initLibraryFilePathList", &Registry::initLibraryFilePathList)
        //.def("readStateAttribute", &Registry::readStateAttribute)
        //.def("openArchiveImplementation", &Registry::openArchiveImplementation)
        //.def("doRead", &ReadFunctor::doRead)
        //.def("readPluginAliasConfigurationFile", &Registry::readPluginAliasConfigurationFile)
        //.def("createLibraryNameForNodeKit", &Registry::createLibraryNameForNodeKit)
        //.def("closeAllLibraries", &Registry::closeAllLibraries)
        //.def("writeNode", &Registry::writeNode)
        //.def("addMimeTypeExtensionMapping", &Registry::addMimeTypeExtensionMapping)
        //.def("operator=", ReadFunctor_operator=38)
        //.def("setReadFileCallback", &Registry::setReadFileCallback)
        //.def("readCommandLine", &Registry::readCommandLine)
        //.def("findLibraryFile", &Registry::findLibraryFile)
        //.def("writeHeightFieldImplementation", &Registry::writeHeightFieldImplementation)
        //.def("readShaderImplementation", &Registry::readShaderImplementation)
        //.def("writeHeightField", &Registry::writeHeightField)
        //.def("addReaderWriter", &Registry::addReaderWriter)
        //.def("getDataFilePathList", Registry_getDataFilePathList33)
        //.def("createLibraryNameForExtension", &Registry::createLibraryNameForExtension)
        //.def("readShader", Registry_readShader20)
        //.def("setAuthenticationMap", &Registry::setAuthenticationMap)
        //.def("instance", &Registry::instance)
        //.def("readHeightField", &Registry::readHeightField)
        //.def("readNode", Registry_readNode10)
        //.def("writeObject", Registry_writeObject12)
        //.def("operator=", RegisterDotOsgWrapperProxy_operator=2)
        //.def("getReadFileCallback", Registry_getReadFileCallback15)
        //.def("readImage", Registry_readImage18)
        //.def("readNodeImplementation", &Registry::readNodeImplementation)
        //.def("updateTimeStampOfObjectsInCacheWithExternalReferences", &Registry::updateTimeStampOfObjectsInCacheWithExternalReferences)
        //.def("clearArchiveCache", &Registry::clearArchiveCache)
        //.def("setDataFilePathList", Registry_setDataFilePathList30)
        //.def("setDataFilePathList", Registry_setDataFilePathList31)
        //.def("readImage", Registry_readImage9)
        //.def("setKdTreeBuilder", &Registry::setKdTreeBuilder)
        //.def("addFileExtensionAlias", &Registry::addFileExtensionAlias)
        //.def("getReaderWriterForMimeType", &Registry::getReaderWriterForMimeType)
        //.def("matches", &basic_type_wrapper::matches)
        //.def("writeShaderImplementation", &Registry::writeShaderImplementation)
        //.def("writeNodeImplementation", &Registry::writeNodeImplementation)
        //.def("readUniform", &Registry::readUniform)
        //.def("setFileCache", &Registry::setFileCache)
        //.def("isValid", ReadFunctor_isValid40)
        //.def("openArchive", &Registry::openArchive)
        //.def("readHeightFieldImplementation", &Registry::readHeightFieldImplementation)
        //.def("closeLibrary", &Registry::closeLibrary)
        //.def("writeShader", &Registry::writeShader)
	;
}
