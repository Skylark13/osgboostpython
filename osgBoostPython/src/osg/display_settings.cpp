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

#include <osg/ref_ptr>
#include <osg/DisplaySettings>

using namespace osg;
#include "defaults.h"

static ref_ptr<DisplaySettings> getDisplaySettings() {
    return ref_ptr<DisplaySettings>(DisplaySettings::instance());
}

void export_DisplaySettings()
{
    class_<DisplaySettings, bases<Referenced>, ref_ptr<DisplaySettings>, boost::noncopyable>("DisplaySettings", no_init)
        //.def("setSplitStereoVerticalEyeMapping", &DisplaySettings::setSplitStereoVerticalEyeMapping)
        //.def("setScreenWidth", &DisplaySettings::setScreenWidth)
        //.def("getAlphaBuffer", &DisplaySettings::getAlphaBuffer)
        //.def("getEyeSeparation", &DisplaySettings::getEyeSeparation)
        //.def("setSplitStereoAutoAdjustAspectRatio", &DisplaySettings::setSplitStereoAutoAdjustAspectRatio)
        //.def("setDefaults", &DisplaySettings::setDefaults)
        //.def("setMinimumNumAlphaBits", &DisplaySettings::setMinimumNumAlphaBits)
        //.def("getScreenHeight", &DisplaySettings::getScreenHeight)
        //.def("getNumOfHttpDatabaseThreadsHint", &DisplaySettings::getNumOfHttpDatabaseThreadsHint)
        //.def("setDepthBuffer", &DisplaySettings::setDepthBuffer)
        //.def("getSplitStereoHorizontalEyeMapping", &DisplaySettings::getSplitStereoHorizontalEyeMapping)
        //.def("setDisplayType", &DisplaySettings::setDisplayType)
        //.def("getMinimumNumAccumAlphaBits", &DisplaySettings::getMinimumNumAccumAlphaBits)
        //.def("setSplitStereoHorizontalSeparation", &DisplaySettings::setSplitStereoHorizontalSeparation)
        //.def("getNumOfDatabaseThreadsHint", &DisplaySettings::getNumOfDatabaseThreadsHint)
        //.def("getSplitStereoAutoAdjustAspectRatio", &DisplaySettings::getSplitStereoAutoAdjustAspectRatio)
        //.def("getDepthBuffer", &DisplaySettings::getDepthBuffer)
        //.def("setSplitStereoVerticalSeparation", &DisplaySettings::setSplitStereoVerticalSeparation)
        //.def("getMinimumNumAccumRedBits", &DisplaySettings::getMinimumNumAccumRedBits)
        //.def("setApplication", &DisplaySettings::setApplication)
        //.def("getSplitStereoVerticalSeparation", &DisplaySettings::getSplitStereoVerticalSeparation)
        .def("getMinimumNumAlphaBits", &DisplaySettings::getMinimumNumAlphaBits)
        .def("getMinimumNumStencilBits", &DisplaySettings::getMinimumNumStencilBits)
        //.def("setMaxNumberOfGraphicsContexts", &DisplaySettings::setMaxNumberOfGraphicsContexts)
        //.def("getStereoMode", &DisplaySettings::getStereoMode)
        //.def("getDisplayType", &DisplaySettings::getDisplayType)
        //.def("setDisplaySettings", &DisplaySettings::setDisplaySettings)
        //.def("getSplitStereoHorizontalSeparation", &DisplaySettings::getSplitStereoHorizontalSeparation)
        //.def("readEnvironmentalVariables", &DisplaySettings::readEnvironmentalVariables)
        //.def("getMinimumNumAccumBlueBits", &DisplaySettings::getMinimumNumAccumBlueBits)
        //.def("merge", &DisplaySettings::merge)
        .def("getNumMultiSamples", &DisplaySettings::getNumMultiSamples)
        //.def("setNumOfHttpDatabaseThreadsHint", &DisplaySettings::setNumOfHttpDatabaseThreadsHint)
        //.def("getStereo", &DisplaySettings::getStereo)
        //.def("setStereo", &DisplaySettings::setStereo)
        .def("getMultiSamples", &DisplaySettings::getMultiSamples)
        //.def("setScreenDistance", &DisplaySettings::setScreenDistance)
        //.def("setStereoMode", &DisplaySettings::setStereoMode)
        //.def("setDoubleBuffer", &DisplaySettings::setDoubleBuffer)
        //.def("getSplitStereoVerticalEyeMapping", &DisplaySettings::getSplitStereoVerticalEyeMapping)
        //.def("setCompileContextsHint", &DisplaySettings::setCompileContextsHint)
        //.def("getScreenWidth", &DisplaySettings::getScreenWidth)
        //.def("setEyeSeparation", &DisplaySettings::setEyeSeparation)
        //.def("getStencilBuffer", &DisplaySettings::getStencilBuffer)
        //.def("setRGB", &DisplaySettings::setRGB)
        //.def("getSerializeDrawDispatch", &DisplaySettings::getSerializeDrawDispatch)
        //.def("setSplitStereoHorizontalEyeMapping", &DisplaySettings::setSplitStereoHorizontalEyeMapping)
        //.def("getScreenDistance", &DisplaySettings::getScreenDistance)
        .def("instance", &DisplaySettings::instance, osgBoostPython::default_pointer_policy())
        //.def("getAccumBuffer", &DisplaySettings::getAccumBuffer)
        //.def("readCommandLine", &DisplaySettings::readCommandLine)
        //.def("getMinimumNumAccumGreenBits", &DisplaySettings::getMinimumNumAccumGreenBits)
        //.def("getApplication", &DisplaySettings::getApplication)
        //.def("setMinimumNumAccumBits", &DisplaySettings::setMinimumNumAccumBits)
        //.def("setSerializeDrawDispatch", &DisplaySettings::setSerializeDrawDispatch)
        //.def("getCompileContextsHint", &DisplaySettings::getCompileContextsHint)
        //.def("getDoubleBuffer", &DisplaySettings::getDoubleBuffer)
        //.def("setNumOfDatabaseThreadsHint", &DisplaySettings::setNumOfDatabaseThreadsHint)
        //.def("setScreenHeight", &DisplaySettings::setScreenHeight)
        //.def("getRGB", &DisplaySettings::getRGB)
        //.def("setNumMultiSamples", &DisplaySettings::setNumMultiSamples)
        .def("setMinimumNumStencilBits", &DisplaySettings::setMinimumNumStencilBits)
        //.def("getMaxNumberOfGraphicsContexts", &DisplaySettings::getMaxNumberOfGraphicsContexts)
    ;

    // this needs to come last so it replaces the constructor
    def("DisplaySettings", &getDisplaySettings);

}
