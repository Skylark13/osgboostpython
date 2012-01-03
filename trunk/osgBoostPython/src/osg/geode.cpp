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

#include <osg/ref_ptr>
#include <osg/Node>
#include <osg/Geode>
using namespace osg;

#include "defaults.h"


#define USE_PTRS_FOR_DRAWABLELIST
#ifdef USE_PTRS_FOR_DRAWABLELIST
typedef std::vector<Drawable*> DrawableList;
const DrawableList Geode_getDrawableList1(osg::Geode* geode)
{
    const Geode::DrawableList& drawables = geode->getDrawableList();
    DrawableList result;
    for (unsigned int i = 0; i < drawables.size(); ++i)
        result.push_back(drawables[i].get());
    return result;
}
#endif

// The equals that take ref_ptrs aren't called by python at all. To see that, 
// uncomment the #define USE_PTRS_FOR_DRAWABLELIST above and try to do this:
//   drawableList = geode.getDrawableList()
//   drawableList[0].name  # assuming the geode contained at least one drawable
// I guess it's because their type is ref_ptr<T> and not ref_ptr<T*> so it 
// doesn't know it can call them for ref_ptr<ShapeDrawable> == ShapeDrawable*...

void export_Geode() {
#ifndef USE_PTRS_FOR_DRAWABLELIST
        FUNC_PTR0_CONST(const Geode::DrawableList&, Geode, Geode_getDrawableList1, Geode::getDrawableList)
#endif
        FUNC_PTR1(Drawable*, Geode, Geode_getDrawable1, unsigned int , Geode::getDrawable)
        FUNC_PTR1(bool, Geode, Geode_removeDrawable1, osg::Drawable*, Geode::removeDrawable)

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

#ifdef USE_PTRS_FOR_DRAWABLELIST
        // The local DrawableList (see near the top) contains Drawable*
        class_<DrawableList>("DrawableList")
            .def( vector_indexing_suite< DrawableList >() )
        ;
#else
        // Geode::DrawableList contains ref_ptr<Drawable>
        class_<Geode::DrawableList>("DrawableList")
            .def( vector_indexing_suite< Geode::DrawableList >() )
        ;
#endif
    
    ;
}
