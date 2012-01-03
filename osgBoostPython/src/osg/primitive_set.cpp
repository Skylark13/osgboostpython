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
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#include <osg/State>
#include <osg/PrimitiveSet>
using namespace osg;

#include "defaults.h"

void export_PrimitiveSet()
{
  {
    scope in_PrimitiveSet = class_<PrimitiveSet, bases<Object>, ref_ptr<PrimitiveSet>, boost::noncopyable >
      ("PrimitiveSet", no_init)
      ;
    
    enum_<PrimitiveSet::Type>("Type");
    scope().attr("PrimitiveType") =                   PrimitiveSet::PrimitiveType;
    scope().attr("DrawArraysPrimitiveType") =         PrimitiveSet::DrawArraysPrimitiveType;
    scope().attr("DrawArrayLengthsPrimitiveType") =   PrimitiveSet::DrawArrayLengthsPrimitiveType;
    scope().attr("DrawElementsUBytePrimitiveType") =  PrimitiveSet::DrawElementsUBytePrimitiveType;
    scope().attr("DrawElementsUShortPrimitiveType") = PrimitiveSet::DrawElementsUShortPrimitiveType;
    scope().attr("DrawElementsUIntPrimitiveType") =   PrimitiveSet::DrawElementsUIntPrimitiveType;
    
    enum_<PrimitiveSet::Mode>("Mode");
    scope().attr("POINTS") =         PrimitiveSet::POINTS;
    scope().attr("LINES") =          PrimitiveSet::LINES;
    scope().attr("LINE_STRIP") =     PrimitiveSet::LINE_STRIP;
    scope().attr("LINE_LOOP") =      PrimitiveSet::LINE_LOOP;
    scope().attr("TRIANGLES") =      PrimitiveSet::TRIANGLES;
    scope().attr("TRIANGLE_STRIP") = PrimitiveSet::TRIANGLE_STRIP;
    scope().attr("TRIANGLE_FAN") =   PrimitiveSet::TRIANGLE_FAN;
    scope().attr("QUADS") =          PrimitiveSet::QUADS;
    scope().attr("QUAD_STRIP") =     PrimitiveSet::QUAD_STRIP;
    scope().attr("POLYGON") =        PrimitiveSet::POLYGON;       
  }

  // DrawArrays
  {
    class_<DrawArrays, bases<PrimitiveSet>, ref_ptr<DrawArrays> >("DrawArrays")
      .def(init<PrimitiveSet::Mode>())
      .def(init<PrimitiveSet::Mode, GLint, GLsizei>())
      ;
  }
  
  // DrawElements
  {
    class_<DrawElements, bases<PrimitiveSet>, ref_ptr<DrawElements>, boost::noncopyable >
      ("DrawElements", no_init );        
  }
  
  {   
    class_<VectorGLuint>("VectorGLuint")
      .def(vector_indexing_suite<VectorGLuint>() );
    class_<VectorGLubyte>("VectorGLubyte")
      .def(vector_indexing_suite<VectorGLubyte>() );
    class_<VectorGLushort>("VectorGLushort")
      .def(vector_indexing_suite<VectorGLushort>() );
    class_<VectorGLsizei>("VectorGLsizei")
      .def(vector_indexing_suite<VectorGLsizei>() );
  }
  
  // DrawElementsUByte
  {
    void(DrawElementsUByte::*accept_pf)(PrimitiveFunctor&) const = &DrawElementsUByte::accept;
    void(DrawElementsUByte::*accept_pif)(PrimitiveIndexFunctor&) const = &DrawElementsUByte::accept;
    
    class_<DrawElementsUByte, bases<DrawElements,VectorGLubyte>, ref_ptr<DrawElementsUByte> >
      ("DrawElementsUByte")
      .def( init<GLenum>() )
      .def( init<GLenum, unsigned int, GLubyte*, int>() )
      .def( init<GLenum, unsigned int>() )
      //.def( "getData", &DrawElementsUByte::getDataPointer, osgBoostPython::default_pointer_policy() )
      .def("getTotalDataSize", &DrawElementsUByte::getTotalDataSize )
      .def("supportsBufferObject", &DrawElementsUByte::supportsBufferObject )
      .def("draw", &DrawElementsUByte::draw )
      .def("accept", accept_pf )
      .def("accept", accept_pif )
      .def("getNumIndices", &DrawElementsUByte::getNumIndices )
      .def("index", &DrawElementsUByte::index )
      .def("offsetIndices", &DrawElementsUByte::offsetIndices )
      .def("reserveElements", &DrawElementsUByte::reserveElements )
      .def("setElement", &DrawElementsUByte::setElement )
      .def("getElement", &DrawElementsUByte::getElement )
      .def("addElement", &DrawElementsUByte::addElement )
      ;
  } 
  
  // DrawElementsUShort
  {
    void(DrawElementsUShort::*accept_pf)(PrimitiveFunctor&) const = &DrawElementsUShort::accept;
    void(DrawElementsUShort::*accept_pif)(PrimitiveIndexFunctor&) const = &DrawElementsUShort::accept;
    
    class_<DrawElementsUShort, bases<DrawElements,VectorGLushort>, ref_ptr<DrawElementsUShort> >
      ("DrawElementsUShort")
      .def( init<GLenum>() )
      .def( init<GLenum, unsigned int, GLushort*, int>() )
      .def( init<GLenum, unsigned int>() )
      //.def( "getData", &DrawElementsUShort::getDataPointer, osgBoostPython::default_pointer_policy() )
      .def("getTotalDataSize", &DrawElementsUShort::getTotalDataSize )
      .def("supportsBufferObject", &DrawElementsUShort::supportsBufferObject )
      .def("draw", &DrawElementsUShort::draw )
      .def("accept", accept_pf )
      .def("accept", accept_pif )
      .def("getNumIndices", &DrawElementsUShort::getNumIndices )
      .def("index", &DrawElementsUShort::index )
      .def("offsetIndices", &DrawElementsUShort::offsetIndices )
      .def("reserveElements", &DrawElementsUShort::reserveElements )
      .def("setElement", &DrawElementsUShort::setElement )
      .def("getElement", &DrawElementsUShort::getElement )
      .def("addElement", &DrawElementsUShort::addElement )
      ;
  }
  
  // DrawElementsUInt
  {
    void(DrawElementsUInt::*accept_pf)(PrimitiveFunctor&) const = &DrawElementsUInt::accept;
    void(DrawElementsUInt::*accept_pif)(PrimitiveIndexFunctor&) const = &DrawElementsUInt::accept;
    
    class_<DrawElementsUInt, bases<DrawElements,VectorGLuint>, ref_ptr<DrawElementsUInt> >
      ("DrawElementsUInt")
      .def( init<GLenum>() )
      .def( init<GLenum, unsigned int, GLuint*, int>() )
      .def( init<GLenum, unsigned int>() )
      //.def( "getData", &DrawElementsUInt::getDataPointer, osgBoostPython::default_pointer_policy() )
      .def("getTotalDataSize", &DrawElementsUInt::getTotalDataSize )
      .def("supportsBufferObject", &DrawElementsUInt::supportsBufferObject )
      .def("draw", &DrawElementsUInt::draw )
      .def("accept", accept_pf )
      .def("accept", accept_pif )
      .def("getNumIndices", &DrawElementsUInt::getNumIndices )
      .def("index", &DrawElementsUInt::index )
      .def("offsetIndices", &DrawElementsUInt::offsetIndices )
      .def("reserveElements", &DrawElementsUInt::reserveElements )
      .def("setElement", &DrawElementsUInt::setElement )
      .def("getElement", &DrawElementsUInt::getElement )
      .def("addElement", &DrawElementsUInt::addElement )
      ;
  }
}
