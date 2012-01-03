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
#include <osg/Object>

using namespace osg;
#include "defaults.h"

void export_Object()
{
    // Object and its enum
    {
        // Pointer calling a specific version of an overloaded method
        // http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/python/functions.html#python.overloading
        FUNC_PTR1(void, Object, Object_setName1, const std::string&, Object::setName)

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

        enum_<Object::DataVariance>("DataVariance");
            scope().attr("DYNAMIC") = Object::DYNAMIC;
            scope().attr("STATIC") = Object::STATIC;
            scope().attr("UNSPECIFIED") = Object::UNSPECIFIED;
    }

}
