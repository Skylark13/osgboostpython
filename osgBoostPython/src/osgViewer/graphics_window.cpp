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
#include <osgViewer/GraphicsWindow>

#include "defaults.h" 

const osgGA::EventQueue* (osgViewer::GraphicsWindow::* get_event_queue)() const = &osgViewer::GraphicsWindow::getEventQueue;

void export_GraphicsWindow()
{
  
  // TODO: osgViewer::CompositeViewer.
  {
    scope in_GraphicsWindow = class_<osgViewer::GraphicsWindow, 
      bases<osg::GraphicsContext, osgGA::GUIActionAdapter > , 
      osg::ref_ptr<osgViewer::GraphicsWindow>, boost::noncopyable >("GraphicsWindow")
      .add_property("eventQueue", make_function( get_event_queue, osgBoostPython::default_pointer_policy() ),
		    &osgViewer::GraphicsWindow::setEventQueue );
    ;
    
    enum_<osgViewer::GraphicsWindow::MouseCursor>("MouseCursor");
    scope().attr("InheritCursor") = osgViewer::GraphicsWindow::InheritCursor ;
    scope().attr("NoCursor") = osgViewer::GraphicsWindow::NoCursor ;
    scope().attr("RightArrowCursor") = osgViewer::GraphicsWindow::RightArrowCursor ;
    scope().attr("LeftArrowCursor") = osgViewer::GraphicsWindow::LeftArrowCursor ;
    scope().attr("InfoCursor") = osgViewer::GraphicsWindow::InfoCursor ;
    scope().attr("DestroyCursor") = osgViewer::GraphicsWindow::DestroyCursor ;
    scope().attr("HelpCursor") = osgViewer::GraphicsWindow::HelpCursor ;
    scope().attr("CycleCursor") = osgViewer::GraphicsWindow::CycleCursor ;
    scope().attr("SprayCursor") = osgViewer::GraphicsWindow::SprayCursor ;
    scope().attr("WaitCursor") = osgViewer::GraphicsWindow::WaitCursor ;
    scope().attr("TextCursor") = osgViewer::GraphicsWindow::TextCursor ;
    scope().attr("CrosshairCursor") = osgViewer::GraphicsWindow::CrosshairCursor ;
    scope().attr("HandCursor") = osgViewer::GraphicsWindow::HandCursor ;
    scope().attr("UpDownCursor") = osgViewer::GraphicsWindow::UpDownCursor ;
    scope().attr("LeftRightCursor") = osgViewer::GraphicsWindow::LeftRightCursor ;
    scope().attr("TopSideCursor") = osgViewer::GraphicsWindow::TopSideCursor ;
    scope().attr("BottomSideCursor") = osgViewer::GraphicsWindow::BottomSideCursor;
    scope().attr("LeftSideCursor") = osgViewer::GraphicsWindow::LeftSideCursor ;
    scope().attr("RightSideCursor") = osgViewer::GraphicsWindow::RightSideCursor ;
    scope().attr("TopLeftCorner") = osgViewer::GraphicsWindow::TopLeftCorner ;
    scope().attr("TopRightCorner") = osgViewer::GraphicsWindow::TopRightCorner ;
    scope().attr("BottomRightCorner") = osgViewer::GraphicsWindow::BottomRightCorner ;
    scope().attr("BottomLeftCorner") = osgViewer::GraphicsWindow::BottomLeftCorner ;
   
  }

  class_<osgViewer::GraphicsWindowEmbedded, boost::noncopyable>
    ("GraphicsWindowEmbedded", init< optional<osg::GraphicsContext::Traits*> >() )
    .def( init<int, int, int, int>() )
    .def("init", &osgViewer::GraphicsWindowEmbedded::init )
    ;

}
