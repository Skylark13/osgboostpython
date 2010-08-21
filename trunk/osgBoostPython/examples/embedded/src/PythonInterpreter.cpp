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

// This code initially from http://wiki.python.org/moin/boost.python/EmbeddingPython
// with some modifications.

#include "PythonInterpreter.h"

using namespace boost::python;


PythonInterpreter::PythonInterpreter()
{
    Py_Initialize();

    _main_module = object((handle<>(borrowed(PyImport_AddModule("__main__")))));
    _main_namespace = _main_module.attr("__dict__");

    // http://osdir.com/ml/python.c++/2003-11/msg00295.html
    handle<> outputCatcher(
        PyRun_String(
            "class OutputCatcher:\n"
                "\tdef __init__(self):\n"
                    "\t\tself.data = ''\n"
                "\tdef write(self, stuff):\n"
                    "\t\tself.data = self.data + stuff\n\n"
                "\tdef clear(self):\n"
                    "\t\tself.data = ''\n\n"
            "import sys\n"
            "_catcher = OutputCatcher()\n"
            "sys.stdout = _catcher\n"
            "sys.stderr = _catcher\n",
            Py_file_input, _main_namespace.ptr(), _main_namespace.ptr()));
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

std::string PythonInterpreter::getOutput()
{
    // http://osdir.com/ml/python.c++/2003-11/msg00295.html
    // get the string data out of this object.
    std::string output = "cannot print exception";
    object catcher(_main_namespace["_catcher"]);
    object cstr(catcher.attr("data"));
    if (char *sstr = PyString_AsString(cstr.ptr()))
        output = sstr;

    handle<> clearCatcher(
        PyRun_String(
            "_catcher.clear()\n",
            Py_file_input, _main_namespace.ptr(), _main_namespace.ptr()));

    return output;
}
