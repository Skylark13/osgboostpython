/*
* This source file is part of the osgBoostPython library
* 
* Copyright (C) 2009-2010 Jean-S�bastien Guay
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

#include <osg/ref_ptr>
#include <osg/FrameStamp>
using namespace osg;

#include "defaults.h"

void export_FrameStamp() {
    class_<FrameStamp, ref_ptr<FrameStamp> >("FrameStamp")
        .def("getFrameNumber", &FrameStamp::getFrameNumber)
        .def("getReferenceTime", &FrameStamp::getReferenceTime)
        .def("getSimulationTime", &FrameStamp::getSimulationTime)
    ;
}
