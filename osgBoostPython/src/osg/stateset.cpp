#include <boost/python.hpp>
using namespace boost::python;

#define WIN32

#include <osg/StateSet>
#include <osg/StateAttribute>

using namespace osg;

const StateSet::ParentList& (StateSet::*StateSet_getParents1)() const = &StateSet::getParents;
Object* (StateSet::*StateSet_getParent1)( unsigned int ) = &StateSet::getParent;

void (StateSet::*StateSet_setMode1)(StateAttribute::GLMode, StateAttribute::GLModeValue) = &StateSet::setMode;
StateAttribute::GLModeValue (StateSet::*StateSet_getMode1)(StateAttribute::GLMode) const = &StateSet::getMode;

void export_stateset()
{
    // Expose all OpenGL modes so we can use them in StateSet::setMode()
	scope().attr("GL_ALPHA_TEST")           = GL_ALPHA_TEST;
	scope().attr("GL_AUTO_NORMAL")          = GL_AUTO_NORMAL;
	scope().attr("GL_BLEND")                = GL_BLEND;
	scope().attr("GL_CLIP_PLANE0")          = GL_CLIP_PLANE0;
	scope().attr("GL_CLIP_PLANE1")          = GL_CLIP_PLANE1;
	scope().attr("GL_CLIP_PLANE2")          = GL_CLIP_PLANE2;
	scope().attr("GL_CLIP_PLANE3")          = GL_CLIP_PLANE3;
	scope().attr("GL_CLIP_PLANE4")          = GL_CLIP_PLANE4;
	scope().attr("GL_CLIP_PLANE5")          = GL_CLIP_PLANE5;
	scope().attr("GL_COLOR_LOGIC_OP")       = GL_COLOR_LOGIC_OP;
	scope().attr("GL_COLOR_MATERIAL")       = GL_COLOR_MATERIAL;
	scope().attr("GL_CULL_FACE")            = GL_CULL_FACE;
	scope().attr("GL_DEPTH_TEST")           = GL_DEPTH_TEST;
	scope().attr("GL_DITHER")               = GL_DITHER;
	scope().attr("GL_FOG")                  = GL_FOG;
	scope().attr("GL_INDEX_LOGIC_OP")       = GL_INDEX_LOGIC_OP;
	scope().attr("GL_LIGHTi")               = GL_LIGHT0;
	scope().attr("GL_LIGHTi")               = GL_LIGHT1;
	scope().attr("GL_LIGHTi")               = GL_LIGHT2;
	scope().attr("GL_LIGHTi")               = GL_LIGHT3;
	scope().attr("GL_LIGHTi")               = GL_LIGHT4;
	scope().attr("GL_LIGHTi")               = GL_LIGHT5;
	scope().attr("GL_LIGHTi")               = GL_LIGHT6;
	scope().attr("GL_LIGHTi")               = GL_LIGHT7;
	scope().attr("GL_LIGHTING")             = GL_LIGHTING;
	scope().attr("GL_LINE_SMOOTH")          = GL_LINE_SMOOTH;
	scope().attr("GL_LINE_STIPPLE")         = GL_LINE_STIPPLE;
	scope().attr("GL_MAP1_COLOR_4")         = GL_MAP1_COLOR_4;
	scope().attr("GL_MAP1_INDEX")           = GL_MAP1_INDEX;
	scope().attr("GL_MAP1_NORMAL")          = GL_MAP1_NORMAL;
	scope().attr("GL_MAP1_TEXTURE_COORD_1") = GL_MAP1_TEXTURE_COORD_1;
	scope().attr("GL_MAP1_TEXTURE_COORD_2") = GL_MAP1_TEXTURE_COORD_2;
	scope().attr("GL_MAP1_TEXTURE_COORD_3") = GL_MAP1_TEXTURE_COORD_3;
	scope().attr("GL_MAP1_TEXTURE_COORD_4") = GL_MAP1_TEXTURE_COORD_4;
	scope().attr("GL_MAP1_VERTEX_3")        = GL_MAP1_VERTEX_3;
	scope().attr("GL_MAP1_VERTEX_4")        = GL_MAP1_VERTEX_4;
	scope().attr("GL_MAP2_COLOR_4")         = GL_MAP2_COLOR_4;
	scope().attr("GL_MAP2_INDEX")           = GL_MAP2_INDEX;
	scope().attr("GL_MAP2_NORMAL")          = GL_MAP2_NORMAL;
	scope().attr("GL_MAP2_TEXTURE_COORD_1") = GL_MAP2_TEXTURE_COORD_1;
	scope().attr("GL_MAP2_TEXTURE_COORD_2") = GL_MAP2_TEXTURE_COORD_2;
	scope().attr("GL_MAP2_TEXTURE_COORD_3") = GL_MAP2_TEXTURE_COORD_3;
	scope().attr("GL_MAP2_TEXTURE_COORD_4") = GL_MAP2_TEXTURE_COORD_4;
	scope().attr("GL_MAP2_VERTEX_3")        = GL_MAP2_VERTEX_3;
	scope().attr("GL_MAP2_VERTEX_4")        = GL_MAP2_VERTEX_4;
	scope().attr("GL_NORMALIZE")            = GL_NORMALIZE;
	scope().attr("GL_POINT_SMOOTH")         = GL_POINT_SMOOTH;
	scope().attr("GL_POLYGON_OFFSET_FILL")  = GL_POLYGON_OFFSET_FILL;
	scope().attr("GL_POLYGON_OFFSET_LINE")  = GL_POLYGON_OFFSET_LINE;
	scope().attr("GL_POLYGON_OFFSET_POINT") = GL_POLYGON_OFFSET_POINT;
	scope().attr("GL_POLYGON_SMOOTH")       = GL_POLYGON_SMOOTH;
	scope().attr("GL_POLYGON_STIPPLE")      = GL_POLYGON_STIPPLE;
	scope().attr("GL_SCISSOR_TEST")         = GL_SCISSOR_TEST;
	scope().attr("GL_STENCIL_TEST")         = GL_STENCIL_TEST;
	scope().attr("GL_TEXTURE_1D")           = GL_TEXTURE_1D;
	scope().attr("GL_TEXTURE_2D")           = GL_TEXTURE_2D;
	scope().attr("GL_TEXTURE_GEN_Q")        = GL_TEXTURE_GEN_Q;
	scope().attr("GL_TEXTURE_GEN_R")        = GL_TEXTURE_GEN_R;
	scope().attr("GL_TEXTURE_GEN_S")        = GL_TEXTURE_GEN_S;
	scope().attr("GL_TEXTURE_GEN_T")        = GL_TEXTURE_GEN_T;


    {
        scope in_StateAttribute = class_<StateAttribute, bases<Object>, ref_ptr<StateAttribute>, boost::noncopyable >("StateAttribute", no_init)
            //.def()
        ;

        // Need to use + instead of | to combine values, but otherwise works great.
        enum_<StateAttribute::Values>("Values")
            .value("OFF",       StateAttribute::OFF)
            .value("ON",        StateAttribute::ON)
            .value("OVERRIDE",  StateAttribute::OVERRIDE)
            .value("PROTECTED", StateAttribute::PROTECTED)
            .value("INHERIT",   StateAttribute::INHERIT)
        ;
        enum_<StateAttribute::Type>("Type")
            .value("TEXTURE",                     StateAttribute::TEXTURE)
            .value("POLYGONMODE",                 StateAttribute::POLYGONMODE)
            .value("POLYGONOFFSET",               StateAttribute::POLYGONOFFSET)
            .value("MATERIAL",                    StateAttribute::MATERIAL)
            .value("ALPHAFUNC",                   StateAttribute::ALPHAFUNC)
            .value("ANTIALIAS",                   StateAttribute::ANTIALIAS)
            .value("COLORTABLE",                  StateAttribute::COLORTABLE)
            .value("CULLFACE",                    StateAttribute::CULLFACE)
            .value("FOG",                         StateAttribute::FOG)
            .value("FRONTFACE",                   StateAttribute::FRONTFACE)
            .value("LIGHT",                       StateAttribute::LIGHT)
            .value("POINT",                       StateAttribute::POINT)
            .value("LINEWIDTH",                   StateAttribute::LINEWIDTH)
            .value("LINESTIPPLE",                 StateAttribute::LINESTIPPLE)
            .value("POLYGONSTIPPLE",              StateAttribute::POLYGONSTIPPLE)
            .value("SHADEMODEL",                  StateAttribute::SHADEMODEL)
            .value("TEXENV",                      StateAttribute::TEXENV)
            .value("TEXENVFILTER",                StateAttribute::TEXENVFILTER)
            .value("TEXGEN",                      StateAttribute::TEXGEN)
            .value("TEXMAT",                      StateAttribute::TEXMAT)
            .value("LIGHTMODEL",                  StateAttribute::LIGHTMODEL)
            .value("BLENDFUNC",                   StateAttribute::BLENDFUNC)
            .value("BLENDEQUATION",               StateAttribute::BLENDEQUATION)
            .value("LOGICOP",                     StateAttribute::LOGICOP)
            .value("STENCIL",                     StateAttribute::STENCIL)
            .value("COLORMASK",                   StateAttribute::COLORMASK)
            .value("DEPTH",                       StateAttribute::DEPTH)
            .value("VIEWPORT",                    StateAttribute::VIEWPORT)
            .value("SCISSOR",                     StateAttribute::SCISSOR)
            .value("BLENDCOLOR",                  StateAttribute::BLENDCOLOR)
            .value("MULTISAMPLE",                 StateAttribute::MULTISAMPLE)
            .value("CLIPPLANE",                   StateAttribute::CLIPPLANE)
            .value("COLORMATRIX",                 StateAttribute::COLORMATRIX)
            .value("VERTEXPROGRAM",               StateAttribute::VERTEXPROGRAM)
            .value("FRAGMENTPROGRAM",             StateAttribute::FRAGMENTPROGRAM)
            .value("POINTSPRITE",                 StateAttribute::POINTSPRITE)
            .value("PROGRAM",                     StateAttribute::PROGRAM)
            .value("CLAMPCOLOR",                  StateAttribute::CLAMPCOLOR)
            .value("HINT",                        StateAttribute::HINT)
            .value("VALIDATOR",                   StateAttribute::VALIDATOR)
            .value("VIEWMATRIXEXTRACTOR",         StateAttribute::VIEWMATRIXEXTRACTOR)
            .value("OSGNV_PARAMETER_BLOCK",       StateAttribute::OSGNV_PARAMETER_BLOCK)
            .value("OSGNVEXT_TEXTURE_SHADER",     StateAttribute::OSGNVEXT_TEXTURE_SHADER)
            .value("OSGNVEXT_VERTEX_PROGRAM",     StateAttribute::OSGNVEXT_VERTEX_PROGRAM)
            .value("OSGNVEXT_REGISTER_COMBINERS", StateAttribute::OSGNVEXT_REGISTER_COMBINERS)
            .value("OSGNVCG_PROGRAM",             StateAttribute::OSGNVCG_PROGRAM)
            .value("OSGNVSLANG_PROGRAM",          StateAttribute::OSGNVSLANG_PROGRAM)
            .value("OSGNVPARSE_PROGRAM_PARSER",   StateAttribute::OSGNVPARSE_PROGRAM_PARSER)
        ;
    }

    {
        scope in_StateSet = class_<StateSet, bases<Object>, ref_ptr<StateSet> >("StateSet")
            .def("getNumParents", &StateSet::getNumParents)
            .def("getParents", StateSet_getParents1, return_value_policy<return_by_value>())
            .def("getParent", StateSet_getParent1, return_value_policy<reference_existing_object>())
            .def("setMode", StateSet_setMode1)
            .def("removeMode", &StateSet::removeMode)
            .def("getMode", StateSet_getMode1)
            .def("setTextureMode", &StateSet::setTextureMode)
            .def("removeTextureMode", &StateSet::removeTextureMode)
            .def("getTextureMode", &StateSet::getTextureMode)
        ;
    }
}