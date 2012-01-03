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

#include <osg/StateSet>
#include <osg/Uniform>
using namespace osg;

#include "defaults.h"

const Uniform::ParentList& (Uniform::*Uniform_getParents1)() const = &Uniform::getParents;
StateSet* (Uniform::*Uniform_getParent1)( unsigned int ) = &Uniform::getParent;

bool (Uniform::*Uniform_setFloat1)( float ) = &Uniform::set;
bool (Uniform::*Uniform_setInt1)( int ) = &Uniform::set;
bool (Uniform::*Uniform_setUInt1)( unsigned int ) = &Uniform::set;
bool (Uniform::*Uniform_setBool1)( bool ) = &Uniform::set;
bool (Uniform::*Uniform_setVec2f1)( const osg::Vec2& ) = &Uniform::set;
bool (Uniform::*Uniform_setVec3f1)( const osg::Vec3& ) = &Uniform::set;
bool (Uniform::*Uniform_setVec4f1)( const osg::Vec4& ) = &Uniform::set;
bool (Uniform::*Uniform_setMatrix2f1)( const osg::Matrix2& ) = &Uniform::set;
bool (Uniform::*Uniform_setMatrix3f1)( const osg::Matrix3& ) = &Uniform::set;
bool (Uniform::*Uniform_setMatrixf1)( const osg::Matrixf& ) = &Uniform::set;
bool (Uniform::*Uniform_setMatrixd1)( const osg::Matrixd& ) = &Uniform::set;
bool (Uniform::*Uniform_setInt21)( int, int ) = &Uniform::set;
bool (Uniform::*Uniform_setInt31)( int, int, int ) = &Uniform::set;
bool (Uniform::*Uniform_setInt41)( int, int, int, int ) = &Uniform::set;
bool (Uniform::*Uniform_setUInt21)( unsigned int, unsigned int ) = &Uniform::set;
bool (Uniform::*Uniform_setUInt31)( unsigned int, unsigned int, unsigned int ) = &Uniform::set;
bool (Uniform::*Uniform_setUInt41)( unsigned int, unsigned int, unsigned int, unsigned int ) = &Uniform::set;
bool (Uniform::*Uniform_setBool21)( bool, bool ) = &Uniform::set;
bool (Uniform::*Uniform_setBool31)( bool, bool, bool ) = &Uniform::set;
bool (Uniform::*Uniform_setBool41)( bool, bool, bool, bool ) = &Uniform::set;

