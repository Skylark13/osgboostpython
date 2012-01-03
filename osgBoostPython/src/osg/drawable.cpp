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

typedef Drawable::UpdateCallback UpdateCallback;

struct Drawable_UpdateCallback_wrapper : public Drawable::UpdateCallback
{
    // Drawable::UpdateCallback constructors storing initial self parameter
    Drawable_UpdateCallback_wrapper(PyObject *p) 
        : Drawable::UpdateCallback(), self(p) {}
    // In case Drawable::UpdateCallback is returned by-value from a wrapped function
    Drawable_UpdateCallback_wrapper(PyObject *p, const Drawable::UpdateCallback& x) 
        : Drawable::UpdateCallback(x), self(p) {}

    // Override update to call back into Python
    void update(NodeVisitor* nv, Drawable* d)
    {
        call_method<void>(self, "update", ptr(nv), ptr(d));
    }

    // Supplies the default implementation of update
    void default_update(Drawable::UpdateCallback& self_, NodeVisitor* nv, Drawable* d)
    {
        self_.Drawable::UpdateCallback::update(nv,d);
    }
 private:
    PyObject* self;
};


struct Drawable_EventCallback_wrapper : public Drawable::EventCallback
{
    // Drawable::EventCallback constructor storing initial self parameter
    Drawable_EventCallback_wrapper(PyObject *p)
        : Drawable::EventCallback(), self(p) {}

    // In case Drawable::EventCallback is returned by-value from a wrapped function
    Drawable_EventCallback_wrapper(PyObject *p, const Drawable::EventCallback& x)
        : Drawable::EventCallback(x), self(p) {}

    // This version will be called by OSG, and calls the python version.
    void event(osg::NodeVisitor* nv, osg::Drawable* drawable)
    {
        call_method<void>(self, "event", ptr(nv), ptr(drawable));
    }

    // Supplies the default implementation of update
    void default_event(Drawable::EventCallback& self_, osg::NodeVisitor* nv, osg::Drawable* drawable)
    {
        self_.Drawable::EventCallback::event(nv, drawable);
    }

private:
    PyObject* self;
};


struct Drawable_CullCallback_wrapper : public Drawable::CullCallback
{
    // Drawable::CullCallback constructor storing initial self parameter
    Drawable_CullCallback_wrapper(PyObject *p)
        : Drawable::CullCallback(), self(p) {}

    // In case Drawable::CullCallback is returned by-value from a wrapped function
    Drawable_CullCallback_wrapper(PyObject *p, const Drawable::CullCallback& x)
        : Drawable::CullCallback(x), self(p) {}

    // This version will be called by OSG, and calls the python version.
    bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::State* state)
    {
        return call_method<bool>(self, "cull", ptr(nv), ptr(drawable), ptr(state));
    }

    // Supplies the default implementation of update
    bool default_cull1(Drawable::CullCallback& self_, osg::NodeVisitor* nv, osg::Drawable* drawable, osg::State* state)
    {
        return self_.Drawable::CullCallback::cull(nv, drawable, state);
    }

    // This version will be called by OSG, and calls the python version.
    bool cull(osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo)
    {
        return call_method<bool>(self, "cull", ptr(nv), ptr(drawable), ptr(renderInfo));
    }

    // Supplies the default implementation of update
    bool default_cull2(Drawable::CullCallback& self_, osg::NodeVisitor* nv, osg::Drawable* drawable, osg::RenderInfo* renderInfo)
    {
        return self_.Drawable::CullCallback::cull(nv, drawable, renderInfo);
    }

private:
    PyObject* self;
};


struct Drawable_DrawCallback_wrapper : public Drawable::DrawCallback
{
    // Drawable::DrawCallback constructor storing initial self parameter
    Drawable_DrawCallback_wrapper(PyObject *p)
        : Drawable::DrawCallback(), self(p) {}

    // In case Drawable::DrawCallback is returned by-value from a wrapped function
    Drawable_DrawCallback_wrapper(PyObject *p, const Drawable::DrawCallback& x)
        : Drawable::DrawCallback(x), self(p) {}

    // This version will be called by OSG, and calls the python version.
    void drawImplementation(osg::RenderInfo& renderInfo, const osg::Drawable* drawable)
    {
        call_method<void>(self, "drawImplementation", boost::ref(renderInfo), ptr(drawable));
    }

