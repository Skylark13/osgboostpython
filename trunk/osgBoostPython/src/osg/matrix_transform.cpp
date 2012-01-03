/**
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
#include <osg/Transform>
#include <osg/MatrixTransform>

using namespace osg;

#include "defaults.h"

void export_MatrixTransform()
{

    class_<MatrixTransform, bases<Transform>, ref_ptr<MatrixTransform> >("MatrixTransform")
        .def(init<Matrixd>())
        .add_property("matrix", make_function(&MatrixTransform::getMatrix, osgBoostPython::default_const_reference_policy()), 
		      &MatrixTransform::setMatrix)
        .def("setMatrix", &MatrixTransform::setMatrix)
        .def("getMatrix", &MatrixTransform::getMatrix, osgBoostPython::default_const_reference_policy())
        .def("preMult", &MatrixTransform::preMult)
        .def("postMult", &MatrixTransform::postMult)
        .def("getInverseMatrix", &MatrixTransform::getInverseMatrix, osgBoostPython::default_const_reference_policy())
        //.def("computeLocalToWorldMatrix", &MatrixTransform::computeLocalToWorldMatrix)
        //.def("computeWorldToLocalMatrix", &MatrixTransform::computeWorldToLocalMatrix)
    ;
}
