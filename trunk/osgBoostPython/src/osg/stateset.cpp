#include <boost/python.hpp>
using namespace boost::python;

#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/Uniform>

using namespace osg;

#include "defaults.h"


void export_stateAttributes();

//----------------- StateAttribute -----------------
const StateAttribute::ParentList& (StateAttribute::*StateAttribute_getParents1)() const = &StateAttribute::getParents;
StateSet* (StateAttribute::*StateAttribute_getParent1)( unsigned int ) = &StateAttribute::getParent;
void (StateSet::*StateSet_removeMode1)(StateAttribute::GLMode) = &StateSet::removeMode;
//----------------- StateAttribute -----------------

//----------------- Uniform -----------------
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
//----------------- Uniform -----------------

//----------------- StateSet -----------------
// Parents
const StateSet::ParentList& (StateSet::*StateSet_getParents1)() const = &StateSet::getParents;
Object* (StateSet::*StateSet_getParent1)( unsigned int ) = &StateSet::getParent;

// Modes
void (StateSet::*StateSet_setMode1)(StateAttribute::GLMode, StateAttribute::GLModeValue) = &StateSet::setMode;
StateAttribute::GLModeValue (StateSet::*StateSet_getMode1)(StateAttribute::GLMode) const = &StateSet::getMode;

// Attributes
void (StateSet::*StateSet_setAttribute1)(StateAttribute*, StateAttribute::OverrideValue) = &StateSet::setAttribute;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_setAttribute_overloads, setAttribute, 1, 2)
// getAttribute and removeAttribute have a default value on the second 
// argument, the BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS allows us to use them.
StateAttribute* (StateSet::*StateSet_getAttribute1)(StateAttribute::Type, unsigned int) = &StateSet::getAttribute;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_getAttribute_overloads, getAttribute, 1, 2)
void (StateSet::*StateSet_removeAttribute1)(StateAttribute::Type, unsigned int) = &StateSet::removeAttribute;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_removeAttribute_overloads, removeAttribute, 1, 2)
void (StateSet::*StateSet_removeAttribute2)(StateAttribute*) = &StateSet::removeAttribute;

// TextureAttributes
void (StateSet::*StateSet_setTextureAttribute1)(unsigned int, StateAttribute*, StateAttribute::OverrideValue) = &StateSet::setTextureAttribute;
StateAttribute* (StateSet::*StateSet_getTextureAttribute1)(unsigned int, StateAttribute::Type) = &StateSet::getTextureAttribute;
void (StateSet::*StateSet_removeTextureAttribute1)(unsigned int, StateAttribute::Type) = &StateSet::removeTextureAttribute;
void (StateSet::*StateSet_removeTextureAttribute2)(unsigned int, StateAttribute*) = &StateSet::removeTextureAttribute;

// Uniforms
Uniform* (StateSet::*StateSet_getUniform1)(const std::string&) = &StateSet::getUniform;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_getOrCreateUniform_overloads, getOrCreateUniform, 2, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_addUniform_overloads, addUniform, 1, 2)
void (StateSet::*StateSet_removeUniform1)(const std::string&) = &StateSet::removeUniform;
void (StateSet::*StateSet_removeUniform2)(Uniform*) = &StateSet::removeUniform;

// RenderBin
void (StateSet::*StateSet_setRenderBinDetails1)(int, const std::string&, StateSet::RenderBinMode) = &StateSet::setRenderBinDetails;
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(StateSet_setRenderBinDetails_overloads, setRenderBinDetails, 2, 3)
//----------------- StateSet -----------------

