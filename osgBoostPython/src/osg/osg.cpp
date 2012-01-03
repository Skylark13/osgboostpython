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

// Good sources of information:
// http://wiki.python.org/moin/boost.python
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/tutorial/doc/html/index.html
// http://www.boost.org/doc/libs/1_36_0/libs/python/doc/v2/faq.html

// General Python info
// http://docs.python.org/tut/

#include <boost/python.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
// Sure, "Computational Crystallography Toolbox" doesn't seem like it applies 
// to us, but there's a lot of good example code for wrapping containers, etc.
// http://cctbx.sourceforge.net/
// http://cctbx.svn.sourceforge.net/viewvc/cctbx/trunk/scitbx/
using namespace boost::python;

#include <osg/ref_ptr>
using namespace osg;

#include <osg/GL>
#include "defaults.h"

// Definitions in other source files
// Need to order these by depth in the class hierarchy
// Let's just make it look like the tree
#define EXPORT_THESE \
  (OpenGL)\
  (Matrix)\
  (Math) \
  (Plane) \
  (RenderInfo) \
  (CullSettings) \
  (Referenced) \
    (DisplaySettings) \
    (FrameStamp)\
    (Object)  \
      (Image) \
      (View)  \
      (Shape) \
      (Array) \
      (Uniform)\
      (Drawable) \
        (Geometry) \
        (ShapeDrawable) \
      (StateSet) \
      (NodeCallback) \
      (PrimitiveSet) \
      (StateAttribute) \
        (Texture) \
          (Texture2D) \
        (ColorMask) \
        (Depth) \
        (Stencil) \
        (ClipPlane) \
        (BlendFunc) \
      (Node) \
        (Geode) \
        (Group) \
          (ClipNode) \
          (Switch) \
          (LOD) \
          (Transform) \
            (Camera) \
            (MatrixTransform) \
            (PositionAttitudeTransform) \
    (NodeVisitor)\
  
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

OSGBP_MODULE(_osg, EXPORT_THESE)