// The single-argument gets return the value directly, the multiple-argument 
// ones return them in a tuple. You can call the multiple-argument sets with
// a tuple by unpacking it with '*' like so:
//     values = (False, True, False, False)
//     u.setBool4(*values)
float               Uniform_getFloat1   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); float f;         u->get(f); return f; }
int                 Uniform_getInt1     (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); int i;           u->get(i); return i; }
unsigned int        Uniform_getUInt1    (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); unsigned int ui; u->get(ui); return ui; }
bool                Uniform_getBool1    (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); bool b;          u->get(b); return b; }
osg::Vec2           Uniform_getVec2f1   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Vec2 v;     u->get(v); return v; }
osg::Vec3           Uniform_getVec3f1   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Vec3 v;     u->get(v); return v; }
osg::Vec4           Uniform_getVec4f1   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Vec4 v;     u->get(v); return v; }
osg::Matrix2        Uniform_getMatrix2f1(Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Matrix2 m;  u->get(m); return m; }
osg::Matrix3        Uniform_getMatrix3f1(Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Matrix3 m;  u->get(m); return m; }
osg::Matrixf        Uniform_getMatrixf1 (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Matrixf m;  u->get(m); return m; }
osg::Matrixd        Uniform_getMatrixd1 (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); osg::Matrixd m;  u->get(m); return m; }
boost::python::list Uniform_getInt21    (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; int i[2];           if (!u->get(i[0],  i[1]))                throw std::invalid_argument("Uniform does not contain a vector of 2 ints");  result.append(i[0]);  result.append(i[1]);                                              return result; }
boost::python::list Uniform_getInt31    (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; int i[3];           if (!u->get(i[0],  i[1],  i[2]))         throw std::invalid_argument("Uniform does not contain a vector of 3 ints");  result.append(i[0]);  result.append(i[1]);  result.append(i[2]);                        return result; }
boost::python::list Uniform_getInt41    (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; int i[4];           if (!u->get(i[0],  i[1],  i[2],  i[3]))  throw std::invalid_argument("Uniform does not contain a vector of 4 ints");  result.append(i[0]);  result.append(i[1]);  result.append(i[2]);  result.append(i[3]);  return result; }
boost::python::list Uniform_getUInt21   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; unsigned int ui[2]; if (!u->get(ui[0], ui[1]))               throw std::invalid_argument("Uniform does not contain a vector of 2 uints"); result.append(ui[0]); result.append(ui[1]);                                             return result; }
boost::python::list Uniform_getUInt31   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; unsigned int ui[2]; if (!u->get(ui[0], ui[1], ui[2]))        throw std::invalid_argument("Uniform does not contain a vector of 3 uints"); result.append(ui[0]); result.append(ui[1]); result.append(ui[2]);                       return result; }
boost::python::list Uniform_getUInt41   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; unsigned int ui[2]; if (!u->get(ui[0], ui[1], ui[2], ui[3])) throw std::invalid_argument("Uniform does not contain a vector of 4 uints"); result.append(ui[0]); result.append(ui[1]); result.append(ui[2]); result.append(ui[3]); return result; }
boost::python::list Uniform_getBool21   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; bool b[2];          if (!u->get(b[0],  b[1]))                throw std::invalid_argument("Uniform does not contain a vector of 2 bools"); result.append(b[0]);  result.append(b[1]);                                              return result; }
boost::python::list Uniform_getBool31   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; bool b[2];          if (!u->get(b[0],  b[1],  b[2]))         throw std::invalid_argument("Uniform does not contain a vector of 3 bools"); result.append(b[0]);  result.append(b[1]);  result.append(b[2]);                        return result; }
boost::python::list Uniform_getBool41   (Uniform* u) { if (!u) throw std::invalid_argument("Uniform is NULL"); boost::python::list result; bool b[2];          if (!u->get(b[0],  b[1],  b[2],  b[3]))  throw std::invalid_argument("Uniform does not contain a vector of 4 bools"); result.append(b[0]);  result.append(b[1]);  result.append(b[2]);  result.append(b[3]);  return result; }

bool (Uniform::*Uniform_setFloatArray1)(FloatArray*) = &Uniform::setArray;
bool (Uniform::*Uniform_setIntArray1)(IntArray*) = &Uniform::setArray;
bool (Uniform::*Uniform_setUIntArray1)(UIntArray*) = &Uniform::setArray;
FloatArray* (Uniform::*Uniform_getFloatArray1)() = &Uniform::getFloatArray;
IntArray* (Uniform::*Uniform_getIntArray1)() = &Uniform::getIntArray;
UIntArray* (Uniform::*Uniform_getUIntArray1)() = &Uniform::getUIntArray;

