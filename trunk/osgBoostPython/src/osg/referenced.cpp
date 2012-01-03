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
#include <osg/Referenced>

using namespace osg;
#include "defaults.h"
// The equals that take ref_ptrs aren't called by python at all. To see that, 
// uncomment the #define USE_PTRS_FOR_DRAWABLELIST above and try to do this:
//   drawableList = geode.getDrawableList()
//   drawableList[0].name  # assuming the geode contained at least one drawable
// I guess it's because their type is ref_ptr<T> and not ref_ptr<T*> so it 
// doesn't know it can call them for ref_ptr<ShapeDrawable> == ShapeDrawable*...
template<typename T> bool equals_ref_ref(ref_ptr<T> lhs, ref_ptr<T> rhs) { 
  /*std::cout << "equals_ref_ref" << std::endl;*/ 
  return lhs == rhs; 
}

template<typename T> bool equals_ref_ptr(ref_ptr<T> lhs, T* rhs) { 
  /*std::cout << "equals_ref_ptr" << std::endl;*/ 
  return lhs == rhs; 
}

template<typename T> bool equals_ptr_ref(T* lhs, ref_ptr<T> rhs) { 
  /*std::cout << "equals_ptr_ref" << std::endl;*/ 
return lhs == rhs.get(); 
}

template<typename T> bool equals_ptr_ptr(T* lhs, T* rhs) { 
  /*std::cout << "equals_ptr_ptr" << std::endl;*/ 
  return lhs == rhs; 
}

void export_Referenced()
{
  class_<Referenced, ref_ptr<Referenced> >("Referenced")
    .def("referenceCount", &Referenced::referenceCount)
    
    // For testing
    .def("equals_ref_ref", &equals_ref_ref<Referenced>)
    .def("equals_ref_ptr", &equals_ref_ptr<Referenced>)
    .def("equals_ptr_ref", &equals_ptr_ref<Referenced>)
    .def("equals_ptr_ptr", &equals_ptr_ptr<Referenced>)
    
    .def("__eq__", &equals_ref_ref<Referenced>)
    .def("__eq__", &equals_ref_ptr<Referenced>)
    .def("__eq__", &equals_ptr_ref<Referenced>)
    .def("__eq__", &equals_ptr_ptr<Referenced>)
    ;

}
