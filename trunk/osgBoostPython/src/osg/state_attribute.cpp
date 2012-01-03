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

#include <osg/StateAttribute>

using namespace osg;

#include "defaults.h"
    ;
void export_StateAttribute()
{
  scope in_StateAttribute = class_<StateAttribute, ref_ptr<StateAttribute>, boost::noncopyable >
    ("StateAttribute", no_init)
    ;

  enum_<StateAttribute::Values>("Values");
  scope().attr("OFF") =  StateAttribute::OFF;
  scope().attr("ON") =  StateAttribute::ON;
  scope().attr("OVERRIDE") =  StateAttribute::OVERRIDE;
  scope().attr("PROTECTED") =  StateAttribute::PROTECTED;
  scope().attr("INHERIT") =  StateAttribute::INHERIT;

  enum_<StateAttribute::Type>("Type");
  scope().attr(" TEXTURE") = StateAttribute::TEXTURE;
  scope().attr(" POLYGONMODE") = StateAttribute::POLYGONMODE;
  scope().attr(" POLYGONOFFSET")= StateAttribute::POLYGONOFFSET;
  scope().attr(" MATERIAL") = StateAttribute::MATERIAL;
  scope().attr(" ALPHAFUNC") = StateAttribute:: ALPHAFUNC;
  scope().attr(" ANTIALIAS") = StateAttribute::ANTIALIAS;
  scope().attr(" COLORTABLE") = StateAttribute::COLORTABLE;
  scope().attr(" CULLFACE") = StateAttribute::CULLFACE;
  scope().attr(" FOG") = StateAttribute::FOG;
  scope().attr(" FRONTFACE") = StateAttribute::FRONTFACE;
  scope().attr(" LIGHT") = StateAttribute::LIGHT;
  scope().attr(" POINT") = StateAttribute::POINT;
  scope().attr(" LINEWIDTH") = StateAttribute::LINEWIDTH;
  scope().attr(" LINESTIPPLE") = StateAttribute::LINESTIPPLE;
  scope().attr(" POLYGONSTIPPLE") = StateAttribute::POLYGONSTIPPLE;
  scope().attr(" SHADEMODEL") = StateAttribute::SHADEMODEL;
  scope().attr(" TEXENV") = StateAttribute::TEXENV;
  scope().attr(" TEXENVFILTER") = StateAttribute::TEXENVFILTER;
  scope().attr(" TEXGEN") = StateAttribute::TEXGEN;
  scope().attr(" TEXMAT") = StateAttribute::TEXMAT;
  scope().attr(" LIGHTMODEL") = StateAttribute::LIGHTMODEL;
  scope().attr(" BLENDFUNC") = StateAttribute::BLENDFUNC;
  scope().attr(" BLENDEQUATION") = StateAttribute::BLENDEQUATION;
  scope().attr(" LOGICOP") = StateAttribute::LOGICOP;
  scope().attr(" STENCIL") = StateAttribute::STENCIL;
  scope().attr(" COLORMASK") = StateAttribute::COLORMASK;
  scope().attr(" DEPTH") = StateAttribute::DEPTH;
  scope().attr(" VIEWPORT") = StateAttribute::VIEWPORT;
  scope().attr(" SCISSOR") = StateAttribute::SCISSOR;
  scope().attr(" BLENDCOLOR") = StateAttribute::BLENDCOLOR;
  scope().attr(" MULTISAMPLE") = StateAttribute::MULTISAMPLE;
  scope().attr(" CLIPPLANE") = StateAttribute::CLIPPLANE;
  scope().attr(" COLORMATRIX") = StateAttribute::COLORMATRIX;
  scope().attr(" VERTEXPROGRAM") = StateAttribute::VERTEXPROGRAM;
  scope().attr(" FRAGMENTPROGRAM") = StateAttribute::FRAGMENTPROGRAM;
  scope().attr(" POINTSPRITE") = StateAttribute::POINTSPRITE;
  scope().attr(" PROGRAM") = StateAttribute::PROGRAM;
  scope().attr(" CLAMPCOLOR") = StateAttribute::CLAMPCOLOR;
  scope().attr(" HINT") = StateAttribute::HINT;
  scope().attr(" VALIDATOR") = StateAttribute::VALIDATOR;
  scope().attr(" VIEWMATRIXEXTRACTOR") = StateAttribute::VIEWMATRIXEXTRACTOR;
  scope().attr(" OSGNV_PARAMETER_BLOCK") = StateAttribute::OSGNV_PARAMETER_BLOCK;
  scope().attr(" OSGNVEXT_TEXTURE_SHADER") = StateAttribute::OSGNVEXT_TEXTURE_SHADER;
  scope().attr(" OSGNVEXT_VERTEX_PROGRAM") = StateAttribute::OSGNVEXT_VERTEX_PROGRAM;
  scope().attr(" OSGNVEXT_REGISTER_COMBINERS") = StateAttribute::OSGNVEXT_REGISTER_COMBINERS;
  scope().attr(" OSGNVCG_PROGRAM") = StateAttribute::OSGNVCG_PROGRAM;
  scope().attr(" OSGNVSLANG_PROGRAM") = StateAttribute::OSGNVSLANG_PROGRAM;
  scope().attr(" OSGNVPARSE_PROGRAM_PARSER") = StateAttribute::OSGNVPARSE_PROGRAM_PARSER;
  scope().attr(" UNIFORMBUFFERBINDING") = StateAttribute::UNIFORMBUFFERBINDING;
  scope().attr("TRANSFORMFEEDBACKBUFFERBINDING") = StateAttribute::TRANSFORMFEEDBACKBUFFERBINDING;

}