void export_Uniform()
{

  scope in_Uniform = class_<Uniform, bases<Object>, ref_ptr<Uniform> >("Uniform")
    .def(init<Uniform::Type, const std::string&, optional<int> >())
    .def("setType", &Uniform::setType)
    .def("getType", &Uniform::getType)
    .def("setName", &Uniform::setName)
    .def("setNumElements", &Uniform::setNumElements)
    .def("getNumElements", &Uniform::getNumElements)
    .def("getNumParents", &Uniform::getNumParents)
    .def("getParents", Uniform_getParents1, osgBoostPython::default_value_policy())
    .def("getParent", Uniform_getParent1, osgBoostPython::default_pointer_policy())

    // Since one Python type might correspond to many C++ types, I 
    // think we don't have a choice and have to expose methods called
    // get/setFloat(float), get/setInt(int), etc.
    .def("setFloat",    Uniform_setFloat1)
    .def("getFloat",    Uniform_getFloat1)
    .def("setInt",      Uniform_setInt1)
    .def("getInt",      Uniform_getInt1)
    .def("setUInt",     Uniform_setUInt1)
    .def("getUInt",     Uniform_getUInt1)
    .def("setBool",     Uniform_setBool1)
    .def("getBool",     Uniform_getBool1)
    .def("setVec2f",    Uniform_setVec2f1)
    .def("getVec2f",    Uniform_getVec2f1)
    .def("setVec3f",    Uniform_setVec3f1)
    .def("getVec3f",    Uniform_getVec3f1)
    .def("setVec4f",    Uniform_setVec4f1)
    .def("getVec4f",    Uniform_getVec4f1)
    .def("setMatrix2f", Uniform_setMatrix2f1)
    .def("getMatrix2f", Uniform_getMatrix2f1)
    .def("setMatrix3f", Uniform_setMatrix3f1)
    .def("getMatrix3f", Uniform_getMatrix3f1)
    .def("setMatrixf",  Uniform_setMatrixf1)
    .def("getMatrixf",  Uniform_getMatrixf1)
    .def("setMatrixd",  Uniform_setMatrixd1)
    .def("getMatrixd",  Uniform_getMatrixd1)
    .def("setInt2",     Uniform_setInt21)
    .def("getInt2",     Uniform_getInt21)
    .def("setInt3",     Uniform_setInt31)
    .def("getInt3",     Uniform_getInt31)
    .def("setInt4",     Uniform_setInt41)
    .def("getInt4",     Uniform_getInt41)
    .def("setUInt2",    Uniform_setUInt21)
    .def("getUInt2",    Uniform_getUInt21)
    .def("setUInt3",    Uniform_setUInt31)
    .def("getUInt3",    Uniform_getUInt31)
    .def("setUInt4",    Uniform_setUInt41)
    .def("getUInt4",    Uniform_getUInt41)
    .def("setBool2",    Uniform_setBool21)
    .def("getBool2",    Uniform_getBool21)
    .def("setBool3",    Uniform_setBool31)
    .def("getBool3",    Uniform_getBool31)
    .def("setBool4",    Uniform_setBool41)
    .def("getBool4",    Uniform_getBool41)
    
    .def("setFloatArray", Uniform_setFloatArray1)
    .def("setIntArray", Uniform_setIntArray1)
    .def("setUIntArray", Uniform_setUIntArray1)
    .def("getFloatArray", Uniform_getFloatArray1, osgBoostPython::default_pointer_policy())
    .def("getIntArray", Uniform_getIntArray1, osgBoostPython::default_pointer_policy())
    .def("getUIntArray", Uniform_getUIntArray1, osgBoostPython::default_pointer_policy())   
    ;
  
  enum_<Uniform::Type>("Type");
  scope().attr("FLOAT") = Uniform::FLOAT;
  scope().attr("FLOAT_VEC2") = Uniform::FLOAT_VEC2;
  scope().attr("FLOAT_VEC3") = Uniform::FLOAT_VEC3;
  scope().attr("FLOAT_VEC4") = Uniform::FLOAT_VEC4;
  scope().attr("INT") = Uniform::INT;
  scope().attr("INT_VEC2") = Uniform::INT_VEC2;
  scope().attr("INT_VEC3") = Uniform::INT_VEC3;
  scope().attr("INT_VEC4") = Uniform::INT_VEC4;
  scope().attr("BOOL") = Uniform::BOOL;
  scope().attr("BOOL_VEC2") = Uniform::BOOL_VEC2;
  scope().attr("BOOL_VEC3") = Uniform::BOOL_VEC3;
  scope().attr("BOOL_VEC4") = Uniform::BOOL_VEC4;
  scope().attr("FLOAT_MAT2") = Uniform::FLOAT_MAT2;
  scope().attr("FLOAT_MAT3") = Uniform::FLOAT_MAT3;
  scope().attr("FLOAT_MAT4") = Uniform::FLOAT_MAT4;
  scope().attr("SAMPLER_1D") = Uniform::SAMPLER_1D;
  scope().attr("SAMPLER_2D") = Uniform::SAMPLER_2D;
  scope().attr("SAMPLER_3D") = Uniform::SAMPLER_3D;
  scope().attr("SAMPLER_CUBE") = Uniform::SAMPLER_CUBE;
  scope().attr("SAMPLER_1D_SHADOW") = Uniform::SAMPLER_1D_SHADOW;
  scope().attr("SAMPLER_2D_SHADOW") = Uniform::SAMPLER_2D_SHADOW;
  scope().attr("SAMPLER_1D_ARRAY ") = Uniform::SAMPLER_1D_ARRAY ;
  scope().attr("SAMPLER_2D_ARRAY") = Uniform::SAMPLER_2D_ARRAY;
  scope().attr("SAMPLER_1D_ARRAY_SHADOW") = Uniform::SAMPLER_1D_ARRAY_SHADOW;
  scope().attr("SAMPLER_2D_ARRAY_SHADOW") = Uniform::SAMPLER_2D_ARRAY_SHADOW;
  scope().attr("FLOAT_MAT2x3") = Uniform::FLOAT_MAT2x3;
  scope().attr("FLOAT_MAT2x4") = Uniform::FLOAT_MAT2x4;
  scope().attr("FLOAT_MAT3x2") = Uniform::FLOAT_MAT3x2;
  scope().attr("FLOAT_MAT3x4") = Uniform::FLOAT_MAT3x4;
  scope().attr("FLOAT_MAT4x2") = Uniform::FLOAT_MAT4x2;
  scope().attr("FLOAT_MAT4x3") = Uniform::FLOAT_MAT4x3;
  scope().attr("SAMPLER_BUFFER") = Uniform::SAMPLER_BUFFER;
  scope().attr("SAMPLER_CUBE_SHADOW") = Uniform::SAMPLER_CUBE_SHADOW;
  scope().attr("UNSIGNED_INT") = Uniform::UNSIGNED_INT;
  scope().attr("UNSIGNED_INT_VEC2") = Uniform::UNSIGNED_INT_VEC2;
  scope().attr("UNSIGNED_INT_VEC3") = Uniform::UNSIGNED_INT_VEC3;
  scope().attr("UNSIGNED_INT_VEC4") = Uniform::UNSIGNED_INT_VEC4;
  scope().attr("INT_SAMPLER_1D") = Uniform::INT_SAMPLER_1D;
  scope().attr("INT_SAMPLER_2D") = Uniform::INT_SAMPLER_2D;
  scope().attr("INT_SAMPLER_3D") = Uniform::INT_SAMPLER_3D;
  scope().attr("INT_SAMPLER_CUBE") = Uniform::INT_SAMPLER_CUBE;
  scope().attr("INT_SAMPLER_2D_RECT") = Uniform::INT_SAMPLER_2D_RECT;
  scope().attr("INT_SAMPLER_1D_ARRAY") = Uniform::INT_SAMPLER_1D_ARRAY;
  scope().attr("INT_SAMPLER_2D_ARRAY") = Uniform::INT_SAMPLER_2D_ARRAY;
  scope().attr("INT_SAMPLER_BUFFER") = Uniform::INT_SAMPLER_BUFFER;
  scope().attr("UNSIGNED_INT_SAMPLER_1D") = Uniform::UNSIGNED_INT_SAMPLER_1D;
  scope().attr("UNSIGNED_INT_SAMPLER_2D") = Uniform::UNSIGNED_INT_SAMPLER_2D;
  scope().attr("UNSIGNED_INT_SAMPLER_3D") = Uniform::UNSIGNED_INT_SAMPLER_3D;
  scope().attr("UNSIGNED_INT_SAMPLER_CUBE") = Uniform::UNSIGNED_INT_SAMPLER_CUBE;
  scope().attr("UNSIGNED_INT_SAMPLER_2D_RECT") = Uniform::UNSIGNED_INT_SAMPLER_2D_RECT;
  scope().attr("UNSIGNED_INT_SAMPLER_1D_ARRAY") = Uniform::UNSIGNED_INT_SAMPLER_1D_ARRAY;
  scope().attr("UNSIGNED_INT_SAMPLER_2D_ARRAY") = Uniform::UNSIGNED_INT_SAMPLER_2D_ARRAY;
  scope().attr("UNSIGNED_INT_SAMPLER_BUFFER") = Uniform::UNSIGNED_INT_SAMPLER_BUFFER;
  scope().attr("UNDEFINED") = Uniform::UNDEFINED;
  
 }