void export_stateset()
{
    // Expose all OpenGL modes so we can use them in StateSet::setMode()
    scope().attr("GL_ALPHA_TEST") = GL_ALPHA_TEST;
    scope().attr("GL_AUTO_NORMAL") = GL_AUTO_NORMAL;
    scope().attr("GL_BLEND") = GL_BLEND;
    scope().attr("GL_CLIP_PLANE0") = GL_CLIP_PLANE0;
    scope().attr("GL_CLIP_PLANE1") = GL_CLIP_PLANE1;
    scope().attr("GL_CLIP_PLANE2") = GL_CLIP_PLANE2;
    scope().attr("GL_CLIP_PLANE3") = GL_CLIP_PLANE3;
    scope().attr("GL_CLIP_PLANE4") = GL_CLIP_PLANE4;
    scope().attr("GL_CLIP_PLANE5") = GL_CLIP_PLANE5;
    scope().attr("GL_COLOR_LOGIC_OP") = GL_COLOR_LOGIC_OP;
    scope().attr("GL_COLOR_MATERIAL") = GL_COLOR_MATERIAL;
    scope().attr("GL_CULL_FACE") = GL_CULL_FACE;
    scope().attr("GL_DEPTH_TEST") = GL_DEPTH_TEST;
    scope().attr("GL_DITHER") = GL_DITHER;
    scope().attr("GL_FOG") = GL_FOG;
    scope().attr("GL_INDEX_LOGIC_OP") = GL_INDEX_LOGIC_OP;
    scope().attr("GL_LIGHTi") = GL_LIGHT0;
    scope().attr("GL_LIGHTi") = GL_LIGHT1;
    scope().attr("GL_LIGHTi") = GL_LIGHT2;
    scope().attr("GL_LIGHTi") = GL_LIGHT3;
    scope().attr("GL_LIGHTi") = GL_LIGHT4;
    scope().attr("GL_LIGHTi") = GL_LIGHT5;
    scope().attr("GL_LIGHTi") = GL_LIGHT6;
    scope().attr("GL_LIGHTi") = GL_LIGHT7;
    scope().attr("GL_LIGHTING") = GL_LIGHTING;
    scope().attr("GL_LINE_SMOOTH") = GL_LINE_SMOOTH;
    scope().attr("GL_LINE_STIPPLE") = GL_LINE_STIPPLE;
    scope().attr("GL_MAP1_COLOR_4") = GL_MAP1_COLOR_4;
    scope().attr("GL_MAP1_INDEX") = GL_MAP1_INDEX;
    scope().attr("GL_MAP1_NORMAL") = GL_MAP1_NORMAL;
    scope().attr("GL_MAP1_TEXTURE_COORD_1") = GL_MAP1_TEXTURE_COORD_1;
    scope().attr("GL_MAP1_TEXTURE_COORD_2") = GL_MAP1_TEXTURE_COORD_2;
    scope().attr("GL_MAP1_TEXTURE_COORD_3") = GL_MAP1_TEXTURE_COORD_3;
    scope().attr("GL_MAP1_TEXTURE_COORD_4") = GL_MAP1_TEXTURE_COORD_4;
    scope().attr("GL_MAP1_VERTEX_3") = GL_MAP1_VERTEX_3;
    scope().attr("GL_MAP1_VERTEX_4") = GL_MAP1_VERTEX_4;
    scope().attr("GL_MAP2_COLOR_4") = GL_MAP2_COLOR_4;
    scope().attr("GL_MAP2_INDEX") = GL_MAP2_INDEX;
    scope().attr("GL_MAP2_NORMAL") = GL_MAP2_NORMAL;
    scope().attr("GL_MAP2_TEXTURE_COORD_1") = GL_MAP2_TEXTURE_COORD_1;
    scope().attr("GL_MAP2_TEXTURE_COORD_2") = GL_MAP2_TEXTURE_COORD_2;
    scope().attr("GL_MAP2_TEXTURE_COORD_3") = GL_MAP2_TEXTURE_COORD_3;
    scope().attr("GL_MAP2_TEXTURE_COORD_4") = GL_MAP2_TEXTURE_COORD_4;
    scope().attr("GL_MAP2_VERTEX_3") = GL_MAP2_VERTEX_3;
    scope().attr("GL_MAP2_VERTEX_4") = GL_MAP2_VERTEX_4;
    scope().attr("GL_NORMALIZE") = GL_NORMALIZE;
    scope().attr("GL_POINT_SMOOTH") = GL_POINT_SMOOTH;
    scope().attr("GL_POLYGON_OFFSET_FILL") = GL_POLYGON_OFFSET_FILL;
    scope().attr("GL_POLYGON_OFFSET_LINE") = GL_POLYGON_OFFSET_LINE;
    scope().attr("GL_POLYGON_OFFSET_POINT") = GL_POLYGON_OFFSET_POINT;
    scope().attr("GL_POLYGON_SMOOTH") = GL_POLYGON_SMOOTH;
    scope().attr("GL_POLYGON_STIPPLE") = GL_POLYGON_STIPPLE;
    scope().attr("GL_SCISSOR_TEST") = GL_SCISSOR_TEST;
    scope().attr("GL_STENCIL_TEST") = GL_STENCIL_TEST;
    scope().attr("GL_TEXTURE_1D") = GL_TEXTURE_1D;
    scope().attr("GL_TEXTURE_2D") = GL_TEXTURE_2D;
    scope().attr("GL_TEXTURE_GEN_Q") = GL_TEXTURE_GEN_Q;
    scope().attr("GL_TEXTURE_GEN_R") = GL_TEXTURE_GEN_R;
    scope().attr("GL_TEXTURE_GEN_S") = GL_TEXTURE_GEN_S;
    scope().attr("GL_TEXTURE_GEN_T") = GL_TEXTURE_GEN_T;


    {
        scope in_StateAttribute = class_<StateAttribute, bases<Object>, ref_ptr<StateAttribute>, boost::noncopyable >("StateAttribute", no_init)
            .def("getNumParents", &StateAttribute::getNumParents)
            .def("getParents", StateAttribute_getParents1, osgBoostPython::default_value_policy())
            .def("getParent", StateAttribute_getParent1, osgBoostPython::default_pointer_policy())
            .def("getType", &StateAttribute::getType)
            .def("isTextureAttribute", &StateAttribute::isTextureAttribute)
            // TODO: set/get update/event callback
        ;

        // Need to use + instead of | to combine values, but otherwise works great.
        enum_<StateAttribute::Values>("Values");
            scope().attr("OFF") = StateAttribute::OFF;
            scope().attr("ON") = StateAttribute::ON;
            scope().attr("OVERRIDE") = StateAttribute::OVERRIDE;
            scope().attr("PROTECTED") = StateAttribute::PROTECTED;
            scope().attr("INHERIT") = StateAttribute::INHERIT;

        enum_<StateAttribute::Type>("Type");
            scope().attr("TEXTURE") = StateAttribute::TEXTURE;
            scope().attr("POLYGONMODE") = StateAttribute::POLYGONMODE;
            scope().attr("POLYGONOFFSET") = StateAttribute::POLYGONOFFSET;
            scope().attr("MATERIAL") = StateAttribute::MATERIAL;
            scope().attr("ALPHAFUNC") = StateAttribute::ALPHAFUNC;
            scope().attr("ANTIALIAS") = StateAttribute::ANTIALIAS;
            scope().attr("COLORTABLE") = StateAttribute::COLORTABLE;
            scope().attr("CULLFACE") = StateAttribute::CULLFACE;
            scope().attr("FOG") = StateAttribute::FOG;
            scope().attr("FRONTFACE") = StateAttribute::FRONTFACE;
            scope().attr("LIGHT") = StateAttribute::LIGHT;
            scope().attr("POINT") = StateAttribute::POINT;
            scope().attr("LINEWIDTH") = StateAttribute::LINEWIDTH;
            scope().attr("LINESTIPPLE") = StateAttribute::LINESTIPPLE;
            scope().attr("POLYGONSTIPPLE") = StateAttribute::POLYGONSTIPPLE;
            scope().attr("SHADEMODEL") = StateAttribute::SHADEMODEL;
            scope().attr("TEXENV") = StateAttribute::TEXENV;
            scope().attr("TEXENVFILTER") = StateAttribute::TEXENVFILTER;
            scope().attr("TEXGEN") = StateAttribute::TEXGEN;
            scope().attr("TEXMAT") = StateAttribute::TEXMAT;
            scope().attr("LIGHTMODEL") = StateAttribute::LIGHTMODEL;
            scope().attr("BLENDFUNC") = StateAttribute::BLENDFUNC;
            scope().attr("BLENDEQUATION") = StateAttribute::BLENDEQUATION;
            scope().attr("LOGICOP") = StateAttribute::LOGICOP;
            scope().attr("STENCIL") = StateAttribute::STENCIL;
            scope().attr("COLORMASK") = StateAttribute::COLORMASK;
            scope().attr("DEPTH") = StateAttribute::DEPTH;
            scope().attr("VIEWPORT") = StateAttribute::VIEWPORT;
            scope().attr("SCISSOR") = StateAttribute::SCISSOR;
            scope().attr("BLENDCOLOR") = StateAttribute::BLENDCOLOR;
            scope().attr("MULTISAMPLE") = StateAttribute::MULTISAMPLE;
            scope().attr("CLIPPLANE") = StateAttribute::CLIPPLANE;
            scope().attr("COLORMATRIX") = StateAttribute::COLORMATRIX;
            scope().attr("VERTEXPROGRAM") = StateAttribute::VERTEXPROGRAM;
            scope().attr("FRAGMENTPROGRAM") = StateAttribute::FRAGMENTPROGRAM;
            scope().attr("POINTSPRITE") = StateAttribute::POINTSPRITE;
            scope().attr("PROGRAM") = StateAttribute::PROGRAM;
            scope().attr("CLAMPCOLOR") = StateAttribute::CLAMPCOLOR;
            scope().attr("HINT") = StateAttribute::HINT;
            scope().attr("VALIDATOR") = StateAttribute::VALIDATOR;
            scope().attr("VIEWMATRIXEXTRACTOR") = StateAttribute::VIEWMATRIXEXTRACTOR;
            scope().attr("OSGNV_PARAMETER_BLOCK") = StateAttribute::OSGNV_PARAMETER_BLOCK;
            scope().attr("OSGNVEXT_TEXTURE_SHADER") = StateAttribute::OSGNVEXT_TEXTURE_SHADER;
            scope().attr("OSGNVEXT_VERTEX_PROGRAM") = StateAttribute::OSGNVEXT_VERTEX_PROGRAM;
            scope().attr("OSGNVEXT_REGISTER_COMBINERS") = StateAttribute::OSGNVEXT_REGISTER_COMBINERS;
            scope().attr("OSGNVCG_PROGRAM") = StateAttribute::OSGNVCG_PROGRAM;
            scope().attr("OSGNVSLANG_PROGRAM") = StateAttribute::OSGNVSLANG_PROGRAM;
            scope().attr("OSGNVPARSE_PROGRAM_PARSER") = StateAttribute::OSGNVPARSE_PROGRAM_PARSER;
    }

    export_stateAttributes();

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

    {
        scope in_StateSet = class_<StateSet, bases<Object>, ref_ptr<StateSet> >("StateSet")
            .def("getNumParents", &StateSet::getNumParents)
            .def("getParents", StateSet_getParents1, osgBoostPython::default_value_policy())
            .def("getParent", StateSet_getParent1, osgBoostPython::default_pointer_policy())
            .def("setMode", StateSet_setMode1)
            .def("removeMode", StateSet_removeMode1)
            .def("getMode", StateSet_getMode1)
            .def("setAttribute", StateSet_setAttribute1, StateSet_setAttribute_overloads())
            .def("setAttributeAndModes", &StateSet::setAttributeAndModes)
            .def("removeAttribute", StateSet_removeAttribute1, StateSet_removeAttribute_overloads())
            .def("removeAttribute", StateSet_removeAttribute2)
            .def("getAttribute", StateSet_getAttribute1, osgBoostPython::default_pointer_policy(), StateSet_getAttribute_overloads())
            .def("setTextureMode", &StateSet::setTextureMode)
            .def("removeTextureMode", &StateSet::removeTextureMode)
            .def("getTextureMode", &StateSet::getTextureMode)
            .def("setTextureAttribute", StateSet_setTextureAttribute1)
            .def("setTextureAttributeAndModes", &StateSet::setTextureAttributeAndModes)
            .def("removeTextureAttribute", StateSet_removeTextureAttribute1)
            .def("removeTextureAttribute", StateSet_removeTextureAttribute2)
            .def("getTextureAttribute", StateSet_getTextureAttribute1, osgBoostPython::default_pointer_policy())
            .def("setRenderingHint", &StateSet::setRenderingHint)
            .def("getRenderingHint", &StateSet::getRenderingHint)
            .def("addUniform", &StateSet::addUniform, StateSet_addUniform_overloads())
            .def("removeUniform", StateSet_removeUniform1)
            .def("removeUniform", StateSet_removeUniform2)
            .def("getUniform", StateSet_getUniform1, osgBoostPython::default_pointer_policy())
            .def("getOrCreateUniform", &StateSet::getOrCreateUniform, osgBoostPython::default_pointer_policy(), StateSet_getOrCreateUniform_overloads())
             .def("setRenderBinDetails", StateSet_setRenderBinDetails1, StateSet_setRenderBinDetails_overloads())
        ;

        enum_<StateSet::RenderingHint>("RenderingHint");
            scope().attr("DEFAULT_BIN") = StateSet::DEFAULT_BIN;
            scope().attr("OPAQUE_BIN") = StateSet::OPAQUE_BIN;
            scope().attr("TRANSPARENT_BIN") = StateSet::TRANSPARENT_BIN;

        enum_<StateSet::RenderBinMode>("RenderBinMode");
            scope().attr("INHERIT_RENDERBIN_DETAILS") = StateSet::INHERIT_RENDERBIN_DETAILS;
            scope().attr("USE_RENDERBIN_DETAILS") = StateSet::USE_RENDERBIN_DETAILS;
            scope().attr("OVERRIDE_RENDERBIN_DETAILS") = StateSet::OVERRIDE_RENDERBIN_DETAILS;

    }
}
