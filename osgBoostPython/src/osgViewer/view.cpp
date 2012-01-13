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

#include <osgViewer/View>

using namespace osg;
using namespace osgViewer;

#include "defaults.h" 

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(osgView_setUpViewInWindow_overloads, setUpViewInWindow, 4, 5)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(osgView_setUpViewOnSingleScreen_overloads, setUpViewOnSingleScreen, 0, 1)

void export_View()
{

  // TODO: Wrap osgViewer::View at least, then osgViewer::ViewerBase and osgViewer::CompositeViewer.
  class_<osgViewer::View, bases<osg::View, osgGA::GUIActionAdapter>, ref_ptr<osgViewer::View> >("View")
    .def("setUpViewAcrossAllScreens", &osgViewer::View::setUpViewAcrossAllScreens)
    .def("setUpViewInWindow", &osgViewer::View::setUpViewInWindow, osgView_setUpViewInWindow_overloads())
    .def("setUpViewOnSingleScreen", &osgViewer::View::setUpViewOnSingleScreen, osgView_setUpViewOnSingleScreen_overloads())
    .def("setSceneData", &osgViewer::View::setSceneData )
    .def("addEventHandler", &osgViewer::View::addEventHandler )
    .def("setCameraManipulator", &osgViewer::View::setCameraManipulator )
    ;

}
