/*
* This source file is part of the osgBoostPython library
* 
* Copyright (C) 2009-2010 Jean-Sébastien Guay
* 
* This program is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License as published by the Free Software
* Foundation; either version 3 of the License, or (at your option) any later
* version.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
* http://www.gnu.org/copyleft/lesser.txt.
*/

#include "boost/python.hpp"

#include <osgDB/Options>
using namespace osg;
using namespace osgDB;
using namespace boost::python;

#include "defaults.h"

osgDB::FilePathList & (Options::*Options_getDatabasePathList1)() = & Options::getDatabasePathList;
osgDB::FilePathList const & (Options::*Options_getDatabasePathList2)() const = & Options::getDatabasePathList;
void * (Options::*Options_getPluginData3)(std::string const & s) = & Options::getPluginData;
void const * (Options::*Options_getPluginData4)(std::string const & s) const = & Options::getPluginData;
std::string & (Options::*Options_getPluginStringData5)(std::string const & s) = & Options::getPluginStringData;
std::string const (Options::*Options_getPluginStringData6)(std::string const & s) const = & Options::getPluginStringData;


void export_options() {
 
    scope in_Options = class_<Options, bases<osg::Object>, ref_ptr<Options>, boost::noncopyable >( "Options", init<>() ) 
        //.def("removePluginStringData", &Options::removePluginStringData)
        //.def("setPluginData", &Options::setPluginData)
        //.def("setPluginStringData", &Options::setPluginStringData)
        //.def("setAuthenticationMap", &Options::setAuthenticationMap)
        //.def("getDatabasePathList", Options_getDatabasePathList2)
        //.def("getDatabasePathList", Options_getDatabasePathList1)
        //.def("setFileLocationCallback", &Options::setFileLocationCallback)
        //.def("getWriteFileCallback", &Options::getWriteFileCallback)
        //.def("getFileCache", &Options::getFileCache)
        //.def("setFindFileCallback", &Options::setFindFileCallback)
        //.def("setObjectCacheHint", &Options::setObjectCacheHint)
        //.def("getPluginData", Options_getPluginData4)
        //.def("setReadFileCallback", &Options::setReadFileCallback)
        //.def("getPluginData", Options_getPluginData3)
        //.def("clone", &Options::clone)
        //.def("libraryName", &Options::libraryName)
        //.def("getFindFileCallback", &Options::getFindFileCallback)
        //.def("isSameKindAs", &Options::isSameKindAs)
        //.def("getReadFileCallback", &Options::getReadFileCallback)
        //.def("cloneType", &Options::cloneType)
        //.def("setFileCache", &Options::setFileCache)
        //.def("setWriteFileCallback", &Options::setWriteFileCallback)
        //.def("setDatabasePath", &Options::setDatabasePath)
        //.def("getBuildKdTreesHint", &Options::getBuildKdTreesHint)
        //.def("className", &Options::className)
        //.def("removePluginData", &Options::removePluginData)
        //.def("getAuthenticationMap", &Options::getAuthenticationMap)
        //.def("getOptionString", &Options::getOptionString)
        //.def("getFileLocationCallback", &Options::getFileLocationCallback)
        //.def("setOptionString", &Options::setOptionString)
        .def("setBuildKdTreesHint", &Options::setBuildKdTreesHint)
        //.def("getPluginStringData", Options_getPluginStringData6)
        //.def("getPluginStringData", Options_getPluginStringData5)
        //.def("getObjectCacheHint", &Options::getObjectCacheHint)
    ;	   
    
    enum_< osgDB::Options::BuildKdTreesHint>("BuildKdTreesHint");
        scope().attr("NO_PREFERENCE") = osgDB::Options::NO_PREFERENCE;
        scope().attr("DO_NOT_BUILD_KDTREES") = osgDB::Options::DO_NOT_BUILD_KDTREES;
        scope().attr("BUILD_KDTREES") = osgDB::Options::BUILD_KDTREES;

    enum_< osgDB::Options::CacheHintOptions>("CacheHintOptions");
        scope().attr("CACHE_NONE") = osgDB::Options::CACHE_NONE;
        scope().attr("CACHE_NODES") = osgDB::Options::CACHE_NODES;
        scope().attr("CACHE_IMAGES") = osgDB::Options::CACHE_IMAGES;
        scope().attr("CACHE_HEIGHTFIELDS") = osgDB::Options::CACHE_HEIGHTFIELDS;
        scope().attr("CACHE_ARCHIVES") = osgDB::Options::CACHE_ARCHIVES;
        scope().attr("CACHE_OBJECTS") = osgDB::Options::CACHE_OBJECTS;
        scope().attr("CACHE_SHADERS") = osgDB::Options::CACHE_SHADERS;
        scope().attr("CACHE_ALL") = osgDB::Options::CACHE_ALL;
	     
}
