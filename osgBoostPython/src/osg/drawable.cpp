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
            // TODO: Wrap StateSet (big one)
            .add_property("stateSet", make_function(&Drawable::getOrCreateStateSet, osgBoostPython::default_pointer_policy()), &Drawable::setStateSet)     // TODO: wrapper returning ref_ptr for getOrCreateStateSet()
            .def("setStateSet", &Drawable::setStateSet)     // same call as in c++
            .def("getOrCreateStateSet", &Drawable::getOrCreateStateSet, osgBoostPython::default_pointer_policy())
            .def("setInitialBound", &Drawable::setInitialBound)
            .def("getInitialBound", &Drawable::getInitialBound, osgBoostPython::default_const_reference_policy())
            .def("dirtyBound", &Drawable::dirtyBound)
            .def("getBound", &Drawable::getBound, osgBoostPython::default_const_reference_policy())
            .def("computeBound", &Drawable::computeBound)
            .def("setUpdateCallback", &Drawable::setUpdateCallback)
            .def("setUseDisplayList", &Drawable::setUseDisplayList)
            .def("setSupportsDisplayList", &Drawable::setSupportsDisplayList)
            // TODO: Methods to set/get the ComputeBBoxCallback
        ;

        class_<Drawable::ParentList>("ParentList")
            .def( vector_indexing_suite< Drawable::ParentList >() )
        ;

        class_<Drawable::DrawCallback, bases<Object>, ref_ptr<Drawable::DrawCallback> >("DrawCallback")
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

    // TODO: Other shape subclasses

    class_<TessellationHints, bases<Object>, ref_ptr<TessellationHints> >("TessellationHints")
    ;

    class_<ShapeDrawable, bases<Drawable>, ref_ptr<ShapeDrawable> >("ShapeDrawable")
        .def(init<Shape*, TessellationHints*>())
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
    }

    // DrawElementsUByte
    {
    }

    // DrawElementsUShort
    {
    }

    // DrawElementsUInt
    {
    }
}
