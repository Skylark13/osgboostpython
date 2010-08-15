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

#include "PythonInterpreter.h"

using namespace boost::python;

PythonInterpreter::PythonInterpreter()
{
    Py_Initialize();

    _main_module = object((handle<>(borrowed(PyImport_AddModule("__main__")))));
    _main_namespace = _main_module.attr("__dict__");
}

PythonInterpreter::~PythonInterpreter()
{
    Py_Finalize();
}

void PythonInterpreter::execute(const std::string& command)
{
    try 
    {
        handle<> ignored(( PyRun_String( command.c_str(),
                                         Py_file_input,
                                         _main_namespace.ptr(),
                                         _main_namespace.ptr() ) ));
    }
    catch( error_already_set )
    {
        PyErr_Print();
    }
}