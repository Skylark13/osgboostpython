// To build, use the build.bat file in the project dir.
// Before running, make sure you add the lib directory to PYTHONPATH
// as well as the directories containing bjam and boost+OSG DLLs to the PATH.
/*
for /F "Tokens=1" %I in ('cd') do set osgBoostPython_Lib=%I\lib
set PYTHONPATH=%PYTHONPATH%;%osgBoostPython_Lib%
set PATH=%PATH%;G:\boost_1_35_0\tools\jam\src\bin.ntx86;G:\boost_1_35_0\lib;%OSG_BIN_PATH%

cls && build
*/

// Good sources of information:
// http://wiki.python.org/moin/boost.python
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/index.html
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/v2/faq.html

// General Python info
// http://docs.python.org/tut/

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

// Sure, "Computational Crystallography Toolbox" doesn't seem like it applies 
// to us, but there's a lot of good example code for wrapping containers, etc.
// http://cctbx.sourceforge.net/
// http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/

using namespace boost::python;

#define WIN32

#include <osg/ref_ptr>

#include <osg/Referenced>
#include <osg/Object>

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Image>

#include <osg/Transform>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

using namespace osg;

#include "defaults.h"


// Definitions in other source files
void export_math();
void export_util();
void export_array();
void export_drawable();
void export_stateset();

// HeldType for objects which have a protected destructor.
// http://osdir.com/ml/python.c++/2002-07/msg00174.html
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/v2/pointee.html#pointee-spec
// TODO: read this
// http://mail.python.org/pipermail/c++-sig/2007-March/012045.html
// http://language-binding.net/pyplusplus/troubleshooting_guide/smart_ptrs/smart_ptrs.html
// http://markmail.org/message/u7v64d37ai2u6vok
// http://lists.boost.org/Archives/boost/2006/03/102515.php
namespace boost { 
namespace python {
  template <class T> struct pointee< ref_ptr<T> >
  {
     typedef T type;
  };
}
}


// Pointer calling a specific version of an overloaded method
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/python/functions.html#python.overloading
void (Object::*Object_setName1)( const std::string& ) = &Object::setName;

const Node::ParentList& (Node::*Node_getParents1)() const = &Node::getParents;
Group* (Node::*Node_getParent1)( unsigned int ) = &Node::getParent;
const NodeCallback* (Node::*Node_getUpdateCallback1)() const = &Node::getUpdateCallback;
const NodeCallback* (Node::*Node_getEventCallback1)() const = &Node::getEventCallback;
const NodeCallback* (Node::*Node_getCullCallback1)() const = &Node::getCullCallback;

Node* (Group::*Group_getChild1)( unsigned int ) = &Group::getChild;
bool (Group::*Group_removeChild1)( osg::Node* ) = &Group::removeChild;
bool (Group::*Group_removeChild2)( unsigned int, unsigned int ) = &Group::removeChild;    // Can't find a way to use the default argument here.

const Geode::DrawableList& (Geode::*Geode_getDrawableList1)() const = &Geode::getDrawableList;
Drawable* (Geode::*Geode_getDrawable1)( unsigned int ) = &Geode::getDrawable;
bool (Geode::*Geode_removeDrawable1)( osg::Drawable* ) = &Geode::removeDrawable;