    // Supplies the default implementation of update
    void default_drawImplementation(Drawable::DrawCallback& self_, osg::RenderInfo& renderInfo, const osg::Drawable* drawable)
    {
        self_.Drawable::DrawCallback::drawImplementation(renderInfo, drawable);
    }

private:
    PyObject* self;
};

void export_Drawable()
{

    // Drawable and DrawCallback
    {
        // Abstract class
        scope in_Drawable = class_<Drawable, bases<Object>, ref_ptr<Drawable>, boost::noncopyable >("Drawable", no_init)
            .def("getNumParents", &Drawable::getNumParents)
            .def("getParents", Drawable_getParents1, osgBoostPython::default_value_policy())
            .def("getParent", Drawable_getParent1, osgBoostPython::default_pointer_policy())
            .add_property("stateSet", make_function(&Drawable::getOrCreateStateSet, osgBoostPython::default_pointer_policy()), 
			  &Drawable::setStateSet)     // TODO: wrapper returning ref_ptr for getOrCreateStateSet()
            .def("setStateSet", &Drawable::setStateSet)     // same call as in c++
            .def("getOrCreateStateSet", &Drawable::getOrCreateStateSet, osgBoostPython::default_pointer_policy())
            .def("setInitialBound", &Drawable::setInitialBound)
            .def("getInitialBound", &Drawable::getInitialBound, osgBoostPython::default_const_reference_policy())
            .def("dirtyBound", &Drawable::dirtyBound)
            .def("getBound", &Drawable::getBound, osgBoostPython::default_const_reference_policy())
            .def("computeBound", &Drawable::computeBound)
            .def("setUpdateCallback", &Drawable::setUpdateCallback)
            .def("getUpdateCallback", (Drawable::UpdateCallback* (Drawable::*)(void))&Drawable::getUpdateCallback, 
		 osgBoostPython::default_pointer_policy())
            .def("setEventCallback", &Drawable::setEventCallback)
            .def("getEventCallback", (Drawable::EventCallback* (Drawable::*)(void))&Drawable::getEventCallback, 
		 osgBoostPython::default_pointer_policy())
            .def("setCullCallback", &Drawable::setCullCallback)
            .def("getCullCallback", (Drawable::CullCallback* (Drawable::*)(void))&Drawable::getCullCallback, 
		 osgBoostPython::default_pointer_policy())
            .def("setDrawCallback", &Drawable::setDrawCallback)
            .def("getDrawCallback", (Drawable::DrawCallback* (Drawable::*)(void))&Drawable::getDrawCallback, 
		 osgBoostPython::default_pointer_policy())
            .def("setUseDisplayList", &Drawable::setUseDisplayList)
            .def("setSupportsDisplayList", &Drawable::setSupportsDisplayList)
            // TODO: Methods to set/get the ComputeBBoxCallback
        ;

        class_<Drawable::ParentList>("ParentList")
            .def( vector_indexing_suite< Drawable::ParentList >() )
        ;

	class_<Drawable::UpdateCallback, Drawable_UpdateCallback_wrapper, bases<Object>, ref_ptr<UpdateCallback> >("UpdateCallback")
	  .def("update", &Drawable_UpdateCallback_wrapper::default_update)
	  ;
	
	class_<Drawable::EventCallback, Drawable_EventCallback_wrapper, bases<Object>, ref_ptr<Drawable::EventCallback> >("EventCallback")
	  .def("event", &Drawable_EventCallback_wrapper::default_event)
	  ;
	
	class_<Drawable::CullCallback, Drawable_CullCallback_wrapper, bases<Object>, ref_ptr<Drawable::CullCallback> >("CullCallback")
	  .def("cull", &Drawable_CullCallback_wrapper::default_cull1)
	  .def("cull", &Drawable_CullCallback_wrapper::default_cull2)
	  ;
	
	class_<Drawable::DrawCallback, Drawable_DrawCallback_wrapper, bases<Object>, ref_ptr<Drawable::DrawCallback> >("DrawCallback")
	  .def("drawImplementation", &Drawable_DrawCallback_wrapper::default_drawImplementation)
	  ;
    }

}
