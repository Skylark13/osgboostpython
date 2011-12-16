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

#include <osg/Object>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/PrimitiveSet>

#include <osg/Shape>

using namespace osg;

#include "defaults.h"

const Drawable::ParentList& (Drawable::*Drawable_getParents1)() const = &Drawable::getParents;
Node* (Drawable::*Drawable_getParent1)( unsigned int ) = &Drawable::getParent;

Array* (Geometry::*Geometry_getVertexArray1)() = &Geometry::getVertexArray;
Array* (Geometry::*Geometry_getNormalArray1)() = &Geometry::getNormalArray;
Array* (Geometry::*Geometry_getColorArray1)() = &Geometry::getColorArray;
Array* (Geometry::*Geometry_getSecondaryColorArray1)() = &Geometry::getSecondaryColorArray;
Array* (Geometry::*Geometry_getTexCoordArray1)(unsigned int unit) = &Geometry::getTexCoordArray;
Array* (Geometry::*Geometry_getVertexAttribArray1)(unsigned int index) = &Geometry::getVertexAttribArray;
PrimitiveSet* (Geometry::*Geometry_getPrimitiveSet1)(unsigned int pos) = &Geometry::getPrimitiveSet;


void export_drawable()
{

    // Drawable and DrawCallback
    {
        // Abstract class
        scope in_Drawable = class_<Drawable, bases<Object>, ref_ptr<Drawable>, boost::noncopyable >("Drawable", no_init)
            .def("getNumParents", &Drawable::getNumParents)
            .def("getParents", Drawable_getParents1, osgBoostPython::default_value_policy())
            .def("getParent", Drawable_getParent1, osgBoostPython::default_pointer_policy())
            .add_property("stateSet", make_function(&Drawable::getOrCreateStateSet, osgBoostPython::default_pointer_policy()), &Drawable::setStateSet)     // TODO: wrapper returning ref_ptr for getOrCreateStateSet()
            .def("setStateSet", &Drawable::setStateSet)     // same call as in c++
            .def("getOrCreateStateSet", &Drawable::getOrCreateStateSet, osgBoostPython::default_pointer_policy())
            .def("setInitialBound", &Drawable::setInitialBound)
            .def("getInitialBound", &Drawable::getInitialBound, osgBoostPython::default_const_reference_policy())
            .def("dirtyBound", &Drawable::dirtyBound)
            .def("getBound", &Drawable::getBound, osgBoostPython::default_const_reference_policy())
            .def("computeBound", &Drawable::computeBound)
            .def("setUpdateCallback", &Drawable::setUpdateCallback)
            .def("getUpdateCallback", (Drawable::UpdateCallback* (Drawable::*)(void))&Drawable::getUpdateCallback, osgBoostPython::default_pointer_policy())
            .def("setEventCallback", &Drawable::setEventCallback)
            .def("getEventCallback", (Drawable::EventCallback* (Drawable::*)(void))&Drawable::getEventCallback, osgBoostPython::default_pointer_policy())
            .def("setCullCallback", &Drawable::setCullCallback)
            .def("getCullCallback", (Drawable::CullCallback* (Drawable::*)(void))&Drawable::getCullCallback, osgBoostPython::default_pointer_policy())
            .def("setDrawCallback", &Drawable::setDrawCallback)
            .def("getDrawCallback", (Drawable::DrawCallback* (Drawable::*)(void))&Drawable::getDrawCallback, osgBoostPython::default_pointer_policy())
            .def("setUseDisplayList", &Drawable::setUseDisplayList)
            .def("setSupportsDisplayList", &Drawable::setSupportsDisplayList)
            // TODO: Methods to set/get the ComputeBBoxCallback
        ;

        class_<Drawable::ParentList>("ParentList")
            .def( vector_indexing_suite< Drawable::ParentList >() )
        ;

    }

    // Abstract class
    class_<Shape, bases<Object>, ref_ptr<Shape>, boost::noncopyable >("Shape", no_init)
    ;

    class_<Sphere, bases<Shape>, ref_ptr<Sphere> >("Sphere")
        .def(init<Vec3f, float>())
        .def("set", &Sphere::set)
        .add_property("center", make_function(&Sphere::getCenter, osgBoostPython::default_const_reference_policy()), &Sphere::setCenter)
        .add_property("radius", &Sphere::getRadius, &Sphere::setRadius)
    ;

    class_<Box, bases<Shape>, ref_ptr<Box> >("Box")
      .def(init<Vec3f, float>())
      .def(init<Vec3f, float, float, float>())
      .def("set", &Box::set)
      .add_property("center", make_function(&Box::getCenter, osgBoostPython::default_const_reference_policy()), &Box::setCenter )
      .add_property("half_lengths", make_function(&Box::getHalfLengths, osgBoostPython::default_const_reference_policy()), &Box::setHalfLengths )
      .add_property("rotation", make_function(&Box::getRotation, osgBoostPython::default_const_reference_policy()), &Box::setRotation )
      .def("compute_rotation_matrix", &Box::computeRotationMatrix )
      .def("zero_rotation", &Box::zeroRotation )
    ;

    class_<Cone, bases<Shape>, ref_ptr<Cone> >("Cone")
      .def(init<Vec3f, float, float>())
      .def("set", &Cone::set)
      .add_property("center", make_function(&Cone::getCenter, osgBoostPython::default_const_reference_policy()), &Cone::setCenter)
      .add_property("radius", &Cone::getRadius, &Cone::setRadius)
      .add_property("height", &Cone::getHeight, &Cone::setHeight)
      .add_property("rotation", make_function(&Cone::getRotation, osgBoostPython::default_const_reference_policy()), &Cone::setRotation )
      .def("compute_rotation_matrix", &Cone::computeRotationMatrix )
      .def("zero_rotation", &Cone::zeroRotation )
      .add_property("base_offset_factor", &Cone::getBaseOffsetFactor )
      .add_property("base_offset", &Cone::getBaseOffset )
    ;

    class_<Cylinder, bases<Shape>, ref_ptr<Cylinder> >("Cylinder")
      .def(init<Vec3f, float, float>())
      .def("set", &Cylinder::set)
      .add_property("center", make_function(&Cylinder::getCenter, osgBoostPython::default_const_reference_policy()), &Cylinder::setCenter)
      .add_property("radius", &Cylinder::getRadius, &Cylinder::setRadius)
      .add_property("height", &Cylinder::getHeight, &Cylinder::setHeight)
      .add_property("rotation", make_function(&Cylinder::getRotation, osgBoostPython::default_const_reference_policy()), &Cylinder::setRotation )
      .def("compute_rotation_matrix", &Cylinder::computeRotationMatrix )
      .def("zero_rotation", &Cylinder::zeroRotation )
    ;

    class_<Capsule, bases<Shape>, ref_ptr<Capsule> >("Capsule")
      .def(init<Vec3f, float, float>())
      .def("set", &Capsule::set)
      .add_property("center", make_function(&Capsule::getCenter, osgBoostPython::default_const_reference_policy()), &Capsule::setCenter)
      .add_property("radius", &Capsule::getRadius, &Capsule::setRadius)
      .add_property("height", &Capsule::getHeight, &Capsule::setHeight)
      .add_property("rotation", make_function(&Capsule::getRotation, osgBoostPython::default_const_reference_policy()), &Capsule::setRotation )
      .def("compute_rotation_matrix", &Capsule::computeRotationMatrix )
      .def("zero_rotation", &Capsule::zeroRotation )
    ;

    // TODO: Other shape subclasses

    class_<TessellationHints, bases<Object>, ref_ptr<TessellationHints> >("TessellationHints")
    ;

    class_<ShapeDrawable, bases<Drawable>, ref_ptr<ShapeDrawable> >("ShapeDrawable")
        .def(init<Shape*, TessellationHints*>())
        .def(init<Shape*>())
        .add_property("color", make_function(&ShapeDrawable::getColor, osgBoostPython::default_const_reference_policy()), &ShapeDrawable::setColor)
    ;

    // Geometry
    {
        scope in_Geometry = class_<Geometry, bases<Drawable>, ref_ptr<Geometry> >("Geometry")
            // Could have gone for properties, but it doesn't work well for those that need arguments like texcoords...
            .def("setVertexArray", &Geometry::setVertexArray)
            .def("getVertexArray", Geometry_getVertexArray1, osgBoostPython::default_pointer_policy())
            .add_property("normalBinding", &Geometry::getNormalBinding, &Geometry::setNormalBinding)
            .def("setNormalArray", &Geometry::setNormalArray)
            .def("getNormalArray", Geometry_getNormalArray1, osgBoostPython::default_pointer_policy())
            .add_property("colorBinding", &Geometry::getColorBinding, &Geometry::setColorBinding)
            .def("setColorArray", &Geometry::setColorArray)
            .def("getColorArray", Geometry_getColorArray1, osgBoostPython::default_pointer_policy())
            .add_property("secondaryColorBinding", &Geometry::getSecondaryColorBinding, &Geometry::setSecondaryColorBinding)
            .def("setSecondaryColorArray", &Geometry::setSecondaryColorArray)
            .def("getSecondaryColorArray", Geometry_getSecondaryColorArray1, osgBoostPython::default_pointer_policy())
            .def("setTexCoordArray", &Geometry::setTexCoordArray)
            .def("getTexCoordArray", Geometry_getTexCoordArray1, osgBoostPython::default_pointer_policy())
            .def("setVertexAttribArray", &Geometry::setVertexAttribArray)
            .def("getVertexAttribArray", Geometry_getVertexAttribArray1, osgBoostPython::default_pointer_policy())
            .def("addPrimitiveSet", &Geometry::addPrimitiveSet)
            .def("getNumPrimitiveSets", &Geometry::getNumPrimitiveSets)
            .def("getPrimitiveSet", Geometry_getPrimitiveSet1, osgBoostPython::default_pointer_policy())
            .def("removePrimitiveSet", &Geometry::removePrimitiveSet)
        ;

        enum_<Geometry::AttributeBinding>("AttributeBinding");
            scope().attr("BIND_OFF") =               Geometry::BIND_OFF;
            scope().attr("BIND_OVERALL") =           Geometry::BIND_OVERALL;
            scope().attr("BIND_PER_PRIMITIVE_SET") = Geometry::BIND_PER_PRIMITIVE_SET;
            scope().attr("BIND_PER_PRIMITIVE") =     Geometry::BIND_PER_PRIMITIVE;
            scope().attr("BIND_PER_VERTEX") =        Geometry::BIND_PER_VERTEX;

    }

    // PrimitiveSet
    {
        scope in_PrimitiveSet = class_<PrimitiveSet, bases<Object>, ref_ptr<PrimitiveSet>, boost::noncopyable >("PrimitiveSet", no_init)
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
