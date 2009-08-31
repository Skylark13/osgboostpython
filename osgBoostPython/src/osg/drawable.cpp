#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
using namespace boost::python;

#define WIN32

#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Geometry>

#include <osg/Shape>

using namespace osg;

const Drawable::ParentList& (Drawable::*Drawable_getParents1)() const = &Drawable::getParents;
Node* (Drawable::*Drawable_getParent1)( unsigned int ) = &Drawable::getParent;


void export_drawable()
{

    // Drawable and DrawCallback
    {
        // Abstract class
        scope in_Drawable = class_<Drawable, bases<Object>, ref_ptr<Drawable>, boost::noncopyable >("Drawable", no_init)
            .def("getNumParents", &Node::getNumParents)
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
        // TODO: Wrap osg::Array, osg::MixinVector<T>
        //       Then osg::TemplateArray : public Array, public MixinVector<T>
        //       Then Vec3Array et al.

        class_<Geometry, bases<Drawable>, ref_ptr<Geometry> >("Geometry")
            //.add_property("vertexArray", make_function(&Geometry::getVertexArray, return_value_policy<reference_existing_object>()), &Geometry::setVertexArray)
            .add_property("normalBinding", &Geometry::getNormalBinding, &Geometry::setNormalBinding)
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

}