#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/PrimitiveSet>

#include <osg/Shape>

using namespace osg;


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
            .def("getParents", Drawable_getParents1, return_value_policy<return_by_value>())
            .def("getParent", Drawable_getParent1, return_value_policy<reference_existing_object>())
            // TODO: Wrap StateSet (big one)
            .add_property("stateSet", make_function(&Drawable::getOrCreateStateSet, return_internal_reference<>()), &Drawable::setStateSet)     // TODO: wrapper returning ref_ptr for getOrCreateStateSet()
            .def("setInitialBound", &Drawable::setInitialBound)
            .def("getInitialBound", &Drawable::getInitialBound, return_value_policy<copy_const_reference>())
            .def("dirtyBound", &Drawable::dirtyBound)
            .def("getBound", &Drawable::getBound, return_value_policy<copy_const_reference>())
            .def("computeBound", &Drawable::computeBound)
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
        .add_property("center", make_function(&Sphere::getCenter, return_value_policy<copy_const_reference>()), &Sphere::setCenter)
        .add_property("radius", &Sphere::getRadius, &Sphere::setRadius)
    ;

    // TODO: Other shape subclasses

    class_<TessellationHints, bases<Object>, ref_ptr<TessellationHints> >("TessellationHints")
    ;

    class_<ShapeDrawable, bases<Drawable>, ref_ptr<ShapeDrawable> >("ShapeDrawable")
        .def(init<Shape*, TessellationHints*>())
        .add_property("color", make_function(&ShapeDrawable::getColor, return_value_policy<copy_const_reference>()), &ShapeDrawable::setColor)
    ;

    // Geometry
    {
        scope in_Geometry = class_<Geometry, bases<Drawable>, ref_ptr<Geometry> >("Geometry")
            // Could have gone for properties, but it doesn't work well for those that need arguments like texcoords...
            .def("setVertexArray", &Geometry::setVertexArray)
            .def("getVertexArray", Geometry_getVertexArray1, return_value_policy<reference_existing_object>())
            .add_property("normalBinding", &Geometry::getNormalBinding, &Geometry::setNormalBinding)
            .def("setNormalArray", &Geometry::setNormalArray)
            .def("getNormalArray", Geometry_getNormalArray1, return_value_policy<reference_existing_object>())
            .add_property("colorBinding", &Geometry::getColorBinding, &Geometry::setColorBinding)
            .def("setColorArray", &Geometry::setColorArray)
            .def("getColorArray", Geometry_getColorArray1, return_value_policy<reference_existing_object>())
            .add_property("secondaryColorBinding", &Geometry::getSecondaryColorBinding, &Geometry::setSecondaryColorBinding)
            .def("setSecondaryColorArray", &Geometry::setSecondaryColorArray)
            .def("getSecondaryColorArray", Geometry_getSecondaryColorArray1, return_value_policy<reference_existing_object>())
            .def("setTexCoordArray", &Geometry::setTexCoordArray)
            .def("getTexCoordArray", Geometry_getTexCoordArray1, return_value_policy<reference_existing_object>())
            .def("setVertexAttribArray", &Geometry::setVertexAttribArray)
            .def("getVertexAttribArray", Geometry_getVertexAttribArray1, return_value_policy<reference_existing_object>())
            .def("addPrimitiveSet", &Geometry::addPrimitiveSet)
            .def("getNumPrimitiveSets", &Geometry::getNumPrimitiveSets)
            .def("getPrimitiveSet", Geometry_getPrimitiveSet1, return_value_policy<reference_existing_object>())
            .def("removePrimitiveSet", &Geometry::removePrimitiveSet)
            //.def()
        ;

        enum_<Geometry::AttributeBinding>("AttributeBinding")
            .value("BIND_OFF",               Geometry::BIND_OFF)
            .value("BIND_OVERALL",           Geometry::BIND_OVERALL)
            .value("BIND_PER_PRIMITIVE_SET", Geometry::BIND_PER_PRIMITIVE_SET)
            .value("BIND_PER_PRIMITIVE",     Geometry::BIND_PER_PRIMITIVE)
            .value("BIND_PER_VERTEX",        Geometry::BIND_PER_VERTEX)
        ;
    }

    // PrimitiveSet
    {
        scope in_PrimitiveSet = class_<PrimitiveSet, bases<Object>, ref_ptr<PrimitiveSet>, boost::noncopyable >("PrimitiveSet", no_init)
            //.def()
        ;

        enum_<PrimitiveSet::Type>("Type")
            .value("PrimitiveType",                   PrimitiveSet::PrimitiveType)
            .value("DrawArraysPrimitiveType",         PrimitiveSet::DrawArraysPrimitiveType)
            .value("DrawArrayLengthsPrimitiveType",   PrimitiveSet::DrawArrayLengthsPrimitiveType)
            .value("DrawElementsUBytePrimitiveType",  PrimitiveSet::DrawElementsUBytePrimitiveType)
            .value("DrawElementsUShortPrimitiveType", PrimitiveSet::DrawElementsUShortPrimitiveType)
            .value("DrawElementsUIntPrimitiveType",   PrimitiveSet::DrawElementsUIntPrimitiveType)
        ;

        enum_<PrimitiveSet::Mode>("Mode")
            .value("POINTS",         PrimitiveSet::POINTS)
            .value("LINES",          PrimitiveSet::LINES)
            .value("LINE_STRIP",     PrimitiveSet::LINE_STRIP)
            .value("LINE_LOOP",      PrimitiveSet::LINE_LOOP)
            .value("TRIANGLES",      PrimitiveSet::TRIANGLES)
            .value("TRIANGLE_STRIP", PrimitiveSet::TRIANGLE_STRIP)
            .value("TRIANGLE_FAN",   PrimitiveSet::TRIANGLE_FAN)
            .value("QUADS",          PrimitiveSet::QUADS)
            .value("QUAD_STRIP",     PrimitiveSet::QUAD_STRIP)
            .value("POLYGON",        PrimitiveSet::POLYGON)
        ;
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