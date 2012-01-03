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

#include <boost/python.hpp>

using namespace boost::python;

#include <osgDB/ReadFile>
using namespace osgDB;

#include "defaults.h"

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

void export_ReadFile()
{
    def("readNodeFile", readNodeFileWrapper);
    def("readImageFile", readImageFileWrapper);
    def("readShaderFile", readShaderFileWrapper);
}