BOOST_PYTHON_MODULE(_osg)
{
    export_math();

    class_<Referenced, ref_ptr<Referenced> >("Referenced")
    ;

    // Object and its enum
    {
        // Abstract class --> boost::noncopyable and no_init
        // http://mail.python.org/pipermail/c++-sig/2003-April/003699.html
        // http://wiki.python.org/moin/boost.python/FAQ#head-df5c8d3477ac287acce31b86042ab57642288f37
        // 
        // To be able to override C++ abstract base classes in a python class
        // http://www.nabble.com/Overriding-c%2B%2B-abstract-class-in-python-td19039105.html
        // http://mail.python.org/pipermail/c++-sig/2006-October/011523.html
        // http://www.nabble.com/-boost.python--Exposing-abstract-derived-classes-td18450942.html
        scope in_Object = class_<Object, bases<Referenced>, ref_ptr<Object>, boost::noncopyable >("Object", no_init)
            .add_property("name", make_function(&Object::getName, osgBoostPython::default_const_reference_policy()), Object_setName1)
            .add_property("dataVariance", &Object::getDataVariance, &Object::setDataVariance)
        ;

        enum_<Object::DataVariance>("DataVariance")
            .value("DYNAMIC",     Object::DYNAMIC)
            .value("STATIC",      Object::STATIC)
            .value("UNSPECIFIED", Object::UNSPECIFIED)
        ;

    }

    {
        scope in_Image = class_<Image, bases<Object>, ref_ptr<Image> >("Image")
            .def("s", &Image::s)
            .def("t", &Image::t)
            .def("r", &Image::r)
            .def("valid", &Image::valid)
            .def("isImageTranslucent", &Image::isImageTranslucent)
        ;
    }

    export_util();
    export_array();
    export_stateset();

    // Node
    {
        scope in_Node = class_<Node, bases<Object>, ref_ptr<Node> >("Node")
            .def("getNumParents", &Node::getNumParents)
            .def("getParents", Node_getParents1, osgBoostPython::default_value_policy())
            .def("getParent", Node_getParent1, osgBoostPython::default_pointer_policy())
            // TODO: NodePathList
            //.def("getParentalNodePaths", &Node::getParentalNodePaths)
            // TODO: MatrixList
            //.def("getWorldMatrices", &Node::getWorldMatrices)
            .def("accept", &Node::accept)
            .def("setUpdateCallback", &Node::setUpdateCallback)
            .def("getUpdateCallback", Node_getUpdateCallback1, osgBoostPython::default_pointer_policy())
            .def("addUpdateCallback", &Node::addUpdateCallback)
            .def("removeUpdateCallback", &Node::removeUpdateCallback)
            .def("setEventCallback", &Node::setEventCallback)
            .def("getEventCallback", Node_getEventCallback1, osgBoostPython::default_pointer_policy())
            .def("addEventCallback", &Node::addEventCallback)
            .def("removeEventCallback", &Node::removeEventCallback)
            .def("setCullCallback", &Node::setCullCallback)
            .def("getCullCallback", Node_getCullCallback1, osgBoostPython::default_pointer_policy())
            .def("addCullCallback", &Node::addCullCallback)
            .def("removeCullCallback", &Node::removeCullCallback)
            .add_property("cullingActive", &Node::getCullingActive, &Node::setCullingActive)
            .add_property("nodeMask", &Node::getNodeMask, &Node::setNodeMask)
            // TODO: Need methods related to descriptions?
            .add_property("stateSet", make_function(&Node::getOrCreateStateSet, osgBoostPython::default_pointer_policy()), &Node::setStateSet)     // TODO: wrapper returning ref_ptr for getOrCreateStateSet()
            .def("setInitialBound", &Node::setInitialBound)
            .def("getInitialBound", &Node::getInitialBound, osgBoostPython::default_const_reference_policy())
            .def("dirtyBound", &Node::dirtyBound)
            .def("getBound", &Node::getBound, osgBoostPython::default_const_reference_policy())
            .def("computeBound", &Node::computeBound)
            // TODO: Methods to set/get the ComputeBSphereCallback
        ;

        class_<Node::ParentList>("ParentList")
            .def( vector_indexing_suite< Node::ParentList >() )
        ;
    }

    // Group
    class_<Group, bases<Node>, ref_ptr<Group> >("Group")
        .def("getNumChildren", &Group::getNumChildren)
        .def("getChild", Group_getChild1, osgBoostPython::default_pointer_policy())
        .def("addChild", &Group::addChild)
        .def("insertChild", &Group::insertChild)
        .def("removeChild", Group_removeChild1)
        .def("removeChild", Group_removeChild2)
        .def("removeChildren", &Group::removeChildren)
        .def("replaceChild", &Group::replaceChild)
        .def("setChild", &Group::setChild)
        .def("containsNode", &Group::containsNode)
        .def("getChildIndex", &Group::getChildIndex)
    ;

    // Transform and its enum
    {
        // Abstract class
        scope in_Transform = class_<Transform, bases<Group>, ref_ptr<Transform>, boost::noncopyable >("Transform", no_init)
            .add_property("referenceFrame", &Transform::getReferenceFrame, &Transform::setReferenceFrame)
            .def("computeLocalToWorldMatrix", &Transform::computeLocalToWorldMatrix)
            .def("computeWorldToLocalMatrix", &Transform::computeWorldToLocalMatrix)
        ;

        enum_<Transform::ReferenceFrame>("ReferenceFrame")
            .value("RELATIVE_RF",                   Transform::RELATIVE_RF)
            .value("ABSOLUTE_RF",                   Transform::ABSOLUTE_RF)
            .value("ABSOLUTE_RF_INHERIT_VIEWPOINT", Transform::ABSOLUTE_RF_INHERIT_VIEWPOINT)
        ;
    }

    class_<MatrixTransform, bases<Transform>, ref_ptr<MatrixTransform> >("MatrixTransform")
        .def(init<Matrixd>())
        .add_property("matrix", make_function(&MatrixTransform::getMatrix, osgBoostPython::default_const_reference_policy()), &MatrixTransform::setMatrix)
        .def("preMult", &MatrixTransform::preMult)
        .def("postMult", &MatrixTransform::postMult)
        .def("getInverseMatrix", &MatrixTransform::getInverseMatrix, osgBoostPython::default_const_reference_policy())
        .def("computeLocalToWorldMatrix", &MatrixTransform::computeLocalToWorldMatrix)
        .def("computeWorldToLocalMatrix", &MatrixTransform::computeWorldToLocalMatrix)
    ;

    export_drawable();

    // Geode
    {
        class_<Geode, bases<Node>, ref_ptr<Geode> >("Geode")
            .def("addDrawable", &Geode::addDrawable)
            .def("getNumDrawables", &Geode::getNumDrawables)
            .def("getDrawableList", Geode_getDrawableList1, osgBoostPython::default_value_policy())
            .def("getDrawable", Geode_getDrawable1, osgBoostPython::default_pointer_policy())
            .def("addDrawable", &Geode::addDrawable)
            .def("removeDrawable", Geode_removeDrawable1)
            .def("removeDrawables", &Geode::removeDrawables)
            .def("replaceDrawable", &Geode::replaceDrawable)
            .def("setDrawable", &Geode::setDrawable)
            .def("containsDrawable", &Geode::containsDrawable)
            .def("getDrawableIndex", &Geode::getDrawableIndex)
        ;

        // For some reason, this doesn't work:
        // sd = osg.ShapeDrawable(osg.Sphere(), None)
        // sd.name = "sphere"
        // geode = osg.Geode()
        // geode.addDrawable(sd)
        // dl = geode.getDrawableList()
        // len(dl)    # returns 1
        // sd.name    # returns 'sphere'
        // dl[0].name # should return 'sphere', but causes this error instead:
        // # Traceback (most recent call last):
        // #   File "<stdin>", line 1, in <module>
        // # Boost.Python.ArgumentError: Python argument types in
        // #     None.None(Drawable)
        // # did not match C++ signature:
        // #     None(class osg::Object {lvalue})
        class_<Geode::DrawableList>("DrawableList")
            .def( vector_indexing_suite< Geode::DrawableList >() )
        ;
    }

    class_<View, bases<Object>, ref_ptr<View> >("View")
    ;
}
