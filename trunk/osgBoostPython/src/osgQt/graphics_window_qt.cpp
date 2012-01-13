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

#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerBase>
#include <osgQt/GraphicsWindowQt>
using namespace osg;
using namespace osgViewer;
using namespace osgQt;

#include <QtGui/QInputEvent>
#include <QtOpenGL/QGLWidget>

#include "defaults.h"

void export_GraphicsWindowQt()
{

  def("setViewer", &osgQt::setViewer );
  def("initQtWindowingSystem", &osgQt::initQtWindowingSystem );
  
  const GraphicsWindowQt*(GLWidget::* get_graphics_window)() const = &GLWidget::getGraphicsWindow;
  class_<GLWidget, bases<QGLWidget>, boost::noncopyable >
    ("GLWidget")
    .def( init< optional< QWidget*, const QGLWidget*, Qt::WindowFlags, bool > >() )
    .def( init< QGLContext*, optional< QWidget*, const QGLWidget*, Qt::WindowFlags, bool > >() )
    .def( init< const QGLFormat&, optional< QWidget*, const QGLWidget*, Qt::WindowFlags, bool > >() )
    .add_property( "graphicsWindow", make_function( get_graphics_window, osgBoostPython::default_pointer_policy() ),
		   &GLWidget::setGraphicsWindow )
    .add_property("forwardKeyEvents", &GLWidget::getForwardKeyEvents, &GLWidget::setForwardKeyEvents )
    .def("setKeyboardModifiers", &GLWidget::setKeyboardModifiers )
    .def("keyPressEvent", &GLWidget::keyPressEvent )
    .def("keyReleaseEvent", &GLWidget::keyReleaseEvent )
    .def("mousePressEvent", &GLWidget::mousePressEvent )
    .def("mouseReleaseEvent", &GLWidget::mouseReleaseEvent )
    .def("mouseDoubleClickEvent", &GLWidget::mouseDoubleClickEvent )
    .def("mouseMoveEvent", &GLWidget::mouseMoveEvent )
    .def("wheelEvent", &GLWidget::wheelEvent )
    ;

  const GLWidget*(GraphicsWindowQt::* get_gl_widget)() const = &GraphicsWindowQt::getGLWidget;
  scope in_GraphicsWindowQt = class_<GraphicsWindowQt, ref_ptr<GraphicsWindowQt>, 
    bases<GraphicsWindow>, boost::noncopyable > 
    ("GraphicsWindowQt", init<GLWidget*>() )
    .def( init<GraphicsContext::Traits*, optional<QWidget*, const QGLWidget*, Qt::WindowFlags > >() )
    .add_property("glWidget", make_function(get_gl_widget, osgBoostPython::default_pointer_policy() ) )
    .def("init", &GraphicsWindowQt::init )
    .def("setWindowRectangleImplementation", &GraphicsWindowQt::setWindowRectangleImplementation )
    .def("getWindowRectangle", &GraphicsWindowQt::getWindowRectangle )
    .def("setWindowDecorationImplementation", &GraphicsWindowQt::setWindowDecorationImplementation )
    .def("getWindowDecoration", &GraphicsWindowQt::getWindowDecoration )
    .def("grabFocus", &GraphicsWindowQt::grabFocus )
    .def("grabFocusIfPointerInWindow", &GraphicsWindowQt::grabFocusIfPointerInWindow )
    .def("raiseWindow", &GraphicsWindowQt::raiseWindow )
    .def("setWindowName", &GraphicsWindowQt::setWindowName )
    .def("getWindowName", &GraphicsWindowQt::getWindowName )
    .def("useCursor", &GraphicsWindowQt::useCursor )
    .def("setCursor", &GraphicsWindowQt::setCursor )
    .def("valid", &GraphicsWindowQt::valid )
    .def("realizeImplementation", &GraphicsWindowQt::realizeImplementation )
    .def("isRealizedImplementation", &GraphicsWindowQt::isRealizedImplementation )
    .def("closeImplementation", &GraphicsWindowQt::closeImplementation )
    .def("makeCurrentImplementation", &GraphicsWindowQt::makeCurrentImplementation )
    .def("releaseContextImplementation", &GraphicsWindowQt::releaseContextImplementation )
    .def("swapBuffersImplementation", &GraphicsWindowQt::swapBuffersImplementation )
    .def("requestWarpPointer", &GraphicsWindowQt::requestWarpPointer )
    ;    

  class_<GraphicsWindowQt::WindowData, bases<Referenced>, ref_ptr<GraphicsWindowQt::WindowData> >
    ("WindowData", init< optional< GLWidget*, GLWidget* > >() )    
    .def_readwrite("widget", &GraphicsWindowQt::WindowData::_widget )
    .def_readwrite("parent", &GraphicsWindowQt::WindowData::_parent )
    ;
}
