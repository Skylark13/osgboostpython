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

#ifndef __PYTHON_INTERPRETER_H__
#define __PYTHON_INTERPRETER_H__

#include <boost/python.hpp>

class PythonInterpreter
{
public:
    PythonInterpreter();
    ~PythonInterpreter();

    void execute(const std::string& command);
    std::string getOutput();

private:
    boost::python::object _main_module;
    boost::python::object _main_namespace;
};

#endif  // __PYTHON_INTERPRETER_H__
