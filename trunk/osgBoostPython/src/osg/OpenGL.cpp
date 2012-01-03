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
#include <osg/GL>

void export_OpenGL()
{

  scope().attr("GL_ALPHA_TEST") =   GL_ALPHA_TEST;
  scope().attr("GL_AUTO_NORMAL") = GL_AUTO_NORMAL;
  scope().attr("GL_BLEND") = GL_BLEND;
  scope().attr("GL_CLIP_PLANE0") = GL_CLIP_PLANE0;
  scope().attr("GL_CLIP_PLANE1") =  GL_CLIP_PLANE1; 
  scope().attr("GL_CLIP_PLANE2") =   GL_CLIP_PLANE2;
  scope().attr("GL_CLIP_PLANE3") = GL_CLIP_PLANE3;
  scope().attr("GL_CLIP_PLANE4") = GL_CLIP_PLANE4;
  scope().attr("GL_CLIP_PLANE5") = GL_CLIP_PLANE5;
  scope().attr("GL_COLOR_LOGIC_OP") =  GL_COLOR_LOGIC_OP; 
  scope().attr("GL_COLOR_MATERIAL") =   GL_COLOR_MATERIAL;
  scope().attr("GL_CULL_FACE") = GL_CULL_FACE;
  scope().attr("GL_DEPTH_TEST") = GL_DEPTH_TEST;
  scope().attr("GL_DITHER") = GL_DITHER;
  scope().attr("GL_FOG") =  GL_FOG; 
  scope().attr("GL_INDEX_LOGIC_OP") =   GL_INDEX_LOGIC_OP;
  scope().attr("GL_LIGHT0") = GL_LIGHT0;
  scope().attr("GL_LIGHT1") = GL_LIGHT1;
  scope().attr("GL_LIGHT2") = GL_LIGHT2;
  scope().attr("GL_LIGHT3") =  GL_LIGHT3; 
  scope().attr("GL_LIGHT4") =   GL_LIGHT4;
  scope().attr("GL_LIGHT5") = GL_LIGHT5;
  scope().attr("GL_LIGHT6") = GL_LIGHT6;
  scope().attr("GL_LIGHT7") = GL_LIGHT7;
  scope().attr("GL_LIGHTING") =  GL_LIGHTING; 
  scope().attr("GL_LINE_SMOOTH") =   GL_LINE_SMOOTH;
  scope().attr("GL_LINE_STIPPLE") = GL_LINE_STIPPLE;
  scope().attr("GL_MAP1_COLOR_4") = GL_MAP1_COLOR_4;
  scope().attr("GL_MAP1_INDEX") = GL_MAP1_INDEX;
  scope().attr("GL_MAP1_NORMAL") =  GL_MAP1_NORMAL; 
  scope().attr("GL_MAP1_TEXTURE_COORD_1") =   GL_MAP1_TEXTURE_COORD_1;
  scope().attr("GL_MAP1_TEXTURE_COORD_2") = GL_MAP1_TEXTURE_COORD_2;
  scope().attr("GL_MAP1_TEXTURE_COORD_3") = GL_MAP1_TEXTURE_COORD_3;
  scope().attr("GL_MAP1_TEXTURE_COORD_4") = GL_MAP1_TEXTURE_COORD_4;
  scope().attr("GL_MAP1_VERTEX_3") =  GL_MAP1_VERTEX_3; 
  scope().attr("GL_MAP1_VERTEX_4") =   GL_MAP1_VERTEX_4;
  scope().attr("GL_MAP2_COLOR_4") = GL_MAP2_COLOR_4;
  scope().attr("GL_MAP2_INDEX") = GL_MAP2_INDEX;
  scope().attr("GL_MAP2_NORMAL") = GL_MAP2_NORMAL;
  scope().attr("GL_MAP2_TEXTURE_COORD_1") =  GL_MAP2_TEXTURE_COORD_1; 
  scope().attr("GL_MAP2_TEXTURE_COORD_2") =   GL_MAP2_TEXTURE_COORD_2;
  scope().attr("GL_MAP2_TEXTURE_COORD_3") = GL_MAP2_TEXTURE_COORD_3;
  scope().attr("GL_MAP2_TEXTURE_COORD_4") = GL_MAP2_TEXTURE_COORD_4;
  scope().attr("GL_MAP2_VERTEX_3") = GL_MAP2_VERTEX_3;
  scope().attr("GL_MAP2_VERTEX_4") =  GL_MAP2_VERTEX_4; 
  scope().attr("GL_NORMALIZE") =   GL_NORMALIZE;
  scope().attr("GL_POINT_SMOOTH") = GL_POINT_SMOOTH;
  scope().attr("GL_POLYGON_OFFSET_FILL") = GL_POLYGON_OFFSET_FILL;
  scope().attr("GL_POLYGON_OFFSET_LINE") = GL_POLYGON_OFFSET_LINE;
  scope().attr("GL_POLYGON_OFFSET_POINT") =  GL_POLYGON_OFFSET_POINT; 
  scope().attr("GL_POLYGON_SMOOTH") =   GL_POLYGON_SMOOTH;
  scope().attr("GL_POLYGON_STIPPLE") =     GL_POLYGON_STIPPLE;
  scope().attr("GL_SCISSOR_TEST") = GL_SCISSOR_TEST;
  scope().attr("GL_STENCIL_TEST") = GL_STENCIL_TEST;
  scope().attr("GL_TEXTURE_1D") =  GL_TEXTURE_1D; 
  scope().attr("GL_TEXTURE_2D") =   GL_TEXTURE_2D;
  scope().attr("GL_TEXTURE_GEN_Q") = GL_TEXTURE_GEN_Q;
  scope().attr("GL_TEXTURE_GEN_R") = GL_TEXTURE_GEN_R;
  scope().attr("GL_TEXTURE_GEN_S") = GL_TEXTURE_GEN_S;
  scope().attr("GL_TEXTURE_GEN_T") =  GL_TEXTURE_GEN_T; 

}
