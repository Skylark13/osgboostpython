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

#include <osgViewer/CompositeViewer>

using namespace osg;
using namespace osgViewer;

#include "defaults.h"

const osgViewer::View*(CompositeViewer::* get_view)( unsigned ) const = &CompositeViewer::getView;

void export_CompositeViewer()
{

  class_<CompositeViewer, 
    bases<osgViewer::ViewerBase>, 
    ref_ptr<CompositeViewer> >("CompositeViewer")    
    .def("addView", &CompositeViewer::addView)
    .def("removeView", &CompositeViewer::removeView)
    .def("getView", get_view, osgBoostPython::default_pointer_policy() )
    .def("getNumViews", &CompositeViewer::getNumViews)
    .def("run", &CompositeViewer::run )
    ;

}
