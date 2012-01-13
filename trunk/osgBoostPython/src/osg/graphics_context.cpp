/**
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
#include <osg/GraphicsContext>

using namespace osg;

#include "defaults.h"

void export_GraphicsContext()
{

  {
    scope in_GraphicsContext = class_<GraphicsContext, bases<Object>, boost::noncopyable >("GraphicsContext", no_init)      
      ;
    
    class_<GraphicsContext::ScreenIdentifier>("ScreenIndentifier")
      .def( init<int>() )
      .def( init< std::string&, int, int>() )
      ;

    class_<GraphicsContext::Traits, bases<Referenced, GraphicsContext::ScreenIdentifier>, ref_ptr<GraphicsContext::Traits> >
      ("Traits", init< optional<DisplaySettings*> >() )
      .def_readwrite("x",& GraphicsContext::Traits::x )
      .def_readwrite("y",& GraphicsContext::Traits::y )
      .def_readwrite("width",& GraphicsContext::Traits::width )
      .def_readwrite("height",& GraphicsContext::Traits::height )
      .def_readwrite("windowName",& GraphicsContext::Traits::windowName )
      .def_readwrite("windowDecoration",& GraphicsContext::Traits::windowDecoration )
      .def_readwrite("supportsResize",& GraphicsContext::Traits::supportsResize )
      .def_readwrite("red",& GraphicsContext::Traits::red )
      .def_readwrite("blue",& GraphicsContext::Traits::blue )
      .def_readwrite("green",& GraphicsContext::Traits::green )
      .def_readwrite("alpha",& GraphicsContext::Traits::alpha )
      .def_readwrite("depth",& GraphicsContext::Traits::depth )
      .def_readwrite("stencil",& GraphicsContext::Traits::stencil )
      .def_readwrite("sampleBuffers",& GraphicsContext::Traits::sampleBuffers )
      .def_readwrite("samples",& GraphicsContext::Traits::samples )
      .def_readwrite("pbuffer",& GraphicsContext::Traits::pbuffer )
      .def_readwrite("quadBufferStereo",& GraphicsContext::Traits::quadBufferStereo )
      .def_readwrite("doubleBuffer",& GraphicsContext::Traits::doubleBuffer )
      .def_readwrite("target",& GraphicsContext::Traits::target )
      .def_readwrite("format",& GraphicsContext::Traits::format )
      .def_readwrite("level",& GraphicsContext::Traits::level )
      .def_readwrite("face",& GraphicsContext::Traits::face )
      .def_readwrite("mipMapGeneration",& GraphicsContext::Traits::mipMapGeneration )
      .def_readwrite("vsync",& GraphicsContext::Traits::vsync )
      .def_readwrite("swapGroupEnabled",& GraphicsContext::Traits::swapGroupEnabled )
      .def_readwrite("swapGroup",& GraphicsContext::Traits::swapGroup )
      .def_readwrite("swapBarrier",& GraphicsContext::Traits::swapBarrier )
      .def_readwrite("useMultiThreadedOpenGLEngine",& GraphicsContext::Traits::useMultiThreadedOpenGLEngine )
      .def_readwrite("useCursor",& GraphicsContext::Traits::useCursor )
      .def_readwrite("glContextVersion",& GraphicsContext::Traits::glContextVersion )
      .def_readwrite("glContextFlags",& GraphicsContext::Traits::glContextFlags )
      .def_readwrite("glContextProfileMask",& GraphicsContext::Traits::glContextProfileMask )
      .def_readwrite("sharedContext",& GraphicsContext::Traits::sharedContext )
      .def_readwrite("inheritedWindowData",& GraphicsContext::Traits::inheritedWindowData )
      .def_readwrite("setInheritedWindowPixelFormat",& GraphicsContext::Traits::setInheritedWindowPixelFormat )
      .def_readwrite("overrideRedirect",& GraphicsContext::Traits::overrideRedirect )
      .def_readwrite("swapMethod",& GraphicsContext::Traits::swapMethod )
      ;
      
  }

}
